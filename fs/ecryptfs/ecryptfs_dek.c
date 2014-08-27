#include <linux/crypto.h>
#include <asm/unaligned.h>
#include "ecryptfs_dek.h"

extern int dek_encrypt_dek_efs(int sdp_id, dek *plainDek, dek *encDek);
extern int dek_decrypt_dek_efs(int sdp_id, dek *encDek, dek *plainDek, int type);

static int ecryptfs_update_crypt_flag(struct dentry *dentry, int is_sensitive, int is_replaced, int is_rsa_enc);

#if ECRYPTFS_DEK_DEBUG
static void ecryptfs_dumpkey(int sdp_id, char *tag, unsigned char *buf, int len) {
	int i;
	char printBuf[16];
	char sumBuf[512];

	ecryptfs_printk(KERN_INFO, "sdp id=%d,%s", sdp_id, tag);

	if (buf != NULL) {
		memset(sumBuf, 0, 512);
		for(i = 0; i < len; ++i) {
			memset(printBuf, 0, 16);
			sprintf(printBuf, "%02x ", (unsigned char)buf[i]);
			strcat(sumBuf, printBuf);
		}
		ecryptfs_printk(KERN_INFO, "%s\n", sumBuf);
	}
	else{
		ecryptfs_printk(KERN_ERR, "buffer is NULL!!!\n");
	}
}
#endif

int ecryptfs_super_block_get_sdp_id(struct super_block *sb)
{
	int sdp_id = ecryptfs_superblock_to_private(sb)->sdp_id;
#if ECRYPTFS_DEK_DEBUG
	ecryptfs_printk(KERN_INFO, "sdp id is %d\n", sdp_id);
#endif
	return sdp_id;
}

int ecryptfs_is_valid_sdpid(int sdp_id)
{
	if(sdp_id >= 100) { //persona id starts from 100
		return 1;
	}
	return 0;
}

int ecryptfs_get_encrypt_key(unsigned char *sig, int *sig_len, struct ecryptfs_crypt_stat *crypt_stat) 
{
	int rc = 0;
	if(crypt_stat != NULL && (crypt_stat->flags & ECRYPTFS_DEK_SDP_ENABLED)) {
		if((crypt_stat->flags & ECRYPTFS_DEK_IS_SENSITIVE) && (crypt_stat->flags & ECRYPTFS_DEK_IS_REPLACED)) {
			dek DEK;

#if ECRYPTFS_DEK_DEBUG
			ecryptfs_printk(KERN_INFO, "file is sensitive\n");
			ecryptfs_dumpkey(crypt_stat->sdp_id, "encrypted:", crypt_stat->sdp_dek.buf, crypt_stat->sdp_dek.len);
#endif
			if (crypt_stat->flags & ECRYPTFS_DEK_RSA_ENC) {
				rc = dek_decrypt_dek_efs(crypt_stat->sdp_id, &crypt_stat->sdp_dek, &DEK, DEK_RSA_ENC);
			} else {
				rc = dek_decrypt_dek_efs(crypt_stat->sdp_id, &crypt_stat->sdp_dek, &DEK, DEK_AES_ENC);
			}
			if (rc < 0) {
				ecryptfs_printk(KERN_ERR, "Error decypting dek; rc = [%d]\n", rc);
				rc = -1;
				goto out;
			}
#if ECRYPTFS_DEK_DEBUG
			ecryptfs_dumpkey(crypt_stat->sdp_id, "decrypted:", DEK.buf, DEK.len);
			ecryptfs_printk(KERN_INFO, "decrypted key size is %d\n", DEK.len);
#endif
			memcpy(sig, DEK.buf, DEK.len);
			(*sig_len) = DEK.len;
		} else {
			memcpy(sig, crypt_stat->sdp_dek.buf, DEK_DEK_LEN);
			(*sig_len) = DEK_DEK_LEN;
#if ECRYPTFS_DEK_DEBUG
			ecryptfs_printk(KERN_INFO, "plain key size is %d\n", DEK_DEK_LEN);
			ecryptfs_dumpkey(crypt_stat->sdp_id, "plain:", crypt_stat->sdp_dek.buf, DEK_DEK_LEN);
#endif
		}
	}
out:
	return rc;
}

