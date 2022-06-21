#-------------------------------------------------
#
# Project created by QtCreator 2012-07-02T19:49:48
#
#-------------------------------------------------

QT       += core gui sql

TARGET = Attendance
TEMPLATE = app

OBJECTS_DIR = .obj
MOC_DIR = .moc
UI_DIR = .uic

INCLUDEPATH += .\
        ../Attendance/qextserialport/include  \
        ../Attendance/QRFID
LIBS += -L../Attendance/qextserialport/lib
win32 {
    CONFIG(debug, debug|release): LIBS += -lqextserialportd1
    else: LIBS += -lqextserialport1
}
unix {
    LIBS += -lqextserialport
}

SOURCES += main.cpp\
    MainWidget.cpp \
    DBControl.cpp \
    ClockInWidget.cpp \
    ManageWidget.cpp \
    rotatenumberlabel.cpp \
    UserEditDialog.cpp \
    QRFID/ChannelMan/RFIDChannelMan.cpp \
    QRFID/ID125K/ID125KControl.cpp \
    t9keyboard/t9widget.cpp

HEADERS  += \
    DBControl.h \
    ClockInWidget.h \
    ManageWidget.h \
    rotatenumberlabel.h \
    UserEditDialog.h \
    MainWidget.h \
    QRFID/ChannelMan/RFIDChannelMan.h \
    QRFID/ID125K/ID125KControl.h \
    t9keyboard/t9widget.h

FORMS    += MainWidget.ui \
    ClockInWidget.ui \
    ManageWidget.ui \
    UserEditDialog.ui \
    t9keyboard/t9widget.ui

RESOURCES += \
    res.qrc


linux-arm-gnueabi-g++ {
    target.path=/root
    INSTALLS += target
}
