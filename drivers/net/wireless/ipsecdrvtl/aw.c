/*
   'src_compress_deflate_infcodes.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Sun Nov 16 20:01:26 2014
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
#if ( defined( _WIN32) || defined( __WIN32__)) && ! defined( WIN32)
#define WIN32
#endif
#if defined( __GNUC__) || defined( WIN32) || defined( bb1225) ||  \
defined( bb1200)
#ifndef bb397
#define bb397
#endif
#endif
#if defined( __MSDOS__) && ! defined( bb168)
#define bb168
#endif
#if defined( bb168) && ! defined( bb397)
#define bb507
#endif
#ifdef bb168
#define bb1041
#endif
#if ( defined( bb168) || defined( bb1195) || defined( WIN32)) && !  \
defined( bb136)
#define bb136
#endif
#if defined( __STDC__) || defined( __cplusplus) || defined( bb1208)
#ifndef bb136
#define bb136
#endif
#endif
#ifndef bb136
#ifndef bbh
#define bbh
#endif
#endif
#if defined( __BORLANDC__) && ( __BORLANDC__ < 0x500)
#define bb1107
#endif
#ifndef bb290
#ifdef bb507
#define bb290 8
#else
#define bb290 9
#endif
#endif
#ifndef bbp
#ifdef bb136
#define bbp( bb406) bb406
#else
#define bbp( bb406) ()
#endif
#endif
bba bbf bb153;bba bbs bbe bb7;bba bbs bb5 bb24;bba bb153 bb30;bba bbl
bb440;bba bbe bb1099;bba bb7 bb166;bba bb24 bb167;
#ifdef bb136
bba bbb*bb70;bba bbb*bb184;
#else
bba bb153*bb70;bba bb153*bb184;
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bb70( *bb504)bbp((bb70 bb110,bb7 bb496,bb7 bb47));bba bbb( *bb503
)bbp((bb70 bb110,bb70 bb1139));bbi bb376;bba bbi bb1187{bb30*bb127;
bb7 bb148;bb24 bb191;bb30*bb597;bb7 bb384;bb24 bb613;bbl*bb323;bbi
bb376*bb23;bb504 bb401;bb503 bb372;bb70 bb110;bbe bb968;bb24 bb367;
bb24 bb1153;}bb439;bba bb439*bb17;bbr bbh bbl*bb1159 bbp((bbb));bbr
bbe bb511 bbp((bb17 bb16,bbe bb175));bbr bbe bb944 bbp((bb17 bb16));
bbr bbe bb1051 bbp((bb17 bb16,bbe bb175));bbr bbe bb955 bbp((bb17 bb16
));bbr bbe bb1178 bbp((bb17 bb16,bbh bb30*bb426,bb7 bb436));bbr bbe
bb1151 bbp((bb17 bb130,bb17 bb185));bbr bbe bb1053 bbp((bb17 bb16));
bbr bbe bb1176 bbp((bb17 bb16,bbe bb124,bbe bb295));bbr bbe bb1149 bbp
((bb17 bb16,bbh bb30*bb426,bb7 bb436));bbr bbe bb1150 bbp((bb17 bb16));
bbr bbe bb1013 bbp((bb17 bb16));bbr bbe bb1152 bbp((bb30*bb130,bb167*
bb312,bbh bb30*bb185,bb24 bb325));bbr bbe bb1148 bbp((bb30*bb130,
bb167*bb312,bbh bb30*bb185,bb24 bb325,bbe bb124));bbr bbe bb1162 bbp(
(bb30*bb130,bb167*bb312,bbh bb30*bb185,bb24 bb325));bba bb184 bb34;
bbr bb34 bb1210 bbp((bbh bbl*bb1006,bbh bbl*bb57));bbr bb34 bb1211 bbp
((bbe bb472,bbh bbl*bb57));bbr bbe bb1228 bbp((bb34 bb25,bbe bb124,
bbe bb295));bbr bbe bb1191 bbp((bb34 bb25,bb184 bb40,bbs bb21));bbr
bbe bb1188 bbp((bb34 bb25,bbh bb184 bb40,bbs bb21));bbr bbe bb1227 bbp
((bb34 bb25,bbh bbl*bb1230,...));bbr bbe bb1190 bbp((bb34 bb25,bbh bbl
 *bbg));bbr bbl*bb1182 bbp((bb34 bb25,bbl*bb40,bbe bb21));bbr bbe
bb1201 bbp((bb34 bb25,bbe bbo));bbr bbe bb1183 bbp((bb34 bb25));bbr
bbe bb1216 bbp((bb34 bb25,bbe bb175));bbr bb5 bb1198 bbp((bb34 bb25,
bb5 bb92,bbe bb1206));bbr bbe bb1181 bbp((bb34 bb25));bbr bb5 bb1193
bbp((bb34 bb25));bbr bbe bb1199 bbp((bb34 bb25));bbr bbe bb1207 bbp((
bb34 bb25));bbr bbh bbl*bb1186 bbp((bb34 bb25,bbe*bb1180));bbr bb24
bb986 bbp((bb24 bb367,bbh bb30*bb40,bb7 bb21));bbr bb24 bb1168 bbp((
bb24 bb380,bbh bb30*bb40,bb7 bb21));bbr bbe bb1115 bbp((bb17 bb16,bbe
bb124,bbh bbl*bb188,bbe bb195));bbr bbe bb1126 bbp((bb17 bb16,bbh bbl
 *bb188,bbe bb195));bbr bbe bb1048 bbp((bb17 bb16,bbe bb124,bbe bb566
,bbe bb454,bbe bb956,bbe bb295,bbh bbl*bb188,bbe bb195));bbr bbe
bb1082 bbp((bb17 bb16,bbe bb454,bbh bbl*bb188,bbe bb195));bbr bbh bbl
 *bb1169 bbp((bbe bb18));bbr bbe bb1174 bbp((bb17 bby));bbr bbh bb167
 *bb1163 bbp((bbb));
#ifdef __cplusplus
}
#endif
#define bb963 1
#ifdef bb136
#if defined( bb1741)
#else
#endif
#endif
bba bbs bbl bb155;bba bb155 bb1209;bba bbs bb135 bb126;bba bb126 bb501
;bba bbs bb5 bb398;bbr bbh bbl*bb1067[10 ];
#if bb290 >= 8
#define bb788 8
#else
#define bb788 bb290
#endif
#ifdef bb168
#define bb420 0x00
#if defined( __TURBOC__) || defined( __BORLANDC__)
#if( __STDC__ == 1) && ( defined( bb1792) || defined( bb1770))
bbb bb941 bb1337(bbb*bb103);bbb*bb941 bb1341(bbs bb5 bb1740);
#else
#include"uncobf.h"
#include<alloc.h>
#include"cobf.h"
#endif
#else
#include"uncobf.h"
#include<malloc.h>
#include"cobf.h"
#endif
#endif
#ifdef WIN32
#define bb420 0x0b
#endif
#if ( defined( _MSC_VER) && ( _MSC_VER > 600))
#define bb1752( bb472, bb131) bb1788( bb472, bb131)
#endif
#ifndef bb420
#define bb420 0x03
#endif
#if defined( bb1546) && ! defined( _MSC_VER) && ! defined( bb1773)
#define bb963
#endif
bba bb24( *bb934)bbp((bb24 bb475,bbh bb30*bb40,bb7 bb21));bb70 bb1166
bbp((bb70 bb110,bbs bb496,bbs bb47));bbb bb1160 bbp((bb70 bb110,bb70
bb913));bba bbi bb1374 bb152;bbi bb1374{bb556{bbi{bb153 bb1175;bb153
bb959;}bb505;bb7 bb1548;}bb502;bb7 bb611;};bbr bbe bb2014 bbp((bb166*
,bb166* ,bb152* * ,bb152* ,bb17));bbr bbe bb1997 bbp((bb7,bb7,bb166* ,
bb166* ,bb166* ,bb152* * ,bb152* * ,bb152* ,bb17));bbr bbe bb1967 bbp
((bb166* ,bb166* ,bb152* * ,bb152* * ,bb17));bbi bb1103;bba bbi bb1103
bb303;bbr bb303*bb2011 bbp((bb17 bby,bb934 bbo,bb7 bbv));bbr bbe
bb1981 bbp((bb303* ,bb17,bbe));bbr bbb bb1791 bbp((bb303* ,bb17,bb167
 * ));bbr bbe bb1995 bbp((bb303* ,bb17));bbr bbb bb2024 bbp((bb303*
bbg,bbh bb30*bbt,bb7 bb11));bbr bbe bb1979 bbp((bb303*bbg));bbi bb1281
;bba bbi bb1281 bb722;bbr bb722*bb1968 bbp((bb7,bb7,bb152* ,bb152* ,
bb17));bbr bbe bb2071 bbp((bb303* ,bb17,bbe));bbr bbb bb1990 bbp((
bb722* ,bb17));bba bb10{bb1768,bb2026,bb2038,bb2075,bb2017,bb1978,
bb1959,bb1884,bb1784,bb921}bb1901;bbi bb1103{bb1901 bb57;bb556{bb7
bb189;bbi{bb7 bb1023;bb7 bb163;bb166*bb1129;bb7 bb1724;bb152*bb1769;}
bb444;bbi{bb722*bb1761;}bb1751;}bb149;bb7 bb1885;bb7 bb366;bb24 bb361
;bb152*bb1807;bb30*bb158;bb30*bb442;bb30*bb369;bb30*bb198;bb934 bb1561
;bb24 bb475;};bb41 bbh bb7 bb1145[17 ]={0x0000 ,0x0001 ,0x0003 ,0x0007 ,
0x000f ,0x001f ,0x003f ,0x007f ,0x00ff ,0x01ff ,0x03ff ,0x07ff ,0x0fff ,0x1fff
,0x3fff ,0x7fff ,0xffff };bbr bbe bb392 bbp((bb303* ,bb17,bbe));bbi bb376
{bbe bb445;};bbr bbe bb2204 bbp((bb7,bb7,bb152* ,bb152* ,bb303* ,bb17
));bba bb10{bb2194,bb2421,bb2363,bb2433,bb2379,bb2373,bb2396,bb2211,
bb2419,bb2127}bb2479;bbi bb1281{bb2479 bb57;bb7 bb21;bb556{bbi{bb152*
bb306;bb7 bb1008;}bb170;bb7 bb2425;bbi{bb7 bb2166;bb7 bb415;}bb1261;}
bb149;bb153 bb2252;bb153 bb2218;bb152*bb1077;bb152*bb1746;};bb722*
bb1968(bb55,bb961,bb1005,bb1000,bby)bb7 bb55,bb961;bb152*bb1005;bb152
 *bb1000;bb17 bby;{bb722*bbo;bbm((bbo=(bb722* )( * ((bby)->bb401))((
bby)->bb110,(1 ),(bb12(bbi bb1281))))!=0 ){bbo->bb57=bb2194;bbo->bb2252
=(bb153)bb55;bbo->bb2218=(bb153)bb961;bbo->bb1077=bb1005;bbo->bb1746=
bb1000;;}bb2 bbo;}bbe bb2071(bbg,bby,bb26)bb303*bbg;bb17 bby;bbe bb26
;{bb7 bb75;bb152*bb45;bb7 bbw;bb24 bbn;bb7 bb3;bb30*bb28;bb7 bb11;
bb30*bb84;bb7 bb95;bb30*bb20;bb722*bbo=bbg->bb149.bb1751.bb1761;{{
bb28=bby->bb127;bb11=bby->bb148;bbn=bbg->bb361;bb3=bbg->bb366;}{bb84=
bbg->bb198;bb95=(bb7)(bb7)(bb84<bbg->bb369?bbg->bb369-bb84-1 :bbg->
bb442-bb84);}}bb107(1 )bb296(bbo->bb57){bb15 bb2194:bbm(bb95>=258 &&
bb11>=10 ){{{bbg->bb361=bbn;bbg->bb366=bb3;}{bby->bb148=bb11;bby->
bb191+=(bb24)(bb28-bby->bb127);bby->bb127=bb28;}{bbg->bb198=bb84;}}
bb26=bb2204(bbo->bb2252,bbo->bb2218,bbo->bb1077,bbo->bb1746,bbg,bby);
{{bb28=bby->bb127;bb11=bby->bb148;bbn=bbg->bb361;bb3=bbg->bb366;}{
bb84=bbg->bb198;bb95=(bb7)(bb7)(bb84<bbg->bb369?bbg->bb369-bb84-1 :bbg
->bb442-bb84);}}bbm(bb26!=0 ){bbo->bb57=bb26==1 ?bb2211:bb2127;bb22;}}
bbo->bb149.bb170.bb1008=bbo->bb2252;bbo->bb149.bb170.bb306=bbo->
bb1077;bbo->bb57=bb2421;bb15 bb2421:bb75=bbo->bb149.bb170.bb1008;{
bb107(bb3<(bb75)){{bbm(bb11)bb26=0 ;bb54{{{bbg->bb361=bbn;bbg->bb366=
bb3;}{bby->bb148=bb11;bby->bb191+=(bb24)(bb28-bby->bb127);bby->bb127=
bb28;}{bbg->bb198=bb84;}}bb2 bb392(bbg,bby,bb26);}};bbn|=((bb24)(bb11
--, *bb28++))<<bb3;bb3+=(bb7)8 ;}}bb45=bbo->bb149.bb170.bb306+((bb7)bbn
&bb1145[bb75]);{bbn>>=(bb45->bb502.bb505.bb959);bb3-=(bb45->bb502.
bb505.bb959);}bbw=(bb7)(bb45->bb502.bb505.bb1175);bbm(bbw==0 ){bbo->
bb149.bb2425=bb45->bb611;;bbo->bb57=bb2396;bb22;}bbm(bbw&16 ){bbo->
bb149.bb1261.bb2166=bbw&15 ;bbo->bb21=bb45->bb611;bbo->bb57=bb2363;
bb22;}bbm((bbw&64 )==0 ){bbo->bb149.bb170.bb1008=bbw;bbo->bb149.bb170.
bb306=bb45+bb45->bb611;bb22;}bbm(bbw&32 ){;bbo->bb57=bb2211;bb22;}bbo
->bb57=bb2127;bby->bb323=(bbl* )"";bb26=(-3 );{{{bbg->bb361=bbn;bbg->
bb366=bb3;}{bby->bb148=bb11;bby->bb191+=(bb24)(bb28-bby->bb127);bby->
bb127=bb28;}{bbg->bb198=bb84;}}bb2 bb392(bbg,bby,bb26);}bb15 bb2363:
bb75=bbo->bb149.bb1261.bb2166;{bb107(bb3<(bb75)){{bbm(bb11)bb26=0 ;
bb54{{{bbg->bb361=bbn;bbg->bb366=bb3;}{bby->bb148=bb11;bby->bb191+=(
bb24)(bb28-bby->bb127);bby->bb127=bb28;}{bbg->bb198=bb84;}}bb2 bb392(
bbg,bby,bb26);}};bbn|=((bb24)(bb11--, *bb28++))<<bb3;bb3+=(bb7)8 ;}}
bbo->bb21+=(bb7)bbn&bb1145[bb75];{bbn>>=(bb75);bb3-=(bb75);}bbo->
bb149.bb170.bb1008=bbo->bb2218;bbo->bb149.bb170.bb306=bbo->bb1746;;
bbo->bb57=bb2433;bb15 bb2433:bb75=bbo->bb149.bb170.bb1008;{bb107(bb3<
(bb75)){{bbm(bb11)bb26=0 ;bb54{{{bbg->bb361=bbn;bbg->bb366=bb3;}{bby->
bb148=bb11;bby->bb191+=(bb24)(bb28-bby->bb127);bby->bb127=bb28;}{bbg
->bb198=bb84;}}bb2 bb392(bbg,bby,bb26);}};bbn|=((bb24)(bb11--, *bb28
++))<<bb3;bb3+=(bb7)8 ;}}bb45=bbo->bb149.bb170.bb306+((bb7)bbn&bb1145[
bb75]);{bbn>>=(bb45->bb502.bb505.bb959);bb3-=(bb45->bb502.bb505.bb959
);}bbw=(bb7)(bb45->bb502.bb505.bb1175);bbm(bbw&16 ){bbo->bb149.bb1261.
bb2166=bbw&15 ;bbo->bb149.bb1261.bb415=bb45->bb611;bbo->bb57=bb2379;
bb22;}bbm((bbw&64 )==0 ){bbo->bb149.bb170.bb1008=bbw;bbo->bb149.bb170.
bb306=bb45+bb45->bb611;bb22;}bbo->bb57=bb2127;bby->bb323=(bbl* )"";
bb26=(-3 );{{{bbg->bb361=bbn;bbg->bb366=bb3;}{bby->bb148=bb11;bby->
bb191+=(bb24)(bb28-bby->bb127);bby->bb127=bb28;}{bbg->bb198=bb84;}}
bb2 bb392(bbg,bby,bb26);}bb15 bb2379:bb75=bbo->bb149.bb1261.bb2166;{
bb107(bb3<(bb75)){{bbm(bb11)bb26=0 ;bb54{{{bbg->bb361=bbn;bbg->bb366=
bb3;}{bby->bb148=bb11;bby->bb191+=(bb24)(bb28-bby->bb127);bby->bb127=
bb28;}{bbg->bb198=bb84;}}bb2 bb392(bbg,bby,bb26);}};bbn|=((bb24)(bb11
--, *bb28++))<<bb3;bb3+=(bb7)8 ;}}bbo->bb149.bb1261.bb415+=(bb7)bbn&
bb1145[bb75];{bbn>>=(bb75);bb3-=(bb75);};bbo->bb57=bb2373;bb15 bb2373
:
#ifndef __TURBOC__
bb20=(bb7)(bb84-bbg->bb158)<bbo->bb149.bb1261.bb415?bbg->bb442-(bbo->
bb149.bb1261.bb415-(bb84-bbg->bb158)):bb84-bbo->bb149.bb1261.bb415;
#else
bb20=bb84-bbo->bb149.bb1261.bb415;bbm((bb7)(bb84-bbg->bb158)<bbo->
bb149.bb1261.bb415)bb20=bbg->bb442-(bbo->bb149.bb1261.bb415-(bb7)(
bb84-bbg->bb158));
#endif
bb107(bbo->bb21){{bbm(bb95==0 ){{bbm(bb84==bbg->bb442&&bbg->bb369!=bbg
->bb158){bb84=bbg->bb158;bb95=(bb7)(bb7)(bb84<bbg->bb369?bbg->bb369-
bb84-1 :bbg->bb442-bb84);}}bbm(bb95==0 ){{{bbg->bb198=bb84;}bb26=bb392(
bbg,bby,bb26);{bb84=bbg->bb198;bb95=(bb7)(bb7)(bb84<bbg->bb369?bbg->
bb369-bb84-1 :bbg->bb442-bb84);}}{bbm(bb84==bbg->bb442&&bbg->bb369!=
bbg->bb158){bb84=bbg->bb158;bb95=(bb7)(bb7)(bb84<bbg->bb369?bbg->
bb369-bb84-1 :bbg->bb442-bb84);}}bbm(bb95==0 ){{{bbg->bb361=bbn;bbg->
bb366=bb3;}{bby->bb148=bb11;bby->bb191+=(bb24)(bb28-bby->bb127);bby->
bb127=bb28;}{bbg->bb198=bb84;}}bb2 bb392(bbg,bby,bb26);}}}bb26=0 ;}{ *
bb84++=(bb153)( *bb20++);bb95--;}bbm(bb20==bbg->bb442)bb20=bbg->bb158
;bbo->bb21--;}bbo->bb57=bb2194;bb22;bb15 bb2396:{bbm(bb95==0 ){{bbm(
bb84==bbg->bb442&&bbg->bb369!=bbg->bb158){bb84=bbg->bb158;bb95=(bb7)(
bb7)(bb84<bbg->bb369?bbg->bb369-bb84-1 :bbg->bb442-bb84);}}bbm(bb95==0
){{{bbg->bb198=bb84;}bb26=bb392(bbg,bby,bb26);{bb84=bbg->bb198;bb95=(
bb7)(bb7)(bb84<bbg->bb369?bbg->bb369-bb84-1 :bbg->bb442-bb84);}}{bbm(
bb84==bbg->bb442&&bbg->bb369!=bbg->bb158){bb84=bbg->bb158;bb95=(bb7)(
bb7)(bb84<bbg->bb369?bbg->bb369-bb84-1 :bbg->bb442-bb84);}}bbm(bb95==0
){{{bbg->bb361=bbn;bbg->bb366=bb3;}{bby->bb148=bb11;bby->bb191+=(bb24
)(bb28-bby->bb127);bby->bb127=bb28;}{bbg->bb198=bb84;}}bb2 bb392(bbg,
bby,bb26);}}}bb26=0 ;}{ *bb84++=(bb153)(bbo->bb149.bb2425);bb95--;}bbo
->bb57=bb2194;bb22;bb15 bb2211:bbm(bb3>7 ){bb3-=8 ;bb11++;bb28--;}{{bbg
->bb198=bb84;}bb26=bb392(bbg,bby,bb26);{bb84=bbg->bb198;bb95=(bb7)(
bb7)(bb84<bbg->bb369?bbg->bb369-bb84-1 :bbg->bb442-bb84);}}bbm(bbg->
bb369!=bbg->bb198){{{bbg->bb361=bbn;bbg->bb366=bb3;}{bby->bb148=bb11;
bby->bb191+=(bb24)(bb28-bby->bb127);bby->bb127=bb28;}{bbg->bb198=bb84
;}}bb2 bb392(bbg,bby,bb26);}bbo->bb57=bb2419;bb15 bb2419:bb26=1 ;{{{
bbg->bb361=bbn;bbg->bb366=bb3;}{bby->bb148=bb11;bby->bb191+=(bb24)(
bb28-bby->bb127);bby->bb127=bb28;}{bbg->bb198=bb84;}}bb2 bb392(bbg,
bby,bb26);}bb15 bb2127:bb26=(-3 );{{{bbg->bb361=bbn;bbg->bb366=bb3;}{
bby->bb148=bb11;bby->bb191+=(bb24)(bb28-bby->bb127);bby->bb127=bb28;}
{bbg->bb198=bb84;}}bb2 bb392(bbg,bby,bb26);}bb419:bb26=(-2 );{{{bbg->
bb361=bbn;bbg->bb366=bb3;}{bby->bb148=bb11;bby->bb191+=(bb24)(bb28-
bby->bb127);bby->bb127=bb28;}{bbg->bb198=bb84;}}bb2 bb392(bbg,bby,
bb26);}}
#ifdef bb1107
bb2(-2 );
#endif
}bbb bb1990(bbo,bby)bb722*bbo;bb17 bby;{( * ((bby)->bb372))((bby)->
bb110,(bb70)(bbo));;}
