/*
   'src_ipsec_pgpIPsecBuffer.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Wed Jan 15 12:08:55 2014
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
bba bb83 bb4;bb10{bb98=0 ,bb364=-12000 ,bb336=-11999 ,bb379=-11998 ,bb658
=-11997 ,bb811=-11996 ,bb717=-11995 ,bb871=-11994 ,bb780=-11992 ,bb713=-
11991 ,bb834=-11990 ,bb730=-11989 ,bb837=-11988 ,bb645=-11987 ,bb900=-
11986 ,bb752=-11985 ,bb687=-11984 ,bb813=-11983 ,bb648=-11982 ,bb844=-
11981 ,bb904=-11980 ,bb667=-11979 ,bb801=-11978 ,bb851=-11977 ,bb578=-
11976 ,bb782=-11975 ,bb762=-11960 ,bb803=-11959 ,bb677=-11500 ,bb725=-
11499 ,bb849=-11498 ,bb791=-11497 ,bb878=-11496 ,bb772=-11495 ,bb898=-
11494 ,bb769=-11493 ,bb843=-11492 ,bb887=-11491 ,bb865=-11490 ,bb727=-
11489 ,bb660=-11488 ,bb866=-11487 ,bb873=-11486 ,bb655=-11485 ,bb638=-
11484 ,bb905=-11483 ,bb830=-11482 ,bb617=-11481 ,bb691=-11480 ,bb757=-
11479 ,bb637=-11478 ,bb653=-11477 ,bb759=-11476 ,bb864=-11475 ,bb862=-
11474 ,bb706=-11473 ,bb695=-11472 ,bb635=-11460 ,bb840=-11450 ,bb729=-
11449 ,bb698=-11448 ,bb726=-11447 ,bb847=-11446 ,bb624=-11445 ,bb894=-
11444 ,bb701=-11443 ,bb694=-11440 ,bb781=-11439 ,bb774=-11438 ,bb793=-
11437 ,bb659=-11436 ,bb746=-11435 ,bb845=-11420 ,bb522=-11419 ,bb567=-
11418 ,bb673=-11417 ,bb627=-11416 ,bb775=-11415 ,bb788=-11414 ,bb724=-
11413 ,bb854=-11412 ,bb715=-11411 ,bb665=-11410 ,bb623=-11409 ,bb700=-
11408 ,bb897=-11407 ,bb907=-11406 ,bb688=-11405 ,bb666=-11404 ,bb639=-
11403 ,bb754=-11402 ,bb764=-11401 ,bb664=-11400 ,bb880=-11399 ,bb883=-
11398 ,bb756=-11397 ,bb670=-11396 ,bb875=-11395 ,bb671=-11394 ,bb827=-
11393 ,bb800=-11392 ,bb678=-11391 ,bb735=-11390 ,bb720=-11389 ,bb767=-
11388 ,bb903=-11387 ,bb901=-11386 ,bb733=-11385 ,bb690=-11384 ,bb829=-
11383 ,bb642=-11382 ,bb768=-11381 ,bb744=-11380 ,bb777=-11379 ,bb620=-
11378 ,bb745=-11377 ,bb795=-11376 ,bb749=-11375 ,bb650=-11374 ,bb841=-
11373 ,bb672=-11372 ,bb846=-11371 ,bb797=-11370 ,bb771=-11369 ,bb835=-
11368 ,bb750=-11367 ,bb852=-11366 ,bb751=-11365 ,bb842=-11364 ,bb807=-
11363 ,bb394=-11350 ,bb714=bb394,bb702=-11349 ,bb902=-11348 ,bb802=-11347
,bb693=-11346 ,bb640=-11345 ,bb884=-11344 ,bb805=-11343 ,bb708=-11342 ,
bb848=-11341 ,bb753=-11340 ,bb689=-11339 ,bb395=-11338 ,bb679=-11337 ,
bb748=bb395,bb705=-11330 ,bb810=-11329 ,bb681=-11328 ,bb785=-11327 ,bb761
=-11326 ,bb643=-11325 ,bb814=-11324 ,bb634=-11320 ,bb822=-11319 ,bb858=-
11318 ,bb737=-11317 ,bb618=-11316 ,bb839=-11315 ,bb821=-11314 ,bb716=-
11313 ,bb633=-11312 ,bb893=-11300 ,bb778=-11299 ,bb790=-11298 ,bb692=-
11297 ,bb668=-11296 ,bb863=-11295 ,bb819=-11294 ,bb649=-11293 ,bb685=-
11292 ,bb886=-11291 ,bb809=-11290 ,bb787=-11289 ,bb879=-11288 ,bb630=-
11287 ,bb789=-11286 ,bb647=-11285 ,bb816=-11284 ,bb806=-11283 ,bb704=-
11282 ,bb663=-11281 ,bb703=-11280 ,bb675=-11279 ,bb731=-11250 ,bb784=-
11249 ,bb652=-11248 ,bb741=-11247 ,bb654=-11246 ,bb891=-11245 ,bb696=-
11244 ,bb747=-11243 ,bb619=-11242 ,bb860=-11240 ,bb626=-11239 ,bb738=-
11238 ,bb783=-11237 ,bb684=-11150 ,bb686=-11100 ,bb831=-11099 ,bb836=-
11098 ,bb697=-11097 ,bb622=-11096 ,bb786=-11095 ,bb632=-11094 ,bb877=-
11093 ,bb828=-11092 ,bb896=-11091 ,bb798=-11090 ,bb874=-11089 ,bb832=-
11088 ,bb908=-11087 ,bb850=-11086 ,bb763=-11085 ,bb776=-11050 ,bb656=-
11049 ,bb876=-10999 ,bb758=-10998 ,bb680=-10997 ,bb743=-10996 ,bb888=-
10995 ,bb669=-10994 ,bb870=-10993 ,bb899=-10992 ,bb766=-10991 ,bb683=-
10990 ,bb616=-10989 ,bb794=-10988 ,bb710=-10979 ,bb856=-10978 ,bb629=-
10977 ,bb885=-10976 ,bb722=-10975 ,bb799=-10974 ,};bba bbi bb452{bb1 bb74
;bbd bb125;bbd bb181;bbi bb452*bb93;}bbx;bb4 bb472(bbx*bb824,bbd bb910
,bbx*bb857,bbd bb895,bbd bb539);bb4 bb524(bbx*bbj,bbd bb92,bbh bbb*
bb95,bbd bb47);bb4 bb576(bbx*bbj,bbd bb92,bbb*bb130,bbd bb47);bbu
bb823(bbx*bbj,bbd bb92,bbh bbb*bb95,bbd bb47);bb4 bb472(bbx*bb824,bbd
bb910,bbx*bb857,bbd bb895,bbd bb539){bbd bb169=0 ;bbd bb147=0 ;bbd bb156
=0 ;bbd bb570=0 ;bbd bb1855;bbd bb1923;bbx*bb73=bb90;bbx*bb46=bb90;bb4
bb18=bb98;bbm(!bb824||!bb857)bb2 bb364;bbm(!bb824->bb74||!bb857->bb74
)bb2 bb364;bb73=bb824;bb46=bb857;bb147=bb895;bb156=bb73->bb125;bb107(
bb156<bb910&&bb73){bb73=bb73->bb93;bb570=bb156;bb156+=bb73->bb125;}
bb169=bb910-bb570;bb570=0 ;bb156=bb46->bb181;bb107(bb156<bb895&&((bb18
)==bb98)){bbm(!bb46->bb93)bb18=bb379;bb54{bb46=bb46->bb93;bb570=bb156
;bb156+=bb46->bb181;}}bb147=bb895-bb570;bbm(&(bb73->bb74[bb169])==&(
bb46->bb74[bb147]))bb2 bb18;bb107(bb539>0 &&bb73&&((bb18)==bb98)){
bb1855=bb73->bb125-bb169;bb1923=bb46->bb181-bb147;bbm(bb1855>bb539)bb1855
=bb539;bbm(bb1923>bb539)bb1923=bb539;bbm(bb1855<=bb1923){bb81(&bb46->
bb74[bb147],&bb73->bb74[bb169],bb1855);bb73=bb73->bb93;bb169=0 ;bb147
+=bb1855;bb539-=bb1855;bbm(bb46->bb125<bb147)bb46->bb125=bb147;}bb54{
bbm(!bb46->bb93)bb18=bb379;bb54{bb81(&bb46->bb74[bb147],&bb73->bb74[
bb169],bb1923);bb46->bb125=bb46->bb181;bb46=bb46->bb93;bb147=0 ;bb169
+=bb1923;bb539-=bb1923;}}}bbm(((bb18)==bb98)&&(bb539>0 ))bb18=bb379;
bb2 bb18;}bb4 bb524(bbx*bbj,bbd bb92,bbh bbb*bb2511,bbd bb47){bbx bb95
;bb95.bb74=(bb1)bb2511;bb95.bb125=bb47;bb95.bb181=bb47;bb95.bb93=bb90
;bb2 bb472(&bb95,0 ,bbj,bb92,bb47);}bb4 bb576(bbx*bbj,bbd bb92,bbb*
bb2450,bbd bb47){bbx bb130;bb130.bb74=bb2450;bb130.bb125=0 ;bb130.
bb181=bb47;bb130.bb93=bb90;bb2 bb472(bbj,bb92,&bb130,0 ,bb47);}bbu
bb823(bbx*bbj,bbd bb92,bbh bbb*bb95,bbd bb47){bbd bb169=0 ;bbd bb147=0
;bbd bb156=0 ;bbd bb570=0 ;bbd bb1888;bbd bb1889;bbd bb2550=bb47;bbx*
bb73=bb90;bbm(!bbj)bb2 0 ;bbm(!bbj->bb74||!bb95)bb2 0 ;bb73=bbj;bb156=
bb73->bb125;bb107(bb156<bb92&&bb73){bb73=bb73->bb93;bb570=bb156;bb156
+=bb73->bb125;}bb169=bb92-bb570;bbm(&bb73->bb74[bb169]==bb95)bb2 1 ;
bb107(bb47&&bb73){bb1888=bb73->bb125-bb169;bb1889=bb2550-bb147;bbm(
bb1888>bb47)bb1888=bb47;bbm(bb1889>bb47)bb1889=bb47;bbm(bb1888<=
bb1889){bbm(bb1898(&bb73->bb74[bb169],(bb1)bb95+bb147,bb1888)!=0 )bb2 0
;bb73=bb73->bb93;bb169=0 ;bb147+=bb1888;bb47-=bb1888;}bb54{bbm(bb1898(
&bb73->bb74[bb169],(bb1)bb95+bb147,bb1889)!=0 )bb2 0 ;bb169+=bb1889;
bb47-=bb1889;bb21;}}bb2!bb47;}
