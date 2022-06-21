#include "DBControl.h"
#include <QDebug>
#include <stdio.h>

/*****************************************************************/
/* DBControl class                                               */
/*****************************************************************/
QSqlDatabase *DBControl::_mainDB = NULL;
DBControl::DBControl()
    : q(NULL)
{}
DBControl::~DBControl()
{
    if(q)
        delete q;
}

bool DBControl::Create()
{
    if(_mainDB != NULL)
        return true;
    _mainDB = new QSqlDatabase;
    *_mainDB = QSqlDatabase::addDatabase("QSQLITE", "drug");
    _mainDB->setDatabaseName("drug.db");
    if(!_mainDB->open())
    {
        delete _mainDB;
        _mainDB = NULL;
        QSqlDatabase::removeDatabase("drug");
        return false;
    }
    checkDatabase();
    return true;
}

void DBControl::Destroy()
{
    if(_mainDB != NULL)
    {
        _mainDB->close();
        delete _mainDB;
        _mainDB = NULL;
    }
    QSqlDatabase::removeDatabase("drug");
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
    if(!checkTable("tbl_drugs"))
    {
        createTable("tbl_drugs", QStringList()
                    <<"[id] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT"
                    <<"[cardid] TEXT  UNIQUE NOT NULL"
                    <<"[name] TEXT  NOT NULL"
                    <<"[price] REAL NOT NULL"
                    <<"[count] INTEGER NOT NULL"
                    );
    }
    if(!checkTable("tbl_record"))
    {
        createTable("tbl_record", QStringList()
                    <<"[id] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT"
                    <<"[date] TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL"
                    <<"[name] TEXT NOT NULL"
                    <<"[price] REAL NOT NULL"
                    <<"[count] INTEGER NOT NULL"
                    <<"[type] INTEGER NOT NULL DEFAULT 1"
                    );
    }
}

