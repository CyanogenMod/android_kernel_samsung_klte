/*
   'src_pm_pgpNetPMSA.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Wed Jan 15 12:08:55 2014
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
#define bb956 bb53(0x0800)
#define bb1140 bb53(0x0806)
#define bb937 bb53(0x01f4)
#define bb939 bb53(0x1194)
#define bb1134 bb53(0x4000)
#define bb1117 bb53(0x2000)
#define bb1108 bb53(0x1FFF)
#define bb1067( bb8) (( bb8) & bb53(0x2000 | 0x1FFF))
#define bb993( bb8) ((( bb195( bb8)) & 0x1FFF) << 3)
#define bb979( bb8) ((( bb8) & bb53(0x1FFF)) == 0)
#define bb496( bb8) (( bb8) & bb53(0x2000))
#define bb988( bb8) (!( bb496( bb8)))
#pragma pack(push, 1)
bba bbi{bbf bb369[6 ];bbf bb1008[6 ];bbk bb375;}bb365, *bb376;bba bbi{
bbf bb444[6 ];bbk bb375;}bb1084, *bb1093;bba bbi{bbf bb938:4 ;bbf bb1089
:4 ;bbf bb1055;bbk bb367;bbk bb892;bbk bb566;bbf bb1002;bbf bb283;bbk
bb614;bbd bb309;bbd bb203;}bb326, *bb318;bba bbi{bbk bb1035;bbk bb1083
;bbf bb1038;bbf bb1046;bbk bb1063;bbf bb1082[6 ];bbd bb1039;bbf bb1092
[6 ];bbd bb1090;}bb1075, *bb1064;
#pragma pack(pop)
bba bbi{bbk bb218;bbk bb424;bbk bb1005;bbk bb322;}bb415, *bb346;bba
bbi{bbk bb218;bbk bb591;bbd bb543;bbd bb923;bbf bb92;bbf bb172;bbk
bb158;bbk bb322;bbk bb1018;}bb483, *bb313;bba bbi{bbf bb1078;bbf
bb1070;bbf bb1088;bbf bb1040;bbd bb1065;bbk bb1050;bbk bb373;bbd
bb1033;bbd bb1079;bbd bb1066;bbd bb1062;bbf bb1085[16 ];bbf bb1052[64 ]
;bbf bb25[128 ];bbf bb1034[64 ];}bb1045, *bb1074;bba bbi{bbd bb309;bbd
bb203;bbf bb918;bbf bb283;bbk bb914;}bb610, *bb560;
#if defined( _WIN32)
#define bb53( bbc) (((( bbc) & 0XFF00) >> 8) | ((( bbc) & 0X00FF) <<  \
8))
#define bb195( bbc) ( bb53( bbc))
#define bb445( bbc) (((( bbc) & 0XFF000000) >> 24) | ((( bbc) &  \
0X00FF0000) >> 8) | ((( bbc) & 0X0000FF00) << 8) | ((( bbc) &  \
0X000000FF) << 24))
#define bb493( bbc) ( bb445( bbc))
#endif
bbk bb928(bbh bbb*bb297);bbk bb859(bbh bbb*bb510,bbe bb22);bba bb83
bb4;bb10{bb98=0 ,bb364=-12000 ,bb336=-11999 ,bb379=-11998 ,bb658=-11997 ,
bb811=-11996 ,bb717=-11995 ,bb871=-11994 ,bb780=-11992 ,bb713=-11991 ,
bb834=-11990 ,bb730=-11989 ,bb837=-11988 ,bb645=-11987 ,bb900=-11986 ,
bb752=-11985 ,bb687=-11984 ,bb813=-11983 ,bb648=-11982 ,bb844=-11981 ,
bb904=-11980 ,bb667=-11979 ,bb801=-11978 ,bb851=-11977 ,bb578=-11976 ,
bb782=-11975 ,bb762=-11960 ,bb803=-11959 ,bb677=-11500 ,bb725=-11499 ,
bb849=-11498 ,bb791=-11497 ,bb878=-11496 ,bb772=-11495 ,bb898=-11494 ,
bb769=-11493 ,bb843=-11492 ,bb887=-11491 ,bb865=-11490 ,bb727=-11489 ,
bb660=-11488 ,bb866=-11487 ,bb873=-11486 ,bb655=-11485 ,bb638=-11484 ,
bb905=-11483 ,bb830=-11482 ,bb617=-11481 ,bb691=-11480 ,bb757=-11479 ,
bb637=-11478 ,bb653=-11477 ,bb759=-11476 ,bb864=-11475 ,bb862=-11474 ,
bb706=-11473 ,bb695=-11472 ,bb635=-11460 ,bb840=-11450 ,bb729=-11449 ,
bb698=-11448 ,bb726=-11447 ,bb847=-11446 ,bb624=-11445 ,bb894=-11444 ,
bb701=-11443 ,bb694=-11440 ,bb781=-11439 ,bb774=-11438 ,bb793=-11437 ,
bb659=-11436 ,bb746=-11435 ,bb845=-11420 ,bb522=-11419 ,bb567=-11418 ,
bb673=-11417 ,bb627=-11416 ,bb775=-11415 ,bb788=-11414 ,bb724=-11413 ,
bb854=-11412 ,bb715=-11411 ,bb665=-11410 ,bb623=-11409 ,bb700=-11408 ,
bb897=-11407 ,bb907=-11406 ,bb688=-11405 ,bb666=-11404 ,bb639=-11403 ,
bb754=-11402 ,bb764=-11401 ,bb664=-11400 ,bb880=-11399 ,bb883=-11398 ,
bb756=-11397 ,bb670=-11396 ,bb875=-11395 ,bb671=-11394 ,bb827=-11393 ,
bb800=-11392 ,bb678=-11391 ,bb735=-11390 ,bb720=-11389 ,bb767=-11388 ,
bb903=-11387 ,bb901=-11386 ,bb733=-11385 ,bb690=-11384 ,bb829=-11383 ,
bb642=-11382 ,bb768=-11381 ,bb744=-11380 ,bb777=-11379 ,bb620=-11378 ,
bb745=-11377 ,bb795=-11376 ,bb749=-11375 ,bb650=-11374 ,bb841=-11373 ,
bb672=-11372 ,bb846=-11371 ,bb797=-11370 ,bb771=-11369 ,bb835=-11368 ,
bb750=-11367 ,bb852=-11366 ,bb751=-11365 ,bb842=-11364 ,bb807=-11363 ,
bb394=-11350 ,bb714=bb394,bb702=-11349 ,bb902=-11348 ,bb802=-11347 ,bb693
=-11346 ,bb640=-11345 ,bb884=-11344 ,bb805=-11343 ,bb708=-11342 ,bb848=-
11341 ,bb753=-11340 ,bb689=-11339 ,bb395=-11338 ,bb679=-11337 ,bb748=bb395
,bb705=-11330 ,bb810=-11329 ,bb681=-11328 ,bb785=-11327 ,bb761=-11326 ,
bb643=-11325 ,bb814=-11324 ,bb634=-11320 ,bb822=-11319 ,bb858=-11318 ,
bb737=-11317 ,bb618=-11316 ,bb839=-11315 ,bb821=-11314 ,bb716=-11313 ,
bb633=-11312 ,bb893=-11300 ,bb778=-11299 ,bb790=-11298 ,bb692=-11297 ,
bb668=-11296 ,bb863=-11295 ,bb819=-11294 ,bb649=-11293 ,bb685=-11292 ,
bb886=-11291 ,bb809=-11290 ,bb787=-11289 ,bb879=-11288 ,bb630=-11287 ,
bb789=-11286 ,bb647=-11285 ,bb816=-11284 ,bb806=-11283 ,bb704=-11282 ,
bb663=-11281 ,bb703=-11280 ,bb675=-11279 ,bb731=-11250 ,bb784=-11249 ,
bb652=-11248 ,bb741=-11247 ,bb654=-11246 ,bb891=-11245 ,bb696=-11244 ,
bb747=-11243 ,bb619=-11242 ,bb860=-11240 ,bb626=-11239 ,bb738=-11238 ,
bb783=-11237 ,bb684=-11150 ,bb686=-11100 ,bb831=-11099 ,bb836=-11098 ,
bb697=-11097 ,bb622=-11096 ,bb786=-11095 ,bb632=-11094 ,bb877=-11093 ,
bb828=-11092 ,bb896=-11091 ,bb798=-11090 ,bb874=-11089 ,bb832=-11088 ,
bb908=-11087 ,bb850=-11086 ,bb763=-11085 ,bb776=-11050 ,bb656=-11049 ,
bb876=-10999 ,bb758=-10998 ,bb680=-10997 ,bb743=-10996 ,bb888=-10995 ,
bb669=-10994 ,bb870=-10993 ,bb899=-10992 ,bb766=-10991 ,bb683=-10990 ,
bb616=-10989 ,bb794=-10988 ,bb710=-10979 ,bb856=-10978 ,bb629=-10977 ,
bb885=-10976 ,bb722=-10975 ,bb799=-10974 ,};bba bbi bb452{bb1 bb74;bbd
bb125;bbd bb181;bbi bb452*bb93;}bbx;bb4 bb472(bbx*bb824,bbd bb910,bbx
 *bb857,bbd bb895,bbd bb539);bb4 bb524(bbx*bbj,bbd bb92,bbh bbb*bb95,
bbd bb47);bb4 bb576(bbx*bbj,bbd bb92,bbb*bb130,bbd bb47);bbu bb823(
bbx*bbj,bbd bb92,bbh bbb*bb95,bbd bb47);bb4 bb596(bbx*bb87,bbf bb102,
bbx*bb58);bb4 bb674(bbx*bb87,bbu bb177,bbf*bb408);bb4 bb940(bbx*bb58,
bbf*bb397);bb4 bb958(bbh bbf*bb397,bbx*bb58);bb4 bb541(bbx*bb51,bbf
bb102,bbd*bb944);bb4 bb929(bbx*bb87,bbf bb102,bbf bb408,bbx*bb58);bbd
bb517(bbx*bb51);bbk bb536(bbx*bb51);bbb bb526(bbk bb151,bbx*bb51);bbb
bb545(bbx*bb51);bbb bb978(bbx*bb51,bbd*bb26);bbb bb1001(bbx*bb51,bbd*
bb26);bbb bb991(bbx*bb51,bbd bb26);bbb bb925(bbx*bb51,bbd bb26);bbb
bb984(bbx*bb51);bbu bb1016(bbf*bb51);bba bbi bb1010*bb1026;bba bbi
bb1029*bb1006;bba bbi bb994*bb1027;bba bbi bb1028*bb1015;bba bbi bb999
 *bb1022;bba bbi bb1019*bb987;bba bb10{bb552=0 ,bb594=1 ,bb584=2 ,bb755=
3 ,bb581=4 ,bb561=5 ,bb575=6 ,bb563=7 ,bb586=9 ,}bb418;bba bb10{bb601=0 ,
bb992,bb603,bb1012,bb909,bb921,bb920,bb919,bb927,bb926,bb913,}bb515;
#pragma pack(push, 8)
#ifdef _MSC_VER
#pragma warning (disable:4200)
#endif
bba bbf bb178[4 ];bba bb10{bb1655=0 ,bb1471=1 ,}bb1395;bba bb10{bb1531=0
,bb1721=1 ,bb1562=2 ,bb1443=3 ,bb1663=4 ,bb1496=5 ,bb1639=6 ,bb1519=7 ,
bb1608=8 ,bb1522=9 ,bb1683=10 ,bb1512=11 ,bb1698=12 ,bb1713=13 ,bb1720=14 ,
bb1427=15 ,bb1458=16 ,bb1397=17 ,bb1601=18 ,bb1694=19 ,bb1646=20 ,bb1587=21
,bb1510=22 ,bb1478=23 ,bb1604=24 ,bb1607=25 ,bb1454=26 ,bb1583=27 ,bb1378=
28 ,bb1707=29 ,bb1692=30 ,bb1575=16300 ,bb1617=16301 ,bb1729=16384 ,bb1541=
24576 ,bb1469=24577 ,bb1453=24578 ,bb1482=34793 ,bb1384=40500 ,}bb625;bba
bb10{bb1466=0 ,bb1527=1 ,bb1461=2 ,bb1430=3 ,bb1702=4 ,bb1391=5 ,bb1674=6 ,
bb1479=7 ,bb1533=8 ,bb1402=9 ,bb1447=21 ,bb1493=22 ,bb1502=23 ,bb1451=24 ,
bb1544=25 ,bb1513=26 ,bb1467=27 ,bb1387=28 ,bb1483=29 ,bb1494=80 ,}bb765;
bba bb10{bb1641=0 ,bb1701=1 ,bb1697=2 ,bb1489=3 ,bb1524=4 ,}bb1628;bba bb10
{bb1609=0 ,bb1347=1 ,bb1164=2 ,bb1220=3 ,bb1290=4 ,bb1054=61440 ,bb1359=
61441 ,bb1114=61443 ,bb1299=61444 ,}bb482;bba bb10{bb1703=0 ,bb1499=1 ,
bb1564=2 ,}bb1686;bba bb10{bb1618=0 ,bb1726,bb1444,bb1459,bb1568,bb1501
,bb1640,bb1470,bb1528,bb1497,bb1399,bb1592,}bb728;bba bb10{bb1682=0 ,
bb1365=2 ,bb1328=3 ,bb1379=4 ,bb1322=9 ,bb1296=12 ,bb1362=13 ,bb1310=14 ,
bb1348=249 ,}bb621;bba bb10{bb1327=0 ,bb1298=1 ,bb1286=2 ,bb1433=3 ,bb1643
=4 ,bb1358=5 ,bb1330=12 ,bb1320=13 ,bb1370=14 ,bb1287=61440 ,}bb484;bba bb10
{bb1293=1 ,bb1307=2 ,bb1308=3 ,bb1543=4 ,bb1605=5 ,bb1455=6 ,bb1434=7 ,
bb1475=8 ,bb1460=9 ,bb1542=10 ,bb1303=11 ,bb400=12 ,bb1289=13 ,bb391=240 ,
bb1364=(128 <<16 )|bb391,bb1342=(192 <<16 )|bb391,bb1333=(256 <<16 )|bb391,
bb1302=(128 <<16 )|bb400,bb1294=(192 <<16 )|bb400,bb1367=(256 <<16 )|bb400,
}bb711;bba bb10{bb1352=0 ,bb1507=1 ,bb1369=2 ,bb1329=3 ,bb1463=4 ,}bb889;
bba bb10{bb1441=0 ,bb1576=1 ,bb1195=2 ,bb604=3 ,bb1236=4 ,}bb773;bba bb10{
bb1579=0 ,bb1530=1 ,bb1409=2 ,bb1676=5 ,bb1709=7 ,}bb486;bba bb10{bb1431=0
,bb1518=1 ,bb1602=2 ,bb1712=3 ,bb1635=4 ,bb1688=5 ,bb1652=6 ,bb398=7 ,bb1548
=65001 ,bb388=240 ,bb1490=(128 <<16 )|bb388,bb1508=(192 <<16 )|bb388,bb1516
=(256 <<16 )|bb388,bb1547=(128 <<16 )|bb398,bb1560=(192 <<16 )|bb398,bb1619
=(256 <<16 )|bb398,}bb796;bba bb10{bb1719=0 ,bb1464=1 ,bb1666=2 ,bb1574=3 ,
bb1477=4 ,bb1532=5 ,bb1569=6 ,bb1649=65001 ,}bb872;bba bb10{bb1684=0 ,
bb1529=1 ,bb1664=2 ,bb1555=3 ,bb1660=4 ,bb1615=5 ,bb1557=64221 ,bb1630=
64222 ,bb1662=64223 ,bb1437=64224 ,bb1710=65001 ,bb1687=65002 ,bb1553=
65003 ,bb1445=65004 ,bb1723=65005 ,bb1492=65006 ,bb1515=65007 ,bb1481=
65008 ,bb1565=65009 ,bb1480=65010 ,}bb661;bba bb10{bb1700=0 ,bb1418=1 ,
bb1438=2 ,}bb676;bba bb10{bb1413=0 ,bb1373=1 ,bb1485=2 ,bb1690=3 ,}bb881;
bba bb10{bb1677=0 ,bb1423=1 ,bb1440=2 ,bb1653=3 ,bb1600=4 ,bb1645=5 ,bb1506
=21 ,bb1572=6 ,bb1620=7 ,bb1539=8 ,bb1383=1000 ,}bb476;bba bb10{bb1414=0 ,
bb1671=1 ,bb1672=2 ,}bb723;bba bb10{bb1670=0 ,bb1400=1 ,bb1718=2 ,bb1442=3
,bb1476=4 ,}bb662;bba bb10{bb1535=0 ,bb1679=1 ,bb1396=1001 ,bb1714=1002 ,}
bb826;bba bb10{bb1563=0 ,bb1135=1 ,bb1047=2 ,bb1057=3 ,bb1129=4 ,bb1130=5 ,
bb1095=6 ,bb1699=100 ,bb1584=101 ,}bb478;bba bbi bb386{bb711 bb152;bb484
bb585;bb482 bb57;}bb386;bba bbi bb387{bb621 bb1349;bb484 bb585;bb482
bb57;}bb387;bba bbi bb396{bb889 bb1003;}bb396;bba bbi bb485{bb661
bb1633;bb872 bb413;bb796 bb152;bbu bb1491;bb486 bb882;}bb485;bba bbi
bb474{bbu bb611;bb386 bb308;bbu bb631;bb387 bb559;bbu bb734;bb396
bb605;bb486 bb882;}bb474;bba bbi bb455{bb178 bb952;bb178 bb1212;bb773
bb102;bb557{bbi{bb387 bb45;bbf bb554[64 ];bbf bb556[64 ];}bb559;bbi{
bb386 bb45;bbf bb1211[32 ];bbf bb1230[32 ];bbf bb554[64 ];bbf bb556[64 ];
bbf bb1213[16 ];}bb308;bbi{bb396 bb45;}bb605;}bb316;}bb455;bba bbi{bbd
bb812,bb592;bbf bb1143:1 ;bbf bb1158:1 ;bbf bb102;bbk bb435;}bb186;bba
bbi bb506{bbd bb11;bb186 bbc[64 *2 ];}bb506;
#ifdef UNDER_CE
bba bb43 bb380;
#else
bba bb83 bb380;
#endif
bba bbi bb199{bbi bb199*bb1473, *bb1392;bbd bb26;bbd bb1115;bb186
bb917[64 ];bb478 bb511;bbd bb1353;bbk bb1068;bbd bb553;bbd bb709;bbd
bb808;bbf bb488;bbf bb1351;bbf bb1104;bbd bb1031;bbd bb1385;bb380
bb572;bbk bb1280;bb455 bb407[3 ];bb380 bb1570;bbf bb1509[40 ];bbd bb589
;bbd bb1581;}bb199;bba bbi bb389{bbi bb389*bb1727;bb186 bb487;}bb389;
bba bbi bb740{bbu bb479;bbu bb488;bbd bb26;bbd bb589;bbf bb1517;bbk
bb1598;bbf*bb1551;bbd bb1426;bbf*bb1500;bbd bb1717;bbf*bb1381;bbd
bb1416;bbu bb1651;bbu bb1573;bb389*bb130;bbu bb1484;bb662 bb1523;bbd
bb1597;bb676 bb1708;bb478 bb511;bbk bb1374;bbd bb1537;bb826 bb1404;
bbd bb1424;bbd bb1659;bb728 bb1421;bbf*bb1410;bbd bb1417;bb476 bb657;
bbd bb1625;bbd bb1658;bbd bb1412;bbd bb1706;bbd bb1498;bb485*bb1540;
bbd bb1614;bb474*bb1511;bbd bb1401;bbd bb1534;bbd bb1656;}bb740;bba
bbi bb718{bbu bb479;bbd bb26;bb186 bb487;}bb718;bba bbi bb867{bb199*
bb317;bbu bb1571;bbf*bb1704;bbd bb1673;}bb867;bba bbi bb869{bbd bb26;
bb186 bb487;bbf bb1439;bbf bb1452;}bb869;bba bbi bb855{bbu bb479;bbu
bb1120;bbd bb26;bbf*bb1631;bbd bb1545;}bb855;bba bbi bb804{bbd bb26;
bbk bb1730;bbk bb1731;bbd bb151;bbf*bb49;}bb804;bba bbi bb646{bbu
bb1590;bbd bb26;bbd bb553;bbd bb709;bbd bb808;}bb646;bba bbi bb906{
bb625 bb1495;bbd bb26;bb765 bb1324;bbu bb1559;}bb906;bba bbi bb820{
bbf bb1681;bbf bb1394;bbf bb1596;bbf bb1589;bbf bb1578;bbf bb1606;bbf
bb1450;bbf bb1465;bbf bb1376;bbf bb1525;bbf bb1415;bbf bb1665;bbf
bb1728;bbf bb1411;bbf bb1377;bbf bb1446;bbf bb1624;bbf bb1388;bbf
bb1456;bbf bb508;bbf bb1552;bbf bb1667;bbf bb1536;bbf bb1693;bbf
bb1420;bbf bb1436;bbf bb1419;}bb820;bba bbi bb732{bbu bb1650;bbd bb490
;bbd bb1711;bb881 bb1432;bbk bb1638;bbu bb1521;bbu bb1566;bbu bb1657;
bbu bb1457;bbu bb1637;bbu bb1599;bbu bb1403;bbl bb1626[128 ];bbl bb1675
[128 ];bbl bb1632[128 ];bbl bb1425[256 ];bbl bb1642[128 ];bbl bb1449[128 ]
;bbd bb1594;bbf bb1567[8 ];bbf bb1408[8 ];}bb732;bba bbi bb853{bbd bb26
;bbd bb1390;}bb853;bba bbi bb815{bbd bb26;bbu bb488;}bb815;bba bbi
bb636{bbu bb1716;bbd bb510;bbd bb1171;}bb636;bba bbi bb651{bbd bb26;
bb476 bb657;bb723 bb1603;bbf*bb1582;bbd bb1591;}bb651;bba bb10{bb1407
=0 ,bb1556,bb1678,bb1389,bb1616,bb1538,bb1636,bb1680,bb1526,bb1585,
bb1586,bb1696,bb1621,bb1386,bb1405,bb1588,bb1468,bb1406,bb1627,bb1644
,}bb641;bba bbi bb1654 bb739;bba bb4( *bb1554)(bb739*bb1380,bbb*
bb1593,bb641 bb324,bbb*bb74);
#pragma pack(pop)
#ifdef _WIN32
#ifdef UNDER_CE
#define bb466 bb1705 bb598("1:")
#else
#define bb466 bb598("\\\\.\\IPSecTL")
#endif
#else
#define bb602 "ipsecdrvtl"
#define bb466 "/dev/" bb602
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
#include"uncobf.h"
#include<linux/ioctl.h>
#include"cobf.h"
bba bbi{bb1 bb1345;bbd bb1339;bb1 bb1241;bbd bb1146;bbd bb451;}bb1203
;
#define bb1357 1
#endif
#pragma pack(push, 8)
bb10{bb1360=3 ,bb1354,bb1355,bb1428,};bba bbi{bbf bb104[4 ];}bb1237;bba
bbi{bbf bb104[4 ];}bb1235;bba bbi{bbd bb947;bbd bb26;}bb1260;bba bbi{
bbd bb131;bbf bb1227[8 ];}bb409;bba bb10{bb1223=0 ,bb1232,bb1252,bb1247
,bb1372}bb1233;bba bbi{bbf bb1121;bbd bb1076;bbf bb1363;}bb489;
#pragma pack(pop)
#pragma pack(push, 8)
bb10{bb1137=-5000 ,bb1105=-4000 ,bb998=-4999 ,bb990=-4998 ,bb989=-4997 ,
bb981=-4996 ,bb1094=-4995 ,bb1087=-4994 ,bb1098=-4993 ,bb1014=-4992 ,
bb1080=-4991 };bb4 bb1133(bb4 bb1127,bbd bb1116,bbl*bb1100);bba bbi{
bb199 bb180;bbd bb1201;bbd bb1073;bbd bb1371;bbd bb1081;bbd bb1240;
bbd bb1279;bbd bb1277;bbd bb1239;bbd bb1249;bbd bb1281;bbd bb1251;bbu
bb1225;bb43 bb572,bb1159,bb1170;bbf bb369[6 ];}bb160;bba bbi bb481{bbi
bb481*bb93;bbf bb102;bbk bb1276;bbk bb1253;bbk bb1272;bbk bb1274;}
bb426;bba bbi bb779{bbi bb779*bb93;bbi bb481*bb1096;bbd bb26;bbf bb369
[6 ];}bb411;bba bb10{bb1147=0 ,bb1577,bb1041,bb1023,bb1009}bb204;bba bbi
{bbd bb385;bbd bb451;bbd bb509;bb409*bb915;bb97 bb966;}bb305;bba bbi{
bb489*bb458;bb411*bb1124;bbd bb582;bb426*bb548;bb97 bb615;bbq bb1119;
bbq bb547;bb160*bb503;bbu bb1270;bbk bb1160;bbk bb1107;bb305 bb1086;}
bb33, *bb1611;
#pragma pack(pop)
bba bbi bb982 bb1319, *bb78;bba bbi bb818{bbi bb818*bb321;bb1 bb465;
bbq bb569;bbd bb26;bbk bb435;bbq bb92;bb1 bb314;bbq bb456;bb1 bb534;
bbq bb546;bb1 bb1505;bb103 bb1366;bbf bb1306[6 ];bb103 bb964;bb103
bb1142;bb103 bb516;bb103 bb533;}bb174, *bb86;bba bbi bb868{bbi bb868*
bb93;bb174*bb321;bbd bb26;bbk bb537;bbk bb1474;bbq bb1448;bbq bb1488;
bbk bb1435;}bb1462, *bb457;bbu bb1268(bb33* *bb1214);bbb bb1285(bb33*
bbj);bb204 bb1269(bb33*bb108,bb376 bb450,bb318 bb138,bb346 bb412,
bb313 bb200);bb204 bb1248(bb33*bb108,bb376 bb450,bb318 bb138,bb346
bb412,bb313 bb200);bb204 bb1258(bb33*bb108,bb174*bb49,bb78 bb75);
bb204 bb1234(bb33*bb108,bb174*bb49,bb78 bb75);bb4 bb1245(bb33*bb108,
bb174*bb49,bbd*bb104);bb4 bb1156(bb78 bb75,bb33*bb108,bb174*bb49,
bb160*bb317,bbu bb595,bbu bb946);bba bb10{bb403,bb1504,}bb295;bbk
bb1215(bb295 bb712,bbh bbf*bb446);bbd bb544(bb295 bb712,bbh bbf*bb446
);bbb bb1173(bbk bb159,bb295 bb550,bbf bb441[2 ]);bbb bb975(bbd bb159,
bb295 bb550,bbf bb441[4 ]);bbb bb1910(bb33*bbj,bbd bb294,bbh bbf bb1187
[6 ]);bbu bb1922(bb33*bbj,bbd bb294,bb411*bb423);bbb bb2036(bb33*bbj);
bbb bb2004(bb33*bbj,bbd bb294,bbh bbf bb1187[6 ],bbf bb102,bbk bb410,
bbk bb406);bbu bb2012(bb33*bbj,bbd bb294,bbf bb102,bbk bb410,bbk bb406
);bbu bb1853(bb33*bbj,bbf bb102,bbk bb410,bbk bb406);bbb bb1987(bb33*
bbj,bb426*bb548,bbq bb582);bbu bb1868(bbd bb294);bb160*bb1789(bb33*
bbj,bbd bb294,bbu bb595);bb160*bb1844(bb33*bbj,bbd bb294,bbd bb104);
bb160*bb1918(bb33*bbj,bb178 bb104);bbb bb1938(bb506*bb40);bb160*
bb1935(bb33*bbj,bb199*bb180);bbb bb1881(bb33*bbj,bb178 bb104);bbb
bb1859(bb33*bbj,bb178 bb104);bbb bb1980(bb33*bbj);bbb bb1796(bb33*bbj
);bb41 bb506 bb593;bbu bb1868(bbd bb2570){bbd bb294=bb493(bb2570);bbe
bbz;bb91(bbz=0 ;bbz<bb593.bb11;bbz++){bb186*bb564=&bb593.bbc[bbz];bbu
bbn;bbm(!bb564->bb1143){bbn=(bb564->bb812&bb564->bb592)==(bb294&bb564
->bb592);}bb54{bbn=bb564->bb812<=bb294&&bb294<=bb564->bb592;}bbm(bbn)bb2
1 ;}bb2 0 ;}bb160*bb1789(bb33*bbj,bbd bb294,bbu bb595){bb160*bb1278=bbj
->bb503;bbe bbz;bb91(bbz=bbj->bb547-1 ;bbz>=0 ;bbz--){bb160*bb166=&
bb1278[bbz];bb199*bb1218=&bb166->bb180;bbm(bb595){bbm(bb1218->bb26==
bb294)bb2 bb166;}bb54{bbq bb76;bbu bb2244=0 ;bbm(!bb1218->bb1104)bb1691
;bbm(bb1218->bb26==bb294){bbm(bb1218->bb407[0 ].bb316.bb308.bb45.bb57
==bb1164)bb2 bb166;bb54 bb2 bb90;}bb91(bb76=0 ;bb76<bb1218->bb1115;
bb76++){bbu bbn;bb186*bb564=&bb1218->bb917[bb76];bbm(!bb564->bb1143){
bbn=(bb564->bb812&bb564->bb592)==(bb294&bb564->bb592);}bb54{bbd bbc=
bb493(bb294);bbn=bb493(bb564->bb812)<=bbc&&bbc<=bb493(bb564->bb592);}
bbm(bbn){bbm(bb564->bb1158){bb2244=0 ;bb21;}bb54 bb2244=1 ;}}bbm(bb2244
)bb2 bb166;}}bb2 bb90;}bb160*bb1844(bb33*bbj,bbd bb294,bbd bb104){
bb160*bb1278=bbj->bb503;bbq bbz,bb11=bbj->bb547;bb91(bbz=0 ;bbz<bb11;
bbz++){bb160*bb166=&bb1278[bbz];bb199*bb1218=&bb166->bb180;bbm(bb1218
->bb26==bb294){bbq bb76,bb11=bb1218->bb1280;bb91(bb76=0 ;bb76<bb11;
bb76++){bbd bb2567=bb544(bb403,bb1218->bb407[bb76].bb952);bbm(bb2567
==bb104)bb2 bb166;}}}bb2 bb90;}bb160*bb1918(bb33*bbj,bb178 bb104){
bb160*bb1278=bbj->bb503;bbq bbz,bb11=bbj->bb547;bb91(bbz=0 ;bbz<bb11;
bbz++){bb160*bb166=&bb1278[bbz];bbm(bb1898(bb166->bb180.bb407[0 ].
bb952,bb104,bb12(bb178))==0 )bb2 bb166;}bb2 bb90;}bbb bb1938(bb506*
bb40){bbq bbz;bb593.bb11=0 ;bb91(bbz=0 ;bbz<bb40->bb11;bbz++){bb593.bbc
[bb593.bb11]=bb40->bbc[bbz];bb593.bbc[bb593.bb11].bb812=bb493(bb40->
bbc[bbz].bb812);bb593.bbc[bb593.bb11].bb592=bb493(bb40->bbc[bbz].
bb592);bb593.bb11++;}}bb160*bb1935(bb33*bbj,bb199*bb180){bb160*bb1110
=bb90;bbm(bbj->bb547>=bbj->bb1119){bbd bb2392=bbj->bb1119+8 ;bb160*
bb2225=bb137(1 ,bb2392*bb12( *bb1110));bbm(!bb2225)bb2 bb90;bbm(bbj->
bb503){bb81(bb2225,bbj->bb503,bbj->bb1119*bb12( *bb1110));bb109(bbj->
bb503);}bbj->bb503=bb2225;bbj->bb1119=bb2392;}{bb160*bb1278=bbj->
bb503;bbq bbz;bb91(bbz=0 ;bbz<bbj->bb547;bbz++){bb160*bb166=&bb1278[
bbz];bb199*bb1218=&bb166->bb180;bbq bb76;bbu bb2304=0 ;bb91(bb76=0 ;
bb76<bb1218->bb1115;bb76++){bb186*bb564=&bb1218->bb917[bb76];bbq bb3;
bb91(bb3=0 ;bb3<bb180->bb1115;bb3++){bb186*bb2223=&bb180->bb917[bb3];
bbm(bb564->bb1143&&bb2223->bb1143){bbu bbn=bb493(bb2223->bb812)<bb493
(bb564->bb812)&&bb493(bb564->bb592)<=bb493(bb2223->bb592);bbm(bbn&&
bb564->bb1158)bbn=!bbn;bbm(bbn){bb2368(bb166+1 ,bb166,bb12( *bb166) * (
bbj->bb547-bbz));bb997(bb166,0 ,bb12( *bb166));bb1110=bb166;bbj->bb547
++;bb2304=1 ;bb21;}}}bbm(bb2304)bb21;}bbm(bb2304)bb21;}}bbm(!bb1110){
bb1110=&bbj->bb503[bbj->bb547++];bb997(bb1110,0 ,bb12( *bb1110));}{
bb411 bb2322;bbm(bb1922(bbj,bb180->bb26,&bb2322))bb81(bb1110->bb369,
bb2322.bb369,6 );bb81(&bb1110->bb180,bb180,bb12( *bb180));bb1110->
bb1225=0 ;bb1110->bb572=bb302(bb90);bb1110->bb1159=bb302(bb90);bb1110
->bb1170=bb302(bb90);bb1110->bb1201=bb180->bb589;}bb593.bb11=0 ;bb2
bb1110;}bbb bb1881(bb33*bbj,bb178 bb104){bb160*bb1278=bbj->bb503;bbq
bbz,bb11=bbj->bb547;bbm(bb593.bb11==0 ){bb91(bbz=0 ;bbz<bb11;bbz++){
bb160*bb166=&bb1278[bbz];bbe bb76;bb91(bb76=0 ;bb76<bb166->bb180.
bb1115;bb76++){bb186*bb564=&bb166->bb180.bb917[bb76];bbm(bb564->
bb1158)bb1691;bbm(!(bb593.bb11<(bb12(bb593.bbc)/bb12((bb593.bbc)[0 ]))))bb21
;bb593.bbc[bb593.bb11]= *bb564;bb593.bbc[bb593.bb11].bb812=bb493(
bb564->bb812);bb593.bbc[bb593.bb11].bb592=bb493(bb564->bb592);bb593.
bb11++;}}}bb91(bbz=0 ;bbz<bb11;bbz++){bb160*bb166=&bb1278[bbz];bbm(
bb1898(bb166->bb180.bb407[0 ].bb952,bb104,bb12(bb178))==0 ){bb2368(
bb166,bb166+1 ,(bb11-bbz-1 ) *bb12( *bb166));bbj->bb547--;bb2;}}}bbb
bb1859(bb33*bbj,bb178 bb104){bb160*bb1278=bbj->bb503;bbq bbz,bb11=bbj
->bb547;bb91(bbz=0 ;bbz<bb11;bbz++){bb160*bb166=&bb1278[bbz];bbm(
bb1898(bb166->bb180.bb407[0 ].bb952,bb104,bb12(bb178))==0 ){bb166->
bb180.bb1104=0 ;bb2;}}}bbb bb1980(bb33*bbj){bbj->bb547=0 ;}bbb bb1796(
bb33*bbj){bbm(bbj->bb503){bb109(bbj->bb503);bbj->bb503=bb90;}bbj->
bb1119=0 ;bbj->bb547=0 ;bb593.bb11=0 ;}
