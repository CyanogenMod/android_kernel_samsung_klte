/*
 *  Copyright (C) 2013, Samsung Electronics Co. Ltd. All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */


#include	"sec_filter.h"
#include	"tcp_track.h"
#include	"url_parser.h"

#define ALLOWED_ID     5001

static  dev_t           url_ver;
static  struct  cdev    url_cdev;
static  struct  class   *url_class  = NULL;

static  DECLARE_WAIT_QUEUE_HEAD(user_noti_Q);
static  tcp_Info_Manager    *getting_TrackInfo= NULL;
static  tcp_Info_Manager    *notifying_TrackInfo = NULL;
static  tcp_Info_Manager    *notified_TrackInfo = NULL;
static  tcp_Info_Manager    *rejected_TrackInfo	= NULL;
static  char                *exceptionURL       = NULL;
static  atomic_t		totalReference	= ATOMIC_INIT(0);
static  unsigned long       resetTime               = 0;
char    *errorMsg   = NULL;
int     errMsgSize  = 0;
int     filterMode  = FILTER_MODE_OFF;

#ifdef CONFIG_SEC_NET_FILTER
int nfqnl_enqueue_packet(struct nf_queue_entry *entry, unsigned int queuenum);
#endif

//  sec_filter driver open function
int sec_url_filter_open(struct inode *inode, struct file *filp)
{
    atomic_inc(&totalReference);
    return 0;
}

//  sec_filter driver release function
int sec_url_filter_release( struct inode *inode, struct file *filp)
{
     if (atomic_dec_and_test(&totalReference))
    {
    	if (filterMode != FILTER_MODE_OFF)
    	{
            resetTime   = get_jiffies_64()+60*HZ;
            filterMode  = FILTER_MODE_CLOSING;
    	}
        wake_up_interruptible(&user_noti_Q);
        clean_tcp_TrackInfos(getting_TrackInfo);
        clean_tcp_TrackInfos(rejected_TrackInfo);
        clean_tcp_TrackInfos(notifying_TrackInfo);
        clean_tcp_TrackInfos(notified_TrackInfo);
        SEC_FREE(exceptionURL);
        SEC_FREE(errorMsg);
        errMsgSize  = 0;
        printk(KERN_ALERT "SEC_URL_FILTER : FILE HANDLE IS 0\r\n");
    }
   return 0;
}

//  sec_filter driver write function
ssize_t sec_url_filter_write( struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    int	result = -EIO;
    if ((buf != NULL) && (count >4))
    {
        short   version = *(short *)buf;
        int     cmd     = *(int *)(buf+sizeof(short));
        char    *data   = (char *)(buf+sizeof(short)+sizeof(int));
        {
            if (version == 0)
            {
                switch(cmd)
                {
                    case SET_FILTER_MODE:   // Turn On and Off filtering.
                    {
                        filterMode    = *(int *)data;
                        result      = count;
                        if (filterMode == FILTER_MODE_OFF)
                        {
                            wake_up_interruptible(&user_noti_Q);
                            clean_tcp_TrackInfos(getting_TrackInfo);
                            clean_tcp_TrackInfos(rejected_TrackInfo);
                            clean_tcp_TrackInfos(notifying_TrackInfo);
                            clean_tcp_TrackInfos(notified_TrackInfo);
                            SEC_FREE(exceptionURL);
                            SEC_FREE(errorMsg);
                            errMsgSize  = 0;
                        }
                        printk(KERN_INFO "SEC_URL_Filter : Mode is %d\n", filterMode);
                    }
                    break;
                    case SET_USER_SELECT:   //version 2, id 4, choice 2
                    {
                        tcp_TrackInfo   *selectInfo = NULL;
                        int             id          = *((int *)(data));
                        int             choice      = *((int *)(data+sizeof(unsigned int)));
                        unsigned int    verdict     = NF_DROP;
                        struct nf_queue_entry *entry= NULL;
                        selectInfo	= find_tcp_TrackInfo_withID(notified_TrackInfo, id);
                        if (selectInfo != NULL)
                        {
                            result  = count;
                            entry   = (struct nf_queue_entry *)selectInfo->q_entry;
                            selectInfo->q_entry = NULL;
                            selectInfo->status  = choice;
                            if (choice == ALLOW || ((filterMode%10) == FILTER_MODE_ON_RESPONSE))
                            {
                                verdict	= NF_ACCEPT;    //Response case should send packet
                            }
                            if (choice == BLOCK)
                            {
                                add_tcp_TrackInfo(rejected_TrackInfo, selectInfo);  // Add this node to Rejected List.
                            }
                            else
                            {
                                free_tcp_TrackInfo(selectInfo);
                            }
                            nf_reinject(entry, verdict);    // Reinject packet with the verdict
                        }
                        else
                        {
                            printk("SEC_URL_FILTER : NO SUCH ID\n");
                        }
                    }
                    break;
                    case    SET_EXCEPTION_URL:
                    {
                        int urlLen  = *((int *)(data));
                        SEC_FREE(exceptionURL);
                        exceptionURL    = SEC_MALLOC(urlLen+1);
                        if (exceptionURL != NULL)
                        {
                            memcpy(exceptionURL, (data+sizeof(int)), urlLen);
                            result  = count;
                        }
                    }
                    break;
                    case    SET_ERROR_MSG:
                    {
                        int msgLen  = *((int *)(data));
                        SEC_FREE(errorMsg);
                        errMsgSize  = 0;
                        errorMsg    = SEC_MALLOC(msgLen+1);
                        if (errorMsg != NULL)
                        {
                            memcpy(errorMsg, (data+sizeof(int)), msgLen);
                            errMsgSize = msgLen;
                            result  = count;
                        }
                    }
                    break;
                }
            }
        }
    }
    return result;
}

