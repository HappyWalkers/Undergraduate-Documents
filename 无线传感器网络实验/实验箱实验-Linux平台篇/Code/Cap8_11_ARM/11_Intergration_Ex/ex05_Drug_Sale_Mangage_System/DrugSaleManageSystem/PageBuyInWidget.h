#ifndef PAGEBUYINWIDGET_H
#define PAGEBUYINWIDGET_H

#include <QWidget>

namespace Ui {
    class PageBuyInWidget;
}

class PageBuyInWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PageBuyInWidget(QWidget *parent = 0);
    ~PageBuyInWidget();

public slots:
    void onCardDetected(const QString &id);

private:
    Ui::PageBuyInWidget *ui;

private slots:
    void on_storageBtn_clicked();
};

#endif // PAGEBUYINWIDGET_H
