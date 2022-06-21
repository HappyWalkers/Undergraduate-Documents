/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created: Thu Aug 23 15:49:41 2018
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include "MjpgWidget.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *mainlabel;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *ipText;
    QLabel *label_3;
    QLineEdit *portText;
    QPushButton *startstopButton;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    MjpgWidget *widget;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 480);
        QFont font;
        font.setFamily(QString::fromUtf8("Monospace"));
        Widget->setFont(font);
        mainlabel = new QLabel(Widget);
        mainlabel->setObjectName(QString::fromUtf8("mainlabel"));
        mainlabel->setEnabled(true);
        mainlabel->setGeometry(QRect(0, 30, 801, 71));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Ubuntu"));
        font1.setPointSize(48);
        mainlabel->setFont(font1);
        mainlabel->setAlignment(Qt::AlignCenter);
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(460, 110, 301, 341));
        QFont font2;
        font2.setPointSize(26);
        groupBox->setFont(font2);
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 40, 311, 165));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        ipText = new QLineEdit(gridLayoutWidget);
        ipText->setObjectName(QString::fromUtf8("ipText"));
        QFont font3;
        font3.setPointSize(24);
        ipText->setFont(font3);

        gridLayout->addWidget(ipText, 0, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font3);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        portText = new QLineEdit(gridLayoutWidget);
        portText->setObjectName(QString::fromUtf8("portText"));
        portText->setFont(font3);

        gridLayout->addWidget(portText, 1, 1, 1, 1);

        startstopButton = new QPushButton(gridLayoutWidget);
        startstopButton->setObjectName(QString::fromUtf8("startstopButton"));
        startstopButton->setFont(font3);

        gridLayout->addWidget(startstopButton, 2, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font3);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(40, 110, 411, 341));
        groupBox_2->setFont(font2);
        widget = new MjpgWidget(groupBox_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 40, 400, 300));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        mainlabel->setText(QApplication::translate("Widget", "\350\247\206\351\242\221\345\233\276\345\203\217\351\207\207\351\233\206\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Widget", "\350\256\276\347\275\256\345\214\272", 0, QApplication::UnicodeUTF8));
        ipText->setText(QApplication::translate("Widget", "192.168.1.80", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget", "PORT:", 0, QApplication::UnicodeUTF8));
        portText->setText(QApplication::translate("Widget", "80", 0, QApplication::UnicodeUTF8));
        startstopButton->setText(QApplication::translate("Widget", "start", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "IP:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Widget", "\345\233\276\345\203\217\345\214\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