// sec filter read function
ssize_t	sec_url_filter_read( struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    int             result      = -EIO;
    tcp_TrackInfo   *notifyInfo = NULL;
    int             leftLen     = 0;
    int             writeCount  = count;
    int             notifyFlag  = 0;
    
    if (buf != NULL)
    {
        while (filterMode)
        {
            unsigned long   flags = 0;
            SEC_spin_lock_irqsave(&notifying_TrackInfo->tcp_info_lock, flags);
            notifyInfo = notifying_TrackInfo->head;
            SEC_spin_unlock_irqrestore(&notifying_TrackInfo->tcp_info_lock, flags);
            if (notifyInfo != NULL)
            {
                result  =   access_ok( VERIFY_WRITE, (void *)buf, count);	// This buffer should be verified because it is already blocked buffer.
                if (result != 0)
                {
                    leftLen = notifyInfo->urlLen - notifyInfo->notify_Index;    // Get left size
                    if ( leftLen <= count)              // If buffer is enough, it would be last block
                    {
                        writeCount  = leftLen;
                        notifyFlag  = 1;
                    }
                    result  = copy_to_user(buf, &(notifyInfo->url[notifyInfo->notify_Index]), writeCount);      // Check the result because it is blocked function
                    if (result == 0)
                    {
                        result  = writeCount;
                        notifyInfo->notify_Index += writeCount;
                        if (notifyFlag == 1)
                        {
                            notifyInfo->status = NOTIFIED;
                            notifyInfo = getFirst_tcp_TrackInfo(notifying_TrackInfo);
                            add_tcp_TrackInfo(notified_TrackInfo, notifyInfo);
                        }
                    }
                }
                break;      // Return result
            }
            else
            {
                interruptible_sleep_on(&user_noti_Q);
            }
        }
    }
    return (ssize_t)result;
}

unsigned int sec_url_filter_hook( unsigned int hook_no,
     struct sk_buff *skb,
     const struct net_device *dev_in,
     const struct net_device *dev_out,
     int (*handler)(struct sk_buff *))
{
    unsigned int    verdict = NF_ACCEPT;
    if (filterMode)
    {
        if (skb != NULL)
        {
            struct iphdr *iph = (struct iphdr*) ip_hdr(skb);
            if (iph != NULL)
            {
                if (iph->protocol == 6)	// TCP case
                {
                    int             delFlag     = 0;
                    struct tcphdr   *tcph       = (struct tcphdr *)skb_transport_header(skb);
                    tcp_TrackInfo   *rejected   = NULL;

                    if (filterMode == FILTER_MODE_CLOSING)
                    {
                    	if (time_before((unsigned long)get_jiffies_64(), resetTime))
                    	{
                    	    verdict    = NF_DROP;
                    	}
                    	else
                    	{
                    	    filterMode = FILTER_MODE_OFF;
                    	}
                        return verdict;
                    }

                    if (tcph!= NULL)
                    {
                        delFlag = (tcph->fin || tcph->rst);
                    }
                    verdict     = NF_QUEUE_NR(5001);
                    rejected    = find_tcp_TrackInfo(rejected_TrackInfo, skb, delFlag);     // If this is FIN packet, remove TCP Info.
                    if (rejected != NULL)   // This is Rejected
                    {
                        verdict = NF_DROP;
                    }
                    if (delFlag == 1)
                    {
                        tcp_TrackInfo   *gettingNode    = NULL;
                        verdict = NF_ACCEPT;    // FIN, RST can go out.
                        free_tcp_TrackInfo(rejected);
                        gettingNode = find_tcp_TrackInfo(getting_TrackInfo, skb, 1);    // Find previous TCP Track Info and remove from list
                        free_tcp_TrackInfo(gettingNode);
                    }
                }
            }
        }
    }
    return verdict;
}

