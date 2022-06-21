/********************************************************************************
** Form generated from reading UI file 'MainWidget.ui'
**
** Created: Sun Nov 25 12:03:45 2018
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "ClockInWidget.h"
#include "ManageWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *spacer;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *reconnectBtn;
    QTabWidget *tabWidget;
    ClockInWidget *clockInPage;
    ManageWidget *manPage;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(879, 512);
        verticalLayout = new QVBoxLayout(MainWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(MainWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/pic/title.png")));

        horizontalLayout->addWidget(label);

        spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacer);

        label_2 = new QLabel(MainWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(MainWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        reconnectBtn = new QPushButton(MainWidget);
        reconnectBtn->setObjectName(QString::fromUtf8("reconnectBtn"));

        horizontalLayout->addWidget(reconnectBtn);


        verticalLayout->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(MainWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        clockInPage = new ClockInWidget();
        clockInPage->setObjectName(QString::fromUtf8("clockInPage"));
        tabWidget->addTab(clockInPage, QString());
        manPage = new ManageWidget();
        manPage->setObjectName(QString::fromUtf8("manPage"));
        tabWidget->addTab(manPage, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(MainWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "MainWidget", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWidget", "DB Server:", 0, QApplication::UnicodeUTF8));
        reconnectBtn->setText(QApplication::translate("MainWidget", "Reconnect", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(clockInPage), QApplication::translate("MainWidget", "Clock in", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(manPage), QApplication::translate("MainWidget", "Manage", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
