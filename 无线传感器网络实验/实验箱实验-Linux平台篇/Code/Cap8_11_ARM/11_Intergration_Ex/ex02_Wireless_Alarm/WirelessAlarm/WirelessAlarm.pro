#-------------------------------------------------
#
# Project created by QtCreator 2012-07-03T15:58:40
#
#-------------------------------------------------

QT       += core gui

TARGET = WirelessAlarm
TEMPLATE = app

OBJECTS_DIR = .obj
MOC_DIR = .moc
UI_DIR = .uic

INCLUDEPATH += .\
    ../WirelessAlarm/include  \

!win32 {
LIBS +=  -L../WirelessAlarm/lib  \
         -lipv6comm \
         -llibsmscb
}

SOURCES += main.cpp\
        WirelessAlarmWidget.cpp

HEADERS  += WirelessAlarmWidget.h

FORMS    += WirelessAlarmWidget.ui

RESOURCES += \
    res.qrc

HEADERS += \
    TwinklingLabel.h

SOURCES += \
    TwinklingLabel.cpp