int ecryptfs_get_decrypt_key(unsigned char *sig, int *sig_len, struct ecryptfs_crypt_stat *crypt_stat)
{
	int rc = 0;
	if(crypt_stat != NULL && (crypt_stat->flags & ECRYPTFS_DEK_SDP_ENABLED)) {
		if((crypt_stat->flags & ECRYPTFS_DEK_IS_SENSITIVE) && (crypt_stat->flags & ECRYPTFS_DEK_IS_REPLACED)) {
			dek DEK;
#if ECRYPTFS_DEK_DEBUG
			ecryptfs_printk(KERN_INFO, "file is sensitive\n");
			ecryptfs_dumpkey(crypt_stat->sdp_id, "encrypted:", crypt_stat->sdp_dek.buf, crypt_stat->sdp_dek.len);
#endif
			if (crypt_stat->flags & ECRYPTFS_DEK_RSA_ENC) {
				rc = dek_decrypt_dek_efs(crypt_stat->sdp_id, &crypt_stat->sdp_dek, &DEK, DEK_RSA_ENC);
			} else {
				rc = dek_decrypt_dek_efs(crypt_stat->sdp_id, &crypt_stat->sdp_dek, &DEK, DEK_AES_ENC);
			}
			if (rc < 0) {
				ecryptfs_printk(KERN_ERR, "Error decypting dek; rc = [%d]\n", rc);
				rc = -1;
				goto out;
			}
#if ECRYPTFS_DEK_DEBUG
			ecryptfs_dumpkey(crypt_stat->sdp_id, "decrypted:", DEK.buf, DEK.len);
			ecryptfs_printk(KERN_INFO, "decrypted key size is %d\n", DEK.len);
#endif
			memcpy(sig, DEK.buf, DEK.len);
			(*sig_len) = DEK.len;
		} else {
			memcpy(sig, crypt_stat->sdp_dek.buf, DEK_DEK_LEN);
			(*sig_len) = DEK_DEK_LEN;
#if ECRYPTFS_DEK_DEBUG
			ecryptfs_printk(KERN_INFO, "plain key size is %d\n", DEK_DEK_LEN);
			ecryptfs_dumpkey(crypt_stat->sdp_id, "plain:", crypt_stat->sdp_dek.buf, DEK_DEK_LEN);
#endif
		}
	}
out:
	return rc;
}

int ecryptfs_encrypt_and_replace_sdp_dek(struct dentry *dentry, int is_sensitive)
{
	int rc = 0;
	int rsa_enc = 0;
	struct ecryptfs_crypt_stat *crypt_stat;

	crypt_stat = &ecryptfs_inode_to_private(dentry->d_inode)->crypt_stat;

	if(crypt_stat != NULL && (crypt_stat->flags & ECRYPTFS_DEK_SDP_ENABLED) &&
			!(crypt_stat->flags & ECRYPTFS_DEK_IS_REPLACED)) {
		if (is_sensitive) {
			dek new_dek;
			if (crypt_stat->sdp_dek.len <= 0) {
				ecryptfs_printk(KERN_ERR, "sdp_dek is empty\n");
				rc = -1;
				goto out;
			}
#if ECRYPTFS_DEK_DEBUG
			ecryptfs_printk(KERN_INFO, "filename=[%s]", (char*)dentry->d_name.name);
			ecryptfs_dumpkey(crypt_stat->sdp_id, "decrypted:", crypt_stat->sdp_dek.buf, crypt_stat->sdp_dek.len);
#endif
			rc = dek_encrypt_dek_efs(crypt_stat->sdp_id, &crypt_stat->sdp_dek, &new_dek);
			if (rc == DEK_RSA_ENC) {
				ecryptfs_printk(KERN_INFO, "encrypted with pub_key\n");
				rsa_enc = 1;
			} else if (rc == DEK_AES_ENC){
				ecryptfs_printk(KERN_INFO, "encrypted with m_key\n");
			}

			if(rc < 0) {
				ecryptfs_printk(KERN_ERR, "dek_encrypt_dek_efs error : rc=%d, key to be plain\n", rc);
				ecryptfs_update_crypt_flag(dentry, 0, 1, rsa_enc);
				rc = -1;
				goto out;
			}

			crypt_stat->sdp_dek.len = new_dek.len;
			memset(crypt_stat->sdp_dek.buf, 0, DEK_DEK_ENC_LEN);
			memcpy(crypt_stat->sdp_dek.buf, new_dek.buf, sizeof(new_dek.buf));
#if ECRYPTFS_DEK_DEBUG
			ecryptfs_dumpkey(crypt_stat->sdp_id, "encrypted:", crypt_stat->sdp_dek.buf, crypt_stat->sdp_dek.len);
			ecryptfs_printk(KERN_INFO, "dek key replaced to sensitive\n");
#endif
			ecryptfs_update_crypt_flag(dentry, 1, 1, rsa_enc);

		}
		else{
#if ECRYPTFS_DEK_DEBUG
			ecryptfs_update_crypt_flag(dentry, 0, 1, rsa_enc);
			ecryptfs_printk(KERN_INFO, "dek key is plain\n");
#endif
		}
	}

out:
	return rc;
}

