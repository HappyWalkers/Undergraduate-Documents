#-------------------------------------------------
#
# Project created by QtCreator 2011-08-12T17:40:36
#
#-------------------------------------------------

QT       += core gui

TARGET = Excute
TEMPLATE = app

LIBS += -L../Excute/lib -lwsncomm

INCLUDEPATH += ../Excute/include


SOURCES += main.cpp\
        widget.cpp \
        excute.cpp

HEADERS  += widget.h \
            excute.h

FORMS    += widget.ui \
            excute.ui