int sec_url_filter_slow(struct nf_queue_entry *entry, unsigned int queuenum)
{
#ifdef CONFIG_SEC_NET_FILTER
    if (queuenum == ALLOWED_ID)
    {
#endif
    if (entry != NULL)
    {
        if (filterMode)
        {
            struct sk_buff  *skb            = entry->skb;
            char            *request        = NULL;
            tcp_TrackInfo   *gettingNode    = NULL;
            tcp_TrackInfo   *notifyNode     = NULL;

            if (skb != NULL)
            {
                struct iphdr *iph   = (struct iphdr*)ip_hdr(skb);
                if (iph != NULL)
                {
                    if (iph->protocol == 6)
                    {
                        struct tcphdr   *tcph = (struct tcphdr *)skb_transport_header(skb);
                        if (tcph!= NULL)
                        {
                            notifyNode  = find_tcp_TrackInfo(notifying_TrackInfo, skb, 0);
                            if (notifyNode != NULL)     // If this is already notified to user, drop it.
                            {
                                unsigned int verdict    = NF_DROP;
                                nf_reinject(entry, verdict);
                                return 0;
                            }
                            gettingNode	= find_tcp_TrackInfo(getting_TrackInfo, skb, 1);    // Find previous TCP Track Info and remove from list
                            if (gettingNode == NULL)            // No previous Info
                            {
                                gettingNode = isURL(skb);       // If this is URL Request then make TCP Track Info
                            }
                            if (gettingNode != NULL)
                            {
                                request	= getPacketData(skb, gettingNode);  // Get Packet
                                if (request != NULL)                        // If there is packet data
                                {
                                    getURL(request, gettingNode);           // Get URL	and update status
                                    kfree(request);
                                    request	= NULL;
                                    if (gettingNode->status == GOT_FULL_URL)		// If get Full URL, then make notify info
                                    {
                                        makeNotifyInfo(gettingNode);
                                        if ((exceptionURL != NULL) && (gettingNode->url !=NULL))
                                        {
                                            if (strstr(&gettingNode->url[sizeof(URL_Info)], exceptionURL) != NULL)  // This is exception URL
                                            {
                                                free_tcp_TrackInfo(gettingNode);
                                                nf_reinject(entry, NF_ACCEPT);
                                                return 0;
                                            }
                                        }
                                        gettingNode->q_entry = entry;
                                        add_tcp_TrackInfo(notifying_TrackInfo, gettingNode);
                                        wake_up_interruptible(&user_noti_Q);    // Wake Up read function
                                        return 0;
                                    }
                                }
                                add_tcp_TrackInfo_ToHead(getting_TrackInfo, gettingNode);
                            }
                        }
                    }
                }
            }
        }
        nf_reinject(entry, NF_ACCEPT);
    }
#ifdef CONFIG_SEC_NET_FILTER
    }
	else
    {
	return nfqnl_enqueue_packet(entry,  queuenum);
    }
#endif
    return 0;
}


unsigned int sec_url_filter_recv_hook( unsigned int hook_no,
     struct sk_buff *skb,
     const struct net_device *dev_in,
     const struct net_device *dev_out,
     int (*handler)(struct sk_buff *))
{
    unsigned int    verdict = NF_ACCEPT;
    if ((filterMode == FILTER_MODE_ON_RESPONSE) ||((filterMode == FILTER_MODE_ON_RESPONSE_REFER)))
    {
        if (skb != NULL)
        {
            struct iphdr *iph = (struct iphdr*) ip_hdr(skb);
            if (iph != NULL)
            {
                if (iph->protocol == 6) // TCP case
                {
                    tcp_TrackInfo   *rejected   = NULL;
                    rejected = find_tcp_TrackInfo_Reverse(rejected_TrackInfo, skb); // If this is FIN packet, remove TCP Info.
                    if (rejected != NULL)   // This is Rejected
                    {
                        change_tcp_Data(skb);
                    }
                }
            }
        }
    }
    return verdict;
}

