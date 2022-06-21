#include "BigSpinBoxEdit.h"
#include "ui_BigSpinBoxEdit.h"
#include <math.h>
#include <QDebug>

BigSpinBoxEdit::BigSpinBoxEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BigSpinBoxEdit),
    floatMode(true),
    numDigit(2),
    numFloat(2),
    currentValue(0.0),
    negLabel(NULL), numContainer(NULL), numOpBtn(NULL), pntLabel(NULL)
{
    ui->setupUi(this);
    updateUI();
}

BigSpinBoxEdit::~BigSpinBoxEdit()
{
    destroyUI();
    delete ui;
}

void BigSpinBoxEdit::createUI()
{
    destroyUI();
    if(!floatMode)
        numFloat = 0;
    numOpBtn = new AddSubButton[(numDigit + numFloat + 1) * 2];
    int i;
    for(i = 0; i < numDigit + 1 + numFloat; i++)
    {
        numOpBtn[2 * i + 0].setMaximumSize(30, 20);
        numOpBtn[2 * i + 0].setMinimumSize(30, 20);
        numOpBtn[2 * i + 0].setIndex(i - 1);
        numOpBtn[2 * i + 0].setNeg(1);
        numOpBtn[2 * i + 0].setText("+");
        connect(numOpBtn + 2 * i + 0, SIGNAL(clicked(int,int)), this, SLOT(onNumberOpBtnClicked(int,int)));
        numOpBtn[2 * i + 1].setMaximumSize(30, 20);
        numOpBtn[2 * i + 1].setMinimumSize(30, 20);
        numOpBtn[2 * i + 1].setIndex(i - 1);
        numOpBtn[2 * i + 1].setNeg(-1);
        numOpBtn[2 * i + 1].setText("-");
        connect(numOpBtn + 2 * i + 1, SIGNAL(clicked(int,int)), this, SLOT(onNumberOpBtnClicked(int,int)));
        if(i >= numDigit + 1)
        {
            ui->mainLayout->addWidget(numOpBtn + 2 * i + 0, 0, i + floatMode);
            ui->mainLayout->addWidget(numOpBtn + 2 * i + 1, 2, i + floatMode);
        }
        else
        {
            ui->mainLayout->addWidget(numOpBtn + 2 * i + 0, 0, i);
            ui->mainLayout->addWidget(numOpBtn + 2 * i + 1, 2, i);
        }
    }

    negLabel = new QLabel(this);
    negLabel->setMaximumSize(30, 50);
    negLabel->setMinimumSize(30, 50);
    negLabel->setScaledContents(true);
    negLabel->setPixmap(QPixmap(":/pic/plus.png"));
    ui->mainLayout->addWidget(negLabel, 1, 0);

    numContainer = new QLCDNumber[numDigit + numFloat];
    for(i = 0; i < numDigit + numFloat; i++)
    {
        numContainer[i].setMaximumSize(30, 50);
        numContainer[i].setMinimumSize(30, 50);
        numContainer[i].setNumDigits(1);
        numContainer[i].setDecMode();
        if(i >= numDigit)
            ui->mainLayout->addWidget(numContainer + i, 1, i + 1 + floatMode);
        else
            ui->mainLayout->addWidget(numContainer + i, 1, i + 1);
    }
    if(floatMode)
    {
        pntLabel = new QLabel;
        pntLabel->setMaximumSize(30, 50);
        pntLabel->setMinimumSize(30, 50);
//        pntLabel->setScaledContents(true);
        pntLabel->setPixmap(QPixmap(":/pic/point.png"));
        ui->mainLayout->addWidget(pntLabel, 1, numDigit + 1);
    }
}

void BigSpinBoxEdit::updateUI(bool reCreate)
{
    if(reCreate)
        createUI();
    if((negLabel == NULL) || (numContainer == NULL))
        createUI();
    if(currentValue >= 0.0)
    {
        negLabel->setPixmap(QPixmap(":/pic/plus.png"));
        isNeg = false;
    }
    else
    {
        negLabel->setPixmap(QPixmap(":/pic/neg.png"));
        isNeg = true;
    }
    float v = fabs(currentValue);
    float power = 1;
    int i;
    for(i = numDigit - 1; i >= 0; i--)
    {
        numContainer[i].display(int(v / power) % 10);
        power *= 10;
    }
    power = 10;
    for(i = numDigit; i < numDigit + numFloat; i++)
    {
        numContainer[i].display(int(v * power) % 10);
        power *= 10;
    }
}

void BigSpinBoxEdit::destroyUI()
{
    if(negLabel)
    {
        ui->mainLayout->removeWidget(negLabel);
        delete negLabel;
        negLabel = NULL;
    }
    if(numContainer)
    {
        int i;
        for(i = 0; i < numDigit + numFloat; i++)
            ui->mainLayout->removeWidget(negLabel + i);
        delete []numContainer;
        numContainer = NULL;
    }
    if(numOpBtn)
    {
        int i = (numDigit + numFloat + 1) * 2;
        for(i = i - 1; i >= 0; i--)
            ui->mainLayout->removeWidget(numOpBtn + i);
        delete []numOpBtn;
        numOpBtn = NULL;
    }
    if(pntLabel)
    {
        ui->mainLayout->removeWidget(pntLabel);
        delete pntLabel;
        pntLabel = NULL;
    }
}

void BigSpinBoxEdit::onNumberOpBtnClicked(int idx, int neg)
{
    if(idx < 0)
    {
        if(neg > 0)
        {
            negLabel->setPixmap(QPixmap(":/pic/plus.png"));
            isNeg = false;
        }
        else
        {
            negLabel->setPixmap(QPixmap(":/pic/neg.png"));
            isNeg = true;
        }
    }
    else
    {
        if(neg > 0)
        {
            if(numContainer[idx].value() < 9)
                numContainer[idx].display(numContainer[idx].value() + 1);
        }
        else
        {
            if(numContainer[idx].value() > 0)
                numContainer[idx].display(numContainer[idx].value() - 1);
        }
    }
    qDebug()<<"currentValue = "<<value();
}

float BigSpinBoxEdit::value() const
{
    float ret = 0;
    int i;
    float power = pow(10, numDigit);
    for(i = 0; i < numDigit; i++)
    {
        power /= 10;
        ret += (numContainer[i].value() * power);
    }
    power = 1;
    for(i = 0; i < numFloat; i++)
    {
        power *= 0.1;
        ret += (numContainer[i + numDigit].value() * power);
    }
    if(isNeg)
        ret *= -1;
    return ret;
}

void BigSpinBoxEdit::setValue(float value)
{
    currentValue = value;
    updateUI(false);
}

void BigSpinBoxEdit::setEditable(bool editable)
{
    if(numOpBtn == NULL)
        return;
    int i = (numDigit + numFloat + 1) * 2;
    while(i-- > 0)
    {
        numOpBtn[i].setEnabled(editable);
    }
}
