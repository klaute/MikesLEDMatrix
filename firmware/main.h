/*
This Program is based on
fornax LED cube V1.0 Copyright (C) 2009 Andreas Fiessler aka fornax

Changed by Kai Lauterbach (klaute at gmail.com) aka klaute 2010-02-11
to get it work with Mike's LED Matrix. See http://klautesblog.blogspot.com/ for details.

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <math.h>
#include <string.h>

#include <avr/interrupt.h>
#include <avr/wdt.h>

#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#include "ledcube.h"

#include "equalizer.h"
#include "blockeq.h"
//#include "invaders.h"

#include "usbdrv.h"

//#define USB_POLL_TCNT_START 40000 // ASROCK Rechner
#define USB_POLL_TCNT_START 25000 // Notebooks

PROGMEM char usbHidReportDescriptor[22] = {    /* USB report descriptor */
    0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x80,                    //   REPORT_COUNT (128)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0xc0                           // END_COLLECTION
};

volatile uint8_t seconds_timer_cnt;

uint16_t brightness;

/* The following variables store the status of the current data transfer */
static uchar    bytesRemaining;

typedef struct Cont {
        uchar                 mode; // 0 = Kommandomodus (Pgm Modus wird gelesen); 1 = Frame-Daten empfangen;
	volatile uchar doAnimation;
	volatile uchar eqValue;
	volatile uchar blockValue[16];
} Cont_t;
static Cont_t container;

static uchar frames;
static uchar frames_counter;
static uchar aenderungen_counter;
static uchar sekunden;
static uchar minuten;
static uchar stunden;
uchar* ptrSekunden;
uchar* ptrMinuten;
uchar* ptrStunden;

static bool playAnimation;
static bool boolPlayFloatingText;
static bool showTime;

void init(void);
void usbReset(void);

void start_animation(void);
//void play_animation(void);
void playAnimationen(uchar*, uchar*, uchar);
void playFloatingText();


//void show_Prozent(uchar);
//void animation_invaders(void);

usbMsgLen_t usbFunctionSetup(uchar[]);
uchar usbFunctionWrite(uchar*, uchar);
uchar usbFunctionRead(uchar*, uchar);

