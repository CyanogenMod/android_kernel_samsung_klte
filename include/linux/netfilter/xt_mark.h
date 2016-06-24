#ifndef _XT_MARK_H
#define _XT_MARK_H

#include <linux/types.h>

struct xt_mark_tginfo2 {
	__u32 mark, mask;
};

struct xt_mark_mtinfo1 {
	__u32 mark, mask;
	__u8 invert;
};

// ------------- START of KNOX_VPN ------------------//

/* KNOX framework uses mark value 100 to 500 
 * when the special meta data is added
 * This will indicate to the kernel code that
 * it needs to append meta data to the packets
 */

#define META_MARK_BASE_LOWER 100
#define META_MARK_BASE_UPPER 500

/* Structure to hold metadata values
 * intended for VPN clients to make 
 * more intelligent decisions
 * when the KNOX meta mark 
 * feature is enabled
 */

struct skb_meta_param {
	uid_t uid;
	pid_t pid;
};

// ------------- END of KNOX_VPN -------------------//

#endif /*_XT_MARK_H*/
