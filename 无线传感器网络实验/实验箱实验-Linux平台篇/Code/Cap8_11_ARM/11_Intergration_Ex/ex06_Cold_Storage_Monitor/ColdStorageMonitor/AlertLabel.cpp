#include "AlertLabel.h"

AlertLabel::AlertLabel(QWidget *parent) :
    QLabel(parent),
    flashFreq(1),
    isShowPic(false)
{
    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

AlertLabel::~AlertLabel()
{
}

void AlertLabel::onTimeout()
{
    isShowPic = !isShowPic;
    if(isShowPic)
        this->setPixmap(QPixmap(":/pic/alert.png"));
    else
        this->setPixmap(QPixmap());
}

bool AlertLabel::isAlerting() const
{
    return timer->isActive();
}

void AlertLabel::startAlert(int freq)
{
    flashFreq = freq;
    timer->setInterval(freq * 500);
    timer->start();
}

void AlertLabel::stopAlert()
{
    timer->stop();
    isShowPic = false;
    this->setPixmap(QPixmap());
}
