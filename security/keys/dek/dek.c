#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/time.h>
#include <linux/list.h>
#include <linux/wait.h>
#include <linux/random.h>
#include <linux/err.h>
#include <dek/dek.h>
#include <dek/dek_aes.h>


#define DEK_USER_ID_OFFSET	100

#define DEK_DEBUG		0
#define DEK_LOG_COUNT	100

#define PERSONA_KEY_ARR_IDX(personaId) (personaId-DEK_USER_ID_OFFSET)

/* RSA keypairs */
kek pub_key[DEK_MAX_PERSONA];
kek priv_key[DEK_MAX_PERSONA];
kek mas_key[DEK_MAX_PERSONA];

/* Crypto tfms */
struct crypto_cipher *tfm[DEK_MAX_PERSONA];

/* Log buffer */
struct log_struct
{
	int len;
	char buf[256];
	struct list_head list;
	spinlock_t list_lock;
};
struct log_struct log_buffer;
static int log_count = 0;

/* Wait queue */
wait_queue_head_t wq;
static int flag = 0;

/* Log */
static void dek_add_to_log(int persona_id, char * buffer);


static int dek_open_evt(struct inode *inode, struct file *file)
{
	printk("dek: dek_open_evt\n");
	return 0;
}

static int dek_release_evt(struct inode *ignored, struct file *file)
{
	printk("dek: dek_release_evt\n");
	return 0;
}

static int dek_open_req(struct inode *inode, struct file *file)
{
	printk("dek: dek_open_req\n");
	return 0;
}

static int dek_release_req(struct inode *ignored, struct file *file)
{
	printk("dek: dek_release_req\n");
	return 0;
}

static int dek_open_kek(struct inode *inode, struct file *file)
{
	printk("dek: dek_open_kek\n");
	return 0;
}

static int dek_release_kek(struct inode *ignored, struct file *file)
{
	printk("dek: dek_release_kek\n");
	return 0;
}

#if DEK_DEBUG
static void dump(unsigned char *buf, int len) {
	int i;

	printk("len=%d: ", len);
	for(i=0;i<len;++i) {
		printk("%02x ", (unsigned char)buf[i]);
	}
	printk("\n");
}

static void dump_all_keys(int key_arr_idx) {
	printk("dek: pub_key: ");
	dump(pub_key[key_arr_idx].buf, pub_key[key_arr_idx].len);
	printk("dek: priv_key: ");
	dump(priv_key[key_arr_idx].buf, priv_key[key_arr_idx].len);
	printk("dek: m_key: ");
	dump(mas_key[key_arr_idx].buf, mas_key[key_arr_idx].len);
}
#endif

static int dek_is_persona(int persona_id) {
	if ((persona_id < 100) || (persona_id > 100+DEK_MAX_PERSONA-1)) {
		printk("dek: invalid persona id: %d\n", persona_id);
		dek_add_to_log(persona_id, "Invalid persona id");
		return 0;
	}
	return 1;
}

int dek_generate_dek(int persona_id, dek *newDek) {
	if (!dek_is_persona(persona_id)) {
		return -EFAULT;
	}

	newDek->len = DEK_DEK_LEN;
	get_random_bytes(newDek->buf, newDek->len);

	if (newDek->len <= 0 || newDek->len > DEK_DEK_LEN) {
		memset(newDek, 0, sizeof(dek));
		return -EFAULT;
	}
#if DEK_DEBUG
	else {
		printk("dek: DEK: ");
		dump(newDek->buf, newDek->len);
	}
#endif

	return 0;
}

static int dek_encrypt_dek(int persona_id, dek *plainDek, dek *encDek) {
	int ret = 0;
	int key_arr_idx = PERSONA_KEY_ARR_IDX(persona_id);
	unsigned int i;
	unsigned int bsize;

	if (!dek_is_persona(persona_id)) {
		return -EFAULT;
	}
#if DEK_DEBUG
	printk("dek: plainDek from user: ");
	dump(plainDek->buf, plainDek->len);
#endif
	if (tfm[key_arr_idx] != NULL) {
		bsize = crypto_cipher_blocksize(tfm[key_arr_idx]);
		for (i = 0; i < plainDek->len; i += bsize) {
			crypto_cipher_encrypt_one(
					tfm[key_arr_idx],
					encDek->buf+i,
					plainDek->buf+i);
		}
		encDek->len = plainDek->len;
		ret = DEK_AES_ENC;
	} else {
		printk("dek: no encryption key for id: %d\n", persona_id);
		dek_add_to_log(persona_id, "encrypt failed, no key");
		return -EIO;
	}

	if (encDek->len <= 0 || encDek->len > DEK_DEK_ENC_LEN) {
		printk("dek: dek_encrypt_dek, incorrect len=%d\n", encDek->len);
		memset(encDek, 0, sizeof(dek));
		return -EFAULT;
	}
#if DEK_DEBUG
	else {
		printk("dek: encDek to user: ");
		dump(encDek->buf, encDek->len);
	}
#endif

	return ret;
}

