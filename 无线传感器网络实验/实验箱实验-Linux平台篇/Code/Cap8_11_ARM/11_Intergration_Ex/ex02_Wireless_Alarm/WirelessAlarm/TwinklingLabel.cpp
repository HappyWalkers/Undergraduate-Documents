#include "TwinklingLabel.h"

TwinklingLabel::TwinklingLabel(QWidget *parent) :
    QLabel(parent),
    flashFreq(1),
    isShowPic(false)
{
    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

TwinklingLabel::~TwinklingLabel()
{
}

void TwinklingLabel::onTimeout()
{
    isShowPic = !isShowPic;
    if(isShowPic)
        QLabel::setPixmap(lastPixmap);
    else
        QLabel::setPixmap(QPixmap());
}

bool TwinklingLabel::isTwinkling() const
{
    return timer->isActive();
}

void TwinklingLabel::setPixmap(const QPixmap &pixMap)
{
    lastPixmap = pixMap;
//    QLabel::setPixmap(pixMap);
}

void TwinklingLabel::startTwinkling(int freq)
{
    flashFreq = freq;
    timer->setInterval(freq / 2);
    timer->start();
}

void TwinklingLabel::stopTwinkling()
{
    timer->stop();
    isShowPic = false;
    QLabel::setPixmap(QPixmap());
}
