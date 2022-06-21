#-------------------------------------------------
#
# Project created by QtCreator 2012-06-29T15:36:50
#
#-------------------------------------------------

QT       += core gui

TARGET = ColdStorageMonitor
TEMPLATE = app

OBJECTS_DIR = .obj
MOC_DIR = .moc
UI_DIR = .uic

INCLUDEPATH += .\
    ../ColdStorageMonitor/include  \

!win32 {
LIBS +=  -L../ColdStorageMonitor/lib  \
     -lwificomm
}

SOURCES += main.cpp\
        widget.cpp \
    RealTimeMonitorWidget.cpp \
    HistoryMonitorWidget.cpp \
    ControlSettingWidget.cpp \
    BigSpinBoxEdit.cpp

HEADERS  += widget.h \
    RealTimeMonitorWidget.h \
    HistoryMonitorWidget.h \
    ControlSettingWidget.h \
    BigSpinBoxEdit.h

FORMS    += widget.ui \
    RealTimeMonitorWidget.ui \
    HistoryMonitorWidget.ui \
    ControlSettingWidget.ui \
    BigSpinBoxEdit.ui

RESOURCES += \
    res.qrc

HEADERS +=

SOURCES +=

FORMS +=

HEADERS += \
    AlertLabel.h

SOURCES += \
    AlertLabel.cpp

FORMS +=

HEADERS += \
    ColdStorageSetting.h

SOURCES += \
    ColdStorageSetting.cpp

HEADERS += \
    datagridlabel.h

SOURCES += \
    datagridlabel.cpp
