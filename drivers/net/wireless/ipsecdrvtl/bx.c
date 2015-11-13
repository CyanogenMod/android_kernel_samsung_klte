/*
   'src_pm_pgpNetPMSA.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Sun Nov 16 20:01:26 2014
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
bb985(bbx*bb51);bbu bb1018(bbf*bb51);bba bbi bb1019*bb989;bba bbi
bb1027*bb1029;bba bbi bb993*bb1026;bba bbi bb1001*bb1016;bba bbi
bb1024*bb1022;bba bbi bb990*bb987;bba bb10{bb551=0 ,bb578=1 ,bb589=2 ,
bb756=3 ,bb587=4 ,bb563=5 ,bb572=6 ,bb573=7 ,bb592=9 ,}bb421;bba bb10{bb615
=0 ,bb991,bb600,bb1014,bb910,bb926,bb909,bb920,bb928,bb929,bb918,}
bb517;
#pragma pack(push, 8)
#ifdef _MSC_VER
#pragma warning (disable:4200)
#endif
bba bbf bb178[4 ];bba bb10{bb1652=0 ,bb1467=1 ,}bb1394;bba bb10{bb1529=0
,bb1721=1 ,bb1557=2 ,bb1440=3 ,bb1660=4 ,bb1494=5 ,bb1636=6 ,bb1517=7 ,
bb1609=8 ,bb1521=9 ,bb1678=10 ,bb1510=11 ,bb1697=12 ,bb1713=13 ,bb1720=14 ,
bb1424=15 ,bb1453=16 ,bb1395=17 ,bb1602=18 ,bb1692=19 ,bb1643=20 ,bb1495=21
,bb1508=22 ,bb1475=23 ,bb1607=24 ,bb1608=25 ,bb1449=26 ,bb1581=27 ,bb1376=
28 ,bb1708=29 ,bb1688=30 ,bb1632=16300 ,bb1616=16301 ,bb1729=16384 ,bb1538=
24576 ,bb1465=24577 ,bb1439=24578 ,bb1480=34793 ,bb1382=40500 ,}bb626;bba
bb10{bb1462=0 ,bb1526=1 ,bb1456=2 ,bb1426=3 ,bb1701=4 ,bb1388=5 ,bb1671=6 ,
bb1476=7 ,bb1530=8 ,bb1400=9 ,bb1445=21 ,bb1490=22 ,bb1500=23 ,bb1447=24 ,
bb1542=25 ,bb1512=26 ,bb1463=27 ,bb1384=28 ,bb1481=29 ,bb1491=80 ,}bb632;
bba bb10{bb1639=0 ,bb1700=1 ,bb1552=2 ,bb1486=3 ,bb1523=4 ,}bb1663;bba bb10
{bb1687=0 ,bb1349=1 ,bb1167=2 ,bb1226=3 ,bb1290=4 ,bb1050=61440 ,bb1359=
61441 ,bb1117=61443 ,bb1301=61444 ,}bb473;bba bb10{bb1702=0 ,bb1498=1 ,
bb1563=2 ,}bb1681;bba bb10{bb1391=0 ,bb1727,bb1441,bb1454,bb1567,bb1499
,bb1637,bb1466,bb1606,bb1496,bb1397,bb1696,}bb729;bba bb10{bb1677=0 ,
bb1365=2 ,bb1327=3 ,bb1377=4 ,bb1321=9 ,bb1298=12 ,bb1363=13 ,bb1310=14 ,
bb1350=249 ,}bb623;bba bb10{bb1360=0 ,bb1300=1 ,bb1286=2 ,bb1429=3 ,bb1640
=4 ,bb1358=5 ,bb1330=12 ,bb1319=13 ,bb1369=14 ,bb1287=61440 ,}bb481;bba bb10
{bb1294=1 ,bb1308=2 ,bb1338=3 ,bb1541=4 ,bb1550=5 ,bb1450=6 ,bb1430=7 ,
bb1471=8 ,bb1455=9 ,bb1540=10 ,bb1304=11 ,bb396=12 ,bb1339=13 ,bb394=240 ,
bb1345=(128 <<16 )|bb394,bb1342=(192 <<16 )|bb394,bb1329=(256 <<16 )|bb394,
bb1303=(128 <<16 )|bb396,bb1295=(192 <<16 )|bb396,bb1366=(256 <<16 )|bb396,
}bb687;bba bb10{bb1297=0 ,bb1505=1 ,bb1368=2 ,bb1328=3 ,bb1460=4 ,}bb884;
bba bb10{bb1437=0 ,bb1574=1 ,bb1192=2 ,bb603=3 ,bb1235=4 ,}bb710;bba bb10{
bb1577=0 ,bb1528=1 ,bb1407=2 ,bb1473=5 ,bb1710=7 ,}bb488;bba bb10{bb1427=0
,bb1518=1 ,bb1603=2 ,bb1714=3 ,bb1484=4 ,bb1685=5 ,bb1648=6 ,bb391=7 ,bb1545
=65001 ,bb399=240 ,bb1487=(128 <<16 )|bb399,bb1506=(192 <<16 )|bb399,bb1515
=(256 <<16 )|bb399,bb1544=(128 <<16 )|bb391,bb1560=(192 <<16 )|bb391,bb1617
=(256 <<16 )|bb391,}bb795;bba bb10{bb1719=0 ,bb1461=1 ,bb1662=2 ,bb1573=3 ,
bb1474=4 ,bb1531=5 ,bb1568=6 ,bb1646=65001 ,}bb879;bba bb10{bb1679=0 ,
bb1527=1 ,bb1661=2 ,bb1555=3 ,bb1657=4 ,bb1613=5 ,bb1558=64221 ,bb1626=
64222 ,bb1659=64223 ,bb1675=64224 ,bb1711=65001 ,bb1683=65002 ,bb1553=
65003 ,bb1442=65004 ,bb1723=65005 ,bb1489=65006 ,bb1514=65007 ,bb1479=
65008 ,bb1712=65009 ,bb1478=65010 ,}bb891;bba bb10{bb1699=0 ,bb1416=1 ,
bb1434=2 ,}bb850;bba bb10{bb1410=0 ,bb1634=1 ,bb1635=2 ,bb1686=3 ,}bb860;
bba bb10{bb1594=0 ,bb1420=1 ,bb1436=2 ,bb1649=3 ,bb1601=4 ,bb1642=5 ,bb1504
=21 ,bb1570=6 ,bb1618=7 ,bb1537=8 ,bb1381=1000 ,}bb477;bba bb10{bb1412=0 ,
bb1667=1 ,bb1669=2 ,}bb725;bba bb10{bb1666=0 ,bb1629=1 ,bb1718=2 ,bb1438=3
,bb1472=4 ,}bb667;bba bb10{bb1532=0 ,bb1674=1 ,bb1393=1001 ,bb1715=1002 ,}
bb822;bba bb10{bb1562=0 ,bb1136=1 ,bb1078=2 ,bb1052=3 ,bb1113=4 ,bb1131=5 ,
bb1095=6 ,bb1698=100 ,bb1583=101 ,}bb480;bba bbi bb400{bb687 bb154;bb481
bb590;bb473 bb57;}bb400;bba bbi bb390{bb623 bb1352;bb481 bb590;bb473
bb57;}bb390;bba bbi bb389{bb884 bb1007;}bb389;bba bbi bb482{bb891
bb1628;bb879 bb414;bb795 bb154;bbu bb1488;bb488 bb650;}bb482;bba bbi
bb484{bbu bb610;bb400 bb308;bbu bb764;bb390 bb558;bbu bb773;bb389
bb604;bb488 bb650;}bb484;bba bbi bb446{bb178 bb954;bb178 bb1213;bb710
bb102;bb556{bbi{bb390 bb45;bbf bb552[64 ];bbf bb559[64 ];}bb558;bbi{
bb400 bb45;bbf bb1219[32 ];bbf bb1229[32 ];bbf bb552[64 ];bbf bb559[64 ];
bbf bb1203[16 ];}bb308;bbi{bb389 bb45;}bb604;}bb316;}bb446;bba bbi{bbd
bb851,bb580;bbf bb1142:1 ;bbf bb1157:1 ;bbf bb102;bbk bb437;}bb186;bba
bbi bb510{bbd bb11;bb186 bbc[64 *2 ];}bb510;
#ifdef UNDER_CE
bba bb43 bb378;
#else
bba bb83 bb378;
#endif
bba bbi bb199{bbi bb199*bb1469, *bb1389;bbd bb27;bbd bb1118;bb186
bb919[64 ];bb480 bb506;bbd bb1354;bbk bb1070;bbd bb553;bbd bb852;bbd
bb806;bbf bb489;bbf bb1332;bbf bb1130;bbd bb1031;bbd bb1383;bb378
bb569;bbk bb1279;bb446 bb402[3 ];bb378 bb1569;bbf bb1507[40 ];bbd bb595
;bbd bb1579;}bb199;bba bbi bb393{bbi bb393*bb1726;bb186 bb476;}bb393;
bba bbi bb735{bbu bb479;bbu bb489;bbd bb27;bbd bb595;bbf bb1516;bbk
bb1597;bbf*bb1549;bbd bb1422;bbf*bb1582;bbd bb1717;bbf*bb1379;bbd
bb1414;bbu bb1477;bbu bb1572;bb393*bb130;bbu bb1482;bb667 bb1522;bbd
bb1596;bb850 bb1709;bb480 bb506;bbk bb1373;bbd bb1534;bb822 bb1401;
bbd bb1650;bbd bb1622;bb729 bb1419;bbf*bb1408;bbd bb1415;bb477 bb867;
bbd bb1654;bbd bb1625;bbd bb1411;bbd bb1707;bbd bb1497;bb482*bb1539;
bbd bb1458;bb484*bb1509;bbd bb1399;bbd bb1533;bbd bb1653;}bb735;bba
bbi bb720{bbu bb479;bbd bb27;bb186 bb476;}bb720;bba bbi bb865{bb199*
bb317;bbu bb1571;bbf*bb1703;bbd bb1670;}bb865;bba bbi bb873{bbd bb27;
bb186 bb476;bbf bb1435;bbf bb1448;}bb873;bba bbi bb782{bbu bb479;bbu
bb1121;bbd bb27;bbf*bb1627;bbd bb1543;}bb782;bba bbi bb659{bbd bb27;
bbk bb1730;bbk bb1731;bbd bb151;bbf*bb48;}bb659;bba bbi bb824{bbu
bb1590;bbd bb27;bbd bb553;bbd bb852;bbd bb806;}bb824;bba bbi bb905{
bb626 bb1492;bbd bb27;bb632 bb1323;bbu bb1559;}bb905;bba bbi bb816{
bbf bb1676;bbf bb1392;bbf bb1691;bbf bb1589;bbf bb1576;bbf bb1605;bbf
bb1587;bbf bb1459;bbf bb1375;bbf bb1525;bbf bb1413;bbf bb1705;bbf
bb1728;bbf bb1409;bbf bb1405;bbf bb1443;bbf bb1621;bbf bb1385;bbf
bb1451;bbf bb511;bbf bb1551;bbf bb1614;bbf bb1535;bbf bb1690;bbf
bb1418;bbf bb1432;bbf bb1417;}bb816;bba bbi bb690{bbu bb1647;bbd bb487
;bbd bb1610;bb860 bb1428;bbk bb1633;bbu bb1520;bbu bb1565;bbu bb1655;
bbu bb1452;bbu bb1592;bbu bb1598;bbu bb1398;bbl bb1623[128 ];bbl bb1672
[128 ];bbl bb1599[128 ];bbl bb1421[256 ];bbl bb1638[128 ];bbl bb1446[128 ]
;bbd bb1593;bbf bb1566[8 ];bbf bb1406[8 ];}bb690;bba bbi bb654{bbd bb27
;bbd bb1387;}bb654;bba bbi bb855{bbd bb27;bbu bb489;}bb855;bba bbi
bb765{bbu bb1716;bbd bb513;bbd bb1161;}bb765;bba bbi bb747{bbd bb27;
bb477 bb867;bb725 bb1604;bbf*bb1580;bbd bb1591;}bb747;bba bb10{bb1404
=0 ,bb1556,bb1673,bb1386,bb1615,bb1536,bb1600,bb1680,bb1524,bb1585,
bb1586,bb1695,bb1706,bb1656,bb1402,bb1588,bb1464,bb1403,bb1624,bb1641
,}bb645;bba bbi bb1651 bb840;bba bb4( *bb1554)(bb840*bb1378,bbb*
bb1694,bb645 bb323,bbb*bb74);
#pragma pack(pop)
#ifdef _WIN32
#ifdef UNDER_CE
#define bb468 bb1704 bb599("1:")
#else
#define bb468 bb599("\\\\.\\IPSecTL")
#endif
#else
#define bb602 "ipsecdrvtl"
#define bb468 "/dev/" bb602
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
#include"uncobf.h"
#include<linux/ioctl.h>
#include"cobf.h"
bba bbi{bb1 bb1346;bbd bb1322;bb1 bb1239;bbd bb1146;bbd bb448;}bb1202
;
#define bb1357 1
#endif
#pragma pack(push, 8)
bb10{bb1361=3 ,bb1355,bb1356,bb1425,};bba bbi{bbf bb104[4 ];}bb1284;bba
bbi{bbf bb104[4 ];}bb1234;bba bbi{bbd bb935;bbd bb27;}bb1269;bba bbi{
bbd bb131;bbf bb1218[8 ];}bb411;bba bb10{bb1222=0 ,bb1233,bb1251,bb1231
,bb1372}bb1252;bba bbi{bbf bb1122;bbd bb1071;bbf bb1364;}bb486;
#pragma pack(pop)
#pragma pack(push, 8)
bb10{bb1127=-5000 ,bb1108=-4000 ,bb998=-4999 ,bb988=-4998 ,bb1017=-4997 ,
bb981=-4996 ,bb1094=-4995 ,bb1087=-4994 ,bb1100=-4993 ,bb1015=-4992 ,
bb1081=-4991 };bb4 bb1133(bb4 bb1137,bbd bb1119,bbl*bb1102);bba bbi{
bb199 bb180;bbd bb1197;bbd bb1086;bbd bb1371;bbd bb1092;bbd bb1238;
bbd bb1278;bbd bb1276;bbd bb1237;bbd bb1247;bbd bb1280;bbd bb1249;bbu
bb1223;bb43 bb569,bb1158,bb1170;bbf bb371[6 ];}bb160;bba bbi bb478{bbi
bb478*bb94;bbf bb102;bbk bb1275;bbk bb1277;bbk bb1271;bbk bb1273;}
bb427;bba bbi bb778{bbi bb778*bb94;bbi bb478*bb1096;bbd bb27;bbf bb371
[6 ];}bb409;bba bb10{bb1147=0 ,bb1575,bb1042,bb1003,bb1012}bb203;bba bbi
{bbd bb383;bbd bb448;bbd bb512;bb411*bb923;bb97 bb966;}bb305;bba bbi{
bb486*bb460;bb409*bb1143;bbd bb585;bb427*bb538;bb97 bb605;bbq bb1120;
bbq bb534;bb160*bb508;bbu bb1258;bbk bb1171;bbk bb1110;bb305 bb1047;}
bb33, *bb1493;
#pragma pack(pop)
bba bbi bb983 bb1334, *bb79;bba bbi bb817{bbi bb817*bb321;bb1 bb470;
bbq bb561;bbd bb27;bbk bb437;bbq bb92;bb1 bb314;bbq bb456;bb1 bb535;
bbq bb548;bb1 bb1502;bb101 bb1367;bbf bb1307[6 ];bb101 bb964;bb101
bb1105;bb101 bb521;bb101 bb533;}bb174, *bb85;bba bbi bb863{bbi bb863*
bb94;bb174*bb321;bbd bb27;bbk bb542;bbk bb1470;bbq bb1444;bbq bb1584;
bbk bb1431;}bb1457, *bb457;bbu bb1266(bb33* *bb1215);bbb bb1285(bb33*
bbj);bb203 bb1267(bb33*bb108,bb381 bb450,bb315 bb138,bb352 bb413,
bb313 bb200);bb203 bb1246(bb33*bb108,bb381 bb450,bb315 bb138,bb352
bb413,bb313 bb200);bb203 bb1256(bb33*bb108,bb174*bb48,bb79 bb76);
bb203 bb1245(bb33*bb108,bb174*bb48,bb79 bb76);bb4 bb1243(bb33*bb108,
bb174*bb48,bbd*bb104);bb4 bb1155(bb79 bb76,bb33*bb108,bb174*bb48,
bb160*bb317,bbu bb594,bbu bb945);bba bb10{bb403,bb1501,}bb297;bbk
bb1214(bb297 bb866,bbh bbf*bb455);bbd bb545(bb297 bb866,bbh bbf*bb455
);bbb bb1173(bbk bb159,bb297 bb554,bbf bb438[2 ]);bbb bb974(bbd bb159,
bb297 bb554,bbf bb438[4 ]);bbb bb1910(bb33*bbj,bbd bb294,bbh bbf bb1185
[6 ]);bbu bb1922(bb33*bbj,bbd bb294,bb409*bb428);bbb bb2036(bb33*bbj);
bbb bb2004(bb33*bbj,bbd bb294,bbh bbf bb1185[6 ],bbf bb102,bbk bb404,
bbk bb407);bbu bb2012(bb33*bbj,bbd bb294,bbf bb102,bbk bb404,bbk bb407
);bbu bb1853(bb33*bbj,bbf bb102,bbk bb404,bbk bb407);bbb bb1987(bb33*
bbj,bb427*bb538,bbq bb585);bbu bb1868(bbd bb294);bb160*bb1789(bb33*
bbj,bbd bb294,bbu bb594);bb160*bb1844(bb33*bbj,bbd bb294,bbd bb104);
bb160*bb1918(bb33*bbj,bb178 bb104);bbb bb1937(bb510*bb40);bb160*
bb1934(bb33*bbj,bb199*bb180);bbb bb1881(bb33*bbj,bb178 bb104);bbb
bb1859(bb33*bbj,bb178 bb104);bbb bb1980(bb33*bbj);bbb bb1796(bb33*bbj
);bb41 bb510 bb582;bbu bb1868(bbd bb2571){bbd bb294=bb494(bb2571);bbe
bbz;bb91(bbz=0 ;bbz<bb582.bb11;bbz++){bb186*bb568=&bb582.bbc[bbz];bbu
bbn;bbm(!bb568->bb1142){bbn=(bb568->bb851&bb568->bb580)==(bb294&bb568
->bb580);}bb54{bbn=bb568->bb851<=bb294&&bb294<=bb568->bb580;}bbm(bbn)bb2
1 ;}bb2 0 ;}bb160*bb1789(bb33*bbj,bbd bb294,bbu bb594){bb160*bb1250=bbj
->bb508;bbe bbz;bb91(bbz=bbj->bb534-1 ;bbz>=0 ;bbz--){bb160*bb165=&
bb1250[bbz];bb199*bb1205=&bb165->bb180;bbm(bb594){bbm(bb1205->bb27==
bb294)bb2 bb165;}bb54{bbq bb75;bbu bb2244=0 ;bbm(!bb1205->bb1130)bb1689
;bbm(bb1205->bb27==bb294){bbm(bb1205->bb402[0 ].bb316.bb308.bb45.bb57
==bb1167)bb2 bb165;bb54 bb2 bb90;}bb91(bb75=0 ;bb75<bb1205->bb1118;
bb75++){bbu bbn;bb186*bb568=&bb1205->bb919[bb75];bbm(!bb568->bb1142){
bbn=(bb568->bb851&bb568->bb580)==(bb294&bb568->bb580);}bb54{bbd bbc=
bb494(bb294);bbn=bb494(bb568->bb851)<=bbc&&bbc<=bb494(bb568->bb580);}
bbm(bbn){bbm(bb568->bb1157){bb2244=0 ;bb22;}bb54 bb2244=1 ;}}bbm(bb2244
)bb2 bb165;}}bb2 bb90;}bb160*bb1844(bb33*bbj,bbd bb294,bbd bb104){
bb160*bb1250=bbj->bb508;bbq bbz,bb11=bbj->bb534;bb91(bbz=0 ;bbz<bb11;
bbz++){bb160*bb165=&bb1250[bbz];bb199*bb1205=&bb165->bb180;bbm(bb1205
->bb27==bb294){bbq bb75,bb11=bb1205->bb1279;bb91(bb75=0 ;bb75<bb11;
bb75++){bbd bb2567=bb545(bb403,bb1205->bb402[bb75].bb954);bbm(bb2567
==bb104)bb2 bb165;}}}bb2 bb90;}bb160*bb1918(bb33*bbj,bb178 bb104){
bb160*bb1250=bbj->bb508;bbq bbz,bb11=bbj->bb534;bb91(bbz=0 ;bbz<bb11;
bbz++){bb160*bb165=&bb1250[bbz];bbm(bb1898(bb165->bb180.bb402[0 ].
bb954,bb104,bb12(bb178))==0 )bb2 bb165;}bb2 bb90;}bbb bb1937(bb510*
bb40){bbq bbz;bb582.bb11=0 ;bb91(bbz=0 ;bbz<bb40->bb11;bbz++){bb582.bbc
[bb582.bb11]=bb40->bbc[bbz];bb582.bbc[bb582.bb11].bb851=bb494(bb40->
bbc[bbz].bb851);bb582.bbc[bb582.bb11].bb580=bb494(bb40->bbc[bbz].
bb580);bb582.bb11++;}}bb160*bb1934(bb33*bbj,bb199*bb180){bb160*bb1114
=bb90;bbm(bbj->bb534>=bbj->bb1120){bbd bb2393=bbj->bb1120+8 ;bb160*
bb2225=bb137(1 ,bb2393*bb12( *bb1114));bbm(!bb2225)bb2 bb90;bbm(bbj->
bb508){bb81(bb2225,bbj->bb508,bbj->bb1120*bb12( *bb1114));bb109(bbj->
bb508);}bbj->bb508=bb2225;bbj->bb1120=bb2393;}{bb160*bb1250=bbj->
bb508;bbq bbz;bb91(bbz=0 ;bbz<bbj->bb534;bbz++){bb160*bb165=&bb1250[
bbz];bb199*bb1205=&bb165->bb180;bbq bb75;bbu bb2304=0 ;bb91(bb75=0 ;
bb75<bb1205->bb1118;bb75++){bb186*bb568=&bb1205->bb919[bb75];bbq bb3;
bb91(bb3=0 ;bb3<bb180->bb1118;bb3++){bb186*bb2222=&bb180->bb919[bb3];
bbm(bb568->bb1142&&bb2222->bb1142){bbu bbn=bb494(bb2222->bb851)<bb494
(bb568->bb851)&&bb494(bb568->bb580)<=bb494(bb2222->bb580);bbm(bbn&&
bb568->bb1157)bbn=!bbn;bbm(bbn){bb2368(bb165+1 ,bb165,bb12( *bb165) * (
bbj->bb534-bbz));bb997(bb165,0 ,bb12( *bb165));bb1114=bb165;bbj->bb534
++;bb2304=1 ;bb22;}}}bbm(bb2304)bb22;}bbm(bb2304)bb22;}}bbm(!bb1114){
bb1114=&bbj->bb508[bbj->bb534++];bb997(bb1114,0 ,bb12( *bb1114));}{
bb409 bb2322;bbm(bb1922(bbj,bb180->bb27,&bb2322))bb81(bb1114->bb371,
bb2322.bb371,6 );bb81(&bb1114->bb180,bb180,bb12( *bb180));bb1114->
bb1223=0 ;bb1114->bb569=bb302(bb90);bb1114->bb1158=bb302(bb90);bb1114
->bb1170=bb302(bb90);bb1114->bb1197=bb180->bb595;}bb582.bb11=0 ;bb2
bb1114;}bbb bb1881(bb33*bbj,bb178 bb104){bb160*bb1250=bbj->bb508;bbq
bbz,bb11=bbj->bb534;bbm(bb582.bb11==0 ){bb91(bbz=0 ;bbz<bb11;bbz++){
bb160*bb165=&bb1250[bbz];bbe bb75;bb91(bb75=0 ;bb75<bb165->bb180.
bb1118;bb75++){bb186*bb568=&bb165->bb180.bb919[bb75];bbm(bb568->
bb1157)bb1689;bbm(!(bb582.bb11<(bb12(bb582.bbc)/bb12((bb582.bbc)[0 ]))))bb22
;bb582.bbc[bb582.bb11]= *bb568;bb582.bbc[bb582.bb11].bb851=bb494(
bb568->bb851);bb582.bbc[bb582.bb11].bb580=bb494(bb568->bb580);bb582.
bb11++;}}}bb91(bbz=0 ;bbz<bb11;bbz++){bb160*bb165=&bb1250[bbz];bbm(
bb1898(bb165->bb180.bb402[0 ].bb954,bb104,bb12(bb178))==0 ){bb2368(
bb165,bb165+1 ,(bb11-bbz-1 ) *bb12( *bb165));bbj->bb534--;bb2;}}}bbb
bb1859(bb33*bbj,bb178 bb104){bb160*bb1250=bbj->bb508;bbq bbz,bb11=bbj
->bb534;bb91(bbz=0 ;bbz<bb11;bbz++){bb160*bb165=&bb1250[bbz];bbm(
bb1898(bb165->bb180.bb402[0 ].bb954,bb104,bb12(bb178))==0 ){bb165->
bb180.bb1130=0 ;bb2;}}}bbb bb1980(bb33*bbj){bbj->bb534=0 ;}bbb bb1796(
bb33*bbj){bbm(bbj->bb508){bb109(bbj->bb508);bbj->bb508=bb90;}bbj->
bb1120=0 ;bbj->bb534=0 ;bb582.bb11=0 ;}
