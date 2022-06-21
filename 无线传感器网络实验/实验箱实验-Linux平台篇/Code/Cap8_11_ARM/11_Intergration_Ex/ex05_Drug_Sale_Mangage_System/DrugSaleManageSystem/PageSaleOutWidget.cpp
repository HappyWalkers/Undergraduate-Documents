#include "PageSaleOutWidget.h"
#include "ui_PageSaleOutWidget.h"
#include "SaleItemWidget.h"
#include "DBControl.h"
#include <QDateTime>
#include <QMessageBox>

PageSaleOutWidget::PageSaleOutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageSaleOutWidget)
{
    ui->setupUi(this);
}

PageSaleOutWidget::~PageSaleOutWidget()
{
    delete ui;
}

void PageSaleOutWidget::updateAmount()
{
    float totAmount = 0.0;
    int i;
    for(i = ui->sailListLayout->count() - 1; i >= 0; i--)
    {
        SaleItemWidget *w = qobject_cast<SaleItemWidget *>(ui->sailListLayout->itemAt(i)->widget());
        if(w == NULL)
            continue;
        totAmount += w->drugPrice() * w->count();
    }
    ui->totalAmountEdit->setText(QString::number(totAmount));
}

void PageSaleOutWidget::onSaleItemCountChanged(int count)
{
    updateAmount();
}

void PageSaleOutWidget::onSaleItemDeleted()
{
    updateAmount();
}

void PageSaleOutWidget::onCardDetected(const QString &id)
{
    QString name = DBDrugInfo::findName(id);
    if(name.isEmpty())
    {
        QMessageBox::information(this, tr("Warning"), tr("No such drug!"));
        return;
    }
    for(int i = 0; i < ui->sailListLayout->count(); i++)
    {
        SaleItemWidget *item = qobject_cast<SaleItemWidget *>(ui->sailListLayout->itemAt(i)->widget());
        if(item == NULL)
            continue;
        if(item->id() == id)
            return;
    }
    float price = DBDrugInfo::findPrice(id);
    int count = DBDrugInfo::findCount(id);
    SaleItemWidget *item = new SaleItemWidget(id, name, price, 1, this);
    connect(item, SIGNAL(countChaned(int)), this, SLOT(onSaleItemCountChanged(int)));
    connect(item, SIGNAL(destroyed()), this, SLOT(onSaleItemDeleted()));
    item->setMaxCount(count);
    ui->sailListLayout->addWidget(item);
    updateAmount();
}

void PageSaleOutWidget::on_saleBtn_clicked()
{
    int i = ui->sailListLayout->count();
    for(i = i - 1; i >= 0; i--)
    {
        SaleItemWidget *item = qobject_cast<SaleItemWidget *>(ui->sailListLayout->itemAt(i)->widget());
        if(item == NULL)
            continue;
        DBDrugInfo::saleOut(item->id(), item->count());
        item->deleteLater();
    }
}
