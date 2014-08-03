#include "scfs.h"

/* cluster cache list, and related stuff */
struct read_buffer_cache buffer_cache[MAX_BUFFER_CACHE];
spinlock_t buffer_cache_lock;
int read_buffer_index = 0;

/**
 * scfs_readpage
 *
 * Parameters:
 * @file: upper file
 * @page: upper page from SCFS inode mapping, data will be copied in here
 *
 * Return:
 * SCFS_SUCCESS if success, otherwise if error
 *
 * Description:
 * - Read in a page by reading a cluster from the file's lower file.
 *   (Reading in a lower cluster for just a single upper page is inevitable
 *    for decompression. The adverse effect of seemingly amplified reads is
 *    mitigated by adding rest of the pages in the cluster to the page cache,
 *    thereby "reading ahead" in its own way.
 * - A pool of cluster buffers are cached for later re-use.
 *   (Repeated reads for the same page will only search through the said list of
 *    buffers without incurring cluster reads.)
 */

static int scfs_readpage(struct file *file, struct page *page)
{
	struct scfs_inode_info *sii = SCFS_I(page->mapping->host);
	struct scfs_sb_info *sbi = SCFS_S(page->mapping->host->i_sb);
	struct scfs_cluster_buffer buffer = {NULL, NULL, NULL, NULL, 0};
	int ret = SCFS_SUCCESS, compressed = 0;
	int alloc_membuffer = 1;
	int allocated_index = -1;
	int i;
	char *virt;

	SCFS_PRINT("f:%s i:%d c:0x%x u:0x%x\n",
		file->f_path.dentry->d_name.name,
		page->index, buffer.c_buffer, buffer.u_buffer);
	ASSERT(sii->cluster_size <= SCFS_CLUSTER_SIZE_MAX);

	/* search cluster for page in buffer_cache */
	spin_lock(&buffer_cache_lock);
	for (i = 0; i < MAX_BUFFER_CACHE; i++) {
		if (buffer_cache[i].inode_number == sii->vfs_inode.i_ino &&
				buffer_cache[i].cluster_number ==
				PAGE_TO_CLUSTER_INDEX(page, sii) &&
				atomic_read(&buffer_cache[i].is_used) != 1) {
			virt = kmap_atomic(page);

			if (buffer_cache[i].is_compressed)
				memcpy(virt, page_address(buffer_cache[i].u_page) +
					PGOFF_IN_CLUSTER(page, sii) * PAGE_SIZE, PAGE_SIZE);
			else
				memcpy(virt, page_address(buffer_cache[i].c_page) +
					PGOFF_IN_CLUSTER(page, sii) * PAGE_SIZE, PAGE_SIZE);

			spin_unlock(&buffer_cache_lock);
			kunmap_atomic(virt);
			flush_dcache_page(page);
			SetPageUptodate(page);
			unlock_page(page);

			return SCFS_SUCCESS;
		}
		if (i == read_buffer_index &&
				atomic_read(&buffer_cache[i].is_used) == 1) {
			read_buffer_index++;
			if (read_buffer_index >= MAX_BUFFER_CACHE)
				read_buffer_index = 0;
		}
	}

	/* read a cluster into one of the buffers, and decompress if needed */
	if (atomic_read(&buffer_cache[read_buffer_index].is_used) != 1) {
		buffer.c_page = buffer_cache[read_buffer_index].c_page;
		buffer.u_page = buffer_cache[read_buffer_index].u_page;
		atomic_set(&buffer_cache[read_buffer_index].is_used, 1);
		buffer_cache[read_buffer_index].inode_number = sii->vfs_inode.i_ino;
		buffer_cache[read_buffer_index].cluster_number =
			PAGE_TO_CLUSTER_INDEX(page, sii);
		allocated_index = read_buffer_index++;

		if (read_buffer_index >= MAX_BUFFER_CACHE)
			read_buffer_index = 0;
		alloc_membuffer = 0;
	} else {
		for (i = 0; i < MAX_BUFFER_CACHE; i++) {
			if (atomic_read(&buffer_cache[i].is_used) != 1) {
				buffer.c_page = buffer_cache[i].c_page;
				buffer.u_page = buffer_cache[i].u_page;
				atomic_set(&buffer_cache[i].is_used, 1);
				buffer_cache[i].inode_number = sii->vfs_inode.i_ino;
				buffer_cache[i].cluster_number =
					PAGE_TO_CLUSTER_INDEX(page, sii);
				allocated_index = i;
				read_buffer_index = i + 1;

				if (read_buffer_index >= MAX_BUFFER_CACHE)
					read_buffer_index = 0;
				alloc_membuffer = 0;
				break;
			}
		}
	}
	spin_unlock(&buffer_cache_lock);

	/* buffer_cache is full - alloc from mempool buffer */
	if (alloc_membuffer == 1 && (buffer.c_page || buffer.c_buffer))
		ASSERT(0);

	if (!buffer.c_page)
		buffer.c_page = scfs_alloc_mempool_buffer(sbi);

	if (!buffer.c_page) {
		SCFS_PRINT_ERROR("c_page malloc failed\n");
		return SCFS_ERR_OUT_OF_MEMORY;
	}

	if (!buffer.c_buffer)
		buffer.c_buffer = page_address(buffer.c_page);

	if (!buffer.c_buffer) {
		SCFS_PRINT_ERROR("c_buffer malloc failed\n");
		ret = SCFS_ERR_OUT_OF_MEMORY;
		ASSERT(0);
		goto out;
	}

	if (!buffer.u_page)
		buffer.u_page = scfs_alloc_mempool_buffer(sbi);

	if (!buffer.u_page) {
		SCFS_PRINT_ERROR("u_page malloc failed\n");
		return SCFS_ERR_OUT_OF_MEMORY;
	}

	if (!buffer.u_buffer)
		buffer.u_buffer = page_address(buffer.u_page);

	if (!buffer.u_buffer) {
		SCFS_PRINT_ERROR("u_buffer malloc failed\n");
		ret = SCFS_ERR_OUT_OF_MEMORY;
		ASSERT(0);
		goto out;
	}

	ret = scfs_read_cluster(file, page, buffer.c_buffer, &buffer.u_buffer, &compressed);

	if (ret == -ERANGE) {
		SCFS_PRINT_ERROR("file %s error on readpage, OOB. ret %x\n",
				file->f_path.dentry->d_name.name, ret);
		goto out;

	} else if (ret) {
		SCFS_PRINT_ERROR("read cluster failed, "
			"file %s page->index %u ret %d\n",
			file->f_path.dentry->d_name.name, page->index, ret);
		ASSERT(0);
	}

	/* don't need to spinlock, we have is_used=1 for this buffer */
	if (alloc_membuffer != 1)
		buffer_cache[allocated_index].is_compressed = compressed;

	/* fill page cache with the decompressed or original page */
	virt = kmap_atomic(page);
	if (compressed)
		memcpy(virt, page_address(buffer.u_page) + PGOFF_IN_CLUSTER(page, sii) * PAGE_SIZE,
			PAGE_SIZE);
	else
		memcpy(virt, page_address(buffer.c_page) + PGOFF_IN_CLUSTER(page, sii) * PAGE_SIZE,
			PAGE_SIZE);

	kunmap_atomic(virt);
	flush_dcache_page(page);
	SetPageUptodate(page);
	unlock_page(page);

	if (alloc_membuffer != 1) {
		spin_lock(&buffer_cache_lock);
		atomic_set(&buffer_cache[allocated_index].is_used, 0);
		spin_unlock(&buffer_cache_lock);
	}

out:
	if (alloc_membuffer == 1) {
		scfs_free_mempool_buffer(buffer.c_page, sbi);
		scfs_free_mempool_buffer(buffer.u_page, sbi);
	}

	SCFS_PRINT("-f:%s i:%d c:0x%x u:0x%x\n",
		file->f_path.dentry->d_name.name,
		page->index, buffer.c_buffer, buffer.u_buffer);

	return ret;
}

