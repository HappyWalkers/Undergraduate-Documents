#ifndef DBCONTROL_H
#define DBCONTROL_H
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QVariant>

class DBControl
{
public:
    DBControl();
    virtual ~DBControl();

    static bool Create();
    static void Destroy();

protected:
    static QSqlDatabase *_mainDB;
    static bool checkTable(const QString &tblName);
    static bool createTable(const QString &tblName, const QStringList &fieldList);
    static void removeTable(const QString &tblName);
    static void checkDatabase();

protected:
    QSqlQuery *q;
};

class DBDrugInfo : public DBControl
{
public:
    DBDrugInfo(const QString &cardid = "");

    bool first();
    bool next();
    int id() const;
    QString cardid() const;
    QString name() const;
    float price() const;
    int count() const;

    static QString findName(const QString &cardid);
    static float findPrice(const QString &cardid);
    static int findCount(const QString &cardid);

    static void buyIn(const QString &cardid, const QString &name, float price, int count);
    static void saleOut(const QString &cardid, int count);
};

class DBRecord : public DBControl
{
public:
    DBRecord();

    bool first();
    bool next();
    int id() const;
    QDateTime date() const;
    QString name() const;
    float price() const;
    int count() const;
    int type() const;

    static void addBuyInRecord(const QString &name, float price, int count);
    static void addSaleOutRecord(const QString &name, float price, int count);
};
#endif // DBCONTROL_H
