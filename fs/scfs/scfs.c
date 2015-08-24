/*
 *  scfs.c
 */

#include <linux/crypto.h>
#include <linux/nsproxy.h>
#include <linux/parser.h>
#include "scfs.h"

#include <linux/ctype.h>

struct kmem_cache *scfs_file_info_cache;
struct kmem_cache *scfs_dentry_info_cache;
struct kmem_cache *scfs_open_req_cache;
struct kmem_cache *scfs_inode_info_cache;
struct kmem_cache *scfs_sb_info_cache;
struct kmem_cache *scfs_header_cache;
struct kmem_cache *scfs_xattr_cache;
struct kmem_cache *scfs_info_entry_list;

static struct crypto_comp *tfm_handles[TOTAL_TYPES];

static const char *tfm_names[TOTAL_TYPES] = 
{
	"lzo",		/* lzo */
	"bzip", 	/* TODO bzip2? */
	"deflate",	/* zlib */ 
	"fastlzo"	/* TODO lzo? */
};

void scfs_printk(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintk(fmt, args);
	va_end(args);
}

int scfs_reload_meta(struct file *file)
{
	struct dentry *dentry = file->f_dentry;
	struct inode *inode = dentry->d_inode;
	struct scfs_inode_info *sii = SCFS_I(inode);
	void *buf = NULL;
	loff_t pos;
	int ret = 0;
#if SCFS_PROFILE_MEM
	int previous_cinfo_array_size = sii->cinfo_array_size;
	struct scfs_sb_info *sbi = SCFS_S(inode->i_sb);
#endif

	ASSERT(IS_INVALID_META(sii));
	ret = scfs_footer_read(dentry, inode);
	if (ret) {
		SCFS_PRINT_ERROR("f:%s err in reading footer, ret : %d\n",
			file->f_path.dentry->d_name.name, ret);
		return ret;
	}
	ret = scfs_get_lower_file(dentry, inode);
	if (ret) {
		SCFS_PRINT_ERROR("f:%s err in get_lower_file, ret : %d\n",
			file->f_path.dentry->d_name.name, ret);
		return ret;
	}

	SCFS_PRINT("f:%s info size = %d \n",
		file->f_path.dentry->d_name.name, sii->cinfo_array_size);
	ASSERT(sii->cinfo_array_size);
	if (sii->cinfo_array_size) {
		buf = vmalloc(sii->cinfo_array_size);
		if (!buf) {
			ret = -ENOMEM;
			goto out;
		}
#if SCFS_PROFILE_MEM
		atomic_add(sii->cinfo_array_size, &sbi->vmalloc_size);
#endif
		pos = i_size_read(sii->lower_inode) - sii->cinfo_array_size -
				sizeof(struct comp_footer);
		ASSERT(pos > 0);
		ret = scfs_lower_read(sii->lower_file, buf, sii->cinfo_array_size, &pos);
		if (ret < 0)
			goto out;

		ret = 0;
	}

	if (sii->cinfo_array) {
		vfree(sii->cinfo_array);
#if SCFS_PROFILE_MEM
		atomic_sub(previous_cinfo_array_size, &sbi->vmalloc_size);
#endif
	}

	sii->cinfo_array = buf;
	clear_meta_invalid(sii);
out:
	SCFS_PRINT("f:%s calling put_lower_file\n",
			file->f_path.dentry->d_name.name);
	scfs_put_lower_file(inode);
	return ret;
}

/*
 * get_cluster_info
 *
 * Parameters:
 * @inode: inode in VFS layer
 * @cluster_n: cluster number wanted to get info
 * @*clust_info: address of cluster info structure
 *
 * Return:
 * SCFS_SUCCESS if success, otherwise if error
 *
 * Description:
 * Calculate the position of the cluster info for a given cluster,
 * and return the address
 */
int get_cluster_info(struct file *file, int cluster_idx, 
		 struct scfs_cinfo *target)
{
	struct scfs_inode_info *sii = SCFS_I(file->f_dentry->d_inode);
	struct scfs_cinfo *cinfo;
	struct cinfo_entry *cinfo_entry;
	struct list_head *head, *tmp;
	int ret = 0;

	ASSERT(IS_COMPRESSED(sii));

	if (IS_INVALID_META(sii)) {
		SCFS_PRINT("f:%s meta invalid flag is set, "
					"let's reload.\n",
					file->f_path.dentry->d_name.name);
		ret = scfs_reload_meta(file);
		if (ret) {
			SCFS_PRINT_ERROR("f:%s error in re-reading footer, err : %d\n",
				file->f_path.dentry->d_name.name, ret);
			return ret;
		}
	}

	if (cluster_idx + 1 > CLUSTER_COUNT(sii)) {
		SCFS_PRINT_ERROR("f:%s size check err, "
			"cluster_idx %d cluster count of the file %d\n", 
			file->f_path.dentry->d_name.name, cluster_idx, CLUSTER_COUNT(sii));
		return -EINVAL;
	}

