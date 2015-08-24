/*
 *  scfs.h
 */

#ifndef SCFS_HEADER_H
#define SCFS_HEADER_H

#include <linux/file.h>
#include <linux/fs_stack.h>
#include <linux/mount.h>
#include <linux/namei.h>
#include <linux/pagemap.h>
#include <linux/page-flags.h>
#include <linux/slab.h>
#include <linux/buffer_head.h>
#include <linux/backing-dev.h>
#include <linux/vmalloc.h>
#include <linux/time.h>
#include <linux/mempool.h>
#include <linux/version.h>


extern const struct address_space_operations scfs_aops;
extern const struct inode_operations scfs_symlink_iops;
extern const struct inode_operations scfs_dir_iops;
extern const struct inode_operations scfs_file_iops;
extern const struct file_operations scfs_dir_fops;
extern const struct file_operations scfs_file_fops;
extern const struct super_operations scfs_sops;
extern const struct dentry_operations scfs_dops;

extern struct kmem_cache *scfs_file_info_cache;
extern struct kmem_cache *scfs_dentry_info_cache;
extern struct kmem_cache *scfs_open_req_cache;
extern struct kmem_cache *scfs_inode_info_cache;
extern struct kmem_cache *scfs_sb_info_cache;
extern struct kmem_cache *scfs_header_cache;
extern struct kmem_cache *scfs_xattr_cache;


/************************/
/* configurable options */
/************************/

//#define SCFS_DEBUG 			1
#define SCFS_PROFILE_MEM		0
#define SCFS_PROFILE_DURATION		0
#define SCFS_PROFILE 			0
 
/*******************/
/* profiling stuff */
/*******************/
#if SCFS_PROFILE_DURATION
//static struct timeval start_time1, start_time2, start_time3;
//static struct timeval end_time1, end_time2, end_time3;
/*static int scfs_read_time1, scfs_read_time2, scfs_read_time3, scfs_read_time4,
	scfs_read_time5, scfs_read_time6, scfs_read_time7, scfs_read_time8,
	scfs_read_time9, scfs_read_time10, scfs_read_time11;*/
#endif


/*****************************************/
/* size configs, flags, error code, etc. */
/*****************************************/

/* magic values for sanity checking */
#define SCFS_SUPER_MAGIC	0x53305955
#define SCFS_MAGIC		SCFS_SUPER_MAGIC
/* cluster-related */
#define SCFS_CLUSTER_ALIGN	4
#define SCFS_CLUSTER_SIZE_DEF	(16 * 1024)
#define SCFS_CLUSTER_SIZE_MAX	(16 * 1024)
#define SCFS_CLUSTER_SIZE_MIN	(4 * 1024)
/* file status flags */
#define SCFS_DATA_RAW		0x00000001
#define SCFS_DATA_COMPRESS	0x00000002
#define SCFS_META_XATTR		0x00000004

#define SCFS_INVALID_META	0x00000010
/* error return code */
#define SCFS_ERR_OUT_OF_MEMORY	(-ENOMEM)
#define SCFS_ERR_IO		(-EIO)
#define SCFS_ERR_INVALID	(-EINVAL)
#define SCFS_ERR_NO_FILE	(-ENOENT)
#define SCFS_ERR_PERMISSION	(-EACCES)
#define SCFS_ERR_EXEC		(-ENOEXEC)
#define SCFS_CONTINUE		0x2
#define SCFS_ERR_CONTINUE	0x1
#define SCFS_SUCCESS		0x0
/* mount option flags */
#define SCFS_MOUNT_XATTR_META 	0x00000001
/* buffer sizes */
#define SCFS_MEMPOOL_COUNT	32 //TODO may need to tune it down later
#define SCFS_MEMPOOL_ORDER	3
#define SCFS_MEMPOOL_SIZE	(1 << SCFS_MEMPOOL_ORDER << PAGE_SHIFT)
#define SCFS_MEMPOOL_SIZE_TOTAL	(SCFS_MEMPOOL_COUNT * SCFS_MEMPOOL_SIZE)
/* misc */
#define SCFS_IO_MAX_RETRY	10
#define IS_POW2(n)		(n != 0 && ((n & (n - 1)) == 0))

 
/*******************************/
/* compression & cluster stuff */
/*******************************/

enum comp_type {
    LZO,
    BZIP2,
    ZLIB,
    FASTLZO,
    TOTAL_TYPES,
};
 


