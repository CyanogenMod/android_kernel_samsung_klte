/*
   'kmd.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Sun Nov 16 20:01:26 2014
*/
#include"cobf.h"
#ifdef _WIN32
#if defined( UNDER_CE) && defined( bb341) || ! defined( bb343)
#define bb335 1
#define bb351 1
#else
#define bb340 bb348
#define bb331 1
#define bb345 1
#endif
#define bb333 1
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
bba bbs bbl bbf, *bb1;bba bbs bbe bbq, *bb93;bba bb135 bb123, *bb358;
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
#ifndef bb116
#define bb116
#ifdef _WIN32
#include"uncobf.h"
#include<wtypes.h>
#include"cobf.h"
#else
#ifdef bb112
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
bba bb119 bb215;
#else
bba bbe bbu, *bb134, *bb282;
#define bb202 1
#define bb201 0
bba bb275 bb292, *bb279, *bb217;bba bbe bb246, *bb262, *bb285;bba bbs
bbq, *bb93, *bb253;bba bb5 bb266, *bb288;bba bbs bb5 bb265, *bb284;
bba bb5 bb113, *bb211;bba bbs bb5 bb63, *bb287;bba bb63 bb219, *bb240
;bba bb63 bb252, *bb261;bba bb113 bb119, *bb251;bba bb256 bb259;bba
bb277 bb123;bba bb218 bb83;bba bb117 bb114;bba bb117 bb206;
#ifdef bb208
bba bb209 bb39, *bb72;bba bb250 bbk, *bb59;bba bb205 bbd, *bb29;bba
bb207 bb56, *bb120;
#else
bba bb232 bb39, *bb72;bba bb272 bbk, *bb59;bba bb276 bbd, *bb29;bba
bb239 bb56, *bb120;
#endif
bba bb39 bbf, *bb1, *bb249;bba bbk bb221, *bb264, *bb216;bba bbk bb269
, *bb271, *bb227;bba bbd bb60, *bb122, *bb273;bba bb83 bb37, *bb233, *
bb223;bba bbd bb230, *bb255, *bb260;bba bb114 bb248, *bb236, *bb237;
bba bb56 bb244, *bb289, *bb278;
#define bb141 bbb
bba bbb*bb210, *bb77;bba bbh bbb*bb286;bba bbl bb242;bba bbl*bb243;
bba bbh bbl*bb82;
#if defined( bb112)
bba bbe bb111;
#endif
bba bb111 bb19;bba bb19*bb257;bba bbh bb19*bb190;
#if defined( bb238) || defined( bb214)
bba bb19 bb36;bba bb19 bb118;
#else
bba bbl bb36;bba bbs bbl bb118;
#endif
bba bbh bb36*bb234;bba bb36*bb224;bba bb60 bb274, *bb281;bba bbb*
bb106;bba bb106*bb235;
#define bb213( bb35) bbi bb35##__ { bbe bb225; }; bba bbi bb35##__  * \
 bb35
bba bbi{bb37 bb189,bb212,bb222,bb263;}bb220, *bb254, *bb283;bba bbi{
bb37 bb8,bb193;}bb245, *bb270, *bb231;bba bbi{bb37 bb228,bb268;}bb267
, *bb291, *bb241;
#endif
bba bbh bbf*bb89;
#endif
bba bbf bb101;
#define IN
#define OUT
#ifdef _DEBUG
#define bb146( bbc) bb32( bbc)
#else
#define bb146( bbc) ( bbb)( bbc)
#endif
bba bbe bb161, *bb173;
#define bb226 0
#define bb318 1
#define bb300 2
#define bb320 3
#define bb347 4
bba bbe bb357;bba bbb*bb121;
#endif
#ifdef _WIN32
#ifndef UNDER_CE
#define bb31 bb344
#define bb43 bb339
bba bbs bb5 bb31;bba bb5 bb43;
#endif
#else
#endif
#ifdef _WIN32
bbb*bb128(bb31 bb47);bbb bb109(bbb* );bbb*bb137(bb31 bb159,bb31 bb47);
#else
#define bb128( bbc) bb147(1, bbc, bb140)
#define bb109( bbc) bb342( bbc)
#define bb137( bbc, bbn) bb147( bbc, bbn, bb140)
#endif
#ifdef _WIN32
#define bb32( bbc) bb346( bbc)
#else
#ifdef _DEBUG
bbe bb144(bbh bbl*bb96,bbh bbl*bb25,bbs bb229);
#define bb32( bbc) ( bbb)(( bbc) || ( bb144(# bbc, __FILE__, __LINE__ \
)))
#else
#define bb32( bbc) (( bbb)0)
#endif
#endif
bb43 bb302(bb43*bb322);
#ifndef _WIN32
bbe bb327(bbh bbl*bbg);bbe bb324(bbh bbl*bb20,...);
#endif
#ifdef _WIN32
bba bb355 bb97;
#define bb139( bbc) bb330( bbc)
#define bb142( bbc) bb350( bbc)
#define bb133( bbc) bb356( bbc)
#define bb132( bbc) bb332( bbc)
#else
bba bb337 bb97;
#define bb139( bbc) ( bbb)(  *  bbc = bb334( bbc))
#define bb142( bbc) (( bbb)0)
#define bb133( bbc) bb349( bbc)
#define bb132( bbc) bb354( bbc)
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbi{bbd bb9;bbd bb23[4 ];bbf bb103[64 ];}bb526;bbb bb1818(bb526*bbj
);bbb bb1311(bb526*bbj,bbh bbb*bb492,bbq bb9);bbb bb1821(bb526*bbj,
bbb*bb14);bbb bb1852(bbb*bb14,bbh bbb*bb6,bbq bb9);bbb bb1963(bbb*
bb14,bb82 bb6);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbi{bbd bb9;bbd bb23[5 ];bbf bb103[64 ];}bb528;bbb bb1794(bb528*bbj
);bbb bb1291(bb528*bbj,bbh bbb*bb6,bbq bb9);bbb bb1803(bb528*bbj,bbb*
bb14);bba bbi{bbd bb9;bbd bb23[8 ];bbf bb103[64 ];}bb529;bbb bb1820(
bb529*bbj);bbb bb1293(bb529*bbj,bbh bbb*bb6,bbq bb9);bbb bb1816(bb529
 *bbj,bbb*bb14);bba bbi{bbd bb9;bb56 bb23[8 ];bbf bb103[128 ];}bb462;
