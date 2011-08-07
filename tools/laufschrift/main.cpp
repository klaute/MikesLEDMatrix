
#include <QDebug>

#include <usbconfig.h>

#include <iostream>
using namespace std;

extern "C"
{
#include "hiddata.h"
}

//-- USB Support ------------------------------------------
    usbDevice_t *dev;
    char        buffer[65];    /* room for dummy report ID */
    int         err;
    usbDevice_t* openDevice(void);
//----------------------------------------------------------

    char convertASCII_to_FlashTable(char c);

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    if (argc != 2)
    {
        cout << "laufschrift \"Text\"\n";
        return -1;
    }

    if (strlen(argv[1]) > 64)
    {
        cout << "Der Text darf nicht mehr als 64 Zeichen haben\n";
        return -1;
    }

    dev = openDevice();
    bzero(buffer, sizeof(buffer));
    buffer[1] = 1;
       if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
       {
           qDebug("Fehler bei der vorbereitung");
       }

       bzero(buffer, sizeof(buffer));

       for ( int i = 1; i < 9; i++)
       {
           if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
           {
               qDebug("Fehler bei nullchunk");
           }
       }

    bzero(buffer, sizeof(buffer));

    buffer[1] = 8;
    if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
    {
        qDebug("Fehler bei der vorbereitung");
        usbhidCloseDevice(dev);
        return -1;
    }

    bzero(buffer, sizeof(buffer));

    strncpy(&buffer[1], argv[1], strlen(argv[1]));

    //uint i;
    for(int x = 1; x < 65; x++)
    {
        buffer[x] = convertASCII_to_FlashTable(buffer[x]);

        //i = buffer[x-1];
        //cout << i << " " << buffer[x-1] << "\n";
    }

    if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
    {
        qDebug("Fehler bei der Textübertragung");
        usbhidCloseDevice(dev);
        return -1;
    }

    buffer[1] = 9;
    if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
    {
        qDebug("Fehler bei dem starten der Laufschrift");
        usbhidCloseDevice(dev);
        return -1;
    }

    usbhidCloseDevice(dev);

    return 0;
}

usbDevice_t* openDevice(void)
{
usbDevice_t     *dev = NULL;
unsigned char   rawVid[2] = {USB_CFG_VENDOR_ID}, rawPid[2] = {USB_CFG_DEVICE_ID};
char            vendorName[] = {USB_CFG_VENDOR_NAME, 0}, productName[] = {USB_CFG_DEVICE_NAME, 0};
int             vid = rawVid[0] + 256 * rawVid[1];
int             pid = rawPid[0] + 256 * rawPid[1];
int             err;

    if ( (err = usbhidOpenDevice(&dev, vid, vendorName, pid, productName, 0)) != 0) {
        qDebug("Fehler beim oeffnen des USB Device");
        return NULL;
    }
    return dev;
}

char convertASCII_to_FlashTable(char c)
{
    //Nur Grossbuchstaben
    if(c > 96 && c < 123)
    {
        c = c - 32;
        //A ist im Flash 0, B = 1, usw
        c = c - 65;
        return c;
    }

    //A ist im Flash 0, B = 1 usw
    if(c > 64 && c < 91)
        return c - 65;

    //Leerzeichen ist im Flash 26
    if (c == 32)
        return 26;

    //Der Rest wird Leerzeichen
    return 26;
}
