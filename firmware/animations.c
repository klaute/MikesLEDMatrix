/*
fornax LED cube V1.0

Copyright (C) 2009 Andreas Fiessler aka fornax

Changed by Kai Lauterbach (klaute at gmail.com) aka klaute 2010-02-11
to get it work with Mike's LED Matrix. See http://klautesblog.blogspot.com/ for details.

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include "ab.h"
#include "ledcube.h"
#include "animations.h"
#include <stdlib.h>
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "rotation.h"
#include "translation.h"

/* shrinking outline */
void outline_shrink( void )
{
	cube_clear();
	uint8_t i;
	for (i = 1; i < 7; i++ ){
		cube[i][0] = 0b10000001;
		cube[i][7] = 0b10000001;
	}
	for (i = 1; i < 7; i++){
		cube[0][i] = 0b10000001;
		cube[7][i] = 0b10000001;
	}
	cube[0][0] = 0xFF;
	cube[7][0] = 0xFF;
	cube[0][7] = 0xFF;
	cube[7][7] = 0xFF;
	cube_show_loop(OUT_SHRINK_DELAY);

	for (i = 2; i < 6; i++ ){
		cube[i][1] = 0b01000010;
		cube[i][6] = 0b01000010;
	}
	for (i = 2; i < 6; i++){
		cube[1][i] = 0b01000010;
		cube[6][i] = 0b01000010;
	}
	cube[1][1] = 0b01111110;
	cube[6][1] = 0b01111110;
	cube[1][6] = 0b01111110;
	cube[6][6] = 0b01111110;
	cube_show_loop(OUT_SHRINK_DELAY);

	for (i = 3; i < 5; i++ ){
		cube[i][2] = 0b00100100;
		cube[i][5] = 0b00100100;
	}
	for (i = 3; i < 5; i++){
		cube[2][i] = 0b00100100;
		cube[5][i] = 0b00100100;
	}
	cube[2][2] = 0b00111100;
	cube[5][2] = 0b00111100;
	cube[2][5] = 0b00111100;
	cube[5][5] = 0b00111100;
	cube_show_loop(OUT_SHRINK_DELAY);

	cube[3][3] = 0b00011000;
	cube[4][3] = 0b00011000;
	cube[3][4] = 0b00011000;
	cube[4][4] = 0b00011000;	
	cube_show_loop(10*OUT_SHRINK_DELAY);
}


/* explosion illuminate all starting at middle an turn off in same order */
void cube_explosion( void )
{
	uint8_t led_state = 0b00011000;
	uint8_t i;
	for (i = 0; i <= 4; i++){
		uint8_t j;
		for (j = 3; j <= (i+3); j++) {
			uint8_t k;
			for (k = 3; k <= (i+3); k++){
				cube[j][7-k] = led_state;
				cube[j][k] = led_state;
				cube[7-j][7-k] = led_state;
				cube[7-j][k] = led_state;
			}
		}
		cube_show_loop(EXPLOSION_DELAY*(2*i+1));
		led_state |= (1 << (3-i)) | (1 << (4+i));
	}
	cube_show_loop(EXPLOSION_DELAY);
	for (i = 0; i <= 4; i++){
		led_state &= ~((1 << (3-i)) | (1 << (4+i)));
		uint8_t j;
		for (j = 3; j <= (i+3); j++) {
			uint8_t k;
			for (k = 3; k <= (i+3); k++){
				cube[j][7-k] = led_state;
				cube[j][k] = led_state;
				cube[7-j][7-k] = led_state;
				cube[7-j][k] = led_state;
			}
		}
		cube_show_loop(EXPLOSION_DELAY*(2*i+1));
	}
	cube_show_loop(EXPLOSION_DELAY);
}

/* wipe */
void cube_wipe( void )
{
	cube_test_y();
	cube_show_loop(SWIPE_DELAY);
	uint8_t layer;
	for (layer = 0; layer < 7; layer++){	
		uint8_t i;
		for (i = 0; i < 8; i++){
			cube[layer][i] = 0;
			cube[layer+1][i] = 0xFF;
		}
		cube_show_loop(SWIPE_DELAY);
	}
	for (layer = 0; layer < 7; layer++){	
		move_y_rev(0,0,7,7);
		cube_show_loop(SWIPE_DELAY);
	}
}

/* moving chars on a belt
 * a cute function to display larger strings.
 * we need to define an own layer for the chars
 * which is then transformed to the cube array 
 */

