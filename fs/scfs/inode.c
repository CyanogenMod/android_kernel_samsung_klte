/*
 *  inode.c
 * empty comment
 */

#include <linux/dcache.h>
#include <linux/xattr.h>
#include "scfs.h"

/********************/
/* helper functions */
/********************/

static void unlock_dir(struct dentry *dir)
{
	mutex_unlock(&dir->d_inode->i_mutex);
	dput(dir);
}

static struct dentry *lock_parent(struct dentry *dentry)
{
	struct dentry *dir;

	dir = dget_parent(dentry);
	mutex_lock_nested(&(dir->d_inode->i_mutex), I_MUTEX_PARENT);
	return dir;
}

static int scfs_inode_test(struct inode *inode, void *lower_inode)
{
	if (scfs_lower_inode(inode) == (struct inode *)lower_inode)
		return 1;

	return 0;
}

static int scfs_inode_set(struct inode *inode, void *opaque)
{
	struct inode *lower_inode = opaque;

	scfs_set_lower_inode(inode, lower_inode);
	fsstack_copy_attr_all(inode, lower_inode);
	fsstack_copy_inode_size(inode, lower_inode);
	inode->i_ino = lower_inode->i_ino;
	inode->i_version++;
	inode->i_mapping->a_ops = &scfs_aops;
	inode->i_mapping->backing_dev_info = inode->i_sb->s_bdi;

	if (S_ISLNK(inode->i_mode))
		inode->i_op = &scfs_symlink_iops;
	else if (S_ISDIR(inode->i_mode))
		inode->i_op = &scfs_dir_iops;
	else
		inode->i_op = &scfs_file_iops;

	if (S_ISDIR(inode->i_mode))
		inode->i_fop = &scfs_dir_fops;
	else if (special_file(inode->i_mode))
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
	else
		inode->i_fop = &scfs_file_fops;

	return SCFS_SUCCESS;
}

static struct inode *_scfs_get_inode(struct inode *lower_inode,
					  struct super_block *sb)
{
	struct inode *inode;

	if (lower_inode->i_sb != SCFS_S(sb)->lower_sb)
		return ERR_PTR(-EXDEV);
	if (!igrab(lower_inode))
		return ERR_PTR(-ESTALE);
	inode = iget5_locked(sb, (unsigned long)lower_inode->i_ino,
			     scfs_inode_test, scfs_inode_set,
			     lower_inode);
	if (!inode) {
		iput(lower_inode);
		return ERR_PTR(-EACCES);
	}
	if (!(inode->i_state & I_NEW))
		iput(lower_inode);

	return inode;
}

struct inode *scfs_get_inode(struct inode *lower_inode,
				 struct super_block *sb)
{
	struct inode *inode = _scfs_get_inode(lower_inode, sb);

	if (!IS_ERR(inode) && (inode->i_state & I_NEW))
		unlock_new_inode(inode);

	return inode;
}

static int scfs_interpose(struct dentry *lower_dentry,
			      struct dentry *dentry, struct super_block *sb)
{
	struct inode *inode = scfs_get_inode(lower_dentry->d_inode, sb);

	if (IS_ERR(inode))
		return PTR_ERR(inode);

	d_instantiate(dentry, inode);

	return SCFS_SUCCESS;
}

/* need to check parameters in calling vfs_write,
 * especially data buf 
 */
int scfs_make_header(struct dentry *scfs_dentry, struct inode *scfs_inode)
{
	struct scfs_sb_info *sbi = SCFS_S(scfs_inode->i_sb);
	struct file *lower_file = SCFS_I(scfs_inode)->lower_file;
	struct comp_footer cf;
	loff_t pos = 0;
	int ret;

	SCFS_DEBUG_START;

	if (!lower_file) {
		SCFS_PRINT_ERROR("lower_file is null\n");
		return SCFS_ERR_IO;
	}

	cf.footer_size = sizeof(struct comp_footer);
	cf.cluster_size = sbi->options.cluster_size;
	cf.original_file_size = 0;
	cf.comp_type = sbi->options.comp_type;
	cf.magic = SCFS_MAGIC;

	ret = scfs_lower_write(lower_file, (char *)&cf,
				sizeof(struct comp_footer), &pos);
	mark_inode_dirty_sync(scfs_inode); // why?

	if (ret < 0) {
		SCFS_PRINT_ERROR("error in writing header\n");
		return ret;
	}
	ret = 0;

	SCFS_DEBUG_END;

	return ret;
}

