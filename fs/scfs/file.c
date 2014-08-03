/*
 *  file.c
 */

#include "scfs.h"

/*
 * scfs_open
 */
static int scfs_open(struct inode *inode, struct file *file)
{
	struct dentry *lower_dentry;
	struct scfs_inode_info *sii = SCFS_I(inode);
	struct scfs_file_info *fi;
	void *buf = NULL;
	loff_t pos = 0;
	int ret = 0;
#if SCFS_PROFILE_MEM
	struct scfs_sb_info *sbi = SCFS_S(inode->i_sb);
#endif

	fi = kmem_cache_zalloc(scfs_file_info_cache, GFP_KERNEL);
	if (!fi)
		return SCFS_ERR_OUT_OF_MEMORY;
#if SCFS_PROFILE_MEM
	atomic_add(sizeof(struct scfs_file_info), &sbi->kmcache_size);
#endif

	file->private_data = fi;

	lower_dentry = scfs_lower_dentry(file->f_path.dentry);
	ret = scfs_get_lower_file(file->f_path.dentry, inode);
	if (ret) {
		SCFS_PRINT_ERROR("err in get_lower_file %s\n",
			lower_dentry->d_name.name);
		kmem_cache_free(scfs_file_info_cache, file->private_data);
#if SCFS_PROFILE_MEM
			atomic_sub(sizeof(struct scfs_file_info), &sbi->kmcache_size);
#endif
		return ret;
	}

	if (IS_INVALID_META(sii)) {
		SCFS_PRINT("meta is invalid, so we should re-load it\n");
		ret = scfs_reload_meta(file);
		if (ret) {
			SCFS_PRINT_ERROR("error in re-reading footer, err : %d\n", ret);
			goto out;
		}
	}

	/* should I check whether lower file is RO when upper is not and vice versa? */
	if (sii->cinfo_array_size && !sii->cinfo_array) {
		ASSERT(IS_COMPRESSED(sii));
		SCFS_PRINT("info size = %d \n", sii->cinfo_array_size);
		buf = vmalloc(sii->cinfo_array_size);
		if (!buf) {
			ret = SCFS_ERR_OUT_OF_MEMORY;
			goto out;
		}
#if SCFS_PROFILE_MEM
		atomic_add(sii->cinfo_array_size, &sbi->vmalloc_size);
#endif
		pos = i_size_read(sii->lower_inode) - sii->cinfo_array_size -
			sizeof(struct comp_footer);

		ret = scfs_lower_read(sii->lower_file, buf, sii->cinfo_array_size, &pos);
		if (ret < 0)
			goto out;
		ret = 0;
		sii->cinfo_array = buf;
	}
	scfs_set_lower_file(file, sii->lower_file);

out:
	if (!ret)
		fsstack_copy_attr_all(inode, scfs_lower_inode(inode));
	else {
		scfs_set_lower_file(file, NULL);
		scfs_put_lower_file(inode);
		kmem_cache_free(scfs_file_info_cache, file->private_data);
#if SCFS_PROFILE_MEM
		atomic_sub(sizeof(struct scfs_file_info), &sbi->kmcache_size);
#endif
		if (buf) {
			vfree(buf);
#if SCFS_PROFILE_MEM
			atomic_sub(sii->cinfo_array_size, &sbi->vmalloc_size);
#endif
		}
		sii->cinfo_array = NULL;
	}

	SCFS_PRINT("lower, dentry name : %s, count : %d\n",
	lower_dentry->d_name.name, lower_dentry->d_count);
	
	return ret;
}

/*
 * scfs_file_release
 */
static int scfs_file_release(struct inode *inode, struct file *file)
{
#if SCFS_PROFILE_MEM
	struct scfs_sb_info *sbi = SCFS_S(inode->i_sb);
#endif
	SCFS_PRINT("f:%s calling put_lower_file\n",
			file->f_path.dentry->d_name.name);
	scfs_put_lower_file(inode);
	kmem_cache_free(scfs_file_info_cache, SCFS_F(file));
#if SCFS_PROFILE_MEM
	atomic_sub(sizeof(struct scfs_file_info), &sbi->kmcache_size);
#endif

	return 0;
}

/*
 * scfs_readdir
 */
static int scfs_readdir(struct file *file, void *dirent, filldir_t filldir)
{
	struct file *lower_file = NULL;
	struct dentry *dentry = file->f_path.dentry;
	int ret = 0;

	SCFS_DEBUG_START;

	lower_file = scfs_lower_file(file);
	lower_file->f_pos = file->f_pos;
	ret = vfs_readdir(lower_file, filldir, dirent);
	file->f_pos = lower_file->f_pos;
	if (ret >= 0)
		fsstack_copy_attr_atime(dentry->d_inode, lower_file->f_path.dentry->d_inode);

	SCFS_DEBUG_END;

	return ret;
}

/*
 * scfs_unlocked_ioctl
 */
static long scfs_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct file *lower_file;
	long ret = SCFS_ERR_NO_FILE;

	SCFS_DEBUG_START;

	lower_file = scfs_lower_file(file);

	if (!lower_file || !lower_file->f_op)
		goto out;
	if (lower_file->f_op->unlocked_ioctl)
		ret = lower_file->f_op->unlocked_ioctl(lower_file, cmd, arg);

