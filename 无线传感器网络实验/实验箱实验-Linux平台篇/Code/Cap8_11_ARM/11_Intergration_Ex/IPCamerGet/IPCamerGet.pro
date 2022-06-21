#-------------------------------------------------
#
# Project created by QtCreator 2016-03-27T18:57:25
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IPCamerGet
TEMPLATE = app

SOURCES += main.cpp\
        Widget.cpp \
    MjpgWidget/MjpgWidget.cpp \
    MjpgWidget/HttpClientService.cpp \

HEADERS  += Widget.h \
    MjpgWidget/MjpgWidget.h \
    MjpgWidget/HttpClientService.h \
    libqjson/include/qjson/serializerrunnable.h \
    libqjson/include/qjson/serializer.h \
    libqjson/include/qjson/qobjecthelper.h \
    libqjson/include/qjson/qjson_export.h \
    libqjson/include/qjson/parserrunnable.h \
    libqjson/include/qjson/parser.h \

FORMS    += Widget.ui


RESOURCES += \
    qrc.qrc

INCLUDEPATH +=  \
    ../IPCamerGet \
    ../IPCamerGet/MjpgWidget \
    ../IPCamerGet/include \
    ../IPCamerGet/lib_json/include \
    ../IPCamerGet/qhttpserver \
    ../IPCamerGet/VehicleManager \
    ../IPCamerGet/libqjson/include\

LIBS +=  \
    -L./lib \
    -lqjson

linux-arm-gnueabi-g++ {
    target.path=/root
    INSTALLS += target
}