int scfs_initialize_file(struct dentry *scfs_dentry, struct inode *scfs_inode)
{
	struct scfs_inode_info *sii = SCFS_I(scfs_inode);
	int ret = 0;

	SCFS_DEBUG_START;

	copy_mount_flags_to_inode_flags(scfs_inode, scfs_inode->i_sb);
	if (S_ISDIR(scfs_inode->i_mode)) {
		SCFS_PRINT_ERROR("it's a directory\n");
		sii->flags &= ~(SCFS_DATA_COMPRESS);
		goto out;
	}

	ret = scfs_get_lower_file(scfs_dentry, scfs_inode);
	if (ret) {
		SCFS_PRINT_ERROR("error in get_lower_file, ret : %d\n", ret);
		goto out;
	}

	ret = scfs_make_header(scfs_dentry, scfs_inode);
	if (ret)
		SCFS_PRINT_ERROR("error in make header\n");

	scfs_put_lower_file(scfs_inode);

out:
	SCFS_DEBUG_END;
	
	return ret;
}

static struct inode *
scfs_do_create(struct inode *parent_inode,
		struct dentry *scfs_dentry, umode_t mode)
{
	struct dentry *lower_file_dentry;
	struct dentry *lower_parent_dentry;
	struct inode *inode;
	int ret;

	SCFS_DEBUG_START;
	
	lower_file_dentry = scfs_lower_dentry(scfs_dentry);
	lower_parent_dentry = lock_parent(lower_file_dentry);

	if (IS_ERR(lower_parent_dentry)) {
		SCFS_PRINT_ERROR("lower_parent_dentry is invalid\n");
		inode = ERR_CAST(lower_parent_dentry);
		goto out;
	}
	ret = vfs_create(lower_parent_dentry->d_inode, lower_file_dentry,
			mode, NULL);
	if (ret) {
		SCFS_PRINT_ERROR("error in vfs_create, lower create, ret : %d\n", ret);
		inode = ERR_PTR(ret);
		goto unlock;
	}
	inode = _scfs_get_inode(lower_file_dentry->d_inode, parent_inode->i_sb);
	if (IS_ERR(inode)) {
		SCFS_PRINT_ERROR("error in get_inode, so lower thing will be unlinked\n");
		vfs_unlink(lower_parent_dentry->d_inode, lower_file_dentry);
		goto unlock;
	}
	fsstack_copy_attr_times(parent_inode, lower_parent_dentry->d_inode);
	fsstack_copy_inode_size(parent_inode, lower_parent_dentry->d_inode);

unlock:
	unlock_dir(lower_parent_dentry);
out:
	SCFS_DEBUG_END;
	
	return inode;
}

static int
scfs_do_unlink(struct inode *dir, struct dentry *dentry, struct inode *inode)
{
	struct dentry *lower_dentry = scfs_lower_dentry(dentry);
	struct inode *lower_dir_inode = scfs_lower_inode(dir);
	struct dentry *lower_dir_dentry;
	int ret;

	dget(lower_dentry);
	lower_dir_dentry = lock_parent(lower_dentry);
	ret = vfs_unlink(lower_dir_inode, lower_dentry);
	if (ret) {
		SCFS_PRINT_ERROR("error in vfs_unlink, ret : %d\n", ret);
		goto out;
	}
	fsstack_copy_attr_times(dir, lower_dir_inode);
	set_nlink(inode, scfs_lower_inode(inode)->i_nlink);
	inode->i_ctime = dir->i_ctime;
	d_drop(dentry);
out:
	unlock_dir(lower_dir_dentry);
	dput(lower_dentry);
	return ret;
}

/************************/
/* directory operations */
/************************/

/*
 * scfs_mkdir
 *
 * Parameters:
 * @*dir: inode of the dir to create
 * @*scfs_dentry: dentry of the dir to create
 * @mode:
 *
 * Return:
 * SCFS_SUCCESS if success, otherwise if error
 *
 * Description:
 * mkdir() for SCFS.
 */