int ecryptfs_parse_xattr_is_sensitive(const void *data, int len){
	// parse dek data from xattr
	if(len > 0) {
		char *convert = (char*)data;
		if(strcmp(convert,"1") == 0) {
#if ECRYPTFS_DEK_DEBUG
			ecryptfs_printk(KERN_INFO, "is sensitive\n");
#endif
			return 1;
		}
	}
#if ECRYPTFS_DEK_DEBUG
	ecryptfs_printk(KERN_INFO, "is protected\n");
#endif
	return 0;
}

int ecryptfs_encrypt_dek(struct ecryptfs_auth_tok *auth_tok,
		struct ecryptfs_crypt_stat *crypt_stat) {
	struct scatterlist dst_sg[2];
	struct scatterlist src_sg[2];
	struct mutex *tfm_mutex;
	struct blkcipher_desc desc = {
			.tfm = NULL,
			.flags = CRYPTO_TFM_REQ_MAY_SLEEP
	};
	int rc = 0;
	char iv[ECRYPTFS_DEFAULT_IV_BYTES];
#ifdef CONFIG_CRYPTO_FIPS
	rc = ecryptfs_get_tfm_and_mutex_for_cipher_name(&desc.tfm, &tfm_mutex,
		crypt_stat->cipher, crypt_stat->flags);
#else
	rc = ecryptfs_get_tfm_and_mutex_for_cipher_name(&desc.tfm, &tfm_mutex,
		crypt_stat->cipher);
#endif
	if (unlikely(rc)) {
		printk(KERN_ERR "Internal error whilst attempting to get "
			"tfm and mutex for cipher name [%s]; rc = [%d]\n",
			crypt_stat->cipher, rc);
		goto out;
	}

#if ECRYPTFS_DEK_DEBUG
	ecryptfs_printk(KERN_INFO, "Encrypting sdp_dek, size=[%zd]\n", crypt_stat->sdp_dek.len);
	ecryptfs_dumpkey(crypt_stat->sdp_id, "plain:", crypt_stat->sdp_dek.buf, crypt_stat->sdp_dek.len);
#endif
	rc = virt_to_scatterlist(crypt_stat->sdp_dek.buf, crypt_stat->sdp_dek.len,
		src_sg, 2);
	if (rc < 1 || rc > 2) {
		ecryptfs_printk(KERN_ERR, "Error generating scatterlist "
			"for crypt_stat->sdp_dek.buf; expected rc = 1; "
			"got rc = [%d]. crypt_stat->sdp_dek.len = [%zd]\n",
			rc, crypt_stat->sdp_dek.len);
		rc = -ENOMEM;
		goto out;
	}
	rc = virt_to_scatterlist(crypt_stat->sdp_dek_enc.buf, crypt_stat->sdp_dek.len,
		dst_sg, 2);
	if (rc < 1 || rc > 2) {
		ecryptfs_printk(KERN_ERR, "Error generating scatterlist "
			"for crypt_stat encrypted session key; "
			"expected rc = 1; got rc = [%d]. "
			"crypt_stat->sdp_dek.len = [%zd]\n", rc,
			crypt_stat->sdp_dek.len);
		rc = -ENOMEM;
		goto out;
	}
	mutex_lock(tfm_mutex);
	rc = crypto_blkcipher_setkey(desc.tfm, auth_tok->token.password.session_key_encryption_key,
		crypt_stat->key_size);
	if (rc < 0) {
		mutex_unlock(tfm_mutex);
		ecryptfs_printk(KERN_ERR, "Error setting key for crypto "
			"context; rc = [%d]\n", rc);
		goto out;
	}
	rc = 0;
#if ECRYPTFS_DEK_DEBUG
	ecryptfs_printk(KERN_INFO, "Encrypting [%zd] bytes of the key\n",
		crypt_stat->sdp_dek.len);
#endif
	crypto_blkcipher_get_iv(desc.tfm, iv, ECRYPTFS_DEFAULT_IV_BYTES);
	rc = crypto_blkcipher_encrypt(&desc, dst_sg, src_sg,
		crypt_stat->sdp_dek.len);
	crypto_blkcipher_set_iv(desc.tfm, iv, ECRYPTFS_DEFAULT_IV_BYTES);
	mutex_unlock(tfm_mutex);
	if (rc) {
		printk(KERN_ERR "Error encrypting; rc = [%d]\n", rc);
		goto out;
	}
	crypt_stat->sdp_dek_enc.len = crypt_stat->sdp_dek.len;

#if ECRYPTFS_DEK_DEBUG
	ecryptfs_printk(KERN_INFO, "sdp_dek keys, plain size [%zd], enc size [%zd]\n",
		crypt_stat->sdp_dek.len, crypt_stat->sdp_dek_enc.len);
	ecryptfs_dumpkey(crypt_stat->sdp_id, "plain:",
		crypt_stat->sdp_dek.buf, crypt_stat->sdp_dek.len);
	ecryptfs_dumpkey(crypt_stat->sdp_id, "encrypted:",
		crypt_stat->sdp_dek_enc.buf, crypt_stat->sdp_dek_enc.len);
#endif
	return 0;
out:
	return -1;
}

