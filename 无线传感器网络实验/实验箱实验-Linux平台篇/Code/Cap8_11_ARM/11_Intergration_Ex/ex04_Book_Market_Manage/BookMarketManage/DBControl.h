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

class DBCard : public DBControl
{
public:
    DBCard(const QString &cardid = "");

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
};

class DBBook : public DBControl
{
public:
    DBBook(const QString &bookid = "");

    bool first();
    bool next();
    int id() const;
    QString bookId() const;
    QString name() const;
    int status() const;

    static void addBook(const QString &bookid, const QString &name);
    static void delBook(const QString &bookid);
    static void updateBook(const QString &bookid, const QString &name);
    static QString findName(const QString &bookid);
    static int getStatus(const QString &bookid);
    static void borrow(const QString &bookid);
    static void back(const QString &bookid);
};

class DBRecord : public DBControl
{
public:
    DBRecord();

    bool first();
    bool next();
    int id() const;
    QDateTime date() const;
    QString bookid() const;
    QString cardid() const;
    int type() const;

    static bool addRecord(const QString &bookid, const QString &cardid, int type);
    static void delRecord(int id);
#if 0
    static void delOldLog(const QDateTime &d);
    static void delNewLog(const QDateTime &d);
    static void delLogNotIn(const QDateTime &d1, const QDateTime &d2);
    static void delLogBetween(const QDateTime &d1, const QDateTime &d2);
#endif
};
#endif // DBCONTROL_H
