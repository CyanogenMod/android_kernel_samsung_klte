/*
   'kmd.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Wed Jan 15 12:08:55 2014
*/
#include"cobf.h"
#ifdef _WIN32
#if defined( UNDER_CE) && defined( bb355) || ! defined( bb356)
#define bb354 1
#define bb330 1
#else
#define bb352 bb334
#define bb351 1
#define bb340 1
#endif
#define bb347 1
#include"uncobf.h"
#include<ndis.h>
#include"cobf.h"
#ifdef UNDER_CE
#include"uncobf.h"
#include<ndiswan.h>
#include"cobf.h"
#endif
#include"uncobf.h"
#include<stdio.h>
#include<basetsd.h>
#include"cobf.h"
bba bbs bbl bbf, *bb1;bba bbs bbe bbq, *bb94;bba bb135 bb123, *bb332;
bba bbs bbl bb39, *bb72;bba bbs bb135 bbk, *bb59;bba bbe bbu, *bb134;
bba bbh bbf*bb89;
#ifdef bb311
bba bbd bb60, *bb122;
#endif
#else
#include"uncobf.h"
#include<linux/module.h>
#include<linux/ctype.h>
#include<linux/time.h>
#include<linux/slab.h>
#include"cobf.h"
#ifndef bb120
#define bb120
#ifdef _WIN32
#include"uncobf.h"
#include<wtypes.h>
#include"cobf.h"
#else
#ifdef bb119
#include"uncobf.h"
#include<linux/types.h>
#include"cobf.h"
#else
#include"uncobf.h"
#include<stddef.h>
#include<sys/types.h>
#include"cobf.h"
#endif
#endif
#ifdef _WIN32
bba bb113 bb249;
#else
bba bbe bbu, *bb134, *bb236;
#define bb201 1
#define bb202 0
bba bb270 bb211, *bb268, *bb234;bba bbe bb207, *bb217, *bb212;bba bbs
bbq, *bb94, *bb223;bba bb6 bb274, *bb265;bba bbs bb6 bb280, *bb254;
bba bb6 bb116, *bb285;bba bbs bb6 bb63, *bb264;bba bb63 bb242, *bb229
;bba bb63 bb267, *bb235;bba bb116 bb113, *bb240;bba bb227 bb210;bba
bb255 bb123;bba bb245 bb83;bba bb115 bb118;bba bb115 bb272;
#ifdef bb226
bba bb288 bb39, *bb72;bba bb241 bbk, *bb59;bba bb253 bbd, *bb29;bba
bb208 bb56, *bb112;
#else
bba bb224 bb39, *bb72;bba bb291 bbk, *bb59;bba bb238 bbd, *bb29;bba
bb262 bb56, *bb112;
#endif
bba bb39 bbf, *bb1, *bb271;bba bbk bb228, *bb251, *bb277;bba bbk bb231
, *bb260, *bb225;bba bbd bb60, *bb122, *bb248;bba bb83 bb36, *bb279, *
bb292;bba bbd bb232, *bb213, *bb243;bba bb118 bb281, *bb269, *bb275;
bba bb56 bb222, *bb289, *bb247;
#define bb140 bbb
bba bbb*bb205, *bb77;bba bbh bbb*bb290;bba bbl bb252;bba bbl*bb259;
bba bbh bbl*bb82;
#if defined( bb119)
bba bbe bb114;
#endif
bba bb114 bb20;bba bb20*bb215;bba bbh bb20*bb187;
#if defined( bb282) || defined( bb209)
bba bb20 bb37;bba bb20 bb111;
#else
bba bbl bb37;bba bbs bbl bb111;
#endif
bba bbh bb37*bb278;bba bb37*bb246;bba bb60 bb257, *bb261;bba bbb*
bb106;bba bb106*bb258;
#define bb263( bb35) bbi bb35##__ { bbe bb230; }; bba bbi bb35##__  * \
 bb35