	if (cluster_idx * sizeof(struct scfs_cinfo) < sii->cinfo_array_size)
		cinfo = (struct scfs_cinfo *)(sii->cinfo_array) + cluster_idx;
	else {
		mutex_lock(&sii->cinfo_list_mutex);
		if (list_empty(&sii->cinfo_list)) {
			SCFS_PRINT_ERROR("cluster idx : %d, and info size : %d, but "
				"info list is empty!\n");
			ASSERT(0);
		}
		list_for_each_safe(head, tmp, &sii->cinfo_list) {
			cinfo_entry = list_entry(head, struct cinfo_entry, entry);
			ASSERT(cinfo_entry->current_cluster_idx >= cluster_idx);
			if (cinfo_entry->current_cluster_idx == cluster_idx) {
				//SCFS_PRINT("found matched cluster info in list\n");
				cinfo = &cinfo_entry->cinfo;
				mutex_unlock(&sii->cinfo_list_mutex);
				goto out;
			}
		}
		mutex_unlock(&sii->cinfo_list_mutex);
		SCFS_PRINT_ERROR("f:%s invalid cluster idx : %d or cluster_info(size : %d)\n",
			file->f_path.dentry->d_name.name,
			cluster_idx, sii->cinfo_array_size);
		return -EIO;
	}
out:	
	target->offset = cinfo->offset;
	target->size = cinfo->size;

	return ret;
}

enum {
	scfs_opt_nocompress,
	scfs_opt_cluster_size,
	scfs_opt_comp_threshold,
	scfs_opt_comp_type,
 	scfs_opt_err,
};

static const match_table_t tokens = {
	{scfs_opt_nocompress, "nocomp"},
	{scfs_opt_cluster_size, "cluster_size=%u"},
	{scfs_opt_comp_threshold, "comp_threshold=%u"},
	{scfs_opt_comp_type, "comp_type=%s"},
 	{scfs_opt_err, NULL}
};
 
int scfs_parse_options(struct scfs_sb_info *sbi, char *options)
{
	int token;
	int option;
	char *p;
	char *type;
	substring_t args[MAX_OPT_ARGS];

	if (!options)
		return 0;

	while ((p = strsep(&options, ",")) != NULL) {
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case scfs_opt_nocompress:
			sbi->options.flags &= ~SCFS_DATA_COMPRESS;
			break;
		case scfs_opt_cluster_size:
			if (match_int(&args[0], &option))
				return 0;
			if (option > SCFS_CLUSTER_SIZE_MAX ||
				option < SCFS_CLUSTER_SIZE_MIN) {
				SCFS_PRINT_ERROR("cluster_size, out of range\n");
				return -EINVAL;
			}
			if (!IS_POW2(option)) {
				SCFS_PRINT_ERROR("cluster_size must be a power of 2\n");
				return -EINVAL;
			}
			sbi->options.cluster_size = option;
			break;
		case scfs_opt_comp_threshold:
			if (match_int(&args[0], &option))
				return 0;
			if (option > 100 || option < 0) {
				SCFS_PRINT_ERROR("threshold, out of range, "
					"it's a percent\n");
				return -EINVAL;
			}
			sbi->options.comp_threshold = option;
			break;
		case scfs_opt_comp_type:
			type = args[0].from;
			// default type is 'lzo'
			if (!strcmp(type, "lzo"))
				sbi->options.comp_type = LZO;
			else if (!strcmp(type, "bzip2"))
				sbi->options.comp_type = BZIP2;
			else if (!strcmp(type, "zlib"))
				sbi->options.comp_type = ZLIB;
			else if (!strcmp(type, "fastlzo"))
				sbi->options.comp_type = FASTLZO;
			else {
				SCFS_PRINT("invalid compression type\n");
				return -EINVAL;
			}
			break;
 		default:
			SCFS_PRINT("Unrecognized mount option [%s]\n", p);
			return -EINVAL;
		}
	}
	return SCFS_SUCCESS;
}


void copy_mount_flags_to_inode_flags(struct inode *inode, struct super_block *sb)
{
	struct scfs_sb_info *sbi = SCFS_S(sb);
	struct scfs_inode_info *sii = SCFS_I(inode);

	sii->cluster_size = sbi->options.cluster_size;
	sii->comp_type = sbi->options.comp_type;
	if (sbi->options.flags & SCFS_DATA_COMPRESS)
		sii->flags |= SCFS_DATA_COMPRESS;
	if (sbi->options.flags & SCFS_MOUNT_XATTR_META)
		sii->flags |= SCFS_META_XATTR;
}

int scfs_initialize_lower_file(struct dentry *dentry, struct file **lower_file)
{
	const struct cred *cred;
	struct dentry *lower_dentry;
	struct vfsmount *lower_mnt;
	int ret;

	cred = current_cred();
	lower_dentry = scfs_lower_dentry(dentry);
	lower_mnt = scfs_dentry_to_lower_mnt(dentry);

	ret = scfs_privileged_open(lower_file, lower_dentry, lower_mnt, cred);
	if (ret) {
		SCFS_PRINT_ERROR("privileged open failed\n");
		(*lower_file) = NULL;
	}
	
	return ret;
}

int scfs_get_lower_file(struct dentry *dentry, struct inode *inode)
{
	struct scfs_inode_info *sii = SCFS_I(inode);
	int count, ret = 0;

	mutex_lock(&sii->lower_file_mutex);
	count = atomic_inc_return(&sii->lower_file_count);

	if (WARN_ON_ONCE(count < 1))
		ret = SCFS_ERR_INVALID;
	else if (count == 1) {
		//TODO what would this do?
		ret = scfs_initialize_lower_file(dentry, &sii->lower_file);
		if (ret)
			atomic_set(&sii->lower_file_count, 0);
	}
	mutex_unlock(&sii->lower_file_mutex);
	
	return ret;
}