int dek_encrypt_dek_efs(int persona_id, dek *plainDek, dek *encDek) {
	if (!dek_is_persona(persona_id)) {
		return -EFAULT;
	}
	return dek_encrypt_dek(persona_id, plainDek, encDek);
}

static int dek_decrypt_dek(int persona_id, dek *encDek, dek *plainDek, int type) {
	int key_arr_idx = PERSONA_KEY_ARR_IDX(persona_id);
	unsigned int i;
	unsigned int bsize;

	if (!dek_is_persona(persona_id)) {
		return -EFAULT;
	}
#if DEK_DEBUG
	printk("dek: encDek from user: ");
	dump(encDek->buf, encDek->len);
#endif
	if (type == DEK_AES_ENC) {
		if (tfm[key_arr_idx] != NULL) {
			bsize = crypto_cipher_blocksize(tfm[key_arr_idx]);
			for (i = 0; i < encDek->len; i += bsize) {
				crypto_cipher_decrypt_one(
						tfm[key_arr_idx],
						plainDek->buf+i,
						encDek->buf+i);
			}
			plainDek->len = encDek->len;
		} else {
			printk("dek: no master key for id: %d\n", persona_id);
			dek_add_to_log(persona_id, "decrypt failed, persona locked");
			return -EIO;
		}
	} else if (type == DEK_RSA_ENC) {
		printk("dek: Not supported key type: %d\n", type);
		dek_add_to_log(persona_id, "decrypt failed, RSA type not supported");
		return -EFAULT;
	} else {
		printk("dek: wrong decrypt key type: %d\n", type);
		dek_add_to_log(persona_id, "decrypt failed, wrong decrypt key type");
		return -EFAULT;
	}

	if (plainDek->len <= 0 || plainDek->len > DEK_DEK_LEN) {
		printk("dek: dek_decrypt_dek, incorrect len=%d\n", plainDek->len);
		memset(plainDek, 0, sizeof(dek));
		return -EFAULT;
	} else {
#if DEK_DEBUG
		printk("dek: plainDek to user: ");
		dump(plainDek->buf, plainDek->len);
#endif
	}
	return 0;
}

int dek_decrypt_dek_efs(int persona_id, dek *encDek, dek *plainDek, int type) {
	return dek_decrypt_dek(persona_id, encDek, plainDek, type);
}


static int dek_on_boot(dek_arg_on_boot *evt) {
	int ret = 0;
	int key_arr_idx = PERSONA_KEY_ARR_IDX(evt->persona_id);

	memcpy(pub_key[key_arr_idx].buf, evt->pub_key.buf, evt->pub_key.len);
	pub_key[key_arr_idx].len = evt->pub_key.len;

#if DEK_DEBUG
	dump_all_keys(key_arr_idx);
#endif

	return ret;
}

static int dek_on_device_locked(dek_arg_on_device_locked *evt) {
	int key_arr_idx = PERSONA_KEY_ARR_IDX(evt->persona_id);
	dek_aes_key_free(tfm[key_arr_idx]);
	tfm[key_arr_idx] = NULL;

	memset(&priv_key[key_arr_idx], 0, sizeof(kek));
	memset(&mas_key[key_arr_idx], 0, sizeof(kek));

#if DEK_DEBUG
	dump_all_keys(key_arr_idx);
#endif

	return 0;
}