bba bbi{bb36 bb191,bb216,bb284,bb276;}bb266, *bb220, *bb273;bba bbi{
bb36 bb8,bb193;}bb244, *bb250, *bb237;bba bbi{bb36 bb206,bb221;}bb286
, *bb233, *bb214;
#endif
bba bbh bbf*bb89;
#endif
bba bbf bb103;
#define IN
#define OUT
#ifdef _DEBUG
#define bb145( bbc) bb32( bbc)
#else
#define bb145( bbc) ( bbb)( bbc)
#endif
bba bbe bb161, *bb173;
#define bb287 0
#define bb315 1
#define bb299 2
#define bb319 3
#define bb357 4
bba bbe bb349;bba bbb*bb121;
#endif
#ifdef _WIN32
#ifndef UNDER_CE
#define bb31 bb341
#define bb43 bb338
bba bbs bb6 bb31;bba bb6 bb43;
#endif
#else
#endif
#ifdef _WIN32
bbb*bb128(bb31 bb47);bbb bb109(bbb* );bbb*bb137(bb31 bb159,bb31 bb47);
#else
#define bb128( bbc) bb146(1, bbc, bb139)
#define bb109( bbc) bb348( bbc)
#define bb137( bbc, bbn) bb146( bbc, bbn, bb139)
#endif
#ifdef _WIN32
#define bb32( bbc) bb339( bbc)
#else
#ifdef _DEBUG
bbe bb144(bbh bbl*bb95,bbh bbl*bb25,bbs bb239);
#define bb32( bbc) ( bbb)(( bbc) || ( bb144(# bbc, __FILE__, __LINE__ \
)))
#else
#define bb32( bbc) (( bbb)0)
#endif
#endif
bb43 bb302(bb43*bb320);
#ifndef _WIN32
bbe bb328(bbh bbl*bbg);bbe bb323(bbh bbl*bb19,...);
#endif
#ifdef _WIN32
bba bb343 bb97;
#define bb141( bbc) bb345( bbc)
#define bb143( bbc) bb358( bbc)
#define bb133( bbc) bb353( bbc)
#define bb132( bbc) bb333( bbc)
#else
bba bb350 bb97;
#define bb141( bbc) ( bbb)(  *  bbc = bb344( bbc))
#define bb143( bbc) (( bbb)0)
#define bb133( bbc) bb337( bbc)
#define bb132( bbc) bb342( bbc)
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbi{bbd bb9;bbd bb23[4 ];bbf bb101[64 ];}bb523;bbb bb1816(bb523*bbj
);bbb bb1311(bb523*bbj,bbh bbb*bb498,bbq bb9);bbb bb1819(bb523*bbj,
bbb*bb14);bbb bb1852(bbb*bb14,bbh bbb*bb5,bbq bb9);bbb bb1964(bbb*
bb14,bb82 bb5);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbi{bbd bb9;bbd bb23[5 ];bbf bb101[64 ];}bb525;bbb bb1794(bb525*bbj
);bbb bb1291(bb525*bbj,bbh bbb*bb5,bbq bb9);bbb bb1802(bb525*bbj,bbb*
bb14);bba bbi{bbd bb9;bbd bb23[8 ];bbf bb101[64 ];}bb531;bbb bb1818(
bb531*bbj);bbb bb1292(bb531*bbj,bbh bbb*bb5,bbq bb9);bbb bb1814(bb531
 *bbj,bbb*bb14);bba bbi{bbd bb9;bb56 bb23[8 ];bbf bb101[128 ];}bb461;
