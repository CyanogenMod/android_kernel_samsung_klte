/*
   'src_compress_LZS_lzsc.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Wed Jan 15 12:08:55 2014
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
bba bbi bb1864 bb1864;bba bbi bb1864*bb473;bbd bb2195(bbb);bbb bb2138
(bb473 bb0,bbb*bb1316);bbk bb2175(bb473 bb0,bbf* *bb1740,bbf* *bb1733
,bbd*bb916,bbd*bb599,bbb*bb1316,bbk bb373,bbk bb2160);bbk bb2293(
bb473 bb0,bbf* *bb1740,bbf* *bb1733,bbd*bb916,bbd*bb599,bbb*bb1316,
bbk bb373);
#define bb201 1
#define bb202 0
#define bb1250 bb201
#define bb2377 bb202
bba bbi{bbf*bb1755;bbd bb1030;bbf*bb1744;bbd bb606;bbd bb1273;bbd
bb1746;bbk bb2047;bbf bb1912;bbf bb2610;bbk bb1695;bbd bb542;bbd
bb1839;bbk bb1255;bbd*bb2271;bbd bb2291;bbk bb1336;bbk bb2248;bbk
bb2050;bbk bb2099;bbk bb2061;bbk bb2115;bbk bb1021;bb123 bb1060;bbf
bb1715;bbf bb2609;bb123 bb1947;bbk bb1999;bbk bb1827;}bb2519;bba bbi{
bbf*bb1755;bbd bb1030;bbf*bb1744;bbd bb606;bbk bb2092;bbk bb1758;bbk
bb1167;bbk bb2441;bb123 bb1154;bbk bb1172;bbk bb996;bb123 bb1049;
bb123 bb92;bbd bb464;bbk bb1971;}bb2536;bba bbi{bbf bb1843[2048 ];bbk
bb1873[2048 ];bbd bb2084[4096 ];bb2519 bb44;bbf bb2165[2048 ];bb2536 bb80
;bbf bb1153[64 ];}bb2046;bbi bb1864{bb2046*bb448;bb2046 bb13;bbk bb2112
;bbk bb1750;};bba bbi bb2583{bbk bb2317;bb123 bb47;}bb2452;bb41 bb2452
bb2157[24 ]={{0x0 ,0 },{0x0 ,0 },{0x0 ,2 },{0x1 ,2 },{0x2 ,2 },{0xC ,4 },{0xD ,4 },{
0xE ,4 },{0xF0 ,8 },{0xF1 ,8 },{0xF2 ,8 },{0xF3 ,8 },{0xF4 ,8 },{0xF5 ,8 },{0xF6 ,8 }
,{0xF7 ,8 },{0xF8 ,8 },{0xF9 ,8 },{0xFA ,8 },{0xFB ,8 },{0xFC ,8 },{0xFD ,8 },{0xFE
,8 }};bb41 bbk bb2483[5 ][3 ]={{1 ,1 ,1 },{1 ,1 ,1 },{0 ,0 ,1 },{0 ,0 ,1 },{0 ,1 ,1 }};
bb10{bb2230,bb2563,bb2489,bb2474,bb2389};bb10{bb2083,bb2347,bb2383,
bb2350,bb2309,bb2308,bb2422,bb2237,bb2366};bb41 bbb bb2224(bb473 bb0);
bb41 bbb bb2375(bb473 bb0);bb41 bbb bb1099(bb473 bb0);bb41 bbb bb2382
(bb473 bb0);bb41 bbb bb2128(bbd*bb2410,bbd bb2324);bb41 bbb bb2077(
bb473 bb0,bbk bb2158,bbd bb2100);bb41 bbb bb2123(bb473 bb0);bb41 bbk
bb2283(bb473 bb0);bb41 bbk bb1847(bb473 bb0);bb41 bbb bb2073(bb473 bb0
,bbf bbo);bbd bb2195(bbb){bb2 bb12(bb1864);}bb41 bbb bb2224(bb473 bb0
){bb0->bb13.bb44.bb1947=8 ;bb0->bb13.bb44.bb1715=0 ;bb0->bb13.bb44.
bb1336=bb0->bb13.bb44.bb1695=0 ;bb0->bb13.bb44.bb542=bb0->bb13.bb44.
bb1839=0 ;bb0->bb13.bb44.bb2115=bb0->bb13.bb44.bb1827=0 ;bb2;}bbb bb2138
(bb473 bb0,bbb*bb1316){bb0->bb448=(bb2046* )bb1316;bb0->bb13.bb44=bb0
->bb448->bb44;bb0->bb13.bb44.bb1273=0xFFFFFFFFL ;bb0->bb13.bb44.bb1746
=bb0->bb13.bb44.bb1273-1 ;bb0->bb13.bb44.bb1999=0 ;bb2224(bb0);bb2128(
bb0->bb448->bb2084,0xC0000000L );bb0->bb448->bb44=bb0->bb13.bb44;bb0->
bb13.bb80=bb0->bb448->bb80;bb0->bb13.bb80.bb2092=0 ;bb2123(bb0);bb0->
bb448->bb80=bb0->bb13.bb80;bb2;}bb41 bbb bb2128(bbd*bb2410,bbd bb2324
){bbk bbz;bb91(bbz=0 ;bbz<4096 ;bbz++) *bb2410++=bb2324;bb2;}bb41 bbb
bb2375(bb473 bb0){bb931 bbk bbz;bbd*bb2134;bbd bb2222;bb2222=
0xC0000000L ;bbm(bb0->bb13.bb44.bb1273!=0 )bb2222=0x40000000L ;bb2134=
bb0->bb448->bb2084;bb91(bbz=0 ;bbz<4096 ;bbz++,bb2134++)bbm(bb0->bb13.
bb44.bb1273- *bb2134>2048 -2 ) *bb2134=bb2222;bb2;}bb41 bbb bb1099(
bb473 bb0){bb931 bb123 bb1969;bbm(bb0->bb13.bb44.bb606==0 )bb0->bb13.
bb44.bb1999=1 ;bbm((bb1969=bb0->bb13.bb44.bb1060-bb0->bb13.bb44.bb1947
)>0 ){bb0->bb13.bb44.bb1715|=(bb0->bb13.bb44.bb1021>>bb1969);bb0->bb13
.bb44.bb1947=8 ; *bb0->bb13.bb44.bb1744++=bb0->bb13.bb44.bb1715;--bb0
->bb13.bb44.bb606;bb0->bb13.bb44.bb1715=0 ;bb0->bb13.bb44.bb1021&=((1
<<bb1969)-1 );bb0->bb13.bb44.bb1060=bb1969;bb1099(bb0);}bb54 bbm(
bb1969<0 ){bb0->bb13.bb44.bb1715|=(bb0->bb13.bb44.bb1021<<-bb1969);bb0
->bb13.bb44.bb1947-=bb0->bb13.bb44.bb1060;}bb54{bb0->bb13.bb44.bb1715
|=bb0->bb13.bb44.bb1021;bb0->bb13.bb44.bb1947=8 ; *bb0->bb13.bb44.
bb1744++=bb0->bb13.bb44.bb1715;--bb0->bb13.bb44.bb606;bb0->bb13.bb44.
bb1715=0 ;}bb2;}bb41 bbb bb2382(bb473 bb0){bb0->bb13.bb44.bb1021=(
0x180 );bb0->bb13.bb44.bb1060=(9 );bb1099(bb0);bbm(bb0->bb13.bb44.
bb1947!=8 ){ *bb0->bb13.bb44.bb1744++=bb0->bb13.bb44.bb1715;--bb0->
bb13.bb44.bb606;bbm(bb0->bb13.bb44.bb606==0 ){bb0->bb13.bb44.bb1999=1 ;
}}bb0->bb13.bb44.bb1947=8 ;bb0->bb13.bb44.bb1715=0 ;bb2;}bb41 bbb bb2077
(bb473 bb0,bbk bb2158,bbd bb2100){bbm(bb0->bb13.bb44.bb1827==0 ){bbm(
bb2158<128 ){bb0->bb13.bb44.bb1021=(0x180 |bb2158);bb0->bb13.bb44.
bb1060=(9 );bb1099(bb0);}bb54{bb0->bb13.bb44.bb1021=(0x1000 |bb2158);
bb0->bb13.bb44.bb1060=(13 );bb1099(bb0);}}bbm(bb2100>=23 ){bb0->bb13.
bb44.bb1021=(((1 <<4 )-1 ));bb0->bb13.bb44.bb1060=(4 );bb1099(bb0);bb2100
-=((1 <<4 )-1 );bb0->bb13.bb44.bb1839+=((1 <<4 )-1 );bb0->bb13.bb44.bb1827=
1 ;}bb54{bb0->bb13.bb44.bb1021=(bb2157[(bbk)bb2100].bb2317);bb0->bb13.
bb44.bb1060=(bb2157[(bbk)bb2100].bb47);bb1099(bb0);bb0->bb13.bb44.
bb1827=0 ;bb0->bb13.bb44.bb542=0 ;bb0->bb13.bb44.bb1839=0 ;bb0->bb1750=
bb2389;}bb2;}bb41 bbb bb2196(bb473 bb0,bbk bb373){bbm(bb0->bb13.bb44.
bb2115==1 ){bbm(bb0->bb13.bb44.bb542==0 ){bb0->bb13.bb44.bb1021=((bb0->
bb13.bb44.bb1912));bb0->bb13.bb44.bb1060=(9 );bb1099(bb0);bb0->bb1750=
bb2230;}bb54 bb2077(bb0,bb0->bb13.bb44.bb1336,bb0->bb13.bb44.bb542);}
bb2382(bb0);bbm((bb373&0x04 )==0 ){bbm(0 -bb0->bb13.bb44.bb1273>=2048 )bb2128
(bb0->bb448->bb2084,0xC0000000L );bb54 bbm(0x80000000L -bb0->bb13.bb44.
bb1273>=2048 )bb2128(bb0->bb448->bb2084,0x40000000L );bb0->bb13.bb44.
bb1273+=2048 ;bb0->bb13.bb44.bb1746+=2048 ;bb2224(bb0);}bb0->bb13.bb44.
bb2115=0 ;bb2;}bbk bb2175(bb473 bb0,bbf* *bb1740,bbf* *bb1733,bbd*
bb916,bbd*bb599,bbb*bb1316,bbk bb373,bbk bb2160){bb931 bbk bb2184;
bb931 bbk bb2040;bbk bb2169;bbk bb1042=0 ;bb0->bb448=(bb2046* )bb1316;
bb0->bb13.bb44=bb0->bb448->bb44;bb0->bb13.bb44.bb1755= *bb1740;bb0->
bb13.bb44.bb1030= *bb916;bb0->bb13.bb44.bb1744= *bb1733;bb0->bb13.
bb44.bb606= *bb599;bb0->bb13.bb44.bb1999=0 ;bb0->bb2112=0X0018 &bb373;
bbm(bb0->bb2112>0x0010 ){bb0->bb2112=0x0010 ;}bb0->bb2112>>=3 ;bbm( *
bb599<=15 )bb1042=0 ;bb54 bbm(bb0->bb13.bb44.bb1030!=0 ){bb0->bb13.bb44.
bb606-=15 ;bbm(bb0->bb13.bb44.bb2115==0 ){bb0->bb13.bb44.bb1912= *bb0->
bb13.bb44.bb1755++;--bb0->bb13.bb44.bb1030;++bb0->bb13.bb44.bb1273;++
bb0->bb13.bb44.bb1746;bb0->bb13.bb44.bb2047=(bbk)bb0->bb13.bb44.
bb1746&(2048 -1 );bb0->bb448->bb1843[(bbk)bb0->bb13.bb44.bb1273&(2048 -1
)]=bb0->bb13.bb44.bb1912;bb0->bb13.bb44.bb1695=(bb0->bb13.bb44.bb1695
<<8 )+bb0->bb13.bb44.bb1912;bb0->bb13.bb44.bb2115=1 ;}bb107((bb0->bb13.
bb44.bb1030!=0 )&&(bb0->bb13.bb44.bb1999==0 )){++bb0->bb13.bb44.bb1273;
++bb0->bb13.bb44.bb1746;bb0->bb13.bb44.bb2047=(bbk)bb0->bb13.bb44.
bb1746&(2048 -1 );bbm(((bb0->bb13.bb44.bb1273&0x7FFFFFFFL )==0 ))bb2375(
bb0);bb0->bb448->bb1843[(bbk)bb0->bb13.bb44.bb1273&(2048 -1 )]=bb0->
bb13.bb44.bb1912= *bb0->bb13.bb44.bb1755++;bb0->bb13.bb44.bb1695=(bb0
->bb13.bb44.bb1695<<8 )+bb0->bb13.bb44.bb1912;--bb0->bb13.bb44.bb1030;
bb0->bb13.bb44.bb2271=bb0->bb448->bb2084+((((bb0->bb13.bb44.bb1695)&
0xFF00 )>>4 )^((bb0->bb13.bb44.bb1695)&0x00FF ));bbm((bb0->bb13.bb44.
bb2291=bb0->bb13.bb44.bb1746- *bb0->bb13.bb44.bb2271)>2048 -2 ){bb0->
bb448->bb1873[bb0->bb13.bb44.bb2047]=0 ;bbm(bb0->bb13.bb44.bb542!=0 ){
bb2077(bb0,bb0->bb13.bb44.bb1336,bb0->bb13.bb44.bb542);}bb54{bb0->
bb13.bb44.bb1021=((bb0->bb13.bb44.bb1695>>8 ));bb0->bb13.bb44.bb1060=(
9 );bb1099(bb0);bb0->bb1750=bb2230;}}bb54{bb0->bb448->bb1873[bb0->bb13
.bb44.bb2047]=(bbk)bb0->bb13.bb44.bb2291;bbm(bb0->bb13.bb44.bb542!=0 ){
bbm((bb0->bb448->bb1843[(bbk)(((bbd)bb0->bb13.bb44.bb1255+bb0->bb13.
bb44.bb542+bb0->bb13.bb44.bb1839)&(bbd)(2048 -1 ))]==bb0->bb13.bb44.
bb1912)&&((bb0->bb13.bb44.bb542+bb0->bb13.bb44.bb1839)<(bbd)0xFFFFFFFFL
)){++bb0->bb13.bb44.bb542;bb0->bb1750=bb2489;bbm(bb0->bb13.bb44.
bb1827){bbm(bb0->bb13.bb44.bb542>=23 ){bb0->bb13.bb44.bb1021=(((1 <<4 )-
1 ));bb0->bb13.bb44.bb1060=(4 );bb1099(bb0);bb0->bb13.bb44.bb542-=((1 <<
4 )-1 );bb0->bb13.bb44.bb1839+=((1 <<4 )-1 );}}bb54 bbm(bb0->bb13.bb44.
bb542>=23 ){bbm(bb0->bb13.bb44.bb1336<128 ){bb0->bb13.bb44.bb1021=(
0x180 |bb0->bb13.bb44.bb1336);bb0->bb13.bb44.bb1060=(9 );bb1099(bb0);}
bb54{bb0->bb13.bb44.bb1021=(0x1000 |bb0->bb13.bb44.bb1336);bb0->bb13.
bb44.bb1060=(13 );bb1099(bb0);}bb0->bb13.bb44.bb1021=(((1 <<4 )-1 ));bb0
->bb13.bb44.bb1060=(4 );bb1099(bb0);bb0->bb13.bb44.bb542-=((1 <<4 )-1 );
bb0->bb13.bb44.bb1839+=((1 <<4 )-1 );bb0->bb13.bb44.bb1827=1 ;}}bb54 bbm(
bb0->bb13.bb44.bb1827){bb0->bb13.bb44.bb1021=(bb2157[(bbk)bb0->bb13.
bb44.bb542].bb2317);bb0->bb13.bb44.bb1060=(bb2157[(bbk)bb0->bb13.bb44
.bb542].bb47);bb1099(bb0);bb0->bb13.bb44.bb542=0 ;bb0->bb13.bb44.
bb1839=0 ;bb0->bb13.bb44.bb1827=0 ;bb0->bb1750=bb2389;}bb54 bbm(bb0->
bb13.bb44.bb542>=8 ){bb2077(bb0,bb0->bb13.bb44.bb1336,bb0->bb13.bb44.
bb542);}bb54{bb2040=0 ;bb0->bb13.bb44.bb2099=bb0->bb13.bb44.bb1336;
bb107((bb0->bb448->bb1873[bb0->bb13.bb44.bb1255]!=0 )&&(bb2040==0 )&&(
bb0->bb13.bb44.bb2061<bb2160)&&(bb0->bb13.bb44.bb2099<(bbk)(2048 -bb0
->bb13.bb44.bb542))){bb0->bb13.bb44.bb2099+=bb0->bb448->bb1873[bb0->
bb13.bb44.bb1255];++bb0->bb13.bb44.bb2061;bbm(bb0->bb13.bb44.bb2099<(
bbk)(2048 -bb0->bb13.bb44.bb542)){bb0->bb13.bb44.bb1255=bb0->bb13.bb44
.bb1255-bb0->bb448->bb1873[bb0->bb13.bb44.bb1255]&(2048 -1 );bbm(bb0->
bb448->bb1843[bb0->bb13.bb44.bb1255]==bb0->bb448->bb1843[bb0->bb13.
bb44.bb2248]){bb2040=1 ;bb91(bb2184=2 ,bb2169=(bb0->bb13.bb44.bb1255+2 )&
(2048 -1 );bb2184<=(bbk)bb0->bb13.bb44.bb542;bb2184++,bb2169=(bb2169+1 )&
(2048 -1 )){bbm(bb0->bb448->bb1843[bb2169]!=bb0->bb448->bb1843[(bb0->
bb13.bb44.bb2248+bb2184)&(2048 -1 )]){bb2040=0 ;bb21;}}}}}bbm(bb2040){
bb0->bb13.bb44.bb1336=bb0->bb13.bb44.bb2099;++bb0->bb13.bb44.bb542;
bb0->bb1750=bb2474;}bb54{bb2077(bb0,bb0->bb13.bb44.bb1336,bb0->bb13.
bb44.bb542);}}}bb54{bb0->bb13.bb44.bb2050=(bbk)bb0->bb13.bb44.bb2291;
bb0->bb13.bb44.bb2061=0 ;bb574{bb0->bb13.bb44.bb1255=(bbk)(bb0->bb13.
bb44.bb1746-bb0->bb13.bb44.bb2050&(2048 -1 ));bbm(bb0->bb448->bb1843[
bb0->bb13.bb44.bb1255]==(bbf)(bb0->bb13.bb44.bb1695>>8 )){bb0->bb13.
bb44.bb542=2 ;bb0->bb13.bb44.bb2248=bb0->bb13.bb44.bb2047;bb0->bb13.
bb44.bb1336=bb0->bb13.bb44.bb2050;bb0->bb1750=bb2563;bb21;}bb54{bb0->
bb13.bb44.bb2050+=bb0->bb448->bb1873[bb0->bb13.bb44.bb1255];++bb0->
bb13.bb44.bb2061;}}bb107((bb0->bb448->bb1873[bb0->bb13.bb44.bb1255]!=
0 )&&(bb0->bb13.bb44.bb2061<bb2160)&&(bb0->bb13.bb44.bb2050<2048 -2 ));
bbm(bb0->bb13.bb44.bb542==0 ){bb0->bb13.bb44.bb1021=((bb0->bb13.bb44.
bb1695>>8 ));bb0->bb13.bb44.bb1060=(9 );bb1099(bb0);bb0->bb1750=bb2230;
}}}bbm(bb2483[bb0->bb1750][bb0->bb2112]){ *bb0->bb13.bb44.bb2271=bb0
->bb13.bb44.bb1746;}}bbm(bb0->bb13.bb44.bb1030==0 ){bb1042=1 ;bbm(bb373
&0x01 ){bb2196(bb0,bb373);bb1042|=4 ;}}bbm((bb0->bb13.bb44.bb606==0 )||(
bb0->bb13.bb44.bb1999)){bbm(!(bb1042&1 )){bb1042=2 ;bbm(bb373&0x02 ){
bb2196(bb0,bb373);bb1042|=4 ;}}bb54{bb1042|=3 ;bbm((!(bb373&0x01 ))&&(
bb373&0x02 )){bb2196(bb0,bb373);bb1042|=4 ;}}}bb0->bb13.bb44.bb606+=15 ;
}bb54{bb1042=1 ;bbm(bb373&0x01 ){bb2196(bb0,bb373);bb1042|=4 ;}}bb0->
bb448->bb44=bb0->bb13.bb44; *bb1740=bb0->bb13.bb44.bb1755; *bb916=bb0
->bb13.bb44.bb1030; *bb1733=bb0->bb13.bb44.bb1744; *bb599=bb0->bb13.
bb44.bb606;bb2(bb1042);}bb41 bbb bb2123(bb473 bb0){bb0->bb13.bb80.
bb2092&=(2048 -1 );bb0->bb13.bb80.bb1049=bb0->bb13.bb80.bb1154=bb0->
bb13.bb80.bb92=0 ;bb0->bb13.bb80.bb996=bb0->bb13.bb80.bb1758=bb0->bb13
.bb80.bb1172=0 ;bb0->bb13.bb80.bb464=0 ;bb0->bb13.bb80.bb1971=0 ;bb0->
bb13.bb80.bb1167=bb2083;bb0->bb13.bb80.bb2441=1 ;bb2;}bb41 bbk bb2283(
bb473 bb0){bbm((bb0->bb13.bb80.bb1030==0 )&&(bb0->bb13.bb80.bb1049==0 ))bb0
->bb13.bb80.bb996=bb2377;bb54{bb0->bb13.bb80.bb996=bb1250;bbm(bb0->
bb13.bb80.bb1049==0 ){bb0->bb13.bb80.bb1758= *bb0->bb13.bb80.bb1755++;
--bb0->bb13.bb80.bb1030;bb0->bb13.bb80.bb1049=7 ;bb0->bb13.bb80.bb1172
=(bb0->bb13.bb80.bb1758>127 )?1 :0 ;bb0->bb13.bb80.bb1758&=((bbf)0x7F );}
bb54{bb0->bb13.bb80.bb1172=(bb0->bb13.bb80.bb1758>>(bb0->bb13.bb80.
bb1049-1 ));--bb0->bb13.bb80.bb1049;bb0->bb13.bb80.bb1758&=((bbf)0xFF
>>(8 -bb0->bb13.bb80.bb1049));}}bb2(bb0->bb13.bb80.bb996);}bb41 bbk
bb1847(bb473 bb0){bbk bb2156;bb123 bb8;bbm(bb0->bb13.bb80.bb996==
bb1250)bb0->bb13.bb80.bb1172=0 ;bb54 bb0->bb13.bb80.bb996=bb1250;bb107
((bb0->bb13.bb80.bb1154>0 )&&(bb0->bb13.bb80.bb996==bb1250)){bbm((bb0
->bb13.bb80.bb1030==0 )&&(bb0->bb13.bb80.bb1049==0 ))bb0->bb13.bb80.
bb996=bb2377;bb54{bbm(bb0->bb13.bb80.bb1049==0 ){bb0->bb13.bb80.bb1758
= *bb0->bb13.bb80.bb1755++;--bb0->bb13.bb80.bb1030;bb0->bb13.bb80.
bb1049=8 ;}bb2156=bb0->bb13.bb80.bb1758;bbm((bb8=bb0->bb13.bb80.bb1154
-bb0->bb13.bb80.bb1049)>0 )bb2156<<=bb8;bb54 bb2156>>=-bb8;bb0->bb13.
bb80.bb1172|=bb2156;bb8=((((8 )<(bb0->bb13.bb80.bb1154)?(8 ):(bb0->bb13
.bb80.bb1154)))<(bb0->bb13.bb80.bb1049)?(((8 )<(bb0->bb13.bb80.bb1154)?
(8 ):(bb0->bb13.bb80.bb1154))):(bb0->bb13.bb80.bb1049));bb0->bb13.bb80
.bb1154-=bb8;bb0->bb13.bb80.bb1049-=bb8;bb0->bb13.bb80.bb1758&=((bbf)0xFF
>>(8 -bb0->bb13.bb80.bb1049));}}bb2(bb0->bb13.bb80.bb996);}bb41 bbb
bb2073(bb473 bb0,bbf bbo){bbm(bb0->bb13.bb80.bb606!=0 ){ *bb0->bb13.
bb80.bb1744++=bbo;--bb0->bb13.bb80.bb606;bb0->bb448->bb2165[bb0->bb13
.bb80.bb2092++]=(bbf)bbo;bb0->bb13.bb80.bb2092&=(2048 -1 );}}bbk bb2293
(bb473 bb0,bbf* *bb1740,bbf* *bb1733,bbd*bb916,bbd*bb599,bbb*bb1316,
bbk bb373){bbk bb2200=0 ;bbk bb1042=0 ;bb0->bb448=(bb2046* )bb1316;bb0
->bb13.bb80=bb0->bb448->bb80;bb0->bb13.bb80.bb1755= *bb1740;bb0->bb13
.bb80.bb1030= *bb916;bb0->bb13.bb80.bb1744= *bb1733;bb0->bb13.bb80.
bb606= *bb599;bbm(bb373&0x01 ){bb2123(bb0);}bbm((bb0->bb13.bb80.bb1030
!=0 )&&(bb0->bb13.bb80.bb606!=0 )){bb107((bb0->bb13.bb80.bb606!=0 )&&((
bb0->bb13.bb80.bb1030!=0 )||(bb0->bb13.bb80.bb1049!=0 ))&&(bb2200==0 )){
bbm(bb0->bb13.bb80.bb1971){bb107((bb0->bb13.bb80.bb606!=0 )&&(bb0->
bb13.bb80.bb464>0 )){bb0->bb13.bb80.bb92&=(2048 -1 );bb2073(bb0,bb0->
bb448->bb2165[bb0->bb13.bb80.bb92++]);--bb0->bb13.bb80.bb464;}bbm(bb0
->bb13.bb80.bb464==0 )bb0->bb13.bb80.bb1971=0 ;bb0->bb13.bb80.bb1167=
bb2083;}bb54{bb296(bb0->bb13.bb80.bb1167){bb15 bb2083:bb2283(bb0);bbm
(bb0->bb13.bb80.bb1172==0 ){bb0->bb13.bb80.bb1154=8 ;bb0->bb13.bb80.
bb1167=bb2347;bb15 bb2347:bb1847(bb0);bbm(bb0->bb13.bb80.bb996==
bb1250){bb2073(bb0,(bbf)bb0->bb13.bb80.bb1172);bb0->bb13.bb80.bb1167=
bb2083;}}bb54{bb0->bb13.bb80.bb1167=bb2383;bb15 bb2383:bb2283(bb0);
bbm(bb0->bb13.bb80.bb996==bb1250){bb0->bb13.bb80.bb1154=bb0->bb13.
bb80.bb1172?7 :11 ;bb0->bb13.bb80.bb1167=bb2350;bb15 bb2350:bb1847(bb0);
bbm(bb0->bb13.bb80.bb996==bb1250){bb0->bb13.bb80.bb92=bb0->bb13.bb80.
bb1172;bbm(bb0->bb13.bb80.bb92==0 )bb2200=1 ;bb54{bb0->bb13.bb80.bb92=
bb0->bb13.bb80.bb2092-bb0->bb13.bb80.bb92;bb0->bb13.bb80.bb1154=2 ;bb0
->bb13.bb80.bb1167=bb2309;bb15 bb2309:bb1847(bb0);bbm(bb0->bb13.bb80.
bb996==bb1250){bb0->bb13.bb80.bb464=2 +bb0->bb13.bb80.bb1172;bbm(bb0->
bb13.bb80.bb464==5 ){bb0->bb13.bb80.bb1154=2 ;bb0->bb13.bb80.bb1167=
bb2308;bb15 bb2308:bb1847(bb0);bbm(bb0->bb13.bb80.bb996==bb1250){bb0
->bb13.bb80.bb464+=bb0->bb13.bb80.bb1172;bbm(bb0->bb13.bb80.bb464==8 ){
bb0->bb13.bb80.bb1154=4 ;bb0->bb13.bb80.bb1167=bb2422;bb15 bb2422:
bb1847(bb0);bbm(bb0->bb13.bb80.bb996==bb1250){bb0->bb13.bb80.bb464+=
bb0->bb13.bb80.bb1172;bbm(bb0->bb13.bb80.bb464==23 ){bb574{bb15 bb2237
:bb107((bb0->bb13.bb80.bb606!=0 )&&(bb0->bb13.bb80.bb464>0 )){bb0->bb13
.bb80.bb92&=(2048 -1 );bb2073(bb0,bb0->bb448->bb2165[bb0->bb13.bb80.
bb92++]);--bb0->bb13.bb80.bb464;}bbm(bb0->bb13.bb80.bb606==0 ){bb0->
bb13.bb80.bb1167=bb2237;bb21;}bb54{bb0->bb13.bb80.bb1154=4 ;bb0->bb13.
bb80.bb1167=bb2366;bb15 bb2366:bb1847(bb0);bbm(bb0->bb13.bb80.bb996==
bb1250)bb0->bb13.bb80.bb464+=bb0->bb13.bb80.bb1172;bb54 bb21;}}bb107(
bb0->bb13.bb80.bb1172==((1 <<4 )-1 ));}}}}}}bbm((bb0->bb13.bb80.bb996==
bb1250)&&(bb0->bb13.bb80.bb1167!=bb2237)){bb0->bb13.bb80.bb1971=1 ;}}}
}}}}}bbm(bb0->bb13.bb80.bb1971){bb107((bb0->bb13.bb80.bb606!=0 )&&(bb0
->bb13.bb80.bb464>0 )){bb0->bb13.bb80.bb92&=(2048 -1 );bb2073(bb0,bb0->
bb448->bb2165[bb0->bb13.bb80.bb92++]);--bb0->bb13.bb80.bb464;}bbm(bb0
->bb13.bb80.bb464==0 )bb0->bb13.bb80.bb1971=0 ;bb0->bb13.bb80.bb1167=
bb2083;}}bbm(bb2200){bb2123(bb0);bb1042|=4 ;}bbm(bb0->bb13.bb80.bb1030
==0 ){bb1042|=1 ;}bbm(bb0->bb13.bb80.bb606==0 ){bb1042|=2 ;}bb0->bb448->
bb80=bb0->bb13.bb80; *bb1740=bb0->bb13.bb80.bb1755; *bb916=bb0->bb13.
bb80.bb1030; *bb1733=bb0->bb13.bb80.bb1744; *bb599=bb0->bb13.bb80.
bb606;bb2(bb1042);}