static int scfs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	struct dentry *lower_dir_dentry;
	struct dentry *lower_parent_dentry;
	int ret;

	SCFS_DEBUG_START;
	
	lower_dir_dentry = scfs_lower_dentry(dentry);
	lower_parent_dentry = lock_parent(lower_dir_dentry);
	ret = vfs_mkdir(lower_parent_dentry->d_inode, lower_dir_dentry, mode);
	if (ret || !lower_dir_dentry->d_inode) {
		SCFS_PRINT_ERROR("dir %s vfs_mkdir failed, "
			"lower_dir %s lower_parent %s mode %x\n",
			dentry->d_name.name,
			lower_dir_dentry->d_name.name,
			lower_parent_dentry->d_name.name, mode);
		goto out;
	}
	ret = scfs_interpose(lower_dir_dentry, dentry, dir->i_sb);
	if (ret) {
		SCFS_PRINT_ERROR("dir %s interpose failed, "
			"lower_dir %s lower_parent %s mode %x\n",
			dentry->d_name.name,
			lower_dir_dentry->d_name.name,
			lower_parent_dentry->d_name.name, mode);
		vfs_rmdir(lower_parent_dentry->d_inode, lower_dir_dentry);
		goto out;
	}
	fsstack_copy_attr_times(dir, lower_parent_dentry->d_inode);
	fsstack_copy_inode_size(dir, lower_parent_dentry->d_inode);
	set_nlink(dir, lower_parent_dentry->d_inode->i_nlink);

out:
	unlock_dir(lower_parent_dentry);
	if (!dentry->d_inode)
		d_drop(dentry);

	SCFS_DEBUG_END;

	return ret;
}

/*
 * scfs_create
 *
 * Parameters:
 * @*parent_inode: inode of the parent directory
 * @*scfs_dentry: dentry of the file to create
 * @mode:
 * @*nd: nameidata
 *
 * Return:
 * SCFS_SUCCESS if success, otherwise if error
 *
 * Description:
 * create() for SCFS.
 */
static int scfs_create(struct inode *parent_inode, struct dentry *scfs_dentry,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
		umode_t mode, bool dummy)
#else
		umode_t mode, struct nameidata *nd)
#endif
{
	struct inode *scfs_inode;
	int ret;

	SCFS_DEBUG_START;
	
	scfs_inode = scfs_do_create(parent_inode, scfs_dentry, mode);
	
	if (!scfs_inode) {
		SCFS_PRINT_ERROR("file %s error in do_create\n",
			scfs_dentry->d_name.name);
		return PTR_ERR(scfs_inode);
	}
	ret = scfs_initialize_file(scfs_dentry, scfs_inode);
	if (ret) {
		scfs_do_unlink(parent_inode, scfs_dentry,
				   scfs_inode);
		make_bad_inode(scfs_inode);
		unlock_new_inode(scfs_inode);
		iput(scfs_inode);
	} else {
		d_instantiate(scfs_dentry, scfs_inode);
		unlock_new_inode(scfs_inode);
	}

	SCFS_DEBUG_END;
	
	return ret;
}

