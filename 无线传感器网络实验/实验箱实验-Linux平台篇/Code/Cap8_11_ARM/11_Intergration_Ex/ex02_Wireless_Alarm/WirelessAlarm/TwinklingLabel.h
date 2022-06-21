#ifndef TWINKLINGLABEL_H
#define TWINKLINGLABEL_H

#include <QLabel>
#include <QTimer>
#include <QPixmap>

class TwinklingLabel : public QLabel
{
    Q_OBJECT

public:
    explicit TwinklingLabel(QWidget *parent = 0);
    ~TwinklingLabel();

    bool isTwinkling(void) const;

public slots:
    void setPixmap(const QPixmap &pixMap);
    void startTwinkling(int freq = 1000);
    void stopTwinkling(void);

private:
    QTimer *timer;
    QPixmap lastPixmap;
    int flashFreq;
    bool isShowPic;

private slots:
    void onTimeout(void);
};

#endif // TWINKLINGLABEL_H
