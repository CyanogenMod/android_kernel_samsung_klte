/*
 * fs/scfs/mmap.c
 *
 * Copyright (C) 2014 Samsung Electronics Co., Ltd.
 *   Authors: Sunghwan Yun <sunghwan.yun@samsung.com>
 *            Jongmin Kim <jm45.kim@samsung.com>
 *            Sangwoo Lee <sangwoo2.lee@samsung.com>
 *            Inbae Lee   <inbae.lee@samsung.com>
 *
 * This program has been developed as a stackable file system based on
 * the WrapFS, which was written by:
 *
 * Copyright (C) 1997-2003 Erez Zadok
 * Copyright (C) 2001-2003 Stony Brook University
 * Copyright (C) 2004-2006 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mahalcro@us.ibm.com>
 *              Michael C. Thompson <mcthomps@us.ibm.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "scfs.h"

#if MAX_BUFFER_CACHE
/* cluster cache list, and related stuff */
struct read_buffer_cache buffer_cache[MAX_BUFFER_CACHE];
spinlock_t buffer_cache_lock;
int read_buffer_index = 0;
#endif

#ifdef SCFS_ASYNC_READ_PAGES
u64 scfs_readpage_total_count = ATOMIC_INIT(0);
u64 scfs_readpage_io_count = ATOMIC_INIT(0);
u64 scfs_lowerpage_total_count = ATOMIC_INIT(0);
u64 scfs_lowerpage_reclaim_count = ATOMIC_INIT(0);
u64 scfs_lowerpage_alloc_count = ATOMIC_INIT(0);
u64 scfs_op_mode = ATOMIC_INIT(0);
u64 scfs_sequential_page_number = SCFS_SEQUENTIAL_PAGE_NUM;
#endif

#ifdef SCFS_PRELOAD_BOOTING_CLUSTER
struct task_struct *scfs_pbc = NULL;
int is_scfs_mounted = 0;
atomic_t pcb_read_count = {0};
atomic_t scfs_lower_read_count = {0};
#endif

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
 *   (Reading in a cluster for just a single page read is inevitable, but this
 *    "amplified read" and decompressing overhead should be amortized when
 *    other pages in that same cluster is accessed later, and only incurs
 *    memcpy from the cached cluster buffer.)
 * - Recently accessed clusters ("buffer_cache") are cached for later reads.
 */

