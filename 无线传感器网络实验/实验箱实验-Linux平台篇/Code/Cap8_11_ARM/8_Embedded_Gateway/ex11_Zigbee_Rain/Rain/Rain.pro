#-------------------------------------------------
#
# Project created by QtCreator 2014-12-02T19:54:14
#
#-------------------------------------------------

QT       += core gui

TARGET = Rain
TEMPLATE = app

LIBS += -L../Rain/lib -lwsncomm
INCLUDEPATH +=  ../Rain/include

SOURCES += main.cpp\
        widget.cpp \
    rain.cpp

HEADERS  += widget.h \
    rain.h

FORMS    += widget.ui \
    rain.ui

RESOURCES += \
    Rain_Res.qrc
