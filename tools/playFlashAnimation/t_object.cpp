#include "t_object.h"

T_Object::T_Object(usbDevice_t* d, QCoreApplication* a,QObject *parent) :
    QObject(parent)
{
    dev = d;
    app = a;
}

void T_Object::end()
{

    bzero(buffer, sizeof(buffer));

    buffer[1] =4;
    buffer[2] = 254;

    if( usbhidSetReport(dev, buffer, 3) != 0)
    {
        qDebug("Fehler beim oeffnen");
    }
    usbhidCloseDevice(dev);
    app->quit();
}