static int scfs_readpage(struct file *file, struct page *page)
{
	struct scfs_inode_info *sii = SCFS_I(page->mapping->host);
	struct scfs_sb_info *sbi = SCFS_S(page->mapping->host->i_sb);
	struct scfs_cluster_buffer buffer = {NULL, NULL, NULL, NULL, 0};
	int ret = 0, compressed = 0;
	int alloc_membuffer = 1;
	int allocated_index = -1;
	int i;
	char *virt;

	SCFS_PRINT("f:%s i:%d c:0x%x u:0x%x\n",
		file->f_path.dentry->d_name.name,
		page->index, buffer.c_buffer, buffer.u_buffer);
	ASSERT(sii->cluster_size <= SCFS_CLUSTER_SIZE_MAX);

#if (defined(SCFS_READ_PAGES_PROFILE) && defined(SCFS_ASYNC_READ_PAGES))
	scfs_readpage_total_count++;
#endif

#if MAX_BUFFER_CACHE
	/* search buffer_cache first in case the cluster is left cached */
	spin_lock(&buffer_cache_lock);
	for (i = 0; i < MAX_BUFFER_CACHE; i++) {
		if (buffer_cache[i].inode_number == sii->vfs_inode.i_ino &&
				buffer_cache[i].cluster_number ==
				PAGE_TO_CLUSTER_INDEX(page, sii) &&
				atomic_read(&buffer_cache[i].is_used) != 1) {
			atomic_set(&buffer_cache[i].is_used, 1);
			spin_unlock(&buffer_cache_lock);
			virt = kmap_atomic(page);

			if (buffer_cache[i].is_compressed)
				memcpy(virt, page_address(buffer_cache[i].u_page) +
					PGOFF_IN_CLUSTER(page, sii) * PAGE_SIZE, PAGE_SIZE);
			else
				memcpy(virt, page_address(buffer_cache[i].c_page) +
					PGOFF_IN_CLUSTER(page, sii) * PAGE_SIZE, PAGE_SIZE);

			spin_lock(&buffer_cache_lock);
			atomic_set(&buffer_cache[i].is_used, 0);
			spin_unlock(&buffer_cache_lock);
			kunmap_atomic(virt);
			SetPageUptodate(page);
			unlock_page(page);
			SCFS_PRINT("%s<h> %d\n",file->f_path.dentry->d_name.name, page->index);

			return 0;
		}
		if (i == read_buffer_index &&
				atomic_read(&buffer_cache[i].is_used) == 1) {
			read_buffer_index++;
			if (read_buffer_index >= MAX_BUFFER_CACHE)
				read_buffer_index = 0;
		}
	}

	/* pick a slot in buffer_cache to use */
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
#endif

#if (defined(SCFS_READ_PAGES_PROFILE) && defined(SCFS_ASYNC_READ_PAGES))
	scfs_readpage_io_count++;
#endif

	/* sanity check & prepare buffers for scfs_read_cluster */
	if (alloc_membuffer == 1 && (buffer.c_page || buffer.c_buffer))
		ASSERT(0);

	if (!buffer.c_page)
		buffer.c_page = scfs_alloc_mempool_buffer(sbi);

	if (!buffer.c_page) {
		SCFS_PRINT_ERROR("c_page malloc failed\n");
		ret = -ENOMEM;
		goto out;
	}

	if (!buffer.c_buffer)
		buffer.c_buffer = page_address(buffer.c_page);

	if (!buffer.c_buffer) {
		SCFS_PRINT_ERROR("c_buffer malloc failed\n");
		ret = -ENOMEM;
		goto out;
	}

	if (!buffer.u_page)
		buffer.u_page = scfs_alloc_mempool_buffer(sbi);

	if (!buffer.u_page) {
		SCFS_PRINT_ERROR("u_page malloc failed\n");
		ret = -ENOMEM;
		goto out;
	}

	if (!buffer.u_buffer)
		buffer.u_buffer = page_address(buffer.u_page);

	if (!buffer.u_buffer) {
		SCFS_PRINT_ERROR("u_buffer malloc failed\n");
		ret = -ENOMEM;
		goto out;
	}

	/* read cluster from lower */
	ret = scfs_read_cluster(file, page, buffer.c_buffer, &buffer.u_buffer, &compressed);

	if (ret) {
		if (ret == -ERANGE)
			SCFS_PRINT_ERROR("file %s error on readpage, OOB. ret %x\n",
				file->f_path.dentry->d_name.name, ret);
		else
			SCFS_PRINT_ERROR("read cluster failed, "
				"file %s page->index %u ret %d\n",
				file->f_path.dentry->d_name.name, page->index, ret);
		goto out;
	}

#if MAX_BUFFER_CACHE
	/* don't need to spinlock, we have is_used=1 for this buffer */
	if (alloc_membuffer != 1)
		buffer_cache[allocated_index].is_compressed = compressed;
#endif

#ifdef SCFS_REMOVE_NO_COMPRESSED_UPPER_MEMCPY
	/* fill page cache with the decompressed or original page */
	if (compressed) {
		virt = kmap_atomic(page);
		memcpy(virt, page_address(buffer.u_page) + PGOFF_IN_CLUSTER(page, sii) * PAGE_SIZE,
			PAGE_SIZE);
		kunmap_atomic(virt);
	}
#else
	/* fill page cache with the decompressed/original data */
	virt = kmap_atomic(page);
	if (compressed)
		memcpy(virt, page_address(buffer.u_page) + PGOFF_IN_CLUSTER(page, sii) * PAGE_SIZE,
			PAGE_SIZE);
	else
		memcpy(virt, page_address(buffer.c_page) + PGOFF_IN_CLUSTER(page, sii) * PAGE_SIZE,
			PAGE_SIZE);
	kunmap_atomic(virt);
#endif

	SetPageUptodate(page);

#if MAX_BUFFER_CACHE
#ifndef SCFS_REMOVE_NO_COMPRESSED_UPPER_MEMCPY
	if (alloc_membuffer != 1) {
		spin_lock(&buffer_cache_lock);
		atomic_set(&buffer_cache[allocated_index].is_used, 0);
		spin_unlock(&buffer_cache_lock);
	}
#else
	if (alloc_membuffer != 1 && compressed) {
		spin_lock(&buffer_cache_lock);
		atomic_set(&buffer_cache[allocated_index].is_used, 0);
		spin_unlock(&buffer_cache_lock);
	} else if (alloc_membuffer != 1) {
		spin_lock(&buffer_cache_lock);
		buffer_cache[allocated_index].inode_number = -1;
		buffer_cache[allocated_index].cluster_number = -1;
		buffer_cache[allocated_index].is_compressed = -1;
		atomic_set(&buffer_cache[allocated_index].is_used, -1);
		spin_unlock(&buffer_cache_lock);
	}
#endif
#endif

out:
	unlock_page(page);

	if (alloc_membuffer == 1) {
		scfs_free_mempool_buffer(buffer.c_page, sbi);
		scfs_free_mempool_buffer(buffer.u_page, sbi);
	}

	SCFS_PRINT("-f:%s i:%d c:0x%x u:0x%x\n",
		file->f_path.dentry->d_name.name,
		page->index, buffer.c_buffer, buffer.u_buffer);

	SCFS_PRINT("%s<r> %d\n",file->f_path.dentry->d_name.name, page->index);
	return ret;
}

