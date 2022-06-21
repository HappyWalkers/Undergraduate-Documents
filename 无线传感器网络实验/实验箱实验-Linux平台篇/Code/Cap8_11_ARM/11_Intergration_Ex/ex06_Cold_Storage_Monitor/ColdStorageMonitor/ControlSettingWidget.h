#ifndef CONTROLSETTINGWIDGET_H
#define CONTROLSETTINGWIDGET_H

#include <QWidget>
#include "ColdStorageSetting.h"

namespace Ui {
    class ControlSettingWidget;
}

class ControlSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControlSettingWidget(QWidget *parent = 0);
    ~ControlSettingWidget();

private:
    Ui::ControlSettingWidget *ui;

public slots:
    void updataNodeInfo(const QString &ip, int endPoint, int funcID, float value);

private slots:
    void on_applyBtn_clicked();
    void on_resetBtn_clicked();
};

#endif // CONTROLSETTINGWIDGET_H
