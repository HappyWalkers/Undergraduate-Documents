#include "datagridlabel.h"
#include <QPainter>
#include <QDebug>

DataGridLabel::DataGridLabel(QWidget *parent) :
    QLabel(parent),
    _gridColor(128, 128, 128),
    _labelColor(255, 255, 0),
    _fgColor(255, 0, 0),
    _bgColor(0, 128, 128),
    _textLabelFormat("%d")
{
    _gridSize = 15;
    _timeGrid = 5;
    _min = 0;
    _max = 100;
    _textLabelWidth = _textLabelHeight = 0;
    _cursorTip = true;
    setMouseTracking(_cursorTip);
}

DataGridLabel::~DataGridLabel()
{
    _data.remove();
}

void DataGridLabel::setTmpFile(QString name){
    qDebug()<<"the filename is"<<name;
    _data.setFileName(name);
   qDebug()<< _data.open(QIODevice::ReadWrite | QIODevice::Truncate);
}
void DataGridLabel::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter pt(this);
    QRect rc = this->geometry();
#if 1
    if((_textLabelWidth == 0) || (_textLabelHeight == 0))
    {
        #define max(a, b)       ((a) > (b) ? (a) : (b))
        QRect txtrc1, txtrc2;
        char txt1[1024];
        char txt2[1024];
        sprintf(txt1, _textLabelFormat.toAscii().constData(), _max);
        sprintf(txt2, _textLabelFormat.toAscii().constData(), _min);
        pt.drawText(0, 0, rc.width(), rc.height(), Qt::AlignRight, txt1, &txtrc1);
        pt.drawText(0, 0, rc.width(), rc.height(), Qt::AlignRight, txt2, &txtrc2);
        _textLabelWidth = max(txtrc1.width(), txtrc2.width());
        _textLabelHeight = max(txtrc1.height(), txtrc2.height());
    }
#endif
    pt.fillRect(QRect(QPoint(0, 0), rc.size()), _bgColor);
    if(rc.width() < _textLabelWidth + _timeGrid)
        return;
    if(this->_gridSize > 0)
    {
        pt.setPen(_gridColor);
        for(int i = _textLabelWidth; i < rc.width(); i += _gridSize)
            pt.drawLine(i, 0, i, rc.height());
        for(int j = rc.height() - 1; j >= 0; j -= _gridSize)
        {
            pt.drawLine(_textLabelWidth, j, rc.width(), j);
            pt.setPen(_labelColor);
            char tmp[1024];
            sprintf(tmp, _textLabelFormat.toAscii().constData(), (rc.height() - 1 - j) * (_max - _min) / rc.height() + _min);
//            QString l = QString("%1").arg((rc.height() - 1 - j) * (_max - _min) / rc.height() + _min);
            pt.drawText(0, j - _textLabelHeight, _textLabelWidth, _textLabelHeight, Qt::AlignRight, tmp);
            pt.setPen(_gridColor);
        }
    }
    pt.setPen(_fgColor);
    int seek_pos = 0;
    int drawWidth = rc.width() - _textLabelWidth;
    if((_data.size() / sizeof(int)) > (drawWidth / _timeGrid))
        seek_pos = ((_data.size() / sizeof(int)) - (drawWidth / _timeGrid)) * sizeof(int);
    _data.seek(seek_pos);
    int pos = _textLabelWidth;
    QPoint lastPnt;
    while(!_data.atEnd())
    {
        int d;
        _data.read((char *)&d, sizeof(d));
        if(d == _min - 1)
        {
            pos += _timeGrid;
            continue;
        }
        int h = (d - _min) * rc.height() / (_max - _min);
        QPoint pnt(pos, rc.height() - h);
        pt.drawPoint(pnt);
        if(pos > _textLabelWidth)
            pt.drawLine(lastPnt, pnt);
        lastPnt = pnt;
        if(_cursorTip)
        {
            if((_lastMousePnt.x() >= pos) && (_lastMousePnt.x() < (pos + _timeGrid)))
            {
                QString txt = QString("%1").arg(d);
                pt.setPen(_labelColor);
                pt.drawText(_lastMousePnt, txt);
                pt.setPen(_fgColor);
            }
        }
        pos += _timeGrid;
    }
}

void DataGridLabel::mouseMoveEvent(QMouseEvent *ev)
{
    _lastMousePnt = ev->pos();
    update();
}

void DataGridLabel::addData(int data)
{
    qint64 pos = _data.pos();
    _data.seek(_data.size());
    _data.write((char *)&data, sizeof(data));
    _data.seek(pos);
    update();
}

void DataGridLabel::skip(int step)
{
    qint64 pos = _data.pos();
    _data.seek(_data.size());
    int d = _min - 1;
    while(step--)
    {
        _data.write((char *)&d, sizeof(d));
    }
    _data.seek(pos);
    update();
}

void DataGridLabel::clear()
{
    _data.remove();
    _data.open(QIODevice::ReadWrite | QIODevice::Truncate);
    update();
}

void DataGridLabel::setRange(int min, int max)
{
    if(min < max)
    {
        _min = min;
        _max = max;
    }
    else
    {
        _min = max;
        _max = min;
    }
    _textLabelWidth = _textLabelHeight = 0;
}
