/*
   'src_compress_deflate_trees.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Sun Nov 16 20:01:26 2014
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
bb913));bba bbi bb1954{bb556{bb126 bb430;bb126 bb170;}bb258;bb556{
bb126 bb2164;bb126 bb21;}bb49;}bb459;bba bbi bb2278 bb2006;bba bbi
bb1940{bb459*bb1748;bbe bb509;bb2006*bb1722;}bb1734;bba bb126 bb1061;
bba bb1061 bb1370;bba bbs bb1318;bba bbi bb376{bb17 bb16;bbe bb360;
bb30*bb172;bb398 bb2039;bb30*bb1875;bbe bb182;bbe bb1347;bb153 bb968;
bb153 bb566;bbe bb1894;bb7 bb936;bb7 bb2163;bb7 bb1808;bb30*bb158;
bb398 bb2227;bb1370*bb967;bb1370*bb383;bb7 bb491;bb7 bb1326;bb7 bb2130
;bb7 bb1380;bb7 bb1611;bb5 bb429;bb7 bb953;bb1318 bb2298;bbe bb1939;
bb7 bb183;bb7 bb2023;bb7 bb463;bb7 bb1262;bb7 bb2177;bb7 bb2055;bbe
bb124;bbe bb295;bb7 bb2182;bbe bb1837;bbi bb1954 bb969[(2 * (256 +1 +29 )+
1 )];bbi bb1954 bb1682[2 *30 +1 ];bbi bb1954 bb532[2 *19 +1 ];bbi bb1940
bb1936;bbi bb1940 bb1862;bbi bb1940 bb2062;bb126 bb1196[15 +1 ];bbe
bb514[2 * (256 +1 +29 )+1 ];bbe bb1503;bbe bb1944;bb155 bb1236[2 * (256 +1 +
29 )+1 ];bb1209*bb1725;bb7 bb1125;bb7 bb609;bb501*bb1645;bb398 bb1906;
bb398 bb2118;bb7 bb2231;bbe bb1992;bb126 bb100;bbe bb78;}bb192;bbb
bb2210 bbp((bb192*bbg));bbe bb2391 bbp((bb192*bbg,bbs bb415,bbs bb1138
));bbb bb1619 bbp((bb192*bbg,bb440*bb40,bb398 bb1292,bbe bb1112));bbb
bb2255 bbp((bb192*bbg));bbb bb2144 bbp((bb192*bbg,bb440*bb40,bb398
bb1292,bbe bb1112));bb41 bbh bbe bb2415[29 ]={0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,1 ,
2 ,2 ,2 ,2 ,3 ,3 ,3 ,3 ,4 ,4 ,4 ,4 ,5 ,5 ,5 ,5 ,0 };bb41 bbh bbe bb2380[30 ]={0 ,0 ,0 ,0 ,1
,1 ,2 ,2 ,3 ,3 ,4 ,4 ,5 ,5 ,6 ,6 ,7 ,7 ,8 ,8 ,9 ,9 ,10 ,10 ,11 ,11 ,12 ,12 ,13 ,13 };bb41 bbh
bbe bb2480[19 ]={0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2 ,3 ,7 };bb41 bbh bb155
bb2199[19 ]={16 ,17 ,18 ,0 ,8 ,7 ,9 ,6 ,10 ,5 ,11 ,4 ,12 ,3 ,13 ,2 ,14 ,1 ,15 };bb41 bbh
bb459 bb1738[(256 +1 +29 )+2 ]={{{12 },{8 }},{{140 },{8 }},{{76 },{8 }},{{204 },
{8 }},{{44 },{8 }},{{172 },{8 }},{{108 },{8 }},{{236 },{8 }},{{28 },{8 }},{{156 }
,{8 }},{{92 },{8 }},{{220 },{8 }},{{60 },{8 }},{{188 },{8 }},{{124 },{8 }},{{252
},{8 }},{{2 },{8 }},{{130 },{8 }},{{66 },{8 }},{{194 },{8 }},{{34 },{8 }},{{162 }
,{8 }},{{98 },{8 }},{{226 },{8 }},{{18 },{8 }},{{146 },{8 }},{{82 },{8 }},{{210 }
,{8 }},{{50 },{8 }},{{178 },{8 }},{{114 },{8 }},{{242 },{8 }},{{10 },{8 }},{{138
},{8 }},{{74 },{8 }},{{202 },{8 }},{{42 },{8 }},{{170 },{8 }},{{106 },{8 }},{{
234 },{8 }},{{26 },{8 }},{{154 },{8 }},{{90 },{8 }},{{218 },{8 }},{{58 },{8 }},{{
186 },{8 }},{{122 },{8 }},{{250 },{8 }},{{6 },{8 }},{{134 },{8 }},{{70 },{8 }},{{
198 },{8 }},{{38 },{8 }},{{166 },{8 }},{{102 },{8 }},{{230 },{8 }},{{22 },{8 }},{
{150 },{8 }},{{86 },{8 }},{{214 },{8 }},{{54 },{8 }},{{182 },{8 }},{{118 },{8 }},
{{246 },{8 }},{{14 },{8 }},{{142 },{8 }},{{78 },{8 }},{{206 },{8 }},{{46 },{8 }},
{{174 },{8 }},{{110 },{8 }},{{238 },{8 }},{{30 },{8 }},{{158 },{8 }},{{94 },{8 }}
,{{222 },{8 }},{{62 },{8 }},{{190 },{8 }},{{126 },{8 }},{{254 },{8 }},{{1 },{8 }}
,{{129 },{8 }},{{65 },{8 }},{{193 },{8 }},{{33 },{8 }},{{161 },{8 }},{{97 },{8 }}
,{{225 },{8 }},{{17 },{8 }},{{145 },{8 }},{{81 },{8 }},{{209 },{8 }},{{49 },{8 }}
,{{177 },{8 }},{{113 },{8 }},{{241 },{8 }},{{9 },{8 }},{{137 },{8 }},{{73 },{8 }}
,{{201 },{8 }},{{41 },{8 }},{{169 },{8 }},{{105 },{8 }},{{233 },{8 }},{{25 },{8 }
},{{153 },{8 }},{{89 },{8 }},{{217 },{8 }},{{57 },{8 }},{{185 },{8 }},{{121 },{8
}},{{249 },{8 }},{{5 },{8 }},{{133 },{8 }},{{69 },{8 }},{{197 },{8 }},{{37 },{8 }
},{{165 },{8 }},{{101 },{8 }},{{229 },{8 }},{{21 },{8 }},{{149 },{8 }},{{85 },{8
}},{{213 },{8 }},{{53 },{8 }},{{181 },{8 }},{{117 },{8 }},{{245 },{8 }},{{13 },{
8 }},{{141 },{8 }},{{77 },{8 }},{{205 },{8 }},{{45 },{8 }},{{173 },{8 }},{{109 },
{8 }},{{237 },{8 }},{{29 },{8 }},{{157 },{8 }},{{93 },{8 }},{{221 },{8 }},{{61 },
{8 }},{{189 },{8 }},{{125 },{8 }},{{253 },{8 }},{{19 },{9 }},{{275 },{9 }},{{147
},{9 }},{{403 },{9 }},{{83 },{9 }},{{339 },{9 }},{{211 },{9 }},{{467 },{9 }},{{
51 },{9 }},{{307 },{9 }},{{179 },{9 }},{{435 },{9 }},{{115 },{9 }},{{371 },{9 }},
{{243 },{9 }},{{499 },{9 }},{{11 },{9 }},{{267 },{9 }},{{139 },{9 }},{{395 },{9 }
},{{75 },{9 }},{{331 },{9 }},{{203 },{9 }},{{459 },{9 }},{{43 },{9 }},{{299 },{9
}},{{171 },{9 }},{{427 },{9 }},{{107 },{9 }},{{363 },{9 }},{{235 },{9 }},{{491 }
,{9 }},{{27 },{9 }},{{283 },{9 }},{{155 },{9 }},{{411 },{9 }},{{91 },{9 }},{{347
},{9 }},{{219 },{9 }},{{475 },{9 }},{{59 },{9 }},{{315 },{9 }},{{187 },{9 }},{{
443 },{9 }},{{123 },{9 }},{{379 },{9 }},{{251 },{9 }},{{507 },{9 }},{{7 },{9 }},{
{263 },{9 }},{{135 },{9 }},{{391 },{9 }},{{71 },{9 }},{{327 },{9 }},{{199 },{9 }}
,{{455 },{9 }},{{39 },{9 }},{{295 },{9 }},{{167 },{9 }},{{423 },{9 }},{{103 },{9
}},{{359 },{9 }},{{231 },{9 }},{{487 },{9 }},{{23 },{9 }},{{279 },{9 }},{{151 },
{9 }},{{407 },{9 }},{{87 },{9 }},{{343 },{9 }},{{215 },{9 }},{{471 },{9 }},{{55 }
,{9 }},{{311 },{9 }},{{183 },{9 }},{{439 },{9 }},{{119 },{9 }},{{375 },{9 }},{{
247 },{9 }},{{503 },{9 }},{{15 },{9 }},{{271 },{9 }},{{143 },{9 }},{{399 },{9 }},
{{79 },{9 }},{{335 },{9 }},{{207 },{9 }},{{463 },{9 }},{{47 },{9 }},{{303 },{9 }}
,{{175 },{9 }},{{431 },{9 }},{{111 },{9 }},{{367 },{9 }},{{239 },{9 }},{{495 },{
9 }},{{31 },{9 }},{{287 },{9 }},{{159 },{9 }},{{415 },{9 }},{{95 },{9 }},{{351 },
{9 }},{{223 },{9 }},{{479 },{9 }},{{63 },{9 }},{{319 },{9 }},{{191 },{9 }},{{447
},{9 }},{{127 },{9 }},{{383 },{9 }},{{255 },{9 }},{{511 },{9 }},{{0 },{7 }},{{64
},{7 }},{{32 },{7 }},{{96 },{7 }},{{16 },{7 }},{{80 },{7 }},{{48 },{7 }},{{112 },
{7 }},{{8 },{7 }},{{72 },{7 }},{{40 },{7 }},{{104 },{7 }},{{24 },{7 }},{{88 },{7 }
},{{56 },{7 }},{{120 },{7 }},{{4 },{7 }},{{68 },{7 }},{{36 },{7 }},{{100 },{7 }},
{{20 },{7 }},{{84 },{7 }},{{52 },{7 }},{{116 },{7 }},{{3 },{8 }},{{131 },{8 }},{{
67 },{8 }},{{195 },{8 }},{{35 },{8 }},{{163 },{8 }},{{99 },{8 }},{{227 },{8 }}};
bb41 bbh bb459 bb2235[30 ]={{{0 },{5 }},{{16 },{5 }},{{8 },{5 }},{{24 },{5 }},
{{4 },{5 }},{{20 },{5 }},{{12 },{5 }},{{28 },{5 }},{{2 },{5 }},{{18 },{5 }},{{10 }
,{5 }},{{26 },{5 }},{{6 },{5 }},{{22 },{5 }},{{14 },{5 }},{{30 },{5 }},{{1 },{5 }}
,{{17 },{5 }},{{9 },{5 }},{{25 },{5 }},{{5 },{5 }},{{21 },{5 }},{{13 },{5 }},{{29
},{5 }},{{3 },{5 }},{{19 },{5 }},{{11 },{5 }},{{27 },{5 }},{{7 },{5 }},{{23 },{5 }
}};bb41 bbh bb155 bb1735[512 ]={0 ,1 ,2 ,3 ,4 ,4 ,5 ,5 ,6 ,6 ,6 ,6 ,7 ,7 ,7 ,7 ,8 ,8 ,8 ,
8 ,8 ,8 ,8 ,8 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,
10 ,10 ,11 ,11 ,11 ,11 ,11 ,11 ,11 ,11 ,11 ,11 ,11 ,11 ,11 ,11 ,11 ,11 ,12 ,12 ,12 ,12 ,12 ,
12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,
12 ,12 ,12 ,12 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,
13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,
14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,
14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,
14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,
15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,
15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,
15 ,15 ,15 ,0 ,0 ,16 ,17 ,18 ,18 ,19 ,19 ,20 ,20 ,20 ,20 ,21 ,21 ,21 ,21 ,22 ,22 ,22 ,22 ,22
,22 ,22 ,22 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24
,24 ,24 ,24 ,24 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,26 ,26 ,26
,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26
,26 ,26 ,26 ,26 ,26 ,26 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27
,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28
,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28
,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28
,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29
,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29
,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29
,29 ,29 ,29 ,29 ,29 };bb41 bbh bb155 bb2052[258 -3 +1 ]={0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,8 ,
9 ,9 ,10 ,10 ,11 ,11 ,12 ,12 ,12 ,12 ,13 ,13 ,13 ,13 ,14 ,14 ,14 ,14 ,15 ,15 ,15 ,15 ,16 ,16
,16 ,16 ,16 ,16 ,16 ,16 ,17 ,17 ,17 ,17 ,17 ,17 ,17 ,17 ,18 ,18 ,18 ,18 ,18 ,18 ,18 ,18 ,19
,19 ,19 ,19 ,19 ,19 ,19 ,19 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20
,21 ,21 ,21 ,21 ,21 ,21 ,21 ,21 ,21 ,21 ,21 ,21 ,21 ,21 ,21 ,21 ,22 ,22 ,22 ,22 ,22 ,22 ,22
,22 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23
,23 ,23 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24
,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25
,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,26 ,26 ,26
,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26
,26 ,26 ,26 ,26 ,26 ,26 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27
,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,28 };bb41 bbh bbe bb2334[29
]={0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,10 ,12 ,14 ,16 ,20 ,24 ,28 ,32 ,40 ,48 ,56 ,64 ,80 ,96 ,112 ,
128 ,160 ,192 ,224 ,0 };bb41 bbh bbe bb2417[30 ]={0 ,1 ,2 ,3 ,4 ,6 ,8 ,12 ,16 ,24 ,32
,48 ,64 ,96 ,128 ,192 ,256 ,384 ,512 ,768 ,1024 ,1536 ,2048 ,3072 ,4096 ,6144 ,8192 ,
12288 ,16384 ,24576 };bbi bb2278{bbh bb459*bb2345;bbh bb1099*bb2473;bbe
bb2454;bbe bb2176;bbe bb1941;};bb41 bb2006 bb2491={bb1738,bb2415,256 +
1 ,(256 +1 +29 ),15 };bb41 bb2006 bb2559={bb2235,bb2380,0 ,30 ,15 };bb41
bb2006 bb2498={(bbh bb459* )0 ,bb2480,0 ,19 ,7 };bb41 bbb bb2250 bbp((
bb192*bbg));bb41 bbb bb2168 bbp((bb192*bbg,bb459*bb306,bbe bb3));bb41
bbb bb2367 bbp((bb192*bbg,bb1734*bb1068));bb41 bbb bb2397 bbp((bb459*
bb306,bbe bb509,bb501*bb1196));bb41 bbb bb2186 bbp((bb192*bbg,bb1734*
bb1068));bb41 bbb bb2307 bbp((bb192*bbg,bb459*bb306,bbe bb509));bb41
bbb bb2232 bbp((bb192*bbg,bb459*bb306,bbe bb509));bb41 bbe bb2387 bbp
((bb192*bbg));bb41 bbb bb2410 bbp((bb192*bbg,bbe bb2051,bbe bb2093,
bbe bb2045));bb41 bbb bb2272 bbp((bb192*bbg,bb459*bb1077,bb459*bb1746
));bb41 bbb bb2314 bbp((bb192*bbg));bb41 bbs bb2374 bbp((bbs bb1323,
bbe bb465));bb41 bbb bb2259 bbp((bb192*bbg));bb41 bbb bb2303 bbp((
bb192*bbg));bb41 bbb bb2318 bbp((bb192*bbg,bb440*bb40,bbs bb21,bbe
bb978));bbb bb2210(bbg)bb192*bbg;{bbg->bb1936.bb1748=bbg->bb969;bbg->
bb1936.bb1722=&bb2491;bbg->bb1862.bb1748=bbg->bb1682;bbg->bb1862.
bb1722=&bb2559;bbg->bb2062.bb1748=bbg->bb532;bbg->bb2062.bb1722=&
bb2498;bbg->bb100=0 ;bbg->bb78=0 ;bbg->bb1992=8 ;bb2250(bbg);}bb41 bbb
bb2250(bbg)bb192*bbg;{bbe bb11;bb91(bb11=0 ;bb11<(256 +1 +29 );bb11++)bbg
->bb969[bb11].bb258.bb430=0 ;bb91(bb11=0 ;bb11<30 ;bb11++)bbg->bb1682[
bb11].bb258.bb430=0 ;bb91(bb11=0 ;bb11<19 ;bb11++)bbg->bb532[bb11].bb258
.bb430=0 ;bbg->bb969[256 ].bb258.bb430=1 ;bbg->bb1906=bbg->bb2118=0L ;bbg
->bb609=bbg->bb2231=0 ;}bb41 bbb bb2168(bbg,bb306,bb3)bb192*bbg;bb459*
bb306;bbe bb3;{bbe bb432=bbg->bb514[bb3];bbe bb75=bb3<<1 ;bb107(bb75<=
bbg->bb1503){bbm(bb75<bbg->bb1503&&(bb306[bbg->bb514[bb75+1 ]].bb258.
bb430<bb306[bbg->bb514[bb75]].bb258.bb430||(bb306[bbg->bb514[bb75+1 ]]
.bb258.bb430==bb306[bbg->bb514[bb75]].bb258.bb430&&bbg->bb1236[bbg->
bb514[bb75+1 ]]<=bbg->bb1236[bbg->bb514[bb75]]))){bb75++;}bbm((bb306[
bb432].bb258.bb430<bb306[bbg->bb514[bb75]].bb258.bb430||(bb306[bb432]
.bb258.bb430==bb306[bbg->bb514[bb75]].bb258.bb430&&bbg->bb1236[bb432]
<=bbg->bb1236[bbg->bb514[bb75]])))bb22;bbg->bb514[bb3]=bbg->bb514[
bb75];bb3=bb75;bb75<<=1 ;}bbg->bb514[bb3]=bb432;}bb41 bbb bb2367(bbg,
bb1068)bb192*bbg;bb1734*bb1068;{bb459*bb306=bb1068->bb1748;bbe bb509=
bb1068->bb509;bbh bb459*bb2116=bb1068->bb1722->bb2345;bbh bb1099*
bb1800=bb1068->bb1722->bb2473;bbe bb611=bb1068->bb1722->bb2454;bbe
bb1941=bb1068->bb1722->bb1941;bbe bb42;bbe bb11,bb95;bbe bb515;bbe
bb2145;bb126 bb20;bbe bb2140=0 ;bb91(bb515=0 ;bb515<=15 ;bb515++)bbg->
bb1196[bb515]=0 ;bb306[bbg->bb514[bbg->bb1944]].bb49.bb21=0 ;bb91(bb42=
bbg->bb1944+1 ;bb42<(2 * (256 +1 +29 )+1 );bb42++){bb11=bbg->bb514[bb42];
bb515=bb306[bb306[bb11].bb49.bb2164].bb49.bb21+1 ;bbm(bb515>bb1941)bb515
=bb1941,bb2140++;bb306[bb11].bb49.bb21=(bb126)bb515;bbm(bb11>bb509)bb1689
;bbg->bb1196[bb515]++;bb2145=0 ;bbm(bb11>=bb611)bb2145=bb1800[bb11-
bb611];bb20=bb306[bb11].bb258.bb430;bbg->bb1906+=(bb398)bb20* (bb515+
bb2145);bbm(bb2116)bbg->bb2118+=(bb398)bb20* (bb2116[bb11].bb49.bb21+
bb2145);}bbm(bb2140==0 )bb2;;bb574{bb515=bb1941-1 ;bb107(bbg->bb1196[
bb515]==0 )bb515--;bbg->bb1196[bb515]--;bbg->bb1196[bb515+1 ]+=2 ;bbg->
bb1196[bb1941]--;bb2140-=2 ;}bb107(bb2140>0 );bb91(bb515=bb1941;bb515!=
0 ;bb515--){bb11=bbg->bb1196[bb515];bb107(bb11!=0 ){bb95=bbg->bb514[--
bb42];bbm(bb95>bb509)bb1689;bbm(bb306[bb95].bb49.bb21!=(bbs)bb515){;
bbg->bb1906+=((bb5)bb515-(bb5)bb306[bb95].bb49.bb21) * (bb5)bb306[
bb95].bb258.bb430;bb306[bb95].bb49.bb21=(bb126)bb515;}bb11--;}}}bb41
bbb bb2397(bb306,bb509,bb1196)bb459*bb306;bbe bb509;bb501*bb1196;{
bb126 bb2405[15 +1 ];bb126 bb170=0 ;bbe bb515;bbe bb11;bb91(bb515=1 ;
bb515<=15 ;bb515++){bb2405[bb515]=bb170=(bb170+bb1196[bb515-1 ])<<1 ;};;
bb91(bb11=0 ;bb11<=bb509;bb11++){bbe bb21=bb306[bb11].bb49.bb21;bbm(
bb21==0 )bb1689;bb306[bb11].bb258.bb170=bb2374(bb2405[bb21]++,bb21);;}
}bb41 bbb bb2186(bbg,bb1068)bb192*bbg;bb1734*bb1068;{bb459*bb306=
bb1068->bb1748;bbh bb459*bb2116=bb1068->bb1722->bb2345;bbe bb2176=
bb1068->bb1722->bb2176;bbe bb11,bb95;bbe bb509=-1 ;bbe bb1776;bbg->
bb1503=0 ,bbg->bb1944=(2 * (256 +1 +29 )+1 );bb91(bb11=0 ;bb11<bb2176;bb11++
){bbm(bb306[bb11].bb258.bb430!=0 ){bbg->bb514[++(bbg->bb1503)]=bb509=
bb11;bbg->bb1236[bb11]=0 ;}bb54{bb306[bb11].bb49.bb21=0 ;}}bb107(bbg->
bb1503<2 ){bb1776=bbg->bb514[++(bbg->bb1503)]=(bb509<2 ?++bb509:0 );
bb306[bb1776].bb258.bb430=1 ;bbg->bb1236[bb1776]=0 ;bbg->bb1906--;bbm(
bb2116)bbg->bb2118-=bb2116[bb1776].bb49.bb21;}bb1068->bb509=bb509;
bb91(bb11=bbg->bb1503/2 ;bb11>=1 ;bb11--)bb2168(bbg,bb306,bb11);bb1776=
bb2176;bb574{{bb11=bbg->bb514[1 ];bbg->bb514[1 ]=bbg->bb514[bbg->bb1503
--];bb2168(bbg,bb306,1 );};bb95=bbg->bb514[1 ];bbg->bb514[--(bbg->
bb1944)]=bb11;bbg->bb514[--(bbg->bb1944)]=bb95;bb306[bb1776].bb258.
bb430=bb306[bb11].bb258.bb430+bb306[bb95].bb258.bb430;bbg->bb1236[
bb1776]=(bb155)((bbg->bb1236[bb11]>=bbg->bb1236[bb95]?bbg->bb1236[
bb11]:bbg->bb1236[bb95])+1 );bb306[bb11].bb49.bb2164=bb306[bb95].bb49.
bb2164=(bb126)bb1776;bbg->bb514[1 ]=bb1776++;bb2168(bbg,bb306,1 );}
bb107(bbg->bb1503>=2 );bbg->bb514[--(bbg->bb1944)]=bbg->bb514[1 ];
bb2367(bbg,(bb1734* )bb1068);bb2397((bb459* )bb306,bb509,bbg->bb1196);
}bb41 bbb bb2307(bbg,bb306,bb509)bb192*bbg;bb459*bb306;bbe bb509;{bbe
bb11;bbe bb2085=-1 ;bbe bb907;bbe bb1204=bb306[0 ].bb49.bb21;bbe bb970=
0 ;bbe bb1335=7 ;bbe bb1302=4 ;bbm(bb1204==0 )bb1335=138 ,bb1302=3 ;bb306[
bb509+1 ].bb49.bb21=(bb126)0xffff ;bb91(bb11=0 ;bb11<=bb509;bb11++){
bb907=bb1204;bb1204=bb306[bb11+1 ].bb49.bb21;bbm(++bb970<bb1335&&bb907
==bb1204){bb1689;}bb54 bbm(bb970<bb1302){bbg->bb532[bb907].bb258.
bb430+=bb970;}bb54 bbm(bb907!=0 ){bbm(bb907!=bb2085)bbg->bb532[bb907].
bb258.bb430++;bbg->bb532[16 ].bb258.bb430++;}bb54 bbm(bb970<=10 ){bbg->
bb532[17 ].bb258.bb430++;}bb54{bbg->bb532[18 ].bb258.bb430++;}bb970=0 ;
bb2085=bb907;bbm(bb1204==0 ){bb1335=138 ,bb1302=3 ;}bb54 bbm(bb907==
bb1204){bb1335=6 ,bb1302=3 ;}bb54{bb1335=7 ,bb1302=4 ;}}}bb41 bbb bb2232(
bbg,bb306,bb509)bb192*bbg;bb459*bb306;bbe bb509;{bbe bb11;bbe bb2085=
-1 ;bbe bb907;bbe bb1204=bb306[0 ].bb49.bb21;bbe bb970=0 ;bbe bb1335=7 ;
bbe bb1302=4 ;bbm(bb1204==0 )bb1335=138 ,bb1302=3 ;bb91(bb11=0 ;bb11<=
bb509;bb11++){bb907=bb1204;bb1204=bb306[bb11+1 ].bb49.bb21;bbm(++bb970
<bb1335&&bb907==bb1204){bb1689;}bb54 bbm(bb970<bb1302){bb574{{bbe bb21
=bbg->bb532[bb907].bb49.bb21;bbm(bbg->bb78>(bbe)(8 *2 *bb12(bbl))-bb21){
bbe bb171=bbg->bb532[bb907].bb258.bb170;bbg->bb100|=(bb171<<bbg->bb78
);{{bbg->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg->
bb172[bbg->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->bb100=
(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=bb21-(8 *2 *
bb12(bbl));}bb54{bbg->bb100|=(bbg->bb532[bb907].bb258.bb170)<<bbg->
bb78;bbg->bb78+=bb21;}};}bb107(--bb970!=0 );}bb54 bbm(bb907!=0 ){bbm(
bb907!=bb2085){{bbe bb21=bbg->bb532[bb907].bb49.bb21;bbm(bbg->bb78>(
bbe)(8 *2 *bb12(bbl))-bb21){bbe bb171=bbg->bb532[bb907].bb258.bb170;bbg
->bb100|=(bb171<<bbg->bb78);{{bbg->bb172[bbg->bb182++]=((bb155)((bbg
->bb100)&0xff ));};{bbg->bb172[bbg->bb182++]=((bb155)((bb126)(bbg->
bb100)>>8 ));};};bbg->bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->
bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(bbg->bb532[
bb907].bb258.bb170)<<bbg->bb78;bbg->bb78+=bb21;}};bb970--;};{bbe bb21
=bbg->bb532[16 ].bb49.bb21;bbm(bbg->bb78>(bbe)(8 *2 *bb12(bbl))-bb21){
bbe bb171=bbg->bb532[16 ].bb258.bb170;bbg->bb100|=(bb171<<bbg->bb78);{
{bbg->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg->bb172[
bbg->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->bb100=(bb126
)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=bb21-(8 *2 *bb12(
bbl));}bb54{bbg->bb100|=(bbg->bb532[16 ].bb258.bb170)<<bbg->bb78;bbg->
bb78+=bb21;}};{bbe bb21=2 ;bbm(bbg->bb78>(bbe)(8 *2 *bb12(bbl))-bb21){
bbe bb171=bb970-3 ;bbg->bb100|=(bb171<<bbg->bb78);{{bbg->bb172[bbg->
bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg->bb172[bbg->bb182++]=((
bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->bb100=(bb126)bb171>>((bbe)(8
 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->
bb100|=(bb970-3 )<<bbg->bb78;bbg->bb78+=bb21;}};}bb54 bbm(bb970<=10 ){{
bbe bb21=bbg->bb532[17 ].bb49.bb21;bbm(bbg->bb78>(bbe)(8 *2 *bb12(bbl))-
bb21){bbe bb171=bbg->bb532[17 ].bb258.bb170;bbg->bb100|=(bb171<<bbg->
bb78);{{bbg->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg
->bb172[bbg->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->
bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=bb21-
(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(bbg->bb532[17 ].bb258.bb170)<<bbg->
bb78;bbg->bb78+=bb21;}};{bbe bb21=3 ;bbm(bbg->bb78>(bbe)(8 *2 *bb12(bbl))-
bb21){bbe bb171=bb970-3 ;bbg->bb100|=(bb171<<bbg->bb78);{{bbg->bb172[
bbg->bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg->bb172[bbg->bb182++
]=((bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->bb100=(bb126)bb171>>((
bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}bb54{
bbg->bb100|=(bb970-3 )<<bbg->bb78;bbg->bb78+=bb21;}};}bb54{{bbe bb21=
bbg->bb532[18 ].bb49.bb21;bbm(bbg->bb78>(bbe)(8 *2 *bb12(bbl))-bb21){bbe
bb171=bbg->bb532[18 ].bb258.bb170;bbg->bb100|=(bb171<<bbg->bb78);{{bbg
->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg->bb172[bbg
->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->bb100=(bb126)bb171
>>((bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}
bb54{bbg->bb100|=(bbg->bb532[18 ].bb258.bb170)<<bbg->bb78;bbg->bb78+=
bb21;}};{bbe bb21=7 ;bbm(bbg->bb78>(bbe)(8 *2 *bb12(bbl))-bb21){bbe bb171
=bb970-11 ;bbg->bb100|=(bb171<<bbg->bb78);{{bbg->bb172[bbg->bb182++]=(
(bb155)((bbg->bb100)&0xff ));};{bbg->bb172[bbg->bb182++]=((bb155)((
bb126)(bbg->bb100)>>8 ));};};bbg->bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(
bbl))-bbg->bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(
bb970-11 )<<bbg->bb78;bbg->bb78+=bb21;}};}bb970=0 ;bb2085=bb907;bbm(
bb1204==0 ){bb1335=138 ,bb1302=3 ;}bb54 bbm(bb907==bb1204){bb1335=6 ,
bb1302=3 ;}bb54{bb1335=7 ,bb1302=4 ;}}}bb41 bbe bb2387(bbg)bb192*bbg;{
bbe bb1785;bb2307(bbg,(bb459* )bbg->bb969,bbg->bb1936.bb509);bb2307(
bbg,(bb459* )bbg->bb1682,bbg->bb1862.bb509);bb2186(bbg,(bb1734* )(&(
bbg->bb2062)));bb91(bb1785=19 -1 ;bb1785>=3 ;bb1785--){bbm(bbg->bb532[
bb2199[bb1785]].bb49.bb21!=0 )bb22;}bbg->bb1906+=3 * (bb1785+1 )+5 +5 +4 ;;
bb2 bb1785;}bb41 bbb bb2410(bbg,bb2051,bb2093,bb2045)bb192*bbg;bbe
bb2051,bb2093,bb2045;{bbe bb2122;;;;{bbe bb21=5 ;bbm(bbg->bb78>(bbe)(8
 *2 *bb12(bbl))-bb21){bbe bb171=bb2051-257 ;bbg->bb100|=(bb171<<bbg->
bb78);{{bbg->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg
->bb172[bbg->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->
bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=bb21-
(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(bb2051-257 )<<bbg->bb78;bbg->bb78+=
bb21;}};{bbe bb21=5 ;bbm(bbg->bb78>(bbe)(8 *2 *bb12(bbl))-bb21){bbe bb171
=bb2093-1 ;bbg->bb100|=(bb171<<bbg->bb78);{{bbg->bb172[bbg->bb182++]=(
(bb155)((bbg->bb100)&0xff ));};{bbg->bb172[bbg->bb182++]=((bb155)((
bb126)(bbg->bb100)>>8 ));};};bbg->bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(
bbl))-bbg->bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(
bb2093-1 )<<bbg->bb78;bbg->bb78+=bb21;}};{bbe bb21=4 ;bbm(bbg->bb78>(
bbe)(8 *2 *bb12(bbl))-bb21){bbe bb171=bb2045-4 ;bbg->bb100|=(bb171<<bbg
->bb78);{{bbg->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&0xff ));};{
bbg->bb172[bbg->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->
bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=bb21-
(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(bb2045-4 )<<bbg->bb78;bbg->bb78+=
bb21;}};bb91(bb2122=0 ;bb2122<bb2045;bb2122++){;{bbe bb21=3 ;bbm(bbg->
bb78>(bbe)(8 *2 *bb12(bbl))-bb21){bbe bb171=bbg->bb532[bb2199[bb2122]].
bb49.bb21;bbg->bb100|=(bb171<<bbg->bb78);{{bbg->bb172[bbg->bb182++]=(
(bb155)((bbg->bb100)&0xff ));};{bbg->bb172[bbg->bb182++]=((bb155)((
bb126)(bbg->bb100)>>8 ));};};bbg->bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(
bbl))-bbg->bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(
bbg->bb532[bb2199[bb2122]].bb49.bb21)<<bbg->bb78;bbg->bb78+=bb21;}};}
;bb2232(bbg,(bb459* )bbg->bb969,bb2051-1 );;bb2232(bbg,(bb459* )bbg->
bb1682,bb2093-1 );;}bbb bb2144(bbg,bb40,bb1292,bb1112)bb192*bbg;bb440*
bb40;bb398 bb1292;bbe bb1112;{{bbe bb21=3 ;bbm(bbg->bb78>(bbe)(8 *2 *
bb12(bbl))-bb21){bbe bb171=(0 <<1 )+bb1112;bbg->bb100|=(bb171<<bbg->
bb78);{{bbg->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg
->bb172[bbg->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->
bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=bb21-
(8 *2 *bb12(bbl));}bb54{bbg->bb100|=((0 <<1 )+bb1112)<<bbg->bb78;bbg->
bb78+=bb21;}};bb2318(bbg,bb40,(bbs)bb1292,1 );}bbb bb2255(bbg)bb192*
bbg;{{bbe bb21=3 ;bbm(bbg->bb78>(bbe)(8 *2 *bb12(bbl))-bb21){bbe bb171=1
<<1 ;bbg->bb100|=(bb171<<bbg->bb78);{{bbg->bb172[bbg->bb182++]=((bb155
)((bbg->bb100)&0xff ));};{bbg->bb172[bbg->bb182++]=((bb155)((bb126)(
bbg->bb100)>>8 ));};};bbg->bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-
bbg->bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(1 <<1 )<<
bbg->bb78;bbg->bb78+=bb21;}};{bbe bb21=bb1738[256 ].bb49.bb21;bbm(bbg
->bb78>(bbe)(8 *2 *bb12(bbl))-bb21){bbe bb171=bb1738[256 ].bb258.bb170;
bbg->bb100|=(bb171<<bbg->bb78);{{bbg->bb172[bbg->bb182++]=((bb155)((
bbg->bb100)&0xff ));};{bbg->bb172[bbg->bb182++]=((bb155)((bb126)(bbg->
bb100)>>8 ));};};bbg->bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->
bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(bb1738[256 ].
bb258.bb170)<<bbg->bb78;bbg->bb78+=bb21;}};bb2303(bbg);bbm(1 +bbg->
bb1992+10 -bbg->bb78<9 ){{bbe bb21=3 ;bbm(bbg->bb78>(bbe)(8 *2 *bb12(bbl))-
bb21){bbe bb171=1 <<1 ;bbg->bb100|=(bb171<<bbg->bb78);{{bbg->bb172[bbg
->bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg->bb172[bbg->bb182++]=(
(bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->bb100=(bb126)bb171>>((bbe)(
8 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->
bb100|=(1 <<1 )<<bbg->bb78;bbg->bb78+=bb21;}};{bbe bb21=bb1738[256 ].
bb49.bb21;bbm(bbg->bb78>(bbe)(8 *2 *bb12(bbl))-bb21){bbe bb171=bb1738[
256 ].bb258.bb170;bbg->bb100|=(bb171<<bbg->bb78);{{bbg->bb172[bbg->
bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg->bb172[bbg->bb182++]=((
bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->bb100=(bb126)bb171>>((bbe)(8
 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->
bb100|=(bb1738[256 ].bb258.bb170)<<bbg->bb78;bbg->bb78+=bb21;}};bb2303
(bbg);}bbg->bb1992=7 ;}bbb bb1619(bbg,bb40,bb1292,bb1112)bb192*bbg;
bb440*bb40;bb398 bb1292;bbe bb1112;{bb398 bb2013,bb2078;bbe bb1785=0 ;
bbm(bbg->bb124>0 ){bbm(bbg->bb968==2 )bb2314(bbg);bb2186(bbg,(bb1734* )(
&(bbg->bb1936)));;bb2186(bbg,(bb1734* )(&(bbg->bb1862)));;bb1785=
bb2387(bbg);bb2013=(bbg->bb1906+3 +7 )>>3 ;bb2078=(bbg->bb2118+3 +7 )>>3 ;;
bbm(bb2078<=bb2013)bb2013=bb2078;}bb54{;bb2013=bb2078=bb1292+5 ;}bbm(
bb1292+4 <=bb2013&&bb40!=(bbl* )0 ){bb2144(bbg,bb40,bb1292,bb1112);}
bb54 bbm(bb2078==bb2013){{bbe bb21=3 ;bbm(bbg->bb78>(bbe)(8 *2 *bb12(bbl
))-bb21){bbe bb171=(1 <<1 )+bb1112;bbg->bb100|=(bb171<<bbg->bb78);{{bbg
->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg->bb172[bbg
->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->bb100=(bb126)bb171
>>((bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}
bb54{bbg->bb100|=((1 <<1 )+bb1112)<<bbg->bb78;bbg->bb78+=bb21;}};bb2272
(bbg,(bb459* )bb1738,(bb459* )bb2235);}bb54{{bbe bb21=3 ;bbm(bbg->bb78
>(bbe)(8 *2 *bb12(bbl))-bb21){bbe bb171=(2 <<1 )+bb1112;bbg->bb100|=(
bb171<<bbg->bb78);{{bbg->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&
0xff ));};{bbg->bb172[bbg->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));
};};bbg->bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->
bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->bb100|=((2 <<1 )+bb1112)<<bbg->
bb78;bbg->bb78+=bb21;}};bb2410(bbg,bbg->bb1936.bb509+1 ,bbg->bb1862.
bb509+1 ,bb1785+1 );bb2272(bbg,(bb459* )bbg->bb969,(bb459* )bbg->bb1682
);};bb2250(bbg);bbm(bb1112){bb2259(bbg);};}bbe bb2391(bbg,bb415,
bb1138)bb192*bbg;bbs bb415;bbs bb1138;{bbg->bb1645[bbg->bb609]=(bb126
)bb415;bbg->bb1725[bbg->bb609++]=(bb155)bb1138;bbm(bb415==0 ){bbg->
bb969[bb1138].bb258.bb430++;}bb54{bbg->bb2231++;bb415--;;bbg->bb969[
bb2052[bb1138]+256 +1 ].bb258.bb430++;bbg->bb1682[((bb415)<256 ?bb1735[
bb415]:bb1735[256 +((bb415)>>7 )])].bb258.bb430++;}bb2(bbg->bb609==bbg
->bb1125-1 );}bb41 bbb bb2272(bbg,bb1077,bb1746)bb192*bbg;bb459*bb1077
;bb459*bb1746;{bbs bb415;bbe bb1138;bbs bb2288=0 ;bbs bb170;bbe bb1800
;bbm(bbg->bb609!=0 )bb574{bb415=bbg->bb1645[bb2288];bb1138=bbg->bb1725
[bb2288++];bbm(bb415==0 ){{bbe bb21=bb1077[bb1138].bb49.bb21;bbm(bbg->
bb78>(bbe)(8 *2 *bb12(bbl))-bb21){bbe bb171=bb1077[bb1138].bb258.bb170;
bbg->bb100|=(bb171<<bbg->bb78);{{bbg->bb172[bbg->bb182++]=((bb155)((
bbg->bb100)&0xff ));};{bbg->bb172[bbg->bb182++]=((bb155)((bb126)(bbg->
bb100)>>8 ));};};bbg->bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->
bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(bb1077[
bb1138].bb258.bb170)<<bbg->bb78;bbg->bb78+=bb21;}};;}bb54{bb170=
bb2052[bb1138];{bbe bb21=bb1077[bb170+256 +1 ].bb49.bb21;bbm(bbg->bb78>
(bbe)(8 *2 *bb12(bbl))-bb21){bbe bb171=bb1077[bb170+256 +1 ].bb258.bb170;
bbg->bb100|=(bb171<<bbg->bb78);{{bbg->bb172[bbg->bb182++]=((bb155)((
bbg->bb100)&0xff ));};{bbg->bb172[bbg->bb182++]=((bb155)((bb126)(bbg->
bb100)>>8 ));};};bbg->bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->
bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(bb1077[bb170
+256 +1 ].bb258.bb170)<<bbg->bb78;bbg->bb78+=bb21;}};bb1800=bb2415[
bb170];bbm(bb1800!=0 ){bb1138-=bb2334[bb170];{bbe bb21=bb1800;bbm(bbg
->bb78>(bbe)(8 *2 *bb12(bbl))-bb21){bbe bb171=bb1138;bbg->bb100|=(bb171
<<bbg->bb78);{{bbg->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&0xff ));
};{bbg->bb172[bbg->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));};};bbg
->bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=
bb21-(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(bb1138)<<bbg->bb78;bbg->bb78
+=bb21;}};}bb415--;bb170=((bb415)<256 ?bb1735[bb415]:bb1735[256 +((
bb415)>>7 )]);;{bbe bb21=bb1746[bb170].bb49.bb21;bbm(bbg->bb78>(bbe)(8
 *2 *bb12(bbl))-bb21){bbe bb171=bb1746[bb170].bb258.bb170;bbg->bb100|=
(bb171<<bbg->bb78);{{bbg->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&
0xff ));};{bbg->bb172[bbg->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));
};};bbg->bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->
bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(bb1746[bb170].bb258.
bb170)<<bbg->bb78;bbg->bb78+=bb21;}};bb1800=bb2380[bb170];bbm(bb1800
!=0 ){bb415-=bb2417[bb170];{bbe bb21=bb1800;bbm(bbg->bb78>(bbe)(8 *2 *
bb12(bbl))-bb21){bbe bb171=bb415;bbg->bb100|=(bb171<<bbg->bb78);{{bbg
->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg->bb172[bbg
->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->bb100=(bb126)bb171
>>((bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->bb78+=bb21-(8 *2 *bb12(bbl));}
bb54{bbg->bb100|=(bb415)<<bbg->bb78;bbg->bb78+=bb21;}};}};}bb107(
bb2288<bbg->bb609);{bbe bb21=bb1077[256 ].bb49.bb21;bbm(bbg->bb78>(bbe
)(8 *2 *bb12(bbl))-bb21){bbe bb171=bb1077[256 ].bb258.bb170;bbg->bb100|=
(bb171<<bbg->bb78);{{bbg->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&
0xff ));};{bbg->bb172[bbg->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));
};};bbg->bb100=(bb126)bb171>>((bbe)(8 *2 *bb12(bbl))-bbg->bb78);bbg->
bb78+=bb21-(8 *2 *bb12(bbl));}bb54{bbg->bb100|=(bb1077[256 ].bb258.bb170
)<<bbg->bb78;bbg->bb78+=bb21;}};bbg->bb1992=bb1077[256 ].bb49.bb21;}
bb41 bbb bb2314(bbg)bb192*bbg;{bbe bb11=0 ;bbs bb2327=0 ;bbs bb2269=0 ;
bb107(bb11<7 )bb2269+=bbg->bb969[bb11++].bb258.bb430;bb107(bb11<128 )bb2327
+=bbg->bb969[bb11++].bb258.bb430;bb107(bb11<256 )bb2269+=bbg->bb969[
bb11++].bb258.bb430;bbg->bb968=(bb153)(bb2269>(bb2327>>2 )?0 :1 );}bb41
bbs bb2374(bb170,bb21)bbs bb170;bbe bb21;{bb932 bbs bb2305=0 ;bb574{
bb2305|=bb170&1 ;bb170>>=1 ,bb2305<<=1 ;}bb107(--bb21>0 );bb2 bb2305>>1 ;}
bb41 bbb bb2303(bbg)bb192*bbg;{bbm(bbg->bb78==16 ){{{bbg->bb172[bbg->
bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg->bb172[bbg->bb182++]=((
bb155)((bb126)(bbg->bb100)>>8 ));};};bbg->bb100=0 ;bbg->bb78=0 ;}bb54 bbm
(bbg->bb78>=8 ){{bbg->bb172[bbg->bb182++]=((bb153)bbg->bb100);};bbg->
bb100>>=8 ;bbg->bb78-=8 ;}}bb41 bbb bb2259(bbg)bb192*bbg;{bbm(bbg->bb78
>8 ){{{bbg->bb172[bbg->bb182++]=((bb155)((bbg->bb100)&0xff ));};{bbg->
bb172[bbg->bb182++]=((bb155)((bb126)(bbg->bb100)>>8 ));};};}bb54 bbm(
bbg->bb78>0 ){{bbg->bb172[bbg->bb182++]=((bb153)bbg->bb100);};}bbg->
bb100=0 ;bbg->bb78=0 ;}bb41 bbb bb2318(bbg,bb40,bb21,bb978)bb192*bbg;
bb440*bb40;bbs bb21;bbe bb978;{bb2259(bbg);bbg->bb1992=8 ;bbm(bb978){{
{bbg->bb172[bbg->bb182++]=((bb155)(((bb126)bb21)&0xff ));};{bbg->bb172
[bbg->bb182++]=((bb155)((bb126)((bb126)bb21)>>8 ));};};{{bbg->bb172[
bbg->bb182++]=((bb155)(((bb126)~bb21)&0xff ));};{bbg->bb172[bbg->bb182
++]=((bb155)((bb126)((bb126)~bb21)>>8 ));};};}bb107(bb21--){{bbg->
bb172[bbg->bb182++]=( *bb40++);};}}
