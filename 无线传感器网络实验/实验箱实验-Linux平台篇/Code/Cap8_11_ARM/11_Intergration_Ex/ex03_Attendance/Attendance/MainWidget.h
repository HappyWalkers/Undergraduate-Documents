#ifndef MAINWIDGETINWIDGET_H
#define MAINWIDGETINWIDGET_H

#include <QWidget>
#include "DBControl.h"
#include "ChannelMan/RFIDChannelMan.h"
#include "ID125K/ID125KControl.h"

namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    //用来接收卡号的槽函数
    void onNewCard(unsigned long decID, const QByteArray &byteID);

private:
    Ui::MainWidget *ui;
    ID125KControl *rfid;    // 定义一个125K读卡器的操作类指针
};

#endif // MAINWIDGETINWIDGET_H
