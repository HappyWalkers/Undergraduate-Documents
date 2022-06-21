#include "PageBorrowWidget.h"
#include "ui_PageBorrowWidget.h"
#include "DBControl.h"
#include <QMessageBox>

PageBorrowWidget::PageBorrowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageBorrowWidget)
{
    ui->setupUi(this);

    on_clearBtn_clicked();
}

PageBorrowWidget::~PageBorrowWidget()
{
    delete ui;
}

void PageBorrowWidget::onCardDetected(const QString &id)
{
    on_clearBtn_clicked();
    ui->bookIdEdit->setText(id);
    QString name = DBBook::findName(id);
    int status = DBBook::getStatus(id);
    // status = 1, 在架; status = 0, 借出
    if(status < 0)
    {
        ui->bookNameEdit->setText(tr("invalid book"));
    }
    else
    {
        ui->bookNameEdit->setText(name);
        ui->borrowBtn->setEnabled(status == 1);
    }
}

void PageBorrowWidget::on_borrowBtn_clicked()
{
    if(ui->bookIdEdit->text().isEmpty())
        return;
    if(ui->bookNameEdit->text().isEmpty())
        return;
    DBBook::borrow(ui->bookIdEdit->text());
    on_clearBtn_clicked();
    QMessageBox::information(this, tr("Infor"), tr("Book Borrowed"));
}

void PageBorrowWidget::on_clearBtn_clicked()
{
    ui->bookIdEdit->setText("");
    ui->bookNameEdit->setText("");
    ui->borrowBtn->setEnabled(false);
}
