# -------------------------------------------------
# Project created by QtCreator 2012-02-02T10:14:49
# -------------------------------------------------
QT += core \
    gui network

TARGET = ex03_GPRS_Control
TEMPLATE = app

INCLUDEPATH += \
    ../ex03_GPRS_Control/include

LIBS +=   \
		-L../ex03_GPRS_Control/lib \
    -llibsmscb -lwsncomm

SOURCES += ex03_GPRS_Control.cpp

linux-* {
target.path=/root
INSTALLS += target
}