int scfs_footer_read(struct dentry *dentry, struct inode *inode)
{
	struct comp_footer cf;
	struct file *lower_file;
	struct scfs_inode_info *sii = SCFS_I(inode);
	loff_t offset;
	loff_t lower_file_size;
	int ret;

	SCFS_DEBUG_START;
	
	if (S_ISDIR(inode->i_mode))
		return -EISDIR;

	ret = scfs_get_lower_file(dentry, inode);
	if (ret) {
		SCFS_PRINT_ERROR("f:%s error getting lower file\n",
			dentry->d_name.name);
		return ret;
	}

	lower_file = sii->lower_file;
	lower_file_size = i_size_read(lower_file->f_mapping->host);
	offset = lower_file_size - CF_SIZE;
	if (offset < 0) {
		SCFS_PRINT_ERROR("f:%s lower file size wasn't bigger than "
			"footer size, i_size was %lld\n",
			dentry->d_name.name, lower_file_size);
		ASSERT(0);
	}
	ret = scfs_lower_read(lower_file, (char *)&cf, CF_SIZE, &offset);
	if (ret < 0) {
		SCFS_PRINT_ERROR("f:%s read comp_footer error, %d \n",
					dentry->d_name.name, ret);
		goto out;
	}

	if (cf.magic != SCFS_MAGIC || cf.footer_size < CF_SIZE ||
			cf.cluster_size < 0 ||
			cf.cluster_size > SCFS_CLUSTER_SIZE_MAX) {
		SCFS_PRINT_ERROR("f:%s invalid meta, magic : %x,"
		"cf.cluster_size %u, cf.comp_type %d, "
		"cf.footer_size %d, cf.original_file_size %lld, "
		"lower file size : %lld, cf_size %d, offset %lld\n",
		dentry->d_name.name, cf.magic, cf.cluster_size,
		cf.comp_type, cf.footer_size, cf.original_file_size,
		lower_file_size, CF_SIZE, offset);
		
		ret = SCFS_ERR_IO;
		goto out;
	}
	sii->cinfo_array_size = cf.footer_size - CF_SIZE;
	sii->cluster_size = cf.cluster_size;
	i_size_write(inode, cf.original_file_size);
	sii->comp_type = cf.comp_type;
	if (!sii->cinfo_array_size)
		sii->flags &= ~SCFS_DATA_COMPRESS;
	else
		sii->compressd = 1;

	ret = SCFS_SUCCESS;
out:
	SCFS_PRINT("f:%s calling put_lower_file\n",
			lower_file->f_path.dentry->d_name.name);
	scfs_put_lower_file(inode);

	SCFS_DEBUG_END;
	
	return ret;
}

static int scfs_lookup_interpose(struct dentry *dentry, struct dentry *lower_dentry,
				struct inode *dir)
{
	struct inode *inode, *lower_inode = lower_dentry->d_inode;
	struct scfs_dentry_info *dentry_info;
	struct vfsmount *lower_mnt;
	int ret = 0;
#if SCFS_PROFILE_MEM
	struct scfs_sb_info *sbi = SCFS_S(dentry->d_sb);
#endif

	lower_mnt = mntget(scfs_dentry_to_lower_mnt(dentry->d_parent));
	fsstack_copy_attr_atime(dir, lower_dentry->d_parent->d_inode);
	BUG_ON(!lower_dentry->d_count);

	if (!dentry->d_fsdata) {
		dentry_info = kmem_cache_alloc(scfs_dentry_info_cache, GFP_KERNEL);
		dentry->d_fsdata = dentry_info;
		if (!dentry_info) {
			SCFS_PRINT_ERROR("dentry_info alloc failed\n");
			dput(lower_dentry);
			mntput(lower_mnt);
			d_drop(dentry);
			return SCFS_ERR_OUT_OF_MEMORY;
		}
	}
#if SCFS_PROFILE_MEM
	atomic_add(sizeof(struct scfs_dentry_info), &sbi->kmcache_size);
#endif

	scfs_set_lower_dentry(dentry, lower_dentry);
	scfs_set_dentry_lower_mnt(dentry, lower_mnt);

	if (!lower_dentry->d_inode) {
		d_add(dentry, NULL);
		return SCFS_SUCCESS;
	}
	inode = _scfs_get_inode(lower_inode, dir->i_sb);
	if (IS_ERR(inode)) {
		SCFS_PRINT_ERROR("error in get_inode\n");
		return PTR_ERR(inode);
	}
	if (S_ISREG(inode->i_mode)) {
		// We should get the i_size.
		// it'll be done by scfs_footer_read func.
		ret = scfs_footer_read(dentry, inode);
		if (ret) {
			make_bad_inode(inode);
			return ret;
		}
	}
	else
		i_size_write(inode, i_size_read(lower_inode));

	if (inode->i_state & I_NEW)
		unlock_new_inode(inode);

	d_add(dentry, inode);

	return ret;
}

/*
 * scfs_lookup
 *  
 * XXX : not confirmed, sequence of getting and putting a ref
 *
 */
static struct dentry * scfs_lookup(struct inode *dir, struct dentry *dentry,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	unsigned int flags)
#else
	struct nameidata *nd)