/**
 * scfs_write_begin
 * @file: The scfs file
 * @mapping: The scfs object
 * @pos: The file offset at which to start writing
 * @len: Length of the write
 * @flags: Various flags
 * @pagep: Pointer to return the page
 * @fsdata: Pointer to return fs data (unused)
 *
 * SCFS doesn't handle Random Write. So, this function will return EINVAL if pos < i_size for current file.
 *
 */
static int scfs_write_begin(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned flags,
			struct page **pagep, void **fsdata)
{
	pgoff_t index = pos >> PAGE_CACHE_SHIFT;
	struct page *page;
	struct file *lower_file = NULL;
	struct scfs_inode_info *sii = SCFS_I(mapping->host);
	struct scfs_cinfo clust_info;
	int ret = 0;

	SCFS_PRINT("f:%s pos:%lld, len:%d s:%lld\n",
			file->f_path.dentry->d_name.name, pos, len, 
			i_size_read(&sii->vfs_inode));

	page = grab_cache_page_write_begin(mapping, index, flags);
	if (!page)
		return -ENOMEM;
		
	*pagep = page;
	if (pos != i_size_read(&sii->vfs_inode)) {
		SCFS_PRINT("File %s RANDOM write access! pos = %lld, i_size = %lld\n",
			file->f_path.dentry->d_name.name,pos,i_size_read(&sii->vfs_inode));
		ret = -EINVAL;
		goto out;
	}

