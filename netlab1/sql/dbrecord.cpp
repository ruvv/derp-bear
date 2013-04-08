#include "dbrecord.h"

DBRecord::DBRecord() {
    type = "";
    data = "";
    url = "";
    datetime = "";
}

DBRecord::DBRecord(QString _type, QString _data, QString _url, QString _datetime) {
    type = _type;
    data = _data;
    url = _url;
    datetime = _datetime;
}

QString DBRecord::toSelectQuery(QString table = "base") {
    QString result = "";
    result += QString("SELECT (type, data, url, datetime) FROM %1 WHERE (").arg(table);
    result += QString("type = '%1', ").arg(type);
    result += QString("data = '%1', ").arg(data);
    result += QString("url = '%1', ").arg(url);
    result += QString("datetime = '%1');").arg(datetime);
    return result;
}

QString DBRecord::toInsertQuery(QString table = "base") {
    QString result = "";
    result += QString("INSERT INTO %1 (type, data, url, datetime) VALUES (").arg(table);
    result += QString("'%1', ").arg(type);
    result += QString("'%1', ").arg(data);
    result += QString("'%1', ").arg(url);
    result += QString("'%1');").arg(datetime);
    return result;
}

QString DBRecord::toDeleteQuery(QString table = "base") {
    QString result = "";
    result += QString("DELETE FROM %1 WHERE (").arg(table);
    result += QString("type = '%1', ").arg(type);
    result += QString("data = '%1', ").arg(data);
    result += QString("url = '%1', ").arg(url);
    result += QString("datetime = '%1');").arg(datetime);
    return result;
}

void DBRecord::fromStrings(QString _type, QString _data, QString _url, QString _datetime) {
    type = _type;
    data = _data;
    url = _url;
    datetime = _datetime;
}

