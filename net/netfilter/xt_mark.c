/*
 *	xt_mark - Netfilter module to match NFMARK value
 *
 *	(C) 1999-2001 Marc Boucher <marc@mbsi.ca>
 *	Copyright © CC Computer Consultants GmbH, 2007 - 2008
 *	Jan Engelhardt <jengelh@medozas.de>
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License version 2 as
 *	published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/skbuff.h>

#include <linux/netfilter/xt_mark.h>
#include <linux/netfilter/x_tables.h>

// ------------- START of KNOX_VPN ------------------//
#include <linux/types.h>
#include <net/sock.h>
#include <net/ip.h>
#include <linux/ip.h>
#include <linux/tcp.h>
// ------------- END of KNOX_VPN -------------------//

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marc Boucher <marc@mbsi.ca>");
MODULE_DESCRIPTION("Xtables: packet mark operations");
MODULE_ALIAS("ipt_mark");
MODULE_ALIAS("ip6t_mark");
MODULE_ALIAS("ipt_MARK");
MODULE_ALIAS("ip6t_MARK");

static unsigned int
mark_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_mark_tginfo2 *info = par->targinfo;
// ------------- START of KNOX_VPN ------------------//
	unsigned int metabufspace;
	unsigned char *temp_skb_partial = NULL;
	struct skb_meta_param *uh;
	struct iphdr iph;
	struct iphdr *iphlocal;
	uid_t localuid;
	pid_t localpid;
// ------------- END of KNOX_VPN -------------------//

	skb->mark = (skb->mark & ~info->mask) ^ info->mark;

/* The KNOX framework marks packets intended to a VPN client for special processing differently.
 * The marked packets hit special IP table rules and are routed back to user space using the TUN driver
 * for policy based treatment by the VPN client.
 * Some VPN clients can make more intelligent decisions based on the UID/PID information.
 * For such clients, we mark packets to be in the range >= META_MARK_BASE_LOWER and < META_MARK_BASE_UPPER.
 * When such packets are seen, we update the IP headers to carry UID/PID information
 * in the IP options - all other packets are ignored.
 * Also, see the comments above the individual steps taken in the code for details
 */

// ------------- START of KNOX_VPN ------------------//
	if (skb->mark >= META_MARK_BASE_LOWER
	    && skb->mark < META_MARK_BASE_UPPER) {
		metabufspace = sizeof(struct skb_meta_param);
		if (skb->sk != NULL) {
			/* Obtain UID/PID of the source of the packet */
			localuid = skb->sk->knox_uid;
			localpid = skb->sk->knox_pid;
			
			/* Backup the IP header */	
			memcpy(&iph, skb->data, sizeof(struct iphdr));
		
			/* Ensure IP options are not used already
			 * Typically we would check for ">" 
			 */
			if (iph.ihl != sizeof(struct iphdr)/4) {
				pr_err("KNOX: Seems like IP options are already in use - bailout - %d", iph.ihl);
				goto bailout;
			}
			
			/* Strip the IP header from the skb */
			temp_skb_partial = skb_pull(skb, sizeof(struct iphdr));

			if (NULL == temp_skb_partial) {
				pr_err("KNOX: Could not extract IP header from SKB - bailout");
				goto bailout;
			}
			
			/* Push the meta data structure into the packet first
			 * Once we stack the IP header on top of this,
			 * metadata automatically becomes IP options
			 */

			uh = (struct skb_meta_param *)skb_push(skb,
							       metabufspace);
			/* Update the metadata with required information */
			uh->uid = localuid;
			uh->pid = localpid;
			
			/* Update the IP header length to reflect the 
			 * additional metadata (since it is part of the options)
			 */

			iph.ihl = (sizeof(struct iphdr) + metabufspace) / 4;
			iph.tot_len += htons(metabufspace);
			iph.check = 0;
			ip_send_check (&iph);
			/* Push an IP header back into the skb */
			iphlocal =
			    (struct iphdr *)skb_push(skb, sizeof(struct iphdr));
			
			/* Update the IP header with the modified values */
			memcpy(iphlocal, &iph, sizeof(struct iphdr));
			skb_reset_network_header(skb);
		} else {
			pr_err
			    ("KNOX: In %s - Socket structure skb->sk is NULL", __FUNCTION__);
			goto bailout;
		}

	}
bailout:
// ------------- END of KNOX_VPN -------------------//
	return XT_CONTINUE;
}

static bool
mark_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_mark_mtinfo1 *info = par->matchinfo;

	return ((skb->mark & info->mask) == info->mark) ^ info->invert;
}

static struct xt_target mark_tg_reg __read_mostly = {
	.name           = "MARK",
	.revision       = 2,
	.family         = NFPROTO_UNSPEC,
	.target         = mark_tg,
	.targetsize     = sizeof(struct xt_mark_tginfo2),
	.me             = THIS_MODULE,
};

static struct xt_match mark_mt_reg __read_mostly = {
	.name           = "mark",
	.revision       = 1,
	.family         = NFPROTO_UNSPEC,
	.match          = mark_mt,
	.matchsize      = sizeof(struct xt_mark_mtinfo1),
	.me             = THIS_MODULE,
};

static int __init mark_mt_init(void)
{
	int ret;

	ret = xt_register_target(&mark_tg_reg);
	if (ret < 0)
		return ret;
	ret = xt_register_match(&mark_mt_reg);
	if (ret < 0) {
		xt_unregister_target(&mark_tg_reg);
		return ret;
	}
	return 0;
}

static void __exit mark_mt_exit(void)
{
	xt_unregister_match(&mark_mt_reg);
	xt_unregister_target(&mark_tg_reg);
}

module_init(mark_mt_init);
module_exit(mark_mt_exit);
