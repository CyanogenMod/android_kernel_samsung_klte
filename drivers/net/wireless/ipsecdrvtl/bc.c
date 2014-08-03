/*
   'src_compress_deflate_trees.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Wed Jan 15 12:08:55 2014
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
#if ( defined( _WIN32) || defined( __WIN32__)) && ! defined( WIN32)
#define WIN32
#endif
#if defined( __GNUC__) || defined( WIN32) || defined( bb1226) ||  \
defined( bb1198)
#ifndef bb392
#define bb392
#endif
#endif
#if defined( __MSDOS__) && ! defined( bb168)
#define bb168
#endif
#if defined( bb168) && ! defined( bb392)
#define bb507
#endif
#ifdef bb168
#define bb1043
#endif
#if ( defined( bb168) || defined( bb1196) || defined( WIN32)) && !  \
defined( bb136)
#define bb136
#endif
#if defined( __STDC__) || defined( __cplusplus) || defined( bb1221)
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
#define bb1111
#endif
#ifndef bb256
#ifdef bb507
#define bb256 8
#else
#define bb256 9
#endif
#endif
#ifndef bbp
#ifdef bb136
#define bbp( bb405) bb405
#else
#define bbp( bb405) ()
#endif
#endif
bba bbf bb154;bba bbs bbe bb7;bba bbs bb6 bb24;bba bb154 bb30;bba bbl
bb439;bba bbe bb1141;bba bb7 bb165;bba bb24 bb167;
#ifdef bb136
bba bbb*bb70;bba bbb*bb184;
#else
bba bb154*bb70;bba bb154*bb184;
#endif
#ifdef __cplusplus
bbr"\x43"{
#endif
bba bb70( *bb505)bbp((bb70 bb110,bb7 bb497,bb7 bb47));bba bbb( *bb504
)bbp((bb70 bb110,bb70 bb1139));bbi bb377;bba bbi bb1188{bb30*bb127;
bb7 bb148;bb24 bb188;bb30*bb580;bb7 bb383;bb24 bb612;bbl*bb324;bbi
bb377*bb23;bb505 bb401;bb504 bb370;bb70 bb110;bbe bb971;bb24 bb371;
bb24 bb1153;}bb440;bba bb440*bb17;bbr bbh bbl*bb1161 bbp((bbb));bbr
bbe bb508 bbp((bb17 bb16,bbe bb175));bbr bbe bb945 bbp((bb17 bb16));
bbr bbe bb1056 bbp((bb17 bb16,bbe bb175));bbr bbe bb954 bbp((bb17 bb16
));bbr bbe bb1178 bbp((bb17 bb16,bbh bb30*bb425,bb7 bb434));bbr bbe
bb1151 bbp((bb17 bb130,bb17 bb183));bbr bbe bb1058 bbp((bb17 bb16));
bbr bbe bb1176 bbp((bb17 bb16,bbe bb124,bbe bb301));bbr bbe bb1149 bbp
((bb17 bb16,bbh bb30*bb425,bb7 bb434));bbr bbe bb1150 bbp((bb17 bb16));
bbr bbe bb1011 bbp((bb17 bb16));bbr bbe bb1152 bbp((bb30*bb130,bb167*
bb312,bbh bb30*bb183,bb24 bb325));bbr bbe bb1148 bbp((bb30*bb130,
bb167*bb312,bbh bb30*bb183,bb24 bb325,bbe bb124));bbr bbe bb1163 bbp(
(bb30*bb130,bb167*bb312,bbh bb30*bb183,bb24 bb325));bba bb184 bb34;
bbr bb34 bb1208 bbp((bbh bbl*bb1013,bbh bbl*bb57));bbr bb34 bb1209 bbp
((bbe bb467,bbh bbl*bb57));bbr bbe bb1229 bbp((bb34 bb25,bbe bb124,
bbe bb301));bbr bbe bb1194 bbp((bb34 bb25,bb184 bb40,bbs bb22));bbr
bbe bb1189 bbp((bb34 bb25,bbh bb184 bb40,bbs bb22));bbr bbe bb1217 bbp
((bb34 bb25,bbh bbl*bb1228,...));bbr bbe bb1191 bbp((bb34 bb25,bbh bbl
 *bbg));bbr bbl*bb1182 bbp((bb34 bb25,bbl*bb40,bbe bb22));bbr bbe
bb1197 bbp((bb34 bb25,bbe bbo));bbr bbe bb1183 bbp((bb34 bb25));bbr
bbe bb1185 bbp((bb34 bb25,bbe bb175));bbr bb6 bb1200 bbp((bb34 bb25,
bb6 bb92,bbe bb1204));bbr bbe bb1181 bbp((bb34 bb25));bbr bb6 bb1192
bbp((bb34 bb25));bbr bbe bb1202 bbp((bb34 bb25));bbr bbe bb1205 bbp((
bb34 bb25));bbr bbh bbl*bb1186 bbp((bb34 bb25,bbe*bb1180));bbr bb24
bb986 bbp((bb24 bb371,bbh bb30*bb40,bb7 bb22));bbr bb24 bb1169 bbp((
bb24 bb378,bbh bb30*bb40,bb7 bb22));bbr bbe bb1112 bbp((bb17 bb16,bbe
bb124,bbh bbl*bb189,bbe bb197));bbr bbe bb1125 bbp((bb17 bb16,bbh bbl
 *bb189,bbe bb197));bbr bbe bb1048 bbp((bb17 bb16,bbe bb124,bbe bb565
,bbe bb447,bbe bb955,bbe bb301,bbh bbl*bb189,bbe bb197));bbr bbe
bb1051 bbp((bb17 bb16,bbe bb447,bbh bbl*bb189,bbe bb197));bbr bbh bbl
 *bb1155 bbp((bbe bb18));bbr bbe bb1175 bbp((bb17 bby));bbr bbh bb167
 *bb1165 bbp((bbb));
#ifdef __cplusplus
}
#endif
#define bb963 1
#ifdef bb136
#if defined( bb1742)
#else
#endif
#endif
bba bbs bbl bb155;bba bb155 bb1206;bba bbs bb135 bb126;bba bb126 bb501
;bba bbs bb6 bb393;bbr bbh bbl*bb1069[10 ];
#if bb256 >= 8
#define bb825 8
#else
#define bb825 bb256
#endif
#ifdef bb168
#define bb419 0x00
#if defined( __TURBOC__) || defined( __BORLANDC__)
#if( __STDC__ == 1) && ( defined( bb1792) || defined( bb1771))
bbb bb951 bb1315(bbb*bb101);bbb*bb951 bb1341(bbs bb6 bb1741);
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
#define bb419 0x0b
#endif
#if ( defined( _MSC_VER) && ( _MSC_VER > 600))
#define bb1753( bb467, bb131) bb1788( bb467, bb131)
#endif
#ifndef bb419
#define bb419 0x03
#endif
#if defined( bb1546) && ! defined( _MSC_VER) && ! defined( bb1773)
#define bb963
#endif
bba bb24( *bb942)bbp((bb24 bb480,bbh bb30*bb40,bb7 bb22));bb70 bb1168
bbp((bb70 bb110,bbs bb497,bbs bb47));bbb bb1162 bbp((bb70 bb110,bb70
bb912));bba bbi bb1954{bb557{bb126 bb429;bb126 bb172;}bb219;bb557{
bb126 bb2164;bb126 bb22;}bb48;}bb462;bba bbi bb2278 bb2006;bba bbi
bb1940{bb462*bb1749;bbe bb502;bb2006*bb1722;}bb1734;bba bb126 bb1037;
bba bb1037 bb1356;bba bbs bb1317;bba bbi bb377{bb17 bb16;bbe bb359;
bb30*bb171;bb393 bb2039;bb30*bb1875;bbe bb185;bbe bb1346;bb154 bb971;
bb154 bb565;bbe bb1894;bb7 bb933;bb7 bb2163;bb7 bb1807;bb30*bb158;
bb393 bb2227;bb1356*bb969;bb1356*bb385;bb7 bb495;bb7 bb1326;bb7 bb2130
;bb7 bb1382;bb7 bb1610;bb6 bb427;bb7 bb960;bb1317 bb2298;bbe bb1939;
bb7 bb182;bb7 bb2023;bb7 bb460;bb7 bb1264;bb7 bb2177;bb7 bb2055;bbe
bb124;bbe bb301;bb7 bb2182;bbe bb1837;bbi bb1954 bb972[(2 * (256 +1 +29 )+
1 )];bbi bb1954 bb1685[2 *30 +1 ];bbi bb1954 bb527[2 *19 +1 ];bbi bb1940
bb1936;bbi bb1940 bb1863;bbi bb1940 bb2062;bb126 bb1199[15 +1 ];bbe
bb519[2 * (256 +1 +29 )+1 ];bbe bb1503;bbe bb1944;bb155 bb1238[2 * (256 +1 +
29 )+1 ];bb1206*bb1725;bb7 bb1126;bb7 bb600;bb501*bb1648;bb393 bb1906;
bb393 bb2118;bb7 bb2231;bbe bb1993;bb126 bb99;bbe bb79;}bb192;bbb
bb2211 bbp((bb192*bbg));bbe bb2390 bbp((bb192*bbg,bbs bb414,bbs bb1138
));bbb bb1622 bbp((bb192*bbg,bb439*bb40,bb393 bb1340,bbe bb1109));bbb
bb2253 bbp((bb192*bbg));bbb bb2144 bbp((bb192*bbg,bb439*bb40,bb393
bb1340,bbe bb1109));bb41 bbh bbe bb2414[29 ]={0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,1 ,
2 ,2 ,2 ,2 ,3 ,3 ,3 ,3 ,4 ,4 ,4 ,4 ,5 ,5 ,5 ,5 ,0 };bb41 bbh bbe bb2380[30 ]={0 ,0 ,0 ,0 ,1
,1 ,2 ,2 ,3 ,3 ,4 ,4 ,5 ,5 ,6 ,6 ,7 ,7 ,8 ,8 ,9 ,9 ,10 ,10 ,11 ,11 ,12 ,12 ,13 ,13 };bb41 bbh
bbe bb2480[19 ]={0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,2 ,3 ,7 };bb41 bbh bb155
bb2199[19 ]={16 ,17 ,18 ,0 ,8 ,7 ,9 ,6 ,10 ,5 ,11 ,4 ,12 ,3 ,13 ,2 ,14 ,1 ,15 };bb41 bbh
bb462 bb1738[(256 +1 +29 )+2 ]={{{12 },{8 }},{{140 },{8 }},{{76 },{8 }},{{204 },
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
bb41 bbh bb462 bb2235[30 ]={{{0 },{5 }},{{16 },{5 }},{{8 },{5 }},{{24 },{5 }},
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
,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,27 ,28 };bb41 bbh bbe bb2333[29
]={0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,10 ,12 ,14 ,16 ,20 ,24 ,28 ,32 ,40 ,48 ,56 ,64 ,80 ,96 ,112 ,
128 ,160 ,192 ,224 ,0 };bb41 bbh bbe bb2416[30 ]={0 ,1 ,2 ,3 ,4 ,6 ,8 ,12 ,16 ,24 ,32
,48 ,64 ,96 ,128 ,192 ,256 ,384 ,512 ,768 ,1024 ,1536 ,2048 ,3072 ,4096 ,6144 ,8192 ,
12288 ,16384 ,24576 };bbi bb2278{bbh bb462*bb2345;bbh bb1141*bb2473;bbe
bb2454;bbe bb2176;bbe bb1941;};bb41 bb2006 bb2491={bb1738,bb2414,256 +
1 ,(256 +1 +29 ),15 };bb41 bb2006 bb2559={bb2235,bb2380,0 ,30 ,15 };bb41
bb2006 bb2498={(bbh bb462* )0 ,bb2480,0 ,19 ,7 };bb41 bbb bb2250 bbp((
bb192*bbg));bb41 bbb bb2168 bbp((bb192*bbg,bb462*bb307,bbe bb3));bb41
bbb bb2367 bbp((bb192*bbg,bb1734*bb1072));bb41 bbb bb2396 bbp((bb462*
bb307,bbe bb502,bb501*bb1199));bb41 bbb bb2186 bbp((bb192*bbg,bb1734*
bb1072));bb41 bbb bb2307 bbp((bb192*bbg,bb462*bb307,bbe bb502));bb41
bbb bb2232 bbp((bb192*bbg,bb462*bb307,bbe bb502));bb41 bbe bb2386 bbp
((bb192*bbg));bb41 bbb bb2409 bbp((bb192*bbg,bbe bb2051,bbe bb2093,
bbe bb2045));bb41 bbb bb2272 bbp((bb192*bbg,bb462*bb1053,bb462*bb1747
));bb41 bbb bb2314 bbp((bb192*bbg));bb41 bbs bb2374 bbp((bbs bb1324,
bbe bb464));bb41 bbb bb2259 bbp((bb192*bbg));bb41 bbb bb2303 bbp((
bb192*bbg));bb41 bbb bb2318 bbp((bb192*bbg,bb439*bb40,bbs bb22,bbe
bb985));bbb bb2211(bbg)bb192*bbg;{bbg->bb1936.bb1749=bbg->bb972;bbg->
bb1936.bb1722=&bb2491;bbg->bb1863.bb1749=bbg->bb1685;bbg->bb1863.
bb1722=&bb2559;bbg->bb2062.bb1749=bbg->bb527;bbg->bb2062.bb1722=&
bb2498;bbg->bb99=0 ;bbg->bb79=0 ;bbg->bb1993=8 ;bb2250(bbg);}bb41 bbb
bb2250(bbg)bb192*bbg;{bbe bb11;bb91(bb11=0 ;bb11<(256 +1 +29 );bb11++)bbg
->bb972[bb11].bb219.bb429=0 ;bb91(bb11=0 ;bb11<30 ;bb11++)bbg->bb1685[
bb11].bb219.bb429=0 ;bb91(bb11=0 ;bb11<19 ;bb11++)bbg->bb527[bb11].bb219
.bb429=0 ;bbg->bb972[256 ].bb219.bb429=1 ;bbg->bb1906=bbg->bb2118=0L ;bbg
->bb600=bbg->bb2231=0 ;}bb41 bbb bb2168(bbg,bb307,bb3)bb192*bbg;bb462*
bb307;bbe bb3;{bbe bb437=bbg->bb519[bb3];bbe bb76=bb3<<1 ;bb107(bb76<=
bbg->bb1503){bbm(bb76<bbg->bb1503&&(bb307[bbg->bb519[bb76+1 ]].bb219.
bb429<bb307[bbg->bb519[bb76]].bb219.bb429||(bb307[bbg->bb519[bb76+1 ]]
.bb219.bb429==bb307[bbg->bb519[bb76]].bb219.bb429&&bbg->bb1238[bbg->
bb519[bb76+1 ]]<=bbg->bb1238[bbg->bb519[bb76]]))){bb76++;}bbm((bb307[
bb437].bb219.bb429<bb307[bbg->bb519[bb76]].bb219.bb429||(bb307[bb437]
.bb219.bb429==bb307[bbg->bb519[bb76]].bb219.bb429&&bbg->bb1238[bb437]
<=bbg->bb1238[bbg->bb519[bb76]])))bb21;bbg->bb519[bb3]=bbg->bb519[
bb76];bb3=bb76;bb76<<=1 ;}bbg->bb519[bb3]=bb437;}bb41 bbb bb2367(bbg,
bb1072)bb192*bbg;bb1734*bb1072;{bb462*bb307=bb1072->bb1749;bbe bb502=
bb1072->bb502;bbh bb462*bb2116=bb1072->bb1722->bb2345;bbh bb1141*
bb1799=bb1072->bb1722->bb2473;bbe bb607=bb1072->bb1722->bb2454;bbe
bb1941=bb1072->bb1722->bb1941;bbe bb42;bbe bb11,bb96;bbe bb514;bbe
bb2145;bb126 bb19;bbe bb2140=0 ;bb91(bb514=0 ;bb514<=15 ;bb514++)bbg->
bb1199[bb514]=0 ;bb307[bbg->bb519[bbg->bb1944]].bb48.bb22=0 ;bb91(bb42=
bbg->bb1944+1 ;bb42<(2 * (256 +1 +29 )+1 );bb42++){bb11=bbg->bb519[bb42];
bb514=bb307[bb307[bb11].bb48.bb2164].bb48.bb22+1 ;bbm(bb514>bb1941)bb514
=bb1941,bb2140++;bb307[bb11].bb48.bb22=(bb126)bb514;bbm(bb11>bb502)bb1691
;bbg->bb1199[bb514]++;bb2145=0 ;bbm(bb11>=bb607)bb2145=bb1799[bb11-
bb607];bb19=bb307[bb11].bb219.bb429;bbg->bb1906+=(bb393)bb19* (bb514+
bb2145);bbm(bb2116)bbg->bb2118+=(bb393)bb19* (bb2116[bb11].bb48.bb22+
bb2145);}bbm(bb2140==0 )bb2;;bb574{bb514=bb1941-1 ;bb107(bbg->bb1199[
bb514]==0 )bb514--;bbg->bb1199[bb514]--;bbg->bb1199[bb514+1 ]+=2 ;bbg->
bb1199[bb1941]--;bb2140-=2 ;}bb107(bb2140>0 );bb91(bb514=bb1941;bb514!=
0 ;bb514--){bb11=bbg->bb1199[bb514];bb107(bb11!=0 ){bb96=bbg->bb519[--
bb42];bbm(bb96>bb502)bb1691;bbm(bb307[bb96].bb48.bb22!=(bbs)bb514){;
bbg->bb1906+=((bb6)bb514-(bb6)bb307[bb96].bb48.bb22) * (bb6)bb307[
bb96].bb219.bb429;bb307[bb96].bb48.bb22=(bb126)bb514;}bb11--;}}}bb41
bbb bb2396(bb307,bb502,bb1199)bb462*bb307;bbe bb502;bb501*bb1199;{
bb126 bb2404[15 +1 ];bb126 bb172=0 ;bbe bb514;bbe bb11;bb91(bb514=1 ;
bb514<=15 ;bb514++){bb2404[bb514]=bb172=(bb172+bb1199[bb514-1 ])<<1 ;};;
bb91(bb11=0 ;bb11<=bb502;bb11++){bbe bb22=bb307[bb11].bb48.bb22;bbm(
bb22==0 )bb1691;bb307[bb11].bb219.bb172=bb2374(bb2404[bb22]++,bb22);;}
}bb41 bbb bb2186(bbg,bb1072)bb192*bbg;bb1734*bb1072;{bb462*bb307=
bb1072->bb1749;bbh bb462*bb2116=bb1072->bb1722->bb2345;bbe bb2176=
bb1072->bb1722->bb2176;bbe bb11,bb96;bbe bb502=-1 ;bbe bb1776;bbg->
bb1503=0 ,bbg->bb1944=(2 * (256 +1 +29 )+1 );bb91(bb11=0 ;bb11<bb2176;bb11++
){bbm(bb307[bb11].bb219.bb429!=0 ){bbg->bb519[++(bbg->bb1503)]=bb502=
bb11;bbg->bb1238[bb11]=0 ;}bb54{bb307[bb11].bb48.bb22=0 ;}}bb107(bbg->
bb1503<2 ){bb1776=bbg->bb519[++(bbg->bb1503)]=(bb502<2 ?++bb502:0 );
bb307[bb1776].bb219.bb429=1 ;bbg->bb1238[bb1776]=0 ;bbg->bb1906--;bbm(
bb2116)bbg->bb2118-=bb2116[bb1776].bb48.bb22;}bb1072->bb502=bb502;
bb91(bb11=bbg->bb1503/2 ;bb11>=1 ;bb11--)bb2168(bbg,bb307,bb11);bb1776=
bb2176;bb574{{bb11=bbg->bb519[1 ];bbg->bb519[1 ]=bbg->bb519[bbg->bb1503
--];bb2168(bbg,bb307,1 );};bb96=bbg->bb519[1 ];bbg->bb519[--(bbg->
bb1944)]=bb11;bbg->bb519[--(bbg->bb1944)]=bb96;bb307[bb1776].bb219.
bb429=bb307[bb11].bb219.bb429+bb307[bb96].bb219.bb429;bbg->bb1238[
bb1776]=(bb155)((bbg->bb1238[bb11]>=bbg->bb1238[bb96]?bbg->bb1238[
bb11]:bbg->bb1238[bb96])+1 );bb307[bb11].bb48.bb2164=bb307[bb96].bb48.
bb2164=(bb126)bb1776;bbg->bb519[1 ]=bb1776++;bb2168(bbg,bb307,1 );}
bb107(bbg->bb1503>=2 );bbg->bb519[--(bbg->bb1944)]=bbg->bb519[1 ];
bb2367(bbg,(bb1734* )bb1072);bb2396((bb462* )bb307,bb502,bbg->bb1199);
}bb41 bbb bb2307(bbg,bb307,bb502)bb192*bbg;bb462*bb307;bbe bb502;{bbe
bb11;bbe bb2085=-1 ;bbe bb628;bbe bb1216=bb307[0 ].bb48.bb22;bbe bb970=
0 ;bbe bb1337=7 ;bbe bb1300=4 ;bbm(bb1216==0 )bb1337=138 ,bb1300=3 ;bb307[
bb502+1 ].bb48.bb22=(bb126)0xffff ;bb91(bb11=0 ;bb11<=bb502;bb11++){
bb628=bb1216;bb1216=bb307[bb11+1 ].bb48.bb22;bbm(++bb970<bb1337&&bb628
==bb1216){bb1691;}bb54 bbm(bb970<bb1300){bbg->bb527[bb628].bb219.
bb429+=bb970;}bb54 bbm(bb628!=0 ){bbm(bb628!=bb2085)bbg->bb527[bb628].
bb219.bb429++;bbg->bb527[16 ].bb219.bb429++;}bb54 bbm(bb970<=10 ){bbg->
bb527[17 ].bb219.bb429++;}bb54{bbg->bb527[18 ].bb219.bb429++;}bb970=0 ;
bb2085=bb628;bbm(bb1216==0 ){bb1337=138 ,bb1300=3 ;}bb54 bbm(bb628==
bb1216){bb1337=6 ,bb1300=3 ;}bb54{bb1337=7 ,bb1300=4 ;}}}bb41 bbb bb2232(
bbg,bb307,bb502)bb192*bbg;bb462*bb307;bbe bb502;{bbe bb11;bbe bb2085=
-1 ;bbe bb628;bbe bb1216=bb307[0 ].bb48.bb22;bbe bb970=0 ;bbe bb1337=7 ;
bbe bb1300=4 ;bbm(bb1216==0 )bb1337=138 ,bb1300=3 ;bb91(bb11=0 ;bb11<=
bb502;bb11++){bb628=bb1216;bb1216=bb307[bb11+1 ].bb48.bb22;bbm(++bb970
<bb1337&&bb628==bb1216){bb1691;}bb54 bbm(bb970<bb1300){bb574{{bbe bb22
=bbg->bb527[bb628].bb48.bb22;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-bb22){
bbe bb170=bbg->bb527[bb628].bb219.bb172;bbg->bb99|=(bb170<<bbg->bb79);
{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));};{bbg->bb171[
bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(bb126)bb170
>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}
bb54{bbg->bb99|=(bbg->bb527[bb628].bb219.bb172)<<bbg->bb79;bbg->bb79
+=bb22;}};}bb107(--bb970!=0 );}bb54 bbm(bb628!=0 ){bbm(bb628!=bb2085){{
bbe bb22=bbg->bb527[bb628].bb48.bb22;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl
))-bb22){bbe bb170=bbg->bb527[bb628].bb219.bb172;bbg->bb99|=(bb170<<
bbg->bb79);{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));};{
bbg->bb171[bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->
bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(
8 *2 *bb12(bbl));}bb54{bbg->bb99|=(bbg->bb527[bb628].bb219.bb172)<<bbg
->bb79;bbg->bb79+=bb22;}};bb970--;};{bbe bb22=bbg->bb527[16 ].bb48.
bb22;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=bbg->bb527[16
].bb219.bb172;bbg->bb99|=(bb170<<bbg->bb79);{{bbg->bb171[bbg->bb185++
]=((bb155)((bbg->bb99)&0xff ));};{bbg->bb171[bbg->bb185++]=((bb155)((
bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(
bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}bb54{bbg->bb99|=(
bbg->bb527[16 ].bb219.bb172)<<bbg->bb79;bbg->bb79+=bb22;}};{bbe bb22=2
;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=bb970-3 ;bbg->bb99
|=(bb170<<bbg->bb79);{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&
0xff ));};{bbg->bb171[bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));}
;};bbg->bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79
+=bb22-(8 *2 *bb12(bbl));}bb54{bbg->bb99|=(bb970-3 )<<bbg->bb79;bbg->
bb79+=bb22;}};}bb54 bbm(bb970<=10 ){{bbe bb22=bbg->bb527[17 ].bb48.bb22
;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=bbg->bb527[17 ].
bb219.bb172;bbg->bb99|=(bb170<<bbg->bb79);{{bbg->bb171[bbg->bb185++]=
((bb155)((bbg->bb99)&0xff ));};{bbg->bb171[bbg->bb185++]=((bb155)((
bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(
bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}bb54{bbg->bb99|=(
bbg->bb527[17 ].bb219.bb172)<<bbg->bb79;bbg->bb79+=bb22;}};{bbe bb22=3
;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=bb970-3 ;bbg->bb99
|=(bb170<<bbg->bb79);{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&
0xff ));};{bbg->bb171[bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));}
;};bbg->bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79
+=bb22-(8 *2 *bb12(bbl));}bb54{bbg->bb99|=(bb970-3 )<<bbg->bb79;bbg->
bb79+=bb22;}};}bb54{{bbe bb22=bbg->bb527[18 ].bb48.bb22;bbm(bbg->bb79>
(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=bbg->bb527[18 ].bb219.bb172;bbg->
bb99|=(bb170<<bbg->bb79);{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->
bb99)&0xff ));};{bbg->bb171[bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>
8 ));};};bbg->bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg
->bb79+=bb22-(8 *2 *bb12(bbl));}bb54{bbg->bb99|=(bbg->bb527[18 ].bb219.
bb172)<<bbg->bb79;bbg->bb79+=bb22;}};{bbe bb22=7 ;bbm(bbg->bb79>(bbe)(
8 *2 *bb12(bbl))-bb22){bbe bb170=bb970-11 ;bbg->bb99|=(bb170<<bbg->bb79);
{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));};{bbg->bb171[
bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(bb126)bb170
>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}
bb54{bbg->bb99|=(bb970-11 )<<bbg->bb79;bbg->bb79+=bb22;}};}bb970=0 ;
bb2085=bb628;bbm(bb1216==0 ){bb1337=138 ,bb1300=3 ;}bb54 bbm(bb628==
bb1216){bb1337=6 ,bb1300=3 ;}bb54{bb1337=7 ,bb1300=4 ;}}}bb41 bbe bb2386(
bbg)bb192*bbg;{bbe bb1784;bb2307(bbg,(bb462* )bbg->bb972,bbg->bb1936.
bb502);bb2307(bbg,(bb462* )bbg->bb1685,bbg->bb1863.bb502);bb2186(bbg,
(bb1734* )(&(bbg->bb2062)));bb91(bb1784=19 -1 ;bb1784>=3 ;bb1784--){bbm(
bbg->bb527[bb2199[bb1784]].bb48.bb22!=0 )bb21;}bbg->bb1906+=3 * (bb1784
+1 )+5 +5 +4 ;;bb2 bb1784;}bb41 bbb bb2409(bbg,bb2051,bb2093,bb2045)bb192
 *bbg;bbe bb2051,bb2093,bb2045;{bbe bb2122;;;;{bbe bb22=5 ;bbm(bbg->
bb79>(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=bb2051-257 ;bbg->bb99|=(
bb170<<bbg->bb79);{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&
0xff ));};{bbg->bb171[bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));}
;};bbg->bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79
+=bb22-(8 *2 *bb12(bbl));}bb54{bbg->bb99|=(bb2051-257 )<<bbg->bb79;bbg->
bb79+=bb22;}};{bbe bb22=5 ;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-bb22){
bbe bb170=bb2093-1 ;bbg->bb99|=(bb170<<bbg->bb79);{{bbg->bb171[bbg->
bb185++]=((bb155)((bbg->bb99)&0xff ));};{bbg->bb171[bbg->bb185++]=((
bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(bb126)bb170>>((bbe)(8 *2
 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}bb54{bbg->
bb99|=(bb2093-1 )<<bbg->bb79;bbg->bb79+=bb22;}};{bbe bb22=4 ;bbm(bbg->
bb79>(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=bb2045-4 ;bbg->bb99|=(bb170
<<bbg->bb79);{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));}
;{bbg->bb171[bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->
bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(
8 *2 *bb12(bbl));}bb54{bbg->bb99|=(bb2045-4 )<<bbg->bb79;bbg->bb79+=bb22
;}};bb91(bb2122=0 ;bb2122<bb2045;bb2122++){;{bbe bb22=3 ;bbm(bbg->bb79>
(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=bbg->bb527[bb2199[bb2122]].bb48.
bb22;bbg->bb99|=(bb170<<bbg->bb79);{{bbg->bb171[bbg->bb185++]=((bb155
)((bbg->bb99)&0xff ));};{bbg->bb171[bbg->bb185++]=((bb155)((bb126)(bbg
->bb99)>>8 ));};};bbg->bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(bbl))-bbg->
bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}bb54{bbg->bb99|=(bbg->bb527[
bb2199[bb2122]].bb48.bb22)<<bbg->bb79;bbg->bb79+=bb22;}};};bb2232(bbg
,(bb462* )bbg->bb972,bb2051-1 );;bb2232(bbg,(bb462* )bbg->bb1685,
bb2093-1 );;}bbb bb2144(bbg,bb40,bb1340,bb1109)bb192*bbg;bb439*bb40;
bb393 bb1340;bbe bb1109;{{bbe bb22=3 ;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl
))-bb22){bbe bb170=(0 <<1 )+bb1109;bbg->bb99|=(bb170<<bbg->bb79);{{bbg
->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));};{bbg->bb171[bbg->
bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(bb126)bb170
>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}
bb54{bbg->bb99|=((0 <<1 )+bb1109)<<bbg->bb79;bbg->bb79+=bb22;}};bb2318(
bbg,bb40,(bbs)bb1340,1 );}bbb bb2253(bbg)bb192*bbg;{{bbe bb22=3 ;bbm(
bbg->bb79>(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=1 <<1 ;bbg->bb99|=(bb170
<<bbg->bb79);{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));}
;{bbg->bb171[bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->
bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(
8 *2 *bb12(bbl));}bb54{bbg->bb99|=(1 <<1 )<<bbg->bb79;bbg->bb79+=bb22;}};
{bbe bb22=bb1738[256 ].bb48.bb22;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-
bb22){bbe bb170=bb1738[256 ].bb219.bb172;bbg->bb99|=(bb170<<bbg->bb79);
{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));};{bbg->bb171[
bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(bb126)bb170
>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}
bb54{bbg->bb99|=(bb1738[256 ].bb219.bb172)<<bbg->bb79;bbg->bb79+=bb22;
}};bb2303(bbg);bbm(1 +bbg->bb1993+10 -bbg->bb79<9 ){{bbe bb22=3 ;bbm(bbg
->bb79>(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=1 <<1 ;bbg->bb99|=(bb170<<
bbg->bb79);{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));};{
bbg->bb171[bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->
bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(
8 *2 *bb12(bbl));}bb54{bbg->bb99|=(1 <<1 )<<bbg->bb79;bbg->bb79+=bb22;}};
{bbe bb22=bb1738[256 ].bb48.bb22;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-
bb22){bbe bb170=bb1738[256 ].bb219.bb172;bbg->bb99|=(bb170<<bbg->bb79);
{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));};{bbg->bb171[
bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(bb126)bb170
>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}
bb54{bbg->bb99|=(bb1738[256 ].bb219.bb172)<<bbg->bb79;bbg->bb79+=bb22;
}};bb2303(bbg);}bbg->bb1993=7 ;}bbb bb1622(bbg,bb40,bb1340,bb1109)bb192
 *bbg;bb439*bb40;bb393 bb1340;bbe bb1109;{bb393 bb2013,bb2078;bbe
bb1784=0 ;bbm(bbg->bb124>0 ){bbm(bbg->bb971==2 )bb2314(bbg);bb2186(bbg,(
bb1734* )(&(bbg->bb1936)));;bb2186(bbg,(bb1734* )(&(bbg->bb1863)));;
bb1784=bb2386(bbg);bb2013=(bbg->bb1906+3 +7 )>>3 ;bb2078=(bbg->bb2118+3 +
7 )>>3 ;;bbm(bb2078<=bb2013)bb2013=bb2078;}bb54{;bb2013=bb2078=bb1340+5
;}bbm(bb1340+4 <=bb2013&&bb40!=(bbl* )0 ){bb2144(bbg,bb40,bb1340,bb1109
);}bb54 bbm(bb2078==bb2013){{bbe bb22=3 ;bbm(bbg->bb79>(bbe)(8 *2 *bb12(
bbl))-bb22){bbe bb170=(1 <<1 )+bb1109;bbg->bb99|=(bb170<<bbg->bb79);{{
bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));};{bbg->bb171[
bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(bb126)bb170
>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}
bb54{bbg->bb99|=((1 <<1 )+bb1109)<<bbg->bb79;bbg->bb79+=bb22;}};bb2272(
bbg,(bb462* )bb1738,(bb462* )bb2235);}bb54{{bbe bb22=3 ;bbm(bbg->bb79>
(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=(2 <<1 )+bb1109;bbg->bb99|=(bb170
<<bbg->bb79);{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));}
;{bbg->bb171[bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->
bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(
8 *2 *bb12(bbl));}bb54{bbg->bb99|=((2 <<1 )+bb1109)<<bbg->bb79;bbg->bb79
+=bb22;}};bb2409(bbg,bbg->bb1936.bb502+1 ,bbg->bb1863.bb502+1 ,bb1784+1
);bb2272(bbg,(bb462* )bbg->bb972,(bb462* )bbg->bb1685);};bb2250(bbg);
bbm(bb1109){bb2259(bbg);};}bbe bb2390(bbg,bb414,bb1138)bb192*bbg;bbs
bb414;bbs bb1138;{bbg->bb1648[bbg->bb600]=(bb126)bb414;bbg->bb1725[
bbg->bb600++]=(bb155)bb1138;bbm(bb414==0 ){bbg->bb972[bb1138].bb219.
bb429++;}bb54{bbg->bb2231++;bb414--;;bbg->bb972[bb2052[bb1138]+256 +1 ]
.bb219.bb429++;bbg->bb1685[((bb414)<256 ?bb1735[bb414]:bb1735[256 +((
bb414)>>7 )])].bb219.bb429++;}bb2(bbg->bb600==bbg->bb1126-1 );}bb41 bbb
bb2272(bbg,bb1053,bb1747)bb192*bbg;bb462*bb1053;bb462*bb1747;{bbs
bb414;bbe bb1138;bbs bb2288=0 ;bbs bb172;bbe bb1799;bbm(bbg->bb600!=0 )bb574
{bb414=bbg->bb1648[bb2288];bb1138=bbg->bb1725[bb2288++];bbm(bb414==0 ){
{bbe bb22=bb1053[bb1138].bb48.bb22;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-
bb22){bbe bb170=bb1053[bb1138].bb219.bb172;bbg->bb99|=(bb170<<bbg->
bb79);{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));};{bbg->
bb171[bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(
bb126)bb170>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *
bb12(bbl));}bb54{bbg->bb99|=(bb1053[bb1138].bb219.bb172)<<bbg->bb79;
bbg->bb79+=bb22;}};;}bb54{bb172=bb2052[bb1138];{bbe bb22=bb1053[bb172
+256 +1 ].bb48.bb22;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=
bb1053[bb172+256 +1 ].bb219.bb172;bbg->bb99|=(bb170<<bbg->bb79);{{bbg->
bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));};{bbg->bb171[bbg->
bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(bb126)bb170
>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}
bb54{bbg->bb99|=(bb1053[bb172+256 +1 ].bb219.bb172)<<bbg->bb79;bbg->
bb79+=bb22;}};bb1799=bb2414[bb172];bbm(bb1799!=0 ){bb1138-=bb2333[
bb172];{bbe bb22=bb1799;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-bb22){bbe
bb170=bb1138;bbg->bb99|=(bb170<<bbg->bb79);{{bbg->bb171[bbg->bb185++]
=((bb155)((bbg->bb99)&0xff ));};{bbg->bb171[bbg->bb185++]=((bb155)((
bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(
bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}bb54{bbg->bb99|=(
bb1138)<<bbg->bb79;bbg->bb79+=bb22;}};}bb414--;bb172=((bb414)<256 ?
bb1735[bb414]:bb1735[256 +((bb414)>>7 )]);;{bbe bb22=bb1747[bb172].bb48
.bb22;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=bb1747[bb172
].bb219.bb172;bbg->bb99|=(bb170<<bbg->bb79);{{bbg->bb171[bbg->bb185++
]=((bb155)((bbg->bb99)&0xff ));};{bbg->bb171[bbg->bb185++]=((bb155)((
bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(
bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}bb54{bbg->bb99|=(
bb1747[bb172].bb219.bb172)<<bbg->bb79;bbg->bb79+=bb22;}};bb1799=
bb2380[bb172];bbm(bb1799!=0 ){bb414-=bb2416[bb172];{bbe bb22=bb1799;
bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=bb414;bbg->bb99|=(
bb170<<bbg->bb79);{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&
0xff ));};{bbg->bb171[bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));}
;};bbg->bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(bbl))-bbg->bb79);bbg->bb79
+=bb22-(8 *2 *bb12(bbl));}bb54{bbg->bb99|=(bb414)<<bbg->bb79;bbg->bb79
+=bb22;}};}};}bb107(bb2288<bbg->bb600);{bbe bb22=bb1053[256 ].bb48.
bb22;bbm(bbg->bb79>(bbe)(8 *2 *bb12(bbl))-bb22){bbe bb170=bb1053[256 ].
bb219.bb172;bbg->bb99|=(bb170<<bbg->bb79);{{bbg->bb171[bbg->bb185++]=
((bb155)((bbg->bb99)&0xff ));};{bbg->bb171[bbg->bb185++]=((bb155)((
bb126)(bbg->bb99)>>8 ));};};bbg->bb99=(bb126)bb170>>((bbe)(8 *2 *bb12(
bbl))-bbg->bb79);bbg->bb79+=bb22-(8 *2 *bb12(bbl));}bb54{bbg->bb99|=(
bb1053[256 ].bb219.bb172)<<bbg->bb79;bbg->bb79+=bb22;}};bbg->bb1993=
bb1053[256 ].bb48.bb22;}bb41 bbb bb2314(bbg)bb192*bbg;{bbe bb11=0 ;bbs
bb2327=0 ;bbs bb2269=0 ;bb107(bb11<7 )bb2269+=bbg->bb972[bb11++].bb219.
bb429;bb107(bb11<128 )bb2327+=bbg->bb972[bb11++].bb219.bb429;bb107(
bb11<256 )bb2269+=bbg->bb972[bb11++].bb219.bb429;bbg->bb971=(bb154)(
bb2269>(bb2327>>2 )?0 :1 );}bb41 bbs bb2374(bb172,bb22)bbs bb172;bbe bb22
;{bb931 bbs bb2305=0 ;bb574{bb2305|=bb172&1 ;bb172>>=1 ,bb2305<<=1 ;}
bb107(--bb22>0 );bb2 bb2305>>1 ;}bb41 bbb bb2303(bbg)bb192*bbg;{bbm(bbg
->bb79==16 ){{{bbg->bb171[bbg->bb185++]=((bb155)((bbg->bb99)&0xff ));};
{bbg->bb171[bbg->bb185++]=((bb155)((bb126)(bbg->bb99)>>8 ));};};bbg->
bb99=0 ;bbg->bb79=0 ;}bb54 bbm(bbg->bb79>=8 ){{bbg->bb171[bbg->bb185++]=
((bb154)bbg->bb99);};bbg->bb99>>=8 ;bbg->bb79-=8 ;}}bb41 bbb bb2259(bbg
)bb192*bbg;{bbm(bbg->bb79>8 ){{{bbg->bb171[bbg->bb185++]=((bb155)((bbg
->bb99)&0xff ));};{bbg->bb171[bbg->bb185++]=((bb155)((bb126)(bbg->bb99
)>>8 ));};};}bb54 bbm(bbg->bb79>0 ){{bbg->bb171[bbg->bb185++]=((bb154)bbg
->bb99);};}bbg->bb99=0 ;bbg->bb79=0 ;}bb41 bbb bb2318(bbg,bb40,bb22,
bb985)bb192*bbg;bb439*bb40;bbs bb22;bbe bb985;{bb2259(bbg);bbg->
bb1993=8 ;bbm(bb985){{{bbg->bb171[bbg->bb185++]=((bb155)(((bb126)bb22)&
0xff ));};{bbg->bb171[bbg->bb185++]=((bb155)((bb126)((bb126)bb22)>>8 ));
};};{{bbg->bb171[bbg->bb185++]=((bb155)(((bb126)~bb22)&0xff ));};{bbg
->bb171[bbg->bb185++]=((bb155)((bb126)((bb126)~bb22)>>8 ));};};}bb107(
bb22--){{bbg->bb171[bbg->bb185++]=( *bb40++);};}}
