#include "DBControl.h"
#include <QDebug>
#include <stdio.h>

/*****************************************************************/
/* DBControl class                                               */
/*****************************************************************/
QSqlDatabase *DBControl::_mainDB = NULL;
bool DBControl::Create()
{
    if(_mainDB != NULL)
        return true;
    _mainDB = new QSqlDatabase;
    *_mainDB = QSqlDatabase::addDatabase("QSQLITE", "attendance");
    _mainDB->setDatabaseName("attendance.db");
    if(!_mainDB->open())
    {
        delete _mainDB;
        _mainDB = NULL;
        QSqlDatabase::removeDatabase("attendance");
        return false;
    }
    checkDatabase();
    return true;
}

void DBControl::Destroy()
{
    if(_mainDB == NULL)
        return;
    _mainDB->close();
    delete _mainDB;
    _mainDB = NULL;
    QSqlDatabase::removeDatabase("attendance");
}

bool DBControl::checkTable(const QString &tblName)
{
    if(_mainDB == NULL)
        return false;
    QSqlQuery q(*_mainDB);
    QString sql = QString("SELECT COUNT(*) FROM sqlite_master WHERE [name] = '%1'").arg(tblName);
    if(!q.exec(sql))
        return false;
    if(!q.first())
    {
        q.finish();
        return false;
    }
    int count = q.value(0).toInt();
    q.finish();
    return (count > 0);
}

void DBControl::removeTable(const QString &tblName)
{
    if(_mainDB == NULL)
        return;
    QSqlQuery q(*_mainDB);
    QString sql = QString("DROP TABLE [%1]").arg(tblName);
    q.exec(sql);
    q.finish();
}

bool DBControl::createTable(const QString &tblName, const QStringList &fieldList)
{
    if(_mainDB == NULL)
        return false;
    if(fieldList.count() <= 0)
        return false;
    if(checkTable(tblName))
        return true;
    QSqlQuery q(*_mainDB);
    QString sql = QString("CREATE TABLE [%1] (").arg(tblName);
    QStringList::const_iterator i;
    for(i = fieldList.constBegin(); i != fieldList.constEnd(); ++i)
    {
        sql += (*i);
        sql += ",";
    }
    if(sql.at(sql.length() - 1) == ',')
        sql = sql.left(sql.length() - 1);
    else
        return false;
    sql += ")";
    bool ret = q.exec(sql);
    q.finish();
    return ret;
}

void DBControl::checkDatabase()
{
    if(_mainDB == NULL)
        return;
    if(!checkTable("tbl_id"))
    {
        createTable("tbl_id", QStringList()
                    <<"[id] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT"
                    <<"[cardid] TEXT  UNIQUE NOT NULL"
                    <<"[name] TEXT  NOT NULL"
                    );
    }
    if(!checkTable("tbl_log"))
    {
        createTable("tbl_log", QStringList()
                    <<"[id] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT"
                    <<"[date] TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL"
                    <<"[cardid] TEXT  NOT NULL"
                    );
    }
}

/*****************************************************************/
/* DBCard class                                                  */
/*****************************************************************/
DBCard::DBCard(const QString &cardid)
    : q(NULL)
{
    QString sql = QString("SELECT [id],[cardid],[name] FROM [tbl_id]");
    if(!cardid.isEmpty())
        sql += QString(" WHERE [cardid] = '%1'").arg(cardid);
    q = new QSqlQuery(*_mainDB);
    q->exec(sql);
    if(!q->isActive())
    {
        delete q;
        q = NULL;
    }
    else
        q->first();
}

DBCard::~DBCard()
{
    if(q)
        delete q;
}

bool DBCard::first()
{
    if(q == NULL)
        return false;
    return q->first();
}

bool DBCard::next()
{
    if(q == NULL)
        return false;
    return q->next();
}

int DBCard::id() const
{
    if(q == NULL)
        return -1;
    if(!q->isActive())
        return -1;
    if(!q->isValid())
        return -1;
    return q->value(0).toInt();
}

QString DBCard::cardid() const
{
    if(q == NULL)
        return QString();
    if(!q->isActive())
        return QString();
    if(!q->isValid())
        return QString();
    return q->value(1).toString();
}

QString DBCard::name() const
{
    if(q == NULL)
        return QString();
    if(!q->isActive())
        return QString();
    if(!q->isValid())
        return QString();
    return q->value(2).toString();
}

QString DBCard::findName(const QString &cardid)
{
    QString sql = QString("SELECT [name] FROM [tbl_id] WHERE [cardid] = '%1'").arg(cardid);
    QSqlQuery q(*_mainDB);
    q.exec(sql);
    if(!q.isActive())
        return QString();
    if(!q.first())
        return QString();
    QString ret = q.value(0).toString();
    q.finish();
    return ret;
}

QString DBCard::findCard(const QString &name)
{
    QString sql = QString("SELECT [cardid] FROM [tbl_id] WHERE [name] = '%1'").arg(name);
    QSqlQuery q(*_mainDB);
    q.exec(sql);
    if(!q.isActive())
        return QString();
    if(!q.first())
        return QString();
    QString ret = q.value(0).toString();
    q.finish();
    return ret;
}

bool DBCard::addCard(const QString &cardid, const QString &name)
{
    if(findName(cardid).isEmpty() && findCard(name).isEmpty())
    {
        QString sql = QString(
                "INSERT INTO [tbl_id] ([cardid], [name]) VALUES ('%1', '%2')"
                ).arg(cardid).arg(name);
        QSqlQuery q(*_mainDB);
        bool ret = q.exec(sql);
        q.finish();
        return ret;
    }
    else
        return false;
}

