#include "HistoryMonitorWidget.h"
#include "ui_HistoryMonitorWidget.h"

HistoryMonitorWidget::HistoryMonitorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryMonitorWidget),
    lastValue(0.0)
{
    ui->setupUi(this);
    ui->label->setTmpFile("temp");

    connect(ColdStorageSetting::Instance(), SIGNAL(thresholdChanged(float,float)), this, SLOT(onThresholdChanged(float,float)));
    onThresholdChanged(ColdStorageSetting::Instance()->minThreshold(), ColdStorageSetting::Instance()->maxThreshold());
}

HistoryMonitorWidget::~HistoryMonitorWidget()
{
    delete ui;
}

void HistoryMonitorWidget::updataNodeInfo(const QString &ip, int endPoint, int funcID, float value)
{
    Q_UNUSED(ip);Q_UNUSED(endPoint);Q_UNUSED(funcID);
    ui->label->addData(value);
}

void HistoryMonitorWidget::onThresholdChanged(float min, float max)
{
    ui->label->setRange(min, max);
}
