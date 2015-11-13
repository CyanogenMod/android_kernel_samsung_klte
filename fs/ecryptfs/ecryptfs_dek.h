#ifndef ECRYPTFS_DEK_H
#define ECRYPTFS_DEK_H

#include <linux/fs.h>
#include <sdp/dek_common.h>
#include "ecryptfs_kernel.h"

#define ECRYPTFS_DEK_XATTR_NAME "user.sdp"

#define ECRYPTFS_DEK_DEBUG 0

#define O_SDP    0x10000000

int ecryptfs_super_block_get_userid(struct super_block *sb);
int ecryptfs_is_valid_userid(int userid);
int ecryptfs_is_persona_locked(int userid);
int ecryptfs_get_sdp_dek(unsigned char *sig, int *sig_len, struct ecryptfs_crypt_stat *crypt_stat);
int ecryptfs_sdp_convert_dek(struct dentry *dentry);
int ecryptfs_parse_xattr_is_sensitive(const void *data, int len);

int write_dek_packet(char *dest, struct ecryptfs_crypt_stat *crypt_stat, size_t *written);
int parse_dek_packet(char *data, struct ecryptfs_crypt_stat *crypt_stat, size_t *packet_size);

long ecryptfs_do_sdp_ioctl(struct file *file, unsigned int cmd, unsigned long arg);


/*
	ioctl for SDP
*/

typedef struct _dek_arg_sdp_info {
	int sdp_enabled;	
	int is_sensitive;
	unsigned int type;
}dek_arg_get_sdp_info;

typedef struct _dek_arg_get_fek {
	int persona_id;
	dek_t dek;
}dek_arg_get_fek;

typedef struct _dek_arg_get_efek {
	int persona_id;
	dek_t dek;
}dek_arg_get_efek;

typedef struct _dek_arg_set_efek {
	int persona_id;
	dek_t dek;
}dek_arg_set_efek;

typedef struct _dek_arg_set_sensitive {
	int persona_id;
}dek_arg_set_sensitive;

#define ECRYPTFS_IOCTL_GET_SDP_INFO     _IOR('l', 0x11, __u32)
#define ECRYPTFS_IOCTL_GET_FEK          _IOR('l', 0x12, __u32)
#define ECRYPTFS_IOCTL_GET_EFEK         _IOR('l', 0x13, __u32)
#define ECRYPTFS_IOCTL_SET_EFEK         _IOW('l', 0x14, __u32)
#define ECRYPTFS_IOCTL_SET_SENSITIVE    _IOW('l', 0x15, __u32)

#endif /* #ifndef ECRYPTFS_DEK_H */
