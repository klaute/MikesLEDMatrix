#include <QtCore/QCoreApplication>
#include <QDebug>
#include <usbconfig.h>
#include <QDateTime>

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
QDateTime zeit;
int h, m, s;
int main(int argc, char *argv[])
{
    dev = openDevice();
    zeit = QDateTime::currentDateTime();
    qDebug() << zeit.toString("hh:mm:ss");
    h = zeit.toString("hh:mm:ss").section(':',0,0).toInt();
    m = zeit.toString("hh:mm:ss").section(':',1,1).toInt();
    s = zeit.toString("hh:mm:ss").section(':',2,2).toInt();

    bzero(buffer, sizeof(buffer));

    buffer[1] = 1;
    if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
    {
        qDebug("Fehler bei der vorbereitung");
        usbhidCloseDevice(dev);
        return -1;
    }

    bzero(buffer, sizeof(buffer));

    for ( int i = 1; i < 9; i++)
    {
        if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
        {
            qDebug("Fehler bei nullchunk");
            usbhidCloseDevice(dev);
            return -1;
        }
    }

    bzero(buffer, sizeof(buffer));
    buffer[1] = 10;
    buffer[2] = h;
    buffer[3] = m;
    buffer[4] = s;
       if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
       {
           qDebug("Fehler bei dem starten Zeit");
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
