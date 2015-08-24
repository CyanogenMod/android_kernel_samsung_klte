/*
   'src_compress_deflate_inftrees.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Wed Jan 15 12:08:55 2014
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
bb912));bba bbi bb1375 bb153;bbi bb1375{bb557{bbi{bb154 bb1174;bb154
bb959;}bb513;bb7 bb1550;}bb512;bb7 bb607;};bbr bbe bb2014 bbp((bb165*
,bb165* ,bb153* * ,bb153* ,bb17));bbr bbe bb1997 bbp((bb7,bb7,bb165* ,
bb165* ,bb165* ,bb153* * ,bb153* * ,bb153* ,bb17));bbr bbe bb1967 bbp
((bb165* ,bb165* ,bb153* * ,bb153* * ,bb17));
#if ! defined( bb2246) && ! defined( bb136)
#define bb2246
#endif
bbi bb377{bbe bb444;};bb41 bbe bb1975 bbp((bb165* ,bb7,bb7,bbh bb165*
,bbh bb165* ,bb153* * ,bb165* ,bb153* ,bb7* ,bb165* ));bb41 bbh bb7
bb2373[31 ]={3 ,4 ,5 ,6 ,7 ,8 ,9 ,10 ,11 ,13 ,15 ,17 ,19 ,23 ,27 ,31 ,35 ,43 ,51 ,59 ,67 ,
83 ,99 ,115 ,131 ,163 ,195 ,227 ,258 ,0 ,0 };bb41 bbh bb7 bb2361[31 ]={0 ,0 ,0 ,0 ,0
,0 ,0 ,0 ,1 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,3 ,3 ,3 ,3 ,4 ,4 ,4 ,4 ,5 ,5 ,5 ,5 ,0 ,112 ,112 };bb41 bbh bb7
bb2407[30 ]={1 ,2 ,3 ,4 ,5 ,7 ,9 ,13 ,17 ,25 ,33 ,49 ,65 ,97 ,129 ,193 ,257 ,385 ,513 ,
769 ,1025 ,1537 ,2049 ,3073 ,4097 ,6145 ,8193 ,12289 ,16385 ,24577 };bb41 bbh bb7
bb2408[30 ]={0 ,0 ,0 ,0 ,1 ,1 ,2 ,2 ,3 ,3 ,4 ,4 ,5 ,5 ,6 ,6 ,7 ,7 ,8 ,8 ,9 ,9 ,10 ,10 ,11 ,11 ,
12 ,12 ,13 ,13 };bb41 bbe bb1975(bbn,bb11,bbg,bbt,bbw,bb45,bb96,bb1786,
bb1787,bb437)bb165*bbn;bb7 bb11;bb7 bbg;bbh bb165*bbt;bbh bb165*bbw;
bb153* *bb45;bb165*bb96;bb153*bb1786;bb7*bb1787;bb165*bb437;{bb7 bbc;
bb7 bbo[15 +1 ];bb7 bb19;bbe bb52;bbe bb42;bb931 bb7 bbz;bb931 bb7 bb76
;bb931 bbe bb3;bbe bb194;bb7 bb1171;bb931 bb165*bb28;bb153*bb84;bbi
bb1375 bb27={{{0 }},0 };bb153*bb316[15 ];bb931 bbe bbv;bb7 bb8[15 +1 ];
bb165*bb2086;bbe bb193;bb7 bby;bb28=bbo; *bb28++=0 ; *bb28++=0 ; *bb28
++=0 ; *bb28++=0 ; *bb28++=0 ; *bb28++=0 ; *bb28++=0 ; *bb28++=0 ; *bb28++=
0 ; *bb28++=0 ; *bb28++=0 ; *bb28++=0 ; *bb28++=0 ; *bb28++=0 ; *bb28++=0 ; *
bb28++=0 ;bb28=bbn;bbz=bb11;bb574{bbo[ *bb28++]++;}bb107(--bbz);bbm(
bbo[0 ]==bb11){ *bb45=(bb153* )0 ; *bb96=0 ;bb2 0 ;}bb194= *bb96;bb91(
bb76=1 ;bb76<=15 ;bb76++)bbm(bbo[bb76])bb21;bb3=bb76;bbm((bb7)bb194<
bb76)bb194=bb76;bb91(bbz=15 ;bbz;bbz--)bbm(bbo[bbz])bb21;bb52=bbz;bbm(
(bb7)bb194>bbz)bb194=bbz; *bb96=bb194;bb91(bb193=1 <<bb76;bb76<bbz;
bb76++,bb193<<=1 )bbm((bb193-=bbo[bb76])<0 )bb2(-3 );bbm((bb193-=bbo[bbz
])<0 )bb2(-3 );bbo[bbz]+=bb193;bb8[1 ]=bb76=0 ;bb28=bbo+1 ;bb2086=bb8+2 ;
bb107(--bbz){ *bb2086++=(bb76+= *bb28++);}bb28=bbn;bbz=0 ;bb574{bbm((
bb76= *bb28++)!=0 )bb437[bb8[bb76]++]=bbz;}bb107(++bbz<bb11);bb11=bb8[
bb52];bb8[0 ]=bbz=0 ;bb28=bb437;bb42=-1 ;bbv=-bb194;bb316[0 ]=(bb153* )0 ;
bb84=(bb153* )0 ;bby=0 ;bb91(;bb3<=bb52;bb3++){bbc=bbo[bb3];bb107(bbc--
){bb107(bb3>bbv+bb194){bb42++;bbv+=bb194;bby=bb52-bbv;bby=bby>(bb7)bb194
?(bb7)bb194:bby;bbm((bb19=1 <<(bb76=bb3-bbv))>bbc+1 ){bb19-=bbc+1 ;
bb2086=bbo+bb3;bbm(bb76<bby)bb107(++bb76<bby){bbm((bb19<<=1 )<= * ++
bb2086)bb21;bb19-= *bb2086;}}bby=1 <<bb76;bbm( *bb1787+bby>1440 )bb2(-4
);bb316[bb42]=bb84=bb1786+ *bb1787; *bb1787+=bby;bbm(bb42){bb8[bb42]=
bbz;bb27.bb512.bb513.bb959=(bb154)bb194;bb27.bb512.bb513.bb1174=(
bb154)bb76;bb76=bbz>>(bbv-bb194);bb27.bb607=(bb7)(bb84-bb316[bb42-1 ]-
bb76);bb316[bb42-1 ][bb76]=bb27;}bb54*bb45=bb84;}bb27.bb512.bb513.
bb959=(bb154)(bb3-bbv);bbm(bb28>=bb437+bb11)bb27.bb512.bb513.bb1174=
128 +64 ;bb54 bbm( *bb28<bbg){bb27.bb512.bb513.bb1174=(bb154)( *bb28<
256 ?0 :32 +64 );bb27.bb607= *bb28++;}bb54{bb27.bb512.bb513.bb1174=(bb154
)(bbw[ *bb28-bbg]+16 +64 );bb27.bb607=bbt[ *bb28++-bbg];}bb19=1 <<(bb3-
bbv);bb91(bb76=bbz>>bbv;bb76<bby;bb76+=bb19)bb84[bb76]=bb27;bb91(bb76
=1 <<(bb3-1 );bbz&bb76;bb76>>=1 )bbz^=bb76;bbz^=bb76;bb1171=(1 <<bbv)-1 ;
bb107((bbz&bb1171)!=bb8[bb42]){bb42--;bbv-=bb194;bb1171=(1 <<bbv)-1 ;}}
}bb2 bb193!=0 &&bb52!=1 ?(-5 ):0 ;}bbe bb2014(bbo,bb1724,bb1739,bb1786,
bby)bb165*bbo;bb165*bb1724;bb153* *bb1739;bb153*bb1786;bb17 bby;{bbe
bb27;bb7 bb1787=0 ;bb165*bb437;bbm((bb437=(bb165* )( * ((bby)->bb401))(
(bby)->bb110,(19 ),(bb12(bb7))))==0 )bb2(-4 );bb27=bb1975(bbo,19 ,19 ,(
bb165* )0 ,(bb165* )0 ,bb1739,bb1724,bb1786,&bb1787,bb437);bbm(bb27==(-
3 ))bby->bb324=(bbl* )"";bb54 bbm(bb27==(-5 )|| *bb1724==0 ){bby->bb324=
(bbl* )"";bb27=(-3 );}( * ((bby)->bb370))((bby)->bb110,(bb70)(bb437));
bb2 bb27;}bbe bb1997(bb2178,bb2394,bbo,bb55,bb961,bb1017,bb1025,
bb1786,bby)bb7 bb2178;bb7 bb2394;bb165*bbo;bb165*bb55;bb165*bb961;
bb153* *bb1017;bb153* *bb1025;bb153*bb1786;bb17 bby;{bbe bb27;bb7
bb1787=0 ;bb165*bb437;bbm((bb437=(bb165* )( * ((bby)->bb401))((bby)->
bb110,(288 ),(bb12(bb7))))==0 )bb2(-4 );bb27=bb1975(bbo,bb2178,257 ,
bb2373,bb2361,bb1017,bb55,bb1786,&bb1787,bb437);bbm(bb27!=0 || *bb55==
0 ){bbm(bb27==(-3 ))bby->bb324=(bbl* )"";bb54 bbm(bb27!=(-4 )){bby->
bb324=(bbl* )"";bb27=(-3 );}( * ((bby)->bb370))((bby)->bb110,(bb70)(
bb437));bb2 bb27;}bb27=bb1975(bbo+bb2178,bb2394,0 ,bb2407,bb2408,
bb1025,bb961,bb1786,&bb1787,bb437);bbm(bb27!=0 ||( *bb961==0 &&bb2178>
257 )){bbm(bb27==(-3 ))bby->bb324=(bbl* )"";bb54 bbm(bb27==(-5 )){bby->
bb324=(bbl* )"";bb27=(-3 );}bb54 bbm(bb27!=(-4 )){bby->bb324=(bbl* )"";
bb27=(-3 );}( * ((bby)->bb370))((bby)->bb110,(bb70)(bb437));bb2 bb27;}
( * ((bby)->bb370))((bby)->bb110,(bb70)(bb437));bb2 0 ;}
#ifdef bb2246
bb41 bbe bb2337=0 ;
#define bb2541 544
bb41 bb153 bb2428[bb2541];bb41 bb7 bb2131;bb41 bb7 bb2132;bb41 bb153*
bb2266;bb41 bb153*bb2267;
#else
bb41 bb7 bb2131=9 ;bb41 bb7 bb2132=5 ;bb41 bb153 bb2266[]={{{{96 ,7 }},
256 },{{{0 ,8 }},80 },{{{0 ,8 }},16 },{{{84 ,8 }},115 },{{{82 ,7 }},31 },{{{0 ,8 }},
112 },{{{0 ,8 }},48 },{{{0 ,9 }},192 },{{{80 ,7 }},10 },{{{0 ,8 }},96 },{{{0 ,8 }},
32 },{{{0 ,9 }},160 },{{{0 ,8 }},0 },{{{0 ,8 }},128 },{{{0 ,8 }},64 },{{{0 ,9 }},224
},{{{80 ,7 }},6 },{{{0 ,8 }},88 },{{{0 ,8 }},24 },{{{0 ,9 }},144 },{{{83 ,7 }},59 },
{{{0 ,8 }},120 },{{{0 ,8 }},56 },{{{0 ,9 }},208 },{{{81 ,7 }},17 },{{{0 ,8 }},104 },
{{{0 ,8 }},40 },{{{0 ,9 }},176 },{{{0 ,8 }},8 },{{{0 ,8 }},136 },{{{0 ,8 }},72 },{{{
0 ,9 }},240 },{{{80 ,7 }},4 },{{{0 ,8 }},84 },{{{0 ,8 }},20 },{{{85 ,8 }},227 },{{{
83 ,7 }},43 },{{{0 ,8 }},116 },{{{0 ,8 }},52 },{{{0 ,9 }},200 },{{{81 ,7 }},13 },{{{
0 ,8 }},100 },{{{0 ,8 }},36 },{{{0 ,9 }},168 },{{{0 ,8 }},4 },{{{0 ,8 }},132 },{{{0 ,
8 }},68 },{{{0 ,9 }},232 },{{{80 ,7 }},8 },{{{0 ,8 }},92 },{{{0 ,8 }},28 },{{{0 ,9 }}
,152 },{{{84 ,7 }},83 },{{{0 ,8 }},124 },{{{0 ,8 }},60 },{{{0 ,9 }},216 },{{{82 ,7 }
},23 },{{{0 ,8 }},108 },{{{0 ,8 }},44 },{{{0 ,9 }},184 },{{{0 ,8 }},12 },{{{0 ,8 }},
140 },{{{0 ,8 }},76 },{{{0 ,9 }},248 },{{{80 ,7 }},3 },{{{0 ,8 }},82 },{{{0 ,8 }},18
},{{{85 ,8 }},163 },{{{83 ,7 }},35 },{{{0 ,8 }},114 },{{{0 ,8 }},50 },{{{0 ,9 }},
196 },{{{81 ,7 }},11 },{{{0 ,8 }},98 },{{{0 ,8 }},34 },{{{0 ,9 }},164 },{{{0 ,8 }},2
},{{{0 ,8 }},130 },{{{0 ,8 }},66 },{{{0 ,9 }},228 },{{{80 ,7 }},7 },{{{0 ,8 }},90 },
{{{0 ,8 }},26 },{{{0 ,9 }},148 },{{{84 ,7 }},67 },{{{0 ,8 }},122 },{{{0 ,8 }},58 },{
{{0 ,9 }},212 },{{{82 ,7 }},19 },{{{0 ,8 }},106 },{{{0 ,8 }},42 },{{{0 ,9 }},180 },{
{{0 ,8 }},10 },{{{0 ,8 }},138 },{{{0 ,8 }},74 },{{{0 ,9 }},244 },{{{80 ,7 }},5 },{{{
0 ,8 }},86 },{{{0 ,8 }},22 },{{{192 ,8 }},0 },{{{83 ,7 }},51 },{{{0 ,8 }},118 },{{{0
,8 }},54 },{{{0 ,9 }},204 },{{{81 ,7 }},15 },{{{0 ,8 }},102 },{{{0 ,8 }},38 },{{{0 ,
9 }},172 },{{{0 ,8 }},6 },{{{0 ,8 }},134 },{{{0 ,8 }},70 },{{{0 ,9 }},236 },{{{80 ,7
}},9 },{{{0 ,8 }},94 },{{{0 ,8 }},30 },{{{0 ,9 }},156 },{{{84 ,7 }},99 },{{{0 ,8 }},
126 },{{{0 ,8 }},62 },{{{0 ,9 }},220 },{{{82 ,7 }},27 },{{{0 ,8 }},110 },{{{0 ,8 }},
46 },{{{0 ,9 }},188 },{{{0 ,8 }},14 },{{{0 ,8 }},142 },{{{0 ,8 }},78 },{{{0 ,9 }},
252 },{{{96 ,7 }},256 },{{{0 ,8 }},81 },{{{0 ,8 }},17 },{{{85 ,8 }},131 },{{{82 ,7 }
},31 },{{{0 ,8 }},113 },{{{0 ,8 }},49 },{{{0 ,9 }},194 },{{{80 ,7 }},10 },{{{0 ,8 }}
,97 },{{{0 ,8 }},33 },{{{0 ,9 }},162 },{{{0 ,8 }},1 },{{{0 ,8 }},129 },{{{0 ,8 }},65
},{{{0 ,9 }},226 },{{{80 ,7 }},6 },{{{0 ,8 }},89 },{{{0 ,8 }},25 },{{{0 ,9 }},146 },
{{{83 ,7 }},59 },{{{0 ,8 }},121 },{{{0 ,8 }},57 },{{{0 ,9 }},210 },{{{81 ,7 }},17 },
{{{0 ,8 }},105 },{{{0 ,8 }},41 },{{{0 ,9 }},178 },{{{0 ,8 }},9 },{{{0 ,8 }},137 },{{
{0 ,8 }},73 },{{{0 ,9 }},242 },{{{80 ,7 }},4 },{{{0 ,8 }},85 },{{{0 ,8 }},21 },{{{80
,8 }},258 },{{{83 ,7 }},43 },{{{0 ,8 }},117 },{{{0 ,8 }},53 },{{{0 ,9 }},202 },{{{
81 ,7 }},13 },{{{0 ,8 }},101 },{{{0 ,8 }},37 },{{{0 ,9 }},170 },{{{0 ,8 }},5 },{{{0 ,
8 }},133 },{{{0 ,8 }},69 },{{{0 ,9 }},234 },{{{80 ,7 }},8 },{{{0 ,8 }},93 },{{{0 ,8 }
},29 },{{{0 ,9 }},154 },{{{84 ,7 }},83 },{{{0 ,8 }},125 },{{{0 ,8 }},61 },{{{0 ,9 }}
,218 },{{{82 ,7 }},23 },{{{0 ,8 }},109 },{{{0 ,8 }},45 },{{{0 ,9 }},186 },{{{0 ,8 }}
,13 },{{{0 ,8 }},141 },{{{0 ,8 }},77 },{{{0 ,9 }},250 },{{{80 ,7 }},3 },{{{0 ,8 }},
83 },{{{0 ,8 }},19 },{{{85 ,8 }},195 },{{{83 ,7 }},35 },{{{0 ,8 }},115 },{{{0 ,8 }},
51 },{{{0 ,9 }},198 },{{{81 ,7 }},11 },{{{0 ,8 }},99 },{{{0 ,8 }},35 },{{{0 ,9 }},
166 },{{{0 ,8 }},3 },{{{0 ,8 }},131 },{{{0 ,8 }},67 },{{{0 ,9 }},230 },{{{80 ,7 }},7
},{{{0 ,8 }},91 },{{{0 ,8 }},27 },{{{0 ,9 }},150 },{{{84 ,7 }},67 },{{{0 ,8 }},123 }
,{{{0 ,8 }},59 },{{{0 ,9 }},214 },{{{82 ,7 }},19 },{{{0 ,8 }},107 },{{{0 ,8 }},43 },
{{{0 ,9 }},182 },{{{0 ,8 }},11 },{{{0 ,8 }},139 },{{{0 ,8 }},75 },{{{0 ,9 }},246 },{
{{80 ,7 }},5 },{{{0 ,8 }},87 },{{{0 ,8 }},23 },{{{192 ,8 }},0 },{{{83 ,7 }},51 },{{{
0 ,8 }},119 },{{{0 ,8 }},55 },{{{0 ,9 }},206 },{{{81 ,7 }},15 },{{{0 ,8 }},103 },{{{
0 ,8 }},39 },{{{0 ,9 }},174 },{{{0 ,8 }},7 },{{{0 ,8 }},135 },{{{0 ,8 }},71 },{{{0 ,9
}},238 },{{{80 ,7 }},9 },{{{0 ,8 }},95 },{{{0 ,8 }},31 },{{{0 ,9 }},158 },{{{84 ,7 }
},99 },{{{0 ,8 }},127 },{{{0 ,8 }},63 },{{{0 ,9 }},222 },{{{82 ,7 }},27 },{{{0 ,8 }}
,111 },{{{0 ,8 }},47 },{{{0 ,9 }},190 },{{{0 ,8 }},15 },{{{0 ,8 }},143 },{{{0 ,8 }},
79 },{{{0 ,9 }},254 },{{{96 ,7 }},256 },{{{0 ,8 }},80 },{{{0 ,8 }},16 },{{{84 ,8 }},
115 },{{{82 ,7 }},31 },{{{0 ,8 }},112 },{{{0 ,8 }},48 },{{{0 ,9 }},193 },{{{80 ,7 }}
,10 },{{{0 ,8 }},96 },{{{0 ,8 }},32 },{{{0 ,9 }},161 },{{{0 ,8 }},0 },{{{0 ,8 }},128
},{{{0 ,8 }},64 },{{{0 ,9 }},225 },{{{80 ,7 }},6 },{{{0 ,8 }},88 },{{{0 ,8 }},24 },{
{{0 ,9 }},145 },{{{83 ,7 }},59 },{{{0 ,8 }},120 },{{{0 ,8 }},56 },{{{0 ,9 }},209 },{
{{81 ,7 }},17 },{{{0 ,8 }},104 },{{{0 ,8 }},40 },{{{0 ,9 }},177 },{{{0 ,8 }},8 },{{{
0 ,8 }},136 },{{{0 ,8 }},72 },{{{0 ,9 }},241 },{{{80 ,7 }},4 },{{{0 ,8 }},84 },{{{0 ,
8 }},20 },{{{85 ,8 }},227 },{{{83 ,7 }},43 },{{{0 ,8 }},116 },{{{0 ,8 }},52 },{{{0 ,
9 }},201 },{{{81 ,7 }},13 },{{{0 ,8 }},100 },{{{0 ,8 }},36 },{{{0 ,9 }},169 },{{{0 ,
8 }},4 },{{{0 ,8 }},132 },{{{0 ,8 }},68 },{{{0 ,9 }},233 },{{{80 ,7 }},8 },{{{0 ,8 }}
,92 },{{{0 ,8 }},28 },{{{0 ,9 }},153 },{{{84 ,7 }},83 },{{{0 ,8 }},124 },{{{0 ,8 }},
60 },{{{0 ,9 }},217 },{{{82 ,7 }},23 },{{{0 ,8 }},108 },{{{0 ,8 }},44 },{{{0 ,9 }},
185 },{{{0 ,8 }},12 },{{{0 ,8 }},140 },{{{0 ,8 }},76 },{{{0 ,9 }},249 },{{{80 ,7 }},
3 },{{{0 ,8 }},82 },{{{0 ,8 }},18 },{{{85 ,8 }},163 },{{{83 ,7 }},35 },{{{0 ,8 }},
114 },{{{0 ,8 }},50 },{{{0 ,9 }},197 },{{{81 ,7 }},11 },{{{0 ,8 }},98 },{{{0 ,8 }},
34 },{{{0 ,9 }},165 },{{{0 ,8 }},2 },{{{0 ,8 }},130 },{{{0 ,8 }},66 },{{{0 ,9 }},229
},{{{80 ,7 }},7 },{{{0 ,8 }},90 },{{{0 ,8 }},26 },{{{0 ,9 }},149 },{{{84 ,7 }},67 },
{{{0 ,8 }},122 },{{{0 ,8 }},58 },{{{0 ,9 }},213 },{{{82 ,7 }},19 },{{{0 ,8 }},106 },
{{{0 ,8 }},42 },{{{0 ,9 }},181 },{{{0 ,8 }},10 },{{{0 ,8 }},138 },{{{0 ,8 }},74 },{{
{0 ,9 }},245 },{{{80 ,7 }},5 },{{{0 ,8 }},86 },{{{0 ,8 }},22 },{{{192 ,8 }},0 },{{{
83 ,7 }},51 },{{{0 ,8 }},118 },{{{0 ,8 }},54 },{{{0 ,9 }},205 },{{{81 ,7 }},15 },{{{
0 ,8 }},102 },{{{0 ,8 }},38 },{{{0 ,9 }},173 },{{{0 ,8 }},6 },{{{0 ,8 }},134 },{{{0 ,
8 }},70 },{{{0 ,9 }},237 },{{{80 ,7 }},9 },{{{0 ,8 }},94 },{{{0 ,8 }},30 },{{{0 ,9 }}
,157 },{{{84 ,7 }},99 },{{{0 ,8 }},126 },{{{0 ,8 }},62 },{{{0 ,9 }},221 },{{{82 ,7 }
},27 },{{{0 ,8 }},110 },{{{0 ,8 }},46 },{{{0 ,9 }},189 },{{{0 ,8 }},14 },{{{0 ,8 }},
142 },{{{0 ,8 }},78 },{{{0 ,9 }},253 },{{{96 ,7 }},256 },{{{0 ,8 }},81 },{{{0 ,8 }},
17 },{{{85 ,8 }},131 },{{{82 ,7 }},31 },{{{0 ,8 }},113 },{{{0 ,8 }},49 },{{{0 ,9 }},
195 },{{{80 ,7 }},10 },{{{0 ,8 }},97 },{{{0 ,8 }},33 },{{{0 ,9 }},163 },{{{0 ,8 }},1
},{{{0 ,8 }},129 },{{{0 ,8 }},65 },{{{0 ,9 }},227 },{{{80 ,7 }},6 },{{{0 ,8 }},89 },
{{{0 ,8 }},25 },{{{0 ,9 }},147 },{{{83 ,7 }},59 },{{{0 ,8 }},121 },{{{0 ,8 }},57 },{
{{0 ,9 }},211 },{{{81 ,7 }},17 },{{{0 ,8 }},105 },{{{0 ,8 }},41 },{{{0 ,9 }},179 },{
{{0 ,8 }},9 },{{{0 ,8 }},137 },{{{0 ,8 }},73 },{{{0 ,9 }},243 },{{{80 ,7 }},4 },{{{0
,8 }},85 },{{{0 ,8 }},21 },{{{80 ,8 }},258 },{{{83 ,7 }},43 },{{{0 ,8 }},117 },{{{0
,8 }},53 },{{{0 ,9 }},203 },{{{81 ,7 }},13 },{{{0 ,8 }},101 },{{{0 ,8 }},37 },{{{0 ,
9 }},171 },{{{0 ,8 }},5 },{{{0 ,8 }},133 },{{{0 ,8 }},69 },{{{0 ,9 }},235 },{{{80 ,7
}},8 },{{{0 ,8 }},93 },{{{0 ,8 }},29 },{{{0 ,9 }},155 },{{{84 ,7 }},83 },{{{0 ,8 }},
125 },{{{0 ,8 }},61 },{{{0 ,9 }},219 },{{{82 ,7 }},23 },{{{0 ,8 }},109 },{{{0 ,8 }},
45 },{{{0 ,9 }},187 },{{{0 ,8 }},13 },{{{0 ,8 }},141 },{{{0 ,8 }},77 },{{{0 ,9 }},
251 },{{{80 ,7 }},3 },{{{0 ,8 }},83 },{{{0 ,8 }},19 },{{{85 ,8 }},195 },{{{83 ,7 }},
35 },{{{0 ,8 }},115 },{{{0 ,8 }},51 },{{{0 ,9 }},199 },{{{81 ,7 }},11 },{{{0 ,8 }},
99 },{{{0 ,8 }},35 },{{{0 ,9 }},167 },{{{0 ,8 }},3 },{{{0 ,8 }},131 },{{{0 ,8 }},67 }
,{{{0 ,9 }},231 },{{{80 ,7 }},7 },{{{0 ,8 }},91 },{{{0 ,8 }},27 },{{{0 ,9 }},151 },{
{{84 ,7 }},67 },{{{0 ,8 }},123 },{{{0 ,8 }},59 },{{{0 ,9 }},215 },{{{82 ,7 }},19 },{
{{0 ,8 }},107 },{{{0 ,8 }},43 },{{{0 ,9 }},183 },{{{0 ,8 }},11 },{{{0 ,8 }},139 },{{
{0 ,8 }},75 },{{{0 ,9 }},247 },{{{80 ,7 }},5 },{{{0 ,8 }},87 },{{{0 ,8 }},23 },{{{
192 ,8 }},0 },{{{83 ,7 }},51 },{{{0 ,8 }},119 },{{{0 ,8 }},55 },{{{0 ,9 }},207 },{{{
81 ,7 }},15 },{{{0 ,8 }},103 },{{{0 ,8 }},39 },{{{0 ,9 }},175 },{{{0 ,8 }},7 },{{{0 ,
8 }},135 },{{{0 ,8 }},71 },{{{0 ,9 }},239 },{{{80 ,7 }},9 },{{{0 ,8 }},95 },{{{0 ,8 }
},31 },{{{0 ,9 }},159 },{{{84 ,7 }},99 },{{{0 ,8 }},127 },{{{0 ,8 }},63 },{{{0 ,9 }}
,223 },{{{82 ,7 }},27 },{{{0 ,8 }},111 },{{{0 ,8 }},47 },{{{0 ,9 }},191 },{{{0 ,8 }}
,15 },{{{0 ,8 }},143 },{{{0 ,8 }},79 },{{{0 ,9 }},255 }};bb41 bb153 bb2267[]={{
{{80 ,5 }},1 },{{{87 ,5 }},257 },{{{83 ,5 }},17 },{{{91 ,5 }},4097 },{{{81 ,5 }},5 }
,{{{89 ,5 }},1025 },{{{85 ,5 }},65 },{{{93 ,5 }},16385 },{{{80 ,5 }},3 },{{{88 ,5 }
},513 },{{{84 ,5 }},33 },{{{92 ,5 }},8193 },{{{82 ,5 }},9 },{{{90 ,5 }},2049 },{{{
86 ,5 }},129 },{{{192 ,5 }},24577 },{{{80 ,5 }},2 },{{{87 ,5 }},385 },{{{83 ,5 }},
25 },{{{91 ,5 }},6145 },{{{81 ,5 }},7 },{{{89 ,5 }},1537 },{{{85 ,5 }},97 },{{{93 ,
5 }},24577 },{{{80 ,5 }},4 },{{{88 ,5 }},769 },{{{84 ,5 }},49 },{{{92 ,5 }},12289 }
,{{{82 ,5 }},13 },{{{90 ,5 }},3073 },{{{86 ,5 }},193 },{{{192 ,5 }},24577 }};
#endif
bbe bb1967(bb55,bb961,bb1017,bb1025,bby)bb165*bb55;bb165*bb961;bb153*
 *bb1017;bb153* *bb1025;bb17 bby;{(bbb)bby;
#ifdef bb2246
bbm(!bb2337){bbe bb3;bb7 bb19=0 ;bb165*bbo;bb165*bb437;bbm((bbo=(bb165
 * )( * ((bby)->bb401))((bby)->bb110,(288 ),(bb12(bb7))))==0 )bb2(-4 );
bbm((bb437=(bb165* )( * ((bby)->bb401))((bby)->bb110,(288 ),(bb12(bb7))))==
0 ){( * ((bby)->bb370))((bby)->bb110,(bb70)(bbo));bb2(-4 );}bb91(bb3=0 ;
bb3<144 ;bb3++)bbo[bb3]=8 ;bb91(;bb3<256 ;bb3++)bbo[bb3]=9 ;bb91(;bb3<280
;bb3++)bbo[bb3]=7 ;bb91(;bb3<288 ;bb3++)bbo[bb3]=8 ;bb2131=9 ;bb1975(bbo,
288 ,257 ,bb2373,bb2361,&bb2266,&bb2131,bb2428,&bb19,bb437);bb91(bb3=0 ;
bb3<30 ;bb3++)bbo[bb3]=5 ;bb2132=5 ;bb1975(bbo,30 ,0 ,bb2407,bb2408,&
bb2267,&bb2132,bb2428,&bb19,bb437);( * ((bby)->bb370))((bby)->bb110,(
bb70)(bb437));( * ((bby)->bb370))((bby)->bb110,(bb70)(bbo));bb2337=1 ;
}
#endif
 *bb55=bb2131; *bb961=bb2132; *bb1017=bb2266; *bb1025=bb2267;bb2 0 ;}