void cube_string_belt( char *string )
{
	/* 2D 
	 * bits are Y, 0 is bottom, 7 is top
	 * 0 is the right end where the chars come in
	 * 20 visible lines, 5 are added to the "beginning"
	 * outside the cube so the chars can move in
	 */
	char cube_belt[25];
	uint8_t i;
	for (i = 0; i < 25; i++) { cube_belt[i] = 0; }

	string++;
	string++;
	while(*string){
		set_char_to_belt(*string, cube_belt);
		uint8_t i;
		for (i = 0; i < 6; i++){
			show_belt(cube_belt);
			move_belt_left(cube_belt);
		}
		string++;
	}
	/* move the rest out */
	for (i = 0; i < 18; i++){
		show_belt(cube_belt);
		move_belt_left(cube_belt);
	}
}

void move_belt_left( char *belt )
{
	uint8_t i;
	for (i = 25; i > 1; i--){
		belt[i-1] = belt[i-2];
	}
	belt[0] = 0;
}
/*
 * set a char to the cube array, then transform this char to
 * the first 5 elements of the belt array 
 */
void set_char_to_belt( char character, char *belt )
{	
	cube_clear();
	cli();
	PORTC = 0x00;
	cube_char(character, 1);
	uint8_t layer;
	for (layer = 0; layer < 8; layer++) {
		uint8_t i;
		for (i = 1; i < 6; i++){
			if (cube[layer][i] & 0x01) 
				belt[5-i] |= (1 << layer);
		}
	}
	cube_clear();
	sei();
}

/* this function passes the given array to the cube array */
void show_belt( char *belt )
{
	cube_clear();
	/* right side */
	uint8_t i;
	for (i = 5; i <= 11; i++){
		uint8_t j;
		for (j = 0; j < 8; j++){
			if (belt[i] & (1 << j))
				cube[j][7] |= (1 << (12-i));
		}
	}
	/* front side */
	for (i = 12; i <= 17; i++){
		uint8_t j;
		for (j = 0; j < 8; j++){
			if (belt[i] & (1 << j))
				cube[j][18-i] |= (1 << 0);
		}
	}
	/* left side */
	for (i = 18; i <= 24; i++){
		uint8_t j;
		for (j = 0; j < 8; j++){
			if (belt[i] & (1 << j))
				cube[j][0] |= (1 << (i-17));
		}
	}
	cube_show_loop(SHOW_BELT_DELAY);
}

/* 2 fixed chars rotating */
void cube_fixed_string( void )
{
	cube_clear();
	cube_clear();
	cube_char('3', 2);
	rotate_90_deg();
	rotate_90_deg();
	cube_char('d', 2);
	rotate_90_deg();

	rotate_90_auto(8);
}


/* back to front moving */
void cube_string_to_front( char *string )
{
	while(*string) {	
		uint8_t i;
		for (i = 8; i > 0; i--){
			cube_clear();
			cube_char(*string, (1 << (i-1)));
			cube_show_loop(3);
		}
		string++;
	}

}

/* automated text display, takes a string and adds
 * some effects. Usable for short strings.
 */
void cube_string( char *string )
{
	while(*string){
		cube_clear();
		cli();
		PORTC = 0x00;
		cube_char(*string, 16);
		string++;
		rotate_90_deg();
		rotate_90_deg();
		rotate_90_deg();
		move_x_rev(1,0,6,7);
		move_x_rev(1,0,6,7);
		move_x_rev(1,0,6,7);
		sei();
		cube_show_loop(CUBE_STRING_DELAY);
		move_x_fwd(1,0,6,7);
		cube_show_loop(CUBE_STRING_DELAY);
		move_x_fwd(1,0,6,7);
		cube_show_loop(CUBE_STRING_DELAY);
		move_x_fwd(1,0,6,7);
		cube_show_loop(CUBE_STRING_DELAY);
		rotate_90_auto(1);
		move_z_rev(0,0,7,7);
		cube_show_loop(CUBE_STRING_DELAY);
		move_z_rev(0,0,7,7);
		cube_show_loop(CUBE_STRING_DELAY);
		move_z_rev(0,0,7,7);
		cube_show_loop(CUBE_STRING_DELAY);
		move_z_rev(0,0,7,7);
		cube_show_loop(CUBE_STRING_DELAY);
		cube_flash(5);
		cube_explosion();
	}
	cube_explosion();
	cube_explosion();
}

