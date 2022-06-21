# -------------------------------------------------
# Project created by QtCreator 2012-02-02T10:14:49
# -------------------------------------------------
QT += core \
    gui network

TARGET = ex07_IPV6_Control
TEMPLATE = app

INCLUDEPATH += \
    ../ex07_IPV6_Control/include

LIBS +=   \
                -L../ex07_IPV6_Control/lib \
    -llibsmscb -lipv6comm

SOURCES += ex07_IPV6_Control.cpp
