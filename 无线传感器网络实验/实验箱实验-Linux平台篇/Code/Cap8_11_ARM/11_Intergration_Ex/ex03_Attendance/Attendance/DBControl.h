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
    static bool Create();
    static void Destroy();

protected:
    static QSqlDatabase *_mainDB;
    static bool checkTable(const QString &tblName);
    static bool createTable(const QString &tblName, const QStringList &fieldList);
    static void removeTable(const QString &tblName);
    static void checkDatabase();
};

class DBCard : public DBControl
{
public:
    DBCard(const QString &cardid = "");
    virtual ~DBCard();

    bool first();
    bool next();
    int id() const;
    QString cardid() const;
    QString name() const;

    static QString findName(const QString &cardid);
    static QString findCard(const QString &name);
    static bool addCard(const QString &cardid, const QString &name);
    static void delCard(const QString &cardid);
    static bool updateName(const QString &cardid, const QString &newname);
    static bool updateCardId(const QString &name, const QString &newcardid);

protected:
    QSqlQuery *q;
};

class DBLog : public DBControl
{
public:
    DBLog(const QString &cardid = "");
    virtual ~DBLog();

    bool first();
    bool next();
    int id() const;
    QDateTime date() const;
    QString cardid() const;

    static bool addLog(const QString &cardid);
    static void delLog(int id);
    static void delOldLog(const QDateTime &d);
    static void delNewLog(const QDateTime &d);
    static void delLogNotIn(const QDateTime &d1, const QDateTime &d2);
    static void delLogBetween(const QDateTime &d1, const QDateTime &d2);

protected:
    QSqlQuery *q;
};
#endif // DBCONTROL_H
