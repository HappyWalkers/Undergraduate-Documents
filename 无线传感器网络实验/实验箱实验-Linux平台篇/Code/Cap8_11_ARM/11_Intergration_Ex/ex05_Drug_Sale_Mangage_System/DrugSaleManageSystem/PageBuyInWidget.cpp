#include "PageBuyInWidget.h"
#include "ui_PageBuyInWidget.h"
#include "SaleItemWidget.h"
#include "PriceDialog.h"
#include "DBControl.h"

PageBuyInWidget::PageBuyInWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageBuyInWidget)
{
    ui->setupUi(this);
}

PageBuyInWidget::~PageBuyInWidget()
{
    delete ui;
}

void PageBuyInWidget::onCardDetected(const QString &id)
{
    static QString processingId;
    if(!processingId.isEmpty())
        return;
    processingId = id;
    QString name = DBDrugInfo::findName(id);
    float price = DBDrugInfo::findPrice(id);
    if(name.isEmpty())
    {
        PriceDialog dlg;
        if(dlg.exec() == QDialog::Rejected)
            return;
        name = dlg.name();
        price = dlg.price();
    }
    processingId.clear();
    SaleItemWidget *item = new SaleItemWidget(id, name, price, 1, this);
    item->setMaxCount(10000);
    ui->sailListLayout->addWidget(item);
}

void PageBuyInWidget::on_storageBtn_clicked()
{
    int i = ui->sailListLayout->count();
    for(i = i - 1; i >= 0; i--)
    {
        SaleItemWidget *item = qobject_cast<SaleItemWidget *>(ui->sailListLayout->itemAt(i)->widget());
        if(item == NULL)
            continue;
        DBDrugInfo::buyIn(item->id(), item->drugName(), item->drugPrice(), item->count());
        item->deleteLater();
    }
}
