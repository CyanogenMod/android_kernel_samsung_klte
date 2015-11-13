/*
   'src_ipsec_pgpIPsecNATT.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Sun Nov 16 20:01:26 2014
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
bba bb10{bb403,bb1501,}bb297;bbk bb1214(bb297 bb866,bbh bbf*bb455);
bbd bb545(bb297 bb866,bbh bbf*bb455);bbb bb1173(bbk bb159,bb297 bb554
,bbf bb438[2 ]);bbb bb974(bbd bb159,bb297 bb554,bbf bb438[4 ]);
#define bb951 bb53(0x0800)
#define bb1141 bb53(0x0806)
#define bb952 bb53(0x01f4)
#define bb948 bb53(0x1194)
#define bb1104 bb53(0x4000)
#define bb1140 bb53(0x2000)
#define bb1111 bb53(0x1FFF)
#define bb1066( bb8) (( bb8) & bb53(0x2000 | 0x1FFF))
#define bb1025( bb8) ((( bb196( bb8)) & 0x1FFF) << 3)
#define bb979( bb8) ((( bb8) & bb53(0x1FFF)) == 0)
#define bb493( bb8) (( bb8) & bb53(0x2000))
#define bb1030( bb8) (!( bb493( bb8)))
#pragma pack(push, 1)
bba bbi{bbf bb371[6 ];bbf bb1011[6 ];bbk bb373;}bb364, *bb381;bba bbi{
bbf bb445[6 ];bbk bb373;}bb1085, *bb1093;bba bbi{bbf bb958:4 ;bbf bb1090
:4 ;bbf bb1073;bbk bb370;bbk bb895;bbk bb576;bbf bb1004;bbf bb247;bbk
bb612;bbd bb310;bbd bb204;}bb326, *bb315;bba bbi{bbk bb1035;bbk bb1043
;bbf bb1038;bbf bb1046;bbk bb1060;bbf bb1084[6 ];bbd bb1039;bbf bb1037
[6 ];bbd bb1064;}bb1074, *bb1080;
#pragma pack(pop)
bba bbi{bbk bb280;bbk bb425;bbk bb1009;bbk bb319;}bb412, *bb352;bba
bbi{bbk bb280;bbk bb579;bbd bb546;bbd bb924;bbf bb92;bbf bb170;bbk
bb158;bbk bb319;bbk bb1020;}bb490, *bb313;bba bbi{bbf bb1079;bbf
bb1069;bbf bb1063;bbf bb1040;bbd bb1062;bbk bb1075;bbk bb374;bbd
bb1033;bbd bb1056;bbd bb1065;bbd bb1059;bbf bb1088[16 ];bbf bb1076[64 ]
;bbf bb25[128 ];bbf bb1034[64 ];}bb1083, *bb1072;bba bbi{bbd bb310;bbd
bb204;bbf bb917;bbf bb247;bbk bb915;}bb601, *bb564;
#if defined( _WIN32)
#define bb53( bbc) (((( bbc) & 0XFF00) >> 8) | ((( bbc) & 0X00FF) <<  \
8))
#define bb196( bbc) ( bb53( bbc))
#define bb443( bbc) (((( bbc) & 0XFF000000) >> 24) | ((( bbc) &  \
0X00FF0000) >> 8) | ((( bbc) & 0X0000FF00) << 8) | ((( bbc) &  \
0X000000FF) << 24))
#define bb494( bbc) ( bb443( bbc))
#endif
bbk bb930(bbh bbb*bb301);bbk bb680(bbh bbb*bb513,bbe bb21);bba bb83
bb4;bb10{bb98=0 ,bb363=-12000 ,bb338=-11999 ,bb377=-11998 ,bb663=-11997 ,
bb704=-11996 ,bb717=-11995 ,bb683=-11994 ,bb781=-11992 ,bb784=-11991 ,
bb716=-11990 ,bb730=-11989 ,bb833=-11988 ,bb633=-11987 ,bb887=-11986 ,
bb635=-11985 ,bb692=-11984 ,bb622=-11983 ,bb652=-11982 ,bb841=-11981 ,
bb903=-11980 ,bb672=-11979 ,bb815=-11978 ,bb835=-11977 ,bb584=-11976 ,
bb853=-11975 ,bb758=-11960 ,bb629=-11959 ,bb681=-11500 ,bb706=-11499 ,
bb641=-11498 ,bb789=-11497 ,bb876=-11496 ,bb757=-11495 ,bb678=-11494 ,
bb768=-11493 ,bb837=-11492 ,bb902=-11491 ,bb761=-11490 ,bb728=-11489 ,
bb664=-11488 ,bb685=-11487 ,bb848=-11486 ,bb660=-11485 ,bb661=-11484 ,
bb901=-11483 ,bb898=-11482 ,bb733=-11481 ,bb838=-11480 ,bb754=-11479 ,
bb643=-11478 ,bb752=-11477 ,bb755=-11476 ,bb624=-11475 ,bb799=-11474 ,
bb772=-11473 ,bb800=-11472 ,bb638=-11460 ,bb821=-11450 ,bb699=-11449 ,
bb700=-11448 ,bb727=-11447 ,bb832=-11446 ,bb766=-11445 ,bb886=-11444 ,
bb628=-11443 ,bb801=-11440 ,bb779=-11439 ,bb774=-11438 ,bb791=-11437 ,
bb861=-11436 ,bb662=-11435 ,bb804=-11420 ,bb531=-11419 ,bb565=-11418 ,
bb677=-11417 ,bb858=-11416 ,bb809=-11415 ,bb786=-11414 ,bb726=-11413 ,
bb854=-11412 ,bb634=-11411 ,bb671=-11410 ,bb767=-11409 ,bb899=-11408 ,
bb697=-11407 ,bb906=-11406 ,bb657=-11405 ,bb711=-11404 ,bb656=-11403 ,
bb751=-11402 ,bb738=-11401 ,bb670=-11400 ,bb882=-11399 ,bb780=-11398 ,
bb753=-11397 ,bb675=-11396 ,bb630=-11395 ,bb829=-11394 ,bb856=-11393 ,
bb796=-11392 ,bb871=-11391 ,bb828=-11390 ,bb723=-11389 ,bb842=-11388 ,
bb703=-11387 ,bb900=-11386 ,bb693=-11385 ,bb694=-11384 ,bb803=-11383 ,
bb646=-11382 ,bb892=-11381 ,bb731=-11380 ,bb776=-11379 ,bb805=-11378 ,
bb742=-11377 ,bb794=-11376 ,bb748=-11375 ,bb810=-11374 ,bb808=-11373 ,
bb676=-11372 ,bb862=-11371 ,bb896=-11370 ,bb625=-11369 ,bb839=-11368 ,
bb746=-11367 ,bb707=-11366 ,bb714=-11365 ,bb843=-11364 ,bb647=-11363 ,
bb387=-11350 ,bb885=bb387,bb705=-11349 ,bb658=-11348 ,bb686=-11347 ,bb642
=-11346 ,bb644=-11345 ,bb877=-11344 ,bb684=-11343 ,bb881=-11342 ,bb826=-
11341 ,bb750=-11340 ,bb689=-11339 ,bb395=-11338 ,bb792=-11337 ,bb688=bb395
,bb777=-11330 ,bb807=-11329 ,bb844=-11328 ,bb775=-11327 ,bb749=-11326 ,
bb648=-11325 ,bb811=-11324 ,bb640=-11320 ,bb814=-11319 ,bb859=-11318 ,
bb715=-11317 ,bb627=-11316 ,bb713=-11315 ,bb620=-11314 ,bb718=-11313 ,
bb637=-11312 ,bb639=-11300 ,bb771=-11299 ,bb745=-11298 ,bb696=-11297 ,
bb668=-11296 ,bb797=-11295 ,bb894=-11294 ,bb653=-11293 ,bb890=-11292 ,
bb666=-11291 ,bb619=-11290 ,bb709=-11289 ,bb874=-11288 ,bb631=-11287 ,
bb787=-11286 ,bb651=-11285 ,bb813=-11284 ,bb872=-11283 ,bb698=-11282 ,
bb695=-11281 ,bb708=-11280 ,bb818=-11279 ,bb732=-11250 ,bb830=-11249 ,
bb849=-11248 ,bb736=-11247 ,bb655=-11246 ,bb701=-11245 ,bb868=-11244 ,
bb743=-11243 ,bb621=-11242 ,bb802=-11240 ,bb649=-11239 ,bb724=-11238 ,
bb783=-11237 ,bb820=-11150 ,bb691=-11100 ,bb836=-11099 ,bb744=-11098 ,
bb864=-11097 ,bb793=-11096 ,bb785=-11095 ,bb759=-11094 ,bb617=-11093 ,
bb825=-11092 ,bb673=-11091 ,bb762=-11090 ,bb870=-11089 ,bb845=-11088 ,
bb908=-11087 ,bb831=-11086 ,bb712=-11085 ,bb893=-11050 ,bb740=-11049 ,
bb682=-10999 ,bb897=-10998 ,bb888=-10997 ,bb741=-10996 ,bb904=-10995 ,
bb674=-10994 ,bb880=-10993 ,bb846=-10992 ,bb636=-10991 ,bb618=-10990 ,
bb770=-10989 ,bb616=-10988 ,bb883=-10979 ,bb857=-10978 ,bb875=-10977 ,
bb878=-10976 ,bb734=-10975 ,bb798=-10974 ,};bba bbi bb452{bb1 bb74;bbd
bb125;bbd bb181;bbi bb452*bb94;}bbx;bb4 bb464(bbx*bb669,bbd bb911,bbx
 *bb869,bbd bb823,bbd bb541);bb4 bb524(bbx*bbj,bbd bb92,bbh bbb*bb96,
bbd bb47);bb4 bb575(bbx*bbj,bbd bb92,bbb*bb130,bbd bb47);bbu bb819(
bbx*bbj,bbd bb92,bbh bbb*bb96,bbd bb47);bb4 bb596(bbx*bb86,bbf bb102,
bbx*bb58);bb4 bb679(bbx*bb86,bbu bb177,bbf*bb410);bb4 bb940(bbx*bb58,
bbf*bb386);bb4 bb957(bbh bbf*bb386,bbx*bb58);bb4 bb537(bbx*bb51,bbf
bb102,bbd*bb943);bb4 bb925(bbx*bb86,bbf bb102,bbf bb410,bbx*bb58);bbd
bb519(bbx*bb51);bbk bb544(bbx*bb51);bbb bb522(bbk bb151,bbx*bb51);bbb
bb540(bbx*bb51);bbb bb977(bbx*bb51,bbd*bb27);bbb bb1002(bbx*bb51,bbd*
bb27);bbb bb994(bbx*bb51,bbd bb27);bbb bb927(bbx*bb51,bbd bb27);bbb
bb985(bbx*bb51);bbu bb1018(bbf*bb51);bb10{bb1127=-5000 ,bb1108=-4000 ,
bb998=-4999 ,bb988=-4998 ,bb1017=-4997 ,bb981=-4996 ,bb1094=-4995 ,bb1087=
-4994 ,bb1100=-4993 ,bb1015=-4992 ,bb1081=-4991 };bb4 bb1133(bb4 bb1137,
bbd bb1119,bbl*bb1102);bba bbi bb1019*bb989;bba bbi bb1027*bb1029;bba
bbi bb993*bb1026;bba bbi bb1001*bb1016;bba bbi bb1024*bb1022;bba bbi
bb990*bb987;bba bb10{bb551=0 ,bb578=1 ,bb589=2 ,bb756=3 ,bb587=4 ,bb563=5 ,
bb572=6 ,bb573=7 ,bb592=9 ,}bb421;bba bb10{bb615=0 ,bb991,bb600,bb1014,
bb910,bb926,bb909,bb920,bb928,bb929,bb918,}bb517;bbu bb2135(bbx*bb298
);bbu bb2193(bbx*bb298);bb4 bb2060(bbx*bb298,bbd*bb104);bb4 bb2010(
bbx*bb298,bbd*bb104);bb4 bb1846(bbx*bb86,bbx*bb58,bbu bb1058,bbk
bb2120,bbk bb1813);bb4 bb1861(bbx*bb86,bbx*bb58,bbu bb1058);bb41 bbf
bb2022[8 ]={0 };bbu bb2135(bbx*bb298){bbd bb368;bb4 bb18=bb537(bb298,17
,&bb368);bb2((bb18)==bb98)&&bb544(bb298)==bb368+bb12(bb412)+1 ;}bbu
bb2193(bbx*bb298){bbd bb368;bb4 bb18=bb537(bb298,17 ,&bb368);bb2((bb18
)==bb98)&&bb819(bb298,bb368+bb12(bb412),bb2022,bb12(bb2022));}bb4
bb2060(bbx*bb298,bbd*bb104){bbd bb368;bbf bb74[8 ];bb4 bb18; *bb104=0 ;
bb18=bb537(bb298,17 ,&bb368);bbm(((bb18)!=bb98))bb2 bb18;bb368+=bb12(
bb412);bbm(!bb819(bb298,bb368,bb2022,bb12(bb2022)))bb2 bb18;bb368+=8 ;
bbm(bb298->bb125<bb368+8 )bb2 bb18;bb575(bb298,bb368,bb74,8 ); *bb104=
bb545(bb403,&bb74[0 ]);bb2 bb18;}bb4 bb2010(bbx*bb298,bbd*bb104){bbd
bb368;bbf bb74[8 ];bb4 bb18; *bb104=0 ;bb18=bb537(bb298,17 ,&bb368);bbm(
((bb18)!=bb98))bb2 bb18;bb368+=bb12(bb412);bbm(bb298->bb125<bb368+8 )bb2
bb18;bb575(bb298,bb368,bb74,8 ); *bb104=bb545(bb403,&bb74[0 ]);bb2 bb18
;}bb4 bb1846(bbx*bb86,bbx*bb58,bbu bb1058,bbk bb2120,bbk bb1813){bb4
bb18=bb98;bbd bb1184;bbk bb151;bb412 bb2097;bb151=bb544(bb86);bb1184=
bb519(bb86);bb18=bb596(bb86,17 ,bb58);bbm(((bb18)!=bb98))bb99 bb1833;
bb18=bb464(bb86,bb1184,bb58,bb1184+bb12(bb412)+(bb1058?8 :0 ),bb151-
bb1184);bbm(((bb18)!=bb98))bb99 bb1833;bb2097.bb280=bb2120;bb2097.
bb425=bb1813;bb2097.bb1009=bb53(bb151-bb1184+bb12(bb412)+(bb1058?8 :0 ));
bb2097.bb319=0 ;bb18=bb524(bb58,bb1184,&bb2097,bb12(bb412));bbm(((bb18
)!=bb98))bb99 bb1833;bb151+=bb12(bb412);bbm(bb1058){bb18=bb524(bb58,
bb1184+bb12(bb412),bb2022,bb12(bb2022));bbm(((bb18)!=bb98))bb99 bb1833
;bb151+=8 ;}bb522(bb151,bb58);bb540(bb58);bb1833:bb2 bb18;}bb4 bb1861(
bbx*bb86,bbx*bb58,bbu bb1058){bb4 bb18=bb98;bbd bb1184;bbk bb151;bbf
bb410;bb151=bb544(bb86);bb1184=bb519(bb86);bbm(bb151<bb1184+bb12(
bb412)+(bb1058?8 :0 )){bb18=bb1015;bb99 bb1833;}bb679(bb86,0 ,&bb410);
bbm(bb410==17 ){bb18=bb596(bb86,50 ,bb58);bbm(((bb18)!=bb98))bb99 bb1833
;bb18=bb464(bb86,bb1184+bb12(bb412)+(bb1058?8 :0 ),bb58,bb1184,bb151-
bb1184-bb12(bb412)-(bb1058?8 :0 ));bbm(((bb18)!=bb98))bb99 bb1833;bb151
-=(bb12(bb412)+(bb1058?8 :0 ));bb522(bb151,bb58);bb540(bb58);}bb54{bb18
=bb464(bb86,0 ,bb58,0 ,bb151);}bb1833:bb2 bb18;}
