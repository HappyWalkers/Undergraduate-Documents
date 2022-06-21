#-------------------------------------------------
#
# Project created by QtCreator 2012-05-04T05:50:50
#
#-------------------------------------------------

QT       += core gui

TARGET = ex32_WriteUHF900M
TEMPLATE = app

INCLUDEPATH += ../ex32_WriteUHF900M/qextserialport/include \
	../ex32_WriteUHF900M/QRFID

QMAKE_LIBDIR += ../ex32_WriteUHF900M/qextserialport/lib
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
