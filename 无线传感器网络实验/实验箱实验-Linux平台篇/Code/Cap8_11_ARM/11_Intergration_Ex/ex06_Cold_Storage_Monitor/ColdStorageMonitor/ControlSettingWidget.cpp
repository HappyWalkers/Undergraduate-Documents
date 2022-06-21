#include "ControlSettingWidget.h"
#include "ui_ControlSettingWidget.h"

ControlSettingWidget::ControlSettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlSettingWidget)
{
    ui->setupUi(this);

    on_resetBtn_clicked();
}

ControlSettingWidget::~ControlSettingWidget()
{
    delete ui;
}

void ControlSettingWidget::updataNodeInfo(const QString &ip, int endPoint, int funcID, float value)
{
    Q_UNUSED(ip);Q_UNUSED(endPoint);Q_UNUSED(funcID);Q_UNUSED(value);
}

void ControlSettingWidget::on_resetBtn_clicked()
{
    ColdStorageSetting *inst = ColdStorageSetting::Instance();
    if(inst == NULL)
        return;

    ui->minTempValue->setValue(inst->minThreshold());
    ui->maxTempValue->setValue(inst->maxThreshold());
}

void ControlSettingWidget::on_applyBtn_clicked()
{
    ColdStorageSetting *inst = ColdStorageSetting::Instance();
    if(inst == NULL)
        return;
    inst->changeThreshold(ui->minTempValue->value(), ui->maxTempValue->value());
}