#endif
{
	struct dentry *lower_dir_dentry, *lower_dentry;
	int ret = 0;

	SCFS_DEBUG_START;

	lower_dir_dentry = scfs_lower_dentry(dentry->d_parent);
	mutex_lock(&lower_dir_dentry->d_inode->i_mutex);
	lower_dentry = lookup_one_len(dentry->d_name.name, lower_dir_dentry,
					dentry->d_name.len);
	mutex_unlock(&lower_dir_dentry->d_inode->i_mutex);
	if (IS_ERR(lower_dentry)) {
		d_drop(dentry);
		return lower_dentry;
	}

	ret = scfs_lookup_interpose(dentry, lower_dentry, dir);

	SCFS_DEBUG_END;

	return ERR_PTR(ret);
}

static int scfs_rename(struct inode *old_dir, struct dentry *old_dentry,
		struct inode *new_dir, struct dentry *new_dentry)
{
	struct dentry *lower_old_dentry;
	struct dentry *lower_new_dentry;
	struct dentry *lower_old_dir_dentry;
	struct dentry *lower_new_dir_dentry;
	struct dentry *trap = NULL;
	struct inode *target_inode;
	int ret;

	SCFS_DEBUG_START;
	
	lower_old_dentry = scfs_lower_dentry(old_dentry);
	lower_new_dentry = scfs_lower_dentry(new_dentry);
	dget(lower_old_dentry);
	dget(lower_new_dentry);
	lower_old_dir_dentry = dget_parent(lower_old_dentry);
	lower_new_dir_dentry = dget_parent(lower_new_dentry);
	target_inode = new_dentry->d_inode;
	trap = lock_rename(lower_old_dir_dentry, lower_new_dir_dentry);
	/* source should not be ancestor of target */
	if (trap == lower_old_dentry) {
		ret = -EINVAL;
		goto out_lock;
	}
	/* target should not be ancestor of source */
	if (trap == lower_new_dentry) {
		ret = -ENOTEMPTY;
		goto out_lock;
	}
	ret = vfs_rename(lower_old_dir_dentry->d_inode, lower_old_dentry,
			lower_new_dir_dentry->d_inode, lower_new_dentry);
	if (ret)
		goto out_lock;
	if (target_inode)
		fsstack_copy_attr_all(target_inode,
				      scfs_lower_inode(target_inode));
	fsstack_copy_attr_all(new_dir, lower_new_dir_dentry->d_inode);
	if (new_dir != old_dir)
		fsstack_copy_attr_all(old_dir, lower_old_dir_dentry->d_inode);

out_lock:
	unlock_rename(lower_old_dir_dentry, lower_new_dir_dentry);
	dput(lower_new_dir_dentry);
	dput(lower_old_dir_dentry);
	dput(lower_new_dentry);
	dput(lower_old_dentry);

	SCFS_DEBUG_END;

	return ret;
}

static int scfs_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct dentry *lower_dentry;
	struct dentry *lower_dir_dentry;
	int ret;

	SCFS_DEBUG_START;
	
	lower_dentry = scfs_lower_dentry(dentry);
	dget(dentry);
	lower_dir_dentry = lock_parent(lower_dentry);
	dget(lower_dentry);
	ret = vfs_rmdir(lower_dir_dentry->d_inode, lower_dentry);
	dput(lower_dentry);
	if (!ret && dentry->d_inode)
		clear_nlink(dentry->d_inode);
	fsstack_copy_attr_times(dir, lower_dir_dentry->d_inode);
	set_nlink(dir, lower_dir_dentry->d_inode->i_nlink);
	unlock_dir(lower_dir_dentry);
	if (!ret)
		d_drop(dentry);
	dput(dentry);

	SCFS_DEBUG_END;

	return ret;
}

static int scfs_permission(struct inode *inode, int mask)
{
	return inode_permission(scfs_lower_inode(inode), mask);
}

int scfs_getattr(struct vfsmount *mnt, struct dentry *dentry, struct kstat *stat)
{
	struct kstat lower_stat;
	int ret;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	struct path path = {scfs_dentry_to_lower_mnt(dentry),
				scfs_lower_dentry(dentry)};
#endif
	SCFS_DEBUG_START;

	ret = vfs_getattr(
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
			&path,
#else
			scfs_dentry_to_lower_mnt(dentry),
			scfs_lower_dentry(dentry),
#endif
			&lower_stat);
	if (!ret) {
		fsstack_copy_attr_all(dentry->d_inode,
				      scfs_lower_inode(dentry->d_inode));
		generic_fillattr(dentry->d_inode, stat);
		stat->blocks = lower_stat.blocks;
	}

	SCFS_DEBUG_END;
	
	return ret;
}

