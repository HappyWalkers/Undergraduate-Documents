#-------------------------------------------------
#
# Project created by QtCreator 2012-07-03T15:58:40
#
#-------------------------------------------------

QT       += core gui

TARGET = IntelligentMedical
TEMPLATE = app

OBJECTS_DIR = .obj
MOC_DIR = .moc
UI_DIR = .uic

INCLUDEPATH += .\
    ../IntelligentMedical/include  \

!win32 {
LIBS +=  -L../IntelligentMedical/lib  \
         -lipv6comm \
         -lbt4comm \
         -lwsncomm \
         -llibsmscb
}

SOURCES += main.cpp\
        IntelligentMedicalWidget.cpp \
    BigSpinBoxEdit.cpp

HEADERS  += IntelligentMedicalWidget.h \
    bigspinboxedit.h

FORMS    += IntelligentMedicalWidget.ui \
    BigSpinBoxEdit.ui

RESOURCES += \
    res.qrc

HEADERS += \
    TwinklingLabel.h

SOURCES += \
    TwinklingLabel.cpp

linux-arm-gnueabi-g++ {
    target.path=/root
    INSTALLS += target
}