#ifdef SCFS_ASYNC_READ_PAGES
#include <linux/freezer.h>
#include <linux/kthread.h>
#include <linux/gfp.h>
#include <linux/sched.h>

/* memory and file buffer for scfs_readpages, for queueing read requests */
struct page *page_buffer_smb[MAX_PAGE_BUFFER_SIZE_SMB];
struct file *file_buffer_smb[MAX_PAGE_BUFFER_SIZE_SMB];

/* when page_buffer_smb and file_buffer_smb is full, then this filling_index is
	set to MAX_PAGE_BUFFER_SIZE */
int page_buffer_next_filling_index_smb;
int page_buffer_next_io_index_smb;
spinlock_t spinlock_smb;

/* helper threads to process multiple read I/Os simultaneously */
struct task_struct *smb_task[NR_CPUS] = {NULL, };
int smb_task_status[NR_CPUS] = {0, };

#ifdef SCFS_PRELOAD_BOOTING_CLUSTER
int preload_booting_cluster_thread(void *nothing) {
	int read_amount;
	char *read_buf;
	int fd;
	int read_pos = 0;
	char *pathname;
	char *offset;
	char *len;
	unsigned long offset_digit, len_digit;
	int loop_count = 0;
	struct path path;
	int ret;

	if (!is_scfs_mounted) {
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
	}
	msleep(20);

	fd = sys_open("/system/etc/bci", O_RDONLY, 0);
	if (fd < 0) {
		SCFS_PRINT_ERROR("failed to open (%d)\n", fd);
		return fd;
	} else {
		SCFS_PRINT_ERROR("success to open (%d)\n", fd);
	}

	read_buf = (char *)__get_free_pages(GFP_KERNEL, 9);
	if (!read_buf) {
		SCFS_PRINT_ERROR("alloc fail\n");
		return 0;
	}

	read_amount = sys_read(fd, read_buf, 2*1024*1024);
	if (read_amount < 0) {
		SCFS_PRINT_ERROR("read fail (%d)\n", read_amount);
		free_pages((unsigned long) read_buf, 9);
		return read_amount;
	} else {
		SCFS_PRINT_ERROR("read success (%d)\n", read_amount);
	}

	SCFS_PRINT_ERROR("start\n");
	pathname = read_buf;
	while(read_pos < read_amount) {
		loop_count++;
		offset = memchr(pathname, (int)' ', read_amount - read_pos);
		if (offset == NULL) break;
		*offset = '\0';
		offset++;
		read_pos += (offset - pathname);

		len = memchr(offset, (int)' ', read_amount - read_pos);
		if (len == NULL) break;
		*len = '\0';
		len++;
		read_pos += (len - offset);

		if (atomic_read(&pcb_read_count) > atomic_read(&scfs_lower_read_count) + 300 )
			goto sleep;

		if (atomic_read(&pcb_read_count) < atomic_read(&scfs_lower_read_count) - 300 )
			goto next;

		offset_digit = simple_strtoul(offset, NULL, 10);
		len_digit = simple_strtoul(len, NULL, 10);

		//SCFS_PRINT_ERROR("%d %s %u %u %d %d %d\n", loop_count, pathname, offset_digit, len_digit, read_pos,
		//	atomic_read(&pcb_read_count), atomic_read(&scfs_lower_read_count));

		ret = kern_path(pathname, LOOKUP_FOLLOW, &path);
		if (ret) {
			SCFS_PRINT_ERROR("error(%d)\n", ret);
			break;
		}
		ret = force_page_cache_readahead(path.dentry->d_inode->i_mapping, NULL, offset_digit >> PAGE_SHIFT, 
			(unsigned long)(((offset_digit + len_digit + PAGE_SIZE - 1) >> PAGE_SHIFT) - ((offset_digit >> PAGE_SHIFT))));

		if (ret < 0) {
			SCFS_PRINT_ERROR("error(%d)\n", ret);
			break;
		}
		goto next;
sleep:
		if (atomic_read(&pcb_read_count) - atomic_read(&scfs_lower_read_count) > 200)
			msleep(10);
next:
		atomic_inc(&pcb_read_count);
		pathname = memchr(len, (int)'\n', read_amount - read_pos);
		if (pathname == NULL) break;
		pathname++;
		read_pos += (pathname - len);
	}
	free_pages((unsigned long) read_buf, 9);
	SCFS_PRINT_ERROR("end(%d %d %d)\n", loop_count, atomic_read(&pcb_read_count), atomic_read(&scfs_lower_read_count));

	return 0;
}
#endif

