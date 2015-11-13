/*
   'ripemd.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Sun Nov 16 20:01:26 2014
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
bba bbi{bbd bb9;bbd bb23[5 ];bbf bb103[64 ];}bb523;bbb bb1802(bb523*bbj
);bbb bb1296(bb523*bbj,bbh bbb*bb492,bbq bb9);bbb bb1795(bb523*bbj,
bbb*bb14);bbb bb1924(bbb*bb14,bbh bbb*bb6,bbq bb9);bbb bb1973(bbb*
bb14,bb82 bb6);
#ifdef __cplusplus
}
#endif
bb41 bbb bb1254(bbd bb23[5 ],bbh bbf bb96[64 ]){bb32(bb12(bbe)>=4 );{bbd
bb68,bb62,bb65,bb55,bb64,bb69,bb61,bb49,bb67,bb66;bbd bbv[16 ],bbz;
bb68=bb62=bb23[0 ];bb65=bb55=bb23[1 ];bb64=bb69=bb23[2 ];bb61=bb49=bb23[
3 ];bb67=bb66=bb23[4 ];bb91(bbz=0 ;bbz<16 ;bbz++,bb96+=4 )bbv[bbz]=(bb96[0
]|bb96[1 ]<<8 |bb96[2 ]<<16 |bb96[3 ]<<24 );bb62+=(bb55^bb69^bb49)+bbv[0 ];
bb62=((bb62)<<(11 )|(bb62)>>(32 -11 ))+bb66;bb69=((bb69)<<(10 )|(bb69)>>(
32 -10 ));bb66+=(bb62^bb55^bb69)+bbv[1 ];bb66=((bb66)<<(14 )|(bb66)>>(32 -
14 ))+bb49;bb55=((bb55)<<(10 )|(bb55)>>(32 -10 ));bb49+=(bb66^bb62^bb55)+
bbv[2 ];bb49=((bb49)<<(15 )|(bb49)>>(32 -15 ))+bb69;bb62=((bb62)<<(10 )|(
bb62)>>(32 -10 ));bb69+=(bb49^bb66^bb62)+bbv[3 ];bb69=((bb69)<<(12 )|(
bb69)>>(32 -12 ))+bb55;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb55+=(bb69^
bb49^bb66)+bbv[4 ];bb55=((bb55)<<(5 )|(bb55)>>(32 -5 ))+bb62;bb49=((bb49)<<
(10 )|(bb49)>>(32 -10 ));bb62+=(bb55^bb69^bb49)+bbv[5 ];bb62=((bb62)<<(8 )|
(bb62)>>(32 -8 ))+bb66;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb66+=(bb62^
bb55^bb69)+bbv[6 ];bb66=((bb66)<<(7 )|(bb66)>>(32 -7 ))+bb49;bb55=((bb55)<<
(10 )|(bb55)>>(32 -10 ));bb49+=(bb66^bb62^bb55)+bbv[7 ];bb49=((bb49)<<(9 )|
(bb49)>>(32 -9 ))+bb69;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));bb69+=(bb49^
bb66^bb62)+bbv[8 ];bb69=((bb69)<<(11 )|(bb69)>>(32 -11 ))+bb55;bb66=((
bb66)<<(10 )|(bb66)>>(32 -10 ));bb55+=(bb69^bb49^bb66)+bbv[9 ];bb55=((
bb55)<<(13 )|(bb55)>>(32 -13 ))+bb62;bb49=((bb49)<<(10 )|(bb49)>>(32 -10 ));
bb62+=(bb55^bb69^bb49)+bbv[10 ];bb62=((bb62)<<(14 )|(bb62)>>(32 -14 ))+
bb66;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb66+=(bb62^bb55^bb69)+bbv[
11 ];bb66=((bb66)<<(15 )|(bb66)>>(32 -15 ))+bb49;bb55=((bb55)<<(10 )|(bb55
)>>(32 -10 ));bb49+=(bb66^bb62^bb55)+bbv[12 ];bb49=((bb49)<<(6 )|(bb49)>>
(32 -6 ))+bb69;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));bb69+=(bb49^bb66^
bb62)+bbv[13 ];bb69=((bb69)<<(7 )|(bb69)>>(32 -7 ))+bb55;bb66=((bb66)<<(
10 )|(bb66)>>(32 -10 ));bb55+=(bb69^bb49^bb66)+bbv[14 ];bb55=((bb55)<<(9 )|
(bb55)>>(32 -9 ))+bb62;bb49=((bb49)<<(10 )|(bb49)>>(32 -10 ));bb62+=(bb55^
bb69^bb49)+bbv[15 ];bb62=((bb62)<<(8 )|(bb62)>>(32 -8 ))+bb66;bb69=((bb69
)<<(10 )|(bb69)>>(32 -10 ));bb66+=(bb62&bb55|~bb62&bb69)+0x5a827999 +bbv[
7 ];bb66=((bb66)<<(7 )|(bb66)>>(32 -7 ))+bb49;bb55=((bb55)<<(10 )|(bb55)>>
(32 -10 ));bb49+=(bb66&bb62|~bb66&bb55)+0x5a827999 +bbv[4 ];bb49=((bb49)<<
(6 )|(bb49)>>(32 -6 ))+bb69;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));bb69+=(
bb49&bb66|~bb49&bb62)+0x5a827999 +bbv[13 ];bb69=((bb69)<<(8 )|(bb69)>>(
32 -8 ))+bb55;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb55+=(bb69&bb49|~
bb69&bb66)+0x5a827999 +bbv[1 ];bb55=((bb55)<<(13 )|(bb55)>>(32 -13 ))+bb62
;bb49=((bb49)<<(10 )|(bb49)>>(32 -10 ));bb62+=(bb55&bb69|~bb55&bb49)+
0x5a827999 +bbv[10 ];bb62=((bb62)<<(11 )|(bb62)>>(32 -11 ))+bb66;bb69=((
bb69)<<(10 )|(bb69)>>(32 -10 ));bb66+=(bb62&bb55|~bb62&bb69)+0x5a827999 +
bbv[6 ];bb66=((bb66)<<(9 )|(bb66)>>(32 -9 ))+bb49;bb55=((bb55)<<(10 )|(
bb55)>>(32 -10 ));bb49+=(bb66&bb62|~bb66&bb55)+0x5a827999 +bbv[15 ];bb49=
((bb49)<<(7 )|(bb49)>>(32 -7 ))+bb69;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));
bb69+=(bb49&bb66|~bb49&bb62)+0x5a827999 +bbv[3 ];bb69=((bb69)<<(15 )|(
bb69)>>(32 -15 ))+bb55;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb55+=(bb69&
bb49|~bb69&bb66)+0x5a827999 +bbv[12 ];bb55=((bb55)<<(7 )|(bb55)>>(32 -7 ))+
bb62;bb49=((bb49)<<(10 )|(bb49)>>(32 -10 ));bb62+=(bb55&bb69|~bb55&bb49)+
0x5a827999 +bbv[0 ];bb62=((bb62)<<(12 )|(bb62)>>(32 -12 ))+bb66;bb69=((
bb69)<<(10 )|(bb69)>>(32 -10 ));bb66+=(bb62&bb55|~bb62&bb69)+0x5a827999 +
bbv[9 ];bb66=((bb66)<<(15 )|(bb66)>>(32 -15 ))+bb49;bb55=((bb55)<<(10 )|(
bb55)>>(32 -10 ));bb49+=(bb66&bb62|~bb66&bb55)+0x5a827999 +bbv[5 ];bb49=(
(bb49)<<(9 )|(bb49)>>(32 -9 ))+bb69;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));
bb69+=(bb49&bb66|~bb49&bb62)+0x5a827999 +bbv[2 ];bb69=((bb69)<<(11 )|(
bb69)>>(32 -11 ))+bb55;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb55+=(bb69&
bb49|~bb69&bb66)+0x5a827999 +bbv[14 ];bb55=((bb55)<<(7 )|(bb55)>>(32 -7 ))+
bb62;bb49=((bb49)<<(10 )|(bb49)>>(32 -10 ));bb62+=(bb55&bb69|~bb55&bb49)+
0x5a827999 +bbv[11 ];bb62=((bb62)<<(13 )|(bb62)>>(32 -13 ))+bb66;bb69=((
bb69)<<(10 )|(bb69)>>(32 -10 ));bb66+=(bb62&bb55|~bb62&bb69)+0x5a827999 +
bbv[8 ];bb66=((bb66)<<(12 )|(bb66)>>(32 -12 ))+bb49;bb55=((bb55)<<(10 )|(
bb55)>>(32 -10 ));bb49+=((bb66|~bb62)^bb55)+0x6ed9eba1 +bbv[3 ];bb49=((
bb49)<<(11 )|(bb49)>>(32 -11 ))+bb69;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));
bb69+=((bb49|~bb66)^bb62)+0x6ed9eba1 +bbv[10 ];bb69=((bb69)<<(13 )|(bb69
)>>(32 -13 ))+bb55;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb55+=((bb69|~
bb49)^bb66)+0x6ed9eba1 +bbv[14 ];bb55=((bb55)<<(6 )|(bb55)>>(32 -6 ))+bb62
;bb49=((bb49)<<(10 )|(bb49)>>(32 -10 ));bb62+=((bb55|~bb69)^bb49)+
0x6ed9eba1 +bbv[4 ];bb62=((bb62)<<(7 )|(bb62)>>(32 -7 ))+bb66;bb69=((bb69)<<
(10 )|(bb69)>>(32 -10 ));bb66+=((bb62|~bb55)^bb69)+0x6ed9eba1 +bbv[9 ];
bb66=((bb66)<<(14 )|(bb66)>>(32 -14 ))+bb49;bb55=((bb55)<<(10 )|(bb55)>>(
32 -10 ));bb49+=((bb66|~bb62)^bb55)+0x6ed9eba1 +bbv[15 ];bb49=((bb49)<<(9
)|(bb49)>>(32 -9 ))+bb69;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));bb69+=((
bb49|~bb66)^bb62)+0x6ed9eba1 +bbv[8 ];bb69=((bb69)<<(13 )|(bb69)>>(32 -13
))+bb55;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb55+=((bb69|~bb49)^bb66)+
0x6ed9eba1 +bbv[1 ];bb55=((bb55)<<(15 )|(bb55)>>(32 -15 ))+bb62;bb49=((
bb49)<<(10 )|(bb49)>>(32 -10 ));bb62+=((bb55|~bb69)^bb49)+0x6ed9eba1 +bbv
[2 ];bb62=((bb62)<<(14 )|(bb62)>>(32 -14 ))+bb66;bb69=((bb69)<<(10 )|(bb69
)>>(32 -10 ));bb66+=((bb62|~bb55)^bb69)+0x6ed9eba1 +bbv[7 ];bb66=((bb66)<<
(8 )|(bb66)>>(32 -8 ))+bb49;bb55=((bb55)<<(10 )|(bb55)>>(32 -10 ));bb49+=((
bb66|~bb62)^bb55)+0x6ed9eba1 +bbv[0 ];bb49=((bb49)<<(13 )|(bb49)>>(32 -13
))+bb69;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));bb69+=((bb49|~bb66)^bb62)+
0x6ed9eba1 +bbv[6 ];bb69=((bb69)<<(6 )|(bb69)>>(32 -6 ))+bb55;bb66=((bb66)<<
(10 )|(bb66)>>(32 -10 ));bb55+=((bb69|~bb49)^bb66)+0x6ed9eba1 +bbv[13 ];
bb55=((bb55)<<(5 )|(bb55)>>(32 -5 ))+bb62;bb49=((bb49)<<(10 )|(bb49)>>(32
-10 ));bb62+=((bb55|~bb69)^bb49)+0x6ed9eba1 +bbv[11 ];bb62=((bb62)<<(12 )|
(bb62)>>(32 -12 ))+bb66;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb66+=((
bb62|~bb55)^bb69)+0x6ed9eba1 +bbv[5 ];bb66=((bb66)<<(7 )|(bb66)>>(32 -7 ))+
bb49;bb55=((bb55)<<(10 )|(bb55)>>(32 -10 ));bb49+=((bb66|~bb62)^bb55)+
0x6ed9eba1 +bbv[12 ];bb49=((bb49)<<(5 )|(bb49)>>(32 -5 ))+bb69;bb62=((bb62
)<<(10 )|(bb62)>>(32 -10 ));bb69+=(bb49&bb62|bb66&~bb62)+0x8f1bbcdc +bbv[
1 ];bb69=((bb69)<<(11 )|(bb69)>>(32 -11 ))+bb55;bb66=((bb66)<<(10 )|(bb66)>>
(32 -10 ));bb55+=(bb69&bb66|bb49&~bb66)+0x8f1bbcdc +bbv[9 ];bb55=((bb55)<<
(12 )|(bb55)>>(32 -12 ))+bb62;bb49=((bb49)<<(10 )|(bb49)>>(32 -10 ));bb62+=
(bb55&bb49|bb69&~bb49)+0x8f1bbcdc +bbv[11 ];bb62=((bb62)<<(14 )|(bb62)>>
(32 -14 ))+bb66;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb66+=(bb62&bb69|
bb55&~bb69)+0x8f1bbcdc +bbv[10 ];bb66=((bb66)<<(15 )|(bb66)>>(32 -15 ))+
bb49;bb55=((bb55)<<(10 )|(bb55)>>(32 -10 ));bb49+=(bb66&bb55|bb62&~bb55)+
0x8f1bbcdc +bbv[0 ];bb49=((bb49)<<(14 )|(bb49)>>(32 -14 ))+bb69;bb62=((
bb62)<<(10 )|(bb62)>>(32 -10 ));bb69+=(bb49&bb62|bb66&~bb62)+0x8f1bbcdc +
bbv[8 ];bb69=((bb69)<<(15 )|(bb69)>>(32 -15 ))+bb55;bb66=((bb66)<<(10 )|(
bb66)>>(32 -10 ));bb55+=(bb69&bb66|bb49&~bb66)+0x8f1bbcdc +bbv[12 ];bb55=
((bb55)<<(9 )|(bb55)>>(32 -9 ))+bb62;bb49=((bb49)<<(10 )|(bb49)>>(32 -10 ));
bb62+=(bb55&bb49|bb69&~bb49)+0x8f1bbcdc +bbv[4 ];bb62=((bb62)<<(8 )|(
bb62)>>(32 -8 ))+bb66;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb66+=(bb62&
bb69|bb55&~bb69)+0x8f1bbcdc +bbv[13 ];bb66=((bb66)<<(9 )|(bb66)>>(32 -9 ))+
bb49;bb55=((bb55)<<(10 )|(bb55)>>(32 -10 ));bb49+=(bb66&bb55|bb62&~bb55)+
0x8f1bbcdc +bbv[3 ];bb49=((bb49)<<(14 )|(bb49)>>(32 -14 ))+bb69;bb62=((
bb62)<<(10 )|(bb62)>>(32 -10 ));bb69+=(bb49&bb62|bb66&~bb62)+0x8f1bbcdc +
bbv[7 ];bb69=((bb69)<<(5 )|(bb69)>>(32 -5 ))+bb55;bb66=((bb66)<<(10 )|(
bb66)>>(32 -10 ));bb55+=(bb69&bb66|bb49&~bb66)+0x8f1bbcdc +bbv[15 ];bb55=
((bb55)<<(6 )|(bb55)>>(32 -6 ))+bb62;bb49=((bb49)<<(10 )|(bb49)>>(32 -10 ));
bb62+=(bb55&bb49|bb69&~bb49)+0x8f1bbcdc +bbv[14 ];bb62=((bb62)<<(8 )|(
bb62)>>(32 -8 ))+bb66;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb66+=(bb62&
bb69|bb55&~bb69)+0x8f1bbcdc +bbv[5 ];bb66=((bb66)<<(6 )|(bb66)>>(32 -6 ))+
bb49;bb55=((bb55)<<(10 )|(bb55)>>(32 -10 ));bb49+=(bb66&bb55|bb62&~bb55)+
0x8f1bbcdc +bbv[6 ];bb49=((bb49)<<(5 )|(bb49)>>(32 -5 ))+bb69;bb62=((bb62)<<
(10 )|(bb62)>>(32 -10 ));bb69+=(bb49&bb62|bb66&~bb62)+0x8f1bbcdc +bbv[2 ];
bb69=((bb69)<<(12 )|(bb69)>>(32 -12 ))+bb55;bb66=((bb66)<<(10 )|(bb66)>>(
32 -10 ));bb55+=(bb69^(bb49|~bb66))+0xa953fd4e +bbv[4 ];bb55=((bb55)<<(9 )|
(bb55)>>(32 -9 ))+bb62;bb49=((bb49)<<(10 )|(bb49)>>(32 -10 ));bb62+=(bb55^
(bb69|~bb49))+0xa953fd4e +bbv[0 ];bb62=((bb62)<<(15 )|(bb62)>>(32 -15 ))+
bb66;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb66+=(bb62^(bb55|~bb69))+
0xa953fd4e +bbv[5 ];bb66=((bb66)<<(5 )|(bb66)>>(32 -5 ))+bb49;bb55=((bb55)<<
(10 )|(bb55)>>(32 -10 ));bb49+=(bb66^(bb62|~bb55))+0xa953fd4e +bbv[9 ];
bb49=((bb49)<<(11 )|(bb49)>>(32 -11 ))+bb69;bb62=((bb62)<<(10 )|(bb62)>>(
32 -10 ));bb69+=(bb49^(bb66|~bb62))+0xa953fd4e +bbv[7 ];bb69=((bb69)<<(6 )|
(bb69)>>(32 -6 ))+bb55;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb55+=(bb69^
(bb49|~bb66))+0xa953fd4e +bbv[12 ];bb55=((bb55)<<(8 )|(bb55)>>(32 -8 ))+
bb62;bb49=((bb49)<<(10 )|(bb49)>>(32 -10 ));bb62+=(bb55^(bb69|~bb49))+
0xa953fd4e +bbv[2 ];bb62=((bb62)<<(13 )|(bb62)>>(32 -13 ))+bb66;bb69=((
bb69)<<(10 )|(bb69)>>(32 -10 ));bb66+=(bb62^(bb55|~bb69))+0xa953fd4e +bbv
[10 ];bb66=((bb66)<<(12 )|(bb66)>>(32 -12 ))+bb49;bb55=((bb55)<<(10 )|(
bb55)>>(32 -10 ));bb49+=(bb66^(bb62|~bb55))+0xa953fd4e +bbv[14 ];bb49=((
bb49)<<(5 )|(bb49)>>(32 -5 ))+bb69;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));
bb69+=(bb49^(bb66|~bb62))+0xa953fd4e +bbv[1 ];bb69=((bb69)<<(12 )|(bb69)>>
(32 -12 ))+bb55;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb55+=(bb69^(bb49|~
bb66))+0xa953fd4e +bbv[3 ];bb55=((bb55)<<(13 )|(bb55)>>(32 -13 ))+bb62;
bb49=((bb49)<<(10 )|(bb49)>>(32 -10 ));bb62+=(bb55^(bb69|~bb49))+
0xa953fd4e +bbv[8 ];bb62=((bb62)<<(14 )|(bb62)>>(32 -14 ))+bb66;bb69=((
bb69)<<(10 )|(bb69)>>(32 -10 ));bb66+=(bb62^(bb55|~bb69))+0xa953fd4e +bbv
[11 ];bb66=((bb66)<<(11 )|(bb66)>>(32 -11 ))+bb49;bb55=((bb55)<<(10 )|(
bb55)>>(32 -10 ));bb49+=(bb66^(bb62|~bb55))+0xa953fd4e +bbv[6 ];bb49=((
bb49)<<(8 )|(bb49)>>(32 -8 ))+bb69;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));
bb69+=(bb49^(bb66|~bb62))+0xa953fd4e +bbv[15 ];bb69=((bb69)<<(5 )|(bb69)>>
(32 -5 ))+bb55;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb55+=(bb69^(bb49|~
bb66))+0xa953fd4e +bbv[13 ];bb55=((bb55)<<(6 )|(bb55)>>(32 -6 ))+bb62;bb49
=((bb49)<<(10 )|(bb49)>>(32 -10 ));bb68+=(bb65^(bb64|~bb61))+0x50a28be6 +
bbv[5 ];bb68=((bb68)<<(8 )|(bb68)>>(32 -8 ))+bb67;bb64=((bb64)<<(10 )|(
bb64)>>(32 -10 ));bb67+=(bb68^(bb65|~bb64))+0x50a28be6 +bbv[14 ];bb67=((
bb67)<<(9 )|(bb67)>>(32 -9 ))+bb61;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));
bb61+=(bb67^(bb68|~bb65))+0x50a28be6 +bbv[7 ];bb61=((bb61)<<(9 )|(bb61)>>
(32 -9 ))+bb64;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb64+=(bb61^(bb67|~
bb68))+0x50a28be6 +bbv[0 ];bb64=((bb64)<<(11 )|(bb64)>>(32 -11 ))+bb65;
bb67=((bb67)<<(10 )|(bb67)>>(32 -10 ));bb65+=(bb64^(bb61|~bb67))+
0x50a28be6 +bbv[9 ];bb65=((bb65)<<(13 )|(bb65)>>(32 -13 ))+bb68;bb61=((
bb61)<<(10 )|(bb61)>>(32 -10 ));bb68+=(bb65^(bb64|~bb61))+0x50a28be6 +bbv
[2 ];bb68=((bb68)<<(15 )|(bb68)>>(32 -15 ))+bb67;bb64=((bb64)<<(10 )|(bb64
)>>(32 -10 ));bb67+=(bb68^(bb65|~bb64))+0x50a28be6 +bbv[11 ];bb67=((bb67)<<
(15 )|(bb67)>>(32 -15 ))+bb61;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb61+=
(bb67^(bb68|~bb65))+0x50a28be6 +bbv[4 ];bb61=((bb61)<<(5 )|(bb61)>>(32 -5
))+bb64;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb64+=(bb61^(bb67|~bb68))+
0x50a28be6 +bbv[13 ];bb64=((bb64)<<(7 )|(bb64)>>(32 -7 ))+bb65;bb67=((bb67
)<<(10 )|(bb67)>>(32 -10 ));bb65+=(bb64^(bb61|~bb67))+0x50a28be6 +bbv[6 ];
bb65=((bb65)<<(7 )|(bb65)>>(32 -7 ))+bb68;bb61=((bb61)<<(10 )|(bb61)>>(32
-10 ));bb68+=(bb65^(bb64|~bb61))+0x50a28be6 +bbv[15 ];bb68=((bb68)<<(8 )|
(bb68)>>(32 -8 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=(bb68^
(bb65|~bb64))+0x50a28be6 +bbv[8 ];bb67=((bb67)<<(11 )|(bb67)>>(32 -11 ))+
bb61;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb61+=(bb67^(bb68|~bb65))+
0x50a28be6 +bbv[1 ];bb61=((bb61)<<(14 )|(bb61)>>(32 -14 ))+bb64;bb68=((
bb68)<<(10 )|(bb68)>>(32 -10 ));bb64+=(bb61^(bb67|~bb68))+0x50a28be6 +bbv
[10 ];bb64=((bb64)<<(14 )|(bb64)>>(32 -14 ))+bb65;bb67=((bb67)<<(10 )|(
bb67)>>(32 -10 ));bb65+=(bb64^(bb61|~bb67))+0x50a28be6 +bbv[3 ];bb65=((
bb65)<<(12 )|(bb65)>>(32 -12 ))+bb68;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));
bb68+=(bb65^(bb64|~bb61))+0x50a28be6 +bbv[12 ];bb68=((bb68)<<(6 )|(bb68)>>
(32 -6 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=(bb68&bb64|
bb65&~bb64)+0x5c4dd124 +bbv[6 ];bb67=((bb67)<<(9 )|(bb67)>>(32 -9 ))+bb61;
bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb61+=(bb67&bb65|bb68&~bb65)+
0x5c4dd124 +bbv[11 ];bb61=((bb61)<<(13 )|(bb61)>>(32 -13 ))+bb64;bb68=((
bb68)<<(10 )|(bb68)>>(32 -10 ));bb64+=(bb61&bb68|bb67&~bb68)+0x5c4dd124 +
bbv[3 ];bb64=((bb64)<<(15 )|(bb64)>>(32 -15 ))+bb65;bb67=((bb67)<<(10 )|(
bb67)>>(32 -10 ));bb65+=(bb64&bb67|bb61&~bb67)+0x5c4dd124 +bbv[7 ];bb65=(
(bb65)<<(7 )|(bb65)>>(32 -7 ))+bb68;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));
bb68+=(bb65&bb61|bb64&~bb61)+0x5c4dd124 +bbv[0 ];bb68=((bb68)<<(12 )|(
bb68)>>(32 -12 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=(bb68&
bb64|bb65&~bb64)+0x5c4dd124 +bbv[13 ];bb67=((bb67)<<(8 )|(bb67)>>(32 -8 ))+
bb61;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb61+=(bb67&bb65|bb68&~bb65)+
0x5c4dd124 +bbv[5 ];bb61=((bb61)<<(9 )|(bb61)>>(32 -9 ))+bb64;bb68=((bb68)<<
(10 )|(bb68)>>(32 -10 ));bb64+=(bb61&bb68|bb67&~bb68)+0x5c4dd124 +bbv[10 ]
;bb64=((bb64)<<(11 )|(bb64)>>(32 -11 ))+bb65;bb67=((bb67)<<(10 )|(bb67)>>
(32 -10 ));bb65+=(bb64&bb67|bb61&~bb67)+0x5c4dd124 +bbv[14 ];bb65=((bb65)<<
(7 )|(bb65)>>(32 -7 ))+bb68;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));bb68+=(
bb65&bb61|bb64&~bb61)+0x5c4dd124 +bbv[15 ];bb68=((bb68)<<(7 )|(bb68)>>(
32 -7 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=(bb68&bb64|bb65
&~bb64)+0x5c4dd124 +bbv[8 ];bb67=((bb67)<<(12 )|(bb67)>>(32 -12 ))+bb61;
bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb61+=(bb67&bb65|bb68&~bb65)+
0x5c4dd124 +bbv[12 ];bb61=((bb61)<<(7 )|(bb61)>>(32 -7 ))+bb64;bb68=((bb68
)<<(10 )|(bb68)>>(32 -10 ));bb64+=(bb61&bb68|bb67&~bb68)+0x5c4dd124 +bbv[
4 ];bb64=((bb64)<<(6 )|(bb64)>>(32 -6 ))+bb65;bb67=((bb67)<<(10 )|(bb67)>>
(32 -10 ));bb65+=(bb64&bb67|bb61&~bb67)+0x5c4dd124 +bbv[9 ];bb65=((bb65)<<
(15 )|(bb65)>>(32 -15 ))+bb68;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));bb68+=
(bb65&bb61|bb64&~bb61)+0x5c4dd124 +bbv[1 ];bb68=((bb68)<<(13 )|(bb68)>>(
32 -13 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=(bb68&bb64|
bb65&~bb64)+0x5c4dd124 +bbv[2 ];bb67=((bb67)<<(11 )|(bb67)>>(32 -11 ))+
bb61;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb61+=((bb67|~bb68)^bb65)+
0x6d703ef3 +bbv[15 ];bb61=((bb61)<<(9 )|(bb61)>>(32 -9 ))+bb64;bb68=((bb68
)<<(10 )|(bb68)>>(32 -10 ));bb64+=((bb61|~bb67)^bb68)+0x6d703ef3 +bbv[5 ];
bb64=((bb64)<<(7 )|(bb64)>>(32 -7 ))+bb65;bb67=((bb67)<<(10 )|(bb67)>>(32
-10 ));bb65+=((bb64|~bb61)^bb67)+0x6d703ef3 +bbv[1 ];bb65=((bb65)<<(15 )|
(bb65)>>(32 -15 ))+bb68;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));bb68+=((
bb65|~bb64)^bb61)+0x6d703ef3 +bbv[3 ];bb68=((bb68)<<(11 )|(bb68)>>(32 -11
))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=((bb68|~bb65)^bb64)+
0x6d703ef3 +bbv[7 ];bb67=((bb67)<<(8 )|(bb67)>>(32 -8 ))+bb61;bb65=((bb65)<<
(10 )|(bb65)>>(32 -10 ));bb61+=((bb67|~bb68)^bb65)+0x6d703ef3 +bbv[14 ];
bb61=((bb61)<<(6 )|(bb61)>>(32 -6 ))+bb64;bb68=((bb68)<<(10 )|(bb68)>>(32
-10 ));bb64+=((bb61|~bb67)^bb68)+0x6d703ef3 +bbv[6 ];bb64=((bb64)<<(6 )|(
bb64)>>(32 -6 ))+bb65;bb67=((bb67)<<(10 )|(bb67)>>(32 -10 ));bb65+=((bb64|
~bb61)^bb67)+0x6d703ef3 +bbv[9 ];bb65=((bb65)<<(14 )|(bb65)>>(32 -14 ))+
bb68;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));bb68+=((bb65|~bb64)^bb61)+
0x6d703ef3 +bbv[11 ];bb68=((bb68)<<(12 )|(bb68)>>(32 -12 ))+bb67;bb64=((
bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=((bb68|~bb65)^bb64)+0x6d703ef3 +bbv
[8 ];bb67=((bb67)<<(13 )|(bb67)>>(32 -13 ))+bb61;bb65=((bb65)<<(10 )|(bb65
)>>(32 -10 ));bb61+=((bb67|~bb68)^bb65)+0x6d703ef3 +bbv[12 ];bb61=((bb61)<<
(5 )|(bb61)>>(32 -5 ))+bb64;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb64+=((
bb61|~bb67)^bb68)+0x6d703ef3 +bbv[2 ];bb64=((bb64)<<(14 )|(bb64)>>(32 -14
))+bb65;bb67=((bb67)<<(10 )|(bb67)>>(32 -10 ));bb65+=((bb64|~bb61)^bb67)+
0x6d703ef3 +bbv[10 ];bb65=((bb65)<<(13 )|(bb65)>>(32 -13 ))+bb68;bb61=((
bb61)<<(10 )|(bb61)>>(32 -10 ));bb68+=((bb65|~bb64)^bb61)+0x6d703ef3 +bbv
[0 ];bb68=((bb68)<<(13 )|(bb68)>>(32 -13 ))+bb67;bb64=((bb64)<<(10 )|(bb64
)>>(32 -10 ));bb67+=((bb68|~bb65)^bb64)+0x6d703ef3 +bbv[4 ];bb67=((bb67)<<
(7 )|(bb67)>>(32 -7 ))+bb61;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb61+=((
bb67|~bb68)^bb65)+0x6d703ef3 +bbv[13 ];bb61=((bb61)<<(5 )|(bb61)>>(32 -5 ))+
bb64;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb64+=(bb61&bb67|~bb61&bb68)+
0x7a6d76e9 +bbv[8 ];bb64=((bb64)<<(15 )|(bb64)>>(32 -15 ))+bb65;bb67=((
bb67)<<(10 )|(bb67)>>(32 -10 ));bb65+=(bb64&bb61|~bb64&bb67)+0x7a6d76e9 +
bbv[6 ];bb65=((bb65)<<(5 )|(bb65)>>(32 -5 ))+bb68;bb61=((bb61)<<(10 )|(
bb61)>>(32 -10 ));bb68+=(bb65&bb64|~bb65&bb61)+0x7a6d76e9 +bbv[4 ];bb68=(
(bb68)<<(8 )|(bb68)>>(32 -8 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));
bb67+=(bb68&bb65|~bb68&bb64)+0x7a6d76e9 +bbv[1 ];bb67=((bb67)<<(11 )|(
bb67)>>(32 -11 ))+bb61;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb61+=(bb67&
bb68|~bb67&bb65)+0x7a6d76e9 +bbv[3 ];bb61=((bb61)<<(14 )|(bb61)>>(32 -14 ))+
bb64;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb64+=(bb61&bb67|~bb61&bb68)+
0x7a6d76e9 +bbv[11 ];bb64=((bb64)<<(14 )|(bb64)>>(32 -14 ))+bb65;bb67=((
bb67)<<(10 )|(bb67)>>(32 -10 ));bb65+=(bb64&bb61|~bb64&bb67)+0x7a6d76e9 +
bbv[15 ];bb65=((bb65)<<(6 )|(bb65)>>(32 -6 ))+bb68;bb61=((bb61)<<(10 )|(
bb61)>>(32 -10 ));bb68+=(bb65&bb64|~bb65&bb61)+0x7a6d76e9 +bbv[0 ];bb68=(
(bb68)<<(14 )|(bb68)>>(32 -14 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));
bb67+=(bb68&bb65|~bb68&bb64)+0x7a6d76e9 +bbv[5 ];bb67=((bb67)<<(6 )|(
bb67)>>(32 -6 ))+bb61;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb61+=(bb67&
bb68|~bb67&bb65)+0x7a6d76e9 +bbv[12 ];bb61=((bb61)<<(9 )|(bb61)>>(32 -9 ))+
bb64;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb64+=(bb61&bb67|~bb61&bb68)+
0x7a6d76e9 +bbv[2 ];bb64=((bb64)<<(12 )|(bb64)>>(32 -12 ))+bb65;bb67=((
bb67)<<(10 )|(bb67)>>(32 -10 ));bb65+=(bb64&bb61|~bb64&bb67)+0x7a6d76e9 +
bbv[13 ];bb65=((bb65)<<(9 )|(bb65)>>(32 -9 ))+bb68;bb61=((bb61)<<(10 )|(
bb61)>>(32 -10 ));bb68+=(bb65&bb64|~bb65&bb61)+0x7a6d76e9 +bbv[9 ];bb68=(
(bb68)<<(12 )|(bb68)>>(32 -12 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));
bb67+=(bb68&bb65|~bb68&bb64)+0x7a6d76e9 +bbv[7 ];bb67=((bb67)<<(5 )|(
bb67)>>(32 -5 ))+bb61;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb61+=(bb67&
bb68|~bb67&bb65)+0x7a6d76e9 +bbv[10 ];bb61=((bb61)<<(15 )|(bb61)>>(32 -15
))+bb64;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb64+=(bb61&bb67|~bb61&
bb68)+0x7a6d76e9 +bbv[14 ];bb64=((bb64)<<(8 )|(bb64)>>(32 -8 ))+bb65;bb67=
((bb67)<<(10 )|(bb67)>>(32 -10 ));bb65+=(bb64^bb61^bb67)+bbv[12 ];bb65=((
bb65)<<(8 )|(bb65)>>(32 -8 ))+bb68;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));
bb68+=(bb65^bb64^bb61)+bbv[15 ];bb68=((bb68)<<(5 )|(bb68)>>(32 -5 ))+bb67
;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=(bb68^bb65^bb64)+bbv[10 ];
bb67=((bb67)<<(12 )|(bb67)>>(32 -12 ))+bb61;bb65=((bb65)<<(10 )|(bb65)>>(
32 -10 ));bb61+=(bb67^bb68^bb65)+bbv[4 ];bb61=((bb61)<<(9 )|(bb61)>>(32 -9
))+bb64;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb64+=(bb61^bb67^bb68)+
bbv[1 ];bb64=((bb64)<<(12 )|(bb64)>>(32 -12 ))+bb65;bb67=((bb67)<<(10 )|(
bb67)>>(32 -10 ));bb65+=(bb64^bb61^bb67)+bbv[5 ];bb65=((bb65)<<(5 )|(bb65
)>>(32 -5 ))+bb68;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));bb68+=(bb65^bb64^
bb61)+bbv[8 ];bb68=((bb68)<<(14 )|(bb68)>>(32 -14 ))+bb67;bb64=((bb64)<<(
10 )|(bb64)>>(32 -10 ));bb67+=(bb68^bb65^bb64)+bbv[7 ];bb67=((bb67)<<(6 )|
(bb67)>>(32 -6 ))+bb61;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb61+=(bb67^
bb68^bb65)+bbv[6 ];bb61=((bb61)<<(8 )|(bb61)>>(32 -8 ))+bb64;bb68=((bb68)<<
(10 )|(bb68)>>(32 -10 ));bb64+=(bb61^bb67^bb68)+bbv[2 ];bb64=((bb64)<<(13
)|(bb64)>>(32 -13 ))+bb65;bb67=((bb67)<<(10 )|(bb67)>>(32 -10 ));bb65+=(
bb64^bb61^bb67)+bbv[13 ];bb65=((bb65)<<(6 )|(bb65)>>(32 -6 ))+bb68;bb61=(
(bb61)<<(10 )|(bb61)>>(32 -10 ));bb68+=(bb65^bb64^bb61)+bbv[14 ];bb68=((
bb68)<<(5 )|(bb68)>>(32 -5 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));
bb67+=(bb68^bb65^bb64)+bbv[0 ];bb67=((bb67)<<(15 )|(bb67)>>(32 -15 ))+
bb61;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb61+=(bb67^bb68^bb65)+bbv[3
];bb61=((bb61)<<(13 )|(bb61)>>(32 -13 ))+bb64;bb68=((bb68)<<(10 )|(bb68)>>
(32 -10 ));bb64+=(bb61^bb67^bb68)+bbv[9 ];bb64=((bb64)<<(11 )|(bb64)>>(32
-11 ))+bb65;bb67=((bb67)<<(10 )|(bb67)>>(32 -10 ));bb65+=(bb64^bb61^bb67)+
bbv[11 ];bb65=((bb65)<<(11 )|(bb65)>>(32 -11 ))+bb68;bb61=((bb61)<<(10 )|(
bb61)>>(32 -10 ));bb61+=bb23[1 ]+bb69;bb23[1 ]=bb23[2 ]+bb49+bb67;bb23[2 ]=
bb23[3 ]+bb66+bb68;bb23[3 ]=bb23[4 ]+bb62+bb65;bb23[4 ]=bb23[0 ]+bb55+bb64
;bb23[0 ]=bb61;}}bbb bb1802(bb523*bbj){bb41 bbd bb23[5 ]={0x67452301 ,
0xefcdab89 ,0x98badcfe ,0x10325476 ,0xc3d2e1f0 };bbj->bb9=0 ;bb81(bbj->
bb23,bb23,bb12(bb23));}bbb bb1296(bb523*bbj,bbh bbb*bb492,bbq bb9){
bbh bbf*bb6=(bbh bbf* )bb492;bbq bb385=bbj->bb9%bb12(bbj->bb103);bbj
->bb9+=bb9;bbm(bb385){bbq bb11=bb12(bbj->bb103)-bb385;bb81(bbj->bb103
+bb385,bb6,((bb9)<(bb11)?(bb9):(bb11)));bbm(bb9<bb11)bb2;bb6+=bb11;
bb9-=bb11;bb1254(bbj->bb23,bbj->bb103);}bb91(;bb9>=bb12(bbj->bb103);
bb9-=bb12(bbj->bb103),bb6+=bb12(bbj->bb103))bb1254(bbj->bb23,bb6);
bb81(bbj->bb103,bb6,bb9);}bbb bb1795(bb523*bbj,bbb*bb14){bbd bb1010[2
]={(bbd)(bbj->bb9<<3 ),(bbd)(bbj->bb9>>29 )};bbf bb433[bb12(bb1010)];
bbq bbz;bb91(bbz=0 ;bbz<bb12(bb433);bbz++)bb433[bbz]=bb1010[bbz/4 ]>>((
bbz%4 ) *8 )&0xff ;{bbf bb1314[]={0x80 },bb1313[bb12(bbj->bb103)]={0 };bbq
bb385=bbj->bb9%bb12(bbj->bb103);bb1296(bbj,bb1314,1 );bb1296(bbj,
bb1313,(bb12(bbj->bb103) *2 -1 -bb12(bb433)-bb385)%bb12(bbj->bb103));}
bb1296(bbj,bb433,bb12(bb433));bb91(bbz=0 ;bbz<bb12(bbj->bb23);bbz++)((
bbf* )bb14)[bbz]=bbj->bb23[bbz/4 ]>>((bbz%4 ) *8 )&0xff ;}bbb bb1924(bbb*
bb14,bbh bbb*bb6,bbq bb9){bb523 bb95;bb1802(&bb95);bb1296(&bb95,bb6,
bb9);bb1795(&bb95,bb14);}bbb bb1973(bbb*bb14,bb82 bb6){bb1924(bb14,
bb6,(bbq)bb1306(bb6));}
