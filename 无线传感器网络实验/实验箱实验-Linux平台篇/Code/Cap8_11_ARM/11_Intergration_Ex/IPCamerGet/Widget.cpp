#include "Widget.h"
#include "ui_Widget.h"
#include <QTextCodec>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //添加背景图片
    QImage _image;
    _image.load(":src/kuang.png");
    this->setAutoFillBackground(true);   // 这个属性一定要设置
    QPalette pal(palette());
    pal.setBrush(QPalette::Window,
    QBrush(_image.scaled(size(),
           Qt::IgnoreAspectRatio,
           Qt::SmoothTransformation)));
    this->setPalette(pal);

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::blue);
    ui->mainlabel->setPalette(pe);
    ui->mainlabel->setText(tr("视频图像采集系统"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startstopButton_clicked()
{
    if(ui->widget->isRunning())
    {
        ui->widget->stop();
        ui->startstopButton->setText(tr("Start"));
    }
    else
    {
        QString str1=ui->ipText->text();
        QString str2=ui->portText->text();
        quint16 port=str2.toInt();
        qDebug()<<"==11==ip and port:"<<str1<<str2;
        ui->widget->setAuthentication("admin", "admin");//用户名，密码
        ui->widget->start(str1,                     //IP地址
                          port,                     //端口号
                    "/tmpfs/auto.jpg?");           //"/snapshot.cgi"); //ipcamera:
                    //usb camera :"/?action=snapshot");
        ui->startstopButton->setText(tr("Stop"));
    }
}
