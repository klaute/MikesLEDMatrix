/* Name: hidtool.c
 * Project: hid-data example
 * Author: Christian Starkjohann
 * Creation Date: 2008-04-11
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: hidtool.c 692 2008-11-07 15:07:40Z cs $
 *
 * Last change by Kai Lauterbach (klaute at gmail dot com) aka klaute - 27 Mar 2010
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hiddata.h"
#include "usbconfig.h"  /* for device VID, PID, vendor name and product name */

/* ------------------------------------------------------------------------- */

static char *usbErrorMessage(int errCode)
{
static char buffer[80];

    switch(errCode) {
        case USBOPEN_ERR_ACCESS:      return "Access to device denied";
        case USBOPEN_ERR_NOTFOUND:    return "The specified device was not found";
        case USBOPEN_ERR_IO:          return "Communication error with device";
        default:
            sprintf(buffer, "Unknown USB error %d", errCode);
            return buffer;
    }
    return NULL;    /* not reached */
}

static usbDevice_t  *openDevice(void)
{
usbDevice_t     *dev = NULL;
unsigned char   rawVid[2] = {USB_CFG_VENDOR_ID}, rawPid[2] = {USB_CFG_DEVICE_ID};
char            vendorName[] = {USB_CFG_VENDOR_NAME, 0}, productName[] = {USB_CFG_DEVICE_NAME, 0};
int             vid = rawVid[0] + 256 * rawVid[1];
int             pid = rawPid[0] + 256 * rawPid[1];
int             err;

    if ( (err = usbhidOpenDevice(&dev, vid, vendorName, pid, productName, 0)) != 0) {
        fprintf(stderr, "error finding %s: %s\n", productName, usbErrorMessage(err));
        return NULL;
    }
    return dev;
}

/* ------------------------------------------------------------------------- */

static void hexdump(char *buffer, int len)
{
int     i;
FILE    *fp = stdout;

    for ( i = 0; i < len; i++) {
        if ( i != 0) {
            if ( i % 16 == 0) {
                	fprintf(fp, "\n");
            } else {
                	fprintf(fp, " ");
            }
        }
        fprintf(fp, "0x%02x", buffer[i] & 0xff);
    }
    if ( i != 0)
        fprintf(fp, "\n");
}

static int  hexread(char *buffer, char *string, int buflen)
{
char    *s;
int     pos = 0;

    while((s = strtok(string, ", ")) != NULL && pos < buflen) {
        string = NULL;
        buffer[pos++] = (char)strtol(s, NULL, 0);
	//printf("%d>%d\n",pos-1,buffer[pos-1]);
    }
    return pos;
}

/* ------------------------------------------------------------------------- */

static void usage(char *myName)
{
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "  %s read\n", myName);
    fprintf(stderr, "  %s write <listofbytes>\n", myName);
    fprintf(stderr, "  %s interactive\n", myName);
}

int main(int argc, char **argv)
{
usbDevice_t *dev;
char        buffer[65];    /* room for dummy report ID */
int         err;
char        quiet = 0;

    if ( argc < 2) {
        usage(argv[0]);
        exit(1);
    }
    if ( (dev = openDevice()) == NULL)
        exit(1);

    if ( strcasecmp(argv[1], "read") == 0) {
        int len = sizeof(buffer);
        if ( (err = usbhidGetReport(dev, 0, buffer, &len)) != 0) {
            fprintf(stderr, "error reading data: %s\n", usbErrorMessage(err));
        } else {
            hexdump(buffer + 1, sizeof(buffer) - 1);
        }
    } else if ( strcasecmp(argv[1], "write") == 0) {
        int i, pos;
        bzero(buffer, sizeof(buffer));
        for ( pos = 1, i = 2; i < argc && pos < sizeof(buffer); i++) {
            pos += hexread(buffer + pos, argv[i], sizeof(buffer) - pos);
        }
	/*
	printf("%d\n",buffer[0]);
	printf("%d\n",buffer[1]);
	printf("%d\n",buffer[2]);
	printf("%d\n",buffer[3]);
	*/
        //if ( (err = usbhidSetReport(dev, buffer, sizeof(buffer))) != 0)   /* add a dummy report ID */
        if ( (err = usbhidSetReport(dev, buffer, pos)) != 0)   /* add a dummy report ID */
            fprintf(stderr, "error writing data: %s\n", usbErrorMessage(err));
    } else if ( strcasecmp( argv[1], "interactive" ) == 0 ) {
        int t = 0;
            for ( t = 0; t < argc; t++ )
	        if ( strcasecmp(argv[t], "quiet") == 0 )
	            quiet = 1;

	char *help = "q = exit\nr = read\nw = write <Data separated by spaces as decimal or hex (8bit unsigned)>\n";

	if ( !quiet )
	    printf("%s",help);

	char exit = 0;
	while ( exit != 1 )
	{
		int nbytes = 350;

		if ( !quiet )
			printf("> ");

		char *input;
		input = (char *) malloc (nbytes + 1);
		int cnt = getline(&input, &nbytes, stdin);

		if ( strncasecmp(input, "q", 1) == 0 )
		{

			if ( !quiet )
			    printf("bye.\n");

			exit = 1;

		} else if ( strncasecmp(input, "r", 1) == 0 ) {

			if ( !quiet )
			    printf("reading...\n");

			int len = sizeof(buffer) ;
			if ( (err = usbhidGetReport(dev, 0, buffer, &len)) != 0)
			{
				fprintf(stderr, "error reading data: %s\n", usbErrorMessage(err));
				exit = 1;
			} else {
				hexdump(buffer + 1, sizeof(buffer) - 1);
			}

		} else if ( strncasecmp(input, "w ", 2) == 0 ) {
        		int i, pos;
			input[0] = 32; // kommando durch leerzeichen ersetzen
			bzero(buffer, sizeof(buffer));

			if ( !quiet )
				printf("sending data... ");

			for ( pos = 1, i = 2; i < cnt -1 && pos < sizeof(buffer); i++) {
				//printf(">%c\n", input[i]);
				pos += hexread( buffer + pos, &input[i], sizeof(buffer) - pos);
			}
			if ( (err = usbhidSetReport(dev, buffer, sizeof(buffer))) != 0)   // add a dummy report ID
			{
				fprintf(stderr, "error writing data: %s\n", usbErrorMessage(err));
    				usbhidCloseDevice(dev);
				if ( (dev = openDevice()) != NULL)
					printf("reconnect...\n");
				else
					exit = 1;
			} else {
				if ( !quiet )
					printf("ok.\n");
			}
		} else
			printf("%s",help);
	}
    } else {
        usage(argv[0]);
        exit(1);
    }
    usbhidCloseDevice(dev);
    return 0;
}

/* ------------------------------------------------------------------------- */
