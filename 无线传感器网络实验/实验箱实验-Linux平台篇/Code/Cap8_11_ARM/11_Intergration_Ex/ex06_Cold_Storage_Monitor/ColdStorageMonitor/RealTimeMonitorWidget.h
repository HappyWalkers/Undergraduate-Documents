#ifndef REALTIMEMONITORWIDGET_H
#define REALTIMEMONITORWIDGET_H

#include <QWidget>
#include "ColdStorageSetting.h"

namespace Ui {
    class RealTimeMonitorWidget;
}

class RealTimeMonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RealTimeMonitorWidget(QWidget *parent = 0);
    ~RealTimeMonitorWidget();

private:
    Ui::RealTimeMonitorWidget *ui;

public slots:
    void updataNodeInfo(const QString &ip, int endPoint, int funcID, float value);
    void onThresholdChanged(float min, float max);
};

#endif // REALTIMEMONITORWIDGET_H
