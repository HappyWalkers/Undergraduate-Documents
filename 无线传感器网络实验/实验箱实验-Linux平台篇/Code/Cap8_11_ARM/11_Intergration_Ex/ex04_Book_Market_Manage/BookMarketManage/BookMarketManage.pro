#-------------------------------------------------
#
# Project created by QtCreator 2012-07-04T12:16:14
#
#-------------------------------------------------

QT       += core gui sql

TARGET = BookMarketManage
TEMPLATE = app

OBJECTS_DIR = .obj
MOC_DIR = .moc
UI_DIR = .uic

INCLUDEPATH += .\
    ../BookMarketManage/QRFID \
    ../BookMarketManage/qextserialport/include \
    ../BookMarketManage/qhexedit \

LIBS += -L../BookMarketManage/qextserialport/lib
win32 {
    CONFIG(debug, debug|release): LIBS += -lqextserialportd1
    else: LIBS += -lqextserialport1
}
unix {
    LIBS += -lqextserialport
}

SOURCES += main.cpp\
    BookMarketManageWidget.cpp \
    DBControl.cpp \
    qhexedit/xbytearray.cpp \
    qhexedit/qhexedit_p.cpp \
    qhexedit/qhexedit.cpp \
    qhexedit/commands.cpp \
    PageBorrowWidget.cpp \
    PageBackWidget.cpp \
    PageManageWidget.cpp \
    BookInfoEditDialog.cpp \
    t9keyboard/t9widget.cpp \
    QRFID/ChannelMan/RFIDChannelMan.cpp \
    QRFID/RLM100/RLM100Package.cpp \
    QRFID/RLM100/RLM100Control.cpp

HEADERS  += BookMarketManageWidget.h \
    DBControl.h \
    qhexedit/xbytearray.h \
    qhexedit/qhexedit_p.h \
    qhexedit/qhexedit.h \
    qhexedit/commands.h \
    PageBorrowWidget.h \
    PageBackWidget.h \
    PageManageWidget.h \
    BookInfoEditDialog.h \
    t9keyboard/t9widget.h \
    QRFID/ChannelMan/RFIDChannelMan.h \
    QRFID/RLM100/RLM100Package.h \
    QRFID/RLM100/RLM100Control.h

FORMS    += BookMarketManageWidget.ui \
    PageBorrowWidget.ui \
    PageBackWidget.ui \
    PageManageWidget.ui \
    BookInfoEditDialog.ui \
    t9keyboard/t9widget.ui

RESOURCES += \
    res.qrc

TRANSLATIONS += zh_CN.ts
