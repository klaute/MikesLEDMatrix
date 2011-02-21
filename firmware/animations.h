/*
fornax LED cube V1.0

Copyright (C) 2009 Andreas Fiessler aka fornax

Changed by Kai Lauterbach (klaute at gmail.com) aka klaute 2010-02-11
to get it work with Mike's LED Matrix. See http://klautesblog.blogspot.com/ for details.

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/


#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <stdlib.h>
#include <avr/io.h>
#include <inttypes.h>

void cube_string_belt(char *string);
void set_char_to_belt(char character, char *belt);
void move_belt_left(char *belt);

#define SHOW_BELT_DELAY 5 /* seems to be the best */
void show_belt(char *belt);

void cube_string_to_front(char *string);

void cube_fixed_string( void );

void cube_diamond( void );

#define CUBES2_DELAY 15
void cubes_2( void );
#define CUBES4_DELAY 5
void cubes_4( void );

#define STRIPES_DELAY 6
void cube_stripes( void );

#define OUT_SHRINK_DELAY 14
void outline_shrink( void );

#define EXPLOSION_DELAY 1
void cube_explosion( void );

#define SWIPE_DELAY 4
void cube_wipe( void );

#define BLINK_DELAY 3
void cube_flash( uint8_t cycle );

#define CUBE_STRING_DELAY 5
void cube_string( char *string );

#define OUTLINE_DELAY 6
void cube_outline( void );

#define SONIC_DELAY 4
void cube_sonic( void );

#define WAVES_DELAY 3
#define WAVES_DEPTH 255
void cube_waves( void );

#define STARS_DELAY 4
void cube_stars( void );

#define BLOCK_WIPE_DELAY 5
void cube_block_wipe( void );

#define BELT_WIPE_DELAY 5
void cube_belt_wipe( void );
#endif
