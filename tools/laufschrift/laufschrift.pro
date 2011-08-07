#-------------------------------------------------
#
# Project created by QtCreator 2011-08-04T19:46:15
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = laufschrift
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += usbconfig.h \
	   hiddata.h

SOURCES += main.cpp \
	   hiddata.c


LIBS += -L/usr/lib \
        -lusb