int smb_init(void) {
	int i, j;

	page_buffer_next_filling_index_smb = 0;
	page_buffer_next_io_index_smb = 0;
	spin_lock_init(&spinlock_smb);

	for (i = 0; i < NR_CPUS; i++) {
		smb_task[i] = kthread_run(smb_thread, &smb_task_status[i], "scfs_mb%d", i);

		if (IS_ERR(smb_task[i])) {
			SCFS_PRINT_ERROR("smb_init: creating kthread failed\n");

			for (j=0; j < i; j++)
				kthread_stop(smb_task[j]);
			return -ENOMEM;
		}

#ifdef SCFS_SMB_THREAD_CPU_AFFINITY
		{
			struct cpumask cpus[NR_CPUS];
			cpumask_clear(&cpus[i]);
			cpumask_set_cpu(i, &cpus[i]);

			if (sched_setaffinity(smb_task[i]->pid, &cpus[i])) {
				SCFS_PRINT_ERROR("smb_init: set CPU affinity failed\n");
			}
		}
#endif
	}

#ifdef SCFS_PRELOAD_BOOTING_CLUSTER
	scfs_pbc = kthread_run(preload_booting_cluster_thread, NULL, "scfs_pbc");
	if (IS_ERR(scfs_pbc)) {
		SCFS_PRINT_ERROR("preload_booting_cluster_thread: creating kthread failed\n");
	} else {
		SCFS_PRINT_ERROR("preload_booting_cluster_thread: creating kthread success\n");
	}
#endif
	return 0;
}

/* scaling # of threads will be woken up, on-demand */
void wakeup_smb_thread(void) {
	int length = 0, io_index, filling_index;

	spin_lock(&spinlock_smb);
	io_index = page_buffer_next_io_index_smb;
	filling_index = page_buffer_next_filling_index_smb;
	spin_unlock(&spinlock_smb);
	if (filling_index == MAX_PAGE_BUFFER_SIZE_SMB)
		length = MAX_PAGE_BUFFER_SIZE_SMB;
	else if (filling_index > io_index)
		length = filling_index - io_index;
	else if (filling_index < io_index)
		length = (MAX_PAGE_BUFFER_SIZE_SMB - io_index) + filling_index;
	else if (filling_index == io_index) 
		length = 0;

	if (length > 0 && smb_task[0] && !smb_task_status[0])
		wake_up_process(smb_task[0]);
#if (NR_CPUS > 1)
	if (length >= SMB_THREAD_THRESHOLD_2 && smb_task[1] && !smb_task_status[1])
		wake_up_process(smb_task[1]);
#if (NR_CPUS > 2)
	if (length >= SMB_THREAD_THRESHOLD_3 && smb_task[2] && !smb_task_status[2])
		wake_up_process(smb_task[2]);
#if (NR_CPUS > 3)
	if (length >= SMB_THREAD_THRESHOLD_4 && smb_task[3] && !smb_task_status[3])
		wake_up_process(smb_task[3]);
#endif
#endif
#endif
}

