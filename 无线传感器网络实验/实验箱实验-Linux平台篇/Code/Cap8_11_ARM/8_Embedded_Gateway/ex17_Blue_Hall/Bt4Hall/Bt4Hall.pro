#-------------------------------------------------
#
# Project created by QtCreator 2014-10-09T19:08:53
#
#-------------------------------------------------

QT       += core gui

TARGET = Bt4Hall
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    blehall.cpp

HEADERS  += widget.h \
    blehall.h

FORMS    += widget.ui \
    blehall.ui
INCLUDEPATH +=  \
    ../Bt4Hall/include

LIBS +=  \
    -L../Bt4Hall/lib \
    -lbt4comm

linux-arm-gnueabi-g++ {
    target.path=/root
    INSTALLS += target
}

RESOURCES += \
    Hall_Res.qrc
