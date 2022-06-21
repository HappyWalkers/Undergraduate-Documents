#ifndef DATAGRIDLABEL_H
#define DATAGRIDLABEL_H

#include <QLabel>
#include <QFile>
#include <QTime>
#include <QMouseEvent>
#include <QResizeEvent>

class DataGridLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DataGridLabel(QWidget *parent = 0);
    virtual ~DataGridLabel();

    int min() const         { return _min; }
    int max() const         { return _max; }

signals:

public slots:
    void addData(int data);
    void skip(int step);
    void clear();
    void setRange(int min, int max);
    void setGridSize(int gridSize)          {
        if(gridSize > 0)
            _gridSize = gridSize;
        update();
    }
    void setTimeGridSize(int timeGridSize)  {
        if(timeGridSize > 0)
            _timeGrid = timeGridSize;
        update();
    }
    void setLabelFormat(const char *fmt)    {
        _textLabelFormat = fmt;
    }
    void setTmpFile(QString name);

protected:
    void paintEvent(QPaintEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private:
    bool _cursorTip;
    int _gridSize;
    int _timeGrid;
    int _min, _max;
    QColor _gridColor;
    QColor _labelColor;
    QColor _fgColor;
    QColor _bgColor;
    QString _tmpFile;
    QFile _data;
    QPoint _lastMousePnt;
    int _textLabelWidth, _textLabelHeight;
    QString _textLabelFormat;
};

static inline QString GetRandomName(int Len, QString KeyStr = "qwertyuiopasdfghjklzxcvbnm1234567890_")
{
    QString RetStr;
    int MaxLen = KeyStr.length();
    static bool Rand_Init = false;
    if(!Rand_Init)
    {
        srand(QTime::currentTime().msec());
        Rand_Init = true;
    }
    while(Len > 0)
    {
//      int pos = rand() % MaxLen;
        RetStr += KeyStr.at(rand() % MaxLen);
        Len--;
    }
    return RetStr;
}

#endif // DATAGRIDLABEL_H