void cube_outline( void )
{
	cube_clear();
	cube_show_loop(OUTLINE_DELAY);
	uint8_t i;
	for (i = 0; i < 8; i++) {
		cube[0][0] |= (1 << i);
		cube[i][0] |= 1;
		cube[0][i] |= 1;
		cube_show_loop(OUTLINE_DELAY);
	}
	for (i = 1; i < 8; i++) {
		cube[7][0] |= (1 << i);
		cube[7][i] |= 1;
		cube[i][0] |= 128;
		cube[0][i] |= 128;
		cube[0][7] |= (1 << i);
		cube[i][7] |= 1;
		cube_show_loop(OUTLINE_DELAY);
	}
	for (i = 1; i < 8; i++) {
		cube[7][i] |= 128;
		cube[7][7] |= (1 << i);
		cube[i][7] |= 128;
		cube_show_loop(OUTLINE_DELAY);
	}
	cube_show_loop(20);
	/* shrink */
	cube_clear();
	cube[1][1] = 0b01111110;
	cube[1][6] = 0b01111110;
	cube[6][1] = 0b01111110;
	cube[6][6] = 0b01111110;
	for (i=2; i< 6; i++) {
		cube[1][i] = 0b01000010;
		cube[6][i] = 0b01000010;
		cube[i][1] = 0b01000010;
		cube[i][6] = 0b01000010;
	}
	cube_show_loop(30);
	rotate_90_auto( 8 );
 
}

/* freaky: when looking at this for a while in a dark room
 * you begin to see pink dots in the cube */
void cube_stars( void )
{
	uint8_t j;
	for (j = 1; j < 30; j++){
		uint8_t loops;
		for (loops = 0; loops < 18; loops++){
			cube_clear();
			uint8_t i;
			for (i = 0; i< j; i++){
				uint8_t randx = (uint8_t)rand()%8;
				uint8_t randy = (uint8_t)rand()%8;
				uint8_t randz = (uint8_t)rand()%8;
				cube[randy][randx] = (1 << randz);
			}
//		cube[randy][randx] &= ~(1 << randz);
			cube_show_loop(STARS_DELAY);
		}
	}
}

/* kind of sine wave
 * in other words, the best sine you can do with 8x8 pixels 
 */
