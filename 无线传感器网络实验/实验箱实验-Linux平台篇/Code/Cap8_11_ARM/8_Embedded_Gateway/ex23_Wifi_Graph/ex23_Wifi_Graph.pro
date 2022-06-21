#-------------------------------------------------
#
# Project created by QtCreator 2012-04-28T12:22:10
#
#-------------------------------------------------

QT       += core gui

TARGET = ex23_Wifi_Graph
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    wifiWidget/wifi.cpp \
    wifiWidget/datagridlabel.cpp

HEADERS  += widget.h \
    wifiWidget/datagridlabel.h \
    wifiWidget/wifi.h

FORMS    += widget.ui \
    wifiWidget/wifi.ui
INCLUDEPATH +=  \
    . \
    ../ex23_Wifi_Graph/include

LIBS +=  \
    -L. \
    -L../ex23_Wifi_Graph/lib \
    -lwificomm

linux-arm-gnueabi-g++ {
    target.path=/root
    INSTALLS += target
}
