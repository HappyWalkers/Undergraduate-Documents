#ifndef PAGEMANAGEWIDGET_H
#define PAGEMANAGEWIDGET_H

#include <QWidget>
#include "BookInfoEditDialog.h"

namespace Ui {
    class PageManageWidget;
}

class PageManageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PageManageWidget(QWidget *parent = 0);
    ~PageManageWidget();

private:
    Ui::PageManageWidget *ui;
    BookInfoEditDialog *bookInfoEditDlg;

public slots:
    void onCardDetected(const QString &id);

private slots:
    void on_refreshRecordBtn_clicked();
    void on_refreshBookBtn_clicked();
    void on_modifyBookBtn_clicked();
    void on_delBookBtn_clicked();
    void on_addBookBtn_clicked();
    void updateBookList();
    void updateRecordList();
};

#endif // PAGEMANAGEWIDGET_H
