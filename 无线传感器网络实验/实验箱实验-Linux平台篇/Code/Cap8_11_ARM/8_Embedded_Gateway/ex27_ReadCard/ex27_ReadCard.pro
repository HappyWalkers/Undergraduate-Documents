#-------------------------------------------------
#
# Project created by QtCreator 2014-03-10T16:23:34
#
#-------------------------------------------------

QT       += core gui

TARGET = ex27_ReadCard
TEMPLATE = app

INCLUDEPATH += ../ex27_ReadCard/qextserialport/include \
    ../ex27_ReadCard/QRFID

QMAKE_LIBDIR += ../ex27_ReadCard/qextserialport/lib
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
