#ifndef ALERTLABEL_H
#define ALERTLABEL_H

#include <QLabel>
#include <QTimer>

class AlertLabel : public QLabel
{
    Q_OBJECT

public:
    explicit AlertLabel(QWidget *parent = 0);
    ~AlertLabel();

    bool isAlerting(void) const;

public slots:
    void startAlert(int freq = 1);
    void stopAlert(void);

private:
    QTimer *timer;
    int flashFreq;
    bool isShowPic;

private slots:
    void onTimeout(void);
};

#endif // ALERTLABEL_H