out:
	SCFS_DEBUG_END;
	
	return ret;
}

#ifdef CONFIG_COMPAT
/*
 * scfs_compat_ioctl
 */
static long scfs_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct file *lower_file;
	long ret = SCFS_ERR_NO_FILE;

	SCFS_DEBUG_START;
	
	lower_file = scfs_lower_file(file);

	if (!lower_file || !lower_file->f_op)
		goto out;
	if (lower_file->f_op->compat_ioctl)
		ret = lower_file->f_op->compat_ioctl(lower_file, cmd, arg);

out:
	SCFS_DEBUG_END;
	return ret;
}
#endif

static int scfs_flush(struct file *file, fl_owner_t id)
{
	struct file *lower_file = NULL;
	int ret = 0;

	SCFS_DEBUG_START;
	
	lower_file = scfs_lower_file(file);
	if (lower_file && lower_file->f_op && lower_file->f_op->flush)
		ret = lower_file->f_op->flush(lower_file, id);

	SCFS_DEBUG_END;
	
	return ret;
}

static int scfs_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
	int ret = 0;

	SCFS_DEBUG_START;

	ret = vfs_fsync(scfs_lower_file(file), datasync);

	SCFS_DEBUG_END;

	return ret;
}

static int scfs_fasync(int fd, struct file *file, int flag)
{
	struct file *lower_file = NULL;
	int ret = 0;

	SCFS_DEBUG_START;
	
	lower_file = scfs_lower_file(file);
	if (lower_file->f_op && lower_file->f_op->fasync)
		ret = lower_file->f_op->fasync(fd, lower_file, flag);

	SCFS_DEBUG_END;
	
	return ret;
}

static const struct vm_operations_struct scfs_file_vm_ops = {
	.fault		= filemap_fault,
	//TODO we may not need this, but for testing we just printk here 
	//.page_mkwrite   = scfs_page_mkwrite,
};

static int scfs_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct address_space *mapping = file->f_mapping;

	SCFS_DEBUG_START;

	if (!mapping->a_ops->readpage)
		return SCFS_ERR_EXEC;

	SCFS_PRINT("file %s\n", file->f_path.dentry->d_name.name);	

	if (file->f_mode & FMODE_WRITE) {
		SCFS_PRINT_ERROR("f_mode WRITE was set! error. "
			"f_mode %x (FMODE_READ: %x FMODE_WRITE %x)\n", 
			file->f_mode,
			file->f_mode & FMODE_READ,
			file->f_mode & FMODE_WRITE);
		return SCFS_ERR_PERMISSION;
	}

	//TODO should we touch the file before FMODE_WRITE check?
	file_accessed(file);
	vma->vm_ops = &scfs_file_vm_ops;
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
	vma->vm_flags |= VM_CAN_NONLINEAR;
#endif
 	SCFS_PRINT("VM flags: %lx "
 		"EXEC %lx IO %lx "
		"SEQ %lx RAND %lx "
		"READ %lx MAYREAD %lx "
		"WRITE %lx MAYWRITE %lx "
		"SHARED %lx MAYSHARE %lx\n",
		vma->vm_flags,
		vma->vm_flags & VM_EXECUTABLE, vma->vm_flags & VM_IO,
		vma->vm_flags & VM_SEQ_READ, vma->vm_flags & VM_RAND_READ,
		vma->vm_flags & VM_READ, vma->vm_flags & VM_MAYREAD,
		vma->vm_flags & VM_WRITE, vma->vm_flags & VM_MAYWRITE,
		vma->vm_flags & VM_SHARED, vma->vm_flags & VM_MAYSHARE);

	if (vma->vm_flags & VM_WRITE) {
		SCFS_PRINT("VM_WRITE: file %s flags %lx VM_MAYWRITE %lx\n", 
			file->f_path.dentry->d_name.name,
			vma->vm_flags,
			vma->vm_flags & VM_MAYWRITE);
	}

	SCFS_DEBUG_END;
	
	return SCFS_SUCCESS;
}

/*****************************/
/* file_operations structres */
/*****************************/

const struct file_operations scfs_dir_fops = {
	.llseek		= default_llseek,
	.read		= generic_read_dir,
	.readdir	= scfs_readdir,
	.unlocked_ioctl	= scfs_unlocked_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= scfs_compat_ioctl,
#endif
	.open		= scfs_open,
	.release	= scfs_file_release,
	.flush		= scfs_flush,
	.fsync		= scfs_fsync,
	.fasync		= scfs_fasync,
};

const struct file_operations scfs_file_fops = {
	.llseek		= generic_file_llseek,
	.read 		= do_sync_read,
	.aio_read 	= generic_file_aio_read,
	.write 		= do_sync_write,
	.aio_write 	= generic_file_aio_write,
	.unlocked_ioctl	= scfs_unlocked_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= ioctl,
#endif
	.mmap		= scfs_mmap,
	.open 		= scfs_open,
	.release	= scfs_file_release,
	.flush		= scfs_flush,
	.fsync		= scfs_fsync,
	.fasync		= scfs_fasync,
};
