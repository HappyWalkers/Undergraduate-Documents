#ifndef INTELLIGENTMEDICALWIDGET_H
#define INTELLIGENTMEDICALWIDGET_H

#include <QWidget>

namespace Ui {
    class IntelligentMedicalWidget;
}

class IntelligentMedicalWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IntelligentMedicalWidget(QWidget *parent = 0);
    ~IntelligentMedicalWidget();

signals:
    void gotSaftyData(bool stat);
    void gotGasData(bool stat);

    void gotExecuteBData(char execute);
    void gotRainData(bool stat);

    void gotIllumData(unsigned short illum);
    void gotHallData(bool stat);
private:
    Ui::IntelligentMedicalWidget *ui;
    bool irSmsFlag;
    bool gasSmsFlag;
    bool rainSmsFlag;
    bool hallSmsFlag;

    bool openWindFlag;
    bool openLampFlag;

    void *wsnUser;
    void *ipv6User;
    void *bt4User;

    float _minThreshold, _maxThreshold;
private slots:
    void on_pushButton_clicked();
    void onSoftKeyClicked();
    void onGotSaftyData(bool stat);
    void onGotGasData(bool stat);

    void onGotExecuteBData(char execute);
    void onGotRainData(bool stat);

    void onGotIllumData(unsigned short illum);
    void onGotHallData(bool stat);


protected:
    static void cbNewData(IntelligentMedicalWidget *This, unsigned short nwkAddr, int endpoint, int funcCode, int funcID, char *data, int len);

    static void ipv6cbNewData(IntelligentMedicalWidget *This, unsigned char *nwkAddr, int endpoint, int funcCode, int funcID, char *data, int len);
    static void bt4cbNewData(IntelligentMedicalWidget *This, unsigned char *nwkAddr, int endpoint, int funcCode, int funcID, char *data, int len);


};

#endif // WIRELESSSECURITYWIDGET_H
