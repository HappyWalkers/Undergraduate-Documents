#ifndef BOOKINFOEDITDIALOG_H
#define BOOKINFOEDITDIALOG_H

#include <QDialog>
#include "t9keyboard/t9widget.h"

namespace Ui {
    class BookInfoEditDialog;
}

class BookInfoEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookInfoEditDialog(QWidget *parent = 0);
    ~BookInfoEditDialog();

    QString bookId() const;
    QString name() const;

public slots:
    void setBookId(const QString &id);
    void setName(const QString &name);
    void setIdEdiable(bool enable);

private:
    Ui::BookInfoEditDialog *ui;
    T9Widget *sftKeypad;

private slots:
    void onSftKeypadNewString(const QString &str);
};

#endif // BOOKINFODITDIALOG_H
