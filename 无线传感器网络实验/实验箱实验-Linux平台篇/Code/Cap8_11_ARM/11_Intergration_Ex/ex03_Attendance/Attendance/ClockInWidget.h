#ifndef CLOCKINWIDGET_H
#define CLOCKINWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include "DBControl.h"

namespace Ui {
    class widget;
}

class ClockInWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClockInWidget(QWidget *parent = 0);
    ~ClockInWidget();

public slots:
    void onCardReaded(const QString &cardid);

private:
    Ui::widget *ui;
    QTimer *timer;

private slots:
    void updateDateTime();
    void updateTime();
};

#endif // CLOCKINWIDGET_H
