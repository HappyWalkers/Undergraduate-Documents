#ifndef USEREDITDIALOG_H
#define USEREDITDIALOG_H

#include <QDialog>
#include "t9keyboard/t9widget.h"

namespace Ui {
    class UserEditDialog;
}

class UserEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserEditDialog(QWidget *parent = 0);
    ~UserEditDialog();

    QString cardId() const;
    QString name() const;

public slots:
    void setCardId(const QString &id);
    void setName(const QString &name);

private:
    Ui::UserEditDialog *ui;
    T9Widget *sftKeypad;

private slots:
    void onSftKeypadNewString(const QString &str);
};

#endif // USEREDITDIALOG_H
