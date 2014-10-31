
/*=============================================================================
  bmplib, a simple library to create, modify, and write BMP image files.
  Copyright (C) 2009-2013 by Zack T Smith.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License version 2 
  as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  The author may be reached at veritas@comcast.net.
 *============================================================================*/

#include <stdio.h>
#include <math.h>
#include "BMP.h"

int
main()
{
	int i,j;
	double angle;
	int w = 1003;
	int h = 725;
	float w2 = (float) w/2;
	float h2 = (float) h/2;

	//----------------------------------------
	// Create BMP image with black background.
	//
	BMP *bmp = BMP_new (w, h);

	//----------------------------------------
	// Set background to red.
	//
	BMP_clear (bmp, RGB_RED);

	//----------------------------------------
	// Draw green line from upper left.
	//
	for (i=0; i < h; i++) {
		BMP_point (bmp, i, i, RGB_GREEN);
	}

	//----------------------------------------
	// Draw blue line from upper right.
	//
	for (i=0; i < h; i++) {
		BMP_point (bmp, w-1-i, i, RGB_ORANGE);
	}

	//----------------------------------------
	// Draw white spiral.
	//
#define TWOPI (M_PI * 2.0)
	for (angle = 0.0; angle < TWOPI; angle += 0.0001) {
		double distance = h2 * angle / TWOPI;
		double x = sin (angle) * distance + w2;
		double y = cos (angle) * distance + h2;

		BMP_point (bmp, (int)x, (int)y, RGB_WHITE);
	}

	//----------------------------------------
	// Draw yellow oval. 
	//
	for (angle = 0.0; angle < TWOPI; angle += 0.0001) {
		double x = sin (angle) * w2 + w2;
		double y = cos (angle) * h2 + h2;

		BMP_point (bmp, (int)x, (int)y, RGB_YELLOW);
	}

	//----------------------------------------
	// Draw some small text.
	//
	BMP_draw_mini_string (bmp, "!@#$%^&*()-+=/_\\,.<=^=> This is a test...? (yes a test) pi=3.1415926536 [approx.]", 100, 100, RGB_YELLOW);

	//----------------------------------------
	// Draw some 14-point text.
	//
	BMP_draw_string (bmp, "!@#$%^&*()-+=/_\\,.<=^=> This is a test...? (yes a test) pi=3.1415926536 [approx.]", 100, 140, RGB_WHITE);

	//----------------------------------------
	// Fill some rectangles.
	//
	int x = 780;
	int y = 200;
	BMP_fillrect (bmp, x, y, 50, 75, RGB_PURPLE); x += 30; y += 40;
	BMP_fillrect (bmp, x, y, 50, 75, RGB_BLUE); x += 30; y += 40;
	BMP_fillrect (bmp, x, y, 50, 75, RGB_GREEN); x += 30; y += 40;

	//----------------------------------------
	// Draw a gradient.
	//
	for (i = 0; i < 256; i++)
		BMP_fillrect (bmp, x, i+y, 50, 1, (255-i) + (i << 8)); 

	//----------------------------------------
	// Draw grid.
	//
	for (i=200; i <= 400; i+=10) 
		BMP_vline (bmp, i, 200, 400, RGB_WHITE);
	for (j=200; j <= 400; j+=10) 
		BMP_hline (bmp, 200, 400, j, RGB_YELLOW);

	//----------------------------------------
	// Draw some lines.
	//
	for (i=0; i < 400; i+=10) 
		BMP_line (bmp, 600+i, 720, 1000, 720-i, RGB_CYAN);

	//----------------------------------------
	// Write the image file.
	//
	if (1 == BMP_write (bmp, "bmplib.bmp"))
		puts ("Created file bmplib.bmp.");

	BMP_delete (bmp);

	return 0;
}