static struct nf_queue_handler sec_url_queue_handler = {
    .name = SEC_MODULE_NAME,
    .outfn = sec_url_filter_slow
};

static struct nf_hook_ops sec_url_filter = {
    .hook       = sec_url_filter_hook,
    .pf         = PF_INET,
    .hooknum    = NF_INET_LOCAL_OUT,
    .priority   = NF_IP_PRI_FIRST
};


static struct nf_hook_ops sec_url_recv_filter = {
    .hook       = sec_url_filter_recv_hook,
    .pf         = PF_INET,
    .hooknum    = NF_INET_LOCAL_IN,
    .priority   = NF_IP_PRI_FIRST
};

static struct file_operations sec_url_filter_fops = {
    .owner      = THIS_MODULE,
    .read       = sec_url_filter_read,
    .write      = sec_url_filter_write,
    .open       = sec_url_filter_open,
    .release    = sec_url_filter_release
};

void    deInit_Managers(void)
{
    SEC_FREE(getting_TrackInfo);
    SEC_FREE(notifying_TrackInfo);
    SEC_FREE(notified_TrackInfo);
    SEC_FREE(rejected_TrackInfo);
    SEC_FREE(exceptionURL);
}

int	init_Managers(void)
{
    do
    {
        if ((getting_TrackInfo = create_tcp_Info_Manager()) == NULL)    break;
        if ((notifying_TrackInfo = create_tcp_Info_Manager()) == NULL)  break;
        if ((notified_TrackInfo = create_tcp_Info_Manager()) == NULL)   break;
        if ((rejected_TrackInfo = create_tcp_Info_Manager()) == NULL)   break;
        return 0;
    }while(0);
    return -1;
}

int nfilter_init (void)
{
    int     alloc_result            = -1;
    int     add_result              = -1;
    int     add_send_hook           = -1;
    struct	device	*device_result  = NULL;

    cdev_init(&url_cdev,	&sec_url_filter_fops );
    do
    {
        if (init_Managers() < 0) break;
        if ((alloc_result = alloc_chrdev_region(&url_ver, 0, 1, "url"))  < 0 ) break;
        if ((url_class = class_create(THIS_MODULE, "secfilter")) == NULL) break;
        if ((device_result = device_create( url_class, NULL, url_ver, NULL, "url" )) == NULL)   break;
        if ((add_result = cdev_add(&url_cdev, url_ver, 1)) <0) break;
        if ((add_send_hook =nf_register_hook( &sec_url_filter)) <0) break;
        if (nf_register_hook( &sec_url_recv_filter) <0) break;
        nf_register_queue_handler(PF_INET, &sec_url_queue_handler);
        return 0;
    }while(0);
    deInit_Managers();
    if (add_result == 0) cdev_del( &url_cdev );
    if (device_result != NULL) device_destroy(url_class, url_ver);
    if (url_class != NULL) class_destroy(url_class);
    if (alloc_result == 0) unregister_chrdev_region(url_ver, 1);
    if (add_send_hook == 0) nf_unregister_hook(&sec_url_filter);
    printk(KERN_ALERT "SEC_URL_FILTER : FAIL TO INIT\n");
    return -1;
}

void nfilter_exit(void)
{
    filterMode = FILTER_MODE_OFF;
    cdev_del( &url_cdev );
    device_destroy( url_class, url_ver );
    class_destroy(url_class);
    unregister_chrdev_region( url_ver, 1 );
    nf_unregister_hook(&sec_url_filter);
    nf_unregister_hook(&sec_url_recv_filter);
    nf_unregister_queue_handlers(&sec_url_queue_handler);
    clean_tcp_TrackInfos(getting_TrackInfo);
    clean_tcp_TrackInfos(notifying_TrackInfo);
    clean_tcp_TrackInfos(notified_TrackInfo);
    clean_tcp_TrackInfos(rejected_TrackInfo);
    deInit_Managers();
    printk(KERN_ALERT "SEC_URL_FILTER : DEINITED\n");
}
#ifdef CONFIG_SEC_NET_FILTER
EXPORT_SYMBOL(sec_url_filter_slow);
#endif
module_init(nfilter_init);
module_exit(nfilter_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAMSUNG Electronics");
MODULE_DESCRIPTION("SEC FILTER DEVICE");
