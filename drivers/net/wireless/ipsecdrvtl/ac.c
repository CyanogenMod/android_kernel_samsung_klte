/*
   'aes_xcbc.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Wed Jan 15 12:08:55 2014
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
bbb bb2042(bb943*bbj,bbh bbb*bb71,bbq bb142){bb363 bb2151;bbf bb2183[
16 ];bbj->bb9=0 ;bb32(bb142==16 );bb1097(&bb2151,bb71,bb142);bb997(bbj->
bb1842,0 ,16 );bb997(bb2183,1 ,16 );bb1036(&bb2151,bb2183,bb2183);bb997(
bbj->bb1928,2 ,16 );bb1036(&bb2151,bbj->bb1928,bbj->bb1928);bb997(bbj->
bb1926,3 ,16 );bb1036(&bb2151,bbj->bb1926,bbj->bb1926);bb1097(&bbj->
bb2119,bb2183,bb142);}bb41 bbb bb1256(bb943*bbj,bbh bbf*bb5){bbq bbz;
bb91(bbz=0 ;bbz<16 ;bbz++)bbj->bb1842[bbz]^=bb5[bbz];bb1036(&bbj->
bb2119,bbj->bb1842,bbj->bb1842);}bbb bb2094(bb943*bbj,bbh bbb*bb498,
bbq bb9){bbh bbf*bb5=(bbh bbf* )bb498;bbq bb382=bbj->bb9?(bbj->bb9-1 )%
16 +1 :0 ;bbj->bb9+=bb9;bbm(bb382){bbq bb11=16 -bb382;bb81(bbj->bb101+
bb382,bb5,((bb9)<(bb11)?(bb9):(bb11)));bbm(bb9<=bb11)bb2;bb5+=bb11;
bb9-=bb11;bb1256(bbj,bbj->bb101);}bb91(;bb9>16 ;bb9-=16 ,bb5+=16 )bb1256
(bbj,bb5);bb81(bbj->bb101,bb5,bb9);}bbb bb2104(bb943*bbj,bbb*bb14){
bb1 bb3;bbq bbz,bb382=bbj->bb9?(bbj->bb9-1 )%16 +1 :0 ;bbm(bb382<16 ){bbj
->bb101[bb382++]=0x80 ;bb997(bbj->bb101+bb382,0 ,16 -bb382);bb3=bbj->
bb1926;}bb54 bb3=bbj->bb1928;bb91(bbz=0 ;bbz<16 ;bbz++)bbj->bb101[bbz]
^=bb3[bbz];bb1256(bbj,bbj->bb101);bb81(bb14,bbj->bb1842,16 );}
