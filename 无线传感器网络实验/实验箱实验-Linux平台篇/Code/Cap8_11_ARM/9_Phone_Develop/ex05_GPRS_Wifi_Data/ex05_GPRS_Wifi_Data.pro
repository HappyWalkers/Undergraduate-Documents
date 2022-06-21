# -------------------------------------------------
# Project created by QtCreator 2012-02-02T10:14:49
# -------------------------------------------------
QT += core \
    gui network

TARGET = ex05_GPRS_Wifi_Data
TEMPLATE = app

INCLUDEPATH += \
    ../ex05_GPRS_Wifi_Data/include

LIBS +=   \
    -L../ex05_GPRS_Wifi_Data/lib \
    -llibsmscb -lwificomm

SOURCES += ex05_GPRS_Wifi_Data.cpp

linux-* {
target.path=/root
INSTALLS += target
}
