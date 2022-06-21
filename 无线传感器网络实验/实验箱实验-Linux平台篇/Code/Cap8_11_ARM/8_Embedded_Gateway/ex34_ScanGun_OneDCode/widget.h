#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ChannelMan/RFIDChannelMan.h"
#include "ScanGun/ScanGunControl.h"

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
    // 用于接收扫描到的条形码
    void onScanResult(const QByteArray &result);
    void on_clearBtn_clicked();

private:
    Ui::Widget *ui;
    ScanGunControl *scanGun;     // 定义一个扫描枪的操作类指针
};

#endif // WIDGET_H
