#include "UserEditDialog.h"
#include "ui_UserEditDialog.h"

UserEditDialog::UserEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserEditDialog)
{
    ui->setupUi(this);

    ui->sftKeypad->changeRecver(ui->nameEdit);
    connect(ui->sftKeypad, SIGNAL(newString(QString)), this, SLOT(onSftKeypadNewString(QString)));
}

UserEditDialog::~UserEditDialog()
{
    delete ui;
}

QString UserEditDialog::cardId() const
{
    return ui->cardIdEdit->text();
}

QString UserEditDialog::name() const
{
    return ui->nameEdit->text();
}

void UserEditDialog::setCardId(const QString &id)
{
    ui->cardIdEdit->setText(id);
}

void UserEditDialog::setName(const QString &name)
{
    ui->nameEdit->setText(name);
}

void UserEditDialog::onSftKeypadNewString(const QString &str)
{
    ui->nameEdit->insert(str);
}
