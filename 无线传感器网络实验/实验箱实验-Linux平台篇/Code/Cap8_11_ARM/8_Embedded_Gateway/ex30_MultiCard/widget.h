#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ChannelMan/RFIDChannelMan.h"
#include "UHF900M/RLM100Control.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    RLM100Control *rfid;        // 定义一个900M读写器的操作类指针

private slots:
    void onEPCFound(const QByteArray &uii);

    void on_multiLoopScanBtn_clicked();
    void on_stopBtn_clicked();
    void on_clearResult_clicked();
};

#endif // WIDGET_H