void scfs_put_lower_file(struct inode *inode)
{
	struct scfs_inode_info *sii;
	int ret = 0;

	sii = SCFS_I(inode);

	if (atomic_dec_and_mutex_lock(&sii->lower_file_count,
				      &sii->lower_file_mutex)) {
		filemap_write_and_wait(inode->i_mapping);

		ret = scfs_write_meta(sii);
		if (ret)
			SCFS_PRINT_ERROR("error in writing meta, ret : %d\n", ret);
		
		fput(sii->lower_file);
		sii->lower_file = NULL;
		mutex_unlock(&sii->lower_file_mutex);
	}
}

/**
 * scfs_read_cluster
 *
 * Parameters:
 * @file: upper file
 * @page: upper page from SCFS inode mapping
 * @buf_c: buffer for compressed cluster
 * @buf_u: bufferer for uncompressed cluster
 * @compressed: whether cluster was compressed or not
 *
 * Return:
 * SCFS_SUCCESS if success, otherwise if error
 * *compressed = 1 if cluster was compressed
 *
 * Description:
 * - Read a cluster, and if it was compressed, decompress it.
 */

int scfs_read_cluster(struct file *file, struct page *page,
	char *buf_c, char **buf_u, int *compressed)
{
	struct scfs_inode_info *sii = SCFS_I(page->mapping->host);
	struct scfs_cinfo cinfo;
	struct file *lower_file = NULL;
	int cluster_idx = 0, ret = SCFS_SUCCESS, actual = 0;
	int size = 0, last_cluster_idx = 0;
	loff_t i_size = 0, pos = 0, tmp, left;

	/* check upper inode size */
	i_size = i_size_read(&sii->vfs_inode);
	if (!i_size) {
		SCFS_PRINT("file %s: i_size is zero, "
			"flags 0x%x sii->clust_info_size %d\n",
			file->f_path.dentry->d_name.name, sii->flags,
			sii->cinfo_array_size);
		unlock_page(page);

		return SCFS_SUCCESS;
	} else if (page->index * PAGE_SIZE >= i_size) {
		SCFS_PRINT("file %s: page->idx out of bounds, "
			"page->idx %d i_size %lld\n",
			file->f_path.dentry->d_name.name, page->index, i_size);
		unlock_page(page);
		/* return something recognizable for readpage to catch this */
		return SCFS_SUCCESS;
	}

	tmp = i_size;
	left = do_div(tmp, sii->cluster_size);
	if (left)
		tmp++;
	last_cluster_idx = tmp - 1;
	
	cluster_idx = PAGE_TO_CLUSTER_INDEX(page, sii);
	if (cluster_idx > last_cluster_idx) {
			SCFS_PRINT_ERROR("file %s: cluster_idx out of range, "
				"clust %u of %u, i_size %lld, "
				"page->index %d, ret %x\n",
				file->f_path.dentry->d_name.name,
				cluster_idx, last_cluster_idx, i_size, page->index,
				ret);
			ASSERT(0);
			return -ERANGE;
	}

	if (IS_COMPRESSED(sii)) {
		ret = get_cluster_info(file, cluster_idx, &cinfo);
		if (ret) {
			SCFS_PRINT_ERROR("err in get_cluster_info, ret : %d,"
				"i_size %lld\n", ret, i_size);
			return ret;
		}

		if (!cinfo.size || cinfo.size > sii->cluster_size) {
			SCFS_PRINT_ERROR("file %s: cinfo is invalid, "
				"clust %u of %u cinfo.size %u\n",
				file->f_path.dentry->d_name.name,
				cluster_idx, last_cluster_idx, cinfo.size);
			ASSERT(0);
			return -EINVAL;
		}

		/* decide if cluster was compressed */
		if (cinfo.size == sii->cluster_size) {
			*compressed = 0;
		} else {
			if (cluster_idx == last_cluster_idx && left == cinfo.size)
				*compressed = 0;
			else
				*compressed = 1;
		}
		size = cinfo.size;
		pos = (loff_t)cinfo.offset;
	} else {
		/* if it's an uncompressed file, forget clusters, 
		   only read one page. */
		*compressed = 0;
		size = sii->cluster_size;

		if (cluster_idx == last_cluster_idx && left)
			size = left;

		pos = (loff_t)cluster_idx * sii->cluster_size;
	}
	
	lower_file = scfs_lower_file(file);
	if (!lower_file) {
		SCFS_PRINT_ERROR("file %s: lower file is null!\n",
			file->f_path.dentry->d_name.name);
		ASSERT(0);
		return -EINVAL;
	}

	/* vfs read, either cluster or page */
	ret = scfs_lower_read(lower_file, buf_c, size, &pos);	
	if (ret < 0) {
		SCFS_PRINT_ERROR("file %s: vfs_read failed, clust %d of %d, "
			"size %u, pos %lld, ret %d(0x%x), "
			"compressed %d, page->index %d,"
			"i_size %lld, sii->flags 0x%x, sii->cis %d\n",
			file->f_path.dentry->d_name.name, cluster_idx,
			last_cluster_idx, size, pos, ret, ret, *compressed,
			page->index, i_size, sii->flags, sii->cinfo_array_size);
		unlock_page(page);
		return ret;
	}

	/* decompress cluster if needed */
	if (*compressed) {
		actual = sii->cluster_size;
		ret = scfs_decompress(sii->comp_type, buf_c, *buf_u,
			size, &actual);

		if (ret) {
			SCFS_PRINT_ERROR("file %s: decompress failed. "
				"clust %u of %u, offset %u size %u ret 0x%x "
				"buf_c 0x%x buf_u 0x%x\n",
				file->f_path.dentry->d_name.name, 
				cluster_idx, last_cluster_idx, cinfo.offset, 
				size, ret, buf_c, *buf_u);
			ClearPageUptodate(page);
			unlock_page(page);
			ASSERT(0);
			return ret;
		}
	}

	return SCFS_SUCCESS;
}

