#-------------------------------------------------
#
# Project created by QtCreator 2014-12-03T19:01:14
#
#-------------------------------------------------

QT       += core gui

TARGET = ex22_Wifi_Data
TEMPLATE = app

LIBS += -L. -L../ex22_Wifi_Data/lib -lwificomm
INCLUDEPATH += . ../ex22_Wifi_Data/include

SOURCES += main.cpp\
        widget.cpp \
    wifiWidget/wifinet.cpp

HEADERS  += widget.h \
    wifiWidget/wifinet.h

FORMS    += widget.ui \
    wifiWidget/wifinet.ui
