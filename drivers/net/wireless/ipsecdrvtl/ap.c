/*
   'src_compress_LZS_lzsc.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Sun Nov 16 20:01:26 2014
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
bba bbi bb1864 bb1864;bba bbi bb1864*bb474;bbd bb2195(bbb);bbb bb2137
(bb474 bb0,bbb*bb1315);bbk bb2175(bb474 bb0,bbf* *bb1739,bbf* *bb1733
,bbd*bb916,bbd*bb607,bbb*bb1315,bbk bb374,bbk bb2159);bbk bb2293(
bb474 bb0,bbf* *bb1739,bbf* *bb1733,bbd*bb916,bbd*bb607,bbb*bb1315,
bbk bb374);
#define bb202 1
#define bb201 0
#define bb1248 bb202
#define bb2377 bb201
bba bbi{bbf*bb1754;bbd bb1028;bbf*bb1743;bbd bb598;bbd bb1272;bbd
bb1745;bbk bb2048;bbf bb1911;bbf bb2611;bbk bb1693;bbd bb549;bbd
bb1839;bbk bb1253;bbd*bb2271;bbd bb2290;bbk bb1288;bbk bb2248;bbk
bb2050;bbk bb2099;bbk bb2061;bbk bb2115;bbk bb1021;bb123 bb1057;bbf
bb1564;bbf bb2610;bb123 bb1947;bbk bb1999;bbk bb1822;}bb2519;bba bbi{
bbf*bb1754;bbd bb1028;bbf*bb1743;bbd bb598;bbk bb2092;bbk bb1757;bbk
bb1165;bbk bb2441;bb123 bb1154;bbk bb1172;bbk bb995;bb123 bb1049;
bb123 bb92;bbd bb465;bbk bb1971;}bb2536;bba bbi{bbf bb1843[2048 ];bbk
bb1873[2048 ];bbd bb2084[4096 ];bb2519 bb44;bbf bb2165[2048 ];bb2536 bb80
;bbf bb1153[64 ];}bb2046;bbi bb1864{bb2046*bb449;bb2046 bb13;bbk bb2113
;bbk bb1749;};bba bbi bb2584{bbk bb2317;bb123 bb47;}bb2452;bb41 bb2452
bb2157[24 ]={{0x0 ,0 },{0x0 ,0 },{0x0 ,2 },{0x1 ,2 },{0x2 ,2 },{0xC ,4 },{0xD ,4 },{
0xE ,4 },{0xF0 ,8 },{0xF1 ,8 },{0xF2 ,8 },{0xF3 ,8 },{0xF4 ,8 },{0xF5 ,8 },{0xF6 ,8 }
,{0xF7 ,8 },{0xF8 ,8 },{0xF9 ,8 },{0xFA ,8 },{0xFB ,8 },{0xFC ,8 },{0xFD ,8 },{0xFE
,8 }};bb41 bbk bb2482[5 ][3 ]={{1 ,1 ,1 },{1 ,1 ,1 },{0 ,0 ,1 },{0 ,0 ,1 },{0 ,1 ,1 }};
bb10{bb2230,bb2563,bb2489,bb2474,bb2390};bb10{bb2083,bb2347,bb2383,
bb2350,bb2309,bb2308,bb2423,bb2237,bb2366};bb41 bbb bb2224(bb474 bb0);
bb41 bbb bb2375(bb474 bb0);bb41 bbb bb1101(bb474 bb0);bb41 bbb bb2382
(bb474 bb0);bb41 bbb bb2128(bbd*bb2411,bbd bb2325);bb41 bbb bb2077(
bb474 bb0,bbk bb2158,bbd bb2100);bb41 bbb bb2123(bb474 bb0);bb41 bbk
bb2283(bb474 bb0);bb41 bbk bb1847(bb474 bb0);bb41 bbb bb2073(bb474 bb0
,bbf bbo);bbd bb2195(bbb){bb2 bb12(bb1864);}bb41 bbb bb2224(bb474 bb0
){bb0->bb13.bb44.bb1947=8 ;bb0->bb13.bb44.bb1564=0 ;bb0->bb13.bb44.
bb1288=bb0->bb13.bb44.bb1693=0 ;bb0->bb13.bb44.bb549=bb0->bb13.bb44.
bb1839=0 ;bb0->bb13.bb44.bb2115=bb0->bb13.bb44.bb1822=0 ;bb2;}bbb bb2137
(bb474 bb0,bbb*bb1315){bb0->bb449=(bb2046* )bb1315;bb0->bb13.bb44=bb0
->bb449->bb44;bb0->bb13.bb44.bb1272=0xFFFFFFFFL ;bb0->bb13.bb44.bb1745
=bb0->bb13.bb44.bb1272-1 ;bb0->bb13.bb44.bb1999=0 ;bb2224(bb0);bb2128(
bb0->bb449->bb2084,0xC0000000L );bb0->bb449->bb44=bb0->bb13.bb44;bb0->
bb13.bb80=bb0->bb449->bb80;bb0->bb13.bb80.bb2092=0 ;bb2123(bb0);bb0->
bb449->bb80=bb0->bb13.bb80;bb2;}bb41 bbb bb2128(bbd*bb2411,bbd bb2325
){bbk bbz;bb91(bbz=0 ;bbz<4096 ;bbz++) *bb2411++=bb2325;bb2;}bb41 bbb
bb2375(bb474 bb0){bb932 bbk bbz;bbd*bb2134;bbd bb2223;bb2223=
0xC0000000L ;bbm(bb0->bb13.bb44.bb1272!=0 )bb2223=0x40000000L ;bb2134=
bb0->bb449->bb2084;bb91(bbz=0 ;bbz<4096 ;bbz++,bb2134++)bbm(bb0->bb13.
bb44.bb1272- *bb2134>2048 -2 ) *bb2134=bb2223;bb2;}bb41 bbb bb1101(
bb474 bb0){bb932 bb123 bb1969;bbm(bb0->bb13.bb44.bb598==0 )bb0->bb13.
bb44.bb1999=1 ;bbm((bb1969=bb0->bb13.bb44.bb1057-bb0->bb13.bb44.bb1947
)>0 ){bb0->bb13.bb44.bb1564|=(bb0->bb13.bb44.bb1021>>bb1969);bb0->bb13
.bb44.bb1947=8 ; *bb0->bb13.bb44.bb1743++=bb0->bb13.bb44.bb1564;--bb0
->bb13.bb44.bb598;bb0->bb13.bb44.bb1564=0 ;bb0->bb13.bb44.bb1021&=((1
<<bb1969)-1 );bb0->bb13.bb44.bb1057=bb1969;bb1101(bb0);}bb54 bbm(
bb1969<0 ){bb0->bb13.bb44.bb1564|=(bb0->bb13.bb44.bb1021<<-bb1969);bb0
->bb13.bb44.bb1947-=bb0->bb13.bb44.bb1057;}bb54{bb0->bb13.bb44.bb1564
|=bb0->bb13.bb44.bb1021;bb0->bb13.bb44.bb1947=8 ; *bb0->bb13.bb44.
bb1743++=bb0->bb13.bb44.bb1564;--bb0->bb13.bb44.bb598;bb0->bb13.bb44.
bb1564=0 ;}bb2;}bb41 bbb bb2382(bb474 bb0){bb0->bb13.bb44.bb1021=(
0x180 );bb0->bb13.bb44.bb1057=(9 );bb1101(bb0);bbm(bb0->bb13.bb44.
bb1947!=8 ){ *bb0->bb13.bb44.bb1743++=bb0->bb13.bb44.bb1564;--bb0->
bb13.bb44.bb598;bbm(bb0->bb13.bb44.bb598==0 ){bb0->bb13.bb44.bb1999=1 ;
}}bb0->bb13.bb44.bb1947=8 ;bb0->bb13.bb44.bb1564=0 ;bb2;}bb41 bbb bb2077
(bb474 bb0,bbk bb2158,bbd bb2100){bbm(bb0->bb13.bb44.bb1822==0 ){bbm(
bb2158<128 ){bb0->bb13.bb44.bb1021=(0x180 |bb2158);bb0->bb13.bb44.
bb1057=(9 );bb1101(bb0);}bb54{bb0->bb13.bb44.bb1021=(0x1000 |bb2158);
bb0->bb13.bb44.bb1057=(13 );bb1101(bb0);}}bbm(bb2100>=23 ){bb0->bb13.
bb44.bb1021=(((1 <<4 )-1 ));bb0->bb13.bb44.bb1057=(4 );bb1101(bb0);bb2100
-=((1 <<4 )-1 );bb0->bb13.bb44.bb1839+=((1 <<4 )-1 );bb0->bb13.bb44.bb1822=
1 ;}bb54{bb0->bb13.bb44.bb1021=(bb2157[(bbk)bb2100].bb2317);bb0->bb13.
bb44.bb1057=(bb2157[(bbk)bb2100].bb47);bb1101(bb0);bb0->bb13.bb44.
bb1822=0 ;bb0->bb13.bb44.bb549=0 ;bb0->bb13.bb44.bb1839=0 ;bb0->bb1749=
bb2390;}bb2;}bb41 bbb bb2196(bb474 bb0,bbk bb374){bbm(bb0->bb13.bb44.
bb2115==1 ){bbm(bb0->bb13.bb44.bb549==0 ){bb0->bb13.bb44.bb1021=((bb0->
bb13.bb44.bb1911));bb0->bb13.bb44.bb1057=(9 );bb1101(bb0);bb0->bb1749=
bb2230;}bb54 bb2077(bb0,bb0->bb13.bb44.bb1288,bb0->bb13.bb44.bb549);}
bb2382(bb0);bbm((bb374&0x04 )==0 ){bbm(0 -bb0->bb13.bb44.bb1272>=2048 )bb2128
(bb0->bb449->bb2084,0xC0000000L );bb54 bbm(0x80000000L -bb0->bb13.bb44.
bb1272>=2048 )bb2128(bb0->bb449->bb2084,0x40000000L );bb0->bb13.bb44.
bb1272+=2048 ;bb0->bb13.bb44.bb1745+=2048 ;bb2224(bb0);}bb0->bb13.bb44.
bb2115=0 ;bb2;}bbk bb2175(bb474 bb0,bbf* *bb1739,bbf* *bb1733,bbd*
bb916,bbd*bb607,bbb*bb1315,bbk bb374,bbk bb2159){bb932 bbk bb2185;
bb932 bbk bb2040;bbk bb2170;bbk bb1044=0 ;bb0->bb449=(bb2046* )bb1315;
bb0->bb13.bb44=bb0->bb449->bb44;bb0->bb13.bb44.bb1754= *bb1739;bb0->
bb13.bb44.bb1028= *bb916;bb0->bb13.bb44.bb1743= *bb1733;bb0->bb13.
bb44.bb598= *bb607;bb0->bb13.bb44.bb1999=0 ;bb0->bb2113=0X0018 &bb374;
bbm(bb0->bb2113>0x0010 ){bb0->bb2113=0x0010 ;}bb0->bb2113>>=3 ;bbm( *
bb607<=15 )bb1044=0 ;bb54 bbm(bb0->bb13.bb44.bb1028!=0 ){bb0->bb13.bb44.
bb598-=15 ;bbm(bb0->bb13.bb44.bb2115==0 ){bb0->bb13.bb44.bb1911= *bb0->
bb13.bb44.bb1754++;--bb0->bb13.bb44.bb1028;++bb0->bb13.bb44.bb1272;++
bb0->bb13.bb44.bb1745;bb0->bb13.bb44.bb2048=(bbk)bb0->bb13.bb44.
bb1745&(2048 -1 );bb0->bb449->bb1843[(bbk)bb0->bb13.bb44.bb1272&(2048 -1
)]=bb0->bb13.bb44.bb1911;bb0->bb13.bb44.bb1693=(bb0->bb13.bb44.bb1693
<<8 )+bb0->bb13.bb44.bb1911;bb0->bb13.bb44.bb2115=1 ;}bb107((bb0->bb13.
bb44.bb1028!=0 )&&(bb0->bb13.bb44.bb1999==0 )){++bb0->bb13.bb44.bb1272;
++bb0->bb13.bb44.bb1745;bb0->bb13.bb44.bb2048=(bbk)bb0->bb13.bb44.
bb1745&(2048 -1 );bbm(((bb0->bb13.bb44.bb1272&0x7FFFFFFFL )==0 ))bb2375(
bb0);bb0->bb449->bb1843[(bbk)bb0->bb13.bb44.bb1272&(2048 -1 )]=bb0->
bb13.bb44.bb1911= *bb0->bb13.bb44.bb1754++;bb0->bb13.bb44.bb1693=(bb0
->bb13.bb44.bb1693<<8 )+bb0->bb13.bb44.bb1911;--bb0->bb13.bb44.bb1028;
bb0->bb13.bb44.bb2271=bb0->bb449->bb2084+((((bb0->bb13.bb44.bb1693)&
0xFF00 )>>4 )^((bb0->bb13.bb44.bb1693)&0x00FF ));bbm((bb0->bb13.bb44.
bb2290=bb0->bb13.bb44.bb1745- *bb0->bb13.bb44.bb2271)>2048 -2 ){bb0->
bb449->bb1873[bb0->bb13.bb44.bb2048]=0 ;bbm(bb0->bb13.bb44.bb549!=0 ){
bb2077(bb0,bb0->bb13.bb44.bb1288,bb0->bb13.bb44.bb549);}bb54{bb0->
bb13.bb44.bb1021=((bb0->bb13.bb44.bb1693>>8 ));bb0->bb13.bb44.bb1057=(
9 );bb1101(bb0);bb0->bb1749=bb2230;}}bb54{bb0->bb449->bb1873[bb0->bb13
.bb44.bb2048]=(bbk)bb0->bb13.bb44.bb2290;bbm(bb0->bb13.bb44.bb549!=0 ){
bbm((bb0->bb449->bb1843[(bbk)(((bbd)bb0->bb13.bb44.bb1253+bb0->bb13.
bb44.bb549+bb0->bb13.bb44.bb1839)&(bbd)(2048 -1 ))]==bb0->bb13.bb44.
bb1911)&&((bb0->bb13.bb44.bb549+bb0->bb13.bb44.bb1839)<(bbd)0xFFFFFFFFL
)){++bb0->bb13.bb44.bb549;bb0->bb1749=bb2489;bbm(bb0->bb13.bb44.
bb1822){bbm(bb0->bb13.bb44.bb549>=23 ){bb0->bb13.bb44.bb1021=(((1 <<4 )-
1 ));bb0->bb13.bb44.bb1057=(4 );bb1101(bb0);bb0->bb13.bb44.bb549-=((1 <<
4 )-1 );bb0->bb13.bb44.bb1839+=((1 <<4 )-1 );}}bb54 bbm(bb0->bb13.bb44.
bb549>=23 ){bbm(bb0->bb13.bb44.bb1288<128 ){bb0->bb13.bb44.bb1021=(
0x180 |bb0->bb13.bb44.bb1288);bb0->bb13.bb44.bb1057=(9 );bb1101(bb0);}
bb54{bb0->bb13.bb44.bb1021=(0x1000 |bb0->bb13.bb44.bb1288);bb0->bb13.
bb44.bb1057=(13 );bb1101(bb0);}bb0->bb13.bb44.bb1021=(((1 <<4 )-1 ));bb0
->bb13.bb44.bb1057=(4 );bb1101(bb0);bb0->bb13.bb44.bb549-=((1 <<4 )-1 );
bb0->bb13.bb44.bb1839+=((1 <<4 )-1 );bb0->bb13.bb44.bb1822=1 ;}}bb54 bbm(
bb0->bb13.bb44.bb1822){bb0->bb13.bb44.bb1021=(bb2157[(bbk)bb0->bb13.
bb44.bb549].bb2317);bb0->bb13.bb44.bb1057=(bb2157[(bbk)bb0->bb13.bb44
.bb549].bb47);bb1101(bb0);bb0->bb13.bb44.bb549=0 ;bb0->bb13.bb44.
bb1839=0 ;bb0->bb13.bb44.bb1822=0 ;bb0->bb1749=bb2390;}bb54 bbm(bb0->
bb13.bb44.bb549>=8 ){bb2077(bb0,bb0->bb13.bb44.bb1288,bb0->bb13.bb44.
bb549);}bb54{bb2040=0 ;bb0->bb13.bb44.bb2099=bb0->bb13.bb44.bb1288;
bb107((bb0->bb449->bb1873[bb0->bb13.bb44.bb1253]!=0 )&&(bb2040==0 )&&(
bb0->bb13.bb44.bb2061<bb2159)&&(bb0->bb13.bb44.bb2099<(bbk)(2048 -bb0
->bb13.bb44.bb549))){bb0->bb13.bb44.bb2099+=bb0->bb449->bb1873[bb0->
bb13.bb44.bb1253];++bb0->bb13.bb44.bb2061;bbm(bb0->bb13.bb44.bb2099<(
bbk)(2048 -bb0->bb13.bb44.bb549)){bb0->bb13.bb44.bb1253=bb0->bb13.bb44
.bb1253-bb0->bb449->bb1873[bb0->bb13.bb44.bb1253]&(2048 -1 );bbm(bb0->
bb449->bb1843[bb0->bb13.bb44.bb1253]==bb0->bb449->bb1843[bb0->bb13.
bb44.bb2248]){bb2040=1 ;bb91(bb2185=2 ,bb2170=(bb0->bb13.bb44.bb1253+2 )&
(2048 -1 );bb2185<=(bbk)bb0->bb13.bb44.bb549;bb2185++,bb2170=(bb2170+1 )&
(2048 -1 )){bbm(bb0->bb449->bb1843[bb2170]!=bb0->bb449->bb1843[(bb0->
bb13.bb44.bb2248+bb2185)&(2048 -1 )]){bb2040=0 ;bb22;}}}}}bbm(bb2040){
bb0->bb13.bb44.bb1288=bb0->bb13.bb44.bb2099;++bb0->bb13.bb44.bb549;
bb0->bb1749=bb2474;}bb54{bb2077(bb0,bb0->bb13.bb44.bb1288,bb0->bb13.
bb44.bb549);}}}bb54{bb0->bb13.bb44.bb2050=(bbk)bb0->bb13.bb44.bb2290;
bb0->bb13.bb44.bb2061=0 ;bb574{bb0->bb13.bb44.bb1253=(bbk)(bb0->bb13.
bb44.bb1745-bb0->bb13.bb44.bb2050&(2048 -1 ));bbm(bb0->bb449->bb1843[
bb0->bb13.bb44.bb1253]==(bbf)(bb0->bb13.bb44.bb1693>>8 )){bb0->bb13.
bb44.bb549=2 ;bb0->bb13.bb44.bb2248=bb0->bb13.bb44.bb2048;bb0->bb13.
bb44.bb1288=bb0->bb13.bb44.bb2050;bb0->bb1749=bb2563;bb22;}bb54{bb0->
bb13.bb44.bb2050+=bb0->bb449->bb1873[bb0->bb13.bb44.bb1253];++bb0->
bb13.bb44.bb2061;}}bb107((bb0->bb449->bb1873[bb0->bb13.bb44.bb1253]!=
0 )&&(bb0->bb13.bb44.bb2061<bb2159)&&(bb0->bb13.bb44.bb2050<2048 -2 ));
bbm(bb0->bb13.bb44.bb549==0 ){bb0->bb13.bb44.bb1021=((bb0->bb13.bb44.
bb1693>>8 ));bb0->bb13.bb44.bb1057=(9 );bb1101(bb0);bb0->bb1749=bb2230;
}}}bbm(bb2482[bb0->bb1749][bb0->bb2113]){ *bb0->bb13.bb44.bb2271=bb0
->bb13.bb44.bb1745;}}bbm(bb0->bb13.bb44.bb1028==0 ){bb1044=1 ;bbm(bb374
&0x01 ){bb2196(bb0,bb374);bb1044|=4 ;}}bbm((bb0->bb13.bb44.bb598==0 )||(
bb0->bb13.bb44.bb1999)){bbm(!(bb1044&1 )){bb1044=2 ;bbm(bb374&0x02 ){
bb2196(bb0,bb374);bb1044|=4 ;}}bb54{bb1044|=3 ;bbm((!(bb374&0x01 ))&&(
bb374&0x02 )){bb2196(bb0,bb374);bb1044|=4 ;}}}bb0->bb13.bb44.bb598+=15 ;
}bb54{bb1044=1 ;bbm(bb374&0x01 ){bb2196(bb0,bb374);bb1044|=4 ;}}bb0->
bb449->bb44=bb0->bb13.bb44; *bb1739=bb0->bb13.bb44.bb1754; *bb916=bb0
->bb13.bb44.bb1028; *bb1733=bb0->bb13.bb44.bb1743; *bb607=bb0->bb13.
bb44.bb598;bb2(bb1044);}bb41 bbb bb2123(bb474 bb0){bb0->bb13.bb80.
bb2092&=(2048 -1 );bb0->bb13.bb80.bb1049=bb0->bb13.bb80.bb1154=bb0->
bb13.bb80.bb92=0 ;bb0->bb13.bb80.bb995=bb0->bb13.bb80.bb1757=bb0->bb13
.bb80.bb1172=0 ;bb0->bb13.bb80.bb465=0 ;bb0->bb13.bb80.bb1971=0 ;bb0->
bb13.bb80.bb1165=bb2083;bb0->bb13.bb80.bb2441=1 ;bb2;}bb41 bbk bb2283(
bb474 bb0){bbm((bb0->bb13.bb80.bb1028==0 )&&(bb0->bb13.bb80.bb1049==0 ))bb0
->bb13.bb80.bb995=bb2377;bb54{bb0->bb13.bb80.bb995=bb1248;bbm(bb0->
bb13.bb80.bb1049==0 ){bb0->bb13.bb80.bb1757= *bb0->bb13.bb80.bb1754++;
--bb0->bb13.bb80.bb1028;bb0->bb13.bb80.bb1049=7 ;bb0->bb13.bb80.bb1172
=(bb0->bb13.bb80.bb1757>127 )?1 :0 ;bb0->bb13.bb80.bb1757&=((bbf)0x7F );}
bb54{bb0->bb13.bb80.bb1172=(bb0->bb13.bb80.bb1757>>(bb0->bb13.bb80.
bb1049-1 ));--bb0->bb13.bb80.bb1049;bb0->bb13.bb80.bb1757&=((bbf)0xFF
>>(8 -bb0->bb13.bb80.bb1049));}}bb2(bb0->bb13.bb80.bb995);}bb41 bbk
bb1847(bb474 bb0){bbk bb2156;bb123 bb8;bbm(bb0->bb13.bb80.bb995==
bb1248)bb0->bb13.bb80.bb1172=0 ;bb54 bb0->bb13.bb80.bb995=bb1248;bb107
((bb0->bb13.bb80.bb1154>0 )&&(bb0->bb13.bb80.bb995==bb1248)){bbm((bb0
->bb13.bb80.bb1028==0 )&&(bb0->bb13.bb80.bb1049==0 ))bb0->bb13.bb80.
bb995=bb2377;bb54{bbm(bb0->bb13.bb80.bb1049==0 ){bb0->bb13.bb80.bb1757
= *bb0->bb13.bb80.bb1754++;--bb0->bb13.bb80.bb1028;bb0->bb13.bb80.
bb1049=8 ;}bb2156=bb0->bb13.bb80.bb1757;bbm((bb8=bb0->bb13.bb80.bb1154
-bb0->bb13.bb80.bb1049)>0 )bb2156<<=bb8;bb54 bb2156>>=-bb8;bb0->bb13.
bb80.bb1172|=bb2156;bb8=((((8 )<(bb0->bb13.bb80.bb1154)?(8 ):(bb0->bb13
.bb80.bb1154)))<(bb0->bb13.bb80.bb1049)?(((8 )<(bb0->bb13.bb80.bb1154)?
(8 ):(bb0->bb13.bb80.bb1154))):(bb0->bb13.bb80.bb1049));bb0->bb13.bb80
.bb1154-=bb8;bb0->bb13.bb80.bb1049-=bb8;bb0->bb13.bb80.bb1757&=((bbf)0xFF
>>(8 -bb0->bb13.bb80.bb1049));}}bb2(bb0->bb13.bb80.bb995);}bb41 bbb
bb2073(bb474 bb0,bbf bbo){bbm(bb0->bb13.bb80.bb598!=0 ){ *bb0->bb13.
bb80.bb1743++=bbo;--bb0->bb13.bb80.bb598;bb0->bb449->bb2165[bb0->bb13
.bb80.bb2092++]=(bbf)bbo;bb0->bb13.bb80.bb2092&=(2048 -1 );}}bbk bb2293
(bb474 bb0,bbf* *bb1739,bbf* *bb1733,bbd*bb916,bbd*bb607,bbb*bb1315,
bbk bb374){bbk bb2200=0 ;bbk bb1044=0 ;bb0->bb449=(bb2046* )bb1315;bb0
->bb13.bb80=bb0->bb449->bb80;bb0->bb13.bb80.bb1754= *bb1739;bb0->bb13
.bb80.bb1028= *bb916;bb0->bb13.bb80.bb1743= *bb1733;bb0->bb13.bb80.
bb598= *bb607;bbm(bb374&0x01 ){bb2123(bb0);}bbm((bb0->bb13.bb80.bb1028
!=0 )&&(bb0->bb13.bb80.bb598!=0 )){bb107((bb0->bb13.bb80.bb598!=0 )&&((
bb0->bb13.bb80.bb1028!=0 )||(bb0->bb13.bb80.bb1049!=0 ))&&(bb2200==0 )){
bbm(bb0->bb13.bb80.bb1971){bb107((bb0->bb13.bb80.bb598!=0 )&&(bb0->
bb13.bb80.bb465>0 )){bb0->bb13.bb80.bb92&=(2048 -1 );bb2073(bb0,bb0->
bb449->bb2165[bb0->bb13.bb80.bb92++]);--bb0->bb13.bb80.bb465;}bbm(bb0
->bb13.bb80.bb465==0 )bb0->bb13.bb80.bb1971=0 ;bb0->bb13.bb80.bb1165=
bb2083;}bb54{bb296(bb0->bb13.bb80.bb1165){bb15 bb2083:bb2283(bb0);bbm
(bb0->bb13.bb80.bb1172==0 ){bb0->bb13.bb80.bb1154=8 ;bb0->bb13.bb80.
bb1165=bb2347;bb15 bb2347:bb1847(bb0);bbm(bb0->bb13.bb80.bb995==
bb1248){bb2073(bb0,(bbf)bb0->bb13.bb80.bb1172);bb0->bb13.bb80.bb1165=
bb2083;}}bb54{bb0->bb13.bb80.bb1165=bb2383;bb15 bb2383:bb2283(bb0);
bbm(bb0->bb13.bb80.bb995==bb1248){bb0->bb13.bb80.bb1154=bb0->bb13.
bb80.bb1172?7 :11 ;bb0->bb13.bb80.bb1165=bb2350;bb15 bb2350:bb1847(bb0);
bbm(bb0->bb13.bb80.bb995==bb1248){bb0->bb13.bb80.bb92=bb0->bb13.bb80.
bb1172;bbm(bb0->bb13.bb80.bb92==0 )bb2200=1 ;bb54{bb0->bb13.bb80.bb92=
bb0->bb13.bb80.bb2092-bb0->bb13.bb80.bb92;bb0->bb13.bb80.bb1154=2 ;bb0
->bb13.bb80.bb1165=bb2309;bb15 bb2309:bb1847(bb0);bbm(bb0->bb13.bb80.
bb995==bb1248){bb0->bb13.bb80.bb465=2 +bb0->bb13.bb80.bb1172;bbm(bb0->
bb13.bb80.bb465==5 ){bb0->bb13.bb80.bb1154=2 ;bb0->bb13.bb80.bb1165=
bb2308;bb15 bb2308:bb1847(bb0);bbm(bb0->bb13.bb80.bb995==bb1248){bb0
->bb13.bb80.bb465+=bb0->bb13.bb80.bb1172;bbm(bb0->bb13.bb80.bb465==8 ){
bb0->bb13.bb80.bb1154=4 ;bb0->bb13.bb80.bb1165=bb2423;bb15 bb2423:
bb1847(bb0);bbm(bb0->bb13.bb80.bb995==bb1248){bb0->bb13.bb80.bb465+=
bb0->bb13.bb80.bb1172;bbm(bb0->bb13.bb80.bb465==23 ){bb574{bb15 bb2237
:bb107((bb0->bb13.bb80.bb598!=0 )&&(bb0->bb13.bb80.bb465>0 )){bb0->bb13
.bb80.bb92&=(2048 -1 );bb2073(bb0,bb0->bb449->bb2165[bb0->bb13.bb80.
bb92++]);--bb0->bb13.bb80.bb465;}bbm(bb0->bb13.bb80.bb598==0 ){bb0->
bb13.bb80.bb1165=bb2237;bb22;}bb54{bb0->bb13.bb80.bb1154=4 ;bb0->bb13.
bb80.bb1165=bb2366;bb15 bb2366:bb1847(bb0);bbm(bb0->bb13.bb80.bb995==
bb1248)bb0->bb13.bb80.bb465+=bb0->bb13.bb80.bb1172;bb54 bb22;}}bb107(
bb0->bb13.bb80.bb1172==((1 <<4 )-1 ));}}}}}}bbm((bb0->bb13.bb80.bb995==
bb1248)&&(bb0->bb13.bb80.bb1165!=bb2237)){bb0->bb13.bb80.bb1971=1 ;}}}
}}}}}bbm(bb0->bb13.bb80.bb1971){bb107((bb0->bb13.bb80.bb598!=0 )&&(bb0
->bb13.bb80.bb465>0 )){bb0->bb13.bb80.bb92&=(2048 -1 );bb2073(bb0,bb0->
bb449->bb2165[bb0->bb13.bb80.bb92++]);--bb0->bb13.bb80.bb465;}bbm(bb0
->bb13.bb80.bb465==0 )bb0->bb13.bb80.bb1971=0 ;bb0->bb13.bb80.bb1165=
bb2083;}}bbm(bb2200){bb2123(bb0);bb1044|=4 ;}bbm(bb0->bb13.bb80.bb1028
==0 ){bb1044|=1 ;}bbm(bb0->bb13.bb80.bb598==0 ){bb1044|=2 ;}bb0->bb449->
bb80=bb0->bb13.bb80; *bb1739=bb0->bb13.bb80.bb1754; *bb916=bb0->bb13.
bb80.bb1028; *bb1733=bb0->bb13.bb80.bb1743; *bb607=bb0->bb13.bb80.
bb598;bb2(bb1044);}