/*
 * scfs_decompress
 *
 * Parameters:
 * @algo: algorithm type to use
 * @*page: requested page, either the sole page from read/writepage,
 *	   or... the... first page of the cluster for multiple read/writes...?
 * @*buf_c: global buffer for compressed cluster data
 * @*buf_u: global buffer for decompressed cluster data
 * @len: compressed cluster length (as a hint)
 *
 * Return:
 * SCFS_SUCCESS if success, otherwise if error
 *
 * Description:
 * Decompress a cluster
 */
int scfs_decompress(enum comp_type algo, char *buf_c, char *buf_u, int len, 
	int *actual)
{
	int ret = SCFS_SUCCESS;
	
	ASSERT(algo < TOTAL_TYPES);

	if (tfm_handles[algo] == NULL) {
		//TODO use CRYPTO_ALG_ASYNC?
		tfm_handles[algo] = crypto_alloc_comp(tfm_names[algo], 0, 0);
		if (IS_ERR(tfm_handles[algo])) {
			SCFS_PRINT_ERROR("crypto_alloc_comp failed, "
				"len %d error %ld\n",
				len, PTR_ERR(tfm_handles[algo]));
			tfm_handles[algo] = NULL;
			return SCFS_ERR_OUT_OF_MEMORY;
		}
	}
	SCFS_PRINT("crypto_comp_decompress start, len %d\n", len);
	ret = crypto_comp_decompress(tfm_handles[algo], buf_c, len, buf_u, 
		actual);
	SCFS_PRINT("crypto_comp_decompress end, actual %d\n", *actual);
	
	if (ret) {
		SCFS_PRINT_ERROR("crypto_comp_decompress error! "
			"ret %d len %d actual %d\n", 
			ret, len, *actual);
		ret = -EIO;
	}
	
	return ret;
}

/*
 * scfs_compress
 *
 * Parameters:
 * @algo: algorithm type to use
 * @*page: requested page, either the sole page from read/writepage,
 *	   or... the... first page of the cluster for multiple read/writes...?
 * @*buf_c: global buffer for compressed cluster data
 * @*buf_u: global buffer for decompressed cluster data
 * @*len: actual compressed cluster length after compression
 *
 * Return:
 * SCFS_SUCCESS if success, otherwise if error
 *
 * Description:
 * Compress a cluster
 */

int scfs_compress(enum comp_type algo, char *buf_c, char *buf_u, int len, 
	int *actual)
{
	int ret = SCFS_SUCCESS;

	SCFS_DEBUG_START;
	ASSERT(algo < TOTAL_TYPES);

	if (tfm_handles[algo] == NULL) {
		//TODO use CRYPTO_ALG_ASYNC?
		tfm_handles[algo] = crypto_alloc_comp(tfm_names[algo], 0, 0);
		if (IS_ERR(tfm_handles[algo])) {
			SCFS_PRINT_ERROR("crypto_alloc_comp failed, "
				"len %d error %ld\n",
				len, PTR_ERR(tfm_handles[algo]));
			tfm_handles[algo] = NULL;
			return SCFS_ERR_OUT_OF_MEMORY;
		}
	}
	SCFS_PRINT("crypto_comp_compress start, len %d\n", len);
	ret = crypto_comp_compress(tfm_handles[algo], buf_u, len, buf_c, 
		actual);
	SCFS_PRINT("crypto_comp_compress end, actual %d\n", *actual);
	
	if (ret) {
		SCFS_PRINT("crypto_comp_compress error! "
			"ret %d len %d actual %d\n", 
			ret, len, *actual);
		ret = -EIO;
	}

	SCFS_DEBUG_END;
	
	return ret;
}

struct page *scfs_alloc_mempool_buffer(struct scfs_sb_info *sbi)
{
	struct page *ret = mempool_alloc(sbi->mempool, 
			__GFP_NORETRY | __GFP_NOMEMALLOC | __GFP_NOWARN);
	
#if SCFS_PROFILE_MEM
	if (ret != NULL)
		atomic_add(SCFS_MEMPOOL_SIZE, &sbi->mempool_size);
#endif
	return ret;
}

void scfs_free_mempool_buffer(struct page *p, struct scfs_sb_info *sbi)
{
	if (!p)
		return;
	mempool_free(p, sbi->mempool);
#if SCFS_PROFILE_MEM
	atomic_sub(SCFS_MEMPOOL_SIZE, &sbi->mempool_size);
#endif
}

