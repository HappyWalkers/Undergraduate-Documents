#ifndef PAGESALEOUTWIDGET_H
#define PAGESALEOUTWIDGET_H

#include <QWidget>

namespace Ui {
    class PageSaleOutWidget;
}

class PageSaleOutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PageSaleOutWidget(QWidget *parent = 0);
    ~PageSaleOutWidget();

public slots:
    void onCardDetected(const QString &id);

private:
    Ui::PageSaleOutWidget *ui;

private slots:
    void on_saleBtn_clicked();
    void onSaleItemCountChanged(int count);
    void onSaleItemDeleted();
    void updateAmount();
};

#endif // PAGESALEOUTWIDGET_H
