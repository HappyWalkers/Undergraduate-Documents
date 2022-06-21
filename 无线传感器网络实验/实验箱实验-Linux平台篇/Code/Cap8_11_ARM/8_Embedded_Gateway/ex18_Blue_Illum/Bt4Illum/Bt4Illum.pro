#-------------------------------------------------
#
# Project created by QtCreator 2014-10-09T19:08:53
#
#-------------------------------------------------

QT       += core gui

TARGET = Bt4Illum
TEMPLATE = app

LIBS += -L../Bt4Illum/lib -lbt4comm
INCLUDEPATH += ../Bt4Illum/include

SOURCES += main.cpp\
        widget.cpp \
    bleIllum.cpp

HEADERS  += widget.h \
    bleIllum.h

FORMS    += widget.ui \
    bleIllum.ui
