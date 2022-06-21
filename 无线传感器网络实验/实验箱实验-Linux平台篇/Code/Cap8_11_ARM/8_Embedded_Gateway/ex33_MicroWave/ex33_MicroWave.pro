#-------------------------------------------------
#
# Project created by QtCreator 2014-03-11T15:16:30
#
#-------------------------------------------------

QT       += core gui

TARGET = ex33_MicroWave
TEMPLATE = app

INCLUDEPATH += ../ex33_MicroWave/qextserialport/include \
    ../ex33_MicroWave/QRFID
QMAKE_LIBDIR += ../ex33_MicroWave/qextserialport/lib
LIBS += -lqextserialport

SOURCES += main.cpp\
        Widget.cpp \
    QRFID/ChannelMan/RFIDChannelMan.cpp \
    QRFID/MicroWave/MicroWaveControl.cpp

HEADERS  += Widget.h \
    QRFID/ChannelMan/RFIDChannelMan.h \
    QRFID/MicroWave/MicroWaveControl.h

FORMS    += Widget.ui