static int dek_on_device_unlocked(dek_arg_on_device_unlocked *evt) {
	int key_arr_idx = PERSONA_KEY_ARR_IDX(evt->persona_id);

	/*
	 * TODO : lock needed
	 */

	memcpy(mas_key[key_arr_idx].buf, evt->mas_key.buf, evt->mas_key.len);
	mas_key[key_arr_idx].len = evt->mas_key.len;
	memcpy(priv_key[key_arr_idx].buf, evt->priv_key.buf, evt->priv_key.len);
	priv_key[key_arr_idx].len = evt->priv_key.len;

	tfm[key_arr_idx] = dek_aes_key_setup(evt->mas_key.buf, evt->mas_key.len);
	if (IS_ERR(tfm[key_arr_idx])) {
		printk("dek: error setting up key\n");
		dek_add_to_log(evt->persona_id, "error setting up key");
		tfm[key_arr_idx] = NULL;
	}

#if DEK_DEBUG
	dump_all_keys(key_arr_idx);
#endif

	return 0;
}

static int dek_on_user_added(dek_arg_on_user_added *evt) {
	int key_arr_idx = PERSONA_KEY_ARR_IDX(evt->persona_id);

	memcpy(pub_key[key_arr_idx].buf, evt->pub_key.buf, evt->pub_key.len);
	pub_key[key_arr_idx].len = evt->pub_key.len;

#if DEK_DEBUG
	dump_all_keys(key_arr_idx);
#endif
	return 0;
}

static int dek_on_user_removed(dek_arg_on_user_removed *evt) {
	int key_arr_idx = PERSONA_KEY_ARR_IDX(evt->persona_id);

	memset(&pub_key[key_arr_idx], 0, sizeof(kek));
	memset(&priv_key[key_arr_idx], 0, sizeof(kek));
	memset(&mas_key[key_arr_idx], 0, sizeof(kek));

#if DEK_DEBUG
	dump_all_keys(key_arr_idx);
#endif

	dek_aes_key_free(tfm[key_arr_idx]);
	tfm[key_arr_idx] = NULL;

	return 0;
}

// I'm thinking... if minor id can represent persona id

