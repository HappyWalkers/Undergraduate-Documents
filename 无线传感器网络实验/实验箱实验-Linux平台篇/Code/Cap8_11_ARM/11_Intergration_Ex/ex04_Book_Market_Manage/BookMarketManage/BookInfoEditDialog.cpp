#include "BookInfoEditDialog.h"
#include "ui_BookInfoEditDialog.h"

BookInfoEditDialog::BookInfoEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookInfoEditDialog)
{
    ui->setupUi(this);

    ui->sftKeypad->changeRecver(ui->nameEdit);
//    ui->sftKeypad->setAllMethodEnabled(false);
//    ui->sftKeypad->setMethodEnabled(T9Widget::english, true);
//    ui->sftKeypad->setMethod(T9Widget::english);
    connect(ui->sftKeypad, SIGNAL(newString(QString)), this, SLOT(onSftKeypadNewString(QString)));
}

BookInfoEditDialog::~BookInfoEditDialog()
{
    delete ui;
}

QString BookInfoEditDialog::bookId() const
{
    return ui->cardIdEdit->text();
}

QString BookInfoEditDialog::name() const
{
    return ui->nameEdit->text();
}

void BookInfoEditDialog::setBookId(const QString &id)
{
    if(ui->cardIdEdit->isEnabled())
        ui->cardIdEdit->setText(id);
}

void BookInfoEditDialog::setName(const QString &name)
{
    ui->nameEdit->setText(name);
}

void BookInfoEditDialog::setIdEdiable(bool enable)
{
    ui->cardIdEdit->setEnabled(enable);
}

void BookInfoEditDialog::onSftKeypadNewString(const QString &str)
{
    ui->nameEdit->insert(str);
}
