#ifndef RLM100PACKAGE_H
#define RLM100PACKAGE_H
#include <QByteArray>
#include <QString>

class RLM100Package
{
    bool _valid;
    bool _cmdPackage;
    quint8 _sof;            // always 0xAA
    quint8 _length;         // _length + _cmd + _data + crc16
    quint8 _cmd;
    QByteArray _data;
    quint16 _crc16;
    quint8 _eof;            // always 0x55

public:
    enum {
        StartOfFrame = 0xAA, EndOfFrame = 0x55, EscapeChar = 0xFF
    };
    // Command List
    enum CommandType {
        GetStatus = 0x00,           // 询问状态
        GetPower,                   // 读取功率设置
        SetPower,                   // 设置功率
        GetFre = 0x05,              // 读取频率设置
        SetFre,                     // 设置频率
        GetVersion,                 // 读取RLM信息
        ReadUID = 0x0A,             // 读取RLM的UID信息

        Inventory = 0x10,           // (循环模式)单标签识别
        InventoryAnti,              // (循环模式)多标签识别
        StopGet,                    // 停止操作
        ReadData,                   // 读取标签数据(指定UII)
        WriteData,                  // 写入标签数据_单字长(指定UII)
        EraseData,                  // 擦除标签数据(指定UII)
        LockMem,                    // 锁定标签(指定UII)
        KillTag,                    // 销毁标签(指定UII)
        InventorySingle,            // 单标签识别_单步模式
        BlockWriteData,             // 写入标签数据_多字长(指定UII)
        SingleReadData = 0x20,      // 读取标签数据(不指定UII)
        SingleWriteData,            // 写入标签数据_单字长(不指定UII)
        SingleEraseData,            // 擦除标签数据(不指定UII)
        SingleLockMem,              // 锁定标签(不指定UII)
        SingleKillTag,              // 销毁标签(不指定UII)
        SingleBlockWriteData,       // 写入标签数据_多字长(不指定UII)
        AntiColisionReadData,       // (循环模式)多标签识别并读取数据

        ReadReg = 0x30,             // 读取寄存器
        WriteReg,                   // 设置寄存器
        ResetReg,                   // 恢复寄存器出厂设置
        SaveReg,                    // 保存当前设置

        AddSelect = 0x38,           // 添加SELECT记录
        DeleteSelect,               // 删除SELECT记录
        GetSelect,                  // 读取SELECT记录
        ChooseSelect,               // 选择SELECT记录

        EnterSleep = 0x50,          // 进入Sleep模式

        InvalidCommand
    };
    // for recved package
    RLM100Package(const QByteArray &strippedRawPkg);
    // for send package
    RLM100Package(CommandType cmd, const QByteArray &data = QByteArray());

    // Common operation
    bool isValid() const {
        return _valid;
    }

    quint8 length() const {
        return _length;
    }
    quint8 command() const {
        return _cmd;
    }
    const QByteArray &data() const {
        return _data;
    }
    quint8 responseStatus() const {
        if(_data.isEmpty())
            return -1;
        return _data.at(0);
    }
    QByteArray responseData() const {
        if(_data.size() <= 1)
            return QByteArray();
        return _data.mid(1);
    }
    QByteArray toRawPackage() const;

    static QByteArray epc2uii(const QByteArray &epc);
    static QByteArray uii2epc(const QByteArray &uii);

private:
    bool load(const QByteArray &strippedRawPkg);
    bool create(CommandType cmd, const QByteArray &data = QByteArray());

    static uint ebv2int(const quint8 **stream);
    static QByteArray int2ebv(uint num);
};

#endif // RLM100PACKAGE_H
