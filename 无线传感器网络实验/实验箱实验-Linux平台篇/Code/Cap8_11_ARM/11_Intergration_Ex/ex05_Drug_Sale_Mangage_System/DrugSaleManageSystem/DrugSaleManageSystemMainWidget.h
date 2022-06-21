#ifndef DRUGSALEMANAGESYSTEMMAINWIDGET_H
#define DRUGSALEMANAGESYSTEMMAINWIDGET_H

#include <QWidget>
#include <QTranslator>
#include <QByteArray>
#include <RLM100/RLM100Control.h>

namespace Ui {
    class DrugSaleManageSystemMainWidget;
}

class DrugSaleManageSystemMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrugSaleManageSystemMainWidget(QWidget *parent = 0);
    ~DrugSaleManageSystemMainWidget();

private:
    void loadUartDev();

private:
    Ui::DrugSaleManageSystemMainWidget *ui;
    RLM100Control *rfid;
    QTranslator *trans;
    QString commPortName;

private slots:
    void onTimeout();
    void onEPCFound(const QByteArray &uii);

    void on_openCloseBtn_clicked(bool checked);
};

#endif // DRUGSALEMANAGESYSTEMMAINWIDGET_H
