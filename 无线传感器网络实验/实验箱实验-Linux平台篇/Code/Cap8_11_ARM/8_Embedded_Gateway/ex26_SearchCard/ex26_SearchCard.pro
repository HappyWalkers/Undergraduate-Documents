#-------------------------------------------------
#
# Project created by QtCreator 2014-03-10T14:25:15
#
#-------------------------------------------------

QT       += core gui

TARGET = ex26_SearchCard
TEMPLATE = app

INCLUDEPATH += ../ex26_SearchCard/qextserialport/include \
    ../ex26_SearchCard/QRFID

QMAKE_LIBDIR += ../ex26_SearchCard/qextserialport/lib
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
