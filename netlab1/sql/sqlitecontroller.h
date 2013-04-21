#ifndef SQLITECONTROLLER_H
#define SQLITECONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>

//#include <sql/dbrecord.h>

class SqliteController  : public QObject {
        Q_OBJECT
private:
    QStringList queryPool;   // пул запросов на запись и удаление
    QSqlDatabase db;    // связь с бд


    QList<DBRecord>* processSelect(QString query);
    QList<DBRecord>* processInsert(QString query);
    QList<DBRecord>* processDelete(QString query);  // обработчки запросов

private slots:
    void executeOldestQuery(); // выполнение старейшего запроса в пуле

protected:

public:
    SqliteController(QString dbname); // dbname == "default" by default
    QList<DBRecord>* processQuery(QString query);  // обработка SQL-запросов
                                                     // отправляет запрос в пул, либо выполняет в зависимости от занятости бд
                                                     // возвращает указатель на полученные данные, либо 0 (в случае не-select запроса)
signals:
    void msgcrit(QString msg);
    void msgerr(QString msg);
    void msgok(QString msg);
    void msgmsg(QString msg);  // броски статусных сообщений
};

#endif // SQLITECONTROLLER_H
