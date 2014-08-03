/*
   'src_compress_deflate_deflate.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Wed Jan 15 12:08:55 2014
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
bb1340,bbe bb1109));bb41 bbh bb462 bb1738[(256 +1 +29 )+2 ]={{{12 },{8 }},{
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
163 },{8 }},{{99 },{8 }},{{227 },{8 }}};bb41 bbh bb462 bb2235[30 ]={{{0 },{5 }
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
27 ,27 ,27 ,27 ,28 };bb41 bbh bbe bb2333[29 ]={0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,10 ,12 ,14 ,
16 ,20 ,24 ,28 ,32 ,40 ,48 ,56 ,64 ,80 ,96 ,112 ,128 ,160 ,192 ,224 ,0 };bb41 bbh bbe
bb2416[30 ]={0 ,1 ,2 ,3 ,4 ,6 ,8 ,12 ,16 ,24 ,32 ,48 ,64 ,96 ,128 ,192 ,256 ,384 ,512 ,
768 ,1024 ,1536 ,2048 ,3072 ,4096 ,6144 ,8192 ,12288 ,16384 ,24576 };bba bb10{
bb1283,bb2159,bb1757,bb2141}bb1822;bba bb1822( *bb2387)bbp((bb192*bbg
,bbe bb175));bb41 bbb bb2191 bbp((bb192*bbg));bb41 bb1822 bb2381 bbp(
(bb192*bbg,bbe bb175));bb41 bb1822 bb2162 bbp((bb192*bbg,bbe bb175));
bb41 bb1822 bb1946 bbp((bb192*bbg,bbe bb175));bb41 bbb bb2429 bbp((
bb192*bbg));bb41 bbb bb2008 bbp((bb192*bbg,bb7 bbn));bb41 bbb bb1267
bbp((bb17 bb16));bb41 bbe bb2434 bbp((bb17 bb16,bb30*bb40,bbs bb47));
bb41 bb7 bb2258 bbp((bb192*bbg,bb1317 bb1994));bba bbi bb2626{bb126
bb2430;bb126 bb2438;bb126 bb2384;bb126 bb2348;bb2387 bb2021;}bb2513;
bb41 bbh bb2513 bb1335[10 ]={{0 ,0 ,0 ,0 ,bb2381},{4 ,4 ,8 ,4 ,bb2162},{4 ,5 ,16
,8 ,bb2162},{4 ,6 ,32 ,32 ,bb2162},{4 ,4 ,16 ,16 ,bb1946},{8 ,16 ,32 ,32 ,bb1946},
{8 ,16 ,128 ,128 ,bb1946},{8 ,32 ,128 ,256 ,bb1946},{32 ,128 ,258 ,1024 ,bb1946},
{32 ,258 ,258 ,4096 ,bb1946}};bbi bb2278{bbe bb444;};bbe bb1112(bb16,
bb124,bb189,bb197)bb17 bb16;bbe bb124;bbh bbl*bb189;bbe bb197;{bb2
bb1048(bb16,bb124,8 ,15 ,bb825,0 ,bb189,bb197);}bbe bb1048(bb16,bb124,
bb565,bb447,bb955,bb301,bb189,bb197)bb17 bb16;bbe bb124;bbe bb565;bbe
bb447;bbe bb955;bbe bb301;bbh bbl*bb189;bbe bb197;{bb192*bbg;bbe
bb1346=0 ;bb41 bbh bbl*bb2443="\x31\x2e\x31\x2e\x33";bb501*bb1883;bbm(
bb189==0 ||bb189[0 ]!=bb2443[0 ]||bb197!=bb12(bb440)){bb2(-6 );}bbm(bb16
==0 )bb2(-2 );bb16->bb324=0 ;bbm(bb16->bb401==0 ){bb16->bb401=bb1168;bb16
->bb110=(bb70)0 ;}bbm(bb16->bb370==0 )bb16->bb370=bb1162;bbm(bb124==(-1
))bb124=6 ;bbm(bb447<0 ){bb1346=1 ;bb447=-bb447;}bbm(bb955<1 ||bb955>
bb256||bb565!=8 ||bb447<8 ||bb447>15 ||bb124<0 ||bb124>9 ||bb301<0 ||bb301>
2 ){bb2(-2 );}bbg=(bb192* )( * ((bb16)->bb401))((bb16)->bb110,(1 ),(bb12
(bb192)));bbm(bbg==0 )bb2(-4 );bb16->bb23=(bbi bb377* )bbg;bbg->bb16=
bb16;bbg->bb1346=bb1346;bbg->bb2163=bb447;bbg->bb933=1 <<bbg->bb2163;
bbg->bb1807=bbg->bb933-1 ;bbg->bb2130=bb955+7 ;bbg->bb1326=1 <<bbg->
bb2130;bbg->bb1382=bbg->bb1326-1 ;bbg->bb1610=((bbg->bb2130+3 -1 )/3 );
bbg->bb158=(bb30* )( * ((bb16)->bb401))((bb16)->bb110,(bbg->bb933),(2
 *bb12(bb154)));bbg->bb969=(bb1356* )( * ((bb16)->bb401))((bb16)->
bb110,(bbg->bb933),(bb12(bb1037)));bbg->bb385=(bb1356* )( * ((bb16)->
bb401))((bb16)->bb110,(bbg->bb1326),(bb12(bb1037)));bbg->bb1126=1 <<(
bb955+6 );bb1883=(bb501* )( * ((bb16)->bb401))((bb16)->bb110,(bbg->
bb1126),(bb12(bb126)+2 ));bbg->bb171=(bb1206* )bb1883;bbg->bb2039=(
bb393)bbg->bb1126* (bb12(bb126)+2L );bbm(bbg->bb158==0 ||bbg->bb969==0
||bbg->bb385==0 ||bbg->bb171==0 ){bb16->bb324=(bbl* )bb1069[2 -((-4 ))];
bb945(bb16);bb2(-4 );}bbg->bb1648=bb1883+bbg->bb1126/bb12(bb126);bbg->
bb1725=bbg->bb171+(1 +bb12(bb126)) *bbg->bb1126;bbg->bb124=bb124;bbg->
bb301=bb301;bbg->bb565=(bb154)bb565;bb2 bb1058(bb16);}bbe bb1178(bb16
,bb425,bb434)bb17 bb16;bbh bb30*bb425;bb7 bb434;{bb192*bbg;bb7 bb464=
bb434;bb7 bb11;bb1317 bb1131=0 ;bbm(bb16==0 ||bb16->bb23==0 ||bb425==0 ||
bb16->bb23->bb359!=42 )bb2(-2 );bbg=bb16->bb23;bb16->bb371=bb986(bb16->
bb371,bb425,bb434);bbm(bb464<3 )bb2 0 ;bbm(bb464>((bbg)->bb933-(258 +3 +1
))){bb464=((bbg)->bb933-(258 +3 +1 ));bb425+=bb434-bb464;}bb81(bbg->
bb158,bb425,bb464);bbg->bb182=bb464;bbg->bb427=(bb6)bb464;bbg->bb495=
bbg->bb158[0 ];(bbg->bb495=(((bbg->bb495)<<bbg->bb1610)^(bbg->bb158[1 ]
))&bbg->bb1382);bb91(bb11=0 ;bb11<=bb464-3 ;bb11++){((bbg->bb495=(((bbg
->bb495)<<bbg->bb1610)^(bbg->bb158[(bb11)+(3 -1 )]))&bbg->bb1382),bbg->
bb969[(bb11)&bbg->bb1807]=bb1131=bbg->bb385[bbg->bb495],bbg->bb385[
bbg->bb495]=(bb1037)(bb11));}bbm(bb1131)bb1131=0 ;bb2 0 ;}bbe bb1058(
bb16)bb17 bb16;{bb192*bbg;bbm(bb16==0 ||bb16->bb23==0 ||bb16->bb401==0
||bb16->bb370==0 )bb2(-2 );bb16->bb188=bb16->bb612=0 ;bb16->bb324=0 ;bb16
->bb971=2 ;bbg=(bb192* )bb16->bb23;bbg->bb185=0 ;bbg->bb1875=bbg->bb171
;bbm(bbg->bb1346<0 ){bbg->bb1346=0 ;}bbg->bb359=bbg->bb1346?113 :42 ;bb16
->bb371=1 ;bbg->bb1894=0 ;bb2211(bbg);bb2429(bbg);bb2 0 ;}bbe bb1176(
bb16,bb124,bb301)bb17 bb16;bbe bb124;bbe bb301;{bb192*bbg;bb2387
bb2021;bbe bb18=0 ;bbm(bb16==0 ||bb16->bb23==0 )bb2(-2 );bbg=bb16->bb23;
bbm(bb124==(-1 )){bb124=6 ;}bbm(bb124<0 ||bb124>9 ||bb301<0 ||bb301>2 ){bb2
(-2 );}bb2021=bb1335[bbg->bb124].bb2021;bbm(bb2021!=bb1335[bb124].
bb2021&&bb16->bb188!=0 ){bb18=bb508(bb16,1 );}bbm(bbg->bb124!=bb124){
bbg->bb124=bb124;bbg->bb2055=bb1335[bb124].bb2438;bbg->bb2182=bb1335[
bb124].bb2430;bbg->bb1837=bb1335[bb124].bb2384;bbg->bb2177=bb1335[
bb124].bb2348;}bbg->bb301=bb301;bb2 bb18;}bb41 bbb bb2008(bbg,bbn)bb192
 *bbg;bb7 bbn;{{bbg->bb171[bbg->bb185++]=((bb154)(bbn>>8 ));};{bbg->
bb171[bbg->bb185++]=((bb154)(bbn&0xff ));};}bb41 bbb bb1267(bb16)bb17
bb16;{bbs bb22=bb16->bb23->bb185;bbm(bb22>bb16->bb383)bb22=bb16->
bb383;bbm(bb22==0 )bb2;bb81(bb16->bb580,bb16->bb23->bb1875,bb22);bb16
->bb580+=bb22;bb16->bb23->bb1875+=bb22;bb16->bb612+=bb22;bb16->bb383
-=bb22;bb16->bb23->bb185-=bb22;bbm(bb16->bb23->bb185==0 ){bb16->bb23->
bb1875=bb16->bb23->bb171;}}bbe bb508(bb16,bb175)bb17 bb16;bbe bb175;{
bbe bb2344;bb192*bbg;bbm(bb16==0 ||bb16->bb23==0 ||bb175>4 ||bb175<0 ){
bb2(-2 );}bbg=bb16->bb23;bbm(bb16->bb580==0 ||(bb16->bb127==0 &&bb16->
bb148!=0 )||(bbg->bb359==666 &&bb175!=4 )){bb2(bb16->bb324=(bbl* )bb1069
[2 -((-2 ))],((-2 )));}bbm(bb16->bb383==0 )bb2(bb16->bb324=(bbl* )bb1069[
2 -((-5 ))],((-5 )));bbg->bb16=bb16;bb2344=bbg->bb1894;bbg->bb1894=bb175
;bbm(bbg->bb359==42 ){bb7 bb985=(8 +((bbg->bb2163-8 )<<4 ))<<8 ;bb7 bb2299
=(bbg->bb124-1 )>>1 ;bbm(bb2299>3 )bb2299=3 ;bb985|=(bb2299<<6 );bbm(bbg->
bb182!=0 )bb985|=0x20 ;bb985+=31 -(bb985%31 );bbg->bb359=113 ;bb2008(bbg,
bb985);bbm(bbg->bb182!=0 ){bb2008(bbg,(bb7)(bb16->bb371>>16 ));bb2008(
bbg,(bb7)(bb16->bb371&0xffff ));}bb16->bb371=1L ;}bbm(bbg->bb185!=0 ){
bb1267(bb16);bbm(bb16->bb383==0 ){bbg->bb1894=-1 ;bb2 0 ;}}bb54 bbm(bb16
->bb148==0 &&bb175<=bb2344&&bb175!=4 ){bb2(bb16->bb324=(bbl* )bb1069[2 -
((-5 ))],((-5 )));}bbm(bbg->bb359==666 &&bb16->bb148!=0 ){bb2(bb16->bb324
=(bbl* )bb1069[2 -((-5 ))],((-5 )));}bbm(bb16->bb148!=0 ||bbg->bb460!=0 ||
(bb175!=0 &&bbg->bb359!=666 )){bb1822 bb1986;bb1986=( * (bb1335[bbg->
bb124].bb2021))(bbg,bb175);bbm(bb1986==bb1757||bb1986==bb2141){bbg->
bb359=666 ;}bbm(bb1986==bb1283||bb1986==bb1757){bbm(bb16->bb383==0 ){
bbg->bb1894=-1 ;}bb2 0 ;}bbm(bb1986==bb2159){bbm(bb175==1 ){bb2253(bbg);
}bb54{bb2144(bbg,(bbl* )0 ,0L ,0 );bbm(bb175==3 ){bbg->bb385[bbg->bb1326-
1 ]=0 ;bb997((bb30* )bbg->bb385,0 ,(bbs)(bbg->bb1326-1 ) *bb12( *bbg->
bb385));;}}bb1267(bb16);bbm(bb16->bb383==0 ){bbg->bb1894=-1 ;bb2 0 ;}}};
bbm(bb175!=4 )bb2 0 ;bbm(bbg->bb1346)bb2 1 ;bb2008(bbg,(bb7)(bb16->bb371
>>16 ));bb2008(bbg,(bb7)(bb16->bb371&0xffff ));bb1267(bb16);bbg->bb1346
=-1 ;bb2 bbg->bb185!=0 ?0 :1 ;}bbe bb945(bb16)bb17 bb16;{bbe bb359;bbm(
bb16==0 ||bb16->bb23==0 )bb2(-2 );bb359=bb16->bb23->bb359;bbm(bb359!=42
&&bb359!=113 &&bb359!=666 ){bb2(-2 );}{bbm(bb16->bb23->bb171)( * ((bb16)->
bb370))((bb16)->bb110,(bb70)(bb16->bb23->bb171));};{bbm(bb16->bb23->
bb385)( * ((bb16)->bb370))((bb16)->bb110,(bb70)(bb16->bb23->bb385));}
;{bbm(bb16->bb23->bb969)( * ((bb16)->bb370))((bb16)->bb110,(bb70)(
bb16->bb23->bb969));};{bbm(bb16->bb23->bb158)( * ((bb16)->bb370))((
bb16)->bb110,(bb70)(bb16->bb23->bb158));};( * ((bb16)->bb370))((bb16)->
bb110,(bb70)(bb16->bb23));bb16->bb23=0 ;bb2 bb359==113 ?(-3 ):0 ;}bbe
bb1151(bb130,bb183)bb17 bb130;bb17 bb183;{
#ifdef bb507
bb2(-2 );
#else
bb192*bb428;bb192*bb1823;bb501*bb1883;bbm(bb183==0 ||bb130==0 ||bb183->
bb23==0 ){bb2(-2 );}bb1823=bb183->bb23; *bb130= *bb183;bb428=(bb192* )(
 * ((bb130)->bb401))((bb130)->bb110,(1 ),(bb12(bb192)));bbm(bb428==0 )bb2
(-4 );bb130->bb23=(bbi bb377* )bb428; *bb428= *bb1823;bb428->bb16=
bb130;bb428->bb158=(bb30* )( * ((bb130)->bb401))((bb130)->bb110,(
bb428->bb933),(2 *bb12(bb154)));bb428->bb969=(bb1356* )( * ((bb130)->
bb401))((bb130)->bb110,(bb428->bb933),(bb12(bb1037)));bb428->bb385=(
bb1356* )( * ((bb130)->bb401))((bb130)->bb110,(bb428->bb1326),(bb12(
bb1037)));bb1883=(bb501* )( * ((bb130)->bb401))((bb130)->bb110,(bb428
->bb1126),(bb12(bb126)+2 ));bb428->bb171=(bb1206* )bb1883;bbm(bb428->
bb158==0 ||bb428->bb969==0 ||bb428->bb385==0 ||bb428->bb171==0 ){bb945(
bb130);bb2(-4 );}bb81(bb428->bb158,bb1823->bb158,bb428->bb933*2 *bb12(
bb154));bb81((bb30* )bb428->bb969,(bb30* )bb1823->bb969,bb428->bb933*
bb12(bb1037));bb81((bb30* )bb428->bb385,(bb30* )bb1823->bb385,bb428->
bb1326*bb12(bb1037));bb81(bb428->bb171,bb1823->bb171,(bb7)bb428->
bb2039);bb428->bb1875=bb428->bb171+(bb1823->bb1875-bb1823->bb171);
bb428->bb1648=bb1883+bb428->bb1126/bb12(bb126);bb428->bb1725=bb428->
bb171+(1 +bb12(bb126)) *bb428->bb1126;bb428->bb1936.bb1749=bb428->
bb972;bb428->bb1863.bb1749=bb428->bb1685;bb428->bb2062.bb1749=bb428->
bb527;bb2 0 ;
#endif
}bb41 bbe bb2434(bb16,bb40,bb47)bb17 bb16;bb30*bb40;bbs bb47;{bbs bb22
=bb16->bb148;bbm(bb22>bb47)bb22=bb47;bbm(bb22==0 )bb2 0 ;bb16->bb148-=
bb22;bbm(!bb16->bb23->bb1346){bb16->bb371=bb986(bb16->bb371,bb16->
bb127,bb22);}bb81(bb40,bb16->bb127,bb22);bb16->bb127+=bb22;bb16->
bb188+=bb22;bb2(bbe)bb22;}bb41 bbb bb2429(bbg)bb192*bbg;{bbg->bb2227=
(bb393)2L *bbg->bb933;bbg->bb385[bbg->bb1326-1 ]=0 ;bb997((bb30* )bbg->
bb385,0 ,(bbs)(bbg->bb1326-1 ) *bb12( *bbg->bb385));;bbg->bb2055=bb1335
[bbg->bb124].bb2438;bbg->bb2182=bb1335[bbg->bb124].bb2430;bbg->bb1837
=bb1335[bbg->bb124].bb2384;bbg->bb2177=bb1335[bbg->bb124].bb2348;bbg
->bb182=0 ;bbg->bb427=0L ;bbg->bb460=0 ;bbg->bb960=bbg->bb1264=3 -1 ;bbg->
bb1939=0 ;bbg->bb495=0 ;}bb41 bb7 bb2258(bbg,bb1994)bb192*bbg;bb1317
bb1994;{bbs bb2319=bbg->bb2177;bb931 bb30*bb491=bbg->bb158+bbg->bb182
;bb931 bb30*bb609;bb931 bbe bb22;bbe bb1190=bbg->bb1264;bbe bb1837=
bbg->bb1837;bb1317 bb2445=bbg->bb182>(bb1317)((bbg)->bb933-(258 +3 +1 ))?
bbg->bb182-(bb1317)((bbg)->bb933-(258 +3 +1 )):0 ;bb1356*bb969=bbg->bb969
;bb7 bb2471=bbg->bb1807;
#ifdef bb1043
bb931 bb30*bb1893=bbg->bb158+bbg->bb182+258 -1 ;bb931 bb126 bb2533= * (
bb501* )bb491;bb931 bb126 bb2121= * (bb501* )(bb491+bb1190-1 );
#else
bb931 bb30*bb1893=bbg->bb158+bbg->bb182+258 ;bb931 bb154 bb2320=bb491[
bb1190-1 ];bb931 bb154 bb2121=bb491[bb1190];
#endif
;bbm(bbg->bb1264>=bbg->bb2182){bb2319>>=2 ;}bbm((bb7)bb1837>bbg->bb460
)bb1837=bbg->bb460;;bb574{;bb609=bbg->bb158+bb1994;
#if ( defined( bb1043) && bb2581 == 258)
bbm( * (bb501* )(bb609+bb1190-1 )!=bb2121|| * (bb501* )bb609!=bb2533)bb1691
;;bb491++,bb609++;bb574{}bb107( * (bb501* )(bb491+=2 )== * (bb501* )(
bb609+=2 )&& * (bb501* )(bb491+=2 )== * (bb501* )(bb609+=2 )&& * (bb501*
)(bb491+=2 )== * (bb501* )(bb609+=2 )&& * (bb501* )(bb491+=2 )== * (
bb501* )(bb609+=2 )&&bb491<bb1893);;bbm( *bb491== *bb609)bb491++;bb22=
(258 -1 )-(bbe)(bb1893-bb491);bb491=bb1893-(258 -1 );
#else
bbm(bb609[bb1190]!=bb2121||bb609[bb1190-1 ]!=bb2320|| *bb609!= *bb491
|| * ++bb609!=bb491[1 ])bb1691;bb491+=2 ,bb609++;;bb574{}bb107( * ++
bb491== * ++bb609&& * ++bb491== * ++bb609&& * ++bb491== * ++bb609&& *
++bb491== * ++bb609&& * ++bb491== * ++bb609&& * ++bb491== * ++bb609&&
 * ++bb491== * ++bb609&& * ++bb491== * ++bb609&&bb491<bb1893);;bb22=
258 -(bbe)(bb1893-bb491);bb491=bb1893-258 ;
#endif
bbm(bb22>bb1190){bbg->bb2023=bb1994;bb1190=bb22;bbm(bb22>=bb1837)bb21
;
#ifdef bb1043
bb2121= * (bb501* )(bb491+bb1190-1 );
#else
bb2320=bb491[bb1190-1 ];bb2121=bb491[bb1190];
#endif
}}bb107((bb1994=bb969[bb1994&bb2471])>bb2445&&--bb2319!=0 );bbm((bb7)bb1190
<=bbg->bb460)bb2(bb7)bb1190;bb2 bbg->bb460;}bb41 bbb bb2191(bbg)bb192
 *bbg;{bb931 bbs bb11,bb96;bb931 bb1356*bb28;bbs bb1927;bb7 bb1224=
bbg->bb933;bb574{bb1927=(bbs)(bbg->bb2227-(bb393)bbg->bb460-(bb393)bbg
->bb182);bbm(bb1927==0 &&bbg->bb182==0 &&bbg->bb460==0 ){bb1927=bb1224;}
bb54 bbm(bb1927==(bbs)(-1 )){bb1927--;}bb54 bbm(bbg->bb182>=bb1224+((
bbg)->bb933-(258 +3 +1 ))){bb81(bbg->bb158,bbg->bb158+bb1224,(bbs)bb1224
);bbg->bb2023-=bb1224;bbg->bb182-=bb1224;bbg->bb427-=(bb6)bb1224;bb11
=bbg->bb1326;bb28=&bbg->bb385[bb11];bb574{bb96= * --bb28; *bb28=(
bb1037)(bb96>=bb1224?bb96-bb1224:0 );}bb107(--bb11);bb11=bb1224;bb28=&
bbg->bb969[bb11];bb574{bb96= * --bb28; *bb28=(bb1037)(bb96>=bb1224?
bb96-bb1224:0 );}bb107(--bb11);bb1927+=bb1224;}bbm(bbg->bb16->bb148==0
)bb2;;bb11=bb2434(bbg->bb16,bbg->bb158+bbg->bb182+bbg->bb460,bb1927);
bbg->bb460+=bb11;bbm(bbg->bb460>=3 ){bbg->bb495=bbg->bb158[bbg->bb182]
;(bbg->bb495=(((bbg->bb495)<<bbg->bb1610)^(bbg->bb158[bbg->bb182+1 ]))&
bbg->bb1382);}}bb107(bbg->bb460<(258 +3 +1 )&&bbg->bb16->bb148!=0 );}bb41
bb1822 bb2381(bbg,bb175)bb192*bbg;bbe bb175;{bb393 bb2274=0xffff ;
bb393 bb2154;bbm(bb2274>bbg->bb2039-5 ){bb2274=bbg->bb2039-5 ;}bb91(;;){
bbm(bbg->bb460<=1 ){;bb2191(bbg);bbm(bbg->bb460==0 &&bb175==0 )bb2 bb1283
;bbm(bbg->bb460==0 )bb21;};bbg->bb182+=bbg->bb460;bbg->bb460=0 ;bb2154=
bbg->bb427+bb2274;bbm(bbg->bb182==0 ||(bb393)bbg->bb182>=bb2154){bbg->
bb460=(bb7)(bbg->bb182-bb2154);bbg->bb182=(bb7)bb2154;{{bb1622(bbg,(
bbg->bb427>=0L ?(bb439* )&bbg->bb158[(bbs)bbg->bb427]:(bb439* )0 ),(
bb393)((bb6)bbg->bb182-bbg->bb427),(0 ));bbg->bb427=bbg->bb182;bb1267(
bbg->bb16);;};bbm(bbg->bb16->bb383==0 )bb2(0 )?bb1757:bb1283;};}bbm(bbg
->bb182-(bb7)bbg->bb427>=((bbg)->bb933-(258 +3 +1 ))){{{bb1622(bbg,(bbg
->bb427>=0L ?(bb439* )&bbg->bb158[(bbs)bbg->bb427]:(bb439* )0 ),(bb393)(
(bb6)bbg->bb182-bbg->bb427),(0 ));bbg->bb427=bbg->bb182;bb1267(bbg->
bb16);;};bbm(bbg->bb16->bb383==0 )bb2(0 )?bb1757:bb1283;};}}{{bb1622(
bbg,(bbg->bb427>=0L ?(bb439* )&bbg->bb158[(bbs)bbg->bb427]:(bb439* )0 ),
(bb393)((bb6)bbg->bb182-bbg->bb427),(bb175==4 ));bbg->bb427=bbg->bb182
;bb1267(bbg->bb16);;};bbm(bbg->bb16->bb383==0 )bb2(bb175==4 )?bb1757:
bb1283;};bb2 bb175==4 ?bb2141:bb2159;}bb41 bb1822 bb2162(bbg,bb175)bb192
 *bbg;bbe bb175;{bb1317 bb1131=0 ;bbe bb1763;bb91(;;){bbm(bbg->bb460<(
258 +3 +1 )){bb2191(bbg);bbm(bbg->bb460<(258 +3 +1 )&&bb175==0 ){bb2 bb1283;
}bbm(bbg->bb460==0 )bb21;}bbm(bbg->bb460>=3 ){((bbg->bb495=(((bbg->
bb495)<<bbg->bb1610)^(bbg->bb158[(bbg->bb182)+(3 -1 )]))&bbg->bb1382),
bbg->bb969[(bbg->bb182)&bbg->bb1807]=bb1131=bbg->bb385[bbg->bb495],
bbg->bb385[bbg->bb495]=(bb1037)(bbg->bb182));}bbm(bb1131!=0 &&bbg->
bb182-bb1131<=((bbg)->bb933-(258 +3 +1 ))){bbm(bbg->bb301!=2 ){bbg->bb960
=bb2258(bbg,bb1131);}}bbm(bbg->bb960>=3 ){;{bb155 bb22=(bbg->bb960-3 );
bb126 bb414=(bbg->bb182-bbg->bb2023);bbg->bb1648[bbg->bb600]=bb414;
bbg->bb1725[bbg->bb600++]=bb22;bb414--;bbg->bb972[bb2052[bb22]+256 +1 ]
.bb219.bb429++;bbg->bb1685[((bb414)<256 ?bb1735[bb414]:bb1735[256 +((
bb414)>>7 )])].bb219.bb429++;bb1763=(bbg->bb600==bbg->bb1126-1 );};bbg
->bb460-=bbg->bb960;bbm(bbg->bb960<=bbg->bb2055&&bbg->bb460>=3 ){bbg->
bb960--;bb574{bbg->bb182++;((bbg->bb495=(((bbg->bb495)<<bbg->bb1610)^
(bbg->bb158[(bbg->bb182)+(3 -1 )]))&bbg->bb1382),bbg->bb969[(bbg->bb182
)&bbg->bb1807]=bb1131=bbg->bb385[bbg->bb495],bbg->bb385[bbg->bb495]=(
bb1037)(bbg->bb182));}bb107(--bbg->bb960!=0 );bbg->bb182++;}bb54{bbg->
bb182+=bbg->bb960;bbg->bb960=0 ;bbg->bb495=bbg->bb158[bbg->bb182];(bbg
->bb495=(((bbg->bb495)<<bbg->bb1610)^(bbg->bb158[bbg->bb182+1 ]))&bbg
->bb1382);}}bb54{;{bb155 bb1841=(bbg->bb158[bbg->bb182]);bbg->bb1648[
bbg->bb600]=0 ;bbg->bb1725[bbg->bb600++]=bb1841;bbg->bb972[bb1841].
bb219.bb429++;bb1763=(bbg->bb600==bbg->bb1126-1 );};bbg->bb460--;bbg->
bb182++;}bbm(bb1763){{bb1622(bbg,(bbg->bb427>=0L ?(bb439* )&bbg->bb158
[(bbs)bbg->bb427]:(bb439* )0 ),(bb393)((bb6)bbg->bb182-bbg->bb427),(0 ));
bbg->bb427=bbg->bb182;bb1267(bbg->bb16);;};bbm(bbg->bb16->bb383==0 )bb2
(0 )?bb1757:bb1283;};}{{bb1622(bbg,(bbg->bb427>=0L ?(bb439* )&bbg->
bb158[(bbs)bbg->bb427]:(bb439* )0 ),(bb393)((bb6)bbg->bb182-bbg->bb427
),(bb175==4 ));bbg->bb427=bbg->bb182;bb1267(bbg->bb16);;};bbm(bbg->
bb16->bb383==0 )bb2(bb175==4 )?bb1757:bb1283;};bb2 bb175==4 ?bb2141:
bb2159;}bb41 bb1822 bb1946(bbg,bb175)bb192*bbg;bbe bb175;{bb1317
bb1131=0 ;bbe bb1763;bb91(;;){bbm(bbg->bb460<(258 +3 +1 )){bb2191(bbg);
bbm(bbg->bb460<(258 +3 +1 )&&bb175==0 ){bb2 bb1283;}bbm(bbg->bb460==0 )bb21
;}bbm(bbg->bb460>=3 ){((bbg->bb495=(((bbg->bb495)<<bbg->bb1610)^(bbg->
bb158[(bbg->bb182)+(3 -1 )]))&bbg->bb1382),bbg->bb969[(bbg->bb182)&bbg
->bb1807]=bb1131=bbg->bb385[bbg->bb495],bbg->bb385[bbg->bb495]=(
bb1037)(bbg->bb182));}bbg->bb1264=bbg->bb960,bbg->bb2298=bbg->bb2023;
bbg->bb960=3 -1 ;bbm(bb1131!=0 &&bbg->bb1264<bbg->bb2055&&bbg->bb182-
bb1131<=((bbg)->bb933-(258 +3 +1 ))){bbm(bbg->bb301!=2 ){bbg->bb960=
bb2258(bbg,bb1131);}bbm(bbg->bb960<=5 &&(bbg->bb301==1 ||(bbg->bb960==3
&&bbg->bb182-bbg->bb2023>4096 ))){bbg->bb960=3 -1 ;}}bbm(bbg->bb1264>=3
&&bbg->bb960<=bbg->bb1264){bb7 bb2493=bbg->bb182+bbg->bb460-3 ;;{bb155
bb22=(bbg->bb1264-3 );bb126 bb414=(bbg->bb182-1 -bbg->bb2298);bbg->
bb1648[bbg->bb600]=bb414;bbg->bb1725[bbg->bb600++]=bb22;bb414--;bbg->
bb972[bb2052[bb22]+256 +1 ].bb219.bb429++;bbg->bb1685[((bb414)<256 ?
bb1735[bb414]:bb1735[256 +((bb414)>>7 )])].bb219.bb429++;bb1763=(bbg->
bb600==bbg->bb1126-1 );};bbg->bb460-=bbg->bb1264-1 ;bbg->bb1264-=2 ;
bb574{bbm(++bbg->bb182<=bb2493){((bbg->bb495=(((bbg->bb495)<<bbg->
bb1610)^(bbg->bb158[(bbg->bb182)+(3 -1 )]))&bbg->bb1382),bbg->bb969[(
bbg->bb182)&bbg->bb1807]=bb1131=bbg->bb385[bbg->bb495],bbg->bb385[bbg
->bb495]=(bb1037)(bbg->bb182));}}bb107(--bbg->bb1264!=0 );bbg->bb1939=
0 ;bbg->bb960=3 -1 ;bbg->bb182++;bbm(bb1763){{bb1622(bbg,(bbg->bb427>=0L
?(bb439* )&bbg->bb158[(bbs)bbg->bb427]:(bb439* )0 ),(bb393)((bb6)bbg->
bb182-bbg->bb427),(0 ));bbg->bb427=bbg->bb182;bb1267(bbg->bb16);;};bbm
(bbg->bb16->bb383==0 )bb2(0 )?bb1757:bb1283;};}bb54 bbm(bbg->bb1939){;{
bb155 bb1841=(bbg->bb158[bbg->bb182-1 ]);bbg->bb1648[bbg->bb600]=0 ;bbg
->bb1725[bbg->bb600++]=bb1841;bbg->bb972[bb1841].bb219.bb429++;bb1763
=(bbg->bb600==bbg->bb1126-1 );};bbm(bb1763){{bb1622(bbg,(bbg->bb427>=
0L ?(bb439* )&bbg->bb158[(bbs)bbg->bb427]:(bb439* )0 ),(bb393)((bb6)bbg
->bb182-bbg->bb427),(0 ));bbg->bb427=bbg->bb182;bb1267(bbg->bb16);;};}
bbg->bb182++;bbg->bb460--;bbm(bbg->bb16->bb383==0 )bb2 bb1283;}bb54{
bbg->bb1939=1 ;bbg->bb182++;bbg->bb460--;}};bbm(bbg->bb1939){;{bb155
bb1841=(bbg->bb158[bbg->bb182-1 ]);bbg->bb1648[bbg->bb600]=0 ;bbg->
bb1725[bbg->bb600++]=bb1841;bbg->bb972[bb1841].bb219.bb429++;bb1763=(
bbg->bb600==bbg->bb1126-1 );};bbg->bb1939=0 ;}{{bb1622(bbg,(bbg->bb427
>=0L ?(bb439* )&bbg->bb158[(bbs)bbg->bb427]:(bb439* )0 ),(bb393)((bb6)bbg
->bb182-bbg->bb427),(bb175==4 ));bbg->bb427=bbg->bb182;bb1267(bbg->
bb16);;};bbm(bbg->bb16->bb383==0 )bb2(bb175==4 )?bb1757:bb1283;};bb2
bb175==4 ?bb2141:bb2159;}
