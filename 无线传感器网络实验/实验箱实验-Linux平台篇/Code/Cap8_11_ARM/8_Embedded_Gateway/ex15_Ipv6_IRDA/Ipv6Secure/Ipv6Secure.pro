#-------------------------------------------------
#
# Project created by QtCreator 2014-08-06T13:25:08
#
#-------------------------------------------------

QT       += core gui

TARGET = Ipv6Secure
TEMPLATE = app

LIBS += -L../Ipv6Secure/lib -lipv6comm
INCLUDEPATH += ../Ipv6Secure/include

SOURCES += main.cpp\
        widget.cpp \
    secure.cpp

HEADERS  += widget.h \
    secure.h

FORMS    += widget.ui \
    secure.ui

RESOURCES += \
    res.qrc
