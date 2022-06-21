#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ChannelMan/RFIDChannelMan.h"
#include "ID125K/ID125KControl.h"

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
    //用来接收卡号的槽函数
    void onNewCard(unsigned long decID, const QByteArray &byteID);
    void on_clearBtn_clicked();

private:
    Ui::Widget *ui;
    ID125KControl *rfid;    // 定义一个125K读卡器的操作类指针
};

#endif // WIDGET_H