int smb_thread(void *my_smb_task_status)
{
	int length = 0, io_index, filling_index;
	struct page *page;
	struct page *temp_page;
	struct page *page_buffer[3] = {NULL, NULL, NULL};
	struct file *file;
	struct file *temp_file = NULL;
	struct scfs_inode_info *sii;
	int cluster_number = -1;
	int page_buffer_count = 0;
	int i;

	set_freezable();

	/* handle any queued-up read requests, or else go back to sleep */
	while (!kthread_should_stop()) {
		set_current_state(TASK_INTERRUPTIBLE);
		spin_lock(&spinlock_smb);

		/* calculate number of pages of page buffer */
		io_index = page_buffer_next_io_index_smb;
		filling_index = page_buffer_next_filling_index_smb;
		if (filling_index == MAX_PAGE_BUFFER_SIZE_SMB) {
			length = MAX_PAGE_BUFFER_SIZE_SMB;
			page_buffer_next_filling_index_smb = page_buffer_next_io_index_smb;
		}
		else if (filling_index > io_index)
			length = filling_index - io_index;
		else if (filling_index < io_index)
			length = (MAX_PAGE_BUFFER_SIZE_SMB - io_index) + filling_index;
		else if (filling_index == io_index) 
			length = 0;
		page_buffer_count = 0;

		/* the requested page, as well as subsequent pages in the same cluster, will be serviced,
			in two separate readpage calls */
		if (length > 0) {
			__set_current_state(TASK_RUNNING);
			page = page_buffer_smb[page_buffer_next_io_index_smb];
			file = file_buffer_smb[page_buffer_next_io_index_smb];

			page_buffer_next_io_index_smb++;
			if (page_buffer_next_io_index_smb >= MAX_PAGE_BUFFER_SIZE_SMB)
				page_buffer_next_io_index_smb = 0;

			length--;
			sii = SCFS_I(page->mapping->host);
			cluster_number = PAGE_TO_CLUSTER_INDEX(page, sii);

			while (length-- > 0) {
				temp_page = page_buffer_smb[page_buffer_next_io_index_smb];
				temp_file = file_buffer_smb[page_buffer_next_io_index_smb];

				if ((temp_file == file) && (cluster_number == PAGE_TO_CLUSTER_INDEX(temp_page, sii))) {
					page_buffer[page_buffer_count++] = temp_page;
					page_buffer_next_io_index_smb++;
					if (page_buffer_next_io_index_smb >= MAX_PAGE_BUFFER_SIZE_SMB)
						page_buffer_next_io_index_smb = 0;
				} else break;
			}
			spin_unlock(&spinlock_smb);

			/* read first page */
			scfs_readpage(file, page);
			atomic_long_dec(&file->f_count);

			/* read related pages with cluster of first page*/
			for (i = 0; i < page_buffer_count; i++) {
				scfs_readpage(file, page_buffer[i]);
				atomic_long_dec(&file->f_count);
			}
		}
		else {
			*((int *)my_smb_task_status) = 0;
			spin_unlock(&spinlock_smb);
			schedule();
			*((int *)my_smb_task_status) = 1;
		}
	}

	return 0;
}

/**
 * scfs_readpages
 *
 * Parameters:
 * @file: upper file
 * @*mapping: address_space struct for the file
 * @*pages: list of pages to read in
 * @nr_pages: number of pages to read in
 *
 * Return:
 * SCFS_SUCCESS if success, otherwise if error
 *
 * Description:
 * - Asynchronously read pages for readahead. A scaling number of background threads
 *   will read & decompress them in a slightly deferred but parallelized manner.
 */
static int
scfs_readpages(struct file *file, struct address_space *mapping,
		struct list_head *pages, unsigned nr_pages)
{
	struct scfs_inode_info *sii = SCFS_I(file->f_mapping->host);
	int page_idx, page_idx_readahead = 1024, ret = 0;
	struct page *page;
	struct file *lower_file = NULL;
	loff_t i_size;
	int readahead_page = 0;

	i_size = i_size_read(&sii->vfs_inode);
	if (!i_size) {
		SCFS_PRINT("file %s: i_size is zero, "
			"flags 0x%x sii->clust_info_size %d\n",
			file->f_path.dentry->d_name.name, sii->flags,
			sii->cinfo_array_size);
		return 0;
	}

#ifdef SCFS_NOTIFY_RANDOM_READ
	lower_file = scfs_lower_file(file);
	if (!lower_file) {
		SCFS_PRINT_ERROR("file %s: lower file is null!\n",
		        file->f_path.dentry->d_name.name);
		return -EINVAL;
	}

	/* if the read request was random (enough), hint it to the lower file. 
	 * scfs_sequential_page_number is the tunable threshold.
	 * filemap.c will later on refer to this FMODE_RANDOM flag.
	*/
	spin_lock(&lower_file->f_lock);
	if (nr_pages > scfs_sequential_page_number)
		lower_file->f_mode &= ~FMODE_RANDOM;
	else
		lower_file->f_mode |= FMODE_RANDOM;
	spin_unlock(&lower_file->f_lock);
#endif

