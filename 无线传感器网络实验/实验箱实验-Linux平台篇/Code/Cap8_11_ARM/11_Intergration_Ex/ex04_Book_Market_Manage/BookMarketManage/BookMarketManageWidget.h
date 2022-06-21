#ifndef BOOKMARKETMANAGEWIDGET_H
#define BOOKMARKETMANAGEWIDGET_H

#include <QWidget>
#include <qextserialport.h>
#include <QTranslator>
#include <RLM100/RLM100Control.h>

namespace Ui {
    class BookMarketManageWidget;
}

class BookMarketManageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookMarketManageWidget(QWidget *parent = 0);
    ~BookMarketManageWidget();

private:
    void loadUartDev();

private:
    Ui::BookMarketManageWidget *ui;
    RLM100Control *rfid;
    QTranslator *trans;
    QString commPortName;

private slots:
    void onTimeout();
    void onEPCFound(const QByteArray &uii);

    void on_openCloseBtn_clicked(bool checked);
};

#endif // BOOKMARKETMANAGEWIDGET_H