bbb bb1808(bb461*bbj);bbb bb1193(bb461*bbj,bbh bbb*bb5,bbq bb9);bbb
bb1835(bb461*bbj,bbb*bb14);bba bb461 bb911;bbb bb1797(bb911*bbj);bbb
bb1810(bb911*bbj,bbb*bb14);bbb bb1902(bbb*bb14,bbh bbb*bb5,bbq bb9);
bbb bb1866(bbb*bb14,bbh bbb*bb5,bbq bb9);bbb bb1849(bbb*bb14,bbh bbb*
bb5,bbq bb9);bbb bb1929(bbb*bb14,bbh bbb*bb5,bbq bb9);bbb bb2016(bbb*
bb14,bb82 bb5);bbb bb1965(bbb*bb14,bb82 bb5);bbb bb2025(bbb*bb14,bb82
bb5);bbb bb2018(bbb*bb14,bb82 bb5);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbi{bbd bb9;bbd bb23[5 ];bbf bb101[64 ];}bb529;bbb bb1801(bb529*bbj
);bbb bb1295(bb529*bbj,bbh bbb*bb498,bbq bb9);bbb bb1795(bb529*bbj,
bbb*bb14);bbb bb1924(bbb*bb14,bbh bbb*bb5,bbq bb9);bbb bb1973(bbb*
bb14,bb82 bb5);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbi{bbd bb9;bbd bb23[5 ];bbf bb101[64 ];}bb532;bbb bb1804(bb532*bbj
);bbb bb1331(bb532*bbj,bbh bbb*bb498,bbq bb9);bbb bb1838(bb532*bbj,
bbb*bb14);bbb bb1874(bbb*bb14,bbh bbb*bb5,bbq bb9);bbb bb2002(bbb*
bb14,bb82 bb5);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbb( *bb1059)(bbb*bbj);bba bbb( *bb838)(bbb*bbj,bbh bbb*bb5,bbq
bb9);bba bbb( *bb770)(bbb*bbj,bbb*bb14);bba bbi{bbe bb131;bbq bb38;
bbq bb390;bb1059 bb890;bb838 bb179;bb770 bb736;}bb449;bbb bb1856(
bb449*bbj,bbe bb131);bba bbi{bb449 bbn;bbf bbt[256 -bb12(bb449)];}
bb453;bbb bb1985(bb453*bbj,bbe bb131);bbb bb1992(bb453*bbj);bbb bb2020
(bb453*bbj,bbe bb131);bbb bb1983(bb453*bbj,bbh bbb*bb5,bbq bb9);bbb
bb1976(bb453*bbj,bbb*bb14);bbb bb1990(bbe bb131,bbb*bb14,bbh bbb*bb5,
bbq bb9);bbb bb2049(bbe bb131,bbb*bb14,bb82 bb5);bb82 bb1970(bbe bb131
);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbi{bb449 bbn;bbf bb537[(512 -bb12(bb449))/2 ];bbf bb1301[(512 -bb12
(bb449))/2 ];}bb494;bbb bb1961(bb494*bbj,bbe bb597);bbb bb2005(bb494*
bbj,bbh bbb*bb71,bbq bb142);bbb bb2109(bb494*bbj,bbe bb597,bbh bbb*
bb71,bbq bb142);bbb bb1989(bb494*bbj,bbh bbb*bb5,bbq bb9);bbb bb2007(
bb494*bbj,bbb*bb14);bbb bb2108(bbe bb597,bbh bbb*bb71,bbq bb142,bbb*
bb14,bbh bbb*bb5,bbq bb9);bbb bb2192(bbe bb597,bb82 bb71,bbb*bb14,
bb82 bb5);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbi{bbq bb454;bbd bb422[4 * (14 +1 )];}bb363;bbb bb1097(bb363*bbj,
bbh bbb*bb71,bbq bb142);bbb bb1736(bb363*bbj,bbh bbb*bb71,bbq bb142);
bbb bb1036(bb363*bbj,bbb*bb14,bbh bbb*bb5);bbb bb1775(bb363*bbj,bbb*
bb14,bbh bbb*bb5);
#ifdef __cplusplus
}
#endif
bba bbi{bb363 bb2119;bbq bb9;bbf bb101[16 ];bbf bb1928[16 ];bbf bb1926[
16 ];bbf bb1842[16 ];}bb943;bbb bb2042(bb943*bbj,bbh bbb*bb71,bbq bb142
);bbb bb2094(bb943*bbj,bbh bbb*bb5,bbq bb9);bbb bb2104(bb943*bbj,bbb*
bb14);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbb( *bb1865)(bbb*bbj,bbh bbb*bb71,bbq bb142);bba bbi{bbe bb131;
bbq bb38;bbq bb390;bb1865 bb890;bb838 bb179;bb770 bb736;}bb2031;bba
bbi{bb2031 bbn;bbf bbt[512 ];}bb528;bbb bb2146(bb528*bbj,bbe bb131);
bbb bb2170(bb528*bbj,bbh bbb*bb71,bbq bb142);bbb bb1833(bb528*bbj,bbe
bb131,bbh bbb*bb71,bbq bb142);bbb bb1243(bb528*bbj,bbh bbb*bb5,bbq bb9
);bbb bb1815(bb528*bbj,bbb*bb14);bbb bb2167(bbe bb131,bbh bbb*bb71,
bbq bb142,bbb*bb14,bbh bbb*bb5,bbq bb9);bbb bb2197(bbe bb131,bb82 bb71
,bbb*bb14,bb82 bb5);bb82 bb2207(bbe bb131);
#ifdef __cplusplus
}
#endif
bbb bb2146(bb528*bbj,bbe bb131){bb2031 bbn={0 };bbn.bb131=bb131;bb296(
bb131&0xff00 ){bb15 0x1000 :{bb494*bb2238=(bb494* )bbj->bbt;bb1961(
bb2238,bb131&0xff );bbn.bb38=bb2238->bbn.bb38;bbn.bb390=bb2238->bbn.
bb390;}bbn.bb890=(bb1865)bb2005;bbn.bb179=(bb838)bb1989;bbn.bb736=(
bb770)bb2007;bb21;bb15 0x2000 :bbn.bb38=16 ;bbn.bb390=16 ;bbn.bb890=(
bb1865)bb2042;bbn.bb179=(bb838)bb2094;bbn.bb736=(bb770)bb2104;bb21;
bb416:bb32(0 );}bbj->bbn=bbn;}bbb bb2170(bb528*bbj,bbh bbb*bb71,bbq
bb142){bbj->bbn.bb890(bbj->bbt,bb71,bb142);}bbb bb1833(bb528*bbj,bbe
bb131,bbh bbb*bb71,bbq bb142){bb2146(bbj,bb131);bb2170(bbj,bb71,bb142
);}bbb bb1243(bb528*bbj,bbh bbb*bb5,bbq bb9){bbj->bbn.bb179(bbj->bbt,
bb5,bb9);}bbb bb1815(bb528*bbj,bbb*bb14){bbj->bbn.bb736(bbj->bbt,bb14
);}bbb bb2167(bbe bb131,bbh bbb*bb71,bbq bb142,bbb*bb14,bbh bbb*bb5,
bbq bb9){bb528 bb96;bb1833(&bb96,bb131,bb71,bb142);bb1243(&bb96,bb5,
bb9);bb1815(&bb96,bb14);}bbb bb2197(bbe bb131,bb82 bb71,bbb*bb14,bb82
bb5){bb2167(bb131,bb71,(bbq)bb1305(bb71),bb14,bb5,(bbq)bb1305(bb5));}
bb82 bb2207(bbe bb131){bb41 bbl bbg[32 ];bb296(bb131&0xff00 ){bb15
0x1000 :bb1323(bbg,"\x48\x4d\x41\x43\x5f\x25\x73",bb1970(bb131&0xff ));
bb2 bbg;bb15 0x2000 :bb2"\x41\x45\x53\x5f\x58\x43\x42\x43";}bb2 bb90;}