static int scfs_unlink(struct inode *dir, struct dentry *dentry)
{
	return scfs_do_unlink(dir, dentry, dentry->d_inode);
}

static int scfs_symlink(struct inode *dir, struct dentry *dentry,
		const char *symname)
{
	struct dentry *lower_dentry;
	struct dentry *lower_dir_dentry;
	int ret;

	SCFS_DEBUG_START;

	lower_dentry = scfs_lower_dentry(dentry);
	dget(lower_dentry);
	lower_dir_dentry = lock_parent(lower_dentry);
	ret = vfs_symlink(lower_dir_dentry->d_inode, lower_dentry, symname);
	if (ret || !lower_dentry->d_inode)
		goto out;
	ret = scfs_interpose(lower_dentry, dentry, dir->i_sb);
	if (ret)
		goto out;
	fsstack_copy_attr_times(dir, lower_dir_dentry->d_inode);
	fsstack_copy_inode_size(dir, lower_dir_dentry->d_inode);
out:
	unlock_dir(lower_dir_dentry);
	dput(lower_dentry);
	if (!dentry->d_inode)
		d_drop(dentry);

	SCFS_DEBUG_END;

	return ret;
}

static int scfs_mknod(struct inode *dir, struct dentry *dentry,
		umode_t mode, dev_t dev)
{
	struct dentry *lower_dentry;
	struct dentry *lower_dir_dentry;
	int ret;

	SCFS_DEBUG_START;
	
	lower_dentry = scfs_lower_dentry(dentry);
	lower_dir_dentry = lock_parent(lower_dentry);
	ret = vfs_mknod(lower_dir_dentry->d_inode, lower_dentry, mode, dev);
	if (ret || !lower_dentry->d_inode)
		goto out;
	ret = scfs_interpose(lower_dentry, dentry, dir->i_sb);
	if (ret)
		goto out;
	fsstack_copy_attr_times(dir, lower_dir_dentry->d_inode);
	fsstack_copy_inode_size(dir, lower_dir_dentry->d_inode);
out:
	unlock_dir(lower_dir_dentry);
	if (!dentry->d_inode)
		d_drop(dentry);

	SCFS_DEBUG_END;

	return ret;
}

static int scfs_link(struct dentry *old_dentry, struct inode *dir,
			 struct dentry *new_dentry)
{
	struct dentry *lower_old_dentry;
	struct dentry *lower_new_dentry;
	struct dentry *lower_dir_dentry;
	u64 file_size_save;
	int ret;

	SCFS_DEBUG_START;

	file_size_save = i_size_read(old_dentry->d_inode);
	lower_old_dentry = scfs_lower_dentry(old_dentry);
	lower_new_dentry = scfs_lower_dentry(new_dentry);
	dget(lower_old_dentry);
	dget(lower_new_dentry);
	lower_dir_dentry = lock_parent(lower_new_dentry);
	ret = vfs_link(lower_old_dentry, lower_dir_dentry->d_inode,
		      lower_new_dentry);
	if (ret || !lower_new_dentry->d_inode)
		goto out;
	ret = scfs_interpose(lower_new_dentry, new_dentry, dir->i_sb);
	if (ret)
		goto out;
	fsstack_copy_attr_times(dir, lower_dir_dentry->d_inode);
	fsstack_copy_inode_size(dir, lower_dir_dentry->d_inode);
	set_nlink(old_dentry->d_inode,
		  scfs_lower_inode(old_dentry->d_inode)->i_nlink);
	i_size_write(new_dentry->d_inode, file_size_save);
out:
	unlock_dir(lower_dir_dentry);
	dput(lower_new_dentry);
	dput(lower_old_dentry);

	SCFS_DEBUG_END;

	return ret;
}