void DBCard::delCard(const QString &cardid)
{
    QString sql = QString(
            "DELETE FROM [tbl_id] WHERE [cardid] = '%1'").arg(cardid);
    QSqlQuery q(*_mainDB);
    q.exec(sql);
    q.finish();
}

bool DBCard::updateName(const QString &cardid, const QString &newname)
{
    if(!findCard(newname).isEmpty())
        return false;
    if(!findName(cardid).isEmpty())
        delCard(cardid);
    return addCard(cardid, newname);
}

bool DBCard::updateCardId(const QString &name, const QString &newcardid)
{
    if(!findName(newcardid).isEmpty())
        return false;
    QString c = findCard(name);
    if(!c.isEmpty())
        delCard(c);
    return addCard(newcardid, name);
}

/*****************************************************************/
/* DBLog class                                                   */
/*****************************************************************/
DBLog::DBLog(const QString &cardid)
    : q(NULL)
{
    QString sql = QString("SELECT [id], [date], [cardid] FROM [tbl_log]");
    if(!cardid.isEmpty())
        sql += QString(" WHERE [cardid] = '%1'").arg(cardid);
    q = new QSqlQuery(*_mainDB);
    q->exec(sql);
    if(!q->isActive())
    {
        delete q;
        q = NULL;
    }
    q->first();
}

DBLog::~DBLog()
{
    if(q)
        delete q;
}

bool DBLog::first()
{
    if(q == NULL)
        return false;
    return q->first();
}

bool DBLog::next()
{
    if(q == NULL)
        return false;
    return q->next();
}

int DBLog::id() const
{
    if(q == NULL)
        return -1;
    if(!q->isActive())
        return -1;
    if(!q->isValid())
        return -1;
    return q->value(0).toInt();
}

QDateTime DBLog::date() const
{
    if(q == NULL)
        return QDateTime();
    if(!q->isActive())
        return QDateTime();
    if(!q->isValid())
        return QDateTime();
    return q->value(1).toDateTime();
}

QString DBLog::cardid() const
{
    if(q == NULL)
        return QString();
    if(!q->isActive())
        return QString();
    if(!q->isValid())
        return QString();
    return q->value(2).toString();
}

bool DBLog::addLog(const QString &cardid)
{
    QString sql = QString(
            "INSERT INTO [tbl_log] ([cardid]) VALUES ('%1')"
            ).arg(cardid);
    QSqlQuery q(*_mainDB);
    bool ret = q.exec(sql);
    q.finish();
    return ret;
}

void DBLog::delLog(int id)
{
    QString sql = QString(
            "DELETE FROM [tbl_log] WHERE [id] = %1").arg(id);
    QSqlQuery q(*_mainDB);
    q.exec(sql);
    q.finish();
}

void DBLog::delOldLog(const QDateTime &d)
{
    char sql[512];
    sprintf(sql, "DELETE FROM [tbl_log] WHERE [date] < '%d-%02d-%02d %02d:%02d:%02d'",
            d.date().year(), d.date().month(), d.date().day(),
            d.time().hour(), d.time().minute(), d.time().second());
    QSqlQuery q(*_mainDB);
    q.exec(sql);
    q.finish();
}

void DBLog::delNewLog(const QDateTime &d)
{
    char sql[512];
    sprintf(sql, "DELETE FROM [tbl_log] WHERE [date] > '%d-%02d-%02d %02d:%02d:%02d'",
            d.date().year(), d.date().month(), d.date().day(),
            d.time().hour(), d.time().minute(), d.time().second());
    QSqlQuery q(*_mainDB);
    q.exec(sql);
    q.finish();
}

void DBLog::delLogNotIn(const QDateTime &dt1, const QDateTime &dt2)
{
    QDateTime d1(dt1), d2(dt2);
    if(d1 > d2)
    {
        QDateTime d = d1;
        d1 = d2;
        d2 = d1;
    }
    char sql[512];
    sprintf(sql, "DELETE FROM [tbl_log] WHERE [date] < '%d-%02d-%02d %02d:%02d:%02d' OR [date] > '%d-%02d-%02d %02d:%02d:%02d'",
            d1.date().year(), d1.date().month(), d1.date().day(),
            d1.time().hour(), d1.time().minute(), d1.time().second(),
            d2.date().year(), d2.date().month(), d2.date().day(),
            d2.time().hour(), d2.time().minute(), d2.time().second());
    QSqlQuery q(*_mainDB);
    q.exec(sql);
    q.finish();
}

void DBLog::delLogBetween(const QDateTime &dt1, const QDateTime &dt2)
{
    QDateTime d1(dt1), d2(dt2);
    if(d1 > d2)
    {
        QDateTime d = d1;
        d1 = d2;
        d2 = d1;
    }
    char sql[512];
    sprintf(sql, "DELETE FROM [tbl_log] WHERE [date] >= '%d-%02d-%02d %02d:%02d:%02d' AND [date] <= '%d-%02d-%02d %02d:%02d:%02d'",
            d1.date().year(), d1.date().month(), d1.date().day(),
            d1.time().hour(), d1.time().minute(), d1.time().second(),
            d2.date().year(), d2.date().month(), d2.date().day(),
            d2.time().hour(), d2.time().minute(), d2.time().second());
    QSqlQuery q(*_mainDB);
    q.exec(sql);
    q.finish();
}