	lower_file = scfs_lower_file(file);
	if (!lower_file) {
		SCFS_PRINT_ERROR("lower file is null!\n");
		ret = -EIO;
		goto out;
	}	

	if (IS_COMPRESSED(sii)) {
		struct cinfo_entry *info_entry;
		ret = scfs_get_comp_buffer(sii);
		if (ret)
			goto out;

		mutex_lock(&sii->cinfo_list_mutex);
		if (list_empty(&sii->cinfo_list)) {
			info_entry = scfs_alloc_cinfo_entry(PAGE_TO_CLUSTER_INDEX(page,sii), sii);
			if (!info_entry) {
				mutex_unlock(&sii->cinfo_list_mutex);
				SCFS_PRINT_ERROR("Cannot alloc new cluster_info.");
				ret = -ENOMEM;
				ASSERT(0);
				goto out;
			}

			if (PAGE_TO_CLUSTER_INDEX(page,sii) == 0)
				info_entry->cinfo.offset = 0;

			if (CLUSTER_EXISTS(sii, PAGE_TO_CLUSTER_INDEX(page,sii))) {
				mutex_unlock(&sii->cinfo_list_mutex);
				ret = get_cluster_info(file, PAGE_TO_CLUSTER_INDEX(page,sii),
						&clust_info);
				mutex_lock(&sii->cinfo_list_mutex);
				if (ret) {
					mutex_unlock(&sii->cinfo_list_mutex);
					SCFS_PRINT_ERROR("page is in file, " \
						"but cannot get cluster info.");
					ASSERT(0);
					goto out;
				}
				info_entry->cinfo.offset = clust_info.offset;
				ret = scfs_get_cluster_from_lower(sii, lower_file, clust_info);
				if (ret) {
					mutex_unlock(&sii->cinfo_list_mutex);
					SCFS_PRINT_ERROR("Fail to get lower data.");
					ASSERT(0);
					goto out;
				}				

				if (!PageUptodate(page))
					sync_page_from_buffer(page, sii->cluster_buffer.u_buffer);
				
			} else if (PAGE_TO_CLUSTER_INDEX(page,sii) > 0 
				&& CLUSTER_EXISTS(sii, PAGE_TO_CLUSTER_INDEX(page,sii) - 1)) {
				ret = get_cluster_info(file, PAGE_TO_CLUSTER_INDEX(page,sii) - 1,
						&clust_info);
				if (ret) {
					mutex_unlock(&sii->cinfo_list_mutex);
					SCFS_PRINT_ERROR("page is in file, but cannot get cluster info.");
					ASSERT(0);
					goto out;
				}

				info_entry->cinfo.offset = clust_info.offset+clust_info.size;
				if (clust_info.size%SCFS_CLUSTER_ALIGN) {
					info_entry->cinfo.offset += 
					(SCFS_CLUSTER_ALIGN - (clust_info.size%SCFS_CLUSTER_ALIGN));
				}
			}
		} else {
			struct cinfo_entry *new_list = NULL;

			if (!PageUptodate(page) && pos & (PAGE_CACHE_SIZE - 1)) {
				SCFS_PRINT_ERROR("Current page was reclaimed " \
					"before be written to lower\n");
				ASSERT(0);
			}
			info_entry = list_entry(sii->cinfo_list.prev,
				struct cinfo_entry, entry);
			if (info_entry->current_cluster_idx != PAGE_TO_CLUSTER_INDEX(page,sii)) {
				if (info_entry->current_cluster_idx ==
						PAGE_TO_CLUSTER_INDEX(page,sii) - 1)
					new_list = scfs_alloc_cinfo_entry(PAGE_TO_CLUSTER_INDEX(page,sii),
							sii);
				else
					info_entry = NULL;			
			}

			if (!info_entry) {
				mutex_unlock(&sii->cinfo_list_mutex);
				SCFS_PRINT_ERROR("Cannot alloc new cluster_info.");
				ret = -ENOMEM;
				ASSERT(0);
				goto out;
			}

			if (new_list) {
				new_list->cinfo.offset =
					info_entry->cinfo.offset +
					info_entry->cinfo.size;
				if(info_entry->cinfo.size % SCFS_CLUSTER_ALIGN)
					new_list->cinfo.offset += 
					(SCFS_CLUSTER_ALIGN -
					(info_entry->cinfo.size % SCFS_CLUSTER_ALIGN));
			}
		}		
		mutex_unlock(&sii->cinfo_list_mutex);
	} else {
		/* Fake info list : We need to write meta at the EOF. 
		 * But, write meta check whether info list is empty or not.
		 * In this case, we cannot write META because we don't use cluster info list and also list is empty.
		 * So, We add one fake info list to sii->cinfo_list
		*/
		if (list_empty(&sii->cinfo_list)) {
			struct cinfo_entry *info_entry = NULL;
			info_entry = scfs_alloc_cinfo_entry(PAGE_TO_CLUSTER_INDEX(page,sii),
					sii);
			sii->cluster_buffer.original_size = 0;
		}
		if (!PageUptodate(page)) {
			unsigned pos_in_page = pos & (PAGE_CACHE_SIZE - 1);
			//TODO: We should read exist page data from lower if page is not uptodate
			if (pos_in_page) {
				char *source_addr;
				loff_t lower_pos;
			
				lower_pos = pos-pos_in_page;
				source_addr = (char*)kmap(page);
				ret = scfs_lower_read(lower_file, source_addr, pos_in_page, &lower_pos);
				if (ret < 0) {
					SCFS_PRINT_ERROR("read fail. ret = %d, size=%d\n", ret, len);
					lower_pos -= ret;
				} else
					ret = 0;
				kunmap(page);
			}
		}
	}
	SetPageUptodate(page);
out:
	if (unlikely(ret)) {
		unlock_page(page);
		page_cache_release(page);
		*pagep = NULL;
	}

