#include "RealTimeMonitorWidget.h"
#include "ui_RealTimeMonitorWidget.h"
#include <QDebug>

RealTimeMonitorWidget::RealTimeMonitorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RealTimeMonitorWidget)
{
    ui->setupUi(this);
    ui->currentTemp->setEditable(false);

    connect(ColdStorageSetting::Instance(), SIGNAL(thresholdChanged(float,float)), this, SLOT(onThresholdChanged(float,float)));
    onThresholdChanged(ColdStorageSetting::Instance()->minThreshold(), ColdStorageSetting::Instance()->maxThreshold());
}

RealTimeMonitorWidget::~RealTimeMonitorWidget()
{
    delete ui;
}

void RealTimeMonitorWidget::updataNodeInfo(const QString &ip, int endPoint, int funcID, float value)
{
    Q_UNUSED(ip);Q_UNUSED(endPoint);Q_UNUSED(funcID);
    ui->currentTemp->setValue(value);
    if((value > ColdStorageSetting::Instance()->maxThreshold())
        || (value < ColdStorageSetting::Instance()->minThreshold()))
    {
        ui->alertLabel->startAlert();
    }
    else if(ui->alertLabel->isAlerting())
        ui->alertLabel->stopAlert();
}

void RealTimeMonitorWidget::onThresholdChanged(float min, float max)
{
    ui->maxTemp->setText(QString::number(max));
    ui->minTemp->setText(QString::number(min));
}
