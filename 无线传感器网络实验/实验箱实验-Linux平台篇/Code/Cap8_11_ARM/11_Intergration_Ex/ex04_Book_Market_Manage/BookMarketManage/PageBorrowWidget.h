#ifndef PAGEBORROWWIDGET_H
#define PAGEBORROWWIDGET_H

#include <QWidget>

namespace Ui {
    class PageBorrowWidget;
}

class PageBorrowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PageBorrowWidget(QWidget *parent = 0);
    ~PageBorrowWidget();

private:
    Ui::PageBorrowWidget *ui;

private slots:
    void on_clearBtn_clicked();
    void on_borrowBtn_clicked();

public slots:
    void onCardDetected(const QString &id);
};

#endif // PAGEBORROWWIDGET_H