	SCFS_DEBUG_END;
	return ret;
}

static int scfs_write_end(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned copied,
			struct page *page, void *fsdata)
{
	unsigned from = pos & (PAGE_CACHE_SIZE - 1);
	unsigned to = from + copied;
	struct scfs_inode_info *sii = SCFS_I(mapping->host);
	struct file *lower_file = NULL;
	struct scfs_sb_info *sb_info = SCFS_S(sii->vfs_inode.i_sb);
	loff_t lower_pos;
	int ret;
 
	SCFS_PRINT("f:%s pos:%lld, len:%d s:%lld i:%d\n",
			file->f_path.dentry->d_name.name, pos, len, 
			i_size_read(&sii->vfs_inode), page->index);

	lower_file = scfs_lower_file(file);
	if (!lower_file) {
		SCFS_PRINT_ERROR("lower file is null!\n");
		ret = -EINVAL;
		ASSERT(0);
		goto out;
	}

	if (IS_COMPRESSED(sii)) {
 		ret = scfs_get_comp_buffer(sii);
		if (ret)
			goto out;

		sii->cluster_buffer.original_size += len; 
		sync_page_to_buffer(page, sii->cluster_buffer.u_buffer); 
 		if (PGOFF_IN_CLUSTER(page, sii) + 1 == sii->cluster_size / PAGE_CACHE_SIZE &&
				to == PAGE_CACHE_SIZE) {
			struct cinfo_entry *info_entry = NULL;

			mutex_lock(&sii->cinfo_list_mutex);

			if (list_empty(&sii->cinfo_list)) {
				mutex_lock(&sii->cinfo_list_mutex);
				SCFS_PRINT_ERROR("cinfo list is empty\n");
				ret = -EINVAL;
				ASSERT(0);
				goto out;
			}
			info_entry = list_entry(sii->cinfo_list.prev,
					struct cinfo_entry, entry);

			if (info_entry->current_cluster_idx !=
					PAGE_TO_CLUSTER_INDEX(page,sii)) {
				SCFS_PRINT_ERROR("Cannot find cluster info entry" \
					"for cluster idx %d\n", PAGE_TO_CLUSTER_INDEX(page,sii));
				ASSERT(0);
			}
			ret = scfs_compress(sii->comp_type, sii->cluster_buffer.c_buffer,
				sii->cluster_buffer.u_buffer,
				sii->cluster_buffer.original_size,
				&info_entry->cinfo.size);
			if (ret) {
				mutex_unlock(&sii->cinfo_list_mutex);
				ClearPageUptodate(page);
				SCFS_PRINT_ERROR("compression failed.\n");
				ASSERT(0);
				goto out;
			}

			if (info_entry->cinfo.size >=
					sii->cluster_buffer.original_size *
					sb_info->options.comp_threshold / 100)
				info_entry->cinfo.size = sii->cluster_buffer.original_size;
	        	
			if (info_entry->cinfo.size % SCFS_CLUSTER_ALIGN)
				info_entry->pad = SCFS_CLUSTER_ALIGN -
					(info_entry->cinfo.size % SCFS_CLUSTER_ALIGN);
			else
				info_entry->pad = 0;

			SCFS_PRINT("cluster original size = %ld, comp size = %d, pad = %d\n"
				,sii->cluster_buffer.original_size
				,info_entry->cinfo.size
				,info_entry->pad);
				
			lower_pos = (loff_t)info_entry->cinfo.offset;

			if (info_entry->cinfo.size <
					sii->cluster_buffer.original_size *
					sb_info->options.comp_threshold / 100) {
				size_t write_count;
				write_count = (size_t)info_entry->cinfo.size+info_entry->pad;
				mutex_unlock(&sii->cinfo_list_mutex);

				ret = scfs_lower_write(lower_file, sii->cluster_buffer.c_buffer,
					write_count, &lower_pos);
				if (ret < 0) {
					SCFS_PRINT_ERROR("write fail. ret = %d, size=%ld\n",
						ret, write_count);
					ASSERT(0);
					goto out;
				}

				if (!sii->compressd)
					sii->compressd = 1;
		    	} else {
				info_entry->cinfo.size = sii->cluster_buffer.original_size;
				info_entry->pad = 0;
				mutex_unlock(&sii->cinfo_list_mutex);
				ret = scfs_lower_write(lower_file, sii->cluster_buffer.u_buffer,
					sii->cluster_buffer.original_size, &lower_pos); 
				if (ret < 0) {
					SCFS_PRINT_ERROR("write fail. ret = %d, size=%d\n",
						ret, sii->cluster_buffer.original_size);
					ASSERT(0);
					goto out;
				}
		    	}
			sii->cluster_buffer.original_size = 0;
 		}
		ret = len;
	} else {
		char *source_addr;

		lower_pos = pos;
		source_addr = (char*)kmap(page);
		ret = scfs_lower_write(lower_file, source_addr+from, len, &lower_pos);
		if (ret < 0) {
			SCFS_PRINT_ERROR("write fail. ret = %d, size=%d\n", ret, len);
			ASSERT(0);
			goto out;
		}
		kunmap(page);
	}

	if (pos + copied > i_size_read(&sii->vfs_inode)) {
		i_size_write(&sii->vfs_inode, pos + copied);
		SCFS_PRINT("Expanded file size to [0x%.16llx]\n",
			(unsigned long long)i_size_read(&sii->vfs_inode));
	}
	SetPageUptodate(page);
out:
	unlock_page(page);
	page_cache_release(page);
	SCFS_DEBUG_END;
	
	return ret;
}

/**************************************/
/* address_space_operations structure */
/**************************************/

/* I'm not sure we need bmap operation */
const struct address_space_operations scfs_aops = {
	.readpage = scfs_readpage,
	.write_begin = scfs_write_begin,
	.write_end = scfs_write_end,
};
