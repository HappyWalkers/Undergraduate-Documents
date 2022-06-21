#ifndef PAGEBACKWIDGET_H
#define PAGEBACKWIDGET_H

#include <QWidget>

namespace Ui {
    class PageBackWidget;
}

class PageBackWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PageBackWidget(QWidget *parent = 0);
    ~PageBackWidget();

private:
    Ui::PageBackWidget *ui;

public slots:
    void onCardDetected(const QString &id);

private slots:
    void on_backBtn_clicked();
    void on_clearBtn_clicked();
};

#endif // PAGEBACKWIDGET_H
