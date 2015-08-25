
#include <linux/err.h>
#include <dek/dek_aes.h>

struct crypto_cipher *dek_aes_key_setup(unsigned char *key, int len)
{
	struct crypto_cipher *tfm;

	tfm = crypto_alloc_cipher("aes", 0, CRYPTO_ALG_ASYNC);
	if (!IS_ERR(tfm))
		crypto_cipher_setkey(tfm, key, len);

	return tfm;
}


void dek_aes_key_free(struct crypto_cipher *tfm)
{
	crypto_free_cipher(tfm);
}
