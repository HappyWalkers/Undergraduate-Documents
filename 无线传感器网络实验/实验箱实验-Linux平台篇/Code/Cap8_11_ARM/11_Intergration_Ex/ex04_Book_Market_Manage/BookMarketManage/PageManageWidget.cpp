#include "PageManageWidget.h"
#include "ui_PageManageWidget.h"
#include "DBControl.h"
#include <QMessageBox>
#include <QDebug>

PageManageWidget::PageManageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageManageWidget),
    bookInfoEditDlg(new BookInfoEditDialog)
{
    ui->setupUi(this);

    updateBookList();
    updateRecordList();
}

PageManageWidget::~PageManageWidget()
{
    delete ui;
}

void PageManageWidget::updateBookList()
{
    ui->bookTable->clear();
    DBBook b;
    if(b.first())
    {
        QTreeWidgetItem *item;
        do {
            item = new QTreeWidgetItem(ui->bookTable);
            item->setText(0, QString::number(b.id()));
            item->setText(1, b.bookId());
            item->setText(2, b.name());
            item->setText(3, b.status() ? tr("InShop") : tr("Borrowed"));
        } while(b.next());
    }
}

void PageManageWidget::updateRecordList()
{
    ui->logTable->clear();
    DBRecord c;
    if(c.first())
    {
        QTreeWidgetItem *item;
        do {
            item = new QTreeWidgetItem(ui->logTable);
            item->setText(0, QString::number(c.id()));
            item->setText(1, c.date().toString("yyyy-MM-dd hh:mm:ss"));
            item->setText(2, c.bookid());
            item->setText(3, DBBook::findName(c.bookid()));
            qDebug()<<"record type = "<<c.type();
            item->setText(4, c.type() ? tr("Borrow"): tr("Back"));
        } while(c.next());
    }
}

void PageManageWidget::onCardDetected(const QString &id)
{
    bookInfoEditDlg->setBookId(id);
}

void PageManageWidget::on_addBookBtn_clicked()
{
    if(!bookInfoEditDlg->isHidden())
        return;
    bookInfoEditDlg->setIdEdiable(true);
    bookInfoEditDlg->setBookId("");
    bookInfoEditDlg->setName("");
    if(bookInfoEditDlg->exec() == QDialog::Rejected)
        return;
    if(bookInfoEditDlg->bookId().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Book ID can't be empty!"));
        return;
    }
    if(bookInfoEditDlg->name().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Book Title can't be empty!"));
        return;
    }
    DBBook::addBook(bookInfoEditDlg->bookId(), bookInfoEditDlg->name());
    updateBookList();
}

void PageManageWidget::on_delBookBtn_clicked()
{
    QList<QTreeWidgetItem *> selItems = ui->bookTable->selectedItems();
    while(selItems.count())
    {
        QTreeWidgetItem *item = selItems.first();
        DBBook::delBook(item->text(1));
        delete item;
        selItems.removeFirst();
    }
}

void PageManageWidget::on_modifyBookBtn_clicked()
{
    if(!bookInfoEditDlg->isHidden())
        return;
    QList<QTreeWidgetItem *> selItems = ui->bookTable->selectedItems();
    if(selItems.count())
    {
        QTreeWidgetItem *item = selItems.first();
        bookInfoEditDlg->setBookId(item->text(1));
        bookInfoEditDlg->setName(item->text(2));
        bookInfoEditDlg->setIdEdiable(false);
        if(bookInfoEditDlg->exec() == QDialog::Rejected)
            return;
        DBBook::updateBook(bookInfoEditDlg->bookId(), bookInfoEditDlg->name());
        updateBookList();
    }
}

void PageManageWidget::on_refreshBookBtn_clicked()
{
    updateBookList();
}

void PageManageWidget::on_refreshRecordBtn_clicked()
{
    updateRecordList();
}
