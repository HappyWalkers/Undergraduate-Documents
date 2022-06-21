/********************************************************************************
** Form generated from reading UI file 'ClockInWidget.ui'
**
** Created: Sun Nov 25 11:23:55 2018
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOCKINWIDGET_H
#define UI_CLOCKINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "rotatenumberlabel.h"

QT_BEGIN_NAMESPACE

class Ui_widget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLCDNumber *yearNumber;
    QLabel *label_2;
    QLCDNumber *monthNumber;
    QLabel *label_3;
    QLCDNumber *dayNumber;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    RotateNumberLabel *hourLabel;
    RotateNumberLabel *minuteLabel;
    QLCDNumber *secondNumber;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QFormLayout *formLayout;
    QLabel *label_4;
    QLineEdit *cardIdEdit;
    QLabel *label_5;
    QLineEdit *nameEdit;
    QPushButton *updateButton;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName(QString::fromUtf8("widget"));
        widget->resize(542, 284);
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        yearNumber = new QLCDNumber(widget);
        yearNumber->setObjectName(QString::fromUtf8("yearNumber"));
        yearNumber->setNumDigits(4);

        horizontalLayout->addWidget(yearNumber);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        monthNumber = new QLCDNumber(widget);
        monthNumber->setObjectName(QString::fromUtf8("monthNumber"));
        monthNumber->setNumDigits(2);

        horizontalLayout->addWidget(monthNumber);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        dayNumber = new QLCDNumber(widget);
        dayNumber->setObjectName(QString::fromUtf8("dayNumber"));
        dayNumber->setNumDigits(2);

        horizontalLayout->addWidget(dayNumber);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        hourLabel = new RotateNumberLabel(widget);
        hourLabel->setObjectName(QString::fromUtf8("hourLabel"));
        hourLabel->setMinimumSize(QSize(48, 45));

        horizontalLayout_2->addWidget(hourLabel);

        minuteLabel = new RotateNumberLabel(widget);
        minuteLabel->setObjectName(QString::fromUtf8("minuteLabel"));
        minuteLabel->setMinimumSize(QSize(48, 45));

        horizontalLayout_2->addWidget(minuteLabel);

        secondNumber = new QLCDNumber(widget);
        secondNumber->setObjectName(QString::fromUtf8("secondNumber"));
        secondNumber->setMaximumSize(QSize(16777215, 24));
        secondNumber->setNumDigits(2);

        horizontalLayout_2->addWidget(secondNumber);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_4);

        cardIdEdit = new QLineEdit(widget);
        cardIdEdit->setObjectName(QString::fromUtf8("cardIdEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cardIdEdit);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

        nameEdit = new QLineEdit(widget);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, nameEdit);


        horizontalLayout_3->addLayout(formLayout);

        updateButton = new QPushButton(widget);
        updateButton->setObjectName(QString::fromUtf8("updateButton"));

        horizontalLayout_3->addWidget(updateButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(widget);

        QMetaObject::connectSlotsByName(widget);
    } // setupUi

    void retranslateUi(QWidget *widget)
    {
        label->setText(QApplication::translate("widget", "Today is:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("widget", "-", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("widget", "-", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("widget", "Card ID:", 0, QApplication::UnicodeUTF8));
        cardIdEdit->setText(QApplication::translate("widget", "00ff7f9d", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("widget", "Name:", 0, QApplication::UnicodeUTF8));
        updateButton->setText(QApplication::translate("widget", " \346\233\264\346\226\260\346\225\260\346\215\256 ", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(widget);
    } // retranslateUi

};

namespace Ui {
    class widget: public Ui_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOCKINWIDGET_H
