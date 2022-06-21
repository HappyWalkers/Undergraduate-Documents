/********************************************************************************
** Form generated from reading UI file 't9widget.ui'
**
** Created: Sun Nov 25 02:02:08 2018
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_T9WIDGET_H
#define UI_T9WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_T9Widget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *tipLabel;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *pyPgUp;
    QPushButton *pyBtn0;
    QPushButton *pyBtn1;
    QPushButton *pyBtn2;
    QPushButton *pyPgDn;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pgUpBtn;
    QPushButton *hzBtn0;
    QPushButton *hzBtn1;
    QPushButton *hzBtn2;
    QPushButton *hzBtn3;
    QPushButton *hzBtn4;
    QPushButton *pgDnBtn;
    QGridLayout *gridLayout;
    QPushButton *n1Btn;
    QPushButton *n4Btn;
    QPushButton *n7Btn;
    QPushButton *starBtn;
    QPushButton *n2Btn;
    QPushButton *n3Btn;
    QPushButton *methodBtn;
    QPushButton *n5Btn;
    QPushButton *n6Btn;
    QPushButton *backSpaceBtn;
    QPushButton *n8Btn;
    QPushButton *n9Btn;
    QPushButton *spaceBtn;
    QPushButton *n0Btn;
    QPushButton *jingBtn;
    QPushButton *enterBtn;

    void setupUi(QWidget *T9Widget)
    {
        if (T9Widget->objectName().isEmpty())
            T9Widget->setObjectName(QString::fromUtf8("T9Widget"));
        T9Widget->resize(176, 203);
        T9Widget->setAutoFillBackground(false);
        T9Widget->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);"));
        verticalLayout = new QVBoxLayout(T9Widget);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        tipLabel = new QLabel(T9Widget);
        tipLabel->setObjectName(QString::fromUtf8("tipLabel"));
        tipLabel->setMaximumSize(QSize(16777215, 16));

        horizontalLayout_3->addWidget(tipLabel);

        label = new QLabel(T9Widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        horizontalLayout_3->setStretch(0, 10);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pyPgUp = new QPushButton(T9Widget);
        pyPgUp->setObjectName(QString::fromUtf8("pyPgUp"));
        pyPgUp->setEnabled(false);
        pyPgUp->setMinimumSize(QSize(0, 16));
        pyPgUp->setMaximumSize(QSize(16, 32));
        pyPgUp->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pyPgUp);

        pyBtn0 = new QPushButton(T9Widget);
        pyBtn0->setObjectName(QString::fromUtf8("pyBtn0"));
        pyBtn0->setMinimumSize(QSize(0, 16));
        pyBtn0->setMaximumSize(QSize(80, 32));
        pyBtn0->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pyBtn0);

        pyBtn1 = new QPushButton(T9Widget);
        pyBtn1->setObjectName(QString::fromUtf8("pyBtn1"));
        pyBtn1->setMinimumSize(QSize(0, 16));
        pyBtn1->setMaximumSize(QSize(80, 32));
        pyBtn1->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pyBtn1);

        pyBtn2 = new QPushButton(T9Widget);
        pyBtn2->setObjectName(QString::fromUtf8("pyBtn2"));
        pyBtn2->setMinimumSize(QSize(0, 16));
        pyBtn2->setMaximumSize(QSize(80, 32));
        pyBtn2->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pyBtn2);

        pyPgDn = new QPushButton(T9Widget);
        pyPgDn->setObjectName(QString::fromUtf8("pyPgDn"));
        pyPgDn->setEnabled(false);
        pyPgDn->setMinimumSize(QSize(0, 16));
        pyPgDn->setMaximumSize(QSize(16, 32));
        pyPgDn->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pyPgDn);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pgUpBtn = new QPushButton(T9Widget);
        pgUpBtn->setObjectName(QString::fromUtf8("pgUpBtn"));
        pgUpBtn->setMinimumSize(QSize(23, 23));
        pgUpBtn->setMaximumSize(QSize(46, 46));
        pgUpBtn->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(pgUpBtn);

        hzBtn0 = new QPushButton(T9Widget);
        hzBtn0->setObjectName(QString::fromUtf8("hzBtn0"));
        hzBtn0->setMinimumSize(QSize(23, 23));
        hzBtn0->setMaximumSize(QSize(46, 46));
        hzBtn0->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(hzBtn0);

        hzBtn1 = new QPushButton(T9Widget);
        hzBtn1->setObjectName(QString::fromUtf8("hzBtn1"));
        hzBtn1->setMinimumSize(QSize(23, 23));
        hzBtn1->setMaximumSize(QSize(46, 46));
        hzBtn1->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(hzBtn1);

        hzBtn2 = new QPushButton(T9Widget);
        hzBtn2->setObjectName(QString::fromUtf8("hzBtn2"));
        hzBtn2->setMinimumSize(QSize(23, 23));
        hzBtn2->setMaximumSize(QSize(46, 46));
        hzBtn2->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(hzBtn2);

        hzBtn3 = new QPushButton(T9Widget);
        hzBtn3->setObjectName(QString::fromUtf8("hzBtn3"));
        hzBtn3->setMinimumSize(QSize(23, 23));
        hzBtn3->setMaximumSize(QSize(46, 46));
        hzBtn3->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(hzBtn3);

        hzBtn4 = new QPushButton(T9Widget);
        hzBtn4->setObjectName(QString::fromUtf8("hzBtn4"));
        hzBtn4->setMinimumSize(QSize(23, 23));
        hzBtn4->setMaximumSize(QSize(46, 46));
        hzBtn4->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(hzBtn4);

        pgDnBtn = new QPushButton(T9Widget);
        pgDnBtn->setObjectName(QString::fromUtf8("pgDnBtn"));
        pgDnBtn->setMinimumSize(QSize(23, 23));
        pgDnBtn->setMaximumSize(QSize(46, 46));
        pgDnBtn->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(pgDnBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        n1Btn = new QPushButton(T9Widget);
        n1Btn->setObjectName(QString::fromUtf8("n1Btn"));
        n1Btn->setMinimumSize(QSize(32, 32));
        n1Btn->setMaximumSize(QSize(64, 64));
        n1Btn->setFocusPolicy(Qt::NoFocus);
        n1Btn->setIconSize(QSize(29, 29));
        n1Btn->setFlat(false);

        gridLayout->addWidget(n1Btn, 0, 0, 1, 1);

        n4Btn = new QPushButton(T9Widget);
        n4Btn->setObjectName(QString::fromUtf8("n4Btn"));
        n4Btn->setMinimumSize(QSize(32, 32));
        n4Btn->setMaximumSize(QSize(64, 64));
        n4Btn->setFocusPolicy(Qt::NoFocus);
        n4Btn->setIconSize(QSize(29, 29));

        gridLayout->addWidget(n4Btn, 1, 0, 1, 1);

        n7Btn = new QPushButton(T9Widget);
        n7Btn->setObjectName(QString::fromUtf8("n7Btn"));
        n7Btn->setMinimumSize(QSize(32, 32));
        n7Btn->setMaximumSize(QSize(64, 64));
        n7Btn->setFocusPolicy(Qt::NoFocus);
        n7Btn->setIconSize(QSize(29, 29));

        gridLayout->addWidget(n7Btn, 2, 0, 1, 1);

        starBtn = new QPushButton(T9Widget);
        starBtn->setObjectName(QString::fromUtf8("starBtn"));
        starBtn->setMinimumSize(QSize(32, 32));
        starBtn->setMaximumSize(QSize(64, 64));
        starBtn->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(starBtn, 3, 0, 1, 1);

        n2Btn = new QPushButton(T9Widget);
        n2Btn->setObjectName(QString::fromUtf8("n2Btn"));
        n2Btn->setMinimumSize(QSize(32, 32));
        n2Btn->setMaximumSize(QSize(64, 64));
        n2Btn->setFocusPolicy(Qt::NoFocus);
        n2Btn->setIconSize(QSize(29, 29));

        gridLayout->addWidget(n2Btn, 0, 1, 1, 1);

        n3Btn = new QPushButton(T9Widget);
        n3Btn->setObjectName(QString::fromUtf8("n3Btn"));
        n3Btn->setMinimumSize(QSize(32, 32));
        n3Btn->setMaximumSize(QSize(64, 64));
        n3Btn->setFocusPolicy(Qt::NoFocus);
        n3Btn->setIconSize(QSize(29, 29));

        gridLayout->addWidget(n3Btn, 0, 2, 1, 1);

        methodBtn = new QPushButton(T9Widget);
        methodBtn->setObjectName(QString::fromUtf8("methodBtn"));
        methodBtn->setMinimumSize(QSize(65, 32));
        methodBtn->setMaximumSize(QSize(16777215, 64));
        methodBtn->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(methodBtn, 0, 3, 1, 1);

        n5Btn = new QPushButton(T9Widget);
        n5Btn->setObjectName(QString::fromUtf8("n5Btn"));
        n5Btn->setMinimumSize(QSize(32, 32));
        n5Btn->setMaximumSize(QSize(64, 64));
        n5Btn->setFocusPolicy(Qt::NoFocus);
        n5Btn->setIconSize(QSize(29, 29));

        gridLayout->addWidget(n5Btn, 1, 1, 1, 1);

        n6Btn = new QPushButton(T9Widget);
        n6Btn->setObjectName(QString::fromUtf8("n6Btn"));
        n6Btn->setMinimumSize(QSize(32, 32));
        n6Btn->setMaximumSize(QSize(64, 64));
        n6Btn->setFocusPolicy(Qt::NoFocus);
        n6Btn->setIconSize(QSize(29, 29));

        gridLayout->addWidget(n6Btn, 1, 2, 1, 1);

        backSpaceBtn = new QPushButton(T9Widget);
        backSpaceBtn->setObjectName(QString::fromUtf8("backSpaceBtn"));
        backSpaceBtn->setMinimumSize(QSize(65, 32));
        backSpaceBtn->setMaximumSize(QSize(16777215, 64));
        backSpaceBtn->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(backSpaceBtn, 1, 3, 1, 1);

        n8Btn = new QPushButton(T9Widget);
        n8Btn->setObjectName(QString::fromUtf8("n8Btn"));
        n8Btn->setMinimumSize(QSize(32, 32));
        n8Btn->setMaximumSize(QSize(64, 64));
        n8Btn->setFocusPolicy(Qt::NoFocus);
        n8Btn->setIconSize(QSize(29, 29));

        gridLayout->addWidget(n8Btn, 2, 1, 1, 1);

        n9Btn = new QPushButton(T9Widget);
        n9Btn->setObjectName(QString::fromUtf8("n9Btn"));
        n9Btn->setMinimumSize(QSize(32, 32));
        n9Btn->setMaximumSize(QSize(64, 64));
        n9Btn->setFocusPolicy(Qt::NoFocus);
        n9Btn->setIconSize(QSize(29, 29));

        gridLayout->addWidget(n9Btn, 2, 2, 1, 1);

        spaceBtn = new QPushButton(T9Widget);
        spaceBtn->setObjectName(QString::fromUtf8("spaceBtn"));
        spaceBtn->setMinimumSize(QSize(65, 32));
        spaceBtn->setMaximumSize(QSize(16777215, 64));
        spaceBtn->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(spaceBtn, 2, 3, 1, 1);

        n0Btn = new QPushButton(T9Widget);
        n0Btn->setObjectName(QString::fromUtf8("n0Btn"));
        n0Btn->setMinimumSize(QSize(32, 32));
        n0Btn->setMaximumSize(QSize(64, 64));
        n0Btn->setFocusPolicy(Qt::NoFocus);
        n0Btn->setIconSize(QSize(29, 29));

        gridLayout->addWidget(n0Btn, 3, 1, 1, 1);

        jingBtn = new QPushButton(T9Widget);
        jingBtn->setObjectName(QString::fromUtf8("jingBtn"));
        jingBtn->setMinimumSize(QSize(32, 32));
        jingBtn->setMaximumSize(QSize(64, 64));
        jingBtn->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(jingBtn, 3, 2, 1, 1);

        enterBtn = new QPushButton(T9Widget);
        enterBtn->setObjectName(QString::fromUtf8("enterBtn"));
        enterBtn->setMinimumSize(QSize(65, 32));
        enterBtn->setMaximumSize(QSize(16777215, 64));
        enterBtn->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(enterBtn, 3, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(T9Widget);

        QMetaObject::connectSlotsByName(T9Widget);
    } // setupUi

    void retranslateUi(QWidget *T9Widget)
    {
        T9Widget->setWindowTitle(QApplication::translate("T9Widget", "T9Widget", 0, QApplication::UnicodeUTF8));
        tipLabel->setText(QString());
        label->setText(QApplication::translate("T9Widget", "<DragToMove>", 0, QApplication::UnicodeUTF8));
        pyPgUp->setText(QApplication::translate("T9Widget", "<", 0, QApplication::UnicodeUTF8));
        pyBtn0->setText(QString());
        pyBtn1->setText(QString());
        pyBtn2->setText(QString());
        pyPgDn->setText(QApplication::translate("T9Widget", ">", 0, QApplication::UnicodeUTF8));
        pgUpBtn->setText(QApplication::translate("T9Widget", "\342\206\221", 0, QApplication::UnicodeUTF8));
        hzBtn0->setText(QString());
        hzBtn1->setText(QString());
        hzBtn2->setText(QString());
        hzBtn3->setText(QString());
        hzBtn4->setText(QString());
        pgDnBtn->setText(QApplication::translate("T9Widget", "\342\206\223", 0, QApplication::UnicodeUTF8));
        n1Btn->setText(QString());
        n4Btn->setText(QString());
        n7Btn->setText(QString());
        starBtn->setText(QApplication::translate("T9Widget", "<-", 0, QApplication::UnicodeUTF8));
        n2Btn->setText(QString());
        n3Btn->setText(QString());
        methodBtn->setText(QApplication::translate("T9Widget", "CHS", 0, QApplication::UnicodeUTF8));
        n5Btn->setText(QString());
        n6Btn->setText(QString());
        backSpaceBtn->setText(QApplication::translate("T9Widget", "Backspace", 0, QApplication::UnicodeUTF8));
        n8Btn->setText(QString());
        n9Btn->setText(QString());
        spaceBtn->setText(QApplication::translate("T9Widget", "Space", 0, QApplication::UnicodeUTF8));
        n0Btn->setText(QString());
        jingBtn->setText(QApplication::translate("T9Widget", "->", 0, QApplication::UnicodeUTF8));
        enterBtn->setText(QApplication::translate("T9Widget", "Enter", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class T9Widget: public Ui_T9Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_T9WIDGET_H
