/*
   'src_compress_LZS_pgpCompLZS.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Sun Nov 16 20:01:26 2014
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
bba bbi bb1019*bb989;bba bbi bb1027*bb1029;bba bbi bb993*bb1026;bba
bbi bb1001*bb1016;bba bbi bb1024*bb1022;bba bbi bb990*bb987;bba bb10{
bb551=0 ,bb578=1 ,bb589=2 ,bb756=3 ,bb587=4 ,bb563=5 ,bb572=6 ,bb573=7 ,bb592
=9 ,}bb421;bba bb10{bb615=0 ,bb991,bb600,bb1014,bb910,bb926,bb909,bb920
,bb928,bb929,bb918,}bb517;bba bb83 bb4;bb10{bb98=0 ,bb363=-12000 ,bb338
=-11999 ,bb377=-11998 ,bb663=-11997 ,bb704=-11996 ,bb717=-11995 ,bb683=-
11994 ,bb781=-11992 ,bb784=-11991 ,bb716=-11990 ,bb730=-11989 ,bb833=-
11988 ,bb633=-11987 ,bb887=-11986 ,bb635=-11985 ,bb692=-11984 ,bb622=-
11983 ,bb652=-11982 ,bb841=-11981 ,bb903=-11980 ,bb672=-11979 ,bb815=-
11978 ,bb835=-11977 ,bb584=-11976 ,bb853=-11975 ,bb758=-11960 ,bb629=-
11959 ,bb681=-11500 ,bb706=-11499 ,bb641=-11498 ,bb789=-11497 ,bb876=-
11496 ,bb757=-11495 ,bb678=-11494 ,bb768=-11493 ,bb837=-11492 ,bb902=-
11491 ,bb761=-11490 ,bb728=-11489 ,bb664=-11488 ,bb685=-11487 ,bb848=-
11486 ,bb660=-11485 ,bb661=-11484 ,bb901=-11483 ,bb898=-11482 ,bb733=-
11481 ,bb838=-11480 ,bb754=-11479 ,bb643=-11478 ,bb752=-11477 ,bb755=-
11476 ,bb624=-11475 ,bb799=-11474 ,bb772=-11473 ,bb800=-11472 ,bb638=-
11460 ,bb821=-11450 ,bb699=-11449 ,bb700=-11448 ,bb727=-11447 ,bb832=-
11446 ,bb766=-11445 ,bb886=-11444 ,bb628=-11443 ,bb801=-11440 ,bb779=-
11439 ,bb774=-11438 ,bb791=-11437 ,bb861=-11436 ,bb662=-11435 ,bb804=-
11420 ,bb531=-11419 ,bb565=-11418 ,bb677=-11417 ,bb858=-11416 ,bb809=-
11415 ,bb786=-11414 ,bb726=-11413 ,bb854=-11412 ,bb634=-11411 ,bb671=-
11410 ,bb767=-11409 ,bb899=-11408 ,bb697=-11407 ,bb906=-11406 ,bb657=-
11405 ,bb711=-11404 ,bb656=-11403 ,bb751=-11402 ,bb738=-11401 ,bb670=-
11400 ,bb882=-11399 ,bb780=-11398 ,bb753=-11397 ,bb675=-11396 ,bb630=-
11395 ,bb829=-11394 ,bb856=-11393 ,bb796=-11392 ,bb871=-11391 ,bb828=-
11390 ,bb723=-11389 ,bb842=-11388 ,bb703=-11387 ,bb900=-11386 ,bb693=-
11385 ,bb694=-11384 ,bb803=-11383 ,bb646=-11382 ,bb892=-11381 ,bb731=-
11380 ,bb776=-11379 ,bb805=-11378 ,bb742=-11377 ,bb794=-11376 ,bb748=-
11375 ,bb810=-11374 ,bb808=-11373 ,bb676=-11372 ,bb862=-11371 ,bb896=-
11370 ,bb625=-11369 ,bb839=-11368 ,bb746=-11367 ,bb707=-11366 ,bb714=-
11365 ,bb843=-11364 ,bb647=-11363 ,bb387=-11350 ,bb885=bb387,bb705=-11349
,bb658=-11348 ,bb686=-11347 ,bb642=-11346 ,bb644=-11345 ,bb877=-11344 ,
bb684=-11343 ,bb881=-11342 ,bb826=-11341 ,bb750=-11340 ,bb689=-11339 ,
bb395=-11338 ,bb792=-11337 ,bb688=bb395,bb777=-11330 ,bb807=-11329 ,bb844
=-11328 ,bb775=-11327 ,bb749=-11326 ,bb648=-11325 ,bb811=-11324 ,bb640=-
11320 ,bb814=-11319 ,bb859=-11318 ,bb715=-11317 ,bb627=-11316 ,bb713=-
11315 ,bb620=-11314 ,bb718=-11313 ,bb637=-11312 ,bb639=-11300 ,bb771=-
11299 ,bb745=-11298 ,bb696=-11297 ,bb668=-11296 ,bb797=-11295 ,bb894=-
11294 ,bb653=-11293 ,bb890=-11292 ,bb666=-11291 ,bb619=-11290 ,bb709=-
11289 ,bb874=-11288 ,bb631=-11287 ,bb787=-11286 ,bb651=-11285 ,bb813=-
11284 ,bb872=-11283 ,bb698=-11282 ,bb695=-11281 ,bb708=-11280 ,bb818=-
11279 ,bb732=-11250 ,bb830=-11249 ,bb849=-11248 ,bb736=-11247 ,bb655=-
11246 ,bb701=-11245 ,bb868=-11244 ,bb743=-11243 ,bb621=-11242 ,bb802=-
11240 ,bb649=-11239 ,bb724=-11238 ,bb783=-11237 ,bb820=-11150 ,bb691=-
11100 ,bb836=-11099 ,bb744=-11098 ,bb864=-11097 ,bb793=-11096 ,bb785=-
11095 ,bb759=-11094 ,bb617=-11093 ,bb825=-11092 ,bb673=-11091 ,bb762=-
11090 ,bb870=-11089 ,bb845=-11088 ,bb908=-11087 ,bb831=-11086 ,bb712=-
11085 ,bb893=-11050 ,bb740=-11049 ,bb682=-10999 ,bb897=-10998 ,bb888=-
10997 ,bb741=-10996 ,bb904=-10995 ,bb674=-10994 ,bb880=-10993 ,bb846=-
10992 ,bb636=-10991 ,bb618=-10990 ,bb770=-10989 ,bb616=-10988 ,bb883=-
10979 ,bb857=-10978 ,bb875=-10977 ,bb878=-10976 ,bb734=-10975 ,bb798=-
10974 ,};bb10{bb555=1 ,};bbb*bb498(bbd bb1221,bbd bb374);bb4 bb461(bbb*
bb971);bba bbi bb1986 bb1972, *bb382;bba bb10{bb1994=0 ,bb1753=1 ,
bb1767=2 }bb790;bb4 bb1814(bb790 bb1872,bb382*bb359);bb4 bb1949(bb382
bb359,bbf*bb435,bbd bb418,bbf*bb309,bbd bb293,bbd*bb441,bbd*bb307);
bb4 bb1942(bb382 bb359,bbf*bb309,bbd bb293,bbd*bb307,bbu*bb973);bb4
bb1950(bb382 bb359,bbf*bb435,bbd bb418,bbf*bb309,bbd bb293,bbd*bb441,
bbd*bb307,bbu*bb962);bb4 bb1799(bb382 bb359);bb4 bb2206(bb77*bb162);
bb4 bb2294(bb77 bb162,bbf*bb435,bbd bb418,bbf*bb309,bbd bb293,bbd*
bb441,bbd*bb307);bb4 bb2289(bb77 bb162,bbf*bb309,bbd bb293,bbd*bb307,
bbu*bb973);bb4 bb2243(bb77*bb162);bb4 bb2300(bb77*bb162);bb4 bb2205(
bb77 bb162,bbf*bb435,bbd bb418,bbf*bb309,bbd bb293,bbd*bb441,bbd*
bb307,bbu*bb962);bb4 bb2284(bb77*bb162);bba bbi bb1864 bb1864;bba bbi
bb1864*bb474;bbd bb2195(bbb);bbb bb2137(bb474 bb0,bbb*bb1315);bbk
bb2175(bb474 bb0,bbf* *bb1739,bbf* *bb1733,bbd*bb916,bbd*bb607,bbb*
bb1315,bbk bb374,bbk bb2159);bbk bb2293(bb474 bb0,bbf* *bb1739,bbf* *
bb1733,bbd*bb916,bbd*bb607,bbb*bb1315,bbk bb374);bba bbi{bb474 bb0;
bbf*bb1309;}bb2312, *bb1156;bb4 bb2206(bb77*bb162){bb1156 bb431;bb4
bb18=bb98;bbm(!bb162)bb2 bb363; *bb162=bb90;bb431=(bb1156)bb498(bb12(
bb2312),bb555);bbm(!bb431)bb2 bb338;bb431->bb0=(bb474)bb498(bb2195(),
bb555);bbm(!bb431->bb0){bb461(bb431);bb2 bb338;}bb431->bb1309=(bbf* )bb498
(24760 ,bb555);bbm(!bb431->bb1309){bb461(bb431->bb0);bb461(bb431);bb2
bb338;}bb2137(bb431->bb0,bb431->bb1309); *bb162=bb431;bb2 bb18;}bb4
bb2294(bb77 bb162,bbf*bb435,bbd bb418,bbf*bb309,bbd bb293,bbd*bb441,
bbd*bb307){bb1156 bb431;bbk bb1781;bbd bb916;bbd bb607;bbf*bb1827;bbk
bb2229=2 <<3 ;bbk bb2264=200 ;bb4 bb18=bb98;bb431=(bb1156)bb162;bbm(
bb293<=15 )bb2 bb377;bb916=bb418;bb607=bb293;bb1827=bb309;bb1781=
bb2175(bb431->bb0,&bb435,&bb1827,&bb916,&bb607,bb431->bb1309,bb2229,
bb2264);bbm(bb1781==0 )bb18=bb584;bb54{ *bb441=bb418-bb916; *bb307=
bb293-bb607;}bb2 bb18;}bb4 bb2289(bb77 bb162,bbf*bb309,bbd bb293,bbd*
bb307,bbu*bb973){bb1156 bb431;bbk bb1781;bbd bb916;bbd bb607;bbf*
bb1827;bbf*bb2469=bb90;bbk bb2229=2 <<3 ;bbk bb2264=200 ;bb4 bb18=bb98;
bb431=(bb1156)bb162;bbm(bb293<=15 )bb2 bb377;bb916=0 ;bb607=bb293;
bb1827=bb309;bb1781=bb2175(bb431->bb0,&bb2469,&bb1827,&bb916,&bb607,
bb431->bb1309,(bbk)(0x01 |bb2229),bb2264); *bb307=bb293-bb607;bbm(
bb1781&2 ) *bb973=1 ;bb2 bb18;}bb4 bb2243(bb77*bb162){bb4 bb18=bb98;bbm
(!bb162)bb2 bb363;bb461(((bb1156) *bb162)->bb1309);bb461(((bb1156) *
bb162)->bb0);bb461( *bb162); *bb162=bb90;bb2 bb18;}bb4 bb2300(bb77*
bb162){bb1156 bb431;bb4 bb18=bb98;bbm(!bb162)bb2 bb363; *bb162=bb90;
bb431=(bb1156)bb498(bb12(bb2312),bb555);bbm(!bb431)bb2 bb338;bb431->
bb0=(bb474)bb498(bb2195(),bb555);bbm(!bb431->bb0){bb461(bb431);bb2
bb338;}bb431->bb1309=(bbf* )bb498(24760 ,bb555);bbm(!bb431->bb1309){
bb461(bb431->bb0);bb461(bb431);bb2 bb338;}bb2137(bb431->bb0,bb431->
bb1309); *bb162=bb431;bb2 bb18;}bb4 bb2205(bb77 bb162,bbf*bb435,bbd
bb418,bbf*bb309,bbd bb293,bbd*bb441,bbd*bb307,bbu*bb962){bb1156 bb431
;bbk bb1781;bbd bb916;bbd bb607;bbf*bb1827;bb4 bb18=bb98;bb431=(
bb1156)bb162;bb916=bb418;bb607=bb293;bb1827=bb309;bb1781=bb2293(bb431
->bb0,&bb435,&bb1827,&bb916,&bb607,bb431->bb1309,0 ); *bb441=bb418-
bb916; *bb307=bb293-bb607;bbm((bb1781&4 )&&!(bb1781&2 )) *bb962=1 ;bb2
bb18;}bb4 bb2284(bb77*bb162){bb4 bb18=bb98;bbm(!bb162)bb2 bb363;bb461
(((bb1156) *bb162)->bb1309);bb461(((bb1156) *bb162)->bb0);bb461( *
bb162); *bb162=bb90;bb2 bb18;}
