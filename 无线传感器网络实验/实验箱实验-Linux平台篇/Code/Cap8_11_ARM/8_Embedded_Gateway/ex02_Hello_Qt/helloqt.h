#ifndef HELLOQT_H
#define HELLOQT_H

#include <QWidget>

namespace Ui {
    class HelloQt;
}

class HelloQt : public QWidget
{
    Q_OBJECT

public:
    explicit HelloQt(QWidget *parent = 0);
    ~HelloQt();

private:
    Ui::HelloQt *ui;
};

#endif // HELLOQT_H