void sync_page_to_buffer(struct page *page, char *buffer)
{
	char *source_addr;

	SCFS_DEBUG_START;

	source_addr = kmap_atomic(page);
	SCFS_PRINT(" buffer = %x , page address = %x\n", buffer, 
		buffer + (PAGE_SIZE * PGOFF_IN_CLUSTER(page, SCFS_I(page->mapping->host))));
	memcpy(buffer + (PAGE_SIZE * PGOFF_IN_CLUSTER(page, SCFS_I(page->mapping->host))),
		source_addr, PAGE_SIZE);	

	kunmap_atomic(source_addr);

	SCFS_DEBUG_END;
}

void sync_page_from_buffer(struct page *page, char *buffer)
{
	char *dest_addr;

	SCFS_DEBUG_START;

	dest_addr = kmap_atomic(page);

	SCFS_PRINT(" buffer = %x , page address = %x\n", buffer, 
		buffer + (PAGE_SIZE*PGOFF_IN_CLUSTER(page, SCFS_I(page->mapping->host))));
	memcpy(dest_addr, buffer + (PAGE_SIZE *
		PGOFF_IN_CLUSTER(page, SCFS_I(page->mapping->host))), PAGE_SIZE);	

	kunmap_atomic(dest_addr);
	SCFS_DEBUG_END;
}

int scfs_write_meta(struct scfs_inode_info *sii)
{
	struct list_head *head = NULL, *tmp;
	struct cinfo_entry *last, *cinfo_entry = NULL;
	struct comp_footer cf;
	struct scfs_sb_info *sbi = SCFS_S(sii->vfs_inode.i_sb);
	struct inode *lower_inode;
	struct iattr ia;
	int ret, pad, cinfo_size = sizeof(struct scfs_cinfo);
	char *current_pos = NULL;
	loff_t pos;

	SCFS_DEBUG_START;
	
	mutex_lock(&sii->cinfo_list_mutex);
	if (list_empty(&sii->cinfo_list)) {
		SCFS_PRINT("cinfo_list is empty\n");
		mutex_unlock(&sii->cinfo_list_mutex);
		return SCFS_SUCCESS;
	}
	last = list_entry(sii->cinfo_list.prev, struct cinfo_entry, entry);

	//if last cluster exist, we should write it first.
	if (IS_COMPRESSED(sii)) {
	 	if (sii->cluster_buffer.original_size > 0) {
			ret = scfs_compress(sii->comp_type, sii->cluster_buffer.c_buffer
				,sii->cluster_buffer.u_buffer
				,sii->cluster_buffer.original_size
				,&last->cinfo.size);
			if (ret) {
				SCFS_PRINT_ERROR("f:%s Compression failed." \
				"So, write uncompress data.\n",
				sii->lower_file->f_path.dentry->d_name.name);
				last->cinfo.size = sii->cluster_buffer.original_size;
				mutex_unlock(&sii->cinfo_list_mutex);
				return ret;
			}
			if (last->cinfo.size % SCFS_CLUSTER_ALIGN)
				last->pad = SCFS_CLUSTER_ALIGN - (last->cinfo.size %
					SCFS_CLUSTER_ALIGN);
			else
				last->pad = 0;
				
			pos = (loff_t)last->cinfo.offset;

			if (last->cinfo.size <
					sii->cluster_buffer.original_size *
					sbi->options.comp_threshold / 100) {		
				ret = scfs_lower_write(sii->lower_file,
					sii->cluster_buffer.c_buffer,last->cinfo.size +
					last->pad, &pos);
				sii->compressd = 1;					
			} else {
				last->cinfo.size =
					sii->cluster_buffer.original_size;
				ret = scfs_lower_write(sii->lower_file,
					sii->cluster_buffer.u_buffer,last->cinfo.size +
					last->pad, &pos);
			}

			if (ret < 0) {
				SCFS_PRINT_ERROR("f:%s writing last cluster buffer failed, ret : %d\n",
					sii->lower_file->f_path.dentry->d_name.name, ret);
				ASSERT(0);
			} else
				ret = 0;

			if (sii->cluster_buffer.c_page) {
				scfs_free_mempool_buffer(sii->cluster_buffer.c_page, sbi);
				sii->cluster_buffer.c_buffer = NULL;
				sii->cluster_buffer.c_page = NULL;
			} 
			sii->cluster_buffer.original_size = 0;
		}

		if (last->cinfo.size % SCFS_CLUSTER_ALIGN)
			pad = SCFS_CLUSTER_ALIGN - (last->cinfo.size % SCFS_CLUSTER_ALIGN);
		else
			pad = 0;

		pos = last->cinfo.offset + last->cinfo.size + pad;

		if (sii->compressd) {
			last = list_entry(sii->cinfo_list.next, struct cinfo_entry, entry);

			// writing existing meta from sii.
			if (sii->cinfo_array_size) {
				ret = scfs_lower_write(sii->lower_file, sii->cinfo_array
						,cinfo_size * last->current_cluster_idx, &pos);
				if (ret < 0) {
					SCFS_PRINT_ERROR("f:%s write fail in writing" \
						"existing meta, ret : %d.\n",
						sii->lower_file->f_path.dentry->d_name.name, ret);
					ASSERT(0);
				} else
					ret = 0;
			}

			current_pos = sii->cluster_buffer.u_buffer;
			
			list_for_each_safe(head, tmp, &sii->cinfo_list) {
				int written_index;
				cinfo_entry = list_entry(head, struct cinfo_entry, entry);
				written_index = cinfo_entry->current_cluster_idx;
				memcpy(current_pos, &cinfo_entry->cinfo, cinfo_size);

				current_pos += cinfo_size;
				list_del(&cinfo_entry->entry);
				kmem_cache_free(scfs_info_entry_list, cinfo_entry);
				cinfo_entry = NULL;
#if SCFS_PROFILE_MEM
				atomic_sub(cinfo_size, &sbi->kmcache_size);
#endif

				if (current_pos > sii->cluster_buffer.u_buffer +
						((sii->cluster_size * 2) - cinfo_size) ||
						list_empty(&sii->cinfo_list)) {
					ret = scfs_lower_write(sii->lower_file,
						sii->cluster_buffer.u_buffer,
						(size_t)(current_pos - sii->cluster_buffer.u_buffer),
						&pos);
					if (ret < 0) {	
						SCFS_PRINT_ERROR("f:%s write fail in writing " \
							"new metas, ret : %d\n",
							sii->lower_file->f_path.dentry->d_name.name, ret);
						ASSERT(0);
					}

					cf.footer_size = (cinfo_size * (written_index + 1)) + CF_SIZE;
					current_pos = sii->cluster_buffer.u_buffer;
				}
			}
			SCFS_PRINT("footer size %d" , cf.footer_size);
		} else {
			list_for_each_safe(head, tmp, &sii->cinfo_list) {
				cinfo_entry = list_entry(head, struct cinfo_entry, entry);
				list_del(&cinfo_entry->entry);
				kmem_cache_free(scfs_info_entry_list, cinfo_entry);
#if SCFS_PROFILE_MEM
				atomic_sub(cinfo_size, &sbi->kmcache_size);
#endif			
			}
			cf.footer_size = CF_SIZE;
		}
	} else {
		cf.footer_size = CF_SIZE;
		pos = i_size_read(&sii->vfs_inode);
		// Remove fake cluster_info
		cinfo_entry = list_entry(sii->cinfo_list.prev, struct cinfo_entry, entry);
		list_del(&cinfo_entry->entry);
		kmem_cache_free(scfs_info_entry_list, cinfo_entry);		
	}
	cf.cluster_size = sii->cluster_size;
	cf.comp_type = sii->comp_type;
	cf.original_file_size = i_size_read(&sii->vfs_inode);
	cf.magic = SCFS_MAGIC;
	mutex_unlock(&sii->cinfo_list_mutex);

	ret = scfs_lower_write(sii->lower_file, (char*)&cf, CF_SIZE , &pos);
	if (ret < 0) {		
		SCFS_PRINT_ERROR("f:%s write fail, comp_footer, ret : %d",
			sii->lower_file->f_path.dentry->d_name.name, ret);
		ASSERT(0);
	} else
		ret = 0;

	lower_inode = sii->lower_file->f_dentry->d_inode;
	if (pos < i_size_read(lower_inode)) {
		ia.ia_valid = ATTR_SIZE;
		ia.ia_size = pos;
		truncate_setsize(lower_inode, pos);
		mutex_lock(&lower_inode->i_mutex);
		ret = notify_change(sii->lower_file->f_dentry, &ia);
		mutex_unlock(&lower_inode->i_mutex);
		if (ret) {
			SCFS_PRINT_ERROR("f:%s error in lower_truncate, %d",
				sii->lower_file->f_path.dentry->d_name.name,
				ret);
			ASSERT(0);
		}
	}
	if (cf.footer_size > CF_SIZE)
		make_meta_invalid(sii);
	else
		sii->flags &= ~SCFS_DATA_COMPRESS;

	if (sii->cluster_buffer.u_page) {
		scfs_free_mempool_buffer(sii->cluster_buffer.u_page, sbi);
		sii->cluster_buffer.u_buffer = NULL;
		sii->cluster_buffer.u_page = NULL;
	}

	SCFS_DEBUG_END;

	return SCFS_SUCCESS;
}

