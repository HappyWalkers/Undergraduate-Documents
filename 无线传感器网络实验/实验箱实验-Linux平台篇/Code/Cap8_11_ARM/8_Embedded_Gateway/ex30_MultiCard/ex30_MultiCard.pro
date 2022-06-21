#-------------------------------------------------
#
# Project created by QtCreator 2012-05-04T05:50:50
#
#-------------------------------------------------

QT       += core gui

TARGET = ex30_MultiCard
TEMPLATE = app

INCLUDEPATH += \
    ../ex30_MultiCard/qextserialport/include \
    ../ex30_MultiCard/QRFID

QMAKE_LIBDIR += ../ex30_MultiCard/qextserialport/lib
LIBS += -lqextserialport

SOURCES += main.cpp\
        widget.cpp \
    QRFID/ChannelMan/RFIDChannelMan.cpp \
    QRFID/UHF900M/RLM100Package.cpp \
    QRFID/UHF900M/RLM100Control.cpp

HEADERS  += widget.h \
    QRFID/ChannelMan/RFIDChannelMan.h \
    QRFID/UHF900M/RLM100Package.h \
    QRFID/UHF900M/RLM100Control.h

FORMS    += widget.ui
