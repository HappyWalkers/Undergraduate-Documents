#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 选择900M读写器
    RFIDChannelMan::setChannel(RFIDChannelMan::ChannelUHF900M);
    // 创建900M读写器操作类对象
    rfid = new RLM100Control(this);
    // 启动读写器
    rfid->start(RFIDChannelMan::getRfidPort());
    // 停止读写器的循环操作，避免产生影响
    rfid->stopOperation();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_singleScanBtn_clicked()
{
    QByteArray uii;
    if(!rfid->singleScan(uii))
        ui->statusLabel->setText(tr("Failed to start single scan"));
    else
    {
        // 将标签号添加到文本框中显示
        ui->epcLogText->append(uii.toHex());
        // 遍历comboBox查询在列表中是否已经有这个标签
        for(int i = 0; i < ui->comboBox->count(); i++)
        {
            if(uii.toHex() == ui->comboBox->currentText())
            {
                // 如果已经存在这个标签,则选中它
                ui->comboBox->setCurrentIndex(i);
                return ;
            }
        }
        // 如果这个是一个新的标签，则添加到列表中并选中它
        ui->comboBox->addItems(QStringList(uii.toHex()));
        ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);
    }
}

void Widget::on_readCardBtn_clicked()
{
    QByteArray data;
    // 如果标签列表为空则退出
    if(ui->comboBox->count() == 0)
    {
        ui->statusLabel->setText(tr("EPC must not be empty"));
        return;
    }
    // 获取界面上用户选择的标签号、区域、地址、长度等信息
    QString uii = ui->comboBox->currentText();
    RLM100Control::Sections section =
            RLM100Control::Sections(ui->sectionList->currentIndex());
    int addr = ui->addrspinBox->text().toUInt();
    int len = ui->lenspinBox->value();
    // 读取指定标签
    if(!rfid->readCard(data, QByteArray::fromHex(uii.toLatin1()),
                       section, addr, len))
        ui->statusLabel->setText(tr("Read failed!"));
    else
    {
        ui->statusLabel->setText(tr("Read OK!"));
        ui->dataEdit->setText(data.toHex());
    }
}

void Widget::on_writeCardBtn_clicked()
{
    // 获取界面上用户选择的标签号、区域、地址、长度等信息
    QString uii = ui->comboBox->currentText();
    RLM100Control::Sections section =
            RLM100Control::Sections(ui->sectionList->currentIndex());
    int addr = ui->addrspinBox->text().toUInt();
    int len = ui->lenspinBox->value();
    // 获取界面上用户输入的数据
    QByteArray data = QByteArray::fromHex(ui->dataEdit->text().toLatin1());
    // 判断输入的数据长度是否符合所需长度
    if(data.size() != 2 * len)
    {
        ui->statusLabel->setText(tr("Data Length error"));
        return;
    }
    if(!rfid->writeCard(data, QByteArray::fromHex(uii.toLatin1()),
                        section, addr))
    {
        ui->statusLabel->setText(tr("Failed to write to card"));
        return;
    }
    ui->statusLabel->setText(tr("Write %1 word to card OK")
                             .arg(ui->lenspinBox->text().toUInt()));
}

void Widget::on_clearResult_clicked()
{
    ui->epcLogText->clear();
}