struct cinfo_entry *scfs_alloc_cinfo_entry(unsigned int cluster_index,
		struct scfs_inode_info *sii)
{
	struct cinfo_entry *new_entry = NULL;
#if SCFS_PROFILE_MEM
	struct scfs_sb_info *sbi = SCFS_S(sii->vfs_inode.i_sb);
#endif

	new_entry = kmem_cache_zalloc(scfs_info_entry_list, GFP_KERNEL);
	if (!new_entry) {
		SCFS_PRINT_ERROR("kmem_cache_zalloc ERROR.\n");
		return NULL;
	}
#if SCFS_PROFILE_MEM
	atomic_add(sizeof(struct cinfo_entry), &sbi->kmcache_size);
#endif
	new_entry->current_cluster_idx = cluster_index;
	list_add_tail(&new_entry->entry, &sii->cinfo_list);

	return new_entry;
}

int scfs_get_cluster_from_lower(struct scfs_inode_info *sii, struct file *lower_file,
		struct scfs_cinfo clust_info)
{
	loff_t pos = 0;
	int ret;

	if (clust_info.size > sii->cluster_size) {
		SCFS_PRINT_ERROR("f:%s clust_info.size out of bounds, size %d\n",
			lower_file->f_path.dentry->d_name.name, clust_info.size);
		ASSERT(0);
		return -EINVAL;
	}

	pos = clust_info.offset;

