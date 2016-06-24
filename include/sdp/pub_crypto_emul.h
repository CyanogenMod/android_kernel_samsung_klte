#ifndef _FIPS_CRYPTO_H
#define _FIPS_CRYPTO_H

#include <sdp/dek_common.h>

#define OP_RSA_ENC 10
#define OP_RSA_DEC 11
#define OP_DH_DEC 12
#define OP_DH_ENC 13

#define PUB_CRYPTO_ERROR 99

struct rsa_send_msg {
    u8 opcode;
	kek_t key;
	dek_t in;
};

struct dh_send_msg {
    u8 opcode;
	//u32 userid;
	dek_t in;
	kek_t key;
};

struct result_msg {
	u8 opcode;
	u16 len;
    unsigned char *result;
};

typedef struct result {
	u8 opcode;
	s16 ret;
	dek_t dek;
}result_t;

void rsa_encryptByPub(kek_t *pub_key, dek_t *in, dek_t *out);

int rsa_decryptByPair(kek_t *pair, dek_t *in, dek_t *out);

int dh_decryptEDEK(dek_t *edek, dek_t *dek, kek_t *kek);

int dh_encryptDEK(dek_t *dek, dek_t *edek, kek_t *kek);

#endif