static int scfs_setattr(struct dentry *dentry, struct iattr *ia)
{
	struct inode *inode;
	struct inode *lower_inode;
	struct dentry *lower_dentry;
	struct iattr lower_ia;
	int ret = 0;

	SCFS_DEBUG_START;

	inode = dentry->d_inode;
	lower_inode = scfs_lower_inode(inode);
	lower_dentry = scfs_lower_dentry(dentry);

	ret = inode_change_ok(inode, ia);
	if (ret)
		goto out;

	memcpy(&lower_ia, ia, sizeof(lower_ia));
	if (ia->ia_valid & ATTR_FILE)
		lower_ia.ia_file = scfs_lower_file(ia->ia_file);
	if (ia->ia_valid & ATTR_SIZE) {
		ret = scfs_truncate(dentry, ia->ia_size);
		if (ret)
			goto out;
		lower_ia.ia_valid &= ~ATTR_SIZE;
	}
	// for what?
	if (lower_ia.ia_valid & (ATTR_KILL_SUID | ATTR_KILL_SGID))
		lower_ia.ia_valid &= ~ATTR_MODE;

	mutex_lock(&lower_dentry->d_inode->i_mutex);
	ret = notify_change(lower_dentry, &lower_ia);
	mutex_unlock(&lower_dentry->d_inode->i_mutex);
out:
	fsstack_copy_attr_all(inode, lower_inode);

	SCFS_DEBUG_END;

	return ret;

}

static int scfs_readlink(struct dentry *dentry, char __user *buf, int bufsiz)
{
	struct dentry *lower_dentry;
	char *kbuf;
	size_t kbufsiz = PATH_MAX, copied;
	mm_segment_t old_fs;
	int ret;
#if SCFS_PROFILE_MEM
	struct scfs_sb_info *sbi = SCFS_S(dentry->d_sb);
#endif

	SCFS_DEBUG_START;
	
	lower_dentry = scfs_lower_dentry(dentry);
	kbuf = kmalloc(kbufsiz, GFP_KERNEL);
	if (!kbuf) 
		return -ENOMEM;
#if SCFS_PROFILE_MEM
	atomic_add(PATH_MAX, &sbi->kmalloc_size);
#endif

	old_fs = get_fs();
	set_fs(get_ds());
	ret = lower_dentry->d_inode->i_op->readlink(lower_dentry,
						   (char __user *)kbuf,
						   kbufsiz);
	set_fs(old_fs);
	if (ret < 0)
		goto out;

	kbufsiz = ret;

	copied = min_t(size_t, bufsiz, kbufsiz);
	ret = copy_to_user(buf, kbuf, copied) ? -EFAULT : copied;

	fsstack_copy_attr_atime(dentry->d_inode,
				scfs_lower_dentry(dentry)->d_inode);
out:
	kfree(kbuf);
#if SCFS_PROFILE_MEM
	atomic_sub(PATH_MAX, &sbi->kmalloc_size);
#endif

	SCFS_DEBUG_END;

	return ret;
}

static void *scfs_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	char *buf;
	int len = PAGE_SIZE, ret;
	mm_segment_t old_fs;
#if SCFS_PROFILE_MEM
	struct scfs_sb_info *sbi = SCFS_S(dentry->d_sb);
#endif

	SCFS_DEBUG_START;

	buf = kmalloc(len, GFP_KERNEL);
	if (!buf) {
		buf = ERR_PTR(-ENOMEM);
		goto out;
	}
#if SCFS_PROFILE_MEM
	atomic_add(len, &sbi->kmalloc_size);
#endif
	old_fs = get_fs();
	set_fs(get_ds());
	ret = dentry->d_inode->i_op->readlink(dentry, (char __user *)buf, len);
	set_fs(old_fs);
	if (ret < 0) {
		kfree(buf);
#if SCFS_PROFILE_MEM
		atomic_sub(len, &sbi->kmalloc_size);
#endif
		buf = ERR_PTR(ret);
	} else
		buf[ret] = '\0';
out:
	nd_set_link(nd, buf);

	SCFS_DEBUG_END;

	return NULL;
}

static void scfs_put_link(struct dentry *dentry, struct nameidata *nd, void *ptr)
{
	char *buf = nd_get_link(nd);
#if SCFS_PROFILE_MEM
	struct scfs_sb_info *sbi = SCFS_S(dentry->d_sb);
#endif

	SCFS_DEBUG_START;

	if (!IS_ERR(buf)) {
		kfree(buf);
#if SCFS_PROFILE_MEM
		atomic_sub(PAGE_SIZE, &sbi->kmalloc_size);
#endif
	}

	SCFS_DEBUG_END;
}

