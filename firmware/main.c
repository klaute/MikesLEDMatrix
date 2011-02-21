/*
This Program is based on
fornax LED cube V1.0 Copyright (C) 2009 Andreas Fiessler aka fornax

Changed by Kai Lauterbach (klaute at gmail.com) aka klaute 2010-02-11
to get it work with Mike's LED Matrix. See http://klautesblog.blogspot.com/ for details.

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

/* 

PORTA is LE
PORTB is not used
PORTC is layer enable
PORTD is 8 bit latch input

*/

#include "main.h"

/* ------------------------------------------------------------------------- */

int main(void)
{
	init();
	_delay_ms(100);
	_delay_ms(100);
	start_animation();
	// 800 ms pause
	_delay_ms(100);
	_delay_ms(100);
	_delay_ms(100);
	_delay_ms(100);
	_delay_ms(100);
	_delay_ms(100);
	_delay_ms(100);
	_delay_ms(100);
	cube_clear(); /* never forget this */

	while ( 1 )
	{	

		//usbPoll(); // Wird per Timer aufgerufen...
		if ( container.doAnimation != 0 )
		{
			switch ( container.doAnimation )
			{
				case 1 : ;
					cube_clear();
				break;
				case 2 : ;
					cube_full();
				break;
				// Equalizer
				case 20 : ;
					// euqalizer1 steuerung für mehrere ringe gleichzeitig
					cube_clear(); // aktuelles frame löschen
					switch ( container.eqValue )
					{
						case 10: ;
							equalizer_10();
						case  9: ;
							equalizer_9();
						case  8: ;
							equalizer_8();
						case  7: ;
							equalizer_7();
						case  6: ;
							equalizer_6();
						case  5: ;
							equalizer_5();
						case  4: ;
							equalizer_4();
						case  3: ;
							equalizer_3();
						case  2: ;
							equalizer_2();
						case  1: ;
							equalizer_1();
						case  0: ;
							equalizer_0();
					}
				break;
				case 21 : ;
					// euqalizer2 steuerung für mehrere ringe gleichzeitig
					cube_clear(); // aktuelles frame löschen
					switch ( container.eqValue )
					{
						case 10: ;
							equalizer_10();
						break;
						case  9: ;
							equalizer_9();
						break;
						case  8: ;
							equalizer_8();
						break;
						case  7: ;
							equalizer_7();
						break;
						case  6: ;
							equalizer_6();
						break;
						case  5: ;
							equalizer_5();
						break;
						case  4: ;
							equalizer_4();
						break;
						case  3: ;
							equalizer_3();
						break;
						case  2: ;
							equalizer_2();
						break;
						case  1: ;
							equalizer_1();
						break;
						case  0: ;
							equalizer_0();
						break;
					}
				break;
				case 30 : ;
					equalizer_0();
				break;
				case 31 : ;
					equalizer_1();
				break;
				case 32 : ;
					equalizer_2();
				break;
				case 33 : ;
					equalizer_3();
				break;
				case 34 : ;
					equalizer_4();
				break;
				case 35 : ;
					equalizer_5();
				break;
				case 36 : ;
					equalizer_6();
				break;
				case 37 : ;
					equalizer_7();
				break;
				case 38 : ;
					equalizer_8();
				break;
				case 39 : ;
					equalizer_9();
				break;
				case 40 : ;
					equalizer_10();
				break;
				case 50 : ;
					equalizer_clear_0();
				break;
				case 51 : ;
					equalizer_clear_1();
				break;
				case 52 : ;
					equalizer_clear_2();
				break;
				case 53 : ;
					equalizer_clear_3();
				break;
				case 54 : ;
					equalizer_clear_4();
				break;
				case 55 : ;
					equalizer_clear_5();
				break;
				case 56 : ;
					equalizer_clear_6();
				break;
				case 57 : ;
					equalizer_clear_7();
				break;
				case 58 : ;
					equalizer_clear_8();
				break;
				case 59 : ;
					equalizer_clear_9();
				break;
				case 60 : ;
					equalizer_clear_10();
				break;
				// Startanimation zeigen
				case 200 : ;
					start_animation();
				break;
				case 255 : ; // Reset durchführen
					wdt_enable(0);
					while(1);
				break;
			}

			container.doAnimation = 0;

		}

	}

}

/* ------------------------------------------------------------------------- */
/* usbFunctionRead() is called when the host requests a chunk of data from
 * the device. For more information see the documentation in usbdrv/usbdrv.h.
 */
uchar usbFunctionRead(uchar *data, uchar len)
{
	if (len > bytesRemaining)
		len = bytesRemaining;

	// Es dürfen immer nur 64 Bytes übergeben werden
	uint8_t pos = ( 64 - bytesRemaining );

	uchar i = 0;
	for ( i = 0; i < len; i++ ) // Schleife über die übergebenen Bytes.
	{
		if ( container.mode == 1 )
			data[i] = 1;
		else
			data[i] = cube[ (pos/8) ][ i ];
	}
	// Wenn alle 8 Bytes geschrieben wurden wird ein "Block" im globalen Datenarray weitergesprungen.
	if ( bytesRemaining == 8 )
	{
		container.mode = 0;
	}
	bytesRemaining -= len;

	return len;
}

/* ------------------------------------------------------------------------- */
/* usbFunctionWrite() is called when the host sends a chunk of data to the
 * device. For more information see the documentation in usbdrv/usbdrv.h.
 */
uchar usbFunctionWrite(uchar *data, uchar len)
{
	if(bytesRemaining == 0)
		return 1;               // end of transfer

	if(len > bytesRemaining)
		len = bytesRemaining;

	switch ( container.mode )
	{
	    case 0 : ;
	  	  if ( container.lock == 0 )
	  	  {
			container.lock = 1; // Weitere Annahme von Daten blockieren
			switch ( data[0] )
			{
				case 1 : ; // Übertragung von 64 Bytes vorbereiten 
					container.mode = 1;
					bytesRemaining = 0;
					return 1;
				case 2 : ; // Übertragen einer Reihe
					cube[data[1]][data[2]] = data[3];
					bytesRemaining = 0;
					container.lock = 0; // Daten angenommen, entsperren
					return 1;
				case 3 : ; // Helligkeit regeln...
					brightness  = data[1] << 8;
					brightness += data[2];
					bytesRemaining = 0;
					container.lock = 0; // Daten angenommen, entsperren
					return 1;
				case 4 : ; // Animation ausführen
					container.doAnimation = data[1];
					bytesRemaining = 0;
					container.lock = 0; // Daten angenommen, entsperren
					return 1;
				case 5 : ; // Equalizer
					container.doAnimation = data[1]; // Equalizer-Typ (20/21)
					container.eqValue = data[2]; // Stufe der Auslenkung
					bytesRemaining = 0;
					container.lock = 0; // Daten angenommen, entsperren
					return 1;
				default : // Keine Aktion
					bytesRemaining = 0;
					container.lock = 0; // Daten angenommen, entsperren
					return 1;
			}
	      } else {
		      bytesRemaining = 0;
		      return 1;
	      }
	    break;
	    case 1 : ; // read one frame (chunk of 64 byte)
			uint8_t pos = ( 64 - bytesRemaining );
	
			uchar i = 0;
			for ( i = 0; i < len; i++ )
			{
				cube[ (pos/8) ][ i ] = data[i];
			}

			if ( bytesRemaining == 8 )
			{
				container.mode = 0;
				container.lock = 0; // entsperren der Datenannahme
			}
	    break;
	}

	bytesRemaining -= len;
	return bytesRemaining == 0; // return 1 if this was the last chunk 
}