	/* pre-read lower file for scfs_readpages throughput gain */
#ifdef SCFS_PRELOAD_BOOTING_CLUSTER
	if (atomic_read(&pcb_read_count) < atomic_read(&scfs_lower_read_count) + 300 )
#endif
	{
		int cluster_idx = 0;
		pgoff_t start, end;
		struct scfs_cinfo cinfo;
		loff_t i_size = 0;
		lower_file = scfs_lower_file(file);

		page = list_entry(pages->prev, struct page, lru);
		SCFS_PRINT("%s<s> %d %d %d %d\n",file->f_path.dentry->d_name.name, page->index, nr_pages,
			atomic_read(&pcb_read_count), atomic_read(&scfs_lower_read_count));
		cluster_idx = page->index / (sii->cluster_size / PAGE_SIZE);
		if (IS_COMPRESSABLE(sii)) {
			ret = get_cluster_info(file, cluster_idx, &cinfo);
			if (ret) {
				SCFS_PRINT_ERROR("err in get_cluster_info, ret : %d,"
					"i_size %lld\n", ret, i_size);
				return ret;
			}

			if (!cinfo.size || cinfo.size > sii->cluster_size) {
				SCFS_PRINT_ERROR("file %s: cinfo is invalid, "
					"clust %u cinfo.size %u\n",
					file->f_path.dentry->d_name.name,
					cluster_idx, cinfo.size);
				return -EINVAL;
			}
			start = (pgoff_t)(cinfo.offset / PAGE_SIZE);
		} else {
			start = (pgoff_t)(cluster_idx * sii->cluster_size / PAGE_SIZE);
		}

		cluster_idx = (page->index + nr_pages - 1) / (sii->cluster_size / PAGE_SIZE);
		if (IS_COMPRESSABLE(sii)) {
			ret = get_cluster_info(file, cluster_idx, &cinfo);
			if (ret) {
				SCFS_PRINT_ERROR("err in get_cluster_info, ret : %d,"
					"i_size %lld\n", ret, i_size);
				return ret;
			}

			if (!cinfo.size || cinfo.size > sii->cluster_size) {
				SCFS_PRINT_ERROR("file %s: cinfo is invalid, "
					"clust %u cinfo.size %u\n",
					file->f_path.dentry->d_name.name,
					cluster_idx, cinfo.size);
				return -EINVAL;
			}

			end = (pgoff_t)((cinfo.offset + cinfo.size -1) / PAGE_SIZE);
		} else {
			end = (pgoff_t)(((cluster_idx + 1) * sii->cluster_size - 1) / PAGE_SIZE);

			/* check upper inode size */
			i_size = i_size_read(&sii->vfs_inode);
			if (end > (i_size / PAGE_SIZE))
				end = (i_size / PAGE_SIZE);
		}

		force_page_cache_readahead(lower_file->f_mapping, lower_file, start, (unsigned long)(end - start +1));
	}

	for (page_idx = 0; page_idx < nr_pages; page_idx++) {
		page = list_entry(pages->prev, struct page, lru);
		list_del(&page->lru);

		if (PageReadahead(page))
			page_idx_readahead = page_idx;

		ret = add_to_page_cache_lru(page, mapping,
				      page->index, GFP_KERNEL);
		if (ret) {
			SCFS_PRINT("adding to page cache failed, "
				"page %x page->idx %d ret %d\n",
				page, page->index, ret);
			page_cache_release(page);
			continue;
		}

		/* memory buffer is full or synchronous read request - call scfs_readpage to read now */
		if (page_buffer_next_filling_index_smb ==
				MAX_PAGE_BUFFER_SIZE_SMB || page_idx < page_idx_readahead) {
			scfs_readpage(file, page);
		} else {
			spin_lock(&spinlock_smb);

			/* queue is not full so add the page into the queue. also, here we increase 
				file->f_count to protect the file structs from multi-threaded accesses */
			atomic_long_inc(&file->f_count);
			page_buffer_smb[page_buffer_next_filling_index_smb] = page;
			file_buffer_smb[page_buffer_next_filling_index_smb++] = file;

			/* check whether page buffer is full and set page buffer full if needed */
			if (((page_buffer_next_filling_index_smb == MAX_PAGE_BUFFER_SIZE_SMB) &&
				page_buffer_next_io_index_smb == 0) ||
				(page_buffer_next_filling_index_smb == page_buffer_next_io_index_smb))
				page_buffer_next_filling_index_smb = MAX_PAGE_BUFFER_SIZE_SMB;
			else if (page_buffer_next_filling_index_smb == MAX_PAGE_BUFFER_SIZE_SMB)
				page_buffer_next_filling_index_smb = 0;
			spin_unlock(&spinlock_smb);
			++readahead_page;
		}

		page_cache_release(page);
	}

	if (readahead_page > 0) wakeup_smb_thread();
	SCFS_PRINT("<e>\n");

	return 0;
}
#endif

