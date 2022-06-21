# -------------------------------------------------
# Project created by QtCreator 2012-02-02T10:14:49
# -------------------------------------------------
QT += core \
    gui network

TARGET = ex04_GPRS_Blue_Data
TEMPLATE = app

INCLUDEPATH += \
    ../ex04_GPRS_Blue_Data/include

LIBS +=   \
    -L../ex04_GPRS_Blue_Data/lib \
    -llibsmscb -lwsncomm -lbt4comm

SOURCES += ex04_GPRS_Blue_Data.cpp

linux-* {
target.path=/root
INSTALLS += target
}
