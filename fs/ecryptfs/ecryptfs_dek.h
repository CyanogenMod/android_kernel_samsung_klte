#ifndef ECRYPTFS_DEK_H
#define ECRYPTFS_DEK_H

#include <linux/fs.h>
#include <dek/dek.h>
#include "ecryptfs_kernel.h"

#define ECRYPTFS_DEK_XATTR_NAME "user.sdp"

#define ECRYPTFS_DEK_DEBUG 0

int ecryptfs_super_block_get_sdp_id(struct super_block *sb);
int ecryptfs_is_valid_sdpid(int sdp_id);
int ecryptfs_get_encrypt_key(unsigned char *sig, int *sig_len, struct ecryptfs_crypt_stat *crypt_stat);
int ecryptfs_get_decrypt_key(unsigned char *sig, int *sig_len, struct ecryptfs_crypt_stat *crypt_stat);
int ecryptfs_encrypt_and_replace_sdp_dek(struct dentry *dentry, int is_sensitive);
int ecryptfs_parse_xattr_is_sensitive(const void *data, int len);
int ecryptfs_encrypt_dek(struct ecryptfs_auth_tok *auth_tok, struct ecryptfs_crypt_stat *crypt_stat);
int ecryptfs_decrypt_dek(struct ecryptfs_auth_tok *auth_tok, struct ecryptfs_crypt_stat *crypt_stat);

int write_dek_packet(char *dest, struct ecryptfs_crypt_stat *crypt_stat, size_t *written);
int parse_dek_packet(char *data, struct ecryptfs_crypt_stat *crypt_stat, size_t *packet_size);

#endif /* #ifndef ECRYPTFS_DEK_H */
