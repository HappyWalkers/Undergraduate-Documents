#ifndef WIRELESSALARMWIDGET_H
#define WIRELESSALARMWIDGET_H

#include <QWidget>

namespace Ui {
    class WirelessAlarmWidget;
}

class WirelessAlarmWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WirelessAlarmWidget(QWidget *parent = 0);
    ~WirelessAlarmWidget();

signals:
    void gotSaftyData(bool stat);
    void gotGasData(bool stat);

private:
    Ui::WirelessAlarmWidget *ui;
    bool irSmsFlag;
    bool gasSmsFlag;
    void *wsnUser;

private slots:
    void on_pushButton_clicked();
    void onSoftKeyClicked();
    void onGotSaftyData(bool stat);
    void onGotGasData(bool stat);

protected:
    static void cbNewData(WirelessAlarmWidget *This, unsigned short nwkAddr, int endpoint, int funcCode, int funcID, char *data, int len);
};

#endif // WIRELESSALARMWIDGET_H