bbb bb1809(bb462*bbj);bbb bb1194(bb462*bbj,bbh bbb*bb6,bbq bb9);bbb
bb1835(bb462*bbj,bbb*bb14);bba bb462 bb912;bbb bb1797(bb912*bbj);bbb
bb1811(bb912*bbj,bbb*bb14);bbb bb1902(bbb*bb14,bbh bbb*bb6,bbq bb9);
bbb bb1866(bbb*bb14,bbh bbb*bb6,bbq bb9);bbb bb1849(bbb*bb14,bbh bbb*
bb6,bbq bb9);bbb bb1929(bbb*bb14,bbh bbb*bb6,bbq bb9);bbb bb2016(bbb*
bb14,bb82 bb6);bbb bb1965(bbb*bb14,bb82 bb6);bbb bb2025(bbb*bb14,bb82
bb6);bbb bb2018(bbb*bb14,bb82 bb6);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbi{bbd bb9;bbd bb23[5 ];bbf bb103[64 ];}bb523;bbb bb1802(bb523*bbj
);bbb bb1296(bb523*bbj,bbh bbb*bb492,bbq bb9);bbb bb1795(bb523*bbj,
bbb*bb14);bbb bb1924(bbb*bb14,bbh bbb*bb6,bbq bb9);bbb bb1973(bbb*
bb14,bb82 bb6);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbi{bbd bb9;bbd bb23[5 ];bbf bb103[64 ];}bb527;bbb bb1805(bb527*bbj
);bbb bb1353(bb527*bbj,bbh bbb*bb492,bbq bb9);bbb bb1838(bb527*bbj,
bbb*bb14);bbb bb1874(bbb*bb14,bbh bbb*bb6,bbq bb9);bbb bb2002(bbb*
bb14,bb82 bb6);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbb( *bb1054)(bbb*bbj);bba bbb( *bb834)(bbb*bbj,bbh bbb*bb6,bbq
bb9);bba bbb( *bb769)(bbb*bbj,bbb*bb14);bba bbi{bbe bb131;bbq bb38;
bbq bb388;bb1054 bb889;bb834 bb179;bb769 bb737;}bb453;bbb bb1856(
bb453*bbj,bbe bb131);bba bbi{bb453 bbn;bbf bbt[256 -bb12(bb453)];}
bb451;bbb bb1984(bb451*bbj,bbe bb131);bbb bb1991(bb451*bbj);bbb bb2020
(bb451*bbj,bbe bb131);bbb bb1983(bb451*bbj,bbh bbb*bb6,bbq bb9);bbb
bb1976(bb451*bbj,bbb*bb14);bbb bb1989(bbe bb131,bbb*bb14,bbh bbb*bb6,
bbq bb9);bbb bb2049(bbe bb131,bbb*bb14,bb82 bb6);bb82 bb1970(bbe bb131
);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbi{bb453 bbn;bbf bb542[(512 -bb12(bb453))/2 ];bbf bb1340[(512 -bb12
(bb453))/2 ];}bb499;bbb bb1961(bb499*bbj,bbe bb581);bbb bb2005(bb499*
bbj,bbh bbb*bb71,bbq bb143);bbb bb2109(bb499*bbj,bbe bb581,bbh bbb*
bb71,bbq bb143);bbb bb1988(bb499*bbj,bbh bbb*bb6,bbq bb9);bbb bb2007(
bb499*bbj,bbb*bb14);bbb bb2108(bbe bb581,bbh bbb*bb71,bbq bb143,bbb*
bb14,bbh bbb*bb6,bbq bb9);bbb bb2192(bbe bb581,bb82 bb71,bbb*bb14,
bb82 bb6);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbi{bbq bb447;bbd bb422[4 * (14 +1 )];}bb365;bbb bb1097(bb365*bbj,
bbh bbb*bb71,bbq bb143);bbb bb1736(bb365*bbj,bbh bbb*bb71,bbq bb143);
bbb bb1036(bb365*bbj,bbb*bb14,bbh bbb*bb6);bbb bb1775(bb365*bbj,bbb*
bb14,bbh bbb*bb6);
#ifdef __cplusplus
}
#endif
bba bbi{bb365 bb2119;bbq bb9;bbf bb103[16 ];bbf bb1928[16 ];bbf bb1926[
16 ];bbf bb1842[16 ];}bb942;bbb bb2042(bb942*bbj,bbh bbb*bb71,bbq bb143
);bbb bb2094(bb942*bbj,bbh bbb*bb6,bbq bb9);bbb bb2104(bb942*bbj,bbb*
bb14);
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bbb( *bb1865)(bbb*bbj,bbh bbb*bb71,bbq bb143);bba bbi{bbe bb131;
bbq bb38;bbq bb388;bb1865 bb889;bb834 bb179;bb769 bb737;}bb2031;bba
bbi{bb2031 bbn;bbf bbt[512 ];}bb530;bbb bb2146(bb530*bbj,bbe bb131);
bbb bb2171(bb530*bbj,bbh bbb*bb71,bbq bb143);bbb bb1834(bb530*bbj,bbe
bb131,bbh bbb*bb71,bbq bb143);bbb bb1241(bb530*bbj,bbh bbb*bb6,bbq bb9
);bbb bb1817(bb530*bbj,bbb*bb14);bbb bb2167(bbe bb131,bbh bbb*bb71,
bbq bb143,bbb*bb14,bbh bbb*bb6,bbq bb9);bbb bb2197(bbe bb131,bb82 bb71
,bbb*bb14,bb82 bb6);bb82 bb2207(bbe bb131);
#ifdef __cplusplus
}
#endif
bbb bb2146(bb530*bbj,bbe bb131){bb2031 bbn={0 };bbn.bb131=bb131;bb296(
bb131&0xff00 ){bb15 0x1000 :{bb499*bb2238=(bb499* )bbj->bbt;bb1961(
bb2238,bb131&0xff );bbn.bb38=bb2238->bbn.bb38;bbn.bb388=bb2238->bbn.
bb388;}bbn.bb889=(bb1865)bb2005;bbn.bb179=(bb834)bb1988;bbn.bb737=(
bb769)bb2007;bb22;bb15 0x2000 :bbn.bb38=16 ;bbn.bb388=16 ;bbn.bb889=(
bb1865)bb2042;bbn.bb179=(bb834)bb2094;bbn.bb737=(bb769)bb2104;bb22;
bb419:bb32(0 );}bbj->bbn=bbn;}bbb bb2171(bb530*bbj,bbh bbb*bb71,bbq
bb143){bbj->bbn.bb889(bbj->bbt,bb71,bb143);}bbb bb1834(bb530*bbj,bbe
bb131,bbh bbb*bb71,bbq bb143){bb2146(bbj,bb131);bb2171(bbj,bb71,bb143
);}bbb bb1241(bb530*bbj,bbh bbb*bb6,bbq bb9){bbj->bbn.bb179(bbj->bbt,
bb6,bb9);}bbb bb1817(bb530*bbj,bbb*bb14){bbj->bbn.bb737(bbj->bbt,bb14
);}bbb bb2167(bbe bb131,bbh bbb*bb71,bbq bb143,bbb*bb14,bbh bbb*bb6,
bbq bb9){bb530 bb95;bb1834(&bb95,bb131,bb71,bb143);bb1241(&bb95,bb6,
bb9);bb1817(&bb95,bb14);}bbb bb2197(bbe bb131,bb82 bb71,bbb*bb14,bb82
bb6){bb2167(bb131,bb71,(bbq)bb1306(bb71),bb14,bb6,(bbq)bb1306(bb6));}
bb82 bb2207(bbe bb131){bb41 bbl bbg[32 ];bb296(bb131&0xff00 ){bb15
0x1000 :bb1316(bbg,"\x48\x4d\x41\x43\x5f\x25\x73",bb1970(bb131&0xff ));
bb2 bbg;bb15 0x2000 :bb2"\x41\x45\x53\x5f\x58\x43\x42\x43";}bb2 bb90;}
