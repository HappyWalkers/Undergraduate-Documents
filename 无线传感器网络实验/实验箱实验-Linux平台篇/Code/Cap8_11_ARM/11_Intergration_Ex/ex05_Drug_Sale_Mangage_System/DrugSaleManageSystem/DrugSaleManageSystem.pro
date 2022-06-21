#-------------------------------------------------
#
# Project created by QtCreator 2012-07-06T14:34:44
#
#-------------------------------------------------

QT       += core gui sql

TARGET = DrugSaleManageSystem
TEMPLATE = app

OBJECTS_DIR = .obj
MOC_DIR = .moc
UI_DIR = .uic

INCLUDEPATH += .\
    ../DrugSaleManageSystem/QRFID \
    ../DrugSaleManageSystem/qextserialport/include \
    ../DrugSaleManageSystem/qhexedit \

LIBS += -L../DrugSaleManageSystem/qextserialport/lib
win32 {
    CONFIG(debug, debug|release): LIBS += -lqextserialportd1
    else: LIBS += -lqextserialport1
}
unix {
    LIBS += -lqextserialport
}

SOURCES += main.cpp\
        DrugSaleManageSystemMainWidget.cpp \
    DBControl.cpp \
    PageBuyInWidget.cpp \
    PageSaleOutWidget.cpp \
    PageSaleRecordWidget.cpp \
    SaleItemWidget.cpp \
    BigSpinBoxEdit.cpp \
    PriceDialog.cpp \
    t9keyboard/t9widget.cpp \
    QRFID/ChannelMan/RFIDChannelMan.cpp \
    QRFID/RLM100/RLM100Package.cpp \
    QRFID/RLM100/RLM100Control.cpp

HEADERS  += DrugSaleManageSystemMainWidget.h \
    DBControl.h \
    PageBuyInWidget.h \
    PageSaleOutWidget.h \
    PageSaleRecordWidget.h \
    SaleItemWidget.h \
    BigSpinBoxEdit.h \
    PriceDialog.h \
    t9keyboard/t9widget.h \
    QRFID/ChannelMan/RFIDChannelMan.h \
    QRFID/RLM100/RLM100Package.h \
    QRFID/RLM100/RLM100Control.h

FORMS    += DrugSaleManageSystemMainWidget.ui \
    PageBuyInWidget.ui \
    PageSaleOutWidget.ui \
    PageSaleRecordWidget.ui \
    SaleItemWidget.ui \
    BigSpinBoxEdit.ui \
    PriceDialog.ui \
    t9keyboard/t9widget.ui

RESOURCES += \
    res.qrc

TRANSLATIONS += zh_CN.ts
