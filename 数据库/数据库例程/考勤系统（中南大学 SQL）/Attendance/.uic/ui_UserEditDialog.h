/********************************************************************************
** Form generated from reading UI file 'UserEditDialog.ui'
**
** Created: Sun Nov 25 02:02:08 2018
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USEREDITDIALOG_H
#define UI_USEREDITDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include "t9keyboard/t9widget.h"

QT_BEGIN_NAMESPACE

class Ui_UserEditDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *cardIdEdit;
    QLabel *label_2;
    QLineEdit *nameEdit;
    T9Widget *sftKeypad;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *UserEditDialog)
    {
        if (UserEditDialog->objectName().isEmpty())
            UserEditDialog->setObjectName(QString::fromUtf8("UserEditDialog"));
        verticalLayout = new QVBoxLayout(UserEditDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(UserEditDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cardIdEdit = new QLineEdit(UserEditDialog);
        cardIdEdit->setObjectName(QString::fromUtf8("cardIdEdit"));

        gridLayout->addWidget(cardIdEdit, 0, 1, 1, 1);

        label_2 = new QLabel(UserEditDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        nameEdit = new QLineEdit(UserEditDialog);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        gridLayout->addWidget(nameEdit, 1, 1, 1, 1);

        sftKeypad = new T9Widget(UserEditDialog);
        sftKeypad->setObjectName(QString::fromUtf8("sftKeypad"));

        gridLayout->addWidget(sftKeypad, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        buttonBox = new QDialogButtonBox(UserEditDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(UserEditDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), UserEditDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), UserEditDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(UserEditDialog);
    } // setupUi

    void retranslateUi(QDialog *UserEditDialog)
    {
        UserEditDialog->setWindowTitle(QApplication::translate("UserEditDialog", "User Edit Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UserEditDialog", "Card ID:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("UserEditDialog", "Name:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UserEditDialog: public Ui_UserEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USEREDITDIALOG_H
