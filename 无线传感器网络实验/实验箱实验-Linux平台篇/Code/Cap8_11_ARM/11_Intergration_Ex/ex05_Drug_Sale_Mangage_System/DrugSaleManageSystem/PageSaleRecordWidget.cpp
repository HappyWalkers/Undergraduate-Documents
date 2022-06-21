#include "PageSaleRecordWidget.h"
#include "ui_PageSaleRecordWidget.h"
#include "DBControl.h"
#include <QTreeWidgetItem>

PageSaleRecordWidget::PageSaleRecordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageSaleRecordWidget)
{
    ui->setupUi(this);
}

PageSaleRecordWidget::~PageSaleRecordWidget()
{
    delete ui;
}

void PageSaleRecordWidget::on_refreshInventoryBtn_clicked()
{
    ui->drugInventoryList->clear();
    DBDrugInfo d;
    if(d.first())
    {
        do {
            QTreeWidgetItem *item = new QTreeWidgetItem(ui->drugInventoryList);
            item->setText(0, d.cardid());
            item->setText(1, d.name());
            item->setText(2, QString::number(d.price()));
            item->setText(3, QString::number(d.count()));
        } while(d.next());
    }
}

void PageSaleRecordWidget::on_refreshRecordBtn_clicked()
{
    ui->recordList->clear();
    DBRecord r;
    if(r.first())
    {
        do {
            QTreeWidgetItem *item = new QTreeWidgetItem(ui->recordList);
            item->setText(0, QString::number(r.id()));
            item->setText(1, r.name());
            item->setText(2, QString::number(r.price()));
            item->setText(3, QString::number(r.count()));
            item->setText(4, r.type() ? tr("BuyIn") : tr("SaleOut"));
        } while(r.next());
    }
}
