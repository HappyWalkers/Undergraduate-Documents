#include "IEEE14443Package.h"
#include <QDebug>

IEEE14443Package::IEEE14443Package(const QByteArray &rawPkg)
{
    bool done = false;
    const char *raw = rawPkg.constData();
    do {
        if(*raw++ != IEEE1443_START_CODE)
            break;
        _ssync = IEEE1443_START_CODE;
        _addr = *raw++;
        _addr |= (((quint16)(*raw++)) << 8);
//        _addr = *(quint16 *)raw;
//        raw += 2;
        _len = *raw++;
        if(_len > rawPkg.size() - 4)
            break;
        _cmd = *raw++;
        _data.clear();
        int dataLen = _len;
        if(rawPkg.size() - 4 == _len)
            dataLen -= (1 + 2);
        else
            dataLen -= (1 + 1);
        _data.append(raw, dataLen);
        raw += dataLen;
        _chksum = *raw++;
        if(*raw++ != IEEE1443_STOP_CODE)
            break;
        _esync = IEEE1443_STOP_CODE;
        done = true;
    } while(0);
    _valid = done;
}

IEEE14443Package::IEEE14443Package(quint16 addr, quint8 cmd)
{
    _valid = true;
    _ssync = IEEE1443_START_CODE;
    _chksum = 0;
    _addr = addr;
    _chksum += _addr & 0xFF;
    _chksum += (_addr >> 8);
    _len = 0 + 1 + 1;
    // 发送给读卡器的长度包含同步尾
    _len += 1;
    _chksum += _len;
    _cmd = cmd;
    _chksum += cmd;
    _esync = IEEE1443_STOP_CODE;
}

IEEE14443Package::IEEE14443Package(quint16 addr, quint8 cmd, const QByteArray &data)
{
    _valid = true;
    _ssync = IEEE1443_START_CODE;
    _chksum = 0;
    _addr = addr;
    _chksum += addr & 0xFF;
    _chksum += (addr >> 8);
    _len = data.size() + 1 + 1;
    // 发送给读卡器的长度包含同步尾
    _len += 1;
    _chksum += _len;
    _cmd = cmd;
    _chksum += cmd;
    _data = data;
    for(int i = 0; i < data.size(); i++)
        _chksum += data.at(i);
    _esync = IEEE1443_STOP_CODE;
}

IEEE14443Package::IEEE14443Package(quint16 addr, quint8 cmd, quint8 data)
{
    _valid = true;
    _ssync = IEEE1443_START_CODE;
    _chksum = 0;
    _addr = addr;
    _chksum += addr & 0xFF;
    _chksum += (addr >> 8);
    _len = 1 + 1 + 1;
    // 发送给读卡器的长度包含同步尾
    _len += 1;
    _chksum += _len;
    _cmd = cmd;
    _chksum += cmd;
    _data.append(data);
    _chksum += data;
    _esync = IEEE1443_STOP_CODE;
}

IEEE14443Package::IEEE14443Package(quint16 addr, quint8 cmd, quint8 data1, quint8 data2)
{
    _valid = true;
    _ssync = IEEE1443_START_CODE;
    _chksum = 0;
    _addr = addr;
    _chksum += addr & 0xFF;
    _chksum += (addr >> 8);
    _len = 2 + 1 + 1;
    // 发送给读卡器的长度包含同步尾
    _len += 1;
    _chksum += _len;
    _cmd = cmd;
    _chksum += cmd;
    _data.append(data1);
    _chksum += data1;
    _data.append(data2);
    _chksum += data2;
    _esync = IEEE1443_STOP_CODE;
}

QByteArray IEEE14443Package::toPurePackage() const
{
    if(!_valid)
        return QByteArray();
    QByteArray ret;
    ret.append(IEEE1443_START_CODE);
    ret.append((char *)&_addr, sizeof(_addr));
    ret.append(_len);
    ret.append(_cmd);
    ret.append(_data);
    ret.append(_chksum);
    ret.append(IEEE1443_STOP_CODE);
    return ret;
}

QByteArray IEEE14443Package::toRawPackage() const
{
    if(!_valid)
        return QByteArray();
    QByteArray ret;
    ret.append(IEEE1443_START_CODE);
    QByteArray content;
    content.append((char *)&_addr, sizeof(_addr));
    content.append(_len);
    content.append(_cmd);
    content.append(_data);
    content.append(_chksum);
    ret.append(getRawPackage(content));
    ret.append(IEEE1443_STOP_CODE);
    return ret;
}

QByteArray IEEE14443Package::getRawPackage(const quint8 *data, int len)
{
    QByteArray ret;
    while(len-- > 0)
    {
        if((*data == IEEE1443_ESCAPE_CHAR)
            || (*data == 0x02)
            || (*data == 0x03))
            ret.append(IEEE1443_ESCAPE_CHAR);
        ret.append(*data++);
    }
    return ret;
}

QByteArray IEEE14443Package::getRawPackage(const QByteArray &data)
{
    int len = data.size();
    const quint8 *p = (const quint8 *)data.constData();
    return getRawPackage(p, len);
}

QString IEEE14443Package::getRawString(const quint8 *data, int len)
{
    return getRawPackage(data, len).toHex();
}

QString IEEE14443Package::getRawString(const QByteArray &data)
{
    int len = data.size();
    const quint8 *p = (const quint8 *)data.constData();
    return getRawString(p, len);
}
