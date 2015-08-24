/*
 * super.c
 */

#include <linux/export.h>
#include <linux/statfs.h>
#include <linux/seq_file.h>
#include "scfs.h"

extern struct read_buffer_cache buffer_cache[];
extern spinlock_t buffer_cache_lock;

static struct kobject *scfs_kobj;
static const char * scfs_version = "v. SCFSLA1";

static ssize_t version_show(struct kobject *kobj,
			    struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, scfs_version);
}

static struct kobj_attribute version_attr = __ATTR_RO(version);

#ifdef CONFIG_SYSTEM_COMPRESSED
static const char * system_type = "scfs";
#else
static const char * system_type = "ext4";
#endif

static ssize_t system_type_show(struct kobject *kobj,
			    struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, system_type);
}

static struct kobj_attribute system_type_attr = __ATTR_RO(system_type);

static struct attribute *attributes[] = {
	&system_type_attr.attr,
	&version_attr.attr,
	NULL,
};

static struct attribute_group attr_group = {
	.attrs = attributes,
};

static struct inode *scfs_alloc_inode(struct super_block *sb)
{
	struct scfs_inode_info *sii;
#if SCFS_PROFILE_MEM
	struct scfs_sb_info *sbi = SCFS_S(sb);
#endif

	sii = kmem_cache_alloc(scfs_inode_info_cache, GFP_KERNEL);
	if (!sii)
		return NULL;
#if SCFS_PROFILE_MEM
	atomic_add(sizeof(struct scfs_inode_info), &sbi->kmcache_size);
#endif

	memset(sii, 0, offsetof(struct scfs_inode_info, vfs_inode));
	sii->vfs_inode.i_version = 1;
	if (SCFS_S(sb)->options.flags & SCFS_DATA_COMPRESS)
		sii->flags |= SCFS_DATA_COMPRESS;

	mutex_init(&sii->lower_file_mutex);
	mutex_init(&sii->cinfo_list_mutex);
	INIT_LIST_HEAD(&sii->cinfo_list);
	return &sii->vfs_inode;
}

static void scfs_destroy_inode(struct inode *inode)
{
	struct scfs_inode_info *sii = SCFS_I(inode);
#if SCFS_PROFILE_MEM
	struct scfs_sb_info *sbi = SCFS_S(inode->i_sb);
#endif

	if (sii->cinfo_array) {
		vfree(sii->cinfo_array);
#if SCFS_PROFILE_MEM
		atomic_sub(sii->cinfo_array_size, &sbi->vmalloc_size);
#endif
	}
	/*
	if (sii->cluster_buffer.c_buffer)
		scfs_free_mempool_buffer(sii->cluster_buffer.c_page,
			SCFS_S(inode->i_sb));

	if (sii->cluster_buffer.u_buffer)
		scfs_free_mempool_buffer(sii->cluster_buffer.u_page,
			SCFS_S(inode->i_sb));
		*/

	kmem_cache_free(scfs_inode_info_cache, sii);
#if SCFS_PROFILE_MEM
	atomic_sub(sizeof(struct scfs_inode_info), &sbi->kmcache_size);
#endif
}

static void scfs_evict_inode(struct inode *inode)
{
	struct inode *lower_inode;
	struct scfs_inode_info *sii = SCFS_I(inode);
#if SCFS_PROFILE_MEM
	struct scfs_sb_info *sbi = SCFS_S(inode->i_sb);
#endif

	truncate_inode_pages(&inode->i_data, 0);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	clear_inode(inode);
#else
	end_writeback(inode);
#endif
	// for save memory, evicted inode won't keep the cluster info
	if (sii->cinfo_array) {
		vfree(sii->cinfo_array);
#if SCFS_PROFILE_MEM
		atomic_sub(sii->cinfo_array_size, &sbi->vmalloc_size);
#endif
		sii->cinfo_array = NULL;
	}
	lower_inode = scfs_lower_inode(inode);
	scfs_set_lower_inode(inode, NULL);
	iput(lower_inode);
}

