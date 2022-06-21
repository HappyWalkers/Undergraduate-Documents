#include "RLM100Package.h"
#include <QDebug>

RLM100Package::RLM100Package(const QByteArray &strippedRawPkg)
{
    load(strippedRawPkg);
    _cmdPackage = false;
}

RLM100Package::RLM100Package(CommandType cmd, const QByteArray &data)
{
    create(cmd, data);
    _cmdPackage = true;
}

bool RLM100Package::load(const QByteArray &strippedRawPkg)
{
    _valid = false;
    do {
        const quint8 *pkg = (const quint8 *)strippedRawPkg.constData();
        int size = strippedRawPkg.size();
        // do some basic test
        // sof+len+cmd+eof
        if(strippedRawPkg.size() < 4)
            break;
        if(pkg[0] != StartOfFrame)
            break;
        if(pkg[size - 1] != EndOfFrame)
            break;
        _sof = *pkg++;
        _length = ebv2int(&pkg);
        _cmd = *pkg++;
        if(_length > 2)
        {
            _data.resize(_length - 2);
            memcpy(_data.data(), pkg, _length - 2);
            pkg += (_length - 2);
        }
        _eof = *pkg;
        _valid = true;
    } while(0);
    return _valid;
}

bool RLM100Package::create(CommandType cmd, const QByteArray &data)
{
    _valid = true;
    _sof = StartOfFrame;
    _length = 2 + data.size();
    _cmd = cmd;
    _data = data;
    _eof = EndOfFrame;
    return true;
}

QByteArray RLM100Package::toRawPackage() const
{
    if(!_valid)
        return QByteArray();
    QByteArray ret;
    ret.append(char(StartOfFrame));
    ret.append(int2ebv(_length));
    ret.append(char(_cmd));
    for(int i = 0; i < _data.size(); i++)
    {
        switch(quint8(_data.at(i)))
        {
        case StartOfFrame:
        case EndOfFrame:
        case EscapeChar:
            ret.append(EscapeChar);
        default:
            ret.append(_data.at(i));
            break;
        }
    }
    ret.append(char(EndOfFrame));
    return ret;
}

static quint8 uiiPCFlag = 0x00;
QByteArray RLM100Package::epc2uii(const QByteArray &epc)
{
    char len = epc.length() / 2;
    len = (len & 0x1F) << 3;
    len |= uiiPCFlag;
    //qDebug()<<"epc length"<<epc.length()<<"len ="<<(int)len<<"uiiPCFlag"<<uiiPCFlag;
    QByteArray ret;
    ret.append(len);
    ret.append(char(0));
    ret.append(epc);
    return ret;
}

QByteArray RLM100Package::uii2epc(const QByteArray &uii)
{
    if(uii.isEmpty())
        return QByteArray();
    int len = uii.at(0);
    uiiPCFlag = len & 0x07;
    len = (((len >> 3) & 0x1F) + 1) * 2;
    return uii.mid(2, len);
}

uint RLM100Package::ebv2int(const quint8 **stream)
{
    const quint8 *p = *stream;
    uint ret = 0;
    while(1)
    {
        quint8 ch = *p++;
        ret <<= 7;
        ret |= (ch & 0x7F);
        if((ch & 0x80) == 0)
        {
            *stream = p;
            break;
        }
    }
    return ret;
}

QByteArray RLM100Package::int2ebv(uint num)
{
    QByteArray ret, tmp;
    if(num < 128)
    {
        tmp.append(char(num & 0x7F));
        return tmp;
    }
    while(num != 0)
    {
        tmp.append(char(0x80 | (num & 0x7F)));
        num >>= 7;
    }
    tmp[0] = tmp[0] & 0x7F;
    ret.resize(tmp.size());
    for(int i = 0; i < tmp.size(); i++)
        ret[i] = tmp[tmp.size() - i - 1];
    return ret;
}
