/*
   'aes_xcbc.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Sun Nov 16 20:01:26 2014
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
bbb bb2042(bb942*bbj,bbh bbb*bb71,bbq bb143){bb365 bb2151;bbf bb2183[
16 ];bbj->bb9=0 ;bb32(bb143==16 );bb1097(&bb2151,bb71,bb143);bb997(bbj->
bb1842,0 ,16 );bb997(bb2183,1 ,16 );bb1036(&bb2151,bb2183,bb2183);bb997(
bbj->bb1928,2 ,16 );bb1036(&bb2151,bbj->bb1928,bbj->bb1928);bb997(bbj->
bb1926,3 ,16 );bb1036(&bb2151,bbj->bb1926,bbj->bb1926);bb1097(&bbj->
bb2119,bb2183,bb143);}bb41 bbb bb1254(bb942*bbj,bbh bbf*bb6){bbq bbz;
bb91(bbz=0 ;bbz<16 ;bbz++)bbj->bb1842[bbz]^=bb6[bbz];bb1036(&bbj->
bb2119,bbj->bb1842,bbj->bb1842);}bbb bb2094(bb942*bbj,bbh bbb*bb492,
bbq bb9){bbh bbf*bb6=(bbh bbf* )bb492;bbq bb385=bbj->bb9?(bbj->bb9-1 )%
16 +1 :0 ;bbj->bb9+=bb9;bbm(bb385){bbq bb11=16 -bb385;bb81(bbj->bb103+
bb385,bb6,((bb9)<(bb11)?(bb9):(bb11)));bbm(bb9<=bb11)bb2;bb6+=bb11;
bb9-=bb11;bb1254(bbj,bbj->bb103);}bb91(;bb9>16 ;bb9-=16 ,bb6+=16 )bb1254
(bbj,bb6);bb81(bbj->bb103,bb6,bb9);}bbb bb2104(bb942*bbj,bbb*bb14){
bb1 bb3;bbq bbz,bb385=bbj->bb9?(bbj->bb9-1 )%16 +1 :0 ;bbm(bb385<16 ){bbj
->bb103[bb385++]=0x80 ;bb997(bbj->bb103+bb385,0 ,16 -bb385);bb3=bbj->
bb1926;}bb54 bb3=bbj->bb1928;bb91(bbz=0 ;bbz<16 ;bbz++)bbj->bb103[bbz]
^=bb3[bbz];bb1254(bbj,bbj->bb103);bb81(bb14,bbj->bb1842,16 );}
