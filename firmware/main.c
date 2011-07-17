/*
This Program is based on
fornax LED cube V1.0 Copyright (C) 2009 Andreas Fiessler aka fornax

Changed by Kai Lauterbach (klaute at gmail.com) aka klaute 2010-02-11
to get it work with Mike's LED Matrix. See http://klautesblog.blogspot.com/ for details.

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include "main.h"
#include "animations.h"

/* ------------------------------------------------------------------------- */

int main(void)
{
	init();
	_delay_ms(100);
	_delay_ms(100);
	start_animation();
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
					playAnimation = true;
					playAnimationen(maske1, aendrung1,frames1);
				break;
				case 31 : ;
					playAnimation = true;
					playAnimationen(maske2, aendrung2,frames2);
				break;
				case 32 : ;
					playAnimation = true;
					playAnimationen(maske3, aendrung3,frames3);
				break;
				case 33 : ;
					playAnimation = true;
					playAnimationen(maske4, aendrung4,frames4);
				break;
				case 34 : ;
					playAnimation = true;
					playAnimationen(maske5, aendrung5,frames5);
				break;
				case 35 : ;
					playAnimation = true;
					playAnimationen(maske6, aendrung6,frames6);
				break;
				case 36 : ;
					playAnimation = true;
					playAnimationen(maske7, aendrung7,frames7);
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
	uchar v;
	playAnimation = false;

	switch ( container.mode )
	{
	    case 0 : ;
		switch ( data[0] )
		{
			case 1 : ; // Übertragung von 64 Bytes vorbereiten 
				container.mode = 1;
				bytesRemaining = 0;
				return 1;
			case 2 : ; // Übertragen einer Reihe
				cube[data[1]][data[2]] = data[3];
				container.mode = 0;
				bytesRemaining = 0;
				return 1;
			case 3 : ; // Helligkeit regeln...
				brightness   = data[1] << 8;
				brightness  += data[2];
				bytesRemaining   = 0;
				return 1;
			case 4 : ; // Animation ausführen
				container.doAnimation = data[1];
				bytesRemaining = 0;
				return 1;
			case 5 : ; // Equalizer
				container.doAnimation = data[1]; // Equalizer-Typ (20/21)
				container.eqValue = data[2]; // Stufe der Auslenkung
				bytesRemaining = 0;
				return 1;
			case 6 : ; // BlockEqualizer ohne Querbalken
				v = 0;
				for( v = 1; v < 8; v++ )
                                    container.blockValue[v-1] = data[v];
				blockEqualizerBold(container.blockValue, false);
				bytesRemaining = 0;
				return 1;
			case 7 : ; // BlockEqualizer mit Querbalken
				v = 0;
				for( v = 1; v < 8; v++ )
                                    container.blockValue[v-1] = data[v];
				blockEqualizerBold(container.blockValue, true);
				bytesRemaining = 0;
				return 1;
			case 8 : ; // Übertragung von 24 Bytes vorbereiten 
				container.mode = 2;
				bytesRemaining = 0;
				return 1;
			
			default : // Keine Aktion
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
    			container.mode  = 0;
    		}
    	    break;
        case 2 : ; // read blockValue for blockequalizer
		    pos = ( 64 - bytesRemaining );
    		i = 0;
    		if( pos < 17 )
    		{
    			//bzero(container.blockValue, sizeof(container.blockValue));
    			memset(container.blockValue, 255, sizeof(container.blockValue));
    			for ( i = 0; i < len; i++ )
    			{
    				container.blockValue[ pos + i ] = data[i];
    			}
    			//blockEqualizer(container.blockValue);
    		}

    		if ( bytesRemaining == 48)
    		{
    			container.mode  = 0;
                bytesRemaining = 8;
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

	// Timer2 (8Bit)
	TCCR2  = 0x00;
	TCCR2 |= (1 << WGM21); // CTC
	TCCR2 |= (1 << CS22) | (1 << CS01); // prescale = 1024
	TCNT2 = 1;
    OCR2 = 125; // Ergibt genau 0,008 Sekunden
	TIMSK |= (1 << OCIE2);

	_delay_ms(1);
	sei();
	_delay_ms(1);
	qBlock[0] = 0;
	qBlock[1] = 0;
	qBlock[2] = 0;
	qBlock[3] = 0;	
	qBlock[4] = 0;
	qBlock[5] = 0;
	qBlock[6] = 0;
	falldown = 1;
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
	usbPoll();
}

/* ------------------------------------------------------------------------- */
// Interruptroutine
ISR( TIMER2_COMP_vect )
{
    if (seconds_timer_cnt >= 125)
    {
        seconds_timer_cnt = 0;

        // Start the action which should be triggered every second.
        if (cube[0][0] == 0x00) {
            cube[0][0] = 0x12;
        } else {
            cube[0][0] = 0x00;
        }

    }
}

/* ------------------------------------------------------------------------- */

void playAnimationen(uchar* maske_, uchar* aenderungen_, uchar frames_)
{	
 	uint8_t dur = 12;
	cube_clear();
	frames_counter = 0;
	frames = frames_; //sizeof(maske_) / 8;
	unsigned int counter_aenderung = 0;
	uchar i;
	uchar tmpMaske;
	while ( playAnimation )
	{		
		for( i = 0; i < 8; i++ )
		{	tmpMaske = pgm_read_byte(&maske_[frames_counter * 8 + i]);
 
			if(tmpMaske > 0)
			{
				if(tmpMaske & 1) {cube[i][0] = pgm_read_byte(&aenderungen_[counter_aenderung]); counter_aenderung++;}
				if(tmpMaske & 2) {cube[i][1] = pgm_read_byte(&aenderungen_[counter_aenderung]); counter_aenderung++;}
				if(tmpMaske & 4) {cube[i][2] = pgm_read_byte(&aenderungen_[counter_aenderung]); counter_aenderung++;}
				if(tmpMaske & 8) {cube[i][3] = pgm_read_byte(&aenderungen_[counter_aenderung]); counter_aenderung++;}
				if(tmpMaske & 16) {cube[i][4] = pgm_read_byte(&aenderungen_[counter_aenderung]); counter_aenderung++;}
				if(tmpMaske & 32) {cube[i][5] = pgm_read_byte(&aenderungen_[counter_aenderung]); counter_aenderung++;}
				if(tmpMaske & 64) {cube[i][6] = pgm_read_byte(&aenderungen_[counter_aenderung]); counter_aenderung++;}
				if(tmpMaske & 128) {cube[i][7] = pgm_read_byte(&aenderungen_[counter_aenderung]); counter_aenderung++;}	
			}
		}
		frames_counter++;
		cube_show_loop(dur);

		if(frames_counter == frames) 
		{
			frames_counter = 0;
			counter_aenderung = 0;	
			cube_clear();
		}
				
	}
	cube_clear();
}


void start_animation(void)
{
	uint8_t dur = 12;
	cube_clear();
	cube_show_loop(dur);
	cube[0][0] = 0x01;
	cube[0][1] = 0x01;
	cube[0][2] = 0x01;
	cube[0][3] = 0x01;
	cube[0][4] = 0x01;
	cube[0][5] = 0x01;
	cube[0][6] = 0x01;
	cube[0][7] = 0x01;
	cube[3][0] = 0x01;
	cube[3][1] = 0x01;
	cube[3][2] = 0x01;
	cube[3][3] = 0x01;
	cube[3][4] = 0x01;
	cube[3][5] = 0x01;
	cube[3][6] = 0x01;
	cube[3][7] = 0x01;
	cube[6][0] = 0x01;
	cube[6][1] = 0x01;
	cube[6][2] = 0x01;
	cube[6][3] = 0x01;
	cube_show_loop(dur);
	cube[0][0] = 0x02;
	cube[0][1] = 0x02;
	cube[0][2] = 0x02;
	cube[0][3] = 0x02;
	cube[0][4] = 0x02;
	cube[0][5] = 0x02;
	cube[0][6] = 0x02;
	cube[0][7] = 0x02;
	cube[3][0] = 0x02;
	cube[3][1] = 0x02;
	cube[3][2] = 0x02;
	cube[3][3] = 0x02;
	cube[3][4] = 0x02;
	cube[3][5] = 0x02;
	cube[3][6] = 0x02;
	cube[3][7] = 0x02;
	cube[6][0] = 0x02;
	cube[6][1] = 0x02;
	cube[6][2] = 0x02;
	cube[6][3] = 0x02;
	cube_show_loop(dur);
	cube[0][0] = 0x04;
	cube[0][1] = 0x04;
	cube[0][2] = 0x04;
	cube[0][3] = 0x04;
	cube[0][4] = 0x04;
	cube[0][5] = 0x04;
	cube[0][6] = 0x04;
	cube[0][7] = 0x04;
	cube[3][0] = 0x04;
	cube[3][1] = 0x04;
	cube[3][2] = 0x04;
	cube[3][3] = 0x04;
	cube[3][4] = 0x04;
	cube[3][5] = 0x04;
	cube[3][6] = 0x04;
	cube[3][7] = 0x04;
	cube[6][0] = 0x04;
	cube[6][1] = 0x04;
	cube[6][2] = 0x04;
	cube[6][3] = 0x04;
	cube_show_loop(dur);
	cube[0][0] = 0x08;
	cube[0][1] = 0x08;
	cube[0][2] = 0x08;
	cube[0][3] = 0x08;
	cube[0][4] = 0x08;
	cube[0][5] = 0x08;
	cube[0][6] = 0x08;
	cube[0][7] = 0x08;
	cube[3][0] = 0x08;
	cube[3][1] = 0x08;
	cube[3][2] = 0x08;
	cube[3][3] = 0x08;
	cube[3][4] = 0x08;
	cube[3][5] = 0x08;
	cube[3][6] = 0x08;
	cube[3][7] = 0x08;
	cube[6][0] = 0x08;
	cube[6][1] = 0x08;
	cube[6][2] = 0x08;
	cube[6][3] = 0x08;
	cube_show_loop(dur);
	cube[0][0] = 0x10;
	cube[0][1] = 0x10;
	cube[0][2] = 0x10;
	cube[0][3] = 0x10;
	cube[0][4] = 0x10;
	cube[0][5] = 0x10;
	cube[0][6] = 0x10;
	cube[0][7] = 0x18;
	cube[3][0] = 0x18;
	cube[3][1] = 0x18;
	cube[3][2] = 0x18;
	cube[3][3] = 0x18;
	cube[3][4] = 0x18;
	cube[3][5] = 0x10;
	cube[3][6] = 0x10;
	cube[3][7] = 0x10;
	cube[6][0] = 0x10;
	cube[6][1] = 0x10;
	cube[6][2] = 0x10;
	cube[6][3] = 0x10;
	cube_show_loop(dur);
	cube[0][0] = 0x20;
	cube[0][1] = 0x20;
	cube[0][2] = 0x20;
	cube[0][3] = 0x20;
	cube[0][4] = 0x20;
	cube[0][5] = 0x30;
	cube[0][6] = 0x30;
	cube[0][7] = 0x28;
	cube[3][0] = 0x28;
	cube[3][1] = 0x28;
	cube[3][2] = 0x28;
	cube[3][3] = 0x28;
	cube[3][4] = 0x28;
	cube[3][5] = 0x30;
	cube[3][6] = 0x30;
	cube[3][7] = 0x20;
	cube[6][0] = 0x20;
	cube[6][1] = 0x20;
	cube[6][2] = 0x20;
	cube[6][3] = 0x20;
	cube_show_loop(dur);
	cube[0][0] = 0x40;
	cube[0][1] = 0x40;
	cube[0][2] = 0x40;
	cube[0][3] = 0x40;
	cube[0][4] = 0x60;
	cube[0][5] = 0x50;
	cube[0][6] = 0x50;
	cube[0][7] = 0x48;
	cube[3][0] = 0x48;
	cube[3][1] = 0x48;
	cube[3][2] = 0x48;
	cube[3][3] = 0x48;
	cube[3][4] = 0x48;
	cube[3][5] = 0x50;
	cube[3][6] = 0x50;
	cube[3][7] = 0x60;
	cube[6][0] = 0x40;
	cube[6][1] = 0x40;
	cube[6][2] = 0x40;
	cube[6][3] = 0x40;
	cube_show_loop(dur);
	cube[0][0] = 0x80;
	cube[0][1] = 0x80;
	cube[0][2] = 0x80;
	cube[0][3] = 0xc0;
	cube[0][4] = 0xa0;
	cube[0][5] = 0x90;
	cube[0][6] = 0x90;
	cube[0][7] = 0x88;
	cube[3][0] = 0x88;
	cube[3][1] = 0x88;
	cube[3][2] = 0x88;
	cube[3][3] = 0x88;
	cube[3][4] = 0x88;
	cube[3][5] = 0x90;
	cube[3][6] = 0x90;
	cube[3][7] = 0xa0;
	cube[6][0] = 0xc0;
	cube[6][1] = 0x80;
	cube[6][2] = 0x80;
	cube[6][3] = 0x80;
	cube_show_loop(dur);
	cube[0][0] = 0x00;
	cube[0][1] = 0x00;
	cube[0][3] = 0x40;
	cube[0][4] = 0x20;
	cube[0][5] = 0x10;
	cube[0][6] = 0x10;
	cube[0][7] = 0x08;
	cube[1][0] = 0x01;
	cube[1][1] = 0x01;
	cube[1][2] = 0x01;
	cube[1][3] = 0x01;
	cube[1][4] = 0x01;
	cube[1][5] = 0x01;
	cube[1][6] = 0x01;
	cube[1][7] = 0x01;
	cube[3][0] = 0x08;
	cube[3][1] = 0x08;
	cube[3][2] = 0x08;
	cube[3][3] = 0x08;
	cube[3][6] = 0x10;
	cube[3][7] = 0x20;
	cube[4][0] = 0x01;
	cube[4][1] = 0x01;
	cube[4][2] = 0x01;
	cube[4][3] = 0x01;
	cube[4][4] = 0x01;
	cube[4][5] = 0x01;
	cube[4][6] = 0x01;
	cube[4][7] = 0x01;
	cube[6][0] = 0x40;
	cube[6][2] = 0x00;
	cube[6][3] = 0x00;
	cube[6][4] = 0x01;
	cube[6][5] = 0x01;
	cube[6][6] = 0x01;
	cube[6][7] = 0x01;
	cube_show_loop(dur);
	cube[1][0] = 0x02;
	cube[1][1] = 0x02;
	cube[1][2] = 0x03;
	cube[1][3] = 0x02;
	cube[1][4] = 0x02;
	cube[1][5] = 0x02;
	cube[1][6] = 0x02;
	cube[1][7] = 0x02;
	cube[4][0] = 0x02;
	cube[4][1] = 0x02;
	cube[4][2] = 0x03;
	cube[4][3] = 0x03;
	cube[4][4] = 0x03;
	cube[4][5] = 0x03;
	cube[4][6] = 0x02;
	cube[4][7] = 0x02;
	cube[6][4] = 0x02;
	cube[6][5] = 0x03;
	cube[6][6] = 0x02;
	cube[6][7] = 0x02;
	cube_show_loop(dur);
	cube[1][0] = 0x04;
	cube[1][1] = 0x06;
	cube[1][2] = 0x05;
	cube[1][3] = 0x04;
	cube[1][4] = 0x04;
	cube[1][5] = 0x04;
	cube[1][6] = 0x04;
	cube[1][7] = 0x04;
	cube[4][0] = 0x06;
	cube[4][1] = 0x06;
	cube[4][2] = 0x07;
	cube[4][3] = 0x07;
	cube[4][4] = 0x07;
	cube[4][5] = 0x07;
	cube[4][6] = 0x04;
	cube[4][7] = 0x04;
	cube[6][4] = 0x04;
	cube[6][5] = 0x05;
	cube[6][6] = 0x06;
	cube[6][7] = 0x04;
	cube_show_loop(dur);
	cube[1][0] = 0x08;
	cube[1][1] = 0x0e;
	cube[1][2] = 0x09;
	cube[1][3] = 0x08;
	cube[1][4] = 0x08;
	cube[1][5] = 0x08;
	cube[1][6] = 0x0c;
	cube[1][7] = 0x0c;
	cube[4][0] = 0x0e;
	cube[4][1] = 0x0e;
	cube[4][2] = 0x0f;
	cube[4][3] = 0x0f;
	cube[4][4] = 0x0f;
	cube[4][5] = 0x0f;
	cube[4][6] = 0x08;
	cube[4][7] = 0x08;
	cube[6][4] = 0x08;
	cube[6][5] = 0x09;
	cube[6][6] = 0x0e;
	cube[6][7] = 0x08;
	cube_show_loop(dur);
	cube[1][0] = 0x10;
	cube[1][1] = 0x1e;
	cube[1][2] = 0x11;
	cube[1][3] = 0x10;
	cube[1][4] = 0x10;
	cube[1][5] = 0x18;
	cube[1][6] = 0x1c;
	cube[1][7] = 0x1c;
	cube[4][0] = 0x1e;
	cube[4][1] = 0x1e;
	cube[4][2] = 0x1f;
	cube[4][3] = 0x1f;
	cube[4][4] = 0x1f;
	cube[4][5] = 0x1f;
	cube[4][6] = 0x10;
	cube[4][7] = 0x10;
	cube[6][4] = 0x10;
	cube[6][5] = 0x11;
	cube[6][6] = 0x1e;
	cube[6][7] = 0x10;
	cube_show_loop(dur);
	cube[1][0] = 0x20;
	cube[1][1] = 0x3e;
	cube[1][2] = 0x21;
	cube[1][3] = 0x20;
	cube[1][4] = 0x20;
	cube[1][5] = 0x38;
	cube[1][6] = 0x3c;
	cube[1][7] = 0x3c;
	cube[4][0] = 0x3e;
	cube[4][1] = 0x3e;
	cube[4][2] = 0x3f;
	cube[4][3] = 0x3f;
	cube[4][4] = 0x3f;
	cube[4][5] = 0x3f;
	cube[4][6] = 0x20;
	cube[4][7] = 0x20;
	cube[6][4] = 0x20;
	cube[6][5] = 0x21;
	cube[6][6] = 0x3e;
	cube[6][7] = 0x20;
	cube_show_loop(dur);
	cube[1][0] = 0x40;
	cube[1][1] = 0x7e;
	cube[1][2] = 0x41;
	cube[1][3] = 0x40;
	cube[1][4] = 0x40;
	cube[1][5] = 0x58;
	cube[1][6] = 0x7c;
	cube[1][7] = 0x7c;
	cube[4][0] = 0x7e;
	cube[4][1] = 0x7e;
	cube[4][2] = 0x7f;
	cube[4][3] = 0x7f;
	cube[4][4] = 0x7f;
	cube[4][5] = 0x7f;
	cube[4][6] = 0x40;
	cube[4][7] = 0x40;
	cube[6][4] = 0x40;
	cube[6][5] = 0x41;
	cube[6][6] = 0x7e;
	cube[6][7] = 0x40;
	cube_show_loop(dur);
	cube[1][0] = 0x80;
	cube[1][1] = 0xfe;
	cube[1][2] = 0x81;
	cube[1][3] = 0x80;
	cube[1][4] = 0x80;
	cube[1][5] = 0x98;
	cube[1][6] = 0xbc;
	cube[1][7] = 0xbc;
	cube[4][0] = 0xfe;
	cube[4][1] = 0xfe;
	cube[4][2] = 0xff;
	cube[4][3] = 0xff;
	cube[4][4] = 0xff;
	cube[4][5] = 0xff;
	cube[4][6] = 0x80;
	cube[4][7] = 0x80;
	cube[6][4] = 0x80;
	cube[6][5] = 0x81;
	cube[6][6] = 0xfe;
	cube[6][7] = 0x80;
	cube_show_loop(dur);
	cube[1][0] = 0x00;
	cube[1][1] = 0x7e;
	cube[1][3] = 0x00;
	cube[1][4] = 0x00;
	cube[1][5] = 0x18;
	cube[1][6] = 0x3c;
	cube[1][7] = 0x3c;
	cube[2][0] = 0x01;
	cube[2][1] = 0x01;
	cube[2][2] = 0x01;
	cube[2][3] = 0x01;
	cube[2][4] = 0x01;
	cube[2][5] = 0x01;
	cube[2][6] = 0x01;
	cube[2][7] = 0x01;
	cube[4][0] = 0x7e;
	cube[4][1] = 0x7e;
	cube[4][6] = 0x00;
	cube[4][7] = 0x00;
	cube[5][0] = 0x01;
	cube[5][1] = 0x01;
	cube[5][2] = 0x01;
	cube[5][3] = 0x01;
	cube[5][4] = 0x01;
	cube[5][5] = 0x01;
	cube[5][6] = 0x01;
	cube[5][7] = 0x01;
	cube[6][4] = 0x00;
	cube[6][6] = 0x7e;
	cube[6][7] = 0x00;
	cube[7][2] = 0x01;
	cube[7][3] = 0x01;
	cube[7][4] = 0x01;
	cube[7][5] = 0x01;
	cube_show_loop(dur);
	cube[2][0] = 0x02;
	cube[2][1] = 0x02;
	cube[2][2] = 0x03;
	cube[2][3] = 0x02;
	cube[2][4] = 0x02;
	cube[2][5] = 0x02;
	cube[2][6] = 0x02;
	cube[2][7] = 0x02;
	cube[5][0] = 0x02;
	cube[5][1] = 0x02;
	cube[5][2] = 0x02;
	cube[5][3] = 0x02;
	cube[5][4] = 0x03;
	cube[5][5] = 0x03;
	cube[5][6] = 0x02;
	cube[5][7] = 0x02;
	cube[7][2] = 0x02;
	cube[7][3] = 0x03;
	cube[7][4] = 0x02;
	cube[7][5] = 0x02;
	cube_show_loop(dur);
	cube[2][0] = 0x04;
	cube[2][1] = 0x04;
	cube[2][2] = 0x05;
	cube[2][3] = 0x06;
	cube[2][4] = 0x04;
	cube[2][5] = 0x04;
	cube[2][6] = 0x04;
	cube[2][7] = 0x04;
	cube[5][0] = 0x04;
	cube[5][1] = 0x04;
	cube[5][2] = 0x04;
	cube[5][3] = 0x04;
	cube[5][4] = 0x05;
	cube[5][5] = 0x05;
	cube[5][6] = 0x04;
	cube[5][7] = 0x04;
	cube[7][2] = 0x06;
	cube[7][3] = 0x05;
	cube[7][4] = 0x04;
	cube[7][5] = 0x04;
	cube_show_loop(dur);
	cube[2][0] = 0x08;
	cube[2][1] = 0x08;
	cube[2][2] = 0x09;
	cube[2][3] = 0x0a;
	cube[2][4] = 0x0c;
	cube[2][5] = 0x08;
	cube[2][6] = 0x08;
	cube[2][7] = 0x08;
	cube[5][0] = 0x08;
	cube[5][1] = 0x08;
	cube[5][2] = 0x08;
	cube[5][3] = 0x08;
	cube[5][4] = 0x09;
	cube[5][5] = 0x09;
	cube[5][6] = 0x08;
	cube[5][7] = 0x0c;
	cube[7][2] = 0x0a;
	cube[7][3] = 0x09;
	cube[7][4] = 0x08;
	cube[7][5] = 0x08;
	cube_show_loop(dur);
	cube[2][0] = 0x10;
	cube[2][1] = 0x10;
	cube[2][2] = 0x11;
	cube[2][3] = 0x12;
	cube[2][4] = 0x14;
	cube[2][5] = 0x18;
	cube[2][6] = 0x18;
	cube[2][7] = 0x10;
	cube[5][0] = 0x10;
	cube[5][1] = 0x10;
	cube[5][2] = 0x10;
	cube[5][3] = 0x10;
	cube[5][4] = 0x11;
	cube[5][5] = 0x19;
	cube[5][6] = 0x18;
	cube[5][7] = 0x14;
	cube[7][2] = 0x12;
	cube[7][3] = 0x11;
	cube[7][4] = 0x10;
	cube[7][5] = 0x10;
	cube_show_loop(dur);
	cube[2][0] = 0x20;
	cube[2][1] = 0x20;
	cube[2][2] = 0x21;
	cube[2][3] = 0x22;
	cube[2][4] = 0x24;
	cube[2][5] = 0x28;
	cube[2][6] = 0x28;
	cube[2][7] = 0x30;
	cube[5][0] = 0x30;
	cube[5][1] = 0x30;
	cube[5][2] = 0x30;
	cube[5][3] = 0x30;
	cube[5][4] = 0x31;
	cube[5][5] = 0x29;
	cube[5][6] = 0x28;
	cube[5][7] = 0x24;
	cube[7][2] = 0x22;
	cube[7][3] = 0x21;
	cube[7][4] = 0x20;
	cube[7][5] = 0x20;
	cube_show_loop(dur);
	cube[2][0] = 0x40;
	cube[2][1] = 0x40;
	cube[2][2] = 0x41;
	cube[2][3] = 0x42;
	cube[2][4] = 0x44;
	cube[2][5] = 0x48;
	cube[2][6] = 0x48;
	cube[2][7] = 0x50;
	cube[5][0] = 0x50;
	cube[5][1] = 0x50;
	cube[5][2] = 0x50;
	cube[5][3] = 0x50;
	cube[5][4] = 0x51;
	cube[5][5] = 0x49;
	cube[5][6] = 0x48;
	cube[5][7] = 0x44;
	cube[7][2] = 0x42;
	cube[7][3] = 0x41;
	cube[7][4] = 0x40;
	cube[7][5] = 0x40;
	cube_show_loop(dur);
	cube[2][0] = 0x80;
	cube[2][1] = 0x80;
	cube[2][2] = 0x81;
	cube[2][3] = 0x82;
	cube[2][4] = 0x84;
	cube[2][5] = 0x88;
	cube[2][6] = 0x88;
	cube[2][7] = 0x90;
	cube[5][0] = 0x90;
	cube[5][1] = 0x90;
	cube[5][2] = 0x90;
	cube[5][3] = 0x90;
	cube[5][4] = 0x91;
	cube[5][5] = 0x89;
	cube[5][6] = 0x88;
	cube[5][7] = 0x84;
	cube[7][2] = 0x82;
	cube[7][3] = 0x81;
	cube[7][4] = 0x80;
	cube[7][5] = 0x80;
	cube_show_loop(dur);
	cube[2][0] = 0x00;
	cube[2][1] = 0x00;
	cube[2][2] = 0x01;
	cube[2][3] = 0x02;
	cube[2][4] = 0x04;
	cube[2][5] = 0x08;
	cube[2][6] = 0x08;
	cube[2][7] = 0x10;
	cube[5][0] = 0x10;
	cube[5][1] = 0x10;
	cube[5][2] = 0x10;
	cube[5][3] = 0x10;
	cube[5][4] = 0x11;
	cube[5][5] = 0x09;
	cube[5][6] = 0x08;
	cube[5][7] = 0x04;
	cube[7][0] = 0xff;
	cube[7][1] = 0xff;
	cube[7][2] = 0x02;
	cube[7][3] = 0x01;
	cube[7][4] = 0x00;
	cube[7][5] = 0x00;
	cube[7][6] = 0x0f;
	cube_show_loop(dur);
	cube[7][0] = 0x00;
	cube[7][1] = 0x00;
	cube[7][6] = 0x00;
	cube_show_loop(dur);
	cube[0][2] = 0x00;
	cube[0][3] = 0x00;
	cube[0][4] = 0x00;
	cube[0][5] = 0x00;
	cube[0][6] = 0x00;
	cube[0][7] = 0x00;
	cube[1][1] = 0x00;
	cube[1][2] = 0x00;
	cube[1][5] = 0x00;
	cube[1][6] = 0x00;
	cube[1][7] = 0x00;
	cube[2][2] = 0x00;
	cube[2][3] = 0x00;
	cube[2][4] = 0x00;
	cube[2][5] = 0x00;
	cube[2][6] = 0x00;
	cube[2][7] = 0x00;
	cube[3][0] = 0x00;
	cube[3][1] = 0x00;
	cube[3][2] = 0x00;
	cube[3][3] = 0x00;
	cube[3][4] = 0x00;
	cube[3][5] = 0x00;
	cube[3][6] = 0x00;
	cube[3][7] = 0x00;
	cube[4][0] = 0x00;
	cube[4][1] = 0x00;
	cube[4][2] = 0x00;
	cube[4][3] = 0x00;
	cube[4][4] = 0x00;
	cube[4][5] = 0x00;
	cube[5][0] = 0x00;
	cube[5][1] = 0x00;
	cube[5][2] = 0x00;
	cube[5][3] = 0x00;
	cube[5][4] = 0x00;
	cube[5][5] = 0x00;
	cube[5][6] = 0x00;
	cube[5][7] = 0x00;
	cube[6][0] = 0x00;
	cube[6][1] = 0x00;
	cube[6][5] = 0x00;
	cube[6][6] = 0x00;
	cube[7][2] = 0x00;
	cube[7][3] = 0x00;
}

/* ------------------------------------------------------------------------- */