static long dek_do_ioctl_evt(unsigned int minor, unsigned int cmd,
		unsigned long arg) {
	long ret = 0;
	void __user *ubuf = (void __user *)arg;
	void *cleanup = NULL;

	switch (cmd) {
	/*
	 * Event while booting.
	 *
	 * This event comes per persona, the driver is responsible to
	 * verify things good whether it's compromised.
	 */
	case DEK_ON_BOOT: {
		dek_arg_on_boot *evt = kzalloc(sizeof(dek_arg_on_boot), GFP_KERNEL);
		cleanup = evt;

		printk("dek: DEK_ON_BOOT\n");
		//memset(&evt, 0, sizeof(dek_arg_on_boot));

		if(copy_from_user(evt, ubuf, sizeof(dek_arg_on_boot))) {
			printk("dek: can't copy from user\n");
			ret = -EFAULT;
			goto err;
		}
		if (!dek_is_persona(evt->persona_id)) {
			ret = -EFAULT;
			goto err;
		}
		ret = dek_on_boot(evt);
		if (ret < 0) {
			dek_add_to_log(evt->persona_id, "Boot failed");
			goto err;
		}
		dek_add_to_log(evt->persona_id, "Booted");
		break;
	}
	/*
	 * Event when device is locked.
	 *
	 * Nullify private key which prevents decryption.
	 */
	case DEK_ON_DEVICE_LOCKED: {
		//dek_arg_on_device_locked evt;
		dek_arg_on_device_locked *evt = kzalloc(sizeof(dek_arg_on_device_locked), GFP_KERNEL);
		cleanup = evt;

		printk("dek: DEK_ON_DEVICE_LOCKED\n");
		//memset(&evt, 0, sizeof(dek_arg_on_device_locked));

		if(copy_from_user(evt, ubuf, sizeof(dek_arg_on_device_locked))) {
			printk("dek: can't copy from user\n");
			ret = -EFAULT;
			goto err;
		}
		if (!dek_is_persona(evt->persona_id)) {
			ret = -EFAULT;
			goto err;
		}
		ret = dek_on_device_locked(evt);
		if (ret < 0) {
			dek_add_to_log(evt->persona_id, "Lock failed");
			goto err;
		}
		dek_add_to_log(evt->persona_id, "Locked");

		printk("dek: after locked for id: %d\n", evt->persona_id);

		break;
	}
	/*
	 * Event when device unlocked.
	 *
	 * Read private key and decrypt with user password.
	 */
	case DEK_ON_DEVICE_UNLOCKED: {
		//dek_arg_on_device_unlocked evt;
		dek_arg_on_device_unlocked *evt = kzalloc(sizeof(dek_arg_on_device_unlocked), GFP_KERNEL);
		cleanup = evt;


		printk("dek: DEK_ON_DEVICE_UNLOCKED\n");
		//memset(&evt, 0, sizeof(dek_arg_on_device_unlocked));

		if(copy_from_user(evt, ubuf, sizeof(dek_arg_on_device_unlocked))) {
			printk("dek: can't copy from user\n");
			ret = -EFAULT;
			goto err;
		}
		if (!dek_is_persona(evt->persona_id)) {
			ret = -EFAULT;
			goto err;
		}
		ret = dek_on_device_unlocked(evt);
		if (ret < 0) {
			dek_add_to_log(evt->persona_id, "Unlock failed");
			goto err;
		}
		dek_add_to_log(evt->persona_id, "Unlocked");

		memset(evt, 0, sizeof(dek_arg_on_device_unlocked));
		break;
	}
	/*
	 * Event when new user(persona) added.
	 *
	 * Generate RSA public key and encrypt private key with given
	 * password. Also pub-key and encryped priv-key have to be stored
	 * in a file system.
	 */
	case DEK_ON_USER_ADDED: {
		//dek_arg_on_user_added evt;
		dek_arg_on_user_added *evt = kzalloc(sizeof(dek_arg_on_user_added), GFP_KERNEL);
		cleanup = evt;

		printk("dek: DEK_ON_USER_ADDED\n");
		//memset(&evt, 0, sizeof(dek_arg_on_user_added));

		if(copy_from_user(evt, ubuf, sizeof(dek_arg_on_user_added))) {
			printk("dek: can't copy from user\n");
			ret = -EFAULT;
			goto err;
		}
		if (!dek_is_persona(evt->persona_id)) {
			ret = -EFAULT;
			goto err;
		}
		ret = dek_on_user_added(evt);
		if (ret < 0) {
			dek_add_to_log(evt->persona_id, "Add user failed");
			goto err;
		}
		dek_add_to_log(evt->persona_id, "Added user");
		break;
	}
	/*
	 * Event when user is removed.
	 *
	 * Remove pub-key file & encrypted priv-key file.
	 */
	case DEK_ON_USER_REMOVED: {
		dek_arg_on_user_removed evt;

		printk("dek: DEK_ON_USER_REMOVED\n");
		memset(&evt, 0, sizeof(dek_arg_on_user_removed));

		if(copy_from_user(&evt, ubuf, sizeof(evt))) {
			printk("dek: can't copy from user\n");
			ret = -EFAULT;
			goto err;
		}
		if (!dek_is_persona(evt.persona_id)) {
			ret = -EFAULT;
			goto err;
		}
		ret = dek_on_user_removed(&evt);
		if (ret < 0) {
			dek_add_to_log(evt.persona_id, "Remove user failed");
			goto err;
		}
		dek_add_to_log(evt.persona_id, "Removed user");
		break;
	}
	/*
	 * Event when password changed.
	 *
	 * Encrypt priv_key with new password and store it.
	 */
	case DEK_ON_CHANGE_PASSWORD: {
		printk("dek: DEK_ON_CHANGE_PASSWORD << deprecated. SKIP\n");
		ret = 0;
		dek_add_to_log(0, "Changed password << deprecated");
		break;
	}
	default:
		printk("dek: case default\n");
		ret = -EINVAL;
		break;
	}

err:
	if (cleanup) {
		kfree(cleanup);
	}
	return ret;
}

