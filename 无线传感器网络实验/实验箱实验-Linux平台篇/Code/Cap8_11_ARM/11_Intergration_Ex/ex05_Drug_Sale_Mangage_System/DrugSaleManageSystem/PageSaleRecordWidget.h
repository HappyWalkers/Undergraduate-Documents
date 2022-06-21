#ifndef PAGESALERECORDWIDGET_H
#define PAGESALERECORDWIDGET_H

#include <QWidget>

namespace Ui {
    class PageSaleRecordWidget;
}

class PageSaleRecordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PageSaleRecordWidget(QWidget *parent = 0);
    ~PageSaleRecordWidget();

private:
    Ui::PageSaleRecordWidget *ui;

private slots:
    void on_refreshRecordBtn_clicked();
    void on_refreshInventoryBtn_clicked();
};

#endif // PAGESALERECORDWIDGET_H
