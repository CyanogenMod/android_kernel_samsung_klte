#include <crypto/internal/hash.h>
#include <crypto/scatterwalk.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/interrupt.h>
#include <linux/wakelock.h>
#include <linux/sched.h>
#include <linux/netlink.h>
#include <linux/net.h>
#include <net/netlink.h>
#include <net/sock.h>
#include <net/net_namespace.h>
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/audit.h>

#include <linux/version.h>
#include <sdp/pub_crypto_emul.h>

#define NETLINK_FIPS_CRYPTO 29
#define PUB_CRYPTO_PID_SET 3001
#define PUB_CRYPTO_RESULT 3002

#define RESULT_ARRAY_MAX_LEN 100

#define CRYPTO_MAX_TIMEOUT HZ/5

DEFINE_MUTEX(crypto_send_mutex);
DEFINE_MUTEX(crypto_receive_mutex);
DEFINE_MUTEX(crypto_data_ready_mutex);
static int user_fipscryptod_pid = 0;
static struct sock* crypto_sock = NULL;
static DECLARE_WAIT_QUEUE_HEAD(event_wait_crypto_results);

static char* PUB_CRYPTO_DEBUG = "SDP_PUB_CRYPTO: ";

static result_t g_result;
static u8 g_result_status = 0;

static int g_data_ready = 0;

static char* process_crypto_request(u8 opcode, char* send_msg, int send_msg_size, int* result_len, int* ret) {
	struct sk_buff *skb_in = NULL;
    struct sk_buff *skb_out = NULL;
    struct nlmsghdr *nlh = NULL;
	//char* rev_msg = NULL;
	char* result  = NULL;
	int rc = 0;
	int ready = 0;
	
	
	skb_in = nlmsg_new(send_msg_size, 0);
	if (!skb_in) {
		printk("%s %s Failed to allocate new skb: \n", PUB_CRYPTO_DEBUG, __FUNCTION__);
    	return NULL;
	}
	
	nlh = nlmsg_put(skb_in, 0, 0, NLMSG_DONE, send_msg_size, 0);
	NETLINK_CB(skb_in).dst_group = 0;
	memcpy(nlmsg_data(nlh), send_msg, send_msg_size);
	
	mutex_lock(&crypto_send_mutex);
	rc = nlmsg_unicast(crypto_sock, skb_in, user_fipscryptod_pid);
	mutex_unlock(&crypto_send_mutex);
	
    
	if (rc < 0) {
		printk(KERN_INFO "Error while sending bak to user, err id: %d\n", rc);
		return NULL;
	}
	
    //*******Reset the memory to hide plaintext!!!!!!
    memset(send_msg, 0, send_msg_size);
    
	{
		DECLARE_WAITQUEUE(wait, current);
		set_current_state(TASK_INTERRUPTIBLE);
		add_wait_queue(&event_wait_crypto_results, &wait);
	
	    while (!ready) {
			schedule_timeout_interruptible(CRYPTO_MAX_TIMEOUT);
			mutex_lock(&crypto_data_ready_mutex);
		    ready = g_data_ready;
		    g_data_ready = 0;
		    mutex_unlock(&crypto_data_ready_mutex);
		}
	
		set_current_state(TASK_RUNNING);
		remove_wait_queue(&event_wait_crypto_results, &wait);
   		
   		skb_out = skb_dequeue(&crypto_sock->sk_receive_queue);
   		
   		if(g_result_status == PUB_CRYPTO_ERROR) {
   			printk("%s %s FIPS_CRYPTO_ERROR!!!\n", PUB_CRYPTO_DEBUG, __FUNCTION__);
   			if(skb_out) {
	   			kfree_skb(skb_out);
   			}
   			result = NULL; goto out;
   		}
		
   		if(g_result.ret == -1) {
   			printk("%s %s failed to opcode(%d)!!!\n", PUB_CRYPTO_DEBUG, __FUNCTION__, opcode);
   			result = NULL; goto out;
   		}

   		if(opcode == OP_RSA_ENC || opcode == OP_RSA_DEC ||
   				opcode == OP_DH_DEC || opcode == OP_DH_ENC) {
   			*result_len = sizeof(dek_t);
   			result = kmalloc(*result_len, GFP_KERNEL);
   			memcpy(result, &(g_result.dek), *result_len);
   		}
   		*ret = (int)g_result.ret;
	}

out:
	mutex_unlock(&crypto_receive_mutex);
	return result;
}

   
static int crypto_recv_msg(struct sk_buff *skb, struct nlmsghdr *nlh)
{
	void			*data;
	u16			msg_type = nlh->nlmsg_type;
	u32 err = 0;
	struct audit_status	*status_get = NULL;
	u16 len = 0;

	g_result_status = 0;

	data = NLMSG_DATA(nlh);
	len = ntohs(*(uint16_t*) (data+1));
	switch (msg_type) {
		case PUB_CRYPTO_PID_SET:
			status_get   = (struct audit_status *)data;
			user_fipscryptod_pid = status_get->pid;
			printk("%s crypto_receive_msg: pid = %d\n", PUB_CRYPTO_DEBUG, user_fipscryptod_pid);
			mutex_unlock(&crypto_receive_mutex);
			break;
		case PUB_CRYPTO_RESULT:
		{
			result_t *result = (result_t *)data;

			switch (result->opcode) {
				case OP_RSA_ENC:
				case OP_RSA_DEC:
					g_result = *result;
					break;
				case OP_DH_DEC:
				case OP_DH_ENC:
					g_result = *result;
					break;
				default:
					g_result_status = PUB_CRYPTO_ERROR;
			}			
			mutex_lock(&crypto_data_ready_mutex);
			g_data_ready = 1;
			mutex_unlock(&crypto_data_ready_mutex);

			break;
		}
		default:
			g_result_status = PUB_CRYPTO_ERROR;
			break;
	}

	wake_up_interruptible(&event_wait_crypto_results);
	
	return err;
}

