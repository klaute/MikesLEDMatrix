#-------------------------------------------------
#
# Project created by QtCreator 2011-08-07T08:15:38
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = setTime
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += usbconfig.h \
           hiddata.h \

SOURCES += main.cpp \
           hiddata.c

LIBS += -L/usr/lib \
        -lusb