static int scfs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	int ret;
	struct dentry *lower_dentry = scfs_lower_dentry(dentry);

	SCFS_DEBUG_START;
	
	ret = lower_dentry->d_sb->s_op->statfs(lower_dentry, buf);
	if (ret)
		return ret;

	buf->f_type = SCFS_SUPER_MAGIC;

	SCFS_DEBUG_END;
	
	return ret;
}

static int scfs_show_options(struct seq_file *m, struct dentry *root)
{
	struct scfs_sb_info *sbi = SCFS_S(root->d_sb);
	struct scfs_mount_options *opts = &sbi->options;

	if (!(opts->flags & SCFS_DATA_COMPRESS))
		seq_printf(m, ",nocomp");
	if (opts->cluster_size)
		seq_printf(m, ",cluster_size=%u", opts->cluster_size);
	if (opts->comp_threshold)
		seq_printf(m, ",comp_threshold=%u", opts->comp_threshold);

	switch (opts->comp_type) {
	case LZO:
		seq_printf(m, ",comp_type=lzo");
		break;
	case BZIP2:
		seq_printf(m, ",comp_type=bzip2");
		break;
	case ZLIB:
		seq_printf(m, ",comp_type=zlib");
		break;
	case FASTLZO:
		seq_printf(m, ",comp_type=fastlzo");
		break;
	default:
		break;
	}

	return 0;
}

static struct dentry *scfs_mount(struct file_system_type *fs_type, int flags,
				const char *dev_name, void *raw_data)
{
	struct super_block *sb;
	struct scfs_sb_info *sbi;
	struct scfs_dentry_info *root_info;
	struct inode *inode;
	struct path path;
	int ret, i;

	sbi = kzalloc(sizeof(struct scfs_sb_info), GFP_KERNEL);
	if (!sbi) {
		ret = -ENOMEM;
		return ERR_PTR(ret);
	}
#if SCFS_PROFILE_MEM
	atomic_add(sizeof(struct scfs_sb_info), &sbi->kmalloc_size);
#endif

	// setting default values
	sbi->options.flags |= SCFS_DATA_COMPRESS;
	sbi->options.comp_threshold = 50;
	ret = scfs_parse_options(sbi, raw_data);
	if (ret) {
		/* parse err */
		goto out_free;
	}

	if (!sbi->options.cluster_size)
		sbi->options.cluster_size = SCFS_CLUSTER_SIZE_DEF;
	if (!sbi->options.comp_type)
		sbi->options.comp_type = LZO;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	sb = sget(fs_type, NULL, set_anon_super, flags, NULL);
#else
	sb = sget(fs_type, NULL, set_anon_super, NULL);
#endif
	if (IS_ERR(sb)) {
		//ret = sb;
		goto out_free;
	}

	ret = bdi_setup_and_register(&sbi->bdi, "scfs", BDI_CAP_MAP_COPY);
	if (ret)
			goto out_free;

	sb->s_bdi = &sbi->bdi;
	sb->s_bdi->ra_pages = VM_MAX_READAHEAD * 1024 / PAGE_CACHE_SIZE;
	sb->s_fs_info = sbi;

	sb->s_op = &scfs_sops;
	sb->s_d_op = &scfs_dops;
	
	ret= kern_path(dev_name, LOOKUP_FOLLOW | LOOKUP_DIRECTORY, &path);
	if (ret) {
		goto out_deactivate;
	}

	scfs_set_lower_super(sb, path.dentry->d_sb);
	sb->s_maxbytes = path.dentry->d_sb->s_maxbytes;
	sb->s_blocksize = path.dentry->d_sb->s_blocksize;
	sb->s_magic = SCFS_SUPER_MAGIC;

	inode = scfs_get_inode(path.dentry->d_inode, sb);
	if (IS_ERR(inode)) {
		//ret = ERR_PTR(ret);
		goto out_pathput;
	}

	sb->s_root = d_make_root(inode);
	if (!sb->s_root) {
		ret = -ENOMEM;
		goto out_pathput;
	}
		
	root_info = kmem_cache_zalloc(scfs_dentry_info_cache, GFP_KERNEL);
	if (!root_info)
		goto out_pathput;
#if SCFS_PROFILE_MEM
	atomic_add(sizeof(struct scfs_dentry_info), &sbi->kmcache_size);
#endif

	sb->s_root->d_fsdata = root_info;
	scfs_set_lower_dentry(sb->s_root, path.dentry);
	scfs_set_dentry_lower_mnt(sb->s_root, path.mnt);

	/* (oversized) shared mempool for read/write cluster buffers. */
	//TODO this may fail if we mount too late and memory is too fragmented
	sbi->mempool = mempool_create_page_pool(SCFS_MEMPOOL_COUNT, 
		SCFS_MEMPOOL_ORDER);
	if (!sbi->mempool) {
		SCFS_PRINT_ERROR("mempool create failed!\n");
		ret = -ENOMEM;
		goto out_pathput;
	}
	
	for (i = 0; i < MAX_BUFFER_CACHE; i++) {
		buffer_cache[i].u_page = scfs_alloc_mempool_buffer(sbi);
		buffer_cache[i].c_page = scfs_alloc_mempool_buffer(sbi);
		if (buffer_cache[i].u_page == NULL ||
				buffer_cache[i].c_page == NULL) {
			SCFS_PRINT_ERROR("mempool alloc failed!\n");
			ret = -ENOMEM;
			goto out_pathput;
		}
		buffer_cache[i].inode_number = -1;
		buffer_cache[i].cluster_number = -1;
		buffer_cache[i].is_compressed = -1;
		atomic_set(&buffer_cache[i].is_used, -1);
	}
	spin_lock_init(&buffer_cache_lock);

	SCFS_PRINT_ALWAYS("%s (mempool %d KB x %d)\n", scfs_version,
		SCFS_MEMPOOL_SIZE / 1024, SCFS_MEMPOOL_COUNT);

	sb->s_flags |= MS_ACTIVE;
	return dget(sb->s_root);

out_pathput:
	path_put(&path);	
out_deactivate:
	deactivate_locked_super(sb);
out_free:
	kfree(sbi);
	
	return ERR_PTR(ret);
}