int ecryptfs_decrypt_dek(struct ecryptfs_auth_tok *auth_tok,
		struct ecryptfs_crypt_stat *crypt_stat) {
	struct scatterlist dst_sg[2];
	struct scatterlist src_sg[2];
	struct mutex *tfm_mutex;
	struct blkcipher_desc desc = {
			.flags = CRYPTO_TFM_REQ_MAY_SLEEP
	};
	int rc = 0;
	char iv[ECRYPTFS_DEFAULT_IV_BYTES];
#ifdef CONFIG_CRYPTO_FIPS
	rc = ecryptfs_get_tfm_and_mutex_for_cipher_name(&desc.tfm, &tfm_mutex,
			crypt_stat->cipher,crypt_stat->flags);
#else
	rc = ecryptfs_get_tfm_and_mutex_for_cipher_name(&desc.tfm, &tfm_mutex,
			crypt_stat->cipher);
#endif
	if (unlikely(rc)) {
		printk(KERN_ERR "Internal error whilst attempting to get "
				"tfm and mutex for cipher name [%s]; rc = [%d]\n",
				crypt_stat->cipher, rc);
		goto out;
	}

#if ECRYPTFS_DEK_DEBUG
	ecryptfs_printk(KERN_INFO, "Decrypting sdp_dek_enc, size=[%zd]\n",
			crypt_stat->sdp_dek_enc.len);
	ecryptfs_dumpkey(crypt_stat->sdp_id, "encrypted:",
			crypt_stat->sdp_dek_enc.buf, crypt_stat->sdp_dek_enc.len);
#endif
	rc = virt_to_scatterlist(crypt_stat->sdp_dek_enc.buf,
			crypt_stat->sdp_dek_enc.len,
			src_sg, 2);
	if (rc < 1 || rc > 2) {
		printk(KERN_ERR "Internal error whilst attempting to convert "
				"crypt_stat->sdp_dek_enc.buf to scatterlist; "
				"expected rc = 1; got rc = [%d]. "
				"crypt_stat->sdp_dek_enc.len = [%d]\n", rc,
				crypt_stat->sdp_dek_enc.len);
		goto out;
	}

	rc = virt_to_scatterlist(crypt_stat->sdp_dek.buf,
			crypt_stat->sdp_dek_enc.len,
			dst_sg, 2);
	if (rc < 1 || rc > 2) {
		printk(KERN_ERR "Internal error whilst attempting to convert "
				"crypt_stat->sdp_dek.buf to scatterlist; "
				"expected rc = 1; got rc = [%d]\n", rc);
		goto out;
	}

	mutex_lock(tfm_mutex);
	rc = crypto_blkcipher_setkey(
			desc.tfm, auth_tok->token.password.session_key_encryption_key,
			crypt_stat->key_size);
	if (unlikely(rc < 0)) {
		mutex_unlock(tfm_mutex);
		printk(KERN_ERR "Error setting key for crypto context\n");
		rc = -EINVAL;
		goto out;
	}
	crypto_blkcipher_get_iv(desc.tfm, iv, ECRYPTFS_DEFAULT_IV_BYTES);
	rc = crypto_blkcipher_decrypt(&desc, dst_sg, src_sg,
			crypt_stat->sdp_dek_enc.len);
	crypto_blkcipher_set_iv(desc.tfm, iv, ECRYPTFS_DEFAULT_IV_BYTES);
	mutex_unlock(tfm_mutex);
	if (unlikely(rc)) {
		printk(KERN_ERR "Error decrypting; rc = [%d]\n", rc);
		goto out;
	}
	crypt_stat->sdp_dek.len = crypt_stat->sdp_dek_enc.len;

#if ECRYPTFS_DEK_DEBUG
	ecryptfs_printk(KERN_INFO, "sdp_dek keys, plain size [%zd], enc size [%zd]\n",
			crypt_stat->sdp_dek.len, crypt_stat->sdp_dek_enc.len);
	ecryptfs_dumpkey(crypt_stat->sdp_id, "plain:",
			crypt_stat->sdp_dek.buf, crypt_stat->sdp_dek.len);
	ecryptfs_dumpkey(crypt_stat->sdp_id, "encrypted:",
			crypt_stat->sdp_dek_enc.buf, crypt_stat->sdp_dek_enc.len);
#endif
	return 0;
out:
	return -1;
}

