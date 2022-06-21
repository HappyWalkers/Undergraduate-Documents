#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ChannelMan/RFIDChannelMan.h"
#include "MicroWave/MicroWaveControl.h"

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
    // 用于接收扫描到的标签信息
    void onRfidNewCard(int readerAddr, int cardType, bool lowPower,
                       unsigned long decID, const QByteArray &byteID);
    void on_clearBtn_clicked();

private:
    Ui::Widget *ui;
    MicroWaveControl *rfid;     // 定义一个2.4G读卡器的操作类指针
};

#endif // WIDGET_H
