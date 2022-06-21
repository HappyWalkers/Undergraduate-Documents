#ifndef SALEITEMWIDGET_H
#define SALEITEMWIDGET_H

#include <QWidget>

namespace Ui {
    class SaleItemWidget;
}

class SaleItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SaleItemWidget(QWidget *parent = 0);
    SaleItemWidget(const QString &id, const QString &drugName, float price, int count, QWidget *parent = 0);
    ~SaleItemWidget();

    QString id() const;
    QString drugName() const;
    float drugPrice() const;
    int count() const;
    int maxCount() const;

signals:
    void countChaned(int count);

public slots:
    void setID(const QString &id);
    void setDrugName(const QString &name);
    void setDrugPrice(float price);
    void setCount(int count);
    void setMaxCount(int maxCount);
    void remove() {this->deleteLater();}

private:
    Ui::SaleItemWidget *ui;

private slots:
    void on_delBtn_clicked();
};

#endif // SALEITEMWIDGET_H
