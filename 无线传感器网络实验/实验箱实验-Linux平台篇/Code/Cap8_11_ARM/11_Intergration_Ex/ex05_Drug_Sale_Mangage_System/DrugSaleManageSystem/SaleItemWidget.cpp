#include "SaleItemWidget.h"
#include "ui_SaleItemWidget.h"

SaleItemWidget::SaleItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaleItemWidget)
{
    ui->setupUi(this);
}

SaleItemWidget::SaleItemWidget(const QString &id, const QString &drugName, float price, int count, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::SaleItemWidget)
{
    ui->setupUi(this);

    ui->idLabel->setText(id);
    ui->nameEdit->setText(drugName);
    ui->priceEdit->setText(QString::number(price));
    ui->countEdit->setValue(count);

    connect(ui->countEdit, SIGNAL(valueChanged(int)), this, SIGNAL(countChaned(int)));
}

SaleItemWidget::~SaleItemWidget()
{
    delete ui;
}

void SaleItemWidget::on_delBtn_clicked()
{
    this->deleteLater();
}

QString SaleItemWidget::id() const
{
    return ui->idLabel->text();
}

QString SaleItemWidget::drugName() const
{
    return ui->nameEdit->text();
}

float SaleItemWidget::drugPrice() const
{
    return ui->priceEdit->text().toFloat();
}

int SaleItemWidget::count() const
{
    return ui->countEdit->value();
}

int SaleItemWidget::maxCount() const
{
    return ui->countEdit->maximum();
}

void SaleItemWidget::setID(const QString &id)
{
    ui->idLabel->setText(id);
}

void SaleItemWidget::setDrugName(const QString &name)
{
    ui->nameEdit->setText(name);
}

void SaleItemWidget::setDrugPrice(float price)
{
    ui->priceEdit->setText(QString::number(price));
}

void SaleItemWidget::setCount(int count)
{
    ui->countEdit->setValue(count);
}

void SaleItemWidget::setMaxCount(int maxCount)
{
    ui->countEdit->setMaximum(maxCount);
}