struct scfs_cinfo
{
	unsigned int	offset; // byte offset of the start of this cluster
	unsigned int	size;	// byte length of the cluster
};

/* footer = scfs_cinfo * n_cluster + comp_footer (@ end of file) */
struct comp_footer
{
	int footer_size; //TODO rename
	int cluster_size;
	long long original_file_size;
	enum comp_type comp_type;
	int magic;
};

/***************************************/
/* fs-wide structs (mount, inode, etc. */
/***************************************/

struct scfs_mount_options
{
	int flags;
	int cluster_size;
	int comp_threshold;
	enum comp_type comp_type;
};

struct scfs_sb_info
{
 	struct super_block *lower_sb;
	struct scfs_mount_options options;
	struct backing_dev_info bdi;
	mempool_t *mempool;
#if SCFS_PROFILE_MEM
	atomic_t mempool_size;
	atomic_t kmalloc_size;
	atomic_t vmalloc_size;
	atomic_t kmcache_size;
#endif
#if SCFS_PROFILE_DURATION
	atomic_t time_1;
	atomic_t time_2;
	atomic_t time_3;
	atomic_t time_4;
	atomic_t time_5;
	atomic_t time_6;
	atomic_t time_7;
	atomic_t time_8;
	atomic_t time_9;
	atomic_t time_10;
	atomic_t time_11;
	atomic_t time_12;
#endif
};

struct cinfo_entry
{
	struct list_head entry;
	struct scfs_cinfo cinfo;
	unsigned int current_cluster_idx;
	int pad;
};

struct scfs_cluster_buffer
{
	struct page *u_page;
	struct page *c_page;
	char *u_buffer;
	char *c_buffer;
	size_t original_size;
};

struct scfs_inode_info 
{
	int flags;
	struct mutex lower_file_mutex;
	struct mutex cinfo_list_mutex;
	atomic_t lower_file_count;
	struct file *lower_file;
	struct inode *lower_inode; // is it useful?
	void *cinfo_array;
	int cinfo_array_size;
	int cluster_size;
	enum comp_type comp_type;
	size_t upper_file_size;
 	struct scfs_cluster_buffer cluster_buffer;
 	struct list_head cinfo_list; // for written cluster. This will be written at close
	unsigned char compressd;
 	struct inode vfs_inode;
	/* DO NOT ADD FIELDS BELOW vfs_inode */
};

struct scfs_file_info
{
	struct file *lower_file;
};

struct scfs_dentry_info
{
	spinlock_t lock;
	struct path lower_path;
};

/* this structure may be useless someday */
struct scfs_open_req {
#define SCFS_REQ_PROCESSED 0x00000001
#define SCFS_REQ_DROPPED   0x00000002
#define SCFS_REQ_ZOMBIE    0x00000004
	u32 flags;
	struct file **lower_file;
	struct dentry *lower_dentry;
	struct vfsmount *lower_mnt;
	wait_queue_head_t wait;
	struct mutex mux;
	struct list_head kthread_ctl_list;
};

// shyoon - cluster read buffer cache
#define MAX_BUFFER_CACHE 4
struct read_buffer_cache {
	struct page *u_page;
	struct page *c_page;
	int inode_number;
	int cluster_number;
	int is_compressed;
	atomic_t is_used;
};

/**************************/
/* macro helper functions */
/**************************/

#define SCFS_S(sb)	((struct scfs_sb_info *)(sb->s_fs_info))
#define SCFS_I(inode)	(container_of(inode, struct scfs_inode_info, vfs_inode))
#define SCFS_F(file)	((struct scfs_file_info *)(file->private_data))
#define SCFS_D(dent)	((struct scfs_dentry_info *)(dent->d_fsdata))
//#define SCFS_UCB(buffer)	((char *)(buffer->cluster_buffer))
//#define SCFS_CB(buffer)	((char *)(((unsigned int)buffer->cluster_buffer) >> 1))

#define CF_SIZE			sizeof(struct comp_footer)
#define CMETA_SIZE(sii)		(sii->cinfo_array_size + CF_SIZE)
#define IS_COMPRESSED(sii)	(sii->flags & SCFS_DATA_COMPRESS)
#define IS_INVALID_META(sii)	(sii->flags & SCFS_INVALID_META)	
#define make_meta_invalid(sii)	(sii->flags |= SCFS_INVALID_META)
#define clear_meta_invalid(sii)	(sii->flags &= ~SCFS_INVALID_META)