int write_dek_packet(char *dest,
		struct ecryptfs_crypt_stat *crypt_stat,
		size_t *written) {
	*written = 0;
	dest[(*written)++] = ECRYPTFS_DEK_PACKET_TYPE;

	memset(dest + *written, 0, PKG_NAME_SIZE);
	memcpy(dest + *written, current->comm, PKG_NAME_SIZE);
	(*written) += PKG_NAME_SIZE;

	put_unaligned_be32(current_euid(), dest + *written);
	(*written) += 4;

	memset(dest + *written, 0, DEK_DEK_ENC_LEN);
	if (crypt_stat->flags & ECRYPTFS_DEK_IS_SENSITIVE) {
		memcpy(dest + *written, crypt_stat->sdp_dek.buf, crypt_stat->sdp_dek.len);
	} else {
		memcpy(dest + *written, crypt_stat->sdp_dek_enc.buf, crypt_stat->sdp_dek_enc.len);
	}
	(*written) += DEK_DEK_ENC_LEN;

	return 0;
}

int parse_dek_packet(char *data,
		struct ecryptfs_crypt_stat *crypt_stat,
		size_t *packet_size) {
	int rc = 0;
	char temp_comm[PKG_NAME_SIZE]; //test
	int temp_euid;

	(*packet_size) = 0;

	if (data[(*packet_size)++] != ECRYPTFS_DEK_PACKET_TYPE) {
		printk(KERN_ERR "First byte != 0x%.2x; invalid packet\n",
				ECRYPTFS_DEK_PACKET_TYPE);
		rc = -EINVAL;
	}

	memcpy(temp_comm, &data[*packet_size], PKG_NAME_SIZE);
	(*packet_size) += PKG_NAME_SIZE;

	temp_euid = get_unaligned_be32(data + *packet_size);
	(*packet_size) += 4;

	if (crypt_stat->flags & ECRYPTFS_DEK_IS_SENSITIVE) {
		if (crypt_stat->flags & ECRYPTFS_DEK_RSA_ENC) {
			memcpy(crypt_stat->sdp_dek.buf, &data[*packet_size], DEK_DEK_ENC_LEN);
			crypt_stat->sdp_dek.len = DEK_DEK_ENC_LEN;
		} else {
			memcpy(crypt_stat->sdp_dek.buf, &data[*packet_size], DEK_DEK_LEN*2);
			crypt_stat->sdp_dek.len = DEK_DEK_LEN*2;
		}
	} else {
		memcpy(crypt_stat->sdp_dek_enc.buf, &data[*packet_size], DEK_DEK_LEN);
		crypt_stat->sdp_dek_enc.len = DEK_DEK_LEN;
	}
	(*packet_size) += DEK_DEK_ENC_LEN;
#if ECRYPTFS_DEK_DEBUG
	printk("%s() : comm : %s [euid:%d]\n",
		__func__, temp_comm, temp_euid);
#endif
	return rc;
}

