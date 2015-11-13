/*
 * fs/scfs/kthread.c
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

#include <linux/freezer.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include "scfs.h"

static struct scfs_kthread_ctl {
#define SCFS_KTHREAD_ZOMBIE 0x00000001
	u32 flags;
	struct mutex mux;
	struct list_head req_list;
	wait_queue_head_t wait;
} scfs_kthread_ctl;

static struct task_struct *scfs_kthread;

static int scfs_threadfn(void *ignored)
{
	set_freezable();
	while (1)  {
		struct scfs_open_req *req;

		wait_event_freezable(
			scfs_kthread_ctl.wait,
			(!list_empty(&scfs_kthread_ctl.req_list)
			 || kthread_should_stop()));
		mutex_lock(&scfs_kthread_ctl.mux);
		if (scfs_kthread_ctl.flags & SCFS_KTHREAD_ZOMBIE) {
			mutex_unlock(&scfs_kthread_ctl.mux);
			goto out;
		}
		while (!list_empty(&scfs_kthread_ctl.req_list)) {
			req = list_first_entry(&scfs_kthread_ctl.req_list,
					       struct scfs_open_req,
					       kthread_ctl_list);
			mutex_lock(&req->mux);
			list_del(&req->kthread_ctl_list);
			if (!(req->flags & SCFS_REQ_ZOMBIE)) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
				const struct path path = {req->lower_mnt, req->lower_dentry};
#endif
				dget(req->lower_dentry);
				mntget(req->lower_mnt);
				(*req->lower_file) = dentry_open(
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
					&path,
#else
					req->lower_dentry, req->lower_mnt,
#endif
					(O_RDWR | O_LARGEFILE), current_cred());
				req->flags |= SCFS_REQ_PROCESSED;
			}
			wake_up(&req->wait);
			mutex_unlock(&req->mux);
		}
		mutex_unlock(&scfs_kthread_ctl.mux);
	}
out:
	return 0;
}

int __init scfs_init_kthread(void)
{
	int ret = 0;

	mutex_init(&scfs_kthread_ctl.mux);
	init_waitqueue_head(&scfs_kthread_ctl.wait);
	INIT_LIST_HEAD(&scfs_kthread_ctl.req_list);
	scfs_kthread = kthread_run(&scfs_threadfn, NULL,
				       "scfs-kthread");
	if (IS_ERR(scfs_kthread)) {
		ret = PTR_ERR(scfs_kthread);
		SCFS_PRINT_ERROR("%s: Failed to create kernel thread; "
			"ret = [%d]\n",ret);
	}
	return ret;
}

void scfs_destroy_kthread(void)
{
	struct scfs_open_req *req;

	mutex_lock(&scfs_kthread_ctl.mux);
	scfs_kthread_ctl.flags |= SCFS_KTHREAD_ZOMBIE;
	list_for_each_entry(req, &scfs_kthread_ctl.req_list,
			    kthread_ctl_list) {
		mutex_lock(&req->mux);
		req->flags |= SCFS_REQ_ZOMBIE;
		wake_up(&req->wait);
		mutex_unlock(&req->mux);
	}
	mutex_unlock(&scfs_kthread_ctl.mux);
	kthread_stop(scfs_kthread);
	wake_up(&scfs_kthread_ctl.wait);
}

int scfs_privileged_open(struct file **lower_file,
			     struct dentry *lower_dentry,
			     struct vfsmount *lower_mnt,
			     const struct cred *cred)
{
	struct scfs_open_req *req;
	int flags = O_LARGEFILE;
	int ret = 0;
#if SCFS_PROFILE_MEM
//	struct scfs_sb_info *sbi;
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	const struct path path = {lower_mnt, lower_dentry};
#else
	dget(lower_dentry);
	mntget(lower_mnt);
#endif
	flags |= IS_RDONLY(lower_dentry->d_inode) ? O_RDONLY : O_RDWR;
	(*lower_file) = dentry_open(
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
				&path,
#else
				lower_dentry, lower_mnt,
#endif
				flags, cred);
	if (!IS_ERR(*lower_file))
		goto out;
	if ((flags & O_ACCMODE) == O_RDONLY) {
		ret = PTR_ERR((*lower_file));
		goto out;
	}
	req = kmem_cache_alloc(scfs_open_req_cache, GFP_KERNEL);
	if (!req) {
		ret = -ENOMEM;
		goto out;
	}
#if SCFS_PROFILE_MEM
//	atomic_add(sizeof(struct scfs_open_req_cache), &sbi->kmcache_size);
#endif

	mutex_init(&req->mux);
	req->lower_file = lower_file;
	req->lower_dentry = lower_dentry;
	req->lower_mnt = lower_mnt;
	init_waitqueue_head(&req->wait);
	req->flags = 0;
	mutex_lock(&scfs_kthread_ctl.mux);
	if (scfs_kthread_ctl.flags & SCFS_KTHREAD_ZOMBIE) {
		ret = -EIO;
		mutex_unlock(&scfs_kthread_ctl.mux);
		SCFS_PRINT_ERROR("We are in the middle of shutting down; "
		       "aborting privileged request to open lower file\n");
		goto out_free;
	}
	list_add_tail(&req->kthread_ctl_list, &scfs_kthread_ctl.req_list);
	mutex_unlock(&scfs_kthread_ctl.mux);
	wake_up(&scfs_kthread_ctl.wait);
	wait_event(req->wait, (req->flags != 0));
	mutex_lock(&req->mux);
	BUG_ON(req->flags == 0);
	if (req->flags & SCFS_REQ_DROPPED
	    || req->flags & SCFS_REQ_ZOMBIE) {
		ret = -EIO;
		SCFS_PRINT_ERROR( "Privileged open request dropped\n");
		goto out_unlock;
	}
	if (IS_ERR(*req->lower_file))
		ret = PTR_ERR(*req->lower_file);
out_unlock:
	mutex_unlock(&req->mux);
out_free:
	kmem_cache_free(scfs_open_req_cache, req);
#if SCFS_PROFILE_MEM
//	atomic_sub(sizeof(struct scfs_open_req), &sbi->kmcache_size);
#endif
out:
	return ret;
}
