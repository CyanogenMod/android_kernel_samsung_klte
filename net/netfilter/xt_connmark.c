/*
 *	xt_connmark - Netfilter module to operate on connection marks
 *
 *	Copyright (C) 2002,2004 MARA Systems AB <http://www.marasystems.com>
 *	by Henrik Nordstrom <hno@marasystems.com>
 *	Copyright © CC Computer Consultants GmbH, 2007 - 2008
 *	Jan Engelhardt <jengelh@medozas.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/module.h>
#include <linux/skbuff.h>
#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_ecache.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter/xt_connmark.h>

// ------------- START of KNOX_VPN ------------------//
#include <linux/types.h>
#include <linux/netfilter/xt_mark.h>
#include <net/sock.h>
#include <net/ip.h>
#include <linux/ip.h>
#include <linux/tcp.h>
// ------------- END of KNOX_VPN -------------------//

MODULE_AUTHOR("Henrik Nordstrom <hno@marasystems.com>");
MODULE_DESCRIPTION("Xtables: connection mark operations");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_CONNMARK");
MODULE_ALIAS("ip6t_CONNMARK");
MODULE_ALIAS("ipt_connmark");
MODULE_ALIAS("ip6t_connmark");

static unsigned int
connmark_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_connmark_tginfo1 *info = par->targinfo;
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct;
	u_int32_t newmark;

// ------------- START of KNOX_VPN ------------------//
	unsigned int metabufspace;
	unsigned char *temp_skb_partial = NULL;
	struct skb_meta_param *uh;
	struct iphdr iph;
	struct iphdr *iphlocal;
	uid_t localuid;
	pid_t localpid;
// ------------- END of KNOX_VPN -------------------//

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NULL)
		return XT_CONTINUE;

	switch (info->mode) {
	case XT_CONNMARK_SET:
		newmark = (ct->mark & ~info->ctmask) ^ info->ctmark;
		if (ct->mark != newmark) {
			ct->mark = newmark;
			nf_conntrack_event_cache(IPCT_MARK, ct);
		}
		break;
	case XT_CONNMARK_SAVE:
		newmark = (ct->mark & ~info->ctmask) ^
		          (skb->mark & info->nfmask);
		if (ct->mark != newmark) {
			ct->mark = newmark;
			nf_conntrack_event_cache(IPCT_MARK, ct);
		}
		break;
	case XT_CONNMARK_RESTORE:
		newmark = (skb->mark & ~info->nfmask) ^
		          (ct->mark & info->ctmask);
		skb->mark = newmark;

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
		if (newmark >= META_MARK_BASE_LOWER
		    && newmark < META_MARK_BASE_UPPER) {
			metabufspace = sizeof(struct skb_meta_param);
			if (skb->sk != NULL) {
				/* Obtain UID/PID of the source of the packet */
				localuid = skb->sk->knox_uid;
				localpid = skb->sk->knox_pid;
				
				/* Backup the IP header */
				memcpy(&iph, skb->data,
				       sizeof(struct iphdr));

				/* Ensure IP options are not used already
				 * Typically we would check for ">" 
				 */
				if (iph.ihl != sizeof(struct iphdr) / 4) {
					pr_err
					    ("KNOX %s: Seems like IP options are already in use - bailout - %d",
					     __FUNCTION__, iph.ihl);
					goto bailout;
				}

				/* Strip the IP header from the skb */
				temp_skb_partial =
				    skb_pull(skb, sizeof(struct iphdr));
				if (NULL == temp_skb_partial) {
					pr_err
					    ("KNOX: Could not extract IP header from SKB - bailout");
					goto bailout;
				}
				/* Push the meta data structure into the packet first
				 * Once we stack the IP header on top of this,
				 * metadata automatically becomes IP options
				 */
				uh = (struct skb_meta_param *)
				    skb_push(skb, metabufspace);

				/* Update the metadata with required information */
				uh->uid = localuid;
				uh->pid = localpid;

				/* Update the IP header length to reflect the 
				 * additional metadata (since it is part of the options)
				 */
				iph.ihl =
				    (sizeof(struct iphdr) +
				     metabufspace) / 4;
				iph.tot_len += htons(metabufspace);
				iph.check = 0;
				ip_send_check (&iph);

				/* Push an IP header back into the skb */
				iphlocal =
				    (struct iphdr *)skb_push(skb,
							     sizeof
							     (struct
							      iphdr));

				/* Update the IP header with the modified values */
				memcpy(iphlocal, &iph,
				       sizeof(struct iphdr));
				skb_reset_network_header(skb);
			} else {
				pr_err
			    	("KNOX: In %s - Socket structure skb->sk is NULL", __FUNCTION__);
				goto bailout;
			}

		}
// ------------- END of KNOX_VPN -------------------//
		break;
	}
// ------------- START of KNOX_VPN ------------------//
bailout:
// ------------- END of KNOX_VPN -------------------//
	return XT_CONTINUE;
}

static int connmark_tg_check(const struct xt_tgchk_param *par)
{
	int ret;

	ret = nf_ct_l3proto_try_module_get(par->family);
	if (ret < 0)
		pr_info("cannot load conntrack support for proto=%u\n",
			par->family);
	return ret;
}

static void connmark_tg_destroy(const struct xt_tgdtor_param *par)
{
	nf_ct_l3proto_module_put(par->family);
}

static bool
connmark_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_connmark_mtinfo1 *info = par->matchinfo;
	enum ip_conntrack_info ctinfo;
	const struct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NULL)
		return false;

	return ((ct->mark & info->mask) == info->mark) ^ info->invert;
}

static int connmark_mt_check(const struct xt_mtchk_param *par)
{
	int ret;

	ret = nf_ct_l3proto_try_module_get(par->family);
	if (ret < 0)
		pr_info("cannot load conntrack support for proto=%u\n",
			par->family);
	return ret;
}

static void connmark_mt_destroy(const struct xt_mtdtor_param *par)
{
	nf_ct_l3proto_module_put(par->family);
}

static struct xt_target connmark_tg_reg __read_mostly = {
	.name           = "CONNMARK",
	.revision       = 1,
	.family         = NFPROTO_UNSPEC,
	.checkentry     = connmark_tg_check,
	.target         = connmark_tg,
	.targetsize     = sizeof(struct xt_connmark_tginfo1),
	.destroy        = connmark_tg_destroy,
	.me             = THIS_MODULE,
};

static struct xt_match connmark_mt_reg __read_mostly = {
	.name           = "connmark",
	.revision       = 1,
	.family         = NFPROTO_UNSPEC,
	.checkentry     = connmark_mt_check,
	.match          = connmark_mt,
	.matchsize      = sizeof(struct xt_connmark_mtinfo1),
	.destroy        = connmark_mt_destroy,
	.me             = THIS_MODULE,
};

static int __init connmark_mt_init(void)
{
	int ret;

	ret = xt_register_target(&connmark_tg_reg);
	if (ret < 0)
		return ret;
	ret = xt_register_match(&connmark_mt_reg);
	if (ret < 0) {
		xt_unregister_target(&connmark_tg_reg);
		return ret;
	}
	return 0;
}

static void __exit connmark_mt_exit(void)
{
	xt_unregister_match(&connmark_mt_reg);
	xt_unregister_target(&connmark_tg_reg);
}

module_init(connmark_mt_init);
module_exit(connmark_mt_exit);
