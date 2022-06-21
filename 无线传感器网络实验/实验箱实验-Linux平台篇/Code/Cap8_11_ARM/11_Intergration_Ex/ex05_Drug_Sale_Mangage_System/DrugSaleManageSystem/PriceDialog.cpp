#include "PriceDialog.h"
#include "ui_PriceDialog.h"

PriceDialog::PriceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PriceDialog)
{
    ui->setupUi(this);

    ui->sftKeypad->changeRecver(ui->nameEdit);
//    ui->sftKeypad->setAllMethodEnabled(false);
//    ui->sftKeypad->setMethodEnabled(T9Widget::english, true);
//    ui->sftKeypad->setMethod(T9Widget::english);
    connect(ui->sftKeypad, SIGNAL(newString(QString)), this, SLOT(onSftKeypadNewString(QString)));
}

PriceDialog::~PriceDialog()
{
    delete ui;
}

void PriceDialog::onSftKeypadNewString(const QString &str)
{
    ui->nameEdit->insert(str);
}

float PriceDialog::price() const
{
    return ui->priceWidget->value();
}

QString PriceDialog::name() const
{
    return ui->nameEdit->text();
}

void PriceDialog::setPrice(float p)
{
    ui->priceWidget->setValue(p);
}

void PriceDialog::setName(const QString &name)
{
    ui->nameEdit->setText(name);
}
