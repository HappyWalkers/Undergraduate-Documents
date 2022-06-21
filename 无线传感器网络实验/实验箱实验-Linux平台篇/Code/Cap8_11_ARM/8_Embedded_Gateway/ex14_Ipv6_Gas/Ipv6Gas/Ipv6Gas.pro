#-------------------------------------------------
#
# Project created by QtCreator 2014-08-05T16:19:01
#
#-------------------------------------------------

QT       += core gui

TARGET = Ipv6Gas
TEMPLATE = app

LIBS += -L../Ipv6Gas/lib -lipv6comm
INCLUDEPATH += ../Ipv6Gas/include

SOURCES += main.cpp\
        widget.cpp \
    gas.cpp

HEADERS  += widget.h \
    gas.h

FORMS    += widget.ui \
    gas.ui

RESOURCES += \
    Gas_Res.qrc
