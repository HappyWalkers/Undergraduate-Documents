#-------------------------------------------------
#
# Project created by QtCreator 2012-04-28T12:22:10
#
#-------------------------------------------------

QT       += core gui

TARGET = ex24_Wifi_Shake
TEMPLATE = app

LIBS += -L. -L../ex24_Wifi_Shake/lib -lwificomm
INCLUDEPATH += . ../ex24_Wifi_Shake/include

SOURCES += main.cpp\
        widget.cpp \
    wifiWidget/wifinet.cpp

HEADERS  += widget.h \
    wifiWidget/wifinet.h

FORMS    += widget.ui \
    wifiWidget/wifinet.ui
