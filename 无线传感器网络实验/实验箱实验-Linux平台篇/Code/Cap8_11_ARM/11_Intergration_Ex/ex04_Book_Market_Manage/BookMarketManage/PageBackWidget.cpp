#include "PageBackWidget.h"
#include "ui_PageBackWidget.h"
#include "DBControl.h"
#include <QMessageBox>

PageBackWidget::PageBackWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageBackWidget)
{
    ui->setupUi(this);

    on_clearBtn_clicked();
}

PageBackWidget::~PageBackWidget()
{
    delete ui;
}

void PageBackWidget::onCardDetected(const QString &id)
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
        ui->backBtn->setEnabled(status == 0);
        if(status == 0)
        {
            DBRecord c;
            QDateTime d = QDateTime::currentDateTime();
            if(c.first())
            {
                do {
                    if(c.bookid() == id)
                    {
                        d = c.date();
                        break;
                    }
                } while(c.next());
            }
            ui->borrowTimeEdit->setDateTime(d);
        }
    }
}

void PageBackWidget::on_backBtn_clicked()
{
    if(ui->bookIdEdit->text().isEmpty())
        return;
    if(ui->bookNameEdit->text().isEmpty())
        return;
    DBBook::back(ui->bookIdEdit->text());
    on_clearBtn_clicked();
    QMessageBox::information(this, tr("Infor"), tr("Book Backed"));
}

void PageBackWidget::on_clearBtn_clicked()
{
    ui->bookIdEdit->clear();
    ui->bookNameEdit->clear();
    ui->borrowTimeEdit->clear();
    ui->backBtn->setEnabled(false);
}
