#include "MyWid.h"

MyWid::MyWid() : QWidget(),
	m_CurCentigrade(0),
	m_CurFahrenheit(32)
{
    createScreen();
}

MyWid::~MyWid()
{
	if(m_QuitButton)
		delete m_QuitButton;
	if(m_Slider)
		delete m_Slider;
}

void MyWid::createScreen()
{
    m_QuitButton = new QPushButton("Quit", this);
    connect(m_QuitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

	m_Slider = new QSlider(Qt::Vertical);
    m_Slider->setRange(0, 100);
    m_Slider->setValue(0);
    m_Slider->setTickPosition(QSlider::TicksLeft);
    m_Centigrade = new QLabel(QString::number(m_CurCentigrade));
	connect(m_Slider, SIGNAL(valueChanged(int)), m_Centigrade, SLOT(setNum(int)));

	m_Dial = new QDial;
    m_Dial->setRange(32, 212);
    m_Dial->setValue(m_CurFahrenheit);
    m_Dial->setNotchesVisible(true);
	m_Fahrenheit = new QLCDNumber(3);
    m_Fahrenheit->setSegmentStyle(QLCDNumber::Filled);
    m_Fahrenheit->display(m_CurFahrenheit);
	connect(m_Dial, SIGNAL(valueChanged(int)), m_Fahrenheit, SLOT(display(int)));

	connect(m_Slider, SIGNAL(valueChanged(int)), this, SLOT(celToFah(int)));
	connect(m_Dial, SIGNAL(valueChanged(int)), this, SLOT(fahToCel(int)));

	QLabel *Label1 = new QLabel("Centigrade");
	QLabel *Label2 = new QLabel("Fahrenheit");

    QGridLayout *Layout = new QGridLayout;
    Layout->addWidget(m_QuitButton, 0, 0, 1, 3);
    Layout->addWidget(Label1, 1, 0, 1, 2);
    Layout->addWidget(Label2, 1, 2);
    Layout->addWidget(m_Centigrade, 2, 0, 2, 1);
    Layout->addWidget(m_Slider, 2, 1, 2, 1);
    Layout->addWidget(m_Fahrenheit, 2, 2);
    Layout->addWidget(m_Dial, 3, 2);
    this->setLayout(Layout);
    setWindowTitle("Temperature");
}

void MyWid::celToFah(int celNum)
{
    int fahNum = (celNum * 9 / 5) + 32;
    m_Dial->setValue(fahNum);
    m_Fahrenheit->display(fahNum);
    m_CurCentigrade = celNum;
    m_CurFahrenheit = fahNum;
}

void MyWid::fahToCel(int fahNum)
{
    int celNum = (fahNum - 32) * 5 / 9;
    m_Slider->setValue(celNum);
    m_Centigrade->setNum(celNum);
    m_CurCentigrade = celNum;
    m_CurFahrenheit = fahNum;
}