/*****************************************************************/
/* DBDrugInfo class                                              */
/*****************************************************************/
DBDrugInfo::DBDrugInfo(const QString &cardid)
{
    QString sql = QString("SELECT [id],[cardid],[name],[price],[count] FROM [tbl_drugs]");
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

bool DBDrugInfo::first()
{
    if(q == NULL)
        return false;
    return q->first();
}

bool DBDrugInfo::next()
{
    if(q == NULL)
        return false;
    return q->next();
}

int DBDrugInfo::id() const
{
    if(q == NULL)
        return -1;
    if(!q->isActive())
        return -1;
    if(!q->isValid())
        return -1;
    return q->value(0).toInt();
}

QString DBDrugInfo::cardid() const
{
    if(q == NULL)
        return QString();
    if(!q->isActive())
        return QString();
    if(!q->isValid())
        return QString();
    return q->value(1).toString();
}

QString DBDrugInfo::name() const
{
    if(q == NULL)
        return QString();
    if(!q->isActive())
        return QString();
    if(!q->isValid())
        return QString();
    return q->value(2).toString();
}

float DBDrugInfo::price() const
{
    if(q == NULL)
        return 0.0;
    if(!q->isActive())
        return 0.0;
    if(!q->isValid())
        return 0.0;
    return q->value(3).toFloat();
}

int DBDrugInfo::count() const
{
    if(q == NULL)
        return 0;
    if(!q->isActive())
        return 0;
    if(!q->isValid())
        return 0;
    return q->value(4).toInt();
}

QString DBDrugInfo::findName(const QString &cardid)
{
    QString sql = QString("SELECT [name] FROM [tbl_drugs] WHERE [cardid] = '%1'").arg(cardid);
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

float DBDrugInfo::findPrice(const QString &cardid)
{
    QString sql = QString("SELECT [price] FROM [tbl_drugs] WHERE [cardid] = '%1'").arg(cardid);
    QSqlQuery q(*_mainDB);
    q.exec(sql);
    if(!q.isActive())
        return 0.0;
    if(!q.first())
        return 0.0;
    float ret = q.value(0).toFloat();
    q.finish();
    return ret;
}

int DBDrugInfo::findCount(const QString &cardid)
{
    QString sql = QString("SELECT [count] FROM [tbl_drugs] WHERE [cardid] = '%1'").arg(cardid);
    QSqlQuery q(*_mainDB);
    q.exec(sql);
    if(!q.isActive())
        return 0;
    if(!q.first())
        return 0;
    int ret = q.value(0).toInt();
    q.finish();
    return ret;
}

void DBDrugInfo::buyIn(const QString &cardid, const QString &name, float price, int count)
{
    if(findName(cardid).isEmpty())
    {
        QString sql = QString("INSERT INTO [tbl_drugs] ([cardid], [name], [price], [count]) VALUES ('%1', '%2', %3, %4)")
                      .arg(cardid).arg(name).arg(price).arg(count);
        QSqlQuery q(*_mainDB);
        q.exec(sql);
        q.finish();
    }
    else
    {
        int oldcount = findCount(cardid);
        oldcount += count;
        QString sql = QString("UPDATE [tbl_drugs] SET [name] = '%1', [price] = %2, [count] = %3 WHERE [cardid] = '%4'")
                      .arg(name).arg(price).arg(oldcount).arg(cardid);
        QSqlQuery q(*_mainDB);
        q.exec(sql);
        q.finish();
    }
    DBRecord::addBuyInRecord(name, price, count);
}

void DBDrugInfo::saleOut(const QString &cardid, int count)
{
    if(findName(cardid).isEmpty())
        return;
    int oldcount = findCount(cardid);
    oldcount -= count;
    if(oldcount <= 0)
    {
        QString sql = QString("DELETE FROM [tbl_drugs] WHERE [cardid] = '%1'").arg(cardid);
        QSqlQuery q(*_mainDB);
        q.exec(sql);
        q.finish();
    }
    else
    {
        QString sql = QString("UPDATE [tbl_drugs] SET [count] = %1 WHERE [cardid] = '%2'")
                      .arg(oldcount).arg(cardid);
        QSqlQuery q(*_mainDB);
        q.exec(sql);
        q.finish();
    }
    DBRecord::addSaleOutRecord(findName(cardid), findPrice(cardid), count);
}

/*****************************************************************/
/* DBRecord class                                                */
/*****************************************************************/
DBRecord::DBRecord()
{
    QString sql = QString("SELECT [id], [date], [name], [price], [count], [type] FROM [tbl_record]");
    q = new QSqlQuery(*_mainDB);
    q->exec(sql);
    if(!q->isActive())
    {
        delete q;
        q = NULL;
    }
    q->first();
}

bool DBRecord::first()
{
    if(q == NULL)
        return false;
    return q->first();
}

bool DBRecord::next()
{
    if(q == NULL)
        return false;
    return q->next();
}

int DBRecord::id() const
{
    if(q == NULL)
        return -1;
    if(!q->isActive())
        return -1;
    if(!q->isValid())
        return -1;
    return q->value(0).toInt();
}

QDateTime DBRecord::date() const
{
    if(q == NULL)
        return QDateTime();
    if(!q->isActive())
        return QDateTime();
    if(!q->isValid())
        return QDateTime();
    return q->value(1).toDateTime();
}

QString DBRecord::name() const
{
    if(q == NULL)
        return QString();
    if(!q->isActive())
        return QString();
    if(!q->isValid())
        return QString();
    return q->value(2).toString();
}

float DBRecord::price() const
{
    if(q == NULL)
        return 0.0;
    if(!q->isActive())
        return 0.0;
    if(!q->isValid())
        return 0.0;
    return q->value(3).toFloat();
}

int DBRecord::count() const
{
    if(q == NULL)
        return 0;
    if(!q->isActive())
        return 0;
    if(!q->isValid())
        return 0;
    return q->value(4).toInt();
}

int DBRecord::type() const
{
    if(q == NULL)
        return -1;
    if(!q->isActive())
        return -1;
    if(!q->isValid())
        return -1;
    return q->value(5).toInt();
}

void DBRecord::addBuyInRecord(const QString &name, float price, int count)
{
    QString sql = QString(
            "INSERT INTO [tbl_record] ([name], [price], [count], [type]) VALUES ('%1', %2, %3, 1)"
            ).arg(name).arg(price).arg(count);
    QSqlQuery q(*_mainDB);
    q.exec(sql);
    q.finish();
}

void DBRecord::addSaleOutRecord(const QString &name, float price, int count)
{
    QString sql = QString(
            "INSERT INTO [tbl_record] ([name], [price], [count], [type]) VALUES ('%1', %2, %3, 0)"
            ).arg(name).arg(price).arg(count);
    QSqlQuery q(*_mainDB);
    q.exec(sql);
    q.finish();
}
