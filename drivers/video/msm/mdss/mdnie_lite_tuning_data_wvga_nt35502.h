/* Copyright (c) 2009-2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#ifndef _MDNIE_LITE_TUNING_DATA_WVGA_NT35502_H_
#define _MDNIE_LITE_TUNING_DATA_WVGA_NT35502_H_

////////////////// UI /// /////////////////////

static char STANDARD_UI_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char STANDARD_UI_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr	
};
static char STANDARD_UI_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char STANDARD_UI_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char STANDARD_UI_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};


static char NATURAL_UI_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char NATURAL_UI_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char NATURAL_UI_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char NATURAL_UI_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char NATURAL_UI_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};


static char DYNAMIC_UI_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char DYNAMIC_UI_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char DYNAMIC_UI_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char DYNAMIC_UI_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char DYNAMIC_UI_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char MOVIE_UI_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char MOVIE_UI_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char MOVIE_UI_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char MOVIE_UI_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char MOVIE_UI_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};


static char AUTO_UI_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char AUTO_UI_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char AUTO_UI_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char AUTO_UI_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char AUTO_UI_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

////////////////// GALLERY /////////////////////
static char STANDARD_GALLERY_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char STANDARD_GALLERY_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char STANDARD_GALLERY_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char STANDARD_GALLERY_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char STANDARD_GALLERY_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char NATURAL_GALLERY_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char NATURAL_GALLERY_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char NATURAL_GALLERY_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char NATURAL_GALLERY_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char NATURAL_GALLERY_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char DYNAMIC_GALLERY_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char DYNAMIC_GALLERY_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char DYNAMIC_GALLERY_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char DYNAMIC_GALLERY_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char DYNAMIC_GALLERY_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char MOVIE_GALLERY_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char MOVIE_GALLERY_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char MOVIE_GALLERY_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char MOVIE_GALLERY_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char MOVIE_GALLERY_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char AUTO_GALLERY_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char AUTO_GALLERY_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char AUTO_GALLERY_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char AUTO_GALLERY_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char AUTO_GALLERY_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

////////////////// VIDEO /////////////////////

static char STANDARD_VIDEO_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char STANDARD_VIDEO_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char STANDARD_VIDEO_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char STANDARD_VIDEO_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char STANDARD_VIDEO_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char NATURAL_VIDEO_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char NATURAL_VIDEO_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char NATURAL_VIDEO_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char NATURAL_VIDEO_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char NATURAL_VIDEO_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char DYNAMIC_VIDEO_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char DYNAMIC_VIDEO_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char DYNAMIC_VIDEO_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char DYNAMIC_VIDEO_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char DYNAMIC_VIDEO_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char MOVIE_VIDEO_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char MOVIE_VIDEO_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char MOVIE_VIDEO_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char MOVIE_VIDEO_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char MOVIE_VIDEO_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char AUTO_VIDEO_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char AUTO_VIDEO_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char AUTO_VIDEO_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char AUTO_VIDEO_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char AUTO_VIDEO_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

////////////////// VT /////////////////////
static char STANDARD_VT_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char STANDARD_VT_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char STANDARD_VT_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char STANDARD_VT_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char STANDARD_VT_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char NATURAL_VT_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char NATURAL_VT_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char NATURAL_VT_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char NATURAL_VT_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char NATURAL_VT_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char DYNAMIC_VT_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,

};
static char DYNAMIC_VT_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char DYNAMIC_VT_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char DYNAMIC_VT_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char DYNAMIC_VT_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char MOVIE_VT_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char MOVIE_VT_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char MOVIE_VT_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char MOVIE_VT_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char MOVIE_VT_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char AUTO_VT_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char AUTO_VT_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char AUTO_VT_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char AUTO_VT_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char AUTO_VT_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

////////////////// CAMERA /////////////////////

static char CAMERA_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char CAMERA_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char CAMERA_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char CAMERA_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char CAMERA_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char AUTO_CAMERA_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char AUTO_CAMERA_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char AUTO_CAMERA_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char AUTO_CAMERA_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char AUTO_CAMERA_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char CAMERA_OUTDOOR_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char CAMERA_OUTDOOR_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char CAMERA_OUTDOOR_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char CAMERA_OUTDOOR_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char CAMERA_OUTDOOR_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};


static char COLD_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char COLD_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr	
};
static char COLD_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char COLD_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char COLD_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};


static char COLD_OUTDOOR_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char COLD_OUTDOOR_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char COLD_OUTDOOR_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char COLD_OUTDOOR_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char COLD_OUTDOOR_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};


static char WARM_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char WARM_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char WARM_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char WARM_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char WARM_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char WARM_OUTDOOR_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char WARM_OUTDOOR_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char WARM_OUTDOOR_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char WARM_OUTDOOR_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char WARM_OUTDOOR_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char NEGATIVE_1[] = {	
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char NEGATIVE_2[] = {
	0xE6,
	0xff, //scr Cr Yb
	0x00, //scr Rr Bb
	0x00, //scr Cg Yg
	0xff, //scr Rg Bg
	0x00, //scr Cb Yr
	0xff, //scr Rb Br
	0x00, //scr Mr Mb
	0xff, //scr Gr Gb
	0xff, //scr Mg Mg
	0x00, //scr Gg Gg
	0x00, //scr Mb Mr
	0xff, //scr Gb Gr
	0x00, //scr Yr Cb
	0xff, //scr Br Rb
	0x00, //scr Yg Cg
	0xff, //scr Bg Rg
	0xff, //scr Yb Cr
	0x00, //scr Bb Rr
	0x00, //scr Wr Wb
	0xff, //scr Kr Kb
	0x00, //scr Wg Wg
	0xff, //scr Kg Kg
	0x00, //scr Wb Wr
	0xff, //scr Kb Kr
};
static char NEGATIVE_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char NEGATIVE_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char NEGATIVE_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char OUTDOOR_VIDEO_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char OUTDOOR_VIDEO_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char OUTDOOR_VIDEO_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char OUTDOOR_VIDEO_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char OUTDOOR_VIDEO_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

#ifndef MDNIE_DATA_NONE
static char COLOR_BLIND_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char COLOR_BLIND_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char COLOR_BLIND_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char COLOR_BLIND_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char COLOR_BLIND_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};
#endif

////////////////// BROWSER /////////////////////

static char STANDARD_BROWSER_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char STANDARD_BROWSER_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char STANDARD_BROWSER_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char STANDARD_BROWSER_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char STANDARD_BROWSER_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char NATURAL_BROWSER_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char NATURAL_BROWSER_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char NATURAL_BROWSER_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char NATURAL_BROWSER_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char NATURAL_BROWSER_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};


static char DYNAMIC_BROWSER_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char DYNAMIC_BROWSER_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char DYNAMIC_BROWSER_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char DYNAMIC_BROWSER_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char DYNAMIC_BROWSER_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char MOVIE_BROWSER_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char MOVIE_BROWSER_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char MOVIE_BROWSER_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char MOVIE_BROWSER_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char MOVIE_BROWSER_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char AUTO_BROWSER_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char AUTO_BROWSER_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char AUTO_BROWSER_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char AUTO_BROWSER_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char AUTO_BROWSER_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

////////////////// eBOOK /////////////////////

static char AUTO_EBOOK_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char AUTO_EBOOK_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char AUTO_EBOOK_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char AUTO_EBOOK_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char AUTO_EBOOK_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char STANDARD_EBOOK_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char STANDARD_EBOOK_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char STANDARD_EBOOK_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char STANDARD_EBOOK_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char STANDARD_EBOOK_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char DYNAMIC_EBOOK_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char DYNAMIC_EBOOK_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char DYNAMIC_EBOOK_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char DYNAMIC_EBOOK_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char DYNAMIC_EBOOK_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char NATURAL_EBOOK_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char NATURAL_EBOOK_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char NATURAL_EBOOK_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char NATURAL_EBOOK_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char NATURAL_EBOOK_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char MOVIE_EBOOK_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char MOVIE_EBOOK_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char MOVIE_EBOOK_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char MOVIE_EBOOK_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char MOVIE_EBOOK_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};

static char AUTO_EMAIL_1[] = {
	0xE5,
	0x00, //roi0 x start
	0x00,
	0x00, //roi0 x end
	0x00,
	0x00, //roi0 y start
	0x00,
	0x00, //roi0 y end
	0x00,
	0x00, //roi1 x strat
	0x00,
	0x00, //roi1 x end
	0x00,
	0x00, //roi1 y start
	0x00,
	0x00, //roi1 y end
	0x00,
};
static char AUTO_EMAIL_2[] = {
	0xE6,
	0x00, //scr Cr Yb
	0xff, //scr Rr Bb
	0xff, //scr Cg Yg
	0x00, //scr Rg Bg
	0xff, //scr Cb Yr
	0x00, //scr Rb Br
	0xff, //scr Mr Mb
	0x00, //scr Gr Gb
	0x00, //scr Mg Mg
	0xff, //scr Gg Gg
	0xff, //scr Mb Mr
	0x00, //scr Gb Gr
	0xff, //scr Yr Cb
	0x00, //scr Br Rb
	0xff, //scr Yg Cg
	0x00, //scr Bg Rg
	0x00, //scr Yb Cr
	0xff, //scr Bb Rr
	0xff, //scr Wr Wb
	0x00, //scr Kr Kb
	0xff, //scr Wg Wg
	0x00, //scr Kg Kg
	0xff, //scr Wb Wr
	0x00, //scr Kb Kr
};
static char AUTO_EMAIL_3[] = {
	0xE7,
	0x00, //curve 1 b
	0x20, //curve 1 a
	0x00, //curve 2 b
	0x20, //curve 2 a
	0x00, //curve 3 b
	0x20, //curve 3 a
	0x00, //curve 4 b
	0x20, //curve 4 a
	0x00, //curve 5 b
	0x20, //curve 5 a
	0x00, //curve 6 b
	0x20, //curve 6 a
	0x00, //curve 7 b
	0x20, //curve 7 a
	0x00, //curve 8 b
	0x20, //curve 8 a
	0x00, //curve 9 b
	0x20, //curve 9 a
	0x00, //curve10 b
	0x20, //curve10 a
	0x00, //curve11 b
	0x20, //curve11 a
	0x00, //curve12 b
	0x20, //curve12 a
	0x00, //curve13 b
	0x20, //curve13 a
	0x00, //curve14 b
	0x20, //curve14 a
	0x00, //curve15 b
	0x20, //curve15 a
	0x00, //curve16 b
	0x20, //curve16 a
	0x00, //curve17 b
	0x20, //curve17 a
	0x00, //curve18 b
	0x20, //curve18 a
	0x00, //curve19 b
	0x20, //curve19 a
	0x00, //curve20 b
	0x20, //curve20 a
	0x00, //curve21 b
	0x20, //curve21 a
	0x00, //curve22 b
	0x20, //curve22 a
	0x00, //curve23 b
	0x20, //curve23 a
	0x00, //curve24 b
	0xFF, //curve24 a
};
static char AUTO_EMAIL_4[] = {
	0xE8,
	0x00, //cc r1
	0x04,
	0x00, //cc r2
	0x00,
	0x00, //cc r3
	0x00,
	0x00, //cc g1
	0x00,
	0x00, //cc g2
	0x04,
	0x00, //cc g3
	0x00,
	0x00, //cc b1
	0x00,
	0x00, //cc b2
	0x00,
	0x00, //cc b3
	0x04,
};
static char AUTO_EMAIL_5[] = {
	0xE4,
	0x01, //mdnie_en
	0x00, //mask 000 roi_ctrl 00
	0x00, //sharpen cc gamma 00 0 0
	0x33, //scr_roi 1 scr algo_roi 1 algo 00 1 0 00 1 0
};


char *blind_tune_value[ACCESSIBILITY_MAX][5] = {
	/*
		ACCESSIBILITY_OFF,
		NEGATIVE,
		COLOR_BLIND,
	*/
	{NULL, NULL, NULL, NULL, NULL},
	{NEGATIVE_1, NEGATIVE_2, NEGATIVE_3, NEGATIVE_4, NEGATIVE_5},
