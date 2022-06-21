#include "ClockInWidget.h"
#include "ui_ClockInWidget.h"
#include <QDebug>

ClockInWidget::ClockInWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
    updateDateTime();

    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    timer->start();
}

ClockInWidget::~ClockInWidget()
{
    delete timer;
    delete ui;
}

void ClockInWidget::updateTime()
{
    QDateTime d = QDateTime::currentDateTime();
    ui->secondNumber->display(d.time().second());
    if(d.time().second() == 0)
    {
        ui->minuteLabel->motionToNumber(d.time().minute());
        if(d.time().minute() == 0)
        {
            ui->hourLabel->motionToNumber(d.time().hour());
            if(d.time().hour() == 0)
            {
                ui->dayNumber->display(d.date().day());
                if(d.date().day() == 1)
                {
                    ui->monthNumber->display(d.date().month());
                    if(d.date().month() == 1)
                    {
                        ui->yearNumber->display(d.date().year());
                    }
                }
            }
        }
    }
}

void ClockInWidget::updateDateTime()
{
    QDateTime d = QDateTime::currentDateTime();
    ui->yearNumber->display(d.date().year());
    ui->monthNumber->display(d.date().month());
    ui->dayNumber->display(d.date().day());
    ui->hourLabel->motionToNumber(d.time().hour());
    ui->minuteLabel->motionToNumber(d.time().minute());
    ui->secondNumber->display(d.time().second());
}

void ClockInWidget::onCardReaded(const QString &cardid)
{
    QString name = DBCard::findName(cardid);

    qDebug()<<"[onCardReaded] find cardid:"<<cardid<<"; name:"<<name;
    ui->cardIdEdit->setText(cardid);
    ui->nameEdit->setText(name.isEmpty() ? tr("No such person!") : name);

    qDebug()<<"[onCardReaded] addLog cardid:"<<cardid<<"; name:"<<name;
    DBLog::addLog(cardid);
}

void ClockInWidget::on_updateButton_clicked()
{
    QString card = ui->cardIdEdit->text();
    qDebug()<<"====[udpate] get cardid:"<<card;
    onCardReaded(card);
}