static long dek_do_ioctl_req(unsigned int minor, unsigned int cmd,
		unsigned long arg) {
	long ret = 0;
	void __user *ubuf = (void __user *)arg;

	switch (cmd) {
	/*
	 * Request to generate DEK.
	 * Generate DEK and return to the user
	 */
	case DEK_GENERATE_DEK: {
		dek_arg_generate_dek req;

		printk("dek: DEK_GENERATE_DEK\n");

		if(copy_from_user(&req, ubuf, sizeof(req))) {
			printk("dek: can't copy from user\n");
			ret = -EFAULT;
			goto err;
		}
		dek_generate_dek(req.persona_id, &req.dek);
		if(copy_to_user(ubuf, &req, sizeof(req))) {
			printk("dek: can't copy to user\n");
			ret = -EFAULT;
			goto err;
		}
		break;
	}
	/*
	 * Request to encrypt given DEK.
	 *
	 * encrypt dek and return to the user
	 */
	case DEK_ENCRYPT_DEK: {
		dek_arg_encrypt_dek req;

		printk("dek: DEK_ENCRYPT_DEK\n");

		if(copy_from_user(&req, ubuf, sizeof(req))) {
			printk("dek: can't copy from user\n");
			ret = -EFAULT;
			goto err;
		}
		ret = dek_encrypt_dek(req.persona_id,
				&req.plain_dek, &req.enc_dek);
		if (ret < 0) {
			goto err;
		}
		req.enc_type = ret;
		ret = 0;
		if(copy_to_user(ubuf, &req, sizeof(req))) {
			printk("dek: can't copy to user\n");
			ret = -EFAULT;
			goto err;
		}
		break;
	}
	/*
	 * Request to decrypt given DEK.
	 *
	 * Decrypt dek and return to the user.
	 * When device is locked, private key is not available, so
	 * the driver must return EPERM or some kind of error.
	 */
	case DEK_DECRYPT_DEK: {
		dek_arg_decrypt_dek req;

		printk("dek: DEK_DECRYPT_DEK\n");

		if(copy_from_user(&req, ubuf, sizeof(req))) {
			printk("dek: can't copy from user\n");
			ret = -EFAULT;
			goto err;
		}
		ret = dek_decrypt_dek(req.persona_id,
				&req.enc_dek, &req.plain_dek, req.enc_type);
		if (ret < 0) {
			goto err;
		}
		if(copy_to_user(ubuf, &req, sizeof(req))) {
			printk("dek: can't copy to user\n");
			ret = -EFAULT;
			goto err;
		}
		break;
	}

	default:
		printk("dek: case default\n");
		ret = -EINVAL;
		break;
	}

	return ret;
err:
	return ret;
}

static long dek_do_ioctl_kek(unsigned int minor, unsigned int cmd,
		unsigned long arg) {
	long ret = 0;
	void __user *ubuf = (void __user *)arg;
	int key_arr_idx = 0;

	switch (cmd) {
	case DEK_GET_ENC_KEK: {
		dek_arg_get_enc_kek req;

		printk("dek: DEK_GET_ENC_KEK\n");

		if(copy_from_user(&req, ubuf, sizeof(req))) {
			printk("dek: can't copy from user\n");
			ret = -EFAULT;
			goto err;
		}
		key_arr_idx = PERSONA_KEY_ARR_IDX(req.persona_id);

		if (mas_key[key_arr_idx].len > 0) {
			/*
			 * return master key as much as possible ( while unlocked )
			 */
			memcpy(req.key.buf, mas_key[key_arr_idx].buf, mas_key[key_arr_idx].len);
			req.key.len = mas_key[key_arr_idx].len;
			req.key.type = TYPE_MAS_KEK;
			printk("dek: mas_key len : %d\n", req.key.len);
		} else if (pub_key[key_arr_idx].len > 0) {
			memcpy(req.key.buf, pub_key[key_arr_idx].buf, pub_key[key_arr_idx].len);
			req.key.len = pub_key[key_arr_idx].len;
			req.key.type = TYPE_PUB_KEK;
			printk("dek: pub_key len : %d\n", req.key.len);
		} else {
			printk("dek: KEK encryption key not available\n");
			ret = -ENXIO;
			goto err;
		}

		if(copy_to_user(ubuf, &req, sizeof(req))) {
			printk("dek: can't copy to user\n");
			memset(&req, 0, sizeof(dek_arg_get_enc_kek));
			ret = -EFAULT;
			goto err;
		}
		memset(&req, 0, sizeof(dek_arg_get_enc_kek));
		break;
	}
	case DEK_GET_DEC_KEK: {
		dek_arg_get_dec_kek req;
		int requested_type = 0;

		printk("dek: DEK_GET_DEC_KEK\n");

		if(copy_from_user(&req, ubuf, sizeof(req))) {
			printk("dek: can't copy from user\n");
			ret = -EFAULT;
			goto err;
		}
		key_arr_idx = PERSONA_KEY_ARR_IDX(req.persona_id);
		requested_type = req.type;
		req.key.len = 0;
		req.key.type = -1;

		switch(requested_type) {
		case DEK_RSA_ENC:
			if (priv_key[key_arr_idx].len > 0) {
				memcpy(req.key.buf, priv_key[key_arr_idx].buf, priv_key[key_arr_idx].len);
				req.key.len = priv_key[key_arr_idx].len;
				req.key.type = TYPE_PRIV_KEK;
				printk("dek: priv_key len : %d\n", req.key.len);
			} else {
				printk("dek: priv_key not-available\n");
				ret = -EIO;
				goto err;
			}
			break;
		case DEK_AES_ENC:
			if (mas_key[key_arr_idx].len > 0) {
				memcpy(req.key.buf, mas_key[key_arr_idx].buf, mas_key[key_arr_idx].len);
				req.key.len = mas_key[key_arr_idx].len;
				req.key.type = TYPE_MAS_KEK;
				printk("dek: mas_key len : %d\n", req.key.len);
			}else{
				printk("dek: mas_key not-available\n");
				ret = -EIO;
				goto err;
			}
			break;
		default:
			printk("dek: invalid key length\n");
			ret = -EINVAL;
			goto err;
			break;
		}

		if(copy_to_user(ubuf, &req, sizeof(req))) {
			printk("dek: can't copy to user\n");
			memset(&req, 0, sizeof(dek_arg_get_dec_kek));
			ret = -EFAULT;
			goto err;
		}
		memset(&req, 0, sizeof(dek_arg_get_dec_kek));
		break;
	}
	default:
		printk("dek: case default\n");
		ret = -EINVAL;
		break;
	}

	return ret;
err:
	return ret;
}