#define CLUSTER_COUNT(sii) \
	DIV_ROUND_UP_ULL(i_size_read(&sii->vfs_inode), sii->cluster_size)

#define PGOFF_IN_CLUSTER(page, sii) \
	(page->index % (sii->cluster_size / PAGE_SIZE))

#define CLUSTER_EXISTS(sii, idx) \
	(sii->cinfo_array_size != 0 && \
	(idx+1) * sizeof(struct scfs_cinfo) <= sii->cinfo_array_size)

#define PAGE_TO_CLUSTER_INDEX(page, sii) \
	((page->index) / (sii->cluster_size / PAGE_SIZE))

#define ASSERT(x) { \
	if (!(x)) { \
		printk(KERN_ERR "assertion %s failed: file %s line %d\n", #x,\
			__FILE__, __LINE__);\
		BUG(); \
	}\
}

#if (defined(SCFS_DEBUG) && SCFS_DEBUG)
#define SCFS_PRINT(fmt, arg...) \
        scfs_printk(KERN_INFO "[SCFS] %s: " fmt, __func__, ## arg)

#define SCFS_PRINT_WARN(fmt, arg...) \
        scfs_printk(KERN_WARNING "[SCFS] WARN %s: " fmt, __func__, ## arg)

#define SCFS_DEBUG_START	SCFS_PRINT("_start_\n")
#define SCFS_DEBUG_END		SCFS_PRINT("_end_\n")
#else
#define SCFS_PRINT(fmt, arg...)

#define SCFS_PRINT_WARN(fmt, arg...)

#define SCFS_DEBUG_START
#define SCFS_DEBUG_END
#endif

#define SCFS_PRINT_ERROR(fmt, arg...) \
        scfs_printk(KERN_ERR "[SCFS] ERROR %s(%d): " fmt, __func__, __LINE__, ## arg)

#define SCFS_PRINT_ALWAYS(fmt, arg...) \
        scfs_printk(KERN_ERR "[SCFS] %s(%d): " fmt, __func__,__LINE__, ## arg)

#define list_to_page(head) (list_entry((head)->prev, struct page, lru))

/********************/
/* inline functions */
/********************/
#if (defined(SCFS_PROFILE) && SCFS_PROFILE)
//static struct timeval start_time;
//static struct timeval end_time;

static inline void
scfs_start_profile(struct timeval *start_time)
{	
	do_gettimeofday(start_time);
}

static inline void
scfs_end_profile(struct timeval *end_time)
{
	do_gettimeofday(end_time);
}

#define SCFS_START_PROFILE(start_time) \
	scfs_start_profile(start_time);

#define SCFS_END_PROFILE(start, end, target) \
	scfs_end_profile(end); \
	*target += timeval_compare(end, start);
	
//	printk(KERN_ERR "%s in %s(%d): %lld.%06lld seconds elapsed\n",fmt, __FUNCTION__, __LINE__ 
//			, (long long)(end_time.tv_sec - start_time.tv_sec), (long long)(end_time.tv_usec - start_time.tv_usec));

#else
#define SCFS_START_PROFILE() 
#define SCFS_END_PROFILE(fmt)
static inline void
scfs_start_profile(void)
{
}
static inline void
scfs_end_profile(void)
{
}
#endif

static inline struct dentry *
scfs_lower_dentry(struct dentry *dentry)
{
	return ((struct scfs_dentry_info *)dentry->d_fsdata)->lower_path.dentry;
}

static inline void
scfs_set_lower_dentry(struct dentry *dentry, struct dentry *lower_dentry)
{
	((struct scfs_dentry_info*)dentry->d_fsdata)->lower_path.dentry = lower_dentry;
}

static inline struct inode *scfs_lower_inode(const struct inode *i)
{
	return SCFS_I(i)->lower_inode;
}

static inline void scfs_set_lower_inode(struct inode *i, struct inode *val)
{
	SCFS_I(i)->lower_inode = val;
}

static inline struct file *scfs_lower_file(const struct file *f)
{
	return SCFS_F(f)->lower_file;
}

static inline void scfs_set_lower_file(struct file *f, struct file *val)
{
	SCFS_F(f)->lower_file = val;
}

static inline struct super_block *
scfs_lower_super(const struct super_block *sb)
{
	return SCFS_S(sb)->lower_sb;
}

static inline void 
scfs_set_lower_super(struct super_block *sb, struct super_block *val)
{
	SCFS_S(sb)->lower_sb = val;
}

static inline struct vfsmount *
scfs_dentry_to_lower_mnt(struct dentry *dentry)
{
	return ((struct scfs_dentry_info *)dentry->d_fsdata)->lower_path.mnt;
}

static inline void 
scfs_set_dentry_lower_mnt(struct dentry *dentry, struct vfsmount *lower_mnt)
{
	((struct scfs_dentry_info *)dentry->d_fsdata)->lower_path.mnt = lower_mnt;
}


/***********************/
/* function prototypes */
/***********************/

void scfs_printk(const char *fmt, ...);

int __init scfs_init_kthread(void);

void scfs_destroy_kthread(void);

int scfs_init_kmem_caches(void);

void scfs_free_kmem_caches(void);

int scfs_privileged_open(struct file **lower_file,
			     struct dentry *lower_dentry,
			     struct vfsmount *lower_mnt,
			     const struct cred *cred);

int
scfs_parse_options(struct scfs_sb_info *sbi, char *options);

struct inode *
scfs_get_inode(struct inode *lower_inode, struct super_block *sb);

void
copy_mount_flags_to_inode_flags(struct inode *inode, 
					struct super_block *sb);

int
scfs_get_lower_file(struct dentry *dentry, struct inode *inode);

void
scfs_put_lower_file(struct inode *inode);

int 
get_cluster_info(struct file *file, int cluster_n, struct scfs_cinfo *target);

int
get_cluster_info_from_list(struct inode *inode, int cluster_n,
		struct scfs_cinfo *target);

int
scfs_truncate(struct dentry *dentry, loff_t size);

int
scfs_read_cluster(struct file *file, struct page *page,
	char *buf_c, char **buf_u, int *compressed);

int
scfs_decompress(enum comp_type algo, char *buf_c, char *buf_u, int len, int *actual);

int
scfs_compress(enum comp_type algo, char *buf_c, char *buf_u, int len, int *actual);

struct page *scfs_alloc_mempool_buffer(struct scfs_sb_info *sbi);

void scfs_free_mempool_buffer(struct page *p, struct scfs_sb_info *sbi);

struct scfs_cluster_buffer *
scfs_get_cluster_buffer(struct page *page, struct scfs_inode_info *sii, struct file *file);

int
scfs_get_comp_buffer(struct scfs_inode_info *sii);

struct scfs_cluster_buffer *
scfs_alloc_cluster_buffer(unsigned int cluster_idx, struct scfs_inode_info *sii);

int
scfs_privileged_open(struct file **lower_file, struct dentry *lower_dentry,
			struct vfsmount *lower_mnt, const struct cred *cred);

void
sync_page_to_buffer(struct page *page, char *buffer);

void
sync_page_from_buffer(struct page *page, char *buffer);

int
scfs_check_ready_to_comp(struct scfs_cluster_buffer *cluster_buffer);

int
scfs_check_ready_to_write(struct scfs_cluster_buffer *cluster_buffer, struct scfs_inode_info *sii);

void 
scfs_free_cluster_buffer(struct scfs_cluster_buffer *cluster_buffer);

unsigned int 
scfs_get_lower_offset(unsigned int cluster_index, struct scfs_inode_info *sii);

int
scfs_get_cluster_from_lower(struct scfs_inode_info *sii, struct file *lower_file
 	, struct scfs_cinfo clust_info);

struct cinfo_entry *scfs_alloc_cinfo_entry(unsigned int cluster_index,
	struct scfs_inode_info *sii);

int 
scfs_write_pending_cluster_buffer(struct scfs_cluster_buffer *cluster_buffer, struct file *lower_file, struct scfs_inode_info *sii);

int 
scfs_write_meta(struct scfs_inode_info *sii);

ssize_t
scfs_getxattr_lower(struct dentry *lower_dentry, const char *name,
			void *value, size_t size);

int scfs_footer_read(struct dentry *dentry, struct inode *inode);

int scfs_reload_meta(struct file *file);
int scfs_initialize_file(struct dentry *scfs_dentry, struct inode *scfs_inode);
ssize_t scfs_lower_read(struct file *file, char *buf, size_t count, loff_t *pos);
ssize_t scfs_lower_write(struct file *file, char *buf, size_t count, loff_t *pos);

#endif //SCFS_HEADER_H