	if (IS_COMPRESSED(sii) && clust_info.size < sii->cluster_size) {
		//TODO pass appropriate algorithm, retrieved from file meta
		loff_t i_size = i_size_read(&sii->vfs_inode);

		if(do_div(i_size, sii->cluster_size) == clust_info.size) {
			ret = scfs_lower_read(lower_file, sii->cluster_buffer.u_buffer,
				clust_info.size, &pos);
			if (ret < 0) {
				SCFS_PRINT_ERROR("f:%s read failed, size %d pos %d ret = %d\n",
					lower_file->f_path.dentry->d_name.name,
					clust_info.size, (int)pos, ret);
				ASSERT(0);
				return ret;
			} else
				ret = 0;

			sii->cluster_buffer.original_size = clust_info.size;
		} else {			
			int len = sii->cluster_size;

			ret = scfs_lower_read(lower_file, sii->cluster_buffer.c_buffer,
				clust_info.size, &pos);
			if (ret < 0) {
				SCFS_PRINT_ERROR("f:%s read failed, size %d pos %d ret = %d\n",
					lower_file->f_path.dentry->d_name.name,
					clust_info.size, (int)pos, ret);
				ASSERT(0);
				return ret;
			} else
				ret = 0;

 			ret = scfs_decompress(sii->comp_type, 
						sii->cluster_buffer.c_buffer, 
						sii->cluster_buffer.u_buffer, 
						clust_info.size,
						&len);
			if (ret) {
				SCFS_PRINT_ERROR("f:%s decompress lower cluster failed.\n",
					lower_file->f_path.dentry->d_name.name);
				ASSERT(0);
				return -EIO;
			}				
			sii->cluster_buffer.original_size = len;
		}
	} else {
		ret = scfs_lower_read(lower_file, sii->cluster_buffer.u_buffer,
			clust_info.size, &pos);
		if (ret < 0) {
			SCFS_PRINT_ERROR("f:%s vfs_read failed, size %d pos %d ret = %d\n",
				lower_file->f_path.dentry->d_name.name,
				clust_info.size, (int) pos, ret);
			ASSERT(0);
			return ret;
		} else
			ret = 0;

		sii->cluster_buffer.original_size = clust_info.size;		
	}

	return SCFS_SUCCESS;
}

int scfs_get_comp_buffer(struct scfs_inode_info *sii)
{
	if (!sii->cluster_buffer.u_buffer) {
		sii->cluster_buffer.u_page =
			scfs_alloc_mempool_buffer(SCFS_S(sii->vfs_inode.i_sb));
		if (!sii->cluster_buffer.u_page) {
			SCFS_PRINT_ERROR("u_page malloc failed\n");
			return SCFS_ERR_OUT_OF_MEMORY;
		}			
		sii->cluster_buffer.u_buffer = page_address(sii->cluster_buffer.u_page);

		if (!sii->cluster_buffer.u_buffer)
			return SCFS_ERR_OUT_OF_MEMORY;
	}

	if (!sii->cluster_buffer.c_buffer) {
		sii->cluster_buffer.c_page =
			scfs_alloc_mempool_buffer(SCFS_S(sii->vfs_inode.i_sb));
		if (!sii->cluster_buffer.c_page) {
			SCFS_PRINT_ERROR("c_page malloc failed\n");
			return SCFS_ERR_OUT_OF_MEMORY;
		}				
		sii->cluster_buffer.c_buffer = page_address(sii->cluster_buffer.c_page);

		if (!sii->cluster_buffer.c_buffer)
			return SCFS_ERR_OUT_OF_MEMORY;
	}
	
	return SCFS_SUCCESS;
}
 
int scfs_truncate(struct dentry *dentry, loff_t size)
{
	struct iattr ia = { .ia_valid = ATTR_SIZE, .ia_size = size };
	struct inode *inode = dentry->d_inode;
	struct scfs_inode_info *sii = SCFS_I(inode);
	struct dentry *lower_dentry = scfs_lower_dentry(dentry);
	struct list_head *cluster_info, *tmp;
	struct cinfo_entry *info_index;
	int ret = 0;
#if SCFS_PROFILE_MEM
	struct scfs_sb_info *sbi = SCFS_S(inode->i_sb);
#endif

	SCFS_DEBUG_START;

	if (size) {
		SCFS_PRINT_ERROR("only truncate to zero-size is allowd\n");
		return -EINVAL;
	}

	SCFS_PRINT("Truncate %s size to %lld\n", dentry->d_name.name, size);
	truncate_setsize(inode, ia.ia_size);
	mutex_lock(&sii->cinfo_list_mutex);

	list_for_each_safe(cluster_info, tmp, &sii->cinfo_list) {
		info_index = list_entry(cluster_info,
				struct cinfo_entry, entry);
		list_del(&info_index->entry);
		kmem_cache_free(scfs_info_entry_list, info_index);
#if SCFS_PROFILE_MEM
		atomic_sub(sizeof(struct cinfo_entry), &sbi->kmcache_size);
#endif
	}
	mutex_unlock(&sii->cinfo_list_mutex);

	mutex_lock(&lower_dentry->d_inode->i_mutex);
	ret = notify_change(lower_dentry, &ia);
	mutex_unlock(&lower_dentry->d_inode->i_mutex);
	if (ret)
		return ret;

	ret = scfs_initialize_file(dentry, inode);
	if (ret) {
		SCFS_PRINT_ERROR("f:%s err in initializing file, ret : %d\n",
			dentry->d_name.name, ret);
		make_meta_invalid(sii);
		return ret;
	}
	if (sii->cinfo_array) {
		vfree(sii->cinfo_array);
#if SCFS_PROFILE_MEM
		atomic_sub(sii->cinfo_array_size, &sbi->vmalloc_size);
#endif
		sii->cinfo_array = NULL;
	}
	sii->cinfo_array_size = 0;
	sii->upper_file_size = 0;
	sii->cluster_buffer.original_size = 0;
	clear_meta_invalid(sii);

	SCFS_DEBUG_END;

	return ret;
}

