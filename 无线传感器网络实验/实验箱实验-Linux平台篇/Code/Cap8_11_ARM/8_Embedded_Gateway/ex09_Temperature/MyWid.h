#ifndef MY_WID_H
#define MY_WID_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QDial>
#include <QLCDNumber>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QCoreApplication>

class MyWid : public QWidget
{
	Q_OBJECT

public:
    MyWid();
    ~MyWid();

private slots:
	void celToFah(int celNum);
	void fahToCel(int celNum);

private:
    void createScreen();
    QPushButton* m_QuitButton;
    QSlider* m_Slider;
    QLabel* m_Centigrade;
    QDial* m_Dial;
    QLCDNumber* m_Fahrenheit;

    int m_CurCentigrade;
    int m_CurFahrenheit;

};

#endif //MY_WID_H
