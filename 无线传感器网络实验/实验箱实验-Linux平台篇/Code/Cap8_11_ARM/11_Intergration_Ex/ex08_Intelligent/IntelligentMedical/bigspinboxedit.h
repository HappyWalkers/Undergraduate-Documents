#ifndef BIGSPINBOXEDIT_H
#define BIGSPINBOXEDIT_H

#include <QWidget>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>

namespace Ui {
    class BigSpinBoxEdit;
}

class AddSubButton : public QPushButton
{
    Q_OBJECT

private:
    int _i;
    int _n;

private slots:
    void onClicked() {
        emit clicked(this->_i, this->_n);
    }

signals:
    void clicked(int idx, int neg);

public:
    explicit AddSubButton(QWidget *parent = 0)
        : QPushButton(parent)
    {
        connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
    }

    ~AddSubButton() {}

    int index() const           { return _i; }
    int neg() const             { return _n; }
public slots:
    void setIndex(int i)        { this->_i = i; }
    void setNeg(int neg)        { this->_n = neg; }
};

class BigSpinBoxEdit : public QWidget
{
    Q_OBJECT

public:
    explicit BigSpinBoxEdit(QWidget *parent = 0);
    ~BigSpinBoxEdit();

    float value() const;

public slots:
    void setValue(float value);
    void setEditable(bool editable = true);

private:
    Ui::BigSpinBoxEdit *ui;
    bool floatMode;
    int numDigit;
    int numFloat;
    float currentValue;
    bool isNeg;

    // 用于显示符号位
    QLabel *negLabel;
    // 用于显示所有的数字
    QLCDNumber *numContainer;
    // 用于显示每一个数字的加和减
    AddSubButton *numOpBtn;
    // 当打开小数模式时用于显示小数点
    QLabel *pntLabel;

private slots:
    void createUI(void);
    void updateUI(bool reCreate = true);
    void destroyUI(void);
    void onNumberOpBtnClicked(int idx, int neg);
};

#endif // BIGSPINBOXEDIT_H
