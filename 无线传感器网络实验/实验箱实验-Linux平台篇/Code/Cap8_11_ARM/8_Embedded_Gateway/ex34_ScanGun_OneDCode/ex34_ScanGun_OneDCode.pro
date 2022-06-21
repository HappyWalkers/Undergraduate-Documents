#-------------------------------------------------
#
# Project created by QtCreator 2012-05-29T11:20:45
#
#-------------------------------------------------

QT       += core gui

TARGET = ex34_ScanGun_OneDCode
TEMPLATE = app

INCLUDEPATH += \
    ../ex34_ScanGun_OneDCode/qextserialport/include \
    ../ex34_ScanGun_OneDCode/QRFID

QMAKE_LIBDIR += ../ex34_ScanGun_OneDCode/qextserialport/lib
LIBS += -lqextserialport

SOURCES += main.cpp\
        widget.cpp \
    QRFID/ChannelMan/RFIDChannelMan.cpp \
    QRFID/ScanGun/ScanGunControl.cpp

HEADERS  += widget.h \
    QRFID/ChannelMan/RFIDChannelMan.h \
    QRFID/ScanGun/ScanGunControl.h

FORMS    += widget.ui