static long dek_ioctl_evt(struct file *file,
		unsigned int cmd, unsigned long arg)
{
	unsigned int minor;
	printk("dek: dek_ioctl_evt\n");

	minor = iminor(file->f_path.dentry->d_inode);

	return dek_do_ioctl_evt(minor, cmd, arg);
}

static long dek_ioctl_req(struct file *file,
		unsigned int cmd, unsigned long arg)
{
	unsigned int minor;
	printk("dek: dek_ioctl_req\n");

	minor = iminor(file->f_path.dentry->d_inode);

	return dek_do_ioctl_req(minor, cmd, arg);
}

static long dek_ioctl_kek(struct file *file,
		unsigned int cmd, unsigned long arg)
{
	unsigned int minor;
	printk("dek: dek_ioctl_kek\n");

	minor = iminor(file->f_path.dentry->d_inode);

	return dek_do_ioctl_kek(minor, cmd, arg);
}

/*
 * DAR engine log
 */

static int dek_open_log(struct inode *inode, struct file *file)
{
	printk("dek: dek_open_log\n");
	return 0;
}

static int dek_release_log(struct inode *ignored, struct file *file)
{
	printk("dek: dek_release_log\n");
	return 0;
}

static ssize_t dek_read_log(struct file *file, char * buffer, size_t len, loff_t *off)
{
	struct log_struct *tmp = NULL;

	printk("dek: dek_read_log, len=%d, off=%ld, buffer_count=%d\n",
			len, (long int)*off, log_count);

	if (log_count == 0) {
		printk("dek: process %i (%s) going to sleep\n",
				current->pid, current->comm);
		wait_event_interruptible(wq, flag != 0);
	}
	flag = 0;

	if (!list_empty(&log_buffer.list)) {
		spin_lock(&log_buffer.list_lock);
		tmp = list_first_entry(&log_buffer.list, struct log_struct, list);
		if (tmp != NULL) {
			if(copy_to_user(buffer, tmp->buf, tmp->len)) {
				printk("dek: dek_read_log, copy_to_user fail\n");
				spin_unlock(&log_buffer.list_lock);
				return -EFAULT;
			}
			len = tmp->len;
			*off = len;

			list_del(&tmp->list);
			spin_unlock(&log_buffer.list_lock);
			kfree(tmp);
			log_count--;
		}
	} else {
		printk("dek: dek_read_log, list empty\n");
		len = 0;
	}

	return len;
}