ssize_t scfs_lower_read(struct file *file, char *buf, size_t count, loff_t *pos)
{
	int ret, read = 0, retry = 0;
	mm_segment_t  fs_save;

	fs_save = get_fs();

	while (read < count) {
		set_fs(get_ds());
		ret = vfs_read(file, buf + read, count - read, pos);
		set_fs(fs_save);
		if (ret < 0) {
			if (ret == -EINTR || ret == -EAGAIN) {
				SCFS_PRINT("still hungry, ret : %d, %lld/%lld\n",
						ret, read, count - read);
				continue;
			}

			SCFS_PRINT_ERROR("f:%s err in vfs_read, ret : %d\n",
				file->f_path.dentry->d_name.name, ret);
			return ret;
		}
		read += ret;
		if (++retry > SCFS_IO_MAX_RETRY) {
			SCFS_PRINT_ERROR("f:%s too many retries\n",
				file->f_path.dentry->d_name.name);
			return -EIO;
		}
	}
	return read;
}

ssize_t scfs_lower_write(struct file *file, char *buf, size_t count, loff_t *pos)
{
	int ret, written = 0, retry = 0;
	mm_segment_t  fs_save;

	fs_save = get_fs();

	while (written < count) {
		set_fs(get_ds());
		ret = vfs_write(file, buf + written, count - written, pos);
		set_fs(fs_save);
		if (ret < 0) {
			if (ret == -EINTR || ret == -EAGAIN) {
				SCFS_PRINT("still hungry, ret : %d, %lld/%lld\n",
						ret, written, count - written);
				continue;
			}

			SCFS_PRINT_ERROR("f:%s err in vfs_write, ret : %d\n",
				file->f_path.dentry->d_name.name, ret);
			return ret;
		}
		written += ret;
		if (++retry > SCFS_IO_MAX_RETRY) {
			SCFS_PRINT_ERROR("f:%s too many retries\n",
				file->f_path.dentry->d_name.name);
			return -EIO;
		}
	}
	return written;
}

/**
 * inode_info_init_once
 *
 * Initializes the scfs_inode_info_cache when it is created
 */
void
inode_info_init_once(void *vptr)
{
	struct scfs_inode_info *sii = (struct scfs_inode_info *)vptr;

	inode_init_once(&sii->vfs_inode);
}


static struct scfs_cache_info {
	struct kmem_cache **cache;
	const char *name;
	size_t size;
	void (*ctor)(void *obj);
} scfs_cache_infos[] = {
	{
		.cache = &scfs_file_info_cache,
		.name = "scfs_file_cache",
		.size = sizeof(struct scfs_file_info),
	},
	{
		.cache = &scfs_dentry_info_cache,
		.name = "scfs_dentry_info_cache",
		.size = sizeof(struct scfs_dentry_info),
	},
	{
		.cache = &scfs_inode_info_cache,
		.name = "scfs_inode_cache",
		.size = sizeof(struct scfs_inode_info),
		.ctor = inode_info_init_once,
	},
	{
		.cache = &scfs_sb_info_cache,
		.name = "scfs_sb_cache",
		.size = sizeof(struct scfs_sb_info),
	},
	{
		.cache = &scfs_header_cache,
		.name = "scfs_headers",
		.size = PAGE_SIZE,
	},
	{
		.cache = &scfs_xattr_cache,
		.name = "scfs_xattr_cache",
		.size = PAGE_SIZE,
	},
	{
		.cache = &scfs_info_entry_list,
		.name = "scfs_info_entry_list",
		.size = sizeof(struct cinfo_entry),
	},
	{
		.cache = &scfs_open_req_cache,
		.name = "scfs_open_req_cache",
		.size = sizeof(struct scfs_open_req),
	},

};

void scfs_free_kmem_caches(void)
{
	int i;

	SCFS_DEBUG_START;

	for (i = 0; i < ARRAY_SIZE(scfs_cache_infos); i++) {
		struct scfs_cache_info *info;

		info = &scfs_cache_infos[i];
		if (*(info->cache))
			kmem_cache_destroy(*(info->cache));
	}

	SCFS_DEBUG_END;
}

/**
 * scfs_init_kmem_caches
 *
 * Returns zero on success; non-zero otherwise
 */
int scfs_init_kmem_caches(void)
{
	int i;

	SCFS_DEBUG_START;

	for (i = 0; i < ARRAY_SIZE(scfs_cache_infos); i++) {
		struct scfs_cache_info *info;

		info = &scfs_cache_infos[i];
		*(info->cache) = kmem_cache_create(info->name, info->size,
				0, SLAB_HWCACHE_ALIGN, info->ctor);
		if (!*(info->cache)) {
			scfs_free_kmem_caches();
			SCFS_PRINT("kmem_cache_create failed\n",
					info->name);
			return SCFS_ERR_OUT_OF_MEMORY;
		}
	}

	SCFS_DEBUG_END;
	
	return SCFS_SUCCESS;
}


