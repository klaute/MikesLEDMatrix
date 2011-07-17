/*
fornax LED cube V1.0

Copyright (C) 2009 Andreas Fiessler aka fornax

Changed by Kai Lauterbach (klaute at gmail.com) aka klaute 2010-02-11
to get it work with Mike's LED Matrix. See http://klautesblog.blogspot.com/ for details.

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include "ledcube.h"
#include <stdlib.h>
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <math.h>

#include <avr/interrupt.h>

//#include "ab.h"
//#include "rotation.h"

// Initialisiert den Timer0 (8Bit)
void cube_show_init( void )
{
	// Vorteiler auf 1024 => 16MHz/1024 ergibt den Takt mit dem die ISR ausgelöst wird.
	// (1/16MHz)*1024 = 0,000064 Sekunden
	// 0,000064 Sekunden * (0xff Interrupts - 0xb0 Interrupts) = 0,005056 Sekunden
	// 0,000064 bis 0,01632 in 256 Schritten zu je 0,000064 Sekunden
	TCCR0 |= (1 << CS02) | (0 << CS00); 
	TIMSK |= (1 << TOIE0);
}

// Interruptroutine
ISR( TIMER0_OVF_vect )
{

	TCNT0 = 0xB0; // at least 0xA0
	// cli() not neccessary atm
	PORTC = 0x0; // Ebene abschalten
	static uint8_t cube_show_layer = 0;
	asm volatile("nop");
	uint8_t j;
	for(j = 0; j < 8; j++){ // Schleife über alle Ebenen
		PORTD = cube[cube_show_layer][j]; // 8 Bit der aktuellen Ebene übertragen
		asm volatile("nop");
		PORTA |= (1 << j); // Aktuell angelegte Daten der Ebenen laden per Load
		asm volatile("nop");
		PORTA = 0; // Fallende Flanke am Load-Pin
		asm volatile("nop");
	}
	PORTC |= (1 << cube_show_layer); // Nächste Ebene einschalten
	asm volatile("nop");
	if (cube_show_layer < 7) { // Beim nächsten Interrupt die nächste Ebene anzeigen
		cube_show_layer++;
	} else {
		cube_show_layer = 0;
	}
}

/* basic transformations and view functions */

/* all leds off */
void cube_clear ( void )
{
	uint8_t i;
	for (i = 0; i < 8; i++){
		uint8_t j;
		for (j = 0; j < 8; j++){
			cube[i][j] = 0;
		}
	}
}

/* single layer clear to avoid flickering with auto cube */
void cube_clear_layer(uint8_t layer)
{
	uint8_t j;
	for (j = 0; j < 8; j++){
		cube[layer][j] = 0;
	}
}

void cube_set_layer_row(uint8_t layer, uint8_t row, uint8_t data)
{
	cube[layer][row] = data;
}

void cube_full ( void )
{
	uint8_t i;
	for (i = 0; i < 8; i++){
		uint8_t j;
		for (j = 0; j < 8; j++){
			cube[i][j] = 255;
		}
	}
}
/* some test cubes */
void cube_cube_3 ( void )
{
	cube[0][0] = 7;
	cube[0][1] = 7;
	cube[0][2] = 7;
	cube[1][0] = 7;
	cube[1][1] = 7;
	cube[1][2] = 7;
	cube[2][0] = 7;
	cube[2][1] = 7;
	cube[2][2] = 7;
}

void cube_cube_4_line ( void )
{
	cube[0][0] = 15;
	cube[0][1] = 9;
	cube[0][2] = 9;
	cube[0][3] = 15;
	cube[1][0] = 9;
	cube[1][3] = 9;
	cube[2][0] = 9;
	cube[2][3] = 9;
	cube[3][0] = 15;
	cube[3][1] = 9;
	cube[3][2] = 9;
	cube[3][3] = 15;

}

void cube_random( void )
{
	uint8_t i;
	for ( i = 0; i < 8; i++ ){
		uint8_t j;
		for ( j= 0; j < 8; j++) {
			cube[i][j] = rand()%255;
		}
	}
}

/* one layer */
void cube_test_z( void )
{
	uint8_t i;
	for (i = 0; i < 8; i++){
		uint8_t j;
		for (j = 0; j < 8; j++){
			cube[i][j] = 1;
		}
	}
}

void cube_test_y( void )
{
	uint8_t i;
	for (i = 0; i < 8; i++){
		cube[0][i] = 255;
	}
}

void cube_test_x( void )
{
	uint8_t i;
	for (i = 0; i < 8; i++){
		cube[i][0] = 255;
	}
}

/* show one frame */
void cube_show( void )
{

	asm volatile("nop");
	uint8_t i;
	for (i = 0; i < 8; i++){
		uint8_t j;
		for(j = 0; j < 8; j++){
			PORTD = cube[i][j];
			asm volatile("nop");
			PORTA |= (1 << j);
			asm volatile("nop");
			PORTA = 0;
			asm volatile("nop");
		}
		PORTC |= (1 << i);
		_delay_ms(1);
		PORTC = 0x0;
		asm volatile("nop");
	}
}

/* viewed through ISR by default, so just a delay */
void cube_show_loop( uint8_t cycle )
{
	uint16_t i;
	for (i = 0; i < cycle*2; i++){ 
		_delay_ms(8);
	}
}

/* some functions may flicker when the ISR views the cube
 * while transforming something -> use this loop */
void cube_show_loop_wo_int( uint8_t cycle )
{
	uint16_t i;
	for (i = 0; i < cycle*2; i++){
		cube_show();
	}
	
}