/* ------------------------------------------------------------------------- */
void init(void)
{
	/* 
           most important: configure layer enable as output and low
           as the latches are not able to source more than one layer
           at once
        */
	PORTC = 0;
	DDRC  = 0xFF;
	DDRA  = 0xFF;
	DDRD  = 0xFF;
	PORTA = 0;
	PORTD = 0;

	cube_show_init();

	usbInit();
	usbReset();

	// USB Poll with Timer1 (16Bit)
	TCCR1A = 0x00;
	TCCR1B = (1 << CS10); // prescale = 0
	TCNT1 = USB_POLL_TCNT_START;
	TIMSK |= (1 << TOIE1);

	_delay_ms(1);
	sei();
	_delay_ms(1);
}	

/* ------------------------------------------------------------------------- */
/* Simulieren eines USB disconnect */
void usbReset( void )
{
        usbDeviceDisconnect();

        uchar i = 13;
        while ( --i )
        {       // USB disconnect (~250ms)
                _delay_ms(20);
        }

        usbDeviceConnect();
}

/* ------------------------------------------------------------------------- */
usbMsgLen_t usbFunctionSetup(uchar data[8])
{
        usbRequest_t    *rq = (void *)data;

        if ( (rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS)
	{    // HID class request
                if(rq->bRequest == USBRQ_HID_GET_REPORT)
		{  // wValue: ReportType (highbyte), ReportID (lowbyte)
                        // since we have only one report type, we can ignore the report-ID
                        bytesRemaining = 64;
                        usbMsgPtr = &container;
                        return USB_NO_MSG;  // use usbFunctionRead() to obtain data
                }
		else if (rq->bRequest == USBRQ_HID_SET_REPORT)
		{
                        // since we have only one report type, we can ignore the report-ID
                        bytesRemaining = 64;
                        return USB_NO_MSG;  // use usbFunctionWrite() to receive data from host
                }
        }
	else
	{
        	// ignore vendor type requests, we don't use any
        }
        return 0;
}

/* ------------------------------------------------------------------------- */
// Interruptroutine
ISR( TIMER1_OVF_vect )
{
	TCNT1 = USB_POLL_TCNT_START;
	if ( container.lock == 0 )
		usbPoll();
}

/* ------------------------------------------------------------------------- */

void start_animation(void)
{
	uint8_t dur = 6;
	cube_clear();
	cube[0][0] = 0x01;
	cube_show_loop(dur);
	cube[0][0] = 0x03;
	cube[0][1] = 0x01;
	cube_show_loop(dur);
	cube[0][0] = 0x07;
	cube[0][1] = 0x03;
	cube[0][2] = 0x01;
	cube_show_loop(dur);
	cube[0][0] = 0x0f;
	cube[0][1] = 0x07;
	cube[0][2] = 0x03;
	cube[0][3] = 0x01;
	cube_show_loop(dur);
	cube[0][0] = 0x1f;
	cube[0][1] = 0x0f;
	cube[0][2] = 0x07;
	cube[0][3] = 0x03;
	cube[0][4] = 0x01;
	cube_show_loop(dur);
	cube[0][0] = 0x3f;
	cube[0][1] = 0x1f;
	cube[0][2] = 0x0f;
	cube[0][3] = 0x07;
	cube[0][4] = 0x03;
	cube[0][5] = 0x01;
	cube_show_loop(dur);
	cube[0][0] = 0x7f;
	cube[0][1] = 0x3f;
	cube[0][2] = 0x1f;
	cube[0][3] = 0x0f;
	cube[0][4] = 0x07;
	cube[0][5] = 0x03;
	cube[0][6] = 0x01;
	cube_show_loop(dur);
	cube[0][0] = 0xff;
	cube[0][1] = 0x7f;
	cube[0][2] = 0x3f;
	cube[0][3] = 0x1f;
	cube[0][4] = 0x0f;
	cube[0][5] = 0x07;
	cube[0][6] = 0x03;
	cube[0][7] = 0x01;
	cube_show_loop(dur);
	cube[0][1] = 0xff;
	cube[0][2] = 0x7f;
	cube[0][3] = 0x3f;
	cube[0][4] = 0x1f;
	cube[0][5] = 0x0f;
	cube[0][6] = 0x07;
	cube[0][7] = 0x03;
	cube[1][0] = 0x01;
	cube[2][0] = 0x01;
	cube_show_loop(dur);
	cube[0][2] = 0xff;
	cube[0][3] = 0x7f;
	cube[0][4] = 0x3f;
	cube[0][5] = 0x1f;
	cube[0][6] = 0x0f;
	cube[0][7] = 0x07;
	cube[1][0] = 0x03;
	cube[1][1] = 0x01;
	cube[2][0] = 0x03;
	cube[2][1] = 0x01;
	cube_show_loop(dur);
	cube[0][3] = 0xff;
	cube[0][4] = 0x7f;
	cube[0][5] = 0x3f;
	cube[0][6] = 0x1f;
	cube[0][7] = 0x0f;
	cube[1][0] = 0x07;
	cube[1][1] = 0x03;
	cube[1][2] = 0x01;
	cube[2][0] = 0x07;
	cube[2][1] = 0x03;
	cube[2][2] = 0x01;
	cube_show_loop(dur);
	cube[0][4] = 0xff;
	cube[0][5] = 0x7f;
	cube[0][6] = 0x3f;
	cube[0][7] = 0x1f;
	cube[1][0] = 0x0f;
	cube[1][1] = 0x07;
	cube[1][2] = 0x03;
	cube[1][3] = 0x01;
	cube[2][0] = 0x0f;
	cube[2][1] = 0x07;
	cube[2][2] = 0x03;
	cube[2][3] = 0x01;
	cube_show_loop(dur);
	cube[0][5] = 0xff;
	cube[0][6] = 0x7f;
	cube[0][7] = 0x3f;
	cube[1][0] = 0x1f;
	cube[1][1] = 0x0f;
	cube[1][2] = 0x07;
	cube[1][3] = 0x03;
	cube[1][4] = 0x01;
	cube[2][0] = 0x1f;
	cube[2][1] = 0x0f;
	cube[2][2] = 0x07;
	cube[2][3] = 0x03;
	cube[2][4] = 0x01;
	cube_show_loop(dur);
	cube[0][6] = 0xff;
	cube[0][7] = 0x7f;
	cube[1][0] = 0x3f;
	cube[1][1] = 0x1f;
	cube[1][2] = 0x0f;
	cube[1][3] = 0x07;
	cube[1][4] = 0x03;
	cube[1][5] = 0x01;
	cube[2][0] = 0x3f;
	cube[2][1] = 0x1f;
	cube[2][2] = 0x0f;
	cube[2][3] = 0x07;
	cube[2][4] = 0x03;
	cube[2][5] = 0x01;
	cube_show_loop(dur);
	cube[0][7] = 0xff;
	cube[1][0] = 0x7f;
	cube[1][1] = 0x3f;
	cube[1][2] = 0x1f;
	cube[1][3] = 0x0f;
	cube[1][4] = 0x07;
	cube[1][5] = 0x03;
	cube[1][6] = 0x01;
	cube[2][0] = 0x7f;
	cube[2][1] = 0x3f;
	cube[2][2] = 0x1f;
	cube[2][3] = 0x0f;
	cube[2][4] = 0x07;
	cube[2][5] = 0x03;
	cube[2][6] = 0x01;
	cube_show_loop(dur);
	cube[1][0] = 0xff;
	cube[1][1] = 0x7f;
	cube[1][2] = 0x3f;
	cube[1][3] = 0x1f;
	cube[1][4] = 0x0f;
	cube[1][5] = 0x07;
	cube[1][6] = 0x03;
	cube[1][7] = 0x01;
	cube[2][0] = 0xff;
	cube[2][1] = 0x7f;
	cube[2][2] = 0x3f;
	cube[2][3] = 0x1f;
	cube[2][4] = 0x0f;
	cube[2][5] = 0x07;
	cube[2][6] = 0x03;
	cube[2][7] = 0x01;
	cube_show_loop(dur);
	cube[1][1] = 0xff;
	cube[1][2] = 0x7f;
	cube[1][3] = 0x3f;
	cube[1][4] = 0x1f;
	cube[1][5] = 0x0f;
	cube[1][6] = 0x07;
	cube[1][7] = 0x03;
	cube[2][1] = 0xff;
	cube[2][2] = 0x7f;
	cube[2][3] = 0x3f;
	cube[2][4] = 0x1f;
	cube[2][5] = 0x0f;
	cube[2][6] = 0x07;
	cube[2][7] = 0x03;
	cube[3][0] = 0x01;
	cube[4][0] = 0x01;
	cube[5][0] = 0x01;
	cube_show_loop(dur);
	cube[1][2] = 0xff;
	cube[1][3] = 0x7f;
	cube[1][4] = 0x3f;
	cube[1][5] = 0x1f;
	cube[1][6] = 0x0f;
	cube[1][7] = 0x07;
	cube[2][2] = 0xff;
	cube[2][3] = 0x7f;
	cube[2][4] = 0x3f;
	cube[2][5] = 0x1f;
	cube[2][6] = 0x0f;
	cube[2][7] = 0x07;
	cube[3][0] = 0x03;
	cube[3][1] = 0x01;
	cube[4][0] = 0x03;
	cube[4][1] = 0x01;
	cube[5][0] = 0x03;
	cube[5][1] = 0x01;
	cube_show_loop(dur);
	cube[1][3] = 0xff;
	cube[1][4] = 0x7f;
	cube[1][5] = 0x3f;
	cube[1][6] = 0x1f;
	cube[1][7] = 0x0f;
	cube[2][3] = 0xff;
	cube[2][4] = 0x7f;
	cube[2][5] = 0x3f;
	cube[2][6] = 0x1f;
	cube[2][7] = 0x0f;
	cube[3][0] = 0x07;
	cube[3][1] = 0x03;
	cube[3][2] = 0x01;
	cube[4][0] = 0x07;
	cube[4][1] = 0x03;
	cube[4][2] = 0x01;
	cube[5][0] = 0x07;
	cube[5][1] = 0x03;
	cube[5][2] = 0x01;
	cube_show_loop(dur);
	cube[1][4] = 0xff;
	cube[1][5] = 0x7f;
	cube[1][6] = 0x3f;
	cube[1][7] = 0x1f;
	cube[2][4] = 0xff;
	cube[2][5] = 0x7f;
	cube[2][6] = 0x3f;
	cube[2][7] = 0x1f;
	cube[3][0] = 0x0f;
	cube[3][1] = 0x07;
	cube[3][2] = 0x03;
	cube[3][3] = 0x01;
	cube[4][0] = 0x0f;
	cube[4][1] = 0x07;
	cube[4][2] = 0x03;
	cube[4][3] = 0x01;
	cube[5][0] = 0x0f;
	cube[5][1] = 0x07;
	cube[5][2] = 0x03;
	cube[5][3] = 0x01;
	cube_show_loop(dur);
	cube[1][5] = 0xff;
	cube[1][6] = 0x7f;
	cube[1][7] = 0x3f;
	cube[2][5] = 0xff;
	cube[2][6] = 0x7f;
	cube[2][7] = 0x3f;
	cube[3][0] = 0x1f;
	cube[3][1] = 0x0f;
	cube[3][2] = 0x07;
	cube[3][3] = 0x03;
	cube[3][4] = 0x01;
	cube[4][0] = 0x1f;
	cube[4][1] = 0x0f;
	cube[4][2] = 0x07;
	cube[4][3] = 0x03;
	cube[5][0] = 0x1f;
	cube[5][1] = 0x0f;
	cube[5][2] = 0x07;
	cube[5][3] = 0x03;
	cube[7][0] = 0x01;
	cube[7][2] = 0x01;
	cube_show_loop(dur);
	cube[1][6] = 0xff;
	cube[1][7] = 0x7f;
	cube[2][6] = 0xff;
	cube[2][7] = 0x7f;
	cube[3][0] = 0x3f;
	cube[3][1] = 0x1f;
	cube[3][2] = 0x0f;
	cube[3][3] = 0x07;
	cube[3][4] = 0x03;
	cube[3][5] = 0x01;
	cube[4][0] = 0x3f;
	cube[4][1] = 0x1f;
	cube[4][2] = 0x0f;
	cube[4][3] = 0x07;
	cube[5][0] = 0x3f;
	cube[5][1] = 0x1f;
	cube[5][2] = 0x0f;
	cube[5][3] = 0x07;
	cube[7][0] = 0x03;
	cube[7][2] = 0x03;
	cube_show_loop(dur);
	cube[1][7] = 0xff;
	cube[2][7] = 0xff;
	cube[3][0] = 0x7f;
	cube[3][1] = 0x3f;
	cube[3][2] = 0x1f;
	cube[3][3] = 0x0f;
	cube[3][4] = 0x07;
	cube[3][5] = 0x03;
	cube[3][6] = 0x01;
	cube[4][0] = 0x7f;
	cube[4][1] = 0x3f;
	cube[4][2] = 0x1f;
	cube[4][3] = 0x0f;
	cube[5][0] = 0x7f;
	cube[5][1] = 0x3f;
	cube[5][2] = 0x1f;
	cube[5][3] = 0x0f;
	cube[7][0] = 0x07;
	cube[7][2] = 0x07;
	cube_show_loop(dur);
	cube[3][0] = 0xff;
	cube[3][1] = 0x7f;
	cube[3][2] = 0x3f;
	cube[3][3] = 0x1f;
	cube[3][4] = 0x0f;
	cube[3][5] = 0x07;
	cube[3][6] = 0x03;
	cube[3][7] = 0x01;
	cube[4][0] = 0xff;
	cube[4][1] = 0x7f;
	cube[4][2] = 0x3f;
	cube[4][3] = 0x1f;
	cube[5][0] = 0xff;
	cube[5][1] = 0x7f;
	cube[5][2] = 0x3f;
	cube[5][3] = 0x1f;
	cube[7][0] = 0x0f;
	cube[7][2] = 0x0f;
	cube_show_loop(dur);
	cube[3][1] = 0xff;
	cube[3][2] = 0x7f;
	cube[3][3] = 0x3f;
	cube[3][4] = 0x1f;
	cube[3][5] = 0x0f;
	cube[3][6] = 0x07;
	cube[3][7] = 0x03;
	cube[4][1] = 0xff;
	cube[4][2] = 0x7f;
	cube[4][3] = 0x3f;
	cube[4][4] = 0x01;
	cube[5][1] = 0xff;
	cube[5][2] = 0x7f;
	cube[5][3] = 0x3f;
	cube[5][4] = 0x01;
	cube[7][0] = 0x1f;
	cube[7][2] = 0x1f;
	cube[7][4] = 0x05;
	cube_show_loop(dur);
	cube[3][2] = 0xff;
	cube[3][3] = 0x7f;
	cube[3][4] = 0x3f;
	cube[3][5] = 0x1f;
	cube[3][6] = 0x0f;
	cube[3][7] = 0x07;
	cube[4][2] = 0xff;
	cube[4][3] = 0x7f;
	cube[4][4] = 0x03;
	cube[4][5] = 0x01;
	cube[5][2] = 0xff;
	cube[5][3] = 0x7f;
	cube[5][4] = 0x03;
	cube[5][5] = 0x01;
	cube[7][0] = 0x3f;
	cube[7][2] = 0x3f;
	cube[7][5] = 0x05;
	cube_show_loop(dur);
	cube[3][3] = 0xff;
	cube[3][4] = 0x7f;
	cube[3][5] = 0x3f;
	cube[3][6] = 0x1f;
	cube[3][7] = 0x0f;
	cube[4][3] = 0xff;
	cube[4][4] = 0x07;
	cube[4][5] = 0x03;
	cube[4][6] = 0x01;
	cube[5][3] = 0xff;
	cube[5][4] = 0x07;
	cube[5][5] = 0x03;
	cube[5][6] = 0x01;
	cube[7][0] = 0x7f;
	cube[7][2] = 0x7f;
	cube[7][6] = 0x05;
	cube_show_loop(dur);
	cube[3][4] = 0xff;
	cube[3][5] = 0x7f;
	cube[3][6] = 0x3f;
	cube[3][7] = 0x1f;
	cube[4][4] = 0x0f;
	cube[4][5] = 0x07;
	cube[4][6] = 0x03;
	cube[4][7] = 0x01;
	cube[5][4] = 0x0f;
	cube[5][5] = 0x07;
	cube[5][6] = 0x03;
	cube[5][7] = 0x01;
	cube[7][0] = 0xff;
	cube[7][2] = 0xff;
	cube_show_loop(dur);
	cube[3][5] = 0xff;
	cube[3][6] = 0x7f;
	cube[3][7] = 0x3f;
	cube[4][4] = 0x1f;
	cube[4][5] = 0x0f;
	cube[4][6] = 0x07;
	cube[4][7] = 0x03;
	cube[5][4] = 0x1f;
	cube[5][5] = 0x0f;
	cube[5][6] = 0x07;
	cube[5][7] = 0x03;
	cube[7][1] = 0x01;
	cube[7][3] = 0x01;
	cube_show_loop(dur);
	cube[3][6] = 0xff;
	cube[3][7] = 0x7f;
	cube[4][4] = 0x3f;
	cube[4][5] = 0x1f;
	cube[4][6] = 0x0f;
	cube[4][7] = 0x07;
	cube[5][4] = 0x3f;
	cube[5][5] = 0x1f;
	cube[5][6] = 0x0f;
	cube[5][7] = 0x07;
	cube[7][1] = 0x03;
	cube[7][3] = 0x03;
	cube_show_loop(dur);
	cube[3][7] = 0xff;
	cube[4][4] = 0x7f;
	cube[4][5] = 0x3f;
	cube[4][6] = 0x1f;
	cube[4][7] = 0x0f;
	cube[5][4] = 0x7f;
	cube[5][5] = 0x3f;
	cube[5][6] = 0x1f;
	cube[5][7] = 0x0f;
	cube[7][1] = 0x07;
	cube[7][3] = 0x07;
	cube_show_loop(dur);
	cube[4][4] = 0xff;
	cube[4][5] = 0x7f;
	cube[4][6] = 0x3f;
	cube[4][7] = 0x1f;
	cube[5][4] = 0xff;
	cube[5][5] = 0x7f;
	cube[5][6] = 0x3f;
	cube[5][7] = 0x1f;
	cube[7][1] = 0x0f;
	cube[7][3] = 0x0f;
	cube_show_loop(dur);
	cube[4][5] = 0xff;
	cube[4][6] = 0x7f;
	cube[4][7] = 0x3f;
	cube[5][5] = 0xff;
	cube[5][6] = 0x7f;
	cube[5][7] = 0x3f;
	cube[6][0] = 0x01;
	cube[7][1] = 0x1f;
	cube[7][3] = 0x1f;
	cube_show_loop(dur);
	cube[4][6] = 0xff;
	cube[4][7] = 0x7f;
	cube[5][6] = 0xff;
	cube[5][7] = 0x7f;
	cube[6][0] = 0x03;
	cube[6][1] = 0x01;
	cube[7][1] = 0x3f;
	cube[7][3] = 0x3f;
	cube_show_loop(dur);
	cube[4][7] = 0xff;
	cube[5][7] = 0xff;
	cube[6][0] = 0x07;
	cube[6][1] = 0x03;
	cube[6][2] = 0x01;
	cube[7][1] = 0x7f;
	cube[7][3] = 0x7f;
	cube_show_loop(dur);
	cube[6][0] = 0x0f;
	cube[6][1] = 0x07;
	cube[6][2] = 0x03;
	cube[6][3] = 0x01;
	cube[7][1] = 0xff;
	cube[7][3] = 0xff;
	cube_show_loop(dur);
	cube[6][0] = 0x1f;
	cube[6][1] = 0x0f;
	cube[6][2] = 0x07;
	cube[6][3] = 0x03;
	cube[6][4] = 0x01;
	cube_show_loop(dur);
	cube[6][1] = 0x1f;
	cube[6][2] = 0x0f;
	cube[6][3] = 0x07;
	cube[6][4] = 0x03;
	cube_show_loop(dur);
	cube[6][2] = 0x1f;
	cube[6][3] = 0x0f;
	cube[6][4] = 0x07;
	cube_show_loop(dur);
	cube[6][3] = 0x1f;
	cube[6][4] = 0x0f;
	cube_show_loop(dur);
	cube[6][4] = 0x1f;
	cube_show_loop(dur);
	cube[6][4] = 0x0f;
	cube_show_loop(dur);
	cube[6][3] = 0x0f;
	cube[6][4] = 0x07;
	cube_show_loop(dur);
	cube[6][2] = 0x0f;
	cube[6][3] = 0x07;
	cube[6][4] = 0x03;
	cube_show_loop(dur);
	cube[6][1] = 0x0f;
	cube[6][2] = 0x07;
	cube[6][3] = 0x03;
	cube[6][4] = 0x01;
	cube_show_loop(dur);
	cube[6][0] = 0x0f;
	cube[6][1] = 0x07;
	cube[6][2] = 0x03;
	cube[6][3] = 0x01;
	cube[6][4] = 0x00;
	cube_show_loop(dur);
	cube[6][0] = 0x07;
	cube[6][1] = 0x03;
	cube[6][2] = 0x01;
	cube[6][3] = 0x00;
	cube[7][1] = 0x7f;
	cube[7][3] = 0x7f;
	cube_show_loop(dur);
	cube[4][7] = 0x7f;
	cube[5][7] = 0x7f;
	cube[6][0] = 0x03;
	cube[6][1] = 0x01;
	cube[6][2] = 0x00;
	cube[7][1] = 0x3f;
	cube[7][3] = 0x3f;
	cube_show_loop(dur);
	cube[4][6] = 0x7f;
	cube[4][7] = 0x3f;
	cube[5][6] = 0x7f;
	cube[5][7] = 0x3f;
	cube[6][0] = 0x01;
	cube[6][1] = 0x00;
	cube[7][1] = 0x1f;
	cube[7][3] = 0x1f;
	cube_show_loop(dur);
	cube[4][5] = 0x7f;
	cube[4][6] = 0x3f;
	cube[4][7] = 0x1f;
	cube[5][5] = 0x7f;
	cube[5][6] = 0x3f;
	cube[5][7] = 0x1f;
	cube[6][0] = 0x00;
	cube[7][1] = 0x0f;
	cube[7][3] = 0x0f;
	cube_show_loop(dur);
	cube[4][4] = 0x7f;
	cube[4][5] = 0x3f;
	cube[4][6] = 0x1f;
	cube[4][7] = 0x0f;
	cube[5][4] = 0x7f;
	cube[5][5] = 0x3f;
	cube[5][6] = 0x1f;
	cube[5][7] = 0x0f;
	cube[7][1] = 0x07;
	cube[7][3] = 0x07;
	cube[7][7] = 0x05;
	cube_show_loop(dur);
	cube[3][6] = 0x7f;
	cube[3][7] = 0xbf;
	cube[4][4] = 0x5f;
	cube[4][5] = 0x2f;
	cube[4][6] = 0x17;
	cube[4][7] = 0x0b;
	cube[5][4] = 0x5f;
	cube[5][5] = 0x2f;
	cube[5][6] = 0x17;
	cube[5][7] = 0x0b;
	cube_show_loop(dur);
	cube[3][5] = 0x7f;
	cube[3][6] = 0x3f;
	cube[3][7] = 0x9f;
	cube[4][4] = 0x4f;
	cube[4][5] = 0x27;
	cube[4][6] = 0x13;
	cube[4][7] = 0x09;
	cube[5][4] = 0x4f;
	cube[5][5] = 0x27;
	cube[5][6] = 0x13;
	cube[5][7] = 0x09;
	cube_show_loop(dur);
	cube[3][4] = 0x7f;
	cube[3][5] = 0x3f;
	cube[3][6] = 0x1f;
	cube[3][7] = 0x8f;
	cube[4][4] = 0x47;
	cube[4][5] = 0x23;
	cube[4][6] = 0x11;
	cube[4][7] = 0x08;
	cube[5][4] = 0x47;
	cube[5][5] = 0x23;
	cube[5][6] = 0x11;
	cube[5][7] = 0x08;
	cube_show_loop(dur);
	cube[3][3] = 0x7f;
	cube[3][4] = 0x3f;
	cube[3][6] = 0x0f;
	cube[3][7] = 0x87;
	cube[4][3] = 0x7f;
	cube[4][4] = 0x43;
	cube[4][5] = 0x21;
	cube[4][6] = 0x10;
	cube[5][3] = 0x7f;
	cube[5][4] = 0x43;
	cube[5][5] = 0x21;
	cube[5][6] = 0x10;
	cube_show_loop(dur);
	cube[3][2] = 0x7f;
	cube[3][3] = 0x3f;
	cube[3][6] = 0x07;
	cube[3][7] = 0x83;
	cube[4][2] = 0x7f;
	cube[4][3] = 0x3f;
	cube[4][4] = 0x41;
	cube[4][5] = 0x20;
	cube[5][2] = 0x7f;
	cube[5][3] = 0x3f;
	cube[5][4] = 0x41;
	cube[5][5] = 0x20;
	cube_show_loop(dur);
	cube[3][1] = 0x7f;
	cube[3][2] = 0x3f;
	cube[3][6] = 0x03;
	cube[3][7] = 0x81;
	cube[4][1] = 0x7f;
	cube[4][2] = 0x3f;
	cube[4][3] = 0x1f;
	cube[4][4] = 0x40;
	cube[5][1] = 0x7f;
	cube[5][2] = 0x3f;
	cube[5][3] = 0x1f;
	cube[5][4] = 0x40;
	cube_show_loop(dur);
	cube[3][0] = 0x7f;
	cube[3][1] = 0x3f;
	cube[3][6] = 0x01;
	cube[3][7] = 0x80;
	cube[4][0] = 0x7f;
	cube[4][1] = 0x3f;
	cube[4][2] = 0x1f;
	cube[4][3] = 0x0f;
	cube[5][0] = 0x7f;
	cube[5][1] = 0x3f;
	cube[5][2] = 0x1f;
	cube[5][3] = 0x0f;
	cube_show_loop(dur);
	cube[3][3] = 0x37;
	cube[4][1] = 0x1f;
	cube[4][2] = 0x0f;
	cube[4][3] = 0x07;
	cube[5][1] = 0x1f;
	cube[5][2] = 0x0f;
	cube[5][3] = 0x07;
	cube_show_loop(dur);
	cube[3][2] = 0x37;
	cube[3][3] = 0x33;
	cube[4][0] = 0x5f;
	cube[4][1] = 0x0f;
	cube[4][2] = 0x07;
	cube[4][3] = 0x03;
	cube[5][0] = 0x5f;
	cube[5][1] = 0x0f;
	cube_show_loop(dur);
	cube[3][1] = 0x37;
	cube[3][2] = 0x33;
	cube[3][3] = 0x31;
	cube[4][0] = 0x4f;
	cube[4][1] = 0x07;
	cube[4][2] = 0x03;
	cube[4][3] = 0x01;
	cube[5][0] = 0x4f;
	cube[5][2] = 0x0b;
	cube[5][3] = 0x05;
	cube[7][0] = 0xfe;
	cube_show_loop(dur);
	cube[1][7] = 0xef;
	cube[2][4] = 0x7f;
	cube[3][0] = 0x77;
	cube[3][1] = 0x33;
	cube[3][2] = 0x31;
	cube[3][3] = 0x30;
	cube[4][0] = 0x47;
	cube[4][1] = 0x03;
	cube[4][2] = 0x01;
	cube[5][0] = 0x47;
	cube_show_loop(dur);
	cube[1][3] = 0x7f;
	cube[1][7] = 0xe7;
	cube[2][3] = 0x7f;
	cube[2][7] = 0xf7;
	cube[3][0] = 0x73;
	cube[3][1] = 0x31;
	cube[3][2] = 0x30;
	cube[4][0] = 0x43;
	cube[4][1] = 0x01;
	cube[5][0] = 0x43;
	cube[5][1] = 0x0d;
	cube_show_loop(dur);
	cube[1][2] = 0x7f;
	cube[1][3] = 0x3f;
	cube[1][6] = 0xf7;
	cube[1][7] = 0xe3;
	cube[2][2] = 0x7f;
	cube[2][3] = 0x3f;
	cube[2][6] = 0xf7;
	cube[2][7] = 0xf3;
	cube[3][0] = 0x71;
	cube[3][1] = 0x30;
	cube[4][0] = 0x41;
	cube[5][0] = 0x41;
	cube_show_loop(dur);
	cube[1][1] = 0x7f;
	cube[1][2] = 0x3f;
	cube[1][6] = 0xf3;
	cube[1][7] = 0xe1;
	cube[2][1] = 0x7f;
	cube[2][2] = 0x3f;
	cube[2][6] = 0xf3;
	cube[2][7] = 0xf1;
	cube[3][0] = 0x70;
	cube_show_loop(dur);
	cube[1][0] = 0x7f;
	cube[1][1] = 0x3f;
	cube[1][2] = 0x1f;
	cube[1][3] = 0x2f;
	cube[1][4] = 0xf7;
	cube[1][5] = 0xfb;
	cube[1][6] = 0xf1;
	cube[2][1] = 0x3f;
	cube[2][2] = 0x1f;
	cube[2][3] = 0x2f;
	cube[2][4] = 0x77;
	cube[2][5] = 0xfb;
	cube[2][6] = 0xf1;
	cube[2][7] = 0xf0;
	cube_show_loop(dur);
	cube[0][7] = 0x7f;
	cube[1][0] = 0x3f;
	cube[1][1] = 0x1f;
	cube[1][2] = 0x0f;
	cube[1][3] = 0x27;
	cube[1][4] = 0xf3;
	cube[1][5] = 0xf9;
	cube[2][1] = 0x1f;
	cube[2][2] = 0x0f;
	cube[2][3] = 0x27;
	cube[2][4] = 0x73;
	cube[2][5] = 0xf9;
	cube[2][6] = 0xf0;
	cube_show_loop(dur);
	cube[0][6] = 0x7f;
	cube[0][7] = 0x3f;
	cube[1][0] = 0x1f;
	cube[1][1] = 0x0f;
	cube[1][2] = 0x07;
	cube[1][3] = 0x23;
	cube[1][4] = 0xf1;
	cube[2][1] = 0x0f;
	cube[2][2] = 0x07;
	cube[2][3] = 0x23;
	cube[2][4] = 0x71;
	cube[2][5] = 0xf8;
	cube_show_loop(dur);
	cube[0][5] = 0x7f;
	cube[0][6] = 0x3f;
	cube[0][7] = 0x1f;
	cube[1][0] = 0x0f;
	cube[1][1] = 0x07;
	cube[1][2] = 0x03;
	cube[1][3] = 0x21;
	cube[2][1] = 0x07;
	cube[2][2] = 0x03;
	cube[2][3] = 0x21;
	cube[2][4] = 0x70;
	cube_show_loop(dur);
	cube[0][4] = 0x7f;
	cube[0][5] = 0x3f;
	cube[0][6] = 0x1f;
	cube[0][7] = 0x0f;
	cube[1][0] = 0x07;
	cube[1][1] = 0x03;
	cube[1][2] = 0x01;
	cube[2][1] = 0x03;
	cube[2][2] = 0x01;
	cube[2][3] = 0x20;
	cube_show_loop(dur);
	cube_show_loop(dur);
	cube[0][2] = 0x7f;
	cube[0][3] = 0xbf;
	cube[0][4] = 0x5f;
	cube[0][5] = 0x2f;
	cube[0][6] = 0x17;
	cube[0][7] = 0x0b;
	cube[1][0] = 0x05;
	cube[1][1] = 0x02;
	cube[2][0] = 0xfd;
	cube[2][1] = 0x02;
	cube_show_loop(dur);
	cube[0][1] = 0x7f;
	cube[0][2] = 0x3f;
	cube[0][3] = 0x9f;
	cube[0][4] = 0x4f;
	cube[0][5] = 0x27;
	cube[0][6] = 0x13;
	cube[0][7] = 0x09;
	cube[1][0] = 0x04;
	cube[2][0] = 0xfc;
	cube_show_loop(dur);
	cube[0][0] = 0x7f;
	cube[0][1] = 0x3f;
	cube[0][2] = 0x1f;
	cube[0][3] = 0x8f;
	cube[0][4] = 0x47;
	cube[0][5] = 0x23;
	cube[0][6] = 0x11;
	cube[0][7] = 0x08;
	cube_show_loop(dur);
	cube[0][0] = 0x3f;
	cube[0][1] = 0x1f;
	cube[0][2] = 0x0f;
	cube[0][3] = 0x87;
	cube[0][4] = 0x43;
	cube[0][5] = 0x21;
	cube[0][6] = 0x10;
	cube_show_loop(dur);
	cube[0][0] = 0x1f;
	cube[0][1] = 0x0f;
	cube[0][2] = 0x07;
	cube[0][3] = 0x83;
	cube[0][4] = 0x41;
	cube[0][5] = 0x20;
	cube_show_loop(dur);
	cube[0][0] = 0x0f;
	cube[0][1] = 0x07;
	cube[0][2] = 0x03;
	cube[0][3] = 0x81;
	cube[0][4] = 0x40;
	cube_show_loop(dur);
	cube[0][0] = 0x07;
	cube[0][1] = 0x03;
	cube[0][2] = 0x01;
	cube[0][3] = 0x80;
	cube_show_loop(dur);
	cube[0][0] = 0x03;
	cube[0][1] = 0x01;
	cube[0][2] = 0x00;
	cube_show_loop(dur);
	cube[0][0] = 0x01;
	cube[0][1] = 0x00;
	cube_show_loop(dur);
	cube[0][0] = 0x00;
	cube_show_loop(dur);
	cube_show_loop(dur);
	cube_show_loop(dur);
	cube_show_loop(dur);
	cube_show_loop(dur);
	cube[0][4] = 0xc0;
	cube[0][5] = 0x60;
	cube[0][6] = 0x30;
	cube[0][7] = 0x18;
	cube[1][0] = 0x0c;
	cube[1][1] = 0x06;
	cube[1][2] = 0x03;
	cube[1][3] = 0x23;
	cube[1][4] = 0xf3;
	cube[1][5] = 0xfb;
	cube[1][6] = 0xf3;
	cube[1][7] = 0xe3;
	cube[2][1] = 0xfe;
	cube[2][2] = 0x03;
	cube[2][3] = 0x21;
	cube[3][6] = 0x81;
	cube[3][7] = 0xc0;
	cube[4][0] = 0x43;
	cube[4][1] = 0x03;
	cube[4][2] = 0x03;
	cube[4][3] = 0xff;
	cube[4][4] = 0x60;
	cube[4][5] = 0x30;
	cube[4][6] = 0x18;
	cube[4][7] = 0x0f;
	cube[5][0] = 0x43;
	cube[5][1] = 0x0f;
	cube[5][3] = 0xff;
	cube[5][4] = 0x60;
	cube[5][5] = 0x30;
	cube[5][6] = 0x18;
	cube[5][7] = 0x0f;
	cube[7][0] = 0xff;
	cube_show_loop(dur);
	cube[0][5] = 0xe0;
	cube[0][6] = 0x70;
	cube[0][7] = 0x38;
	cube[1][0] = 0x1c;
	cube[1][1] = 0x0e;
	cube[1][2] = 0x07;
	cube[1][3] = 0x27;
	cube[1][4] = 0xf7;
	cube[1][5] = 0xff;
	cube[1][6] = 0xf7;
	cube[1][7] = 0xe7;
	cube[2][2] = 0xff;
	cube[2][3] = 0x23;
	cube[2][4] = 0x71;
	cube[3][5] = 0xbf;
	cube[3][6] = 0xc1;
	cube[3][7] = 0xe0;
	cube[4][0] = 0x47;
	cube[4][1] = 0x07;
	cube[4][2] = 0xff;
	cube[4][4] = 0x70;
	cube[4][5] = 0x38;
	cube[4][6] = 0x1f;
	cube[5][0] = 0x47;
	cube[5][2] = 0xff;
	cube[5][4] = 0x70;
	cube[5][5] = 0x38;
	cube[5][6] = 0x1f;
	cube_show_loop(dur);
	cube[0][6] = 0xf0;
	cube[0][7] = 0x78;
	cube[1][0] = 0x3c;
	cube[1][1] = 0x1e;
	cube[1][2] = 0x0f;
	cube[1][3] = 0x2f;
	cube[1][4] = 0xff;
	cube[1][6] = 0xff;
	cube[1][7] = 0xef;
	cube[2][3] = 0xff;
	cube[2][4] = 0x73;
	cube[2][5] = 0xf9;
	cube[3][4] = 0xbf;
	cube[3][5] = 0xff;
	cube[3][6] = 0xe1;
	cube[3][7] = 0xf0;
	cube[4][0] = 0x4f;
	cube[4][1] = 0xff;
	cube[4][4] = 0x78;
	cube[4][5] = 0x3f;
	cube[5][0] = 0x4f;
	cube[5][1] = 0xff;
	cube[5][4] = 0x78;
	cube[5][5] = 0x3f;
	cube_show_loop(dur);
	cube[0][7] = 0xf8;
	cube[1][0] = 0x7c;
	cube[1][1] = 0x3e;
	cube[1][2] = 0x1f;
	cube[1][3] = 0x3f;
	cube[1][7] = 0xff;
	cube[2][4] = 0xff;
	cube[2][5] = 0xfb;
	cube[2][6] = 0xf1;
	cube[3][3] = 0xb0;
	cube[3][4] = 0xff;
	cube[3][6] = 0xf1;
	cube[3][7] = 0xf8;
	cube[4][0] = 0xff;
	cube[4][4] = 0x7f;
	cube[5][0] = 0xff;
	cube[5][4] = 0x7f;
	cube_show_loop(dur);
	cube[1][0] = 0xfc;
	cube[1][1] = 0x7e;
	cube[1][2] = 0x3f;
	cube[2][5] = 0xff;
	cube[2][6] = 0xf3;
	cube[2][7] = 0xf1;
	cube[3][0] = 0xf0;
	cube[3][1] = 0xb0;
	cube[3][2] = 0xb0;
	cube[3][3] = 0xf0;
	cube[3][6] = 0xf9;
	cube[3][7] = 0xff;
	cube_show_loop(dur);
	cube[1][1] = 0xfe;
	cube[1][2] = 0x7f;
	cube[1][3] = 0x7f;
	cube[2][6] = 0xff;
	cube[2][7] = 0xf3;
	cube[3][0] = 0xf1;
	cube[3][1] = 0xf0;
	cube[3][2] = 0xf0;
	cube[3][6] = 0xff;
	cube_show_loop(dur);
	cube[1][2] = 0xff;
	cube[1][3] = 0xff;
	cube[2][7] = 0xff;
	cube[3][0] = 0xf3;
	cube[3][1] = 0xf1;
	cube_show_loop(dur);
	cube[3][0] = 0xff;
	cube[3][1] = 0xf3;
	cube[3][2] = 0xf1;
	cube[3][3] = 0xf9;
	cube_show_loop(dur);
	cube[3][1] = 0xff;
	cube[3][2] = 0xfb;
	cube[3][3] = 0xff;
	cube_show_loop(dur);
	cube[3][2] = 0xff;
	cube_show_loop(dur);
	cube[3][2] = 0xfb;
	cube_show_loop(dur);
	cube[3][2] = 0xf1;
	cube[3][3] = 0xf9;
	cube_show_loop(dur);
	cube[3][2] = 0xe0;
	cube[3][3] = 0xf1;
	cube[3][4] = 0xfb;
	cube_show_loop(dur);
	cube[2][7] = 0xc7;
	cube[3][1] = 0xfe;
	cube[3][2] = 0xc0;
	cube[3][3] = 0xe1;
	cube[3][4] = 0xf3;
	cube_show_loop(dur);
	cube[1][1] = 0x7e;
	cube[1][6] = 0xbf;
	cube[2][6] = 0x87;
	cube[2][7] = 0x87;
	cube[3][0] = 0xfe;
	cube[3][2] = 0x80;
	cube[3][3] = 0xc1;
	cube[3][4] = 0xe3;
	cube[3][5] = 0xf7;
	cube_show_loop(dur);
	cube[1][0] = 0x7c;
	cube[1][5] = 0xdf;
	cube[1][6] = 0x9f;
	cube[1][7] = 0x1f;
	cube[2][5] = 0x07;
	cube[2][6] = 0x07;
	cube[2][7] = 0x06;
	cube[3][1] = 0x7e;
	cube_show_loop(dur);
	cube[0][7] = 0x78;
	cube[1][0] = 0x3c;
	cube[1][4] = 0xef;
	cube[1][5] = 0xcf;
	cube[1][6] = 0x8f;
	cube[1][7] = 0x0f;
	cube[2][4] = 0x07;
	cube[2][6] = 0x06;
	cube[4][0] = 0x0f;
	cube[4][4] = 0x7e;
	cube[5][0] = 0x0f;
	cube[5][4] = 0x7e;
	cube_show_loop(dur);
	cube[0][6] = 0x70;
	cube[0][7] = 0x38;
	cube[1][3] = 0xf7;
	cube[1][4] = 0xe7;
	cube[1][5] = 0xc7;
	cube[1][6] = 0x87;
	cube[1][7] = 0x07;
	cube[2][3] = 0x07;
	cube[2][5] = 0x06;
	cube[4][0] = 0x07;
	cube[4][1] = 0x07;
	cube[4][5] = 0x3c;
	cube[5][0] = 0x07;
	cube[5][1] = 0x07;
	cube[5][5] = 0x3c;
	cube_show_loop(dur);
	cube[0][5] = 0x60;
	cube[0][6] = 0x30;
	cube[0][7] = 0x18;
	cube[1][0] = 0x2c;
	cube[1][1] = 0x76;
	cube[1][2] = 0xfb;
	cube[1][3] = 0xf3;
	cube[1][4] = 0xe3;
	cube[1][5] = 0xc3;
	cube[1][6] = 0x83;
	cube[1][7] = 0x03;
	cube[2][2] = 0x03;
	cube[2][3] = 0x05;
	cube[2][4] = 0x06;
	cube[3][5] = 0x77;
	cube[3][6] = 0xbf;
	cube[3][7] = 0xdf;
	cube[4][0] = 0x03;
	cube[4][1] = 0x03;
	cube[4][2] = 0x03;
	cube[4][4] = 0x6e;
	cube[4][5] = 0x34;
	cube[4][6] = 0x18;
	cube[5][0] = 0x03;
	cube[5][1] = 0x03;
	cube[5][2] = 0x03;
	cube[5][4] = 0x6e;
	cube[5][5] = 0x34;
	cube[5][6] = 0x18;
	cube_show_loop(dur);
	cube[0][4] = 0x40;
	cube[0][5] = 0x20;
	cube[0][6] = 0x10;
	cube[0][7] = 0x08;
	cube[1][0] = 0x24;
	cube[1][1] = 0x72;
	cube[1][2] = 0xf9;
	cube[1][3] = 0xf1;
	cube[1][4] = 0xe1;
	cube[1][5] = 0xc1;
	cube[1][6] = 0x81;
	cube[1][7] = 0x01;
	cube[2][1] = 0x02;
	cube[2][2] = 0x01;
	cube[2][3] = 0x04;
	cube[3][6] = 0x3f;
	cube[3][7] = 0x9f;
	cube[4][0] = 0x01;
	cube[4][1] = 0x01;
	cube[4][2] = 0x01;
	cube[4][3] = 0x01;
	cube[4][4] = 0x4e;
	cube[4][5] = 0x24;
	cube[4][6] = 0x10;
	cube[4][7] = 0x08;
	cube[5][0] = 0x01;
	cube[5][1] = 0x01;
	cube[5][2] = 0x01;
	cube[5][3] = 0x01;
	cube[5][4] = 0x4e;
	cube[5][5] = 0x24;
	cube[5][6] = 0x10;
	cube[5][7] = 0x08;
	cube_show_loop(dur);
	cube_show_loop(dur);
	cube_show_loop(dur);
	cube_show_loop(dur);
	cube_show_loop(dur);
	cube[1][1] = 0x62;
	cube[1][2] = 0xd9;
	cube[1][3] = 0xb1;
	cube[1][4] = 0x61;
	cube[2][2] = 0x09;
	cube[2][3] = 0x0c;
	cube[2][4] = 0x0c;
	cube[2][5] = 0x0c;
	cube[2][6] = 0x0c;
	cube[2][7] = 0x0c;
	cube[3][0] = 0xfc;
	cube[3][1] = 0xfc;
	cube[3][4] = 0x63;
	cube[3][5] = 0x36;
	cube[3][6] = 0x1d;
	cube[3][7] = 0x8b;
	cube[4][4] = 0x46;
	cube[4][5] = 0x20;
	cube[5][4] = 0x43;
	cube[5][5] = 0x21;
	cube_show_loop(dur);
	cube[1][0] = 0xc4;
	cube[1][1] = 0xe2;
	cube[1][2] = 0xd1;
	cube[1][3] = 0xb9;
	cube[1][4] = 0x79;
	cube[1][5] = 0xf1;
	cube[1][6] = 0xe1;
	cube[1][7] = 0xc1;
	cube[2][2] = 0x11;
	cube[2][3] = 0x18;
	cube[2][4] = 0x18;
	cube[2][5] = 0x18;
	cube[2][6] = 0x18;
	cube[2][7] = 0x18;
	cube[3][0] = 0xf8;
	cube[3][1] = 0xf9;
	cube[3][2] = 0x03;
	cube[3][3] = 0x47;
	cube[3][4] = 0x2f;
	cube[3][5] = 0x1e;
	cube[3][6] = 0x0d;
	cube[3][7] = 0x87;
	cube[4][0] = 0x81;
	cube[4][4] = 0x43;
	cube[4][5] = 0x21;
	cube[5][5] = 0x23;
	cube[5][6] = 0x11;
	cube_show_loop(dur);
	cube[1][0] = 0x84;
	cube[1][1] = 0x82;
	cube[1][2] = 0x01;
	cube[1][3] = 0x01;
	cube[1][4] = 0x01;
	cube[1][5] = 0x0d;
	cube[1][6] = 0x1f;
	cube[1][7] = 0x3d;
	cube[2][1] = 0x22;
	cube[2][2] = 0x31;
	cube[2][3] = 0x30;
	cube[2][4] = 0x30;
	cube[2][5] = 0x30;
	cube[2][6] = 0x30;
	cube[2][7] = 0xf1;
	cube[3][0] = 0xf1;
	cube[3][1] = 0x07;
	cube[3][2] = 0x0f;
	cube[3][3] = 0x1e;
	cube[3][4] = 0x1e;
	cube[3][5] = 0x0e;
	cube[3][6] = 0x06;
	cube[3][7] = 0x86;
	cube[4][0] = 0xf9;
	cube[4][1] = 0xf1;
	cube[4][2] = 0x61;
	cube[4][4] = 0x47;
	cube[4][5] = 0x23;
	cube[5][0] = 0x81;
	cube[5][1] = 0x81;
	cube[5][2] = 0x81;
	cube[5][3] = 0x81;
	cube[5][4] = 0x41;
	cube[5][5] = 0x21;
	cube_show_loop(dur);
	cube[1][0] = 0x04;
	cube[1][5] = 0x01;
	cube[1][6] = 0x05;
	cube[1][7] = 0x0f;
	cube[2][1] = 0x62;
	cube[2][2] = 0x61;
	cube[2][3] = 0x60;
	cube[2][4] = 0x60;
	cube[2][5] = 0x60;
	cube[2][6] = 0xe0;
	cube[2][7] = 0xe2;
	cube[3][0] = 0x07;
	cube[3][1] = 0x0f;
	cube[3][2] = 0x1f;
	cube[3][3] = 0x3e;
	cube[4][0] = 0xff;
	cube[4][1] = 0xff;
	cube[4][2] = 0x7d;
	cube[4][3] = 0x39;
	cube[4][5] = 0x27;
	cube[5][0] = 0xc1;
	cube[5][1] = 0xc1;
	cube[5][2] = 0xc1;
	cube[5][3] = 0xc1;
	cube[5][4] = 0x40;
	cube[5][5] = 0x20;
	cube[5][6] = 0x10;
	cube_show_loop(dur);
	cube[0][3] = 0x00;
	cube[0][4] = 0x00;
	cube[0][5] = 0x00;
	cube[0][6] = 0x00;
	cube[0][7] = 0x00;
	cube[1][0] = 0x00;
	cube[1][1] = 0x80;
	cube[1][2] = 0x00;
	cube[1][3] = 0x00;
	cube[1][4] = 0x00;
	cube[1][5] = 0x00;
	cube[1][6] = 0x04;
	cube[1][7] = 0x0e;
	cube[2][0] = 0x40;
	cube[2][1] = 0x60;
	cube[2][2] = 0x60;
	cube[3][7] = 0x06;
	cube[4][1] = 0xfe;
	cube[4][2] = 0x7c;
	cube[4][3] = 0x38;
	cube[4][4] = 0x07;
	cube[4][5] = 0x07;
	cube[4][6] = 0x00;
	cube[4][7] = 0x00;
	cube[5][0] = 0xc0;
	cube[5][1] = 0xc0;
	cube[5][2] = 0xc0;
	cube[5][3] = 0xc0;
	cube[5][4] = 0x00;
	cube[5][5] = 0x00;
	cube[5][6] = 0x00;
	cube[5][7] = 0x00;
	cube[7][0] = 0x40;
	cube[7][1] = 0x00;
	cube[7][2] = 0x10;
	cube[7][3] = 0x00;
	cube_show_loop(dur);
}

/* ------------------------------------------------------------------------- */

