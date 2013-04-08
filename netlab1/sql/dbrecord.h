#ifndef DBRECORD_H
#define DBRECORD_H

#include <QString>

/* record-unit class */

class DBRecord {
private:
    QString type;
    QString data;
    QString url;
    QString datetime;   // fields

public:
    DBRecord(); // creates DBRecord with empty fields
    DBRecord(QString _type, QString _data, QString _url, QString _datetime);    // creates DBRecord from QString fields

    QString toSelectQuery(QString table);   // forms select-type query, table == "base" by default
    QString toInsertQuery(QString table);   // forms insert-type query, table == "base" by default
    QString toDeleteQuery(QString table);   // forms delete-type query, table == "base" by default

    void fromStrings(QString _type, QString _data, QString _url, QString _datetime);    // rebulds DBRecord with QString fields
};

#endif // DBRECORD_H