void cube_waves( void )
{
	cube_clear();
	uint8_t i;
	for (i = 0; i < 10; i++){
		move_x_rev(0,0,7,7);
		cube[3][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[2][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[1][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[0][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[0][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[1][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[2][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[3][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[4][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[5][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[6][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[7][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[7][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[6][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[5][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[4][7] |= WAVES_DEPTH;
		cube_show_loop(WAVES_DELAY);
	}
}

/* another wave simulation */
void cube_sonic( void )
{
	cli();
	uint8_t i;
	for (i = 0; i < 10; i++){
		cube_clear();
		cube_show_loop(20);
		uint8_t mode = rand()%5;
		uint8_t sonic_layers = (rand()%8)+1;
		if (mode <= 3){
			cube_clear();
			uint8_t layer;
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0b10000000;
			}
			uint8_t deg;
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			cube_show_loop_wo_int(SONIC_DELAY);
			
			cube_clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0b01000000;
				cube[layer][1] = 0b10000000;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			cube_show_loop_wo_int(SONIC_DELAY);
			
			cube_clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0b00100000;
				cube[layer][1] = 0b00100000;
				cube[layer][2] = 0b11000000;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			cube_show_loop_wo_int(SONIC_DELAY);
			
			cube_clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0b00010000;
				cube[layer][1] = 0b00010000;
				cube[layer][2] = 0b00100000;
				cube[layer][3] = 0b11000000;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			cube_show_loop_wo_int(SONIC_DELAY);
			
			cube_clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0b00001000;
				cube[layer][1] = 0b00001000;
				cube[layer][2] = 0b00010000;
				cube[layer][3] = 0b00110000;
				cube[layer][4] = 0b11000000;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			cube_show_loop_wo_int(SONIC_DELAY);
			
			cube_clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0b00000100;
				cube[layer][1] = 0b00000100;
				cube[layer][2] = 0b00000100;
				cube[layer][3] = 0b00001000;
				cube[layer][4] = 0b00010000;
				cube[layer][5] = 0b11100000;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			cube_show_loop_wo_int(SONIC_DELAY);
			
			cube_clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0b00000010;
				cube[layer][1] = 0b00000010;
				cube[layer][2] = 0b00000010;
				cube[layer][3] = 0b00000100;
				cube[layer][4] = 0b00001000;
				cube[layer][5] = 0b00010000;
				cube[layer][6] = 0b11100000;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			cube_show_loop_wo_int(SONIC_DELAY);

			cube_clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0b00000001;
				cube[layer][1] = 0b00000001;
				cube[layer][2] = 0b00000001;
				cube[layer][3] = 0b00000010;
				cube[layer][4] = 0b00000010;
				cube[layer][5] = 0b00000100;
				cube[layer][6] = 0b00011000;
				cube[layer][7] = 0b11100000;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			cube_show_loop_wo_int(SONIC_DELAY);

			cube_clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][4] = 0b00000001;
				cube[layer][5] = 0b00000010;
				cube[layer][6] = 0b00000100;
				cube[layer][7] = 0b00001000;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			cube_show_loop_wo_int(SONIC_DELAY);

			cube_clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][6] = 0b00000001;
				cube[layer][7] = 0b00000010;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			cube_show_loop_wo_int(SONIC_DELAY);

			cube_clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][7] = 0b00000001;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			cube_show_loop_wo_int(SONIC_DELAY);
		} else {
			/* center wave */
			cube_clear();
			uint8_t layer;
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][3] = 0b00011000;
				cube[layer][4] = 0b00011000;
			}
			cube_show_loop_wo_int(SONIC_DELAY);
			cube_clear();
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][2] = 0b00011000;
				cube[layer][3] = 0b00100100;
				cube[layer][4] = 0b00100100;
				cube[layer][5] = 0b00011000;
			}
			cube_show_loop_wo_int(SONIC_DELAY);
			cube_clear();
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][1] = 0b00011000;
				cube[layer][2] = 0b00100100;
				cube[layer][3] = 0b01000010;
				cube[layer][4] = 0b01000010;
				cube[layer][5] = 0b00100100;
				cube[layer][6] = 0b00011000;
			}
			cube_show_loop_wo_int(SONIC_DELAY);
			cube_clear();
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0b00011000;
				cube[layer][1] = 0b01100110;
				cube[layer][2] = 0b01000010;
				cube[layer][3] = 0b10000001;
				cube[layer][4] = 0b10000001;
				cube[layer][5] = 0b01000010;
				cube[layer][6] = 0b01100110;
				cube[layer][7] = 0b00011000;
			}
			cube_show_loop_wo_int(SONIC_DELAY);
			cube_clear();
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0b01000010;
				cube[layer][1] = 0b10000001;
				cube[layer][6] = 0b10000001;
				cube[layer][7] = 0b01000010;
			}
			cube_show_loop_wo_int(SONIC_DELAY);
			cube_clear();
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0b10000001;
				cube[layer][7] = 0b10000001;
			}
			cube_show_loop_wo_int(SONIC_DELAY);
		}
	}
	sei();	
}
/* not sure, 8x8x8 is not really appropriate for diamonds */
void cube_diamond( void )
{
	cube_clear();
	uint8_t i;
	for ( i = 0; i < 3; i++ ){
		cube[4][2] = 0b01111110;
	}
}

/* move the actual frame out of the cube */
void cube_block_wipe( void )
{
	uint8_t i;
	for (i = 0; i < 8; i++){
		move_x_fwd(0,0,7,7);
		uint8_t layer;
		for(layer = 0; layer < 8; layer++){
			cube[layer][0] |= 0xFF;
		}
		cube_show_loop(BLOCK_WIPE_DELAY);
	}
	cube_show_loop(BLOCK_WIPE_DELAY);
	for (i = 8; i != 0; i--){
		uint8_t layer;
		for(layer = 0; layer < 8; layer++){
			cube[layer][i-1] = 0x00;
		}
		cube_show_loop(BLOCK_WIPE_DELAY);
	}
		
}

/* belt moving from top to bottom deleting the frame */
void cube_belt_wipe( void )
{
	uint8_t layer;
	for (layer = 8; layer != 0; layer--){
		cube[layer-1][0] |= 0xFF;
		cube[layer-1][7] |= 0xFF;
		uint8_t i;
		for (i = 1; i < 7; i++){ cube[layer-1][i] |= 0b10000001; }
		cube_show_loop(BELT_WIPE_DELAY);
	}
	for (layer = 8; layer != 0; layer--){
		uint8_t i;
		for (i = 0; i < 8; i++){ cube[layer-1][i] = 0x00; }
		cube_show_loop(BELT_WIPE_DELAY);
	}
}

/* do not source the layer FETs */
void cube_flash( uint8_t cycle )
{
	for (cycle = 0; cycle > 0; cycle--){
	cli();
	PORTC = 0x00;
		_delay_ms(BLINK_DELAY*5);
		_delay_ms(BLINK_DELAY*5);
		_delay_ms(BLINK_DELAY*5);
		_delay_ms(BLINK_DELAY*5);
		_delay_ms(BLINK_DELAY*5);
		_delay_ms(BLINK_DELAY*5);
	sei();
		_delay_ms(BLINK_DELAY*5);
		_delay_ms(BLINK_DELAY*5);
		_delay_ms(BLINK_DELAY*5);
		_delay_ms(BLINK_DELAY*5);
		_delay_ms(BLINK_DELAY*5);
		_delay_ms(BLINK_DELAY*5);
	}
}