#if defined(MDNIE_DATA_NONE)
	{NULL, NULL, NULL, NULL, NULL},
#else
	{COLOR_BLIND_1, COLOR_BLIND_2, COLOR_BLIND_3, COLOR_BLIND_4, COLOR_BLIND_5},
#endif
};

char *mdnie_tune_value[MAX_mDNIe_MODE][MAX_BACKGROUND_MODE][MAX_OUTDOOR_MODE][5] = {
	/*
		DYNAMIC_MODE (outdoor off/on)
		STANDARD_MODE (outdoor off/on)
		NATURAL_MODE (outdoor off/on)
		MOVIE_MODE (outdoor off/on)
		AUTO_MODE (outdoor off/on)
	*/
	// UI_APP
	{
		{{DYNAMIC_UI_1, DYNAMIC_UI_2, DYNAMIC_UI_3, DYNAMIC_UI_4, DYNAMIC_UI_5}, {NULL, NULL, NULL, NULL}},
		{{STANDARD_UI_1, STANDARD_UI_2, STANDARD_UI_3, STANDARD_UI_4, STANDARD_UI_5}, {NULL, NULL, NULL, NULL}},
		{{NATURAL_UI_1, NATURAL_UI_2, NATURAL_UI_3, NATURAL_UI_4, NATURAL_UI_5}, {NULL, NULL, NULL, NULL}},
		{{MOVIE_UI_1, MOVIE_UI_2, MOVIE_UI_3, MOVIE_UI_4, MOVIE_UI_5}, {NULL, NULL, NULL, NULL}},
		{{AUTO_UI_1, AUTO_UI_2, AUTO_UI_3, AUTO_UI_4, AUTO_UI_5}, {NULL, NULL, NULL, NULL}},
	},
	// VIDEO_APP
	{
		{{DYNAMIC_VIDEO_1, DYNAMIC_VIDEO_2, DYNAMIC_VIDEO_3, DYNAMIC_VIDEO_4, DYNAMIC_VIDEO_5},
			{OUTDOOR_VIDEO_1, OUTDOOR_VIDEO_2, OUTDOOR_VIDEO_3, OUTDOOR_VIDEO_4, OUTDOOR_VIDEO_5}},
		{{STANDARD_VIDEO_1, STANDARD_VIDEO_2, STANDARD_VIDEO_3, STANDARD_VIDEO_4, STANDARD_VIDEO_5},
			{OUTDOOR_VIDEO_1, OUTDOOR_VIDEO_2, OUTDOOR_VIDEO_3, OUTDOOR_VIDEO_4, OUTDOOR_VIDEO_5}},
		{{NATURAL_VIDEO_1, NATURAL_VIDEO_2, NATURAL_VIDEO_3, NATURAL_VIDEO_4, NATURAL_VIDEO_5},
			{OUTDOOR_VIDEO_1, OUTDOOR_VIDEO_2, OUTDOOR_VIDEO_3, OUTDOOR_VIDEO_4, OUTDOOR_VIDEO_5}},
		{{MOVIE_VIDEO_1, MOVIE_VIDEO_2, MOVIE_VIDEO_3, MOVIE_VIDEO_4, MOVIE_VIDEO_5},
			{OUTDOOR_VIDEO_1, OUTDOOR_VIDEO_2, OUTDOOR_VIDEO_3, OUTDOOR_VIDEO_4, OUTDOOR_VIDEO_5}},
		{{AUTO_VIDEO_1, AUTO_VIDEO_2, AUTO_VIDEO_3, AUTO_VIDEO_4, AUTO_VIDEO_5},
			{OUTDOOR_VIDEO_1, OUTDOOR_VIDEO_2, OUTDOOR_VIDEO_3, OUTDOOR_VIDEO_4, OUTDOOR_VIDEO_5}},
	},
	// VIDEO_WARM_APP
	{
		{{WARM_1, WARM_2, WARM_3, WARM_4, WARM_5},
			{WARM_OUTDOOR_1, WARM_OUTDOOR_2, WARM_OUTDOOR_3, WARM_OUTDOOR_4, WARM_OUTDOOR_5}},
		{{WARM_1, WARM_2, WARM_3, WARM_4, WARM_5},
			{WARM_OUTDOOR_1, WARM_OUTDOOR_2, WARM_OUTDOOR_3, WARM_OUTDOOR_4, WARM_OUTDOOR_5}},
		{{WARM_1, WARM_2, WARM_3, WARM_4, WARM_5},
			{WARM_OUTDOOR_1, WARM_OUTDOOR_2, WARM_OUTDOOR_3, WARM_OUTDOOR_4, WARM_OUTDOOR_5}},
		{{WARM_1, WARM_2, WARM_3, WARM_4, WARM_5},
			{WARM_OUTDOOR_1, WARM_OUTDOOR_2, WARM_OUTDOOR_3, WARM_OUTDOOR_4, WARM_OUTDOOR_5}},
		{{WARM_1, WARM_2, WARM_3, WARM_4, WARM_5},
			{WARM_OUTDOOR_1, WARM_OUTDOOR_2, WARM_OUTDOOR_3, WARM_OUTDOOR_4, WARM_OUTDOOR_5}},
	},
	// VIDEO_COLD_APP
	{
		{{COLD_1, COLD_2, COLD_3, COLD_4, COLD_5},
			{COLD_OUTDOOR_1, COLD_OUTDOOR_2, COLD_OUTDOOR_3, COLD_OUTDOOR_4, COLD_OUTDOOR_5}},
		{{COLD_1, COLD_2, COLD_3, COLD_4, COLD_5},
			{COLD_OUTDOOR_1, COLD_OUTDOOR_2, COLD_OUTDOOR_3, COLD_OUTDOOR_4, COLD_OUTDOOR_5}},
		{{COLD_1, COLD_2, COLD_3, COLD_4, COLD_5},
			{COLD_OUTDOOR_1, COLD_OUTDOOR_2, COLD_OUTDOOR_3, COLD_OUTDOOR_4, COLD_OUTDOOR_5}},
		{{COLD_1, COLD_2, COLD_3, COLD_4, COLD_5},
			{COLD_OUTDOOR_1, COLD_OUTDOOR_2, COLD_OUTDOOR_3, COLD_OUTDOOR_4, COLD_OUTDOOR_5}},
		{{COLD_1, COLD_2, COLD_3, COLD_4, COLD_5},
			{COLD_OUTDOOR_1, COLD_OUTDOOR_2, COLD_OUTDOOR_3, COLD_OUTDOOR_4, COLD_OUTDOOR_5}},
	},
	// CAMERA_APP
	{
		{{CAMERA_1, CAMERA_2, CAMERA_3, CAMERA_4, CAMERA_5},
			{CAMERA_OUTDOOR_1, CAMERA_OUTDOOR_2, CAMERA_OUTDOOR_3, CAMERA_OUTDOOR_4, CAMERA_OUTDOOR_5}},
		{{CAMERA_1, CAMERA_2, CAMERA_3, CAMERA_4, CAMERA_5},
			{CAMERA_OUTDOOR_1, CAMERA_OUTDOOR_2, CAMERA_OUTDOOR_3, CAMERA_OUTDOOR_4, CAMERA_OUTDOOR_5}},
		{{CAMERA_1, CAMERA_2, CAMERA_3, CAMERA_4, CAMERA_5},
			{CAMERA_OUTDOOR_1, CAMERA_OUTDOOR_2, CAMERA_OUTDOOR_3, CAMERA_OUTDOOR_4, CAMERA_OUTDOOR_5}},
		{{CAMERA_1, CAMERA_2, CAMERA_3, CAMERA_4, CAMERA_5},
			{CAMERA_OUTDOOR_1, CAMERA_OUTDOOR_2, CAMERA_OUTDOOR_3, CAMERA_OUTDOOR_4, CAMERA_OUTDOOR_5}},
		{{AUTO_CAMERA_1, AUTO_CAMERA_2, AUTO_CAMERA_3, AUTO_CAMERA_4, AUTO_CAMERA_5},
			{CAMERA_OUTDOOR_1, CAMERA_OUTDOOR_2, CAMERA_OUTDOOR_3, CAMERA_OUTDOOR_4, CAMERA_OUTDOOR_5}},
	},
	// NAVI_APP
	{
		{{NULL, NULL, NULL, NULL, NULL}, {NULL, NULL, NULL, NULL, NULL}},
		{{NULL, NULL, NULL, NULL, NULL}, {NULL, NULL, NULL, NULL, NULL}},
		{{NULL, NULL, NULL, NULL, NULL}, {NULL, NULL, NULL, NULL, NULL}},
		{{NULL, NULL, NULL, NULL, NULL}, {NULL, NULL, NULL, NULL, NULL}},
		{{NULL, NULL, NULL, NULL, NULL}, {NULL, NULL, NULL, NULL, NULL}},
	},
	// GALLERY_APP
	{
		{{DYNAMIC_GALLERY_1, DYNAMIC_GALLERY_2, DYNAMIC_GALLERY_3, DYNAMIC_GALLERY_4, DYNAMIC_GALLERY_5},
			{NULL,NULL, NULL, NULL, NULL}},
		{{STANDARD_GALLERY_1, STANDARD_GALLERY_2, STANDARD_GALLERY_3, STANDARD_GALLERY_4, STANDARD_GALLERY_5},
			{NULL,NULL, NULL, NULL, NULL}},
		{{NATURAL_GALLERY_1, NATURAL_GALLERY_2, NATURAL_GALLERY_3, NATURAL_GALLERY_4, NATURAL_GALLERY_5},
			{NULL,NULL, NULL, NULL, NULL}},
		{{MOVIE_GALLERY_1, MOVIE_GALLERY_2, MOVIE_GALLERY_3, MOVIE_GALLERY_4, MOVIE_GALLERY_5},
			{NULL,NULL, NULL, NULL, NULL}},
		{{AUTO_GALLERY_1, AUTO_GALLERY_2, AUTO_GALLERY_3, AUTO_GALLERY_4, AUTO_GALLERY_5},
			{NULL,NULL, NULL, NULL, NULL}},
	},
	// VT_APP
	{
		{{DYNAMIC_VT_1, DYNAMIC_VT_2, DYNAMIC_VT_3, DYNAMIC_VT_4, DYNAMIC_VT_5}, {NULL, NULL, NULL, NULL, NULL}},
		{{STANDARD_VT_1, STANDARD_VT_2, STANDARD_VT_3, STANDARD_VT_4, STANDARD_VT_5}, {NULL, NULL, NULL, NULL, NULL}},
		{{NATURAL_VT_1, NATURAL_VT_2, NATURAL_VT_3, NATURAL_VT_4, NATURAL_VT_5}, {NULL, NULL, NULL, NULL, NULL}},
		{{MOVIE_VT_1, MOVIE_VT_2, MOVIE_VT_3, MOVIE_VT_4, MOVIE_VT_5}, {NULL, NULL, NULL, NULL, NULL}},
		{{AUTO_VT_1, AUTO_VT_2, AUTO_VT_3, AUTO_VT_4, AUTO_VT_5}, {NULL, NULL, NULL, NULL, NULL}},
	},
	// BROWSER_APP
	{
		{{DYNAMIC_BROWSER_1, DYNAMIC_BROWSER_2, DYNAMIC_BROWSER_3, DYNAMIC_BROWSER_4, DYNAMIC_BROWSER_5},
			{NULL, NULL, NULL, NULL, NULL}},
		{{STANDARD_BROWSER_1, STANDARD_BROWSER_2, STANDARD_BROWSER_3, STANDARD_BROWSER_4, STANDARD_BROWSER_5},
			{NULL, NULL, NULL, NULL, NULL}},
		{{NATURAL_BROWSER_1, NATURAL_BROWSER_2, NATURAL_BROWSER_3, NATURAL_BROWSER_4, NATURAL_BROWSER_5},
			{NULL, NULL, NULL, NULL, NULL}},
		{{MOVIE_BROWSER_1, MOVIE_BROWSER_2, MOVIE_BROWSER_3, MOVIE_BROWSER_4, MOVIE_BROWSER_5},
			{NULL, NULL, NULL, NULL, NULL}},
		{{AUTO_BROWSER_1, AUTO_BROWSER_2, AUTO_BROWSER_3, AUTO_BROWSER_4, AUTO_BROWSER_5},
			{NULL, NULL, NULL, NULL, NULL}},
	},
	// eBOOK_APP
	{
		{{DYNAMIC_EBOOK_1, DYNAMIC_EBOOK_2, DYNAMIC_EBOOK_3, DYNAMIC_EBOOK_4, DYNAMIC_EBOOK_5},
			{NULL, NULL, NULL, NULL, NULL}},
		{{STANDARD_EBOOK_1, STANDARD_EBOOK_2, STANDARD_EBOOK_3, STANDARD_EBOOK_4, STANDARD_EBOOK_5},
			{NULL, NULL, NULL, NULL, NULL}},
		{{NATURAL_EBOOK_1, NATURAL_EBOOK_2, NATURAL_EBOOK_3, NATURAL_EBOOK_4, NATURAL_EBOOK_5},
			{NULL, NULL, NULL, NULL, NULL}},
		{{MOVIE_EBOOK_1, MOVIE_EBOOK_2, MOVIE_EBOOK_3, MOVIE_EBOOK_4, MOVIE_EBOOK_5},
			{NULL, NULL, NULL, NULL, NULL}},
		{{AUTO_EBOOK_1, AUTO_EBOOK_2, AUTO_EBOOK_3, AUTO_EBOOK_4, AUTO_EBOOK_5},
			{NULL, NULL, NULL, NULL, NULL}},
	},
	// EMAIL_APP
	{
		{{AUTO_EMAIL_1, AUTO_EMAIL_2, AUTO_EMAIL_3, AUTO_EMAIL_4, AUTO_EMAIL_5}, {NULL, NULL, NULL, NULL, NULL}},
		{{AUTO_EMAIL_1, AUTO_EMAIL_2, AUTO_EMAIL_3, AUTO_EMAIL_4, AUTO_EMAIL_5}, {NULL, NULL, NULL, NULL, NULL}},
		{{AUTO_EMAIL_1, AUTO_EMAIL_2, AUTO_EMAIL_3, AUTO_EMAIL_4, AUTO_EMAIL_5}, {NULL, NULL, NULL, NULL, NULL}},
		{{AUTO_EMAIL_1, AUTO_EMAIL_2, AUTO_EMAIL_3, AUTO_EMAIL_4, AUTO_EMAIL_5}, {NULL, NULL, NULL, NULL, NULL}},
		{{AUTO_EMAIL_1, AUTO_EMAIL_2, AUTO_EMAIL_3, AUTO_EMAIL_4, AUTO_EMAIL_5}, {NULL, NULL, NULL, NULL, NULL}},
	},
};
#endif
