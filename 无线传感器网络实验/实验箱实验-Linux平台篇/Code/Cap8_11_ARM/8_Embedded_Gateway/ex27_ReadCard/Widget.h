#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ChannelMan/RFIDChannelMan.h"
#include "IEEE14443/IEEE14443Control.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    // 用来处理寻卡失败
    void onRfidError(int cmdType, const QString &result);
    // 用来处理寻卡成功
    void onRfidFoundCard(const QByteArray &cardid);
    // 用来处理读卡成功
    void onRfidDataReaded(int block, const QByteArray &data);
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    IEEE14443Control *rfid;     // 定义一个13.56M读写器的操作类指针
};

#endif // WIDGET_H