/*
 * Get message from skb.
 */
static void crypto_recv_skb(struct sk_buff *skb)
{
	struct nlmsghdr *nlh;
	int len;
	int err;

	nlh = nlmsg_hdr(skb);
	len = skb->len;

	err = crypto_recv_msg(skb, nlh);
}


/* Receive messages from netlink socket. */
static void crypto_recver(struct sk_buff  *skb)
{
        mutex_lock(&crypto_receive_mutex);
        crypto_recv_skb(skb);
        //mutex_unlock(&crypto_receive_mutex);
}


void rsa_encryptByPub(kek_t *pub_key, dek_t *in, dek_t *out){
	struct rsa_send_msg msg;
	dek_t *out_ret = NULL;
	int len = 0;
	int ret = 0;
	msg.opcode = OP_RSA_ENC;
	memcpy(&msg.key, (void *) pub_key, sizeof(kek_t));
	memcpy(&msg.in, (void *)in, sizeof(dek_t));
	
	out_ret = (dek_t *)process_crypto_request(msg.opcode, (char*)&msg, sizeof(struct rsa_send_msg), &len, &ret);
	if(!out_ret){
		out = NULL;
		return;
	}
	memcpy(out, out_ret, sizeof(dek_t));

	kfree(out_ret);
	return;
}

int rsa_decryptByPair(kek_t *pair, dek_t *in, dek_t *out){
	struct rsa_send_msg msg;
	dek_t *out_ret = NULL;
	int len = 0;
	int ret = 0;
	msg.opcode = OP_RSA_DEC;
	memcpy(&msg.key, (void *) pair, sizeof(kek_t));
	memcpy(&msg.in, (void *)in, sizeof(dek_t));

	out_ret = (dek_t *)process_crypto_request(msg.opcode, (char*)&msg, sizeof(struct rsa_send_msg), &len, &ret);
	
	if(!out_ret){
		out = NULL;
		return -1;
	}
	memcpy(out, out_ret, sizeof(dek_t));
	
	kfree(out_ret);
	return ret;
}

int dh_decryptEDEK(dek_t *edek, dek_t *dek, kek_t *kek){
	struct dh_send_msg r_msg;
	int len = 0;
	int ret = 0;
	dek_t *ret_dek = NULL;
	r_msg.opcode = OP_DH_DEC;
	
	//r_msg.userid = (u32)userid;
	memcpy(&r_msg.in, (void *) edek, sizeof(dek_t));
	memcpy(&r_msg.key, (void *) kek, sizeof(kek_t));
	
	ret_dek = (dek_t *)process_crypto_request(r_msg.opcode, (char*)&r_msg, sizeof(struct dh_send_msg), &len, &ret);
	if(!ret_dek){
		kek = NULL;
		return -1;
	}

	memcpy(dek, ret_dek, sizeof(dek_t));
	
	kfree(ret_dek);
	return ret;
}

int dh_encryptDEK(dek_t *dek, dek_t *edek, kek_t *kek){
	struct dh_send_msg r_msg;
	int len = 0;
	int ret = 0;
	dek_t *ret_dek = NULL;
	r_msg.opcode = OP_DH_ENC;
	//r_msg.userid = (u32)userid;
	memcpy(&r_msg.in, (void *) dek, sizeof(dek_t));
	memcpy(&r_msg.key, (void *) kek, sizeof(kek_t));
	
	ret_dek = (dek_t *)process_crypto_request(r_msg.opcode, (char*)&r_msg, sizeof(struct dh_send_msg), &len, &ret);
	if(!ret_dek){
		kek = NULL;
		return -1;
	}
	memcpy((char*)edek, (char*)ret_dek, sizeof(dek_t));

	kfree(ret_dek);
	return ret;
}

static int __init pub_crypto_mod_init(void) {

#if (LINUX_VERSION_CODE > KERNEL_VERSION(3,4,0))
	struct netlink_kernel_cfg cfg = {
		.input  = crypto_recver,
	};

	crypto_sock = netlink_kernel_create(&init_net, NETLINK_FIPS_CRYPTO, &cfg);
#else
	crypto_sock = netlink_kernel_create(&init_net, NETLINK_FIPS_CRYPTO, 0, crypto_recver, NULL, THIS_MODULE);
#endif

	if (!crypto_sock) {
		printk(KERN_CRIT "Failed to create Crypto Netlink Socket .. Exiting \n");
		return -ENOMEM;
	}
    printk("%s netlink socket is created successfully! \n", PUB_CRYPTO_DEBUG);
    return 0;
	
}

static void __exit pub_crypto_mod_exit(void) {
	
	/*
	if (crypto_sock && crypto_sock->sk_socket) {
        	sock_release(crypto_sock->sk_socket);
    }
    */
    netlink_kernel_release(crypto_sock);
}

module_init(pub_crypto_mod_init);
module_exit(pub_crypto_mod_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("FIPS Crypto Algorithm");

