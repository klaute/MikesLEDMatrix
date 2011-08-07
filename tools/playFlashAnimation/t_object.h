#ifndef T_OBJECT_H
#define T_OBJECT_H

#include <QObject>
#include <QtCore/QCoreApplication>
#include <usbconfig.h>

extern "C"
{
#include "hiddata.h"
}

class T_Object : public QObject
{
    Q_OBJECT

public:
    usbDevice_t *dev;
    QCoreApplication* app;
    char        buffer[65];

    explicit T_Object(usbDevice_t*, QCoreApplication*, QObject *parent = 0);

signals:

public slots:
    void end();

};

#endif // T_OBJECT_H
