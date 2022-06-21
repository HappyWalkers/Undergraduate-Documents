#-------------------------------------------------
#
# Project created by QtCreator 2014-03-10T13:02:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ex25_125K
TEMPLATE = app

INCLUDEPATH += ../ex25_125K/qextserialport/include \
    ../ex25_125K/QRFID

QMAKE_LIBDIR += ../ex25_125K/qextserialport/lib
LIBS += -lqextserialport

SOURCES += main.cpp\
        Widget.cpp \
    QRFID/ChannelMan/RFIDChannelMan.cpp \
    QRFID/ID125K/ID125KControl.cpp

HEADERS  += Widget.h \
    QRFID/ChannelMan/RFIDChannelMan.h \
    QRFID/ID125K/ID125KControl.h

FORMS    += Widget.ui
