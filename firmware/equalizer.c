/* (C) Copyright 2007 Kai Lauterbach klaute at web.de
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#include "equalizer.h"

void equalizer_0(void)
{

	cube[3][2] += 0x04;

}
void equalizer_1(void)
{

	cube[3][1] += 0x0e;
	cube[3][2] += 0x0a;
	cube[3][3] += 0x0e;

}
void equalizer_2(void)
{

	cube[3][0] += 0x1f;
	cube[3][1] += 0x11;
	cube[3][2] += 0x11;
	cube[3][3] += 0x11;
	cube[3][4] += 0x1f;

}
void equalizer_3(void)
{

	cube[0][7] += 0x80;
	cube[1][0] += 0x80;
	cube[1][1] += 0x80;
	cube[1][2] += 0x80;
	cube[1][3] += 0x80;
	cube[1][4] += 0x80;
	cube[1][5] += 0x80;
	cube[2][7] += 0x3f;
	cube[3][0] += 0x20;
	cube[3][1] += 0x20;
	cube[3][2] += 0x20;
	cube[3][3] += 0x20;
	cube[3][4] += 0x20;
	cube[3][5] += 0x3f;

}
void equalizer_4(void)
{

	cube[0][6] += 0xc0;
	cube[0][7] += 0x40;
	cube[1][0] += 0x40;
	cube[1][1] += 0x40;
	cube[1][2] += 0x40;
	cube[1][3] += 0x40;
	cube[1][4] += 0x40;
	cube[1][5] += 0x40;
	cube[1][6] += 0xc0;
	cube[2][6] += 0x7f;
	cube[2][7] += 0x40;
	cube[3][0] += 0x40;
	cube[3][1] += 0x40;
	cube[3][2] += 0x40;
	cube[3][3] += 0x40;
	cube[3][4] += 0x40;
	cube[3][5] += 0x40;
	cube[3][6] += 0x7f;

}
void equalizer_5(void)
{

	cube[0][5] += 0xe0;
	cube[0][6] += 0x20;
	cube[0][7] += 0x20;
	cube[1][0] += 0x20;
	cube[1][1] += 0x20;
	cube[1][2] += 0x20;
	cube[1][3] += 0x20;
	cube[1][4] += 0x20;
	cube[1][5] += 0x20;
	cube[1][6] += 0x20;
	cube[1][7] += 0xe0;
	cube[2][5] += 0xff;
	cube[2][6] += 0x80;
	cube[2][7] += 0x80;
	cube[3][0] += 0x80;
	cube[3][1] += 0x80;
	cube[3][2] += 0x80;
	cube[3][3] += 0x80;
	cube[3][4] += 0x80;
	cube[3][5] += 0x80;
	cube[3][6] += 0x80;
	cube[3][7] += 0xff;

}
void equalizer_6(void)
{

	cube[0][4] += 0xf0;
	cube[0][5] += 0x10;
	cube[0][6] += 0x10;
	cube[0][7] += 0x10;
	cube[1][0] += 0x10;
	cube[1][1] += 0x10;
	cube[1][2] += 0x10;
	cube[1][3] += 0x10;
	cube[1][4] += 0x10;
	cube[1][5] += 0x10;
	cube[1][6] += 0x10;
	cube[1][7] += 0x10;
	cube[2][4] += 0xff;
	cube[4][0] += 0xf0;
	cube[4][4] += 0xff;
	cube[5][0] += 0xf0;
	cube[5][4] += 0xff;
	cube[6][0] += 0x01;

}
void equalizer_7(void)
{

	cube[0][3] += 0xf8;
	cube[0][4] += 0x08;
	cube[0][5] += 0x08;
	cube[0][6] += 0x08;
	cube[0][7] += 0x08;
	cube[1][0] += 0x08;
	cube[1][1] += 0x08;
	cube[1][2] += 0x08;
	cube[1][3] += 0x08;
	cube[1][4] += 0x08;
	cube[1][5] += 0x08;
	cube[1][6] += 0x08;
	cube[1][7] += 0x08;
	cube[2][3] += 0xff;
	cube[4][0] += 0x08;
	cube[4][1] += 0xf8;
	cube[4][5] += 0xff;
	cube[5][0] += 0x08;
	cube[5][1] += 0xf8;
	cube[5][5] += 0xff;
	cube[6][0] += 0x02;
	cube[6][1] += 0x03;

}
void equalizer_8(void)
{

	cube[0][2] += 0xfc;
	cube[0][3] += 0x04;
	cube[0][4] += 0x04;
	cube[0][5] += 0x04;
	cube[0][6] += 0x04;
	cube[0][7] += 0x04;
	cube[1][0] += 0x04;
	cube[1][1] += 0x04;
	cube[1][2] += 0x04;
	cube[1][3] += 0x04;
	cube[1][4] += 0x04;
	cube[1][5] += 0x04;
	cube[1][6] += 0x04;
	cube[1][7] += 0x04;
	cube[2][2] += 0xff;
	cube[4][0] += 0x04;
	cube[4][1] += 0x04;
	cube[4][2] += 0xfc;
	cube[4][6] += 0xff;
	cube[5][0] += 0x04;
	cube[5][1] += 0x04;
	cube[5][2] += 0xfc;
	//cube[5][6] += 0xbf;
	cube[5][6] += 0xff;
	cube[6][0] += 0x04;
	cube[6][1] += 0x04;
	cube[6][2] += 0x07;

}
void equalizer_9(void)
{

	cube[0][1] += 0xfe;
	cube[0][2] += 0x02;
	cube[0][3] += 0x02;
	cube[0][4] += 0x02;
	cube[0][5] += 0x02;
	cube[0][6] += 0x02;
	cube[0][7] += 0x02;
	cube[1][0] += 0x02;
	cube[1][1] += 0x02;
	cube[1][2] += 0x02;
	cube[1][3] += 0x02;
	cube[1][4] += 0x02;
	cube[1][5] += 0x02;
	cube[1][6] += 0x02;
	cube[1][7] += 0x02;
	cube[2][1] += 0xff;
	cube[4][0] += 0x02;
	cube[4][1] += 0x02;
	cube[4][2] += 0x02;
	cube[4][3] += 0xfe;
	cube[4][7] += 0xff;
	cube[5][0] += 0x02;
	cube[5][1] += 0x02;
	cube[5][2] += 0x02;
	cube[5][3] += 0xfe;
	cube[5][7] += 0xff;
	cube[6][0] += 0x08;
	cube[6][1] += 0x08;
	cube[6][2] += 0x08;
	cube[6][3] += 0x0f;

}
void equalizer_10(void)
{

	cube[0][0] += 0xff;
	cube[0][1] += 0x01;
	cube[0][2] += 0x01;
	cube[0][3] += 0x01;
	cube[0][4] += 0x01;
	cube[0][5] += 0x01;
	cube[0][6] += 0x01;
	cube[0][7] += 0x01;
	cube[1][0] += 0x01;
	cube[1][1] += 0x01;
	cube[1][2] += 0x01;
	cube[1][3] += 0x01;
	cube[1][4] += 0x01;
	cube[1][5] += 0x01;
	cube[1][6] += 0x01;
	cube[1][7] += 0x01;
	cube[2][0] += 0xff;
	cube[4][0] += 0x01;
	cube[4][1] += 0x01;
	cube[4][2] += 0x01;
	cube[4][3] += 0x01;
	cube[5][0] += 0x01;
	cube[5][1] += 0x01;
	cube[5][2] += 0x01;
	cube[5][3] += 0x01;
	cube[6][0] += 0x10;
	cube[6][1] += 0x10;
	cube[6][2] += 0x10;
	cube[6][3] += 0x10;
	cube[6][4] += 0x1f;
	cube[7][0] += 0xff;
	cube[7][1] += 0xff;
	cube[7][2] += 0xff;
	cube[7][3] += 0xff;

}
//-----------------------------------------------------------

void equalizer_clear_0(void)
{
	if ( cube[3][2] >= 0x04 )
		cube[3][2] -= 0x04;
}

void equalizer_clear_1(void)
{
	if ( cube[3][1] >= 0x0e )
		cube[3][1] -= 0x0e;
	if ( cube[3][2] >= 0x0a )
		cube[3][2] -= 0x0a;
	if ( cube[3][3] >= 0x0e )
		cube[3][3] -= 0x0e;
}

void equalizer_clear_2(void)
{
	if ( cube[3][0] >= 0x1f )
		cube[3][0] -= 0x1f;
	if ( cube[3][1] >= 0x11 )
		cube[3][1] -= 0x11;
	if ( cube[3][2] >= 0x11 )
		cube[3][2] -= 0x11;
	if ( cube[3][3] >= 0x11 )
		cube[3][3] -= 0x11;
	if ( cube[3][4] >= 0x1f )
		cube[3][4] -= 0x1f;
}

void equalizer_clear_3(void)
{
	if ( cube[0][7] >= 0x80 )
		cube[0][7] -= 0x80;
	if ( cube[1][0] >= 0x80 )
		cube[1][0] -= 0x80;
	if ( cube[1][1] >= 0x80 )
		cube[1][1] -= 0x80;
	if ( cube[1][2] >= 0x80 )
		cube[1][2] -= 0x80;
	if ( cube[1][3] >= 0x80 )
		cube[1][3] -= 0x80;
	if ( cube[1][4] >= 0x80 )
		cube[1][4] -= 0x80;
	if ( cube[1][5] >= 0x80 )
		cube[1][5] -= 0x80;
	if ( cube[2][7] >= 0x3f )
		cube[2][7] -= 0x3f;
	if ( cube[3][0] >= 0x20 )
		cube[3][0] -= 0x20;
	if ( cube[3][1] >= 0x20 )
		cube[3][1] -= 0x20;
	if ( cube[3][2] >= 0x20 )
		cube[3][2] -= 0x20;
	if ( cube[3][3] >= 0x20 )
		cube[3][3] -= 0x20;
	if ( cube[3][4] >= 0x20 )
		cube[3][4] -= 0x20;
	if ( cube[3][5] >= 0x3f )
		cube[3][5] -= 0x3f;
}

void equalizer_clear_4(void)
{
	if ( cube[0][6] >= 0xc0 )
		cube[0][6] -= 0xc0;
	if ( cube[0][7] >= 0x40 )
		cube[0][7] -= 0x40;
	if ( cube[1][0] >= 0x40 )
		cube[1][0] -= 0x40;
	if ( cube[1][1] >= 0x40 )
		cube[1][1] -= 0x40;
	if ( cube[1][2] >= 0x40 )
		cube[1][2] -= 0x40;
	if ( cube[1][3] >= 0x40 )
		cube[1][3] -= 0x40;
	if ( cube[1][4] >= 0x40 )
		cube[1][4] -= 0x40;
	if ( cube[1][5] >= 0x40 )
		cube[1][5] -= 0x40;
	if ( cube[1][6] >= 0xc0 )
		cube[1][6] -= 0xc0;
	if ( cube[2][6] >= 0x7f )
		cube[2][6] -= 0x7f;
	if ( cube[2][7] >= 0x40 )
		cube[2][7] -= 0x40;
	if ( cube[3][0] >= 0x40 )
		cube[3][0] -= 0x40;
	if ( cube[3][1] >= 0x40 )
		cube[3][1] -= 0x40;
	if ( cube[3][2] >= 0x40 )
		cube[3][2] -= 0x40;
	if ( cube[3][3] >= 0x40 )
		cube[3][3] -= 0x40;
	if ( cube[3][4] >= 0x40 )
		cube[3][4] -= 0x40;
	if ( cube[3][5] >= 0x40 )
		cube[3][5] -= 0x40;
	if ( cube[3][6] >= 0x7f )
		cube[3][6] -= 0x7f;
}

void equalizer_clear_5(void)
{
	if ( cube[0][5] >= 0xe0 )
		cube[0][5] -= 0xe0;
	if ( cube[0][6] >= 0x20 )
		cube[0][6] -= 0x20;
	if ( cube[0][7] >= 0x20 )
		cube[0][7] -= 0x20;
	if ( cube[1][0] >= 0x20 )
		cube[1][0] -= 0x20;
	if ( cube[1][1] >= 0x20 )
		cube[1][1] -= 0x20;
	if ( cube[1][2] >= 0x20 )
		cube[1][2] -= 0x20;
	if ( cube[1][3] >= 0x20 )
		cube[1][3] -= 0x20;
	if ( cube[1][4] >= 0x20 )
		cube[1][4] -= 0x20;
	if ( cube[1][5] >= 0x20 )
		cube[1][5] -= 0x20;
	if ( cube[1][6] >= 0x20 )
		cube[1][6] -= 0x20;
	if ( cube[1][7] >= 0xe0 )
		cube[1][7] -= 0xe0;
	if ( cube[2][5] >= 0xff )
		cube[2][5] -= 0xff;
	if ( cube[2][6] >= 0x80 )
		cube[2][6] -= 0x80;
	if ( cube[2][7] >= 0x80 )
		cube[2][7] -= 0x80;
	if ( cube[3][0] >= 0x80 )
		cube[3][0] -= 0x80;
	if ( cube[3][1] >= 0x80 )
		cube[3][1] -= 0x80;
	if ( cube[3][2] >= 0x80 )
		cube[3][2] -= 0x80;
	if ( cube[3][3] >= 0x80 )
		cube[3][3] -= 0x80;
	if ( cube[3][4] >= 0x80 )
		cube[3][4] -= 0x80;
	if ( cube[3][5] >= 0x80 )
		cube[3][5] -= 0x80;
	if ( cube[3][6] >= 0x80 )
		cube[3][6] -= 0x80;
	if ( cube[3][7] >= 0xff )
		cube[3][7] -= 0xff;
}

void equalizer_clear_6(void)
{
	if ( cube[0][4] >= 0xf0 )
		cube[0][4] -= 0xf0;
	if ( cube[0][5] >= 0x10 )
		cube[0][5] -= 0x10;
	if ( cube[0][6] >= 0x10 )
		cube[0][6] -= 0x10;
	if ( cube[0][7] >= 0x10 )
		cube[0][7] -= 0x10;
	if ( cube[1][0] >= 0x10 )
		cube[1][0] -= 0x10;
	if ( cube[1][1] >= 0x10 )
		cube[1][1] -= 0x10;
	if ( cube[1][2] >= 0x10 )
		cube[1][2] -= 0x10;
	if ( cube[1][3] >= 0x10 )
		cube[1][3] -= 0x10;
	if ( cube[1][4] >= 0x10 )
		cube[1][4] -= 0x10;
	if ( cube[1][5] >= 0x10 )
		cube[1][5] -= 0x10;
	if ( cube[1][6] >= 0x10 )
		cube[1][6] -= 0x10;
	if ( cube[1][7] >= 0x10 )
		cube[1][7] -= 0x10;
	if ( cube[2][4] >= 0xff )
		cube[2][4] -= 0xff;
	if ( cube[4][0] >= 0xf0 )
		cube[4][0] -= 0xf0;
	if ( cube[4][4] >= 0xff )
		cube[4][4] -= 0xff;
	if ( cube[5][0] >= 0xf0 )
		cube[5][0] -= 0xf0;
	if ( cube[5][4] >= 0xff )
		cube[5][4] -= 0xff;
	if ( cube[6][0] >= 0x01 )
		cube[6][0] -= 0x01;
}

void equalizer_clear_7(void)
{
	if ( cube[0][3] >= 0xf8 )
		cube[0][3] -= 0xf8;
	if ( cube[0][4] >= 0x08 )
		cube[0][4] -= 0x08;
	if ( cube[0][5] >= 0x08 )
		cube[0][5] -= 0x08;
	if ( cube[0][6] >= 0x08 )
		cube[0][6] -= 0x08;
	if ( cube[0][7] >= 0x08 )
		cube[0][7] -= 0x08;
	if ( cube[1][0] >= 0x08 )
		cube[1][0] -= 0x08;
	if ( cube[1][1] >= 0x08 )
		cube[1][1] -= 0x08;
	if ( cube[1][2] >= 0x08 )
		cube[1][2] -= 0x08;
	if ( cube[1][3] >= 0x08 )
		cube[1][3] -= 0x08;
	if ( cube[1][4] >= 0x08 )
		cube[1][4] -= 0x08;
	if ( cube[1][5] >= 0x08 )
		cube[1][5] -= 0x08;
	if ( cube[1][6] >= 0x08 )
		cube[1][6] -= 0x08;
	if ( cube[1][7] >= 0x08 )
		cube[1][7] -= 0x08;
	if ( cube[2][3] >= 0xff )
		cube[2][3] -= 0xff;
	if ( cube[4][0] >= 0x08 )
		cube[4][0] -= 0x08;
	if ( cube[4][1] >= 0xf8 )
		cube[4][1] -= 0xf8;
	if ( cube[4][5] >= 0xff )
		cube[4][5] -= 0xff;
	if ( cube[5][0] >= 0x08 )
		cube[5][0] -= 0x08;
	if ( cube[5][1] >= 0xf8 )
		cube[5][1] -= 0xf8;
	if ( cube[5][5] >= 0xff )
		cube[5][5] -= 0xff;
	if ( cube[6][0] >= 0x02 )
		cube[6][0] -= 0x02;
	if ( cube[6][1] >= 0x03 )
		cube[6][1] -= 0x03;
}

void equalizer_clear_8(void)
{
	if ( cube[0][2] >= 0xfc )
		cube[0][2] -= 0xfc;
	if ( cube[0][3] >= 0x04 )
		cube[0][3] -= 0x04;
	if ( cube[0][4] >= 0x04 )
		cube[0][4] -= 0x04;
	if ( cube[0][5] >= 0x04 )
		cube[0][5] -= 0x04;
	if ( cube[0][6] >= 0x04 )
		cube[0][6] -= 0x04;
	if ( cube[0][7] >= 0x04 )
		cube[0][7] -= 0x04;
	if ( cube[1][0] >= 0x04 )
		cube[1][0] -= 0x04;
	if ( cube[1][1] >= 0x04 )
		cube[1][1] -= 0x04;
	if ( cube[1][2] >= 0x04 )
		cube[1][2] -= 0x04;
	if ( cube[1][3] >= 0x04 )
		cube[1][3] -= 0x04;
	if ( cube[1][4] >= 0x04 )
		cube[1][4] -= 0x04;
	if ( cube[1][5] >= 0x04 )
		cube[1][5] -= 0x04;
	if ( cube[1][6] >= 0x04 )
		cube[1][6] -= 0x04;
	if ( cube[1][7] >= 0x04 )
		cube[1][7] -= 0x04;
	if ( cube[2][2] >= 0xff )
		cube[2][2] -= 0xff;
	if ( cube[4][0] >= 0x04 )
		cube[4][0] -= 0x04;
	if ( cube[4][1] >= 0x04 )
		cube[4][1] -= 0x04;
	if ( cube[4][2] >= 0xfc )
		cube[4][2] -= 0xfc;
	if ( cube[4][6] >= 0xff )
		cube[4][6] -= 0xff;
	if ( cube[5][0] >= 0x04 )
		cube[5][0] -= 0x04;
	if ( cube[5][1] >= 0x04 )
		cube[5][1] -= 0x04;
	if ( cube[5][2] >= 0xfc )
		cube[5][2] -= 0xfc;
	if ( cube[5][6] >= 0xbf )
		cube[5][6] -= 0xbf;
	if ( cube[6][0] >= 0x04 )
		cube[6][0] -= 0x04;
	if ( cube[6][1] >= 0x04 )
		cube[6][1] -= 0x04;
	if ( cube[6][2] >= 0x07 )
		cube[6][2] -= 0x07;
}

void equalizer_clear_9(void)
{
	if ( cube[0][1] >= 0xfe )
		cube[0][1] -= 0xfe;
	if ( cube[0][2] >= 0x02 )
		cube[0][2] -= 0x02;
	if ( cube[0][3] >= 0x02 )
		cube[0][3] -= 0x02;
	if ( cube[0][4] >= 0x02 )
		cube[0][4] -= 0x02;
	if ( cube[0][5] >= 0x02 )
		cube[0][5] -= 0x02;
	if ( cube[0][6] >= 0x02 )
		cube[0][6] -= 0x02;
	if ( cube[0][7] >= 0x02 )
		cube[0][7] -= 0x02;
	if ( cube[1][0] >= 0x02 )
		cube[1][0] -= 0x02;
	if ( cube[1][1] >= 0x02 )
		cube[1][1] -= 0x02;
	if ( cube[1][2] >= 0x02 )
		cube[1][2] -= 0x02;
	if ( cube[1][3] >= 0x02 )
		cube[1][3] -= 0x02;
	if ( cube[1][4] >= 0x02 )
		cube[1][4] -= 0x02;
	if ( cube[1][5] >= 0x02 )
		cube[1][5] -= 0x02;
	if ( cube[1][6] >= 0x02 )
		cube[1][6] -= 0x02;
	if ( cube[1][7] >= 0x02 )
		cube[1][7] -= 0x02;
	if ( cube[2][1] >= 0xff )
		cube[2][1] -= 0xff;
	if ( cube[4][0] >= 0x02 )
		cube[4][0] -= 0x02;
	if ( cube[4][1] >= 0x02 )
		cube[4][1] -= 0x02;
	if ( cube[4][2] >= 0x02 )
		cube[4][2] -= 0x02;
	if ( cube[4][3] >= 0xfe )
		cube[4][3] -= 0xfe;
	if ( cube[4][7] >= 0xff )
		cube[4][7] -= 0xff;
	if ( cube[5][0] >= 0x02 )
		cube[5][0] -= 0x02;
	if ( cube[5][1] >= 0x02 )
		cube[5][1] -= 0x02;
	if ( cube[5][2] >= 0x02 )
		cube[5][2] -= 0x02;
	if ( cube[5][3] >= 0xfe )
		cube[5][3] -= 0xfe;
	if ( cube[5][7] >= 0xff )
		cube[5][7] -= 0xff;
	if ( cube[6][0] >= 0x08 )
		cube[6][0] -= 0x08;
	if ( cube[6][1] >= 0x08 )
		cube[6][1] -= 0x08;
	if ( cube[6][2] >= 0x08 )
		cube[6][2] -= 0x08;
	if ( cube[6][3] >= 0x0f )
		cube[6][3] -= 0x0f;
}

void equalizer_clear_10(void)
{
	if ( cube[0][0] >= 0xff )
		cube[0][0] -= 0xff;
	if ( cube[0][1] >= 0x01 )
		cube[0][1] -= 0x01;
	if ( cube[0][2] >= 0x01 )
		cube[0][2] -= 0x01;
	if ( cube[0][3] >= 0x01 )
		cube[0][3] -= 0x01;
	if ( cube[0][4] >= 0x01 )
		cube[0][4] -= 0x01;
	if ( cube[0][5] >= 0x01 )
		cube[0][5] -= 0x01;
	if ( cube[0][6] >= 0x01 )
		cube[0][6] -= 0x01;
	if ( cube[0][7] >= 0x01 )
		cube[0][7] -= 0x01;
	if ( cube[1][0] >= 0x01 )
		cube[1][0] -= 0x01;
	if ( cube[1][1] >= 0x01 )
		cube[1][1] -= 0x01;
	if ( cube[1][2] >= 0x01 )
		cube[1][2] -= 0x01;
	if ( cube[1][3] >= 0x01 )
		cube[1][3] -= 0x01;
	if ( cube[1][4] >= 0x01 )
		cube[1][4] -= 0x01;
	if ( cube[1][5] >= 0x01 )
		cube[1][5] -= 0x01;
	if ( cube[1][6] >= 0x01 )
		cube[1][6] -= 0x01;
	if ( cube[1][7] >= 0x01 )
		cube[1][7] -= 0x01;
	if ( cube[2][0] >= 0xff )
		cube[2][0] -= 0xff;
	if ( cube[4][0] >= 0x01 )
		cube[4][0] -= 0x01;
	if ( cube[4][1] >= 0x01 )
		cube[4][1] -= 0x01;
	if ( cube[4][2] >= 0x01 )
		cube[4][2] -= 0x01;
	if ( cube[4][3] >= 0x01 )
		cube[4][3] -= 0x01;
	if ( cube[5][0] >= 0x01 )
		cube[5][0] -= 0x01;
	if ( cube[5][1] >= 0x01 )
		cube[5][1] -= 0x01;
	if ( cube[5][2] >= 0x01 )
		cube[5][2] -= 0x01;
	if ( cube[5][3] >= 0x01 )
		cube[5][3] -= 0x01;
	if ( cube[6][0] >= 0x10 )
		cube[6][0] -= 0x10;
	if ( cube[6][1] >= 0x10 )
		cube[6][1] -= 0x10;
	if ( cube[6][2] >= 0x10 )
		cube[6][2] -= 0x10;
	if ( cube[6][3] >= 0x10 )
		cube[6][3] -= 0x10;
	if ( cube[6][4] >= 0x1f )
		cube[6][4] -= 0x1f;
	if ( cube[7][0] >= 0xff )
		cube[7][0] -= 0xff;
	if ( cube[7][1] >= 0xff )
		cube[7][1] -= 0xff;
	if ( cube[7][2] >= 0xff )
		cube[7][2] -= 0xff;
	if ( cube[7][3] >= 0xff )
		cube[7][3] -= 0xff;
}

