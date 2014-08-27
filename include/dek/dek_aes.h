#ifndef _LINUX_DEK_AES_H
#define _LINUX_DEK_AES_H

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/crypto.h>
#include <dek/dek.h>

struct crypto_cipher *dek_aes_key_setup(unsigned char *key, int len);
void dek_aes_key_free(struct crypto_cipher *tfm);

#endif