static int ecryptfs_update_crypt_flag(struct dentry *dentry, int is_sensitive, int is_replaced, int is_rsa_enc)
{
	int rc = 0;
	struct dentry *lower_dentry;
	struct inode *inode;
	struct inode *lower_inode;
	struct ecryptfs_crypt_stat *crypt_stat;
	struct ecryptfs_mount_crypt_stat *mount_crypt_stat;

	crypt_stat = &ecryptfs_inode_to_private(dentry->d_inode)->crypt_stat;
	if (!(crypt_stat->flags & ECRYPTFS_STRUCT_INITIALIZED))
		ecryptfs_init_crypt_stat(crypt_stat);
	inode = dentry->d_inode;
	lower_inode = ecryptfs_inode_to_lower(inode);
	lower_dentry = ecryptfs_dentry_to_lower(dentry);

	mutex_lock(&crypt_stat->cs_mutex);

	mount_crypt_stat = &ecryptfs_superblock_to_private(
			dentry->d_sb)->mount_crypt_stat;
	rc = ecryptfs_get_lower_file(dentry, inode);
	if (rc) {
		mutex_unlock(&crypt_stat->cs_mutex);
		ecryptfs_printk(KERN_ERR, "ecryptfs_get_lower_file rc=%d\n", rc);
		goto out;
	}

	if (is_sensitive) {
		crypt_stat->flags |= ECRYPTFS_DEK_IS_SENSITIVE;
	}
	else{
		crypt_stat->flags &= ~ECRYPTFS_DEK_IS_SENSITIVE;
	}

	if (is_replaced) {
		crypt_stat->flags |= ECRYPTFS_DEK_IS_REPLACED;
	}
	else{
		crypt_stat->flags &= ~ECRYPTFS_DEK_IS_REPLACED;
	}

	if (is_rsa_enc) {
		crypt_stat->flags |= ECRYPTFS_DEK_RSA_ENC;
	}
	else{
		crypt_stat->flags &= ~ECRYPTFS_DEK_RSA_ENC;
	}

	rc = ecryptfs_write_metadata(dentry, inode);
	if (rc) {
		if (!(mount_crypt_stat->flags
				& ECRYPTFS_PLAINTEXT_PASSTHROUGH_ENABLED)) {
			rc = -EIO;
			printk(KERN_WARNING "Either the lower file "
					"is not in a valid eCryptfs format, "
					"or the key could not be retrieved. "
					"Plaintext passthrough mode is not "
					"enabled; returning -EIO\n");
			mutex_unlock(&crypt_stat->cs_mutex);
			ecryptfs_printk(KERN_INFO, "ecryptfs_write_metadata rc=%d\n", rc);
			goto out;
		}
		rc = 0;
		crypt_stat->flags &= ~(ECRYPTFS_I_SIZE_INITIALIZED
				| ECRYPTFS_ENCRYPTED);
	}

	rc = ecryptfs_write_inode_size_to_metadata(inode);
	if (rc) {
		mutex_unlock(&crypt_stat->cs_mutex);
		printk(KERN_ERR "Problem with "
				"ecryptfs_write_inode_size_to_metadata; "
				"rc = [%d]\n", rc);
		goto out;
	}

	ecryptfs_put_lower_file(inode);

	mutex_unlock(&crypt_stat->cs_mutex);

out:
	fsstack_copy_attr_all(inode, lower_inode);
	return rc;
}