/**
 * scfs_write_begin
 * @file: The scfs file
 * @mapping: The file's address_space
 * @pos: The write starting position, in bytes
 * @len: Bytes to write in this page
 * @flags: Various flags
 * @pagep: Pointer to return the page
 * @fsdata: Pointer to return fs-specific data (unused)
 *
 * Description:
 * - Prepare a page write, which may require a cluster read and re-compression
 *   for partially written clusters at the end of a given file. Cluster info list,
 *   as well as the cluster buffer for the cluster to be written, shall be prepped
 *   accordingly.
 * - Currently SCFS doesn't support random writes, so this function will return 
 *   -EINVAL if pos < i_size.
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

	if (IS_COMPRESSABLE(sii)) {
		struct cinfo_entry *info_entry;
		ret = scfs_get_comp_buffer(sii);
		if (ret)
			goto out;

		mutex_lock(&sii->cinfo_list_mutex);
		if (list_empty(&sii->cinfo_list)) {
			/* first cluster write, probably, since create or open */
			info_entry = scfs_alloc_cinfo_entry(PAGE_TO_CLUSTER_INDEX(page,sii), sii);
			if (!info_entry) {
				mutex_unlock(&sii->cinfo_list_mutex);
				SCFS_PRINT_ERROR("Cannot alloc new cluster_info.");
				ret = -ENOMEM;
				goto out;
			}

			if (PAGE_TO_CLUSTER_INDEX(page,sii) == 0)
				info_entry->cinfo.offset = 0;

			/* lower cluster already exists so we must be writing on the last cluster */
			if (CLUSTER_EXISTS(sii, PAGE_TO_CLUSTER_INDEX(page,sii))) {
				mutex_unlock(&sii->cinfo_list_mutex);
				ret = get_cluster_info(file, PAGE_TO_CLUSTER_INDEX(page,sii),
						&clust_info);
				mutex_lock(&sii->cinfo_list_mutex);
				if (ret) {
					mutex_unlock(&sii->cinfo_list_mutex);
					SCFS_PRINT_ERROR("page is in file, " \
						"but cannot get cluster info.");
					goto out;
				}
				info_entry->cinfo.offset = clust_info.offset;
				ret = scfs_get_cluster_from_lower(sii, lower_file, clust_info);
				if (ret) {
					mutex_unlock(&sii->cinfo_list_mutex);
					SCFS_PRINT_ERROR("Fail to get lower data.");
					goto out;
				}				

				if (!PageUptodate(page))
					sync_page_from_buffer(page, sii->cluster_buffer.u_buffer);
				
			} else if (PAGE_TO_CLUSTER_INDEX(page,sii) > 0 
				&& CLUSTER_EXISTS(sii, PAGE_TO_CLUSTER_INDEX(page,sii) - 1)) {
				/* we must be adding a new cluster with this page write */
				ret = get_cluster_info(file, PAGE_TO_CLUSTER_INDEX(page,sii) - 1,
						&clust_info);
				if (ret) {
					mutex_unlock(&sii->cinfo_list_mutex);
					SCFS_PRINT_ERROR("page is in file, but cannot get cluster info.");
					goto out;
				}

				info_entry->cinfo.offset = clust_info.offset+clust_info.size;
				if (clust_info.size%SCFS_CLUSTER_ALIGN_BYTE) {
					info_entry->cinfo.offset += 
					(SCFS_CLUSTER_ALIGN_BYTE - (clust_info.size%SCFS_CLUSTER_ALIGN_BYTE));
				}
			}
		} else {
			/* cinfo list is not empty, cluster writes must have happened */
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
				goto out;
			}

			if (new_list) {
				new_list->cinfo.offset =
					info_entry->cinfo.offset +
					info_entry->cinfo.size;
				if(info_entry->cinfo.size % SCFS_CLUSTER_ALIGN_BYTE)
					new_list->cinfo.offset += 
					(SCFS_CLUSTER_ALIGN_BYTE -
					(info_entry->cinfo.size % SCFS_CLUSTER_ALIGN_BYTE));
			}
		}		
		mutex_unlock(&sii->cinfo_list_mutex);
	} else {
		/* for uncompressable files, we need at least one cinfo_entry in the list
			because write_meta depends on it, when determining whether to
			append with scfs_meta. */
		if (list_empty(&sii->cinfo_list)) {
			struct cinfo_entry *info_entry = NULL;
			
			info_entry = scfs_alloc_cinfo_entry(PAGE_TO_CLUSTER_INDEX(page,sii),
					sii);
			sii->cluster_buffer.original_size = 0;
		}
		if (!PageUptodate(page)) {
			unsigned pos_in_page = pos & (PAGE_CACHE_SIZE - 1);
			//TODO: read existing page data from lower if page is not up-to-date
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

	return ret;
}

extern struct kmem_cache *scfs_info_entry_list;

/**
 * scfs_write_end
 * @file: The scfs file
 * @mapping: The file's address_space
 * @pos: The write starting position, in bytes
 * @len: Bytes to write in this page
 * @copied: Bytes actually written
 * @page: Page to be written
 * @fsdata: Fs-specific data (unused)
 *
 * Description:
 * - Finishes page write via scfs_lower_write. If the lower folder/partition
 *   is actually out of space and thus unable to satisfy the write request,
 *   write will fail by returning -ENOSPC.
 * - If a cluster is ready for write and compressable, then we compress it
 *   before writing it.
 * - Note that this will only finish writing the data given from the user, and
 *   SCFS metadata will be kept in-memory until scfs_put_lower_file (via fput())
 *   writes it down in a deferred manner.
 *
 */
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
	struct cinfo_entry *info_entry = NULL;
 
	SCFS_PRINT("f:%s pos:%lld, len:%d s:%lld i:%d\n",
			file->f_path.dentry->d_name.name, pos, len, 
			i_size_read(&sii->vfs_inode), page->index);

	lower_file = scfs_lower_file(file);
	if (!lower_file) {
		SCFS_PRINT_ERROR("lower file is null!\n");
		ret = -EINVAL;
		goto out;
	}

	if (IS_COMPRESSABLE(sii)) {
 		ret = scfs_get_comp_buffer(sii);
		if (ret)
			goto out;

		sii->cluster_buffer.original_size += len; 

		atomic64_add(len, &sb_info->current_data_size);
		ret = scfs_check_space(sb_info, file->f_dentry);
		if(ret < 0) {
			SCFS_PRINT_ERROR("No more space in lower-storage\n");
			goto out;
		}

		sync_page_to_buffer(page, sii->cluster_buffer.u_buffer); 
 		if (PGOFF_IN_CLUSTER(page, sii) + 1 == sii->cluster_size / PAGE_CACHE_SIZE &&
				to == PAGE_CACHE_SIZE) {

			mutex_lock(&sii->cinfo_list_mutex);

			if (list_empty(&sii->cinfo_list)) {
				mutex_lock(&sii->cinfo_list_mutex);
				SCFS_PRINT_ERROR("cinfo list is empty\n");
				ret = -EINVAL;
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
				goto out;
			}

			if (info_entry->cinfo.size >=
					sii->cluster_buffer.original_size *
					sb_info->options.comp_threshold / 100)
				info_entry->cinfo.size = sii->cluster_buffer.original_size;
	        	
			if (info_entry->cinfo.size % SCFS_CLUSTER_ALIGN_BYTE)
				info_entry->pad = SCFS_CLUSTER_ALIGN_BYTE -
					(info_entry->cinfo.size % SCFS_CLUSTER_ALIGN_BYTE);
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
					goto out;
				}

				if (!sii->compressed)
					sii->compressed = 1;
		    	} else {
				info_entry->cinfo.size = sii->cluster_buffer.original_size;
				info_entry->pad = 0;

				mutex_unlock(&sii->cinfo_list_mutex);
				ret = scfs_lower_write(lower_file, sii->cluster_buffer.u_buffer,
					sii->cluster_buffer.original_size, &lower_pos); 
				if (ret < 0) {
					SCFS_PRINT_ERROR("write fail. ret = %d, size=%d\n",
						ret, sii->cluster_buffer.original_size);
					goto out;
				}
	    		}	    	
			atomic64_sub(sii->cluster_buffer.original_size,&sb_info->current_data_size);
			sii->cluster_buffer.original_size = 0;
 		}
		ret = len;
	} else {
		char *source_addr;

		lower_pos = pos;
		source_addr = (char*)kmap(page);
		atomic64_add(len, &sb_info->current_data_size);
		ret = scfs_check_space(sb_info, file->f_dentry);
		if(ret < 0) {
			SCFS_PRINT_ERROR("No more space in lower-storage\n");
			goto out;
		}
		atomic64_sub(len, &sb_info->current_data_size);
		ret = scfs_lower_write(lower_file, source_addr+from, len, &lower_pos);
		if (ret < 0) {
			SCFS_PRINT_ERROR("write fail. ret = %d, size=%d\n", ret, len);
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
	
	return ret;
}

/**************************************/
/* address_space_operations structure */
/**************************************/

const struct address_space_operations scfs_aops = {
	.readpage = scfs_readpage,
#ifdef SCFS_ASYNC_READ_PAGES
	.readpages = scfs_readpages,
#endif
	.write_begin = scfs_write_begin,
	.write_end = scfs_write_end,
};
