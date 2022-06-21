#ifndef HISTORYMONITORWIDGET_H
#define HISTORYMONITORWIDGET_H

#include <QWidget>
#include "ColdStorageSetting.h"

namespace Ui {
    class HistoryMonitorWidget;
}

class HistoryMonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryMonitorWidget(QWidget *parent = 0);
    ~HistoryMonitorWidget();

private:
    Ui::HistoryMonitorWidget *ui;
    float lastValue;

public slots:
    void updataNodeInfo(const QString &ip, int endPoint, int funcID, float value);

private slots:
    void onThresholdChanged(float min, float max);
};

#endif // HISTORYMONITORWIDGET_H
