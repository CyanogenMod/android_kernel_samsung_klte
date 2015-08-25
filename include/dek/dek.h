#ifndef _LINUX_DEK_H
#define _LINUX_DEK_H

#include <linux/limits.h>
#include <linux/ioctl.h>

#define DEK_MAX_PERSONA		10	// TODO: check right amount
#define DEK_NAME_LEN		256	// TODO: is this needed?
#define DEK_DEK_LEN			32
#define DEK_DEK_ENC_LEN		(DEK_RSA_KEY_BITS/8) // 256(2048 bits)
#define DEK_RSA_KEY_BITS	2048
#define DEK_RSA_KEY_LEN		(DEK_RSA_KEY_BITS/4+4)
#define DEK_M_KEY_LEN		(DEK_M_KEY_BITS/8)
#define DEK_M_KEY_BITS		256

#define DEK_RSA_ENC		1
#define DEK_AES_ENC		2

#define TYPE_PLAIN_DEK 		0
#define TYPE_RSA_ENC_DEK 	1
#define TYPE_AES_ENC_DEK 	2
#define TYPE_PUB_KEK 	3
#define TYPE_PRIV_KEK 	4
#define TYPE_MAS_KEK 	5

#define __DEKIOC		0x77

typedef struct _key{
	int len;
	int type;
	unsigned char buf[DEK_DEK_ENC_LEN];
}dek;

typedef struct _kek{
	int len;
	int type;
	unsigned char buf[DEK_RSA_KEY_LEN];
}kek;

typedef struct _dek_arg_generate_dek {
	int persona_id;
	dek dek;
}dek_arg_generate_dek;

typedef struct _dek_arg_encrypt_dek {
	int persona_id;
	dek plain_dek;
	dek enc_dek;
	int enc_type;
}dek_arg_encrypt_dek;

typedef struct _dek_arg_decrypt_dek {
	int persona_id;
	dek plain_dek;
	dek enc_dek;
	int enc_type;
}dek_arg_decrypt_dek;

typedef struct _dek_arg_get_kek {
	int persona_id;
	int type;
	kek key;
}dek_arg_get_enc_kek, dek_arg_get_dec_kek;

/*
 * DEK_ON_BOOT indicates that there's persona in the system.
 *
 * The driver will load public key and encrypted private key.
 */
typedef struct _dek_arg_on_boot {
	int persona_id;
	kek pub_key;
}dek_arg_on_boot;

typedef struct _dek_arg_on_device_locked {
	int persona_id;
}dek_arg_on_device_locked;

typedef struct _dek_arg_on_device_unlocked {
	int persona_id;
	kek priv_key;
	kek mas_key;
}dek_arg_on_device_unlocked;

typedef struct _dek_arg_on_user_added {
	int persona_id;
	kek pub_key;
}dek_arg_on_user_added;

typedef struct _dek_arg_on_user_removed {
	int persona_id;
}dek_arg_on_user_removed;

#define DEK_ON_BOOT              _IOW(__DEKIOC, 0, char[DEK_NAME_LEN])
#define DEK_GENERATE_DEK         _IOW(__DEKIOC, 1, char[DEK_NAME_LEN])
#define DEK_ENCRYPT_DEK          _IOW(__DEKIOC, 2, char[DEK_NAME_LEN])
#define DEK_DECRYPT_DEK          _IOR(__DEKIOC, 3, char[DEK_NAME_LEN])
#define DEK_ON_DEVICE_LOCKED     _IOW(__DEKIOC, 4, char[DEK_NAME_LEN])
#define DEK_ON_DEVICE_UNLOCKED   _IOW(__DEKIOC, 5, char[DEK_NAME_LEN])
#define DEK_ON_USER_ADDED        _IOW(__DEKIOC, 6, char[DEK_NAME_LEN])
#define DEK_ON_USER_REMOVED      _IOW(__DEKIOC, 7, char[DEK_NAME_LEN])
#define DEK_ON_CHANGE_PASSWORD   _IOW(__DEKIOC, 8, char[DEK_NAME_LEN])
#define DEK_GET_ENC_KEK          _IOW(__DEKIOC, 9, char[DEK_NAME_LEN])
#define DEK_GET_DEC_KEK          _IOW(__DEKIOC, 10, char[DEK_NAME_LEN])
#endif