static void scfs_kill_block_super(struct super_block *sb)
{
	struct scfs_sb_info *sbi = SCFS_S(sb);

	if (!sbi)
		return;

	if (sbi->mempool)
		mempool_destroy(sbi->mempool);

	kill_anon_super(sb);
	bdi_destroy(&sbi->bdi);
	kmem_cache_free(scfs_sb_info_cache, sbi);
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
static int scfs_d_revalidate(struct dentry *dentry, unsigned int flags)
{
	struct dentry *lower_dentry;
	struct vfsmount *lower_mnt;
	int ret = 1;

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	lower_dentry = scfs_lower_dentry(dentry);
	lower_mnt = scfs_dentry_to_lower_mnt(dentry);
	if (!lower_dentry->d_op || !lower_dentry->d_op->d_revalidate)
		goto out;

	ret = lower_dentry->d_op->d_revalidate(lower_dentry, flags);

	if (dentry->d_inode) {
		struct inode *lower_inode =
			scfs_lower_inode(dentry->d_inode);

		fsstack_copy_attr_all(dentry->d_inode, lower_inode);
	}
out:
	return ret;
}
#else
static int scfs_d_revalidate(struct dentry *dentry, struct nameidata *nd)
{
	struct dentry *lower_dentry;
	struct vfsmount *lower_mnt;
	struct dentry *dentry_save = NULL;
	struct vfsmount *vfsmount_save = NULL;
	int ret = 1;

	if (nd && nd->flags & LOOKUP_RCU)
		return -ECHILD;

	lower_dentry = scfs_lower_dentry(dentry);
	lower_mnt = scfs_dentry_to_lower_mnt(dentry);
	if (!lower_dentry->d_op || !lower_dentry->d_op->d_revalidate)
		goto out;
	if (nd) {
		dentry_save = nd->path.dentry;
		vfsmount_save = nd->path.mnt;
		nd->path.dentry = lower_dentry;
		nd->path.mnt = lower_mnt;
	}
	ret = lower_dentry->d_op->d_revalidate(lower_dentry, nd);
	if (nd) {
		nd->path.dentry = dentry_save;
		nd->path.mnt = vfsmount_save;
	}
	if (dentry->d_inode) {
		struct inode *lower_inode =
			scfs_lower_inode(dentry->d_inode);

		fsstack_copy_attr_all(dentry->d_inode, lower_inode);
	}
out:
	return ret;
}
#endif

static void scfs_d_release(struct dentry *dentry)
{
#if SCFS_PROFILE_MEM
	struct scfs_sb_info *sbi = SCFS_S(dentry->d_sb);
#endif
	if (SCFS_D(dentry)) {
		if (scfs_lower_dentry(dentry)) {
			dput(scfs_lower_dentry(dentry));
			mntput(scfs_dentry_to_lower_mnt(dentry));
		}
		kmem_cache_free(scfs_dentry_info_cache,
				SCFS_D(dentry));
#if SCFS_PROFILE_MEM
		atomic_sub(sizeof(struct scfs_dentry_info), &sbi->kmcache_size);
#endif
	}
	return;
}

static struct file_system_type scfs_fs_type = {
	.owner		= THIS_MODULE,
	.name		= "scfs",
	.mount		= scfs_mount,
	.kill_sb	= scfs_kill_block_super, /* TODO is it OK? */
	.fs_flags	= 0 /* ??? */
};

const struct super_operations scfs_sops = {
	 .alloc_inode		= scfs_alloc_inode,
	 .destroy_inode		= scfs_destroy_inode,
	 .evict_inode		= scfs_evict_inode,
	 .statfs		= scfs_statfs,
	 .remount_fs		= NULL,
	 .show_options		= scfs_show_options,
 };

 const struct dentry_operations scfs_dops = {
	.d_revalidate = scfs_d_revalidate,
	.d_release = scfs_d_release,
 };

/*************************/
/* sysfs & init routines */
/*************************/

static int do_sysfs_registration(void)
{
	int ret;

	SCFS_DEBUG_START;
	
	scfs_kobj = kobject_create_and_add("scfs", fs_kobj);
	if (!scfs_kobj) {
		SCFS_PRINT_ERROR("unable to create scfs kset\n");
		ret = SCFS_ERR_OUT_OF_MEMORY;
		goto out;
	}
	ret = sysfs_create_group(scfs_kobj, &attr_group);
	if (ret) {
		SCFS_PRINT_ERROR("unable to create scfs version attributes\n");
		kobject_put(scfs_kobj);
	}

out:
	SCFS_DEBUG_END;
	
	return ret;
}

static void do_sysfs_unregistration(void)
{
	sysfs_remove_group(scfs_kobj, &attr_group);
	kobject_put(scfs_kobj);
}

static int __init scfs_init(void)
{
	int ret = SCFS_SUCCESS;

	SCFS_DEBUG_START;

	ret = scfs_init_kmem_caches();
	if (ret) {
		SCFS_PRINT_ERROR("kmem_cache init failed\n");
		goto out;
	}
	ret = do_sysfs_registration();
	if (ret) {
		SCFS_PRINT_ERROR("sysfs registration failed\n");
		goto out_free_kmem_caches;
	}
	ret = scfs_init_kthread();
	if (ret) {
		SCFS_PRINT_ERROR("kthread initialization failed; "
		       "ret = [%d]\n", ret);
		goto out_do_sysfs_unregistration;
	}
	ret = register_filesystem(&scfs_fs_type);
	if (ret) {
		SCFS_PRINT_ERROR("failed to register filesystem\n");
		goto out_destroy_kthread;
	}

	goto out;

out_destroy_kthread:
	scfs_destroy_kthread();
out_do_sysfs_unregistration:
	do_sysfs_unregistration();
out_free_kmem_caches:
	scfs_free_kmem_caches();
out:
	SCFS_DEBUG_END;
	return ret;
}

static void __exit scfs_exit(void)
{
	SCFS_DEBUG_START;
	scfs_destroy_kthread();
	do_sysfs_unregistration();
	unregister_filesystem(&scfs_fs_type);
	scfs_free_kmem_caches();
	SCFS_DEBUG_END;
}

module_init(scfs_init);
module_exit(scfs_exit);
