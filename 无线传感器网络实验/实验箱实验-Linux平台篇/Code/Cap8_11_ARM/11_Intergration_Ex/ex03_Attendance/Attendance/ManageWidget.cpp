#include "ManageWidget.h"
#include "ui_ManageWidget.h"
#include <QTreeWidgetItem>
#include <QMessageBox>

ManageWidget::ManageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageWidget),
    usrEditDlg(new UserEditDialog)
{
    ui->setupUi(this);

    updateUserTable();
}

ManageWidget::~ManageWidget()
{
    delete ui;
}

void ManageWidget::onCardReaded(const QString &cardid)
{
    usrEditDlg->setCardId(cardid);
}

void ManageWidget::updateUserTable()
{
    ui->userTable->clear();
    DBCard c;
    if(c.first())
    {
        QTreeWidgetItem *item;
        do {
            item = new QTreeWidgetItem(ui->userTable);
            item->setText(0, QString::number(c.id()));
            item->setText(1, c.cardid());
            item->setText(2, c.name());
        } while(c.next());
    }
}

void ManageWidget::updateLogTable()
{
    ui->logTable->clear();
    DBLog l;
    if(l.first())
    {
        QTreeWidgetItem *item;
        do {
            item = new QTreeWidgetItem(ui->logTable);
            item->setText(0, QString::number(l.id()));
            item->setText(1, l.date().toString("yyyy-MM-dd hh:mm:ss"));
            item->setText(2, l.cardid());
        } while(l.next());
    }
}

void ManageWidget::on_addBtn_clicked()
{
    if(!usrEditDlg->isHidden())
        return;
    usrEditDlg->setCardId("");
    usrEditDlg->setName("");
    if(usrEditDlg->exec() == QDialog::Rejected)
        return;
    if(usrEditDlg->cardId().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Card ID can't be empty!"));
        return;
    }
    if(usrEditDlg->name().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("User Name can't be empty!"));
        return;
    }
    DBCard::addCard(usrEditDlg->cardId(), usrEditDlg->name());
    updateUserTable();
}

void ManageWidget::on_delBtn_clicked()
{
    QList<QTreeWidgetItem *> selItems = ui->userTable->selectedItems();
    while(selItems.count())
    {
        QTreeWidgetItem *item = selItems.first();
        DBCard::delCard(item->text(1));
        delete item;
        selItems.removeFirst();
    }
}

void ManageWidget::on_modifyBtn_clicked()
{
    QList<QTreeWidgetItem *> selItems = ui->userTable->selectedItems();
    if(selItems.count())
    {
        QTreeWidgetItem *item = selItems.first();
        if(!usrEditDlg->isHidden())
            return;
        usrEditDlg->setCardId(item->text(1));
        usrEditDlg->setName(item->text(2));
        if(usrEditDlg->exec() == QDialog::Rejected)
            return;
        DBCard::updateName(usrEditDlg->cardId(), usrEditDlg->name());
        updateUserTable();
    }
}

void ManageWidget::on_refreshBtn_clicked()
{
    updateLogTable();
}