static void dek_add_to_log(int persona_id, char * buffer) {
	struct timespec ts;
	struct log_struct *tmp = (struct log_struct*)kmalloc(sizeof(struct log_struct), GFP_KERNEL);

	if (tmp) {
		INIT_LIST_HEAD(&tmp->list);

		getnstimeofday(&ts);
		tmp->len = sprintf(tmp->buf, "%ld.%.3ld|%d|%s|%d|%s\n",
				(long)ts.tv_sec,
				(long)ts.tv_nsec / 1000000,
				current->pid,
				current->comm,
				persona_id,
				buffer);

		spin_lock(&log_buffer.list_lock);
		list_add_tail(&(tmp->list), &(log_buffer.list));
		spin_unlock(&log_buffer.list_lock);
		log_count++;

		if (log_count > DEK_LOG_COUNT) {
			printk("dek: dek_add_to_log - exceeded DEK_LOG_COUNT\n");
			spin_lock(&log_buffer.list_lock);
			tmp = list_first_entry(&log_buffer.list, struct log_struct, list);
			list_del(&tmp->list);
			spin_unlock(&log_buffer.list_lock);
			kfree(tmp);
			log_count--;
		}

		printk("dek: process %i (%s) awakening the readers, log_count=%d\n",
				current->pid, current->comm, log_count);
		flag = 1;
		wake_up_interruptible(&wq);
	} else {
		printk("dek: dek_add_to_log - failed to allocate buffer\n");
	}
}

const struct file_operations dek_fops_evt = {
		.owner = THIS_MODULE,
		.open = dek_open_evt,
		.release = dek_release_evt,
		.unlocked_ioctl = dek_ioctl_evt,
		.compat_ioctl = dek_ioctl_evt,
};

static struct miscdevice dek_misc_evt = {
		.minor = MISC_DYNAMIC_MINOR,
		.name = "dek_evt",
		.fops = &dek_fops_evt,
};

const struct file_operations dek_fops_req = {
		.owner = THIS_MODULE,
		.open = dek_open_req,
		.release = dek_release_req,
		.unlocked_ioctl = dek_ioctl_req,
		.compat_ioctl = dek_ioctl_req,
};

static struct miscdevice dek_misc_req = {
		.minor = MISC_DYNAMIC_MINOR,
		.name = "dek_req",
		.fops = &dek_fops_req,
};

const struct file_operations dek_fops_log = {
		.owner = THIS_MODULE,
		.open = dek_open_log,
		.release = dek_release_log,
		.read = dek_read_log,
};

static struct miscdevice dek_misc_log = {
		.minor = MISC_DYNAMIC_MINOR,
		.name = "dek_log",
		.fops = &dek_fops_log,
};


const struct file_operations dek_fops_kek = {
		.owner = THIS_MODULE,
		.open = dek_open_kek,
		.release = dek_release_kek,
		.unlocked_ioctl = dek_ioctl_kek,
		.compat_ioctl = dek_ioctl_kek,
};

static struct miscdevice dek_misc_kek = {
		.minor = MISC_DYNAMIC_MINOR,
		.name = "dek_kek",
		.fops = &dek_fops_kek,
};


static int __init dek_init(void) {
	int ret;
	int i;

	ret = misc_register(&dek_misc_evt);
	if (unlikely(ret)) {
		printk("dek: failed to register misc_evt device!\n");
		return ret;
	}
	ret = misc_register(&dek_misc_req);
	if (unlikely(ret)) {
		printk("dek: failed to register misc_req device!\n");
		return ret;
	}

	ret = misc_register(&dek_misc_log);
	if (unlikely(ret)) {
		printk("dek: failed to register misc_log device!\n");
		return ret;
	}

	ret = misc_register(&dek_misc_kek);
	if (unlikely(ret)) {
		printk("dek: failed to register misc_kek device!\n");
		return ret;
	}

	for(i = 0; i < DEK_MAX_PERSONA; i++){
		memset(&pub_key[i], 0, sizeof(kek));
		memset(&priv_key[i], 0, sizeof(kek));
		memset(&mas_key[i], 0, sizeof(kek));
		tfm[i] = NULL;
	}

	INIT_LIST_HEAD(&log_buffer.list);
	spin_lock_init(&log_buffer.list_lock);
	init_waitqueue_head(&wq);

	printk("dek: initialized\n");
	dek_add_to_log(000, "Initialized");

	return 0;
}

static void __exit dek_exit(void)
{
	printk("dek: unloaded\n");
}

module_init(dek_init)
module_exit(dek_exit)

MODULE_LICENSE("GPL");
