#include <QtCore/QCoreApplication>
#include <usbconfig.h>
#include <QTimer>
#include <QStringList>
#include <QDebug>

#include "t_object.h"

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


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc < 2)
    {
         qDebug("playFlashAnimation <0 - 7> <Zeit in Millisekunden>");

         return -1;
     }
    usbDevice_t* dev;
    dev = openDevice();

    T_Object* object;
    object = new T_Object(dev, &a);

    if (dev == NULL)
    {
        qDebug("Konnt USB-Device nicht öffnen");
        return -1;
    }

    int animation = a.arguments().at(1).toInt();
    qDebug() << QString("%1").arg(animation);

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

    buffer[1] =4;
    buffer[2] = 30 + animation;

    if( usbhidSetReport(dev, buffer, 3) != 0)
    {
        qDebug("Fehler beim oeffnen");
    }

    if(argc == 3)
    {
        int t = a.arguments().at(2).toInt();
        QTimer::singleShot(t, object, SLOT(end()));
    }
    else
    {
        usbhidCloseDevice(dev);
        return 0;
    }

    return a.exec();
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
