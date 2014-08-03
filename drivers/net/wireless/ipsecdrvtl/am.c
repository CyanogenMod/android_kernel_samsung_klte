/*
   'ripemd.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Wed Jan 15 12:08:55 2014
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
bba bbi{bbd bb9;bbd bb23[5 ];bbf bb101[64 ];}bb529;bbb bb1801(bb529*bbj
);bbb bb1295(bb529*bbj,bbh bbb*bb498,bbq bb9);bbb bb1795(bb529*bbj,
bbb*bb14);bbb bb1924(bbb*bb14,bbh bbb*bb5,bbq bb9);bbb bb1973(bbb*
bb14,bb82 bb5);
#ifdef __cplusplus
}
#endif
bb41 bbb bb1256(bbd bb23[5 ],bbh bbf bb95[64 ]){bb32(bb12(bbe)>=4 );{bbd
bb65,bb61,bb68,bb55,bb64,bb66,bb62,bb48,bb67,bb69;bbd bbv[16 ],bbz;
bb65=bb61=bb23[0 ];bb68=bb55=bb23[1 ];bb64=bb66=bb23[2 ];bb62=bb48=bb23[
3 ];bb67=bb69=bb23[4 ];bb91(bbz=0 ;bbz<16 ;bbz++,bb95+=4 )bbv[bbz]=(bb95[0
]|bb95[1 ]<<8 |bb95[2 ]<<16 |bb95[3 ]<<24 );bb61+=(bb55^bb66^bb48)+bbv[0 ];
bb61=((bb61)<<(11 )|(bb61)>>(32 -11 ))+bb69;bb66=((bb66)<<(10 )|(bb66)>>(
32 -10 ));bb69+=(bb61^bb55^bb66)+bbv[1 ];bb69=((bb69)<<(14 )|(bb69)>>(32 -
14 ))+bb48;bb55=((bb55)<<(10 )|(bb55)>>(32 -10 ));bb48+=(bb69^bb61^bb55)+
bbv[2 ];bb48=((bb48)<<(15 )|(bb48)>>(32 -15 ))+bb66;bb61=((bb61)<<(10 )|(
bb61)>>(32 -10 ));bb66+=(bb48^bb69^bb61)+bbv[3 ];bb66=((bb66)<<(12 )|(
bb66)>>(32 -12 ))+bb55;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb55+=(bb66^
bb48^bb69)+bbv[4 ];bb55=((bb55)<<(5 )|(bb55)>>(32 -5 ))+bb61;bb48=((bb48)<<
(10 )|(bb48)>>(32 -10 ));bb61+=(bb55^bb66^bb48)+bbv[5 ];bb61=((bb61)<<(8 )|
(bb61)>>(32 -8 ))+bb69;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb69+=(bb61^
bb55^bb66)+bbv[6 ];bb69=((bb69)<<(7 )|(bb69)>>(32 -7 ))+bb48;bb55=((bb55)<<
(10 )|(bb55)>>(32 -10 ));bb48+=(bb69^bb61^bb55)+bbv[7 ];bb48=((bb48)<<(9 )|
(bb48)>>(32 -9 ))+bb66;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));bb66+=(bb48^
bb69^bb61)+bbv[8 ];bb66=((bb66)<<(11 )|(bb66)>>(32 -11 ))+bb55;bb69=((
bb69)<<(10 )|(bb69)>>(32 -10 ));bb55+=(bb66^bb48^bb69)+bbv[9 ];bb55=((
bb55)<<(13 )|(bb55)>>(32 -13 ))+bb61;bb48=((bb48)<<(10 )|(bb48)>>(32 -10 ));
bb61+=(bb55^bb66^bb48)+bbv[10 ];bb61=((bb61)<<(14 )|(bb61)>>(32 -14 ))+
bb69;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb69+=(bb61^bb55^bb66)+bbv[
11 ];bb69=((bb69)<<(15 )|(bb69)>>(32 -15 ))+bb48;bb55=((bb55)<<(10 )|(bb55
)>>(32 -10 ));bb48+=(bb69^bb61^bb55)+bbv[12 ];bb48=((bb48)<<(6 )|(bb48)>>
(32 -6 ))+bb66;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));bb66+=(bb48^bb69^
bb61)+bbv[13 ];bb66=((bb66)<<(7 )|(bb66)>>(32 -7 ))+bb55;bb69=((bb69)<<(
10 )|(bb69)>>(32 -10 ));bb55+=(bb66^bb48^bb69)+bbv[14 ];bb55=((bb55)<<(9 )|
(bb55)>>(32 -9 ))+bb61;bb48=((bb48)<<(10 )|(bb48)>>(32 -10 ));bb61+=(bb55^
bb66^bb48)+bbv[15 ];bb61=((bb61)<<(8 )|(bb61)>>(32 -8 ))+bb69;bb66=((bb66
)<<(10 )|(bb66)>>(32 -10 ));bb69+=(bb61&bb55|~bb61&bb66)+0x5a827999 +bbv[
7 ];bb69=((bb69)<<(7 )|(bb69)>>(32 -7 ))+bb48;bb55=((bb55)<<(10 )|(bb55)>>
(32 -10 ));bb48+=(bb69&bb61|~bb69&bb55)+0x5a827999 +bbv[4 ];bb48=((bb48)<<
(6 )|(bb48)>>(32 -6 ))+bb66;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));bb66+=(
bb48&bb69|~bb48&bb61)+0x5a827999 +bbv[13 ];bb66=((bb66)<<(8 )|(bb66)>>(
32 -8 ))+bb55;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb55+=(bb66&bb48|~
bb66&bb69)+0x5a827999 +bbv[1 ];bb55=((bb55)<<(13 )|(bb55)>>(32 -13 ))+bb61
;bb48=((bb48)<<(10 )|(bb48)>>(32 -10 ));bb61+=(bb55&bb66|~bb55&bb48)+
0x5a827999 +bbv[10 ];bb61=((bb61)<<(11 )|(bb61)>>(32 -11 ))+bb69;bb66=((
bb66)<<(10 )|(bb66)>>(32 -10 ));bb69+=(bb61&bb55|~bb61&bb66)+0x5a827999 +
bbv[6 ];bb69=((bb69)<<(9 )|(bb69)>>(32 -9 ))+bb48;bb55=((bb55)<<(10 )|(
bb55)>>(32 -10 ));bb48+=(bb69&bb61|~bb69&bb55)+0x5a827999 +bbv[15 ];bb48=
((bb48)<<(7 )|(bb48)>>(32 -7 ))+bb66;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));
bb66+=(bb48&bb69|~bb48&bb61)+0x5a827999 +bbv[3 ];bb66=((bb66)<<(15 )|(
bb66)>>(32 -15 ))+bb55;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb55+=(bb66&
bb48|~bb66&bb69)+0x5a827999 +bbv[12 ];bb55=((bb55)<<(7 )|(bb55)>>(32 -7 ))+
bb61;bb48=((bb48)<<(10 )|(bb48)>>(32 -10 ));bb61+=(bb55&bb66|~bb55&bb48)+
0x5a827999 +bbv[0 ];bb61=((bb61)<<(12 )|(bb61)>>(32 -12 ))+bb69;bb66=((
bb66)<<(10 )|(bb66)>>(32 -10 ));bb69+=(bb61&bb55|~bb61&bb66)+0x5a827999 +
bbv[9 ];bb69=((bb69)<<(15 )|(bb69)>>(32 -15 ))+bb48;bb55=((bb55)<<(10 )|(
bb55)>>(32 -10 ));bb48+=(bb69&bb61|~bb69&bb55)+0x5a827999 +bbv[5 ];bb48=(
(bb48)<<(9 )|(bb48)>>(32 -9 ))+bb66;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));
bb66+=(bb48&bb69|~bb48&bb61)+0x5a827999 +bbv[2 ];bb66=((bb66)<<(11 )|(
bb66)>>(32 -11 ))+bb55;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb55+=(bb66&
bb48|~bb66&bb69)+0x5a827999 +bbv[14 ];bb55=((bb55)<<(7 )|(bb55)>>(32 -7 ))+
bb61;bb48=((bb48)<<(10 )|(bb48)>>(32 -10 ));bb61+=(bb55&bb66|~bb55&bb48)+
0x5a827999 +bbv[11 ];bb61=((bb61)<<(13 )|(bb61)>>(32 -13 ))+bb69;bb66=((
bb66)<<(10 )|(bb66)>>(32 -10 ));bb69+=(bb61&bb55|~bb61&bb66)+0x5a827999 +
bbv[8 ];bb69=((bb69)<<(12 )|(bb69)>>(32 -12 ))+bb48;bb55=((bb55)<<(10 )|(
bb55)>>(32 -10 ));bb48+=((bb69|~bb61)^bb55)+0x6ed9eba1 +bbv[3 ];bb48=((
bb48)<<(11 )|(bb48)>>(32 -11 ))+bb66;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));
bb66+=((bb48|~bb69)^bb61)+0x6ed9eba1 +bbv[10 ];bb66=((bb66)<<(13 )|(bb66
)>>(32 -13 ))+bb55;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb55+=((bb66|~
bb48)^bb69)+0x6ed9eba1 +bbv[14 ];bb55=((bb55)<<(6 )|(bb55)>>(32 -6 ))+bb61
;bb48=((bb48)<<(10 )|(bb48)>>(32 -10 ));bb61+=((bb55|~bb66)^bb48)+
0x6ed9eba1 +bbv[4 ];bb61=((bb61)<<(7 )|(bb61)>>(32 -7 ))+bb69;bb66=((bb66)<<
(10 )|(bb66)>>(32 -10 ));bb69+=((bb61|~bb55)^bb66)+0x6ed9eba1 +bbv[9 ];
bb69=((bb69)<<(14 )|(bb69)>>(32 -14 ))+bb48;bb55=((bb55)<<(10 )|(bb55)>>(
32 -10 ));bb48+=((bb69|~bb61)^bb55)+0x6ed9eba1 +bbv[15 ];bb48=((bb48)<<(9
)|(bb48)>>(32 -9 ))+bb66;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));bb66+=((
bb48|~bb69)^bb61)+0x6ed9eba1 +bbv[8 ];bb66=((bb66)<<(13 )|(bb66)>>(32 -13
))+bb55;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb55+=((bb66|~bb48)^bb69)+
0x6ed9eba1 +bbv[1 ];bb55=((bb55)<<(15 )|(bb55)>>(32 -15 ))+bb61;bb48=((
bb48)<<(10 )|(bb48)>>(32 -10 ));bb61+=((bb55|~bb66)^bb48)+0x6ed9eba1 +bbv
[2 ];bb61=((bb61)<<(14 )|(bb61)>>(32 -14 ))+bb69;bb66=((bb66)<<(10 )|(bb66
)>>(32 -10 ));bb69+=((bb61|~bb55)^bb66)+0x6ed9eba1 +bbv[7 ];bb69=((bb69)<<
(8 )|(bb69)>>(32 -8 ))+bb48;bb55=((bb55)<<(10 )|(bb55)>>(32 -10 ));bb48+=((
bb69|~bb61)^bb55)+0x6ed9eba1 +bbv[0 ];bb48=((bb48)<<(13 )|(bb48)>>(32 -13
))+bb66;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));bb66+=((bb48|~bb69)^bb61)+
0x6ed9eba1 +bbv[6 ];bb66=((bb66)<<(6 )|(bb66)>>(32 -6 ))+bb55;bb69=((bb69)<<
(10 )|(bb69)>>(32 -10 ));bb55+=((bb66|~bb48)^bb69)+0x6ed9eba1 +bbv[13 ];
bb55=((bb55)<<(5 )|(bb55)>>(32 -5 ))+bb61;bb48=((bb48)<<(10 )|(bb48)>>(32
-10 ));bb61+=((bb55|~bb66)^bb48)+0x6ed9eba1 +bbv[11 ];bb61=((bb61)<<(12 )|
(bb61)>>(32 -12 ))+bb69;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb69+=((
bb61|~bb55)^bb66)+0x6ed9eba1 +bbv[5 ];bb69=((bb69)<<(7 )|(bb69)>>(32 -7 ))+
bb48;bb55=((bb55)<<(10 )|(bb55)>>(32 -10 ));bb48+=((bb69|~bb61)^bb55)+
0x6ed9eba1 +bbv[12 ];bb48=((bb48)<<(5 )|(bb48)>>(32 -5 ))+bb66;bb61=((bb61
)<<(10 )|(bb61)>>(32 -10 ));bb66+=(bb48&bb61|bb69&~bb61)+0x8f1bbcdc +bbv[
1 ];bb66=((bb66)<<(11 )|(bb66)>>(32 -11 ))+bb55;bb69=((bb69)<<(10 )|(bb69)>>
(32 -10 ));bb55+=(bb66&bb69|bb48&~bb69)+0x8f1bbcdc +bbv[9 ];bb55=((bb55)<<
(12 )|(bb55)>>(32 -12 ))+bb61;bb48=((bb48)<<(10 )|(bb48)>>(32 -10 ));bb61+=
(bb55&bb48|bb66&~bb48)+0x8f1bbcdc +bbv[11 ];bb61=((bb61)<<(14 )|(bb61)>>
(32 -14 ))+bb69;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb69+=(bb61&bb66|
bb55&~bb66)+0x8f1bbcdc +bbv[10 ];bb69=((bb69)<<(15 )|(bb69)>>(32 -15 ))+
bb48;bb55=((bb55)<<(10 )|(bb55)>>(32 -10 ));bb48+=(bb69&bb55|bb61&~bb55)+
0x8f1bbcdc +bbv[0 ];bb48=((bb48)<<(14 )|(bb48)>>(32 -14 ))+bb66;bb61=((
bb61)<<(10 )|(bb61)>>(32 -10 ));bb66+=(bb48&bb61|bb69&~bb61)+0x8f1bbcdc +
bbv[8 ];bb66=((bb66)<<(15 )|(bb66)>>(32 -15 ))+bb55;bb69=((bb69)<<(10 )|(
bb69)>>(32 -10 ));bb55+=(bb66&bb69|bb48&~bb69)+0x8f1bbcdc +bbv[12 ];bb55=
((bb55)<<(9 )|(bb55)>>(32 -9 ))+bb61;bb48=((bb48)<<(10 )|(bb48)>>(32 -10 ));
bb61+=(bb55&bb48|bb66&~bb48)+0x8f1bbcdc +bbv[4 ];bb61=((bb61)<<(8 )|(
bb61)>>(32 -8 ))+bb69;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb69+=(bb61&
bb66|bb55&~bb66)+0x8f1bbcdc +bbv[13 ];bb69=((bb69)<<(9 )|(bb69)>>(32 -9 ))+
bb48;bb55=((bb55)<<(10 )|(bb55)>>(32 -10 ));bb48+=(bb69&bb55|bb61&~bb55)+
0x8f1bbcdc +bbv[3 ];bb48=((bb48)<<(14 )|(bb48)>>(32 -14 ))+bb66;bb61=((
bb61)<<(10 )|(bb61)>>(32 -10 ));bb66+=(bb48&bb61|bb69&~bb61)+0x8f1bbcdc +
bbv[7 ];bb66=((bb66)<<(5 )|(bb66)>>(32 -5 ))+bb55;bb69=((bb69)<<(10 )|(
bb69)>>(32 -10 ));bb55+=(bb66&bb69|bb48&~bb69)+0x8f1bbcdc +bbv[15 ];bb55=
((bb55)<<(6 )|(bb55)>>(32 -6 ))+bb61;bb48=((bb48)<<(10 )|(bb48)>>(32 -10 ));
bb61+=(bb55&bb48|bb66&~bb48)+0x8f1bbcdc +bbv[14 ];bb61=((bb61)<<(8 )|(
bb61)>>(32 -8 ))+bb69;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb69+=(bb61&
bb66|bb55&~bb66)+0x8f1bbcdc +bbv[5 ];bb69=((bb69)<<(6 )|(bb69)>>(32 -6 ))+
bb48;bb55=((bb55)<<(10 )|(bb55)>>(32 -10 ));bb48+=(bb69&bb55|bb61&~bb55)+
0x8f1bbcdc +bbv[6 ];bb48=((bb48)<<(5 )|(bb48)>>(32 -5 ))+bb66;bb61=((bb61)<<
(10 )|(bb61)>>(32 -10 ));bb66+=(bb48&bb61|bb69&~bb61)+0x8f1bbcdc +bbv[2 ];
bb66=((bb66)<<(12 )|(bb66)>>(32 -12 ))+bb55;bb69=((bb69)<<(10 )|(bb69)>>(
32 -10 ));bb55+=(bb66^(bb48|~bb69))+0xa953fd4e +bbv[4 ];bb55=((bb55)<<(9 )|
(bb55)>>(32 -9 ))+bb61;bb48=((bb48)<<(10 )|(bb48)>>(32 -10 ));bb61+=(bb55^
(bb66|~bb48))+0xa953fd4e +bbv[0 ];bb61=((bb61)<<(15 )|(bb61)>>(32 -15 ))+
bb69;bb66=((bb66)<<(10 )|(bb66)>>(32 -10 ));bb69+=(bb61^(bb55|~bb66))+
0xa953fd4e +bbv[5 ];bb69=((bb69)<<(5 )|(bb69)>>(32 -5 ))+bb48;bb55=((bb55)<<
(10 )|(bb55)>>(32 -10 ));bb48+=(bb69^(bb61|~bb55))+0xa953fd4e +bbv[9 ];
bb48=((bb48)<<(11 )|(bb48)>>(32 -11 ))+bb66;bb61=((bb61)<<(10 )|(bb61)>>(
32 -10 ));bb66+=(bb48^(bb69|~bb61))+0xa953fd4e +bbv[7 ];bb66=((bb66)<<(6 )|
(bb66)>>(32 -6 ))+bb55;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb55+=(bb66^
(bb48|~bb69))+0xa953fd4e +bbv[12 ];bb55=((bb55)<<(8 )|(bb55)>>(32 -8 ))+
bb61;bb48=((bb48)<<(10 )|(bb48)>>(32 -10 ));bb61+=(bb55^(bb66|~bb48))+
0xa953fd4e +bbv[2 ];bb61=((bb61)<<(13 )|(bb61)>>(32 -13 ))+bb69;bb66=((
bb66)<<(10 )|(bb66)>>(32 -10 ));bb69+=(bb61^(bb55|~bb66))+0xa953fd4e +bbv
[10 ];bb69=((bb69)<<(12 )|(bb69)>>(32 -12 ))+bb48;bb55=((bb55)<<(10 )|(
bb55)>>(32 -10 ));bb48+=(bb69^(bb61|~bb55))+0xa953fd4e +bbv[14 ];bb48=((
bb48)<<(5 )|(bb48)>>(32 -5 ))+bb66;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));
bb66+=(bb48^(bb69|~bb61))+0xa953fd4e +bbv[1 ];bb66=((bb66)<<(12 )|(bb66)>>
(32 -12 ))+bb55;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb55+=(bb66^(bb48|~
bb69))+0xa953fd4e +bbv[3 ];bb55=((bb55)<<(13 )|(bb55)>>(32 -13 ))+bb61;
bb48=((bb48)<<(10 )|(bb48)>>(32 -10 ));bb61+=(bb55^(bb66|~bb48))+
0xa953fd4e +bbv[8 ];bb61=((bb61)<<(14 )|(bb61)>>(32 -14 ))+bb69;bb66=((
bb66)<<(10 )|(bb66)>>(32 -10 ));bb69+=(bb61^(bb55|~bb66))+0xa953fd4e +bbv
[11 ];bb69=((bb69)<<(11 )|(bb69)>>(32 -11 ))+bb48;bb55=((bb55)<<(10 )|(
bb55)>>(32 -10 ));bb48+=(bb69^(bb61|~bb55))+0xa953fd4e +bbv[6 ];bb48=((
bb48)<<(8 )|(bb48)>>(32 -8 ))+bb66;bb61=((bb61)<<(10 )|(bb61)>>(32 -10 ));
bb66+=(bb48^(bb69|~bb61))+0xa953fd4e +bbv[15 ];bb66=((bb66)<<(5 )|(bb66)>>
(32 -5 ))+bb55;bb69=((bb69)<<(10 )|(bb69)>>(32 -10 ));bb55+=(bb66^(bb48|~
bb69))+0xa953fd4e +bbv[13 ];bb55=((bb55)<<(6 )|(bb55)>>(32 -6 ))+bb61;bb48
=((bb48)<<(10 )|(bb48)>>(32 -10 ));bb65+=(bb68^(bb64|~bb62))+0x50a28be6 +
bbv[5 ];bb65=((bb65)<<(8 )|(bb65)>>(32 -8 ))+bb67;bb64=((bb64)<<(10 )|(
bb64)>>(32 -10 ));bb67+=(bb65^(bb68|~bb64))+0x50a28be6 +bbv[14 ];bb67=((
bb67)<<(9 )|(bb67)>>(32 -9 ))+bb62;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));
bb62+=(bb67^(bb65|~bb68))+0x50a28be6 +bbv[7 ];bb62=((bb62)<<(9 )|(bb62)>>
(32 -9 ))+bb64;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb64+=(bb62^(bb67|~
bb65))+0x50a28be6 +bbv[0 ];bb64=((bb64)<<(11 )|(bb64)>>(32 -11 ))+bb68;
bb67=((bb67)<<(10 )|(bb67)>>(32 -10 ));bb68+=(bb64^(bb62|~bb67))+
0x50a28be6 +bbv[9 ];bb68=((bb68)<<(13 )|(bb68)>>(32 -13 ))+bb65;bb62=((
bb62)<<(10 )|(bb62)>>(32 -10 ));bb65+=(bb68^(bb64|~bb62))+0x50a28be6 +bbv
[2 ];bb65=((bb65)<<(15 )|(bb65)>>(32 -15 ))+bb67;bb64=((bb64)<<(10 )|(bb64
)>>(32 -10 ));bb67+=(bb65^(bb68|~bb64))+0x50a28be6 +bbv[11 ];bb67=((bb67)<<
(15 )|(bb67)>>(32 -15 ))+bb62;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb62+=
(bb67^(bb65|~bb68))+0x50a28be6 +bbv[4 ];bb62=((bb62)<<(5 )|(bb62)>>(32 -5
))+bb64;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb64+=(bb62^(bb67|~bb65))+
0x50a28be6 +bbv[13 ];bb64=((bb64)<<(7 )|(bb64)>>(32 -7 ))+bb68;bb67=((bb67
)<<(10 )|(bb67)>>(32 -10 ));bb68+=(bb64^(bb62|~bb67))+0x50a28be6 +bbv[6 ];
bb68=((bb68)<<(7 )|(bb68)>>(32 -7 ))+bb65;bb62=((bb62)<<(10 )|(bb62)>>(32
-10 ));bb65+=(bb68^(bb64|~bb62))+0x50a28be6 +bbv[15 ];bb65=((bb65)<<(8 )|
(bb65)>>(32 -8 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=(bb65^
(bb68|~bb64))+0x50a28be6 +bbv[8 ];bb67=((bb67)<<(11 )|(bb67)>>(32 -11 ))+
bb62;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb62+=(bb67^(bb65|~bb68))+
0x50a28be6 +bbv[1 ];bb62=((bb62)<<(14 )|(bb62)>>(32 -14 ))+bb64;bb65=((
bb65)<<(10 )|(bb65)>>(32 -10 ));bb64+=(bb62^(bb67|~bb65))+0x50a28be6 +bbv
[10 ];bb64=((bb64)<<(14 )|(bb64)>>(32 -14 ))+bb68;bb67=((bb67)<<(10 )|(
bb67)>>(32 -10 ));bb68+=(bb64^(bb62|~bb67))+0x50a28be6 +bbv[3 ];bb68=((
bb68)<<(12 )|(bb68)>>(32 -12 ))+bb65;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));
bb65+=(bb68^(bb64|~bb62))+0x50a28be6 +bbv[12 ];bb65=((bb65)<<(6 )|(bb65)>>
(32 -6 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=(bb65&bb64|
bb68&~bb64)+0x5c4dd124 +bbv[6 ];bb67=((bb67)<<(9 )|(bb67)>>(32 -9 ))+bb62;
bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb62+=(bb67&bb68|bb65&~bb68)+
0x5c4dd124 +bbv[11 ];bb62=((bb62)<<(13 )|(bb62)>>(32 -13 ))+bb64;bb65=((
bb65)<<(10 )|(bb65)>>(32 -10 ));bb64+=(bb62&bb65|bb67&~bb65)+0x5c4dd124 +
bbv[3 ];bb64=((bb64)<<(15 )|(bb64)>>(32 -15 ))+bb68;bb67=((bb67)<<(10 )|(
bb67)>>(32 -10 ));bb68+=(bb64&bb67|bb62&~bb67)+0x5c4dd124 +bbv[7 ];bb68=(
(bb68)<<(7 )|(bb68)>>(32 -7 ))+bb65;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));
bb65+=(bb68&bb62|bb64&~bb62)+0x5c4dd124 +bbv[0 ];bb65=((bb65)<<(12 )|(
bb65)>>(32 -12 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=(bb65&
bb64|bb68&~bb64)+0x5c4dd124 +bbv[13 ];bb67=((bb67)<<(8 )|(bb67)>>(32 -8 ))+
bb62;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb62+=(bb67&bb68|bb65&~bb68)+
0x5c4dd124 +bbv[5 ];bb62=((bb62)<<(9 )|(bb62)>>(32 -9 ))+bb64;bb65=((bb65)<<
(10 )|(bb65)>>(32 -10 ));bb64+=(bb62&bb65|bb67&~bb65)+0x5c4dd124 +bbv[10 ]
;bb64=((bb64)<<(11 )|(bb64)>>(32 -11 ))+bb68;bb67=((bb67)<<(10 )|(bb67)>>
(32 -10 ));bb68+=(bb64&bb67|bb62&~bb67)+0x5c4dd124 +bbv[14 ];bb68=((bb68)<<
(7 )|(bb68)>>(32 -7 ))+bb65;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));bb65+=(
bb68&bb62|bb64&~bb62)+0x5c4dd124 +bbv[15 ];bb65=((bb65)<<(7 )|(bb65)>>(
32 -7 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=(bb65&bb64|bb68
&~bb64)+0x5c4dd124 +bbv[8 ];bb67=((bb67)<<(12 )|(bb67)>>(32 -12 ))+bb62;
bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb62+=(bb67&bb68|bb65&~bb68)+
0x5c4dd124 +bbv[12 ];bb62=((bb62)<<(7 )|(bb62)>>(32 -7 ))+bb64;bb65=((bb65
)<<(10 )|(bb65)>>(32 -10 ));bb64+=(bb62&bb65|bb67&~bb65)+0x5c4dd124 +bbv[
4 ];bb64=((bb64)<<(6 )|(bb64)>>(32 -6 ))+bb68;bb67=((bb67)<<(10 )|(bb67)>>
(32 -10 ));bb68+=(bb64&bb67|bb62&~bb67)+0x5c4dd124 +bbv[9 ];bb68=((bb68)<<
(15 )|(bb68)>>(32 -15 ))+bb65;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));bb65+=
(bb68&bb62|bb64&~bb62)+0x5c4dd124 +bbv[1 ];bb65=((bb65)<<(13 )|(bb65)>>(
32 -13 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=(bb65&bb64|
bb68&~bb64)+0x5c4dd124 +bbv[2 ];bb67=((bb67)<<(11 )|(bb67)>>(32 -11 ))+
bb62;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb62+=((bb67|~bb65)^bb68)+
0x6d703ef3 +bbv[15 ];bb62=((bb62)<<(9 )|(bb62)>>(32 -9 ))+bb64;bb65=((bb65
)<<(10 )|(bb65)>>(32 -10 ));bb64+=((bb62|~bb67)^bb65)+0x6d703ef3 +bbv[5 ];
bb64=((bb64)<<(7 )|(bb64)>>(32 -7 ))+bb68;bb67=((bb67)<<(10 )|(bb67)>>(32
-10 ));bb68+=((bb64|~bb62)^bb67)+0x6d703ef3 +bbv[1 ];bb68=((bb68)<<(15 )|
(bb68)>>(32 -15 ))+bb65;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));bb65+=((
bb68|~bb64)^bb62)+0x6d703ef3 +bbv[3 ];bb65=((bb65)<<(11 )|(bb65)>>(32 -11
))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=((bb65|~bb68)^bb64)+
0x6d703ef3 +bbv[7 ];bb67=((bb67)<<(8 )|(bb67)>>(32 -8 ))+bb62;bb68=((bb68)<<
(10 )|(bb68)>>(32 -10 ));bb62+=((bb67|~bb65)^bb68)+0x6d703ef3 +bbv[14 ];
bb62=((bb62)<<(6 )|(bb62)>>(32 -6 ))+bb64;bb65=((bb65)<<(10 )|(bb65)>>(32
-10 ));bb64+=((bb62|~bb67)^bb65)+0x6d703ef3 +bbv[6 ];bb64=((bb64)<<(6 )|(
bb64)>>(32 -6 ))+bb68;bb67=((bb67)<<(10 )|(bb67)>>(32 -10 ));bb68+=((bb64|
~bb62)^bb67)+0x6d703ef3 +bbv[9 ];bb68=((bb68)<<(14 )|(bb68)>>(32 -14 ))+
bb65;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));bb65+=((bb68|~bb64)^bb62)+
0x6d703ef3 +bbv[11 ];bb65=((bb65)<<(12 )|(bb65)>>(32 -12 ))+bb67;bb64=((
bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=((bb65|~bb68)^bb64)+0x6d703ef3 +bbv
[8 ];bb67=((bb67)<<(13 )|(bb67)>>(32 -13 ))+bb62;bb68=((bb68)<<(10 )|(bb68
)>>(32 -10 ));bb62+=((bb67|~bb65)^bb68)+0x6d703ef3 +bbv[12 ];bb62=((bb62)<<
(5 )|(bb62)>>(32 -5 ))+bb64;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb64+=((
bb62|~bb67)^bb65)+0x6d703ef3 +bbv[2 ];bb64=((bb64)<<(14 )|(bb64)>>(32 -14
))+bb68;bb67=((bb67)<<(10 )|(bb67)>>(32 -10 ));bb68+=((bb64|~bb62)^bb67)+
0x6d703ef3 +bbv[10 ];bb68=((bb68)<<(13 )|(bb68)>>(32 -13 ))+bb65;bb62=((
bb62)<<(10 )|(bb62)>>(32 -10 ));bb65+=((bb68|~bb64)^bb62)+0x6d703ef3 +bbv
[0 ];bb65=((bb65)<<(13 )|(bb65)>>(32 -13 ))+bb67;bb64=((bb64)<<(10 )|(bb64
)>>(32 -10 ));bb67+=((bb65|~bb68)^bb64)+0x6d703ef3 +bbv[4 ];bb67=((bb67)<<
(7 )|(bb67)>>(32 -7 ))+bb62;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb62+=((
bb67|~bb65)^bb68)+0x6d703ef3 +bbv[13 ];bb62=((bb62)<<(5 )|(bb62)>>(32 -5 ))+
bb64;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb64+=(bb62&bb67|~bb62&bb65)+
0x7a6d76e9 +bbv[8 ];bb64=((bb64)<<(15 )|(bb64)>>(32 -15 ))+bb68;bb67=((
bb67)<<(10 )|(bb67)>>(32 -10 ));bb68+=(bb64&bb62|~bb64&bb67)+0x7a6d76e9 +
bbv[6 ];bb68=((bb68)<<(5 )|(bb68)>>(32 -5 ))+bb65;bb62=((bb62)<<(10 )|(
bb62)>>(32 -10 ));bb65+=(bb68&bb64|~bb68&bb62)+0x7a6d76e9 +bbv[4 ];bb65=(
(bb65)<<(8 )|(bb65)>>(32 -8 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));
bb67+=(bb65&bb68|~bb65&bb64)+0x7a6d76e9 +bbv[1 ];bb67=((bb67)<<(11 )|(
bb67)>>(32 -11 ))+bb62;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb62+=(bb67&
bb65|~bb67&bb68)+0x7a6d76e9 +bbv[3 ];bb62=((bb62)<<(14 )|(bb62)>>(32 -14 ))+
bb64;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb64+=(bb62&bb67|~bb62&bb65)+
0x7a6d76e9 +bbv[11 ];bb64=((bb64)<<(14 )|(bb64)>>(32 -14 ))+bb68;bb67=((
bb67)<<(10 )|(bb67)>>(32 -10 ));bb68+=(bb64&bb62|~bb64&bb67)+0x7a6d76e9 +
bbv[15 ];bb68=((bb68)<<(6 )|(bb68)>>(32 -6 ))+bb65;bb62=((bb62)<<(10 )|(
bb62)>>(32 -10 ));bb65+=(bb68&bb64|~bb68&bb62)+0x7a6d76e9 +bbv[0 ];bb65=(
(bb65)<<(14 )|(bb65)>>(32 -14 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));
bb67+=(bb65&bb68|~bb65&bb64)+0x7a6d76e9 +bbv[5 ];bb67=((bb67)<<(6 )|(
bb67)>>(32 -6 ))+bb62;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb62+=(bb67&
bb65|~bb67&bb68)+0x7a6d76e9 +bbv[12 ];bb62=((bb62)<<(9 )|(bb62)>>(32 -9 ))+
bb64;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb64+=(bb62&bb67|~bb62&bb65)+
0x7a6d76e9 +bbv[2 ];bb64=((bb64)<<(12 )|(bb64)>>(32 -12 ))+bb68;bb67=((
bb67)<<(10 )|(bb67)>>(32 -10 ));bb68+=(bb64&bb62|~bb64&bb67)+0x7a6d76e9 +
bbv[13 ];bb68=((bb68)<<(9 )|(bb68)>>(32 -9 ))+bb65;bb62=((bb62)<<(10 )|(
bb62)>>(32 -10 ));bb65+=(bb68&bb64|~bb68&bb62)+0x7a6d76e9 +bbv[9 ];bb65=(
(bb65)<<(12 )|(bb65)>>(32 -12 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));
bb67+=(bb65&bb68|~bb65&bb64)+0x7a6d76e9 +bbv[7 ];bb67=((bb67)<<(5 )|(
bb67)>>(32 -5 ))+bb62;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb62+=(bb67&
bb65|~bb67&bb68)+0x7a6d76e9 +bbv[10 ];bb62=((bb62)<<(15 )|(bb62)>>(32 -15
))+bb64;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb64+=(bb62&bb67|~bb62&
bb65)+0x7a6d76e9 +bbv[14 ];bb64=((bb64)<<(8 )|(bb64)>>(32 -8 ))+bb68;bb67=
((bb67)<<(10 )|(bb67)>>(32 -10 ));bb68+=(bb64^bb62^bb67)+bbv[12 ];bb68=((
bb68)<<(8 )|(bb68)>>(32 -8 ))+bb65;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));
bb65+=(bb68^bb64^bb62)+bbv[15 ];bb65=((bb65)<<(5 )|(bb65)>>(32 -5 ))+bb67
;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));bb67+=(bb65^bb68^bb64)+bbv[10 ];
bb67=((bb67)<<(12 )|(bb67)>>(32 -12 ))+bb62;bb68=((bb68)<<(10 )|(bb68)>>(
32 -10 ));bb62+=(bb67^bb65^bb68)+bbv[4 ];bb62=((bb62)<<(9 )|(bb62)>>(32 -9
))+bb64;bb65=((bb65)<<(10 )|(bb65)>>(32 -10 ));bb64+=(bb62^bb67^bb65)+
bbv[1 ];bb64=((bb64)<<(12 )|(bb64)>>(32 -12 ))+bb68;bb67=((bb67)<<(10 )|(
bb67)>>(32 -10 ));bb68+=(bb64^bb62^bb67)+bbv[5 ];bb68=((bb68)<<(5 )|(bb68
)>>(32 -5 ))+bb65;bb62=((bb62)<<(10 )|(bb62)>>(32 -10 ));bb65+=(bb68^bb64^
bb62)+bbv[8 ];bb65=((bb65)<<(14 )|(bb65)>>(32 -14 ))+bb67;bb64=((bb64)<<(
10 )|(bb64)>>(32 -10 ));bb67+=(bb65^bb68^bb64)+bbv[7 ];bb67=((bb67)<<(6 )|
(bb67)>>(32 -6 ))+bb62;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb62+=(bb67^
bb65^bb68)+bbv[6 ];bb62=((bb62)<<(8 )|(bb62)>>(32 -8 ))+bb64;bb65=((bb65)<<
(10 )|(bb65)>>(32 -10 ));bb64+=(bb62^bb67^bb65)+bbv[2 ];bb64=((bb64)<<(13
)|(bb64)>>(32 -13 ))+bb68;bb67=((bb67)<<(10 )|(bb67)>>(32 -10 ));bb68+=(
bb64^bb62^bb67)+bbv[13 ];bb68=((bb68)<<(6 )|(bb68)>>(32 -6 ))+bb65;bb62=(
(bb62)<<(10 )|(bb62)>>(32 -10 ));bb65+=(bb68^bb64^bb62)+bbv[14 ];bb65=((
bb65)<<(5 )|(bb65)>>(32 -5 ))+bb67;bb64=((bb64)<<(10 )|(bb64)>>(32 -10 ));
bb67+=(bb65^bb68^bb64)+bbv[0 ];bb67=((bb67)<<(15 )|(bb67)>>(32 -15 ))+
bb62;bb68=((bb68)<<(10 )|(bb68)>>(32 -10 ));bb62+=(bb67^bb65^bb68)+bbv[3
];bb62=((bb62)<<(13 )|(bb62)>>(32 -13 ))+bb64;bb65=((bb65)<<(10 )|(bb65)>>
(32 -10 ));bb64+=(bb62^bb67^bb65)+bbv[9 ];bb64=((bb64)<<(11 )|(bb64)>>(32
-11 ))+bb68;bb67=((bb67)<<(10 )|(bb67)>>(32 -10 ));bb68+=(bb64^bb62^bb67)+
bbv[11 ];bb68=((bb68)<<(11 )|(bb68)>>(32 -11 ))+bb65;bb62=((bb62)<<(10 )|(
bb62)>>(32 -10 ));bb62+=bb23[1 ]+bb66;bb23[1 ]=bb23[2 ]+bb48+bb67;bb23[2 ]=
bb23[3 ]+bb69+bb65;bb23[3 ]=bb23[4 ]+bb61+bb68;bb23[4 ]=bb23[0 ]+bb55+bb64
;bb23[0 ]=bb62;}}bbb bb1801(bb529*bbj){bb41 bbd bb23[5 ]={0x67452301 ,
0xefcdab89 ,0x98badcfe ,0x10325476 ,0xc3d2e1f0 };bbj->bb9=0 ;bb81(bbj->
bb23,bb23,bb12(bb23));}bbb bb1295(bb529*bbj,bbh bbb*bb498,bbq bb9){
bbh bbf*bb5=(bbh bbf* )bb498;bbq bb382=bbj->bb9%bb12(bbj->bb101);bbj
->bb9+=bb9;bbm(bb382){bbq bb11=bb12(bbj->bb101)-bb382;bb81(bbj->bb101
+bb382,bb5,((bb9)<(bb11)?(bb9):(bb11)));bbm(bb9<bb11)bb2;bb5+=bb11;
bb9-=bb11;bb1256(bbj->bb23,bbj->bb101);}bb91(;bb9>=bb12(bbj->bb101);
bb9-=bb12(bbj->bb101),bb5+=bb12(bbj->bb101))bb1256(bbj->bb23,bb5);
bb81(bbj->bb101,bb5,bb9);}bbb bb1795(bb529*bbj,bbb*bb14){bbd bb1007[2
]={(bbd)(bbj->bb9<<3 ),(bbd)(bbj->bb9>>29 )};bbf bb438[bb12(bb1007)];
bbq bbz;bb91(bbz=0 ;bbz<bb12(bb438);bbz++)bb438[bbz]=bb1007[bbz/4 ]>>((
bbz%4 ) *8 )&0xff ;{bbf bb1314[]={0x80 },bb1313[bb12(bbj->bb101)]={0 };bbq
bb382=bbj->bb9%bb12(bbj->bb101);bb1295(bbj,bb1314,1 );bb1295(bbj,
bb1313,(bb12(bbj->bb101) *2 -1 -bb12(bb438)-bb382)%bb12(bbj->bb101));}
bb1295(bbj,bb438,bb12(bb438));bb91(bbz=0 ;bbz<bb12(bbj->bb23);bbz++)((
bbf* )bb14)[bbz]=bbj->bb23[bbz/4 ]>>((bbz%4 ) *8 )&0xff ;}bbb bb1924(bbb*
bb14,bbh bbb*bb5,bbq bb9){bb529 bb96;bb1801(&bb96);bb1295(&bb96,bb5,
bb9);bb1795(&bb96,bb14);}bbb bb1973(bbb*bb14,bb82 bb5){bb1924(bb14,
bb5,(bbq)bb1305(bb5));}