int scfs_setxattr(struct dentry *dentry, const char *name, const void *value,
		  size_t size, int flags)
{
	struct dentry *lower_dentry;
	int ret = 0;

	SCFS_DEBUG_START;

	lower_dentry = scfs_lower_dentry(dentry);
	if (!lower_dentry->d_inode->i_op->setxattr) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	ret = vfs_setxattr(lower_dentry, name, value, size, flags);
	if (!ret)
		fsstack_copy_attr_all(dentry->d_inode, lower_dentry->d_inode);
out:

	SCFS_DEBUG_END;

	return ret;
}

ssize_t scfs_getxattr_lower(struct dentry *lower_dentry, const char *name,
			void *value, size_t size)
{
	int ret = 0;

	SCFS_DEBUG_START;

	if (!lower_dentry->d_inode->i_op->getxattr) {
		ret = -EOPNOTSUPP;
		goto out;
	}
	mutex_lock(&lower_dentry->d_inode->i_mutex);
	ret = lower_dentry->d_inode->i_op->getxattr(lower_dentry, name, value,
						   size);
	mutex_unlock(&lower_dentry->d_inode->i_mutex);
out:

	SCFS_DEBUG_END;

	return ret;
}

static ssize_t scfs_getxattr(struct dentry *dentry, const char *name, void *value,
		  size_t size)
{
	return scfs_getxattr_lower(scfs_lower_dentry(dentry), name,
				       value, size);
}

static ssize_t scfs_listxattr(struct dentry *dentry, char *list, size_t size)
{
	struct dentry *lower_dentry;
	int ret = 0;

	SCFS_DEBUG_START;

	lower_dentry = scfs_lower_dentry(dentry);
	if (!lower_dentry->d_inode->i_op->listxattr) {
		ret = -EOPNOTSUPP;
		goto out;
	}
	mutex_lock(&lower_dentry->d_inode->i_mutex);
	ret = lower_dentry->d_inode->i_op->listxattr(lower_dentry, list, size);
	mutex_unlock(&lower_dentry->d_inode->i_mutex);
out:

	SCFS_DEBUG_END;

	return ret;
}

static int scfs_removexattr(struct dentry *dentry, const char *name)
{
	struct dentry *lower_dentry;
	int ret = 0;

	SCFS_DEBUG_START;

	lower_dentry = scfs_lower_dentry(dentry);
	if (!lower_dentry->d_inode->i_op->removexattr) {
		ret = -EOPNOTSUPP;
		goto out;
	}
	mutex_lock(&lower_dentry->d_inode->i_mutex);
	ret = lower_dentry->d_inode->i_op->removexattr(lower_dentry, name);
	mutex_unlock(&lower_dentry->d_inode->i_mutex);
out:

	SCFS_DEBUG_END;

	return ret;
}

/*******************************/
/* inode_operations structures */
/*******************************/
const struct inode_operations scfs_dir_iops = {
	.create = scfs_create,
	.lookup	= scfs_lookup,
	.link = scfs_link,
	.mkdir = scfs_mkdir,
	.rmdir = scfs_rmdir,
	.mknod = scfs_mknod,
	.rename = scfs_rename,
	.permission = scfs_permission,
	.unlink = scfs_unlink,
	.symlink = scfs_symlink,
	.setattr = scfs_setattr,
	.setxattr = scfs_setxattr,
	.getxattr = scfs_getxattr,
	.listxattr = scfs_listxattr,
	.removexattr = scfs_removexattr
};

const struct inode_operations scfs_file_iops = {
	.permission = scfs_permission,
	.setattr = scfs_setattr,
	.getattr = scfs_getattr,
	.setxattr = scfs_setxattr,
	.getxattr = scfs_getxattr,
	.listxattr = scfs_listxattr,
	.removexattr = scfs_removexattr
};

const struct inode_operations scfs_symlink_iops = {
	.readlink = scfs_readlink,
	.follow_link = scfs_follow_link,
	.put_link = scfs_put_link,
	.permission = scfs_permission,
	.setattr = scfs_setattr,
	.getattr = scfs_getattr,
	.setxattr = scfs_setxattr,
	.getxattr = scfs_getxattr,
	.listxattr = scfs_listxattr,
	.removexattr = scfs_removexattr
};
