#-------------------------------------------------
#
# Project created by QtCreator 2011-06-28T17:38:39
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = playFlashAnimation
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += usbconfig.h \
           hiddata.h \
    t_object.h

SOURCES += main.cpp \
           hiddata.c \
    t_object.cpp

LIBS += -L/usr/lib \
        -lusb
