#-------------------------------------------------
#
# Project created by QtCreator 2014-03-10T16:23:34
#
#-------------------------------------------------

QT       += core gui

TARGET = ex28_WriteCard
TEMPLATE = app

INCLUDEPATH += ../ex28_WriteCard/qextserialport/include \
    ../ex28_WriteCard/QRFID

QMAKE_LIBDIR += ../ex28_WriteCard/qextserialport/lib
LIBS += -lqextserialport

SOURCES += main.cpp\
        Widget.cpp \
    QRFID/ChannelMan/RFIDChannelMan.cpp \
    QRFID/IEEE14443/IEEE14443Package.cpp \
    QRFID/IEEE14443/IEEE14443Control.cpp

HEADERS  += Widget.h \
    QRFID/ChannelMan/RFIDChannelMan.h \
    QRFID/IEEE14443/IEEE14443Package.h \
    QRFID/IEEE14443/IEEE14443Control.h

FORMS    += Widget.ui
