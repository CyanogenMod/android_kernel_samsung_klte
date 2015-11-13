/*
   'src_compress_deflate_deflate.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Sun Nov 16 20:01:26 2014
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
bb1292,bbe bb1112));bb41 bbh bb459 bb1738[(256 +1 +29 )+2 ]={{{12 },{8 }},{
{140 },{8 }},{{76 },{8 }},{{204 },{8 }},{{44 },{8 }},{{172 },{8 }},{{108 },{8 }},
{{236 },{8 }},{{28 },{8 }},{{156 },{8 }},{{92 },{8 }},{{220 },{8 }},{{60 },{8 }},
{{188 },{8 }},{{124 },{8 }},{{252 },{8 }},{{2 },{8 }},{{130 },{8 }},{{66 },{8 }},
{{194 },{8 }},{{34 },{8 }},{{162 },{8 }},{{98 },{8 }},{{226 },{8 }},{{18 },{8 }},
{{146 },{8 }},{{82 },{8 }},{{210 },{8 }},{{50 },{8 }},{{178 },{8 }},{{114 },{8 }}
,{{242 },{8 }},{{10 },{8 }},{{138 },{8 }},{{74 },{8 }},{{202 },{8 }},{{42 },{8 }}
,{{170 },{8 }},{{106 },{8 }},{{234 },{8 }},{{26 },{8 }},{{154 },{8 }},{{90 },{8 }
},{{218 },{8 }},{{58 },{8 }},{{186 },{8 }},{{122 },{8 }},{{250 },{8 }},{{6 },{8 }
},{{134 },{8 }},{{70 },{8 }},{{198 },{8 }},{{38 },{8 }},{{166 },{8 }},{{102 },{8
}},{{230 },{8 }},{{22 },{8 }},{{150 },{8 }},{{86 },{8 }},{{214 },{8 }},{{54 },{8
}},{{182 },{8 }},{{118 },{8 }},{{246 },{8 }},{{14 },{8 }},{{142 },{8 }},{{78 },{
8 }},{{206 },{8 }},{{46 },{8 }},{{174 },{8 }},{{110 },{8 }},{{238 },{8 }},{{30 },
{8 }},{{158 },{8 }},{{94 },{8 }},{{222 },{8 }},{{62 },{8 }},{{190 },{8 }},{{126 }
,{8 }},{{254 },{8 }},{{1 },{8 }},{{129 },{8 }},{{65 },{8 }},{{193 },{8 }},{{33 },
{8 }},{{161 },{8 }},{{97 },{8 }},{{225 },{8 }},{{17 },{8 }},{{145 },{8 }},{{81 },
{8 }},{{209 },{8 }},{{49 },{8 }},{{177 },{8 }},{{113 },{8 }},{{241 },{8 }},{{9 },
{8 }},{{137 },{8 }},{{73 },{8 }},{{201 },{8 }},{{41 },{8 }},{{169 },{8 }},{{105 }
,{8 }},{{233 },{8 }},{{25 },{8 }},{{153 },{8 }},{{89 },{8 }},{{217 },{8 }},{{57 }
,{8 }},{{185 },{8 }},{{121 },{8 }},{{249 },{8 }},{{5 },{8 }},{{133 },{8 }},{{69 }
,{8 }},{{197 },{8 }},{{37 },{8 }},{{165 },{8 }},{{101 },{8 }},{{229 },{8 }},{{21
},{8 }},{{149 },{8 }},{{85 },{8 }},{{213 },{8 }},{{53 },{8 }},{{181 },{8 }},{{
117 },{8 }},{{245 },{8 }},{{13 },{8 }},{{141 },{8 }},{{77 },{8 }},{{205 },{8 }},{
{45 },{8 }},{{173 },{8 }},{{109 },{8 }},{{237 },{8 }},{{29 },{8 }},{{157 },{8 }},
{{93 },{8 }},{{221 },{8 }},{{61 },{8 }},{{189 },{8 }},{{125 },{8 }},{{253 },{8 }}
,{{19 },{9 }},{{275 },{9 }},{{147 },{9 }},{{403 },{9 }},{{83 },{9 }},{{339 },{9 }
},{{211 },{9 }},{{467 },{9 }},{{51 },{9 }},{{307 },{9 }},{{179 },{9 }},{{435 },{
9 }},{{115 },{9 }},{{371 },{9 }},{{243 },{9 }},{{499 },{9 }},{{11 },{9 }},{{267 }
,{9 }},{{139 },{9 }},{{395 },{9 }},{{75 },{9 }},{{331 },{9 }},{{203 },{9 }},{{
459 },{9 }},{{43 },{9 }},{{299 },{9 }},{{171 },{9 }},{{427 },{9 }},{{107 },{9 }},
{{363 },{9 }},{{235 },{9 }},{{491 },{9 }},{{27 },{9 }},{{283 },{9 }},{{155 },{9 }
},{{411 },{9 }},{{91 },{9 }},{{347 },{9 }},{{219 },{9 }},{{475 },{9 }},{{59 },{9
}},{{315 },{9 }},{{187 },{9 }},{{443 },{9 }},{{123 },{9 }},{{379 },{9 }},{{251 }
,{9 }},{{507 },{9 }},{{7 },{9 }},{{263 },{9 }},{{135 },{9 }},{{391 },{9 }},{{71 }
,{9 }},{{327 },{9 }},{{199 },{9 }},{{455 },{9 }},{{39 },{9 }},{{295 },{9 }},{{
167 },{9 }},{{423 },{9 }},{{103 },{9 }},{{359 },{9 }},{{231 },{9 }},{{487 },{9 }}
,{{23 },{9 }},{{279 },{9 }},{{151 },{9 }},{{407 },{9 }},{{87 },{9 }},{{343 },{9 }
},{{215 },{9 }},{{471 },{9 }},{{55 },{9 }},{{311 },{9 }},{{183 },{9 }},{{439 },{
9 }},{{119 },{9 }},{{375 },{9 }},{{247 },{9 }},{{503 },{9 }},{{15 },{9 }},{{271 }
,{9 }},{{143 },{9 }},{{399 },{9 }},{{79 },{9 }},{{335 },{9 }},{{207 },{9 }},{{
463 },{9 }},{{47 },{9 }},{{303 },{9 }},{{175 },{9 }},{{431 },{9 }},{{111 },{9 }},
{{367 },{9 }},{{239 },{9 }},{{495 },{9 }},{{31 },{9 }},{{287 },{9 }},{{159 },{9 }
},{{415 },{9 }},{{95 },{9 }},{{351 },{9 }},{{223 },{9 }},{{479 },{9 }},{{63 },{9
}},{{319 },{9 }},{{191 },{9 }},{{447 },{9 }},{{127 },{9 }},{{383 },{9 }},{{255 }
,{9 }},{{511 },{9 }},{{0 },{7 }},{{64 },{7 }},{{32 },{7 }},{{96 },{7 }},{{16 },{7
}},{{80 },{7 }},{{48 },{7 }},{{112 },{7 }},{{8 },{7 }},{{72 },{7 }},{{40 },{7 }},
{{104 },{7 }},{{24 },{7 }},{{88 },{7 }},{{56 },{7 }},{{120 },{7 }},{{4 },{7 }},{{
68 },{7 }},{{36 },{7 }},{{100 },{7 }},{{20 },{7 }},{{84 },{7 }},{{52 },{7 }},{{
116 },{7 }},{{3 },{8 }},{{131 },{8 }},{{67 },{8 }},{{195 },{8 }},{{35 },{8 }},{{
163 },{8 }},{{99 },{8 }},{{227 },{8 }}};bb41 bbh bb459 bb2235[30 ]={{{0 },{5 }
},{{16 },{5 }},{{8 },{5 }},{{24 },{5 }},{{4 },{5 }},{{20 },{5 }},{{12 },{5 }},{{
28 },{5 }},{{2 },{5 }},{{18 },{5 }},{{10 },{5 }},{{26 },{5 }},{{6 },{5 }},{{22 },{
5 }},{{14 },{5 }},{{30 },{5 }},{{1 },{5 }},{{17 },{5 }},{{9 },{5 }},{{25 },{5 }},{
{5 },{5 }},{{21 },{5 }},{{13 },{5 }},{{29 },{5 }},{{3 },{5 }},{{19 },{5 }},{{11 },
{5 }},{{27 },{5 }},{{7 },{5 }},{{23 },{5 }}};bb41 bbh bb155 bb1735[512 ]={0 ,1
,2 ,3 ,4 ,4 ,5 ,5 ,6 ,6 ,6 ,6 ,7 ,7 ,7 ,7 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,9 ,10 ,10 ,10
,10 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,10 ,11 ,11 ,11 ,11 ,11 ,11 ,11 ,11 ,11 ,11
,11 ,11 ,11 ,11 ,11 ,11 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12
,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,12 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13
,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13 ,13
,13 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14
,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14
,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,14 ,15 ,15 ,15 ,15
,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15
,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15
,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,0 ,0 ,16 ,17 ,18 ,18 ,19 ,19 ,20 ,
20 ,20 ,20 ,21 ,21 ,21 ,21 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,
24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,
25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,
26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,27 ,27 ,27 ,27 ,27 ,
27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,
27 ,27 ,27 ,27 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,
28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,
28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,28 ,29 ,
29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,
29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,
29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 ,29 };bb41 bbh bb155
bb2052[258 -3 +1 ]={0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,8 ,9 ,9 ,10 ,10 ,11 ,11 ,12 ,12 ,12 ,12 ,13 ,
13 ,13 ,13 ,14 ,14 ,14 ,14 ,15 ,15 ,15 ,15 ,16 ,16 ,16 ,16 ,16 ,16 ,16 ,16 ,17 ,17 ,17 ,17 ,
17 ,17 ,17 ,17 ,18 ,18 ,18 ,18 ,18 ,18 ,18 ,18 ,19 ,19 ,19 ,19 ,19 ,19 ,19 ,19 ,20 ,20 ,20 ,
20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,20 ,21 ,21 ,21 ,21 ,21 ,21 ,21 ,21 ,21 ,21 ,
21 ,21 ,21 ,21 ,21 ,21 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,22 ,23 ,
23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,23 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,
24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,
24 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,
25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,
26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,26 ,27 ,27 ,27 ,27 ,
27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,
27 ,27 ,27 ,27 ,28 };bb41 bbh bbe bb2334[29 ]={0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,10 ,12 ,14 ,
16 ,20 ,24 ,28 ,32 ,40 ,48 ,56 ,64 ,80 ,96 ,112 ,128 ,160 ,192 ,224 ,0 };bb41 bbh bbe
bb2417[30 ]={0 ,1 ,2 ,3 ,4 ,6 ,8 ,12 ,16 ,24 ,32 ,48 ,64 ,96 ,128 ,192 ,256 ,384 ,512 ,
768 ,1024 ,1536 ,2048 ,3072 ,4096 ,6144 ,8192 ,12288 ,16384 ,24576 };bba bb10{
bb1282,bb2160,bb1756,bb2141}bb1824;bba bb1824( *bb2388)bbp((bb192*bbg
,bbe bb175));bb41 bbb bb2191 bbp((bb192*bbg));bb41 bb1824 bb2381 bbp(
(bb192*bbg,bbe bb175));bb41 bb1824 bb2162 bbp((bb192*bbg,bbe bb175));
bb41 bb1824 bb1946 bbp((bb192*bbg,bbe bb175));bb41 bbb bb2430 bbp((
bb192*bbg));bb41 bbb bb2008 bbp((bb192*bbg,bb7 bbn));bb41 bbb bb1265
bbp((bb17 bb16));bb41 bbe bb2435 bbp((bb17 bb16,bb30*bb40,bbs bb47));
bb41 bb7 bb2258 bbp((bb192*bbg,bb1318 bb1993));bba bbi bb2627{bb126
bb2431;bb126 bb2439;bb126 bb2385;bb126 bb2348;bb2388 bb2021;}bb2513;
bb41 bbh bb2513 bb1333[10 ]={{0 ,0 ,0 ,0 ,bb2381},{4 ,4 ,8 ,4 ,bb2162},{4 ,5 ,16
,8 ,bb2162},{4 ,6 ,32 ,32 ,bb2162},{4 ,4 ,16 ,16 ,bb1946},{8 ,16 ,32 ,32 ,bb1946},
{8 ,16 ,128 ,128 ,bb1946},{8 ,32 ,128 ,256 ,bb1946},{32 ,128 ,258 ,1024 ,bb1946},
{32 ,258 ,258 ,4096 ,bb1946}};bbi bb2278{bbe bb445;};bbe bb1115(bb16,
bb124,bb188,bb195)bb17 bb16;bbe bb124;bbh bbl*bb188;bbe bb195;{bb2
bb1048(bb16,bb124,8 ,15 ,bb788,0 ,bb188,bb195);}bbe bb1048(bb16,bb124,
bb566,bb454,bb956,bb295,bb188,bb195)bb17 bb16;bbe bb124;bbe bb566;bbe
bb454;bbe bb956;bbe bb295;bbh bbl*bb188;bbe bb195;{bb192*bbg;bbe
bb1347=0 ;bb41 bbh bbl*bb2443="\x31\x2e\x31\x2e\x33";bb501*bb1883;bbm(
bb188==0 ||bb188[0 ]!=bb2443[0 ]||bb195!=bb12(bb439)){bb2(-6 );}bbm(bb16
==0 )bb2(-2 );bb16->bb323=0 ;bbm(bb16->bb401==0 ){bb16->bb401=bb1166;bb16
->bb110=(bb70)0 ;}bbm(bb16->bb372==0 )bb16->bb372=bb1160;bbm(bb124==(-1
))bb124=6 ;bbm(bb454<0 ){bb1347=1 ;bb454=-bb454;}bbm(bb956<1 ||bb956>
bb290||bb566!=8 ||bb454<8 ||bb454>15 ||bb124<0 ||bb124>9 ||bb295<0 ||bb295>
2 ){bb2(-2 );}bbg=(bb192* )( * ((bb16)->bb401))((bb16)->bb110,(1 ),(bb12
(bb192)));bbm(bbg==0 )bb2(-4 );bb16->bb23=(bbi bb376* )bbg;bbg->bb16=
bb16;bbg->bb1347=bb1347;bbg->bb2163=bb454;bbg->bb936=1 <<bbg->bb2163;
bbg->bb1808=bbg->bb936-1 ;bbg->bb2130=bb956+7 ;bbg->bb1326=1 <<bbg->
bb2130;bbg->bb1380=bbg->bb1326-1 ;bbg->bb1611=((bbg->bb2130+3 -1 )/3 );
bbg->bb158=(bb30* )( * ((bb16)->bb401))((bb16)->bb110,(bbg->bb936),(2
 *bb12(bb153)));bbg->bb967=(bb1370* )( * ((bb16)->bb401))((bb16)->
bb110,(bbg->bb936),(bb12(bb1061)));bbg->bb383=(bb1370* )( * ((bb16)->
bb401))((bb16)->bb110,(bbg->bb1326),(bb12(bb1061)));bbg->bb1125=1 <<(
bb956+6 );bb1883=(bb501* )( * ((bb16)->bb401))((bb16)->bb110,(bbg->
bb1125),(bb12(bb126)+2 ));bbg->bb172=(bb1209* )bb1883;bbg->bb2039=(
bb398)bbg->bb1125* (bb12(bb126)+2L );bbm(bbg->bb158==0 ||bbg->bb967==0
||bbg->bb383==0 ||bbg->bb172==0 ){bb16->bb323=(bbl* )bb1067[2 -((-4 ))];
bb944(bb16);bb2(-4 );}bbg->bb1645=bb1883+bbg->bb1125/bb12(bb126);bbg->
bb1725=bbg->bb172+(1 +bb12(bb126)) *bbg->bb1125;bbg->bb124=bb124;bbg->
bb295=bb295;bbg->bb566=(bb153)bb566;bb2 bb1053(bb16);}bbe bb1178(bb16
,bb426,bb436)bb17 bb16;bbh bb30*bb426;bb7 bb436;{bb192*bbg;bb7 bb465=
bb436;bb7 bb11;bb1318 bb1134=0 ;bbm(bb16==0 ||bb16->bb23==0 ||bb426==0 ||
bb16->bb23->bb360!=42 )bb2(-2 );bbg=bb16->bb23;bb16->bb367=bb986(bb16->
bb367,bb426,bb436);bbm(bb465<3 )bb2 0 ;bbm(bb465>((bbg)->bb936-(258 +3 +1
))){bb465=((bbg)->bb936-(258 +3 +1 ));bb426+=bb436-bb465;}bb81(bbg->
bb158,bb426,bb465);bbg->bb183=bb465;bbg->bb429=(bb5)bb465;bbg->bb491=
bbg->bb158[0 ];(bbg->bb491=(((bbg->bb491)<<bbg->bb1611)^(bbg->bb158[1 ]
))&bbg->bb1380);bb91(bb11=0 ;bb11<=bb465-3 ;bb11++){((bbg->bb491=(((bbg
->bb491)<<bbg->bb1611)^(bbg->bb158[(bb11)+(3 -1 )]))&bbg->bb1380),bbg->
bb967[(bb11)&bbg->bb1808]=bb1134=bbg->bb383[bbg->bb491],bbg->bb383[
bbg->bb491]=(bb1061)(bb11));}bbm(bb1134)bb1134=0 ;bb2 0 ;}bbe bb1053(
bb16)bb17 bb16;{bb192*bbg;bbm(bb16==0 ||bb16->bb23==0 ||bb16->bb401==0
||bb16->bb372==0 )bb2(-2 );bb16->bb191=bb16->bb613=0 ;bb16->bb323=0 ;bb16
->bb968=2 ;bbg=(bb192* )bb16->bb23;bbg->bb182=0 ;bbg->bb1875=bbg->bb172
;bbm(bbg->bb1347<0 ){bbg->bb1347=0 ;}bbg->bb360=bbg->bb1347?113 :42 ;bb16
->bb367=1 ;bbg->bb1894=0 ;bb2210(bbg);bb2430(bbg);bb2 0 ;}bbe bb1176(
bb16,bb124,bb295)bb17 bb16;bbe bb124;bbe bb295;{bb192*bbg;bb2388
bb2021;bbe bb18=0 ;bbm(bb16==0 ||bb16->bb23==0 )bb2(-2 );bbg=bb16->bb23;
bbm(bb124==(-1 )){bb124=6 ;}bbm(bb124<0 ||bb124>9 ||bb295<0 ||bb295>2 ){bb2
(-2 );}bb2021=bb1333[bbg->bb124].bb2021;bbm(bb2021!=bb1333[bb124].
bb2021&&bb16->bb191!=0 ){bb18=bb511(bb16,1 );}bbm(bbg->bb124!=bb124){
bbg->bb124=bb124;bbg->bb2055=bb1333[bb124].bb2439;bbg->bb2182=bb1333[
bb124].bb2431;bbg->bb1837=bb1333[bb124].bb2385;bbg->bb2177=bb1333[
bb124].bb2348;}bbg->bb295=bb295;bb2 bb18;}bb41 bbb bb2008(bbg,bbn)bb192
 *bbg;bb7 bbn;{{bbg->bb172[bbg->bb182++]=((bb153)(bbn>>8 ));};{bbg->
bb172[bbg->bb182++]=((bb153)(bbn&0xff ));};}bb41 bbb bb1265(bb16)bb17
bb16;{bbs bb21=bb16->bb23->bb182;bbm(bb21>bb16->bb384)bb21=bb16->
bb384;bbm(bb21==0 )bb2;bb81(bb16->bb597,bb16->bb23->bb1875,bb21);bb16
->bb597+=bb21;bb16->bb23->bb1875+=bb21;bb16->bb613+=bb21;bb16->bb384
-=bb21;bb16->bb23->bb182-=bb21;bbm(bb16->bb23->bb182==0 ){bb16->bb23->
bb1875=bb16->bb23->bb172;}}bbe bb511(bb16,bb175)bb17 bb16;bbe bb175;{
bbe bb2344;bb192*bbg;bbm(bb16==0 ||bb16->bb23==0 ||bb175>4 ||bb175<0 ){
bb2(-2 );}bbg=bb16->bb23;bbm(bb16->bb597==0 ||(bb16->bb127==0 &&bb16->
bb148!=0 )||(bbg->bb360==666 &&bb175!=4 )){bb2(bb16->bb323=(bbl* )bb1067
[2 -((-2 ))],((-2 )));}bbm(bb16->bb384==0 )bb2(bb16->bb323=(bbl* )bb1067[
2 -((-5 ))],((-5 )));bbg->bb16=bb16;bb2344=bbg->bb1894;bbg->bb1894=bb175
;bbm(bbg->bb360==42 ){bb7 bb978=(8 +((bbg->bb2163-8 )<<4 ))<<8 ;bb7 bb2299
=(bbg->bb124-1 )>>1 ;bbm(bb2299>3 )bb2299=3 ;bb978|=(bb2299<<6 );bbm(bbg->
bb183!=0 )bb978|=0x20 ;bb978+=31 -(bb978%31 );bbg->bb360=113 ;bb2008(bbg,
bb978);bbm(bbg->bb183!=0 ){bb2008(bbg,(bb7)(bb16->bb367>>16 ));bb2008(
bbg,(bb7)(bb16->bb367&0xffff ));}bb16->bb367=1L ;}bbm(bbg->bb182!=0 ){
bb1265(bb16);bbm(bb16->bb384==0 ){bbg->bb1894=-1 ;bb2 0 ;}}bb54 bbm(bb16
->bb148==0 &&bb175<=bb2344&&bb175!=4 ){bb2(bb16->bb323=(bbl* )bb1067[2 -
((-5 ))],((-5 )));}bbm(bbg->bb360==666 &&bb16->bb148!=0 ){bb2(bb16->bb323
=(bbl* )bb1067[2 -((-5 ))],((-5 )));}bbm(bb16->bb148!=0 ||bbg->bb463!=0 ||
(bb175!=0 &&bbg->bb360!=666 )){bb1824 bb1985;bb1985=( * (bb1333[bbg->
bb124].bb2021))(bbg,bb175);bbm(bb1985==bb1756||bb1985==bb2141){bbg->
bb360=666 ;}bbm(bb1985==bb1282||bb1985==bb1756){bbm(bb16->bb384==0 ){
bbg->bb1894=-1 ;}bb2 0 ;}bbm(bb1985==bb2160){bbm(bb175==1 ){bb2255(bbg);
}bb54{bb2144(bbg,(bbl* )0 ,0L ,0 );bbm(bb175==3 ){bbg->bb383[bbg->bb1326-
1 ]=0 ;bb997((bb30* )bbg->bb383,0 ,(bbs)(bbg->bb1326-1 ) *bb12( *bbg->
bb383));;}}bb1265(bb16);bbm(bb16->bb384==0 ){bbg->bb1894=-1 ;bb2 0 ;}}};
bbm(bb175!=4 )bb2 0 ;bbm(bbg->bb1347)bb2 1 ;bb2008(bbg,(bb7)(bb16->bb367
>>16 ));bb2008(bbg,(bb7)(bb16->bb367&0xffff ));bb1265(bb16);bbg->bb1347
=-1 ;bb2 bbg->bb182!=0 ?0 :1 ;}bbe bb944(bb16)bb17 bb16;{bbe bb360;bbm(
bb16==0 ||bb16->bb23==0 )bb2(-2 );bb360=bb16->bb23->bb360;bbm(bb360!=42
&&bb360!=113 &&bb360!=666 ){bb2(-2 );}{bbm(bb16->bb23->bb172)( * ((bb16)->
bb372))((bb16)->bb110,(bb70)(bb16->bb23->bb172));};{bbm(bb16->bb23->
bb383)( * ((bb16)->bb372))((bb16)->bb110,(bb70)(bb16->bb23->bb383));}
;{bbm(bb16->bb23->bb967)( * ((bb16)->bb372))((bb16)->bb110,(bb70)(
bb16->bb23->bb967));};{bbm(bb16->bb23->bb158)( * ((bb16)->bb372))((
bb16)->bb110,(bb70)(bb16->bb23->bb158));};( * ((bb16)->bb372))((bb16)->
bb110,(bb70)(bb16->bb23));bb16->bb23=0 ;bb2 bb360==113 ?(-3 ):0 ;}bbe
bb1151(bb130,bb185)bb17 bb130;bb17 bb185;{
#ifdef bb507
bb2(-2 );
#else
bb192*bb423;bb192*bb1825;bb501*bb1883;bbm(bb185==0 ||bb130==0 ||bb185->
bb23==0 ){bb2(-2 );}bb1825=bb185->bb23; *bb130= *bb185;bb423=(bb192* )(
 * ((bb130)->bb401))((bb130)->bb110,(1 ),(bb12(bb192)));bbm(bb423==0 )bb2
(-4 );bb130->bb23=(bbi bb376* )bb423; *bb423= *bb1825;bb423->bb16=
bb130;bb423->bb158=(bb30* )( * ((bb130)->bb401))((bb130)->bb110,(
bb423->bb936),(2 *bb12(bb153)));bb423->bb967=(bb1370* )( * ((bb130)->
bb401))((bb130)->bb110,(bb423->bb936),(bb12(bb1061)));bb423->bb383=(
bb1370* )( * ((bb130)->bb401))((bb130)->bb110,(bb423->bb1326),(bb12(
bb1061)));bb1883=(bb501* )( * ((bb130)->bb401))((bb130)->bb110,(bb423
->bb1125),(bb12(bb126)+2 ));bb423->bb172=(bb1209* )bb1883;bbm(bb423->
bb158==0 ||bb423->bb967==0 ||bb423->bb383==0 ||bb423->bb172==0 ){bb944(
bb130);bb2(-4 );}bb81(bb423->bb158,bb1825->bb158,bb423->bb936*2 *bb12(
bb153));bb81((bb30* )bb423->bb967,(bb30* )bb1825->bb967,bb423->bb936*
bb12(bb1061));bb81((bb30* )bb423->bb383,(bb30* )bb1825->bb383,bb423->
bb1326*bb12(bb1061));bb81(bb423->bb172,bb1825->bb172,(bb7)bb423->
bb2039);bb423->bb1875=bb423->bb172+(bb1825->bb1875-bb1825->bb172);
bb423->bb1645=bb1883+bb423->bb1125/bb12(bb126);bb423->bb1725=bb423->
bb172+(1 +bb12(bb126)) *bb423->bb1125;bb423->bb1936.bb1748=bb423->
bb969;bb423->bb1862.bb1748=bb423->bb1682;bb423->bb2062.bb1748=bb423->
bb532;bb2 0 ;
#endif
}bb41 bbe bb2435(bb16,bb40,bb47)bb17 bb16;bb30*bb40;bbs bb47;{bbs bb21
=bb16->bb148;bbm(bb21>bb47)bb21=bb47;bbm(bb21==0 )bb2 0 ;bb16->bb148-=
bb21;bbm(!bb16->bb23->bb1347){bb16->bb367=bb986(bb16->bb367,bb16->
bb127,bb21);}bb81(bb40,bb16->bb127,bb21);bb16->bb127+=bb21;bb16->
bb191+=bb21;bb2(bbe)bb21;}bb41 bbb bb2430(bbg)bb192*bbg;{bbg->bb2227=
(bb398)2L *bbg->bb936;bbg->bb383[bbg->bb1326-1 ]=0 ;bb997((bb30* )bbg->
bb383,0 ,(bbs)(bbg->bb1326-1 ) *bb12( *bbg->bb383));;bbg->bb2055=bb1333
[bbg->bb124].bb2439;bbg->bb2182=bb1333[bbg->bb124].bb2431;bbg->bb1837
=bb1333[bbg->bb124].bb2385;bbg->bb2177=bb1333[bbg->bb124].bb2348;bbg
->bb183=0 ;bbg->bb429=0L ;bbg->bb463=0 ;bbg->bb953=bbg->bb1262=3 -1 ;bbg->
bb1939=0 ;bbg->bb491=0 ;}bb41 bb7 bb2258(bbg,bb1993)bb192*bbg;bb1318
bb1993;{bbs bb2319=bbg->bb2177;bb932 bb30*bb497=bbg->bb158+bbg->bb183
;bb932 bb30*bb608;bb932 bbe bb21;bbe bb1189=bbg->bb1262;bbe bb1837=
bbg->bb1837;bb1318 bb2445=bbg->bb183>(bb1318)((bbg)->bb936-(258 +3 +1 ))?
bbg->bb183-(bb1318)((bbg)->bb936-(258 +3 +1 )):0 ;bb1370*bb967=bbg->bb967
;bb7 bb2471=bbg->bb1808;
#ifdef bb1041
bb932 bb30*bb1893=bbg->bb158+bbg->bb183+258 -1 ;bb932 bb126 bb2533= * (
bb501* )bb497;bb932 bb126 bb2121= * (bb501* )(bb497+bb1189-1 );
#else
bb932 bb30*bb1893=bbg->bb158+bbg->bb183+258 ;bb932 bb153 bb2320=bb497[
bb1189-1 ];bb932 bb153 bb2121=bb497[bb1189];
#endif
;bbm(bbg->bb1262>=bbg->bb2182){bb2319>>=2 ;}bbm((bb7)bb1837>bbg->bb463
)bb1837=bbg->bb463;;bb574{;bb608=bbg->bb158+bb1993;
#if ( defined( bb1041) && bb2582 == 258)
bbm( * (bb501* )(bb608+bb1189-1 )!=bb2121|| * (bb501* )bb608!=bb2533)bb1689
;;bb497++,bb608++;bb574{}bb107( * (bb501* )(bb497+=2 )== * (bb501* )(
bb608+=2 )&& * (bb501* )(bb497+=2 )== * (bb501* )(bb608+=2 )&& * (bb501*
)(bb497+=2 )== * (bb501* )(bb608+=2 )&& * (bb501* )(bb497+=2 )== * (
bb501* )(bb608+=2 )&&bb497<bb1893);;bbm( *bb497== *bb608)bb497++;bb21=
(258 -1 )-(bbe)(bb1893-bb497);bb497=bb1893-(258 -1 );
#else
bbm(bb608[bb1189]!=bb2121||bb608[bb1189-1 ]!=bb2320|| *bb608!= *bb497
|| * ++bb608!=bb497[1 ])bb1689;bb497+=2 ,bb608++;;bb574{}bb107( * ++
bb497== * ++bb608&& * ++bb497== * ++bb608&& * ++bb497== * ++bb608&& *
++bb497== * ++bb608&& * ++bb497== * ++bb608&& * ++bb497== * ++bb608&&
 * ++bb497== * ++bb608&& * ++bb497== * ++bb608&&bb497<bb1893);;bb21=
258 -(bbe)(bb1893-bb497);bb497=bb1893-258 ;
#endif
bbm(bb21>bb1189){bbg->bb2023=bb1993;bb1189=bb21;bbm(bb21>=bb1837)bb22
;
#ifdef bb1041
bb2121= * (bb501* )(bb497+bb1189-1 );
#else
bb2320=bb497[bb1189-1 ];bb2121=bb497[bb1189];
#endif
}}bb107((bb1993=bb967[bb1993&bb2471])>bb2445&&--bb2319!=0 );bbm((bb7)bb1189
<=bbg->bb463)bb2(bb7)bb1189;bb2 bbg->bb463;}bb41 bbb bb2191(bbg)bb192
 *bbg;{bb932 bbs bb11,bb95;bb932 bb1370*bb28;bbs bb1927;bb7 bb1224=
bbg->bb936;bb574{bb1927=(bbs)(bbg->bb2227-(bb398)bbg->bb463-(bb398)bbg
->bb183);bbm(bb1927==0 &&bbg->bb183==0 &&bbg->bb463==0 ){bb1927=bb1224;}
bb54 bbm(bb1927==(bbs)(-1 )){bb1927--;}bb54 bbm(bbg->bb183>=bb1224+((
bbg)->bb936-(258 +3 +1 ))){bb81(bbg->bb158,bbg->bb158+bb1224,(bbs)bb1224
);bbg->bb2023-=bb1224;bbg->bb183-=bb1224;bbg->bb429-=(bb5)bb1224;bb11
=bbg->bb1326;bb28=&bbg->bb383[bb11];bb574{bb95= * --bb28; *bb28=(
bb1061)(bb95>=bb1224?bb95-bb1224:0 );}bb107(--bb11);bb11=bb1224;bb28=&
bbg->bb967[bb11];bb574{bb95= * --bb28; *bb28=(bb1061)(bb95>=bb1224?
bb95-bb1224:0 );}bb107(--bb11);bb1927+=bb1224;}bbm(bbg->bb16->bb148==0
)bb2;;bb11=bb2435(bbg->bb16,bbg->bb158+bbg->bb183+bbg->bb463,bb1927);
bbg->bb463+=bb11;bbm(bbg->bb463>=3 ){bbg->bb491=bbg->bb158[bbg->bb183]
;(bbg->bb491=(((bbg->bb491)<<bbg->bb1611)^(bbg->bb158[bbg->bb183+1 ]))&
bbg->bb1380);}}bb107(bbg->bb463<(258 +3 +1 )&&bbg->bb16->bb148!=0 );}bb41
bb1824 bb2381(bbg,bb175)bb192*bbg;bbe bb175;{bb398 bb2274=0xffff ;
bb398 bb2154;bbm(bb2274>bbg->bb2039-5 ){bb2274=bbg->bb2039-5 ;}bb91(;;){
bbm(bbg->bb463<=1 ){;bb2191(bbg);bbm(bbg->bb463==0 &&bb175==0 )bb2 bb1282
;bbm(bbg->bb463==0 )bb22;};bbg->bb183+=bbg->bb463;bbg->bb463=0 ;bb2154=
bbg->bb429+bb2274;bbm(bbg->bb183==0 ||(bb398)bbg->bb183>=bb2154){bbg->
bb463=(bb7)(bbg->bb183-bb2154);bbg->bb183=(bb7)bb2154;{{bb1619(bbg,(
bbg->bb429>=0L ?(bb440* )&bbg->bb158[(bbs)bbg->bb429]:(bb440* )0 ),(
bb398)((bb5)bbg->bb183-bbg->bb429),(0 ));bbg->bb429=bbg->bb183;bb1265(
bbg->bb16);;};bbm(bbg->bb16->bb384==0 )bb2(0 )?bb1756:bb1282;};}bbm(bbg
->bb183-(bb7)bbg->bb429>=((bbg)->bb936-(258 +3 +1 ))){{{bb1619(bbg,(bbg
->bb429>=0L ?(bb440* )&bbg->bb158[(bbs)bbg->bb429]:(bb440* )0 ),(bb398)(
(bb5)bbg->bb183-bbg->bb429),(0 ));bbg->bb429=bbg->bb183;bb1265(bbg->
bb16);;};bbm(bbg->bb16->bb384==0 )bb2(0 )?bb1756:bb1282;};}}{{bb1619(
bbg,(bbg->bb429>=0L ?(bb440* )&bbg->bb158[(bbs)bbg->bb429]:(bb440* )0 ),
(bb398)((bb5)bbg->bb183-bbg->bb429),(bb175==4 ));bbg->bb429=bbg->bb183
;bb1265(bbg->bb16);;};bbm(bbg->bb16->bb384==0 )bb2(bb175==4 )?bb1756:
bb1282;};bb2 bb175==4 ?bb2141:bb2160;}bb41 bb1824 bb2162(bbg,bb175)bb192
 *bbg;bbe bb175;{bb1318 bb1134=0 ;bbe bb1762;bb91(;;){bbm(bbg->bb463<(
258 +3 +1 )){bb2191(bbg);bbm(bbg->bb463<(258 +3 +1 )&&bb175==0 ){bb2 bb1282;
}bbm(bbg->bb463==0 )bb22;}bbm(bbg->bb463>=3 ){((bbg->bb491=(((bbg->
bb491)<<bbg->bb1611)^(bbg->bb158[(bbg->bb183)+(3 -1 )]))&bbg->bb1380),
bbg->bb967[(bbg->bb183)&bbg->bb1808]=bb1134=bbg->bb383[bbg->bb491],
bbg->bb383[bbg->bb491]=(bb1061)(bbg->bb183));}bbm(bb1134!=0 &&bbg->
bb183-bb1134<=((bbg)->bb936-(258 +3 +1 ))){bbm(bbg->bb295!=2 ){bbg->bb953
=bb2258(bbg,bb1134);}}bbm(bbg->bb953>=3 ){;{bb155 bb21=(bbg->bb953-3 );
bb126 bb415=(bbg->bb183-bbg->bb2023);bbg->bb1645[bbg->bb609]=bb415;
bbg->bb1725[bbg->bb609++]=bb21;bb415--;bbg->bb969[bb2052[bb21]+256 +1 ]
.bb258.bb430++;bbg->bb1682[((bb415)<256 ?bb1735[bb415]:bb1735[256 +((
bb415)>>7 )])].bb258.bb430++;bb1762=(bbg->bb609==bbg->bb1125-1 );};bbg
->bb463-=bbg->bb953;bbm(bbg->bb953<=bbg->bb2055&&bbg->bb463>=3 ){bbg->
bb953--;bb574{bbg->bb183++;((bbg->bb491=(((bbg->bb491)<<bbg->bb1611)^
(bbg->bb158[(bbg->bb183)+(3 -1 )]))&bbg->bb1380),bbg->bb967[(bbg->bb183
)&bbg->bb1808]=bb1134=bbg->bb383[bbg->bb491],bbg->bb383[bbg->bb491]=(
bb1061)(bbg->bb183));}bb107(--bbg->bb953!=0 );bbg->bb183++;}bb54{bbg->
bb183+=bbg->bb953;bbg->bb953=0 ;bbg->bb491=bbg->bb158[bbg->bb183];(bbg
->bb491=(((bbg->bb491)<<bbg->bb1611)^(bbg->bb158[bbg->bb183+1 ]))&bbg
->bb1380);}}bb54{;{bb155 bb1841=(bbg->bb158[bbg->bb183]);bbg->bb1645[
bbg->bb609]=0 ;bbg->bb1725[bbg->bb609++]=bb1841;bbg->bb969[bb1841].
bb258.bb430++;bb1762=(bbg->bb609==bbg->bb1125-1 );};bbg->bb463--;bbg->
bb183++;}bbm(bb1762){{bb1619(bbg,(bbg->bb429>=0L ?(bb440* )&bbg->bb158
[(bbs)bbg->bb429]:(bb440* )0 ),(bb398)((bb5)bbg->bb183-bbg->bb429),(0 ));
bbg->bb429=bbg->bb183;bb1265(bbg->bb16);;};bbm(bbg->bb16->bb384==0 )bb2
(0 )?bb1756:bb1282;};}{{bb1619(bbg,(bbg->bb429>=0L ?(bb440* )&bbg->
bb158[(bbs)bbg->bb429]:(bb440* )0 ),(bb398)((bb5)bbg->bb183-bbg->bb429
),(bb175==4 ));bbg->bb429=bbg->bb183;bb1265(bbg->bb16);;};bbm(bbg->
bb16->bb384==0 )bb2(bb175==4 )?bb1756:bb1282;};bb2 bb175==4 ?bb2141:
bb2160;}bb41 bb1824 bb1946(bbg,bb175)bb192*bbg;bbe bb175;{bb1318
bb1134=0 ;bbe bb1762;bb91(;;){bbm(bbg->bb463<(258 +3 +1 )){bb2191(bbg);
bbm(bbg->bb463<(258 +3 +1 )&&bb175==0 ){bb2 bb1282;}bbm(bbg->bb463==0 )bb22
;}bbm(bbg->bb463>=3 ){((bbg->bb491=(((bbg->bb491)<<bbg->bb1611)^(bbg->
bb158[(bbg->bb183)+(3 -1 )]))&bbg->bb1380),bbg->bb967[(bbg->bb183)&bbg
->bb1808]=bb1134=bbg->bb383[bbg->bb491],bbg->bb383[bbg->bb491]=(
bb1061)(bbg->bb183));}bbg->bb1262=bbg->bb953,bbg->bb2298=bbg->bb2023;
bbg->bb953=3 -1 ;bbm(bb1134!=0 &&bbg->bb1262<bbg->bb2055&&bbg->bb183-
bb1134<=((bbg)->bb936-(258 +3 +1 ))){bbm(bbg->bb295!=2 ){bbg->bb953=
bb2258(bbg,bb1134);}bbm(bbg->bb953<=5 &&(bbg->bb295==1 ||(bbg->bb953==3
&&bbg->bb183-bbg->bb2023>4096 ))){bbg->bb953=3 -1 ;}}bbm(bbg->bb1262>=3
&&bbg->bb953<=bbg->bb1262){bb7 bb2493=bbg->bb183+bbg->bb463-3 ;;{bb155
bb21=(bbg->bb1262-3 );bb126 bb415=(bbg->bb183-1 -bbg->bb2298);bbg->
bb1645[bbg->bb609]=bb415;bbg->bb1725[bbg->bb609++]=bb21;bb415--;bbg->
bb969[bb2052[bb21]+256 +1 ].bb258.bb430++;bbg->bb1682[((bb415)<256 ?
bb1735[bb415]:bb1735[256 +((bb415)>>7 )])].bb258.bb430++;bb1762=(bbg->
bb609==bbg->bb1125-1 );};bbg->bb463-=bbg->bb1262-1 ;bbg->bb1262-=2 ;
bb574{bbm(++bbg->bb183<=bb2493){((bbg->bb491=(((bbg->bb491)<<bbg->
bb1611)^(bbg->bb158[(bbg->bb183)+(3 -1 )]))&bbg->bb1380),bbg->bb967[(
bbg->bb183)&bbg->bb1808]=bb1134=bbg->bb383[bbg->bb491],bbg->bb383[bbg
->bb491]=(bb1061)(bbg->bb183));}}bb107(--bbg->bb1262!=0 );bbg->bb1939=
0 ;bbg->bb953=3 -1 ;bbg->bb183++;bbm(bb1762){{bb1619(bbg,(bbg->bb429>=0L
?(bb440* )&bbg->bb158[(bbs)bbg->bb429]:(bb440* )0 ),(bb398)((bb5)bbg->
bb183-bbg->bb429),(0 ));bbg->bb429=bbg->bb183;bb1265(bbg->bb16);;};bbm
(bbg->bb16->bb384==0 )bb2(0 )?bb1756:bb1282;};}bb54 bbm(bbg->bb1939){;{
bb155 bb1841=(bbg->bb158[bbg->bb183-1 ]);bbg->bb1645[bbg->bb609]=0 ;bbg
->bb1725[bbg->bb609++]=bb1841;bbg->bb969[bb1841].bb258.bb430++;bb1762
=(bbg->bb609==bbg->bb1125-1 );};bbm(bb1762){{bb1619(bbg,(bbg->bb429>=
0L ?(bb440* )&bbg->bb158[(bbs)bbg->bb429]:(bb440* )0 ),(bb398)((bb5)bbg
->bb183-bbg->bb429),(0 ));bbg->bb429=bbg->bb183;bb1265(bbg->bb16);;};}
bbg->bb183++;bbg->bb463--;bbm(bbg->bb16->bb384==0 )bb2 bb1282;}bb54{
bbg->bb1939=1 ;bbg->bb183++;bbg->bb463--;}};bbm(bbg->bb1939){;{bb155
bb1841=(bbg->bb158[bbg->bb183-1 ]);bbg->bb1645[bbg->bb609]=0 ;bbg->
bb1725[bbg->bb609++]=bb1841;bbg->bb969[bb1841].bb258.bb430++;bb1762=(
bbg->bb609==bbg->bb1125-1 );};bbg->bb1939=0 ;}{{bb1619(bbg,(bbg->bb429
>=0L ?(bb440* )&bbg->bb158[(bbs)bbg->bb429]:(bb440* )0 ),(bb398)((bb5)bbg
->bb183-bbg->bb429),(bb175==4 ));bbg->bb429=bbg->bb183;bb1265(bbg->
bb16);;};bbm(bbg->bb16->bb384==0 )bb2(bb175==4 )?bb1756:bb1282;};bb2
bb175==4 ?bb2141:bb2160;}
