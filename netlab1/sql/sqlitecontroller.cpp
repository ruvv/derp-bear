#include "sqlitecontroller.h"
#include <QSqlError>
#include <QSqlRecord>
#include <QTimer>
#include <QVariant>

void SqliteController::executeOldestQuery() {
    QString query = queryPool.at(0);
    db.transaction();
    QSqlQuery q;
    q.prepare(query);
    q.exec();
    if(!(db.commit())) {
        if(db.lastError().number() == 5 || db.lastError().number() == 6) {
            QTimer::singleShot(50, this, SLOT(executeOldestQuery()));
            return;
        } else {
            queryPool.pop_front();
            msgerr(QString("Error: ") + db.lastError().text());
            if(!queryPool.isEmpty()) {
                QTimer::singleShot(50, this, SLOT(executeOldestQuery()));
            }
        }
    } else {
        queryPool.pop_front();
        msgok(QString("Succesfully executed: ") + query + QString("."));
        if(!queryPool.isEmpty()) {
            QTimer::singleShot(50, this, SLOT(executeOldestQuery()));
        }
    }
}

QList<DBRecord>* SqliteController::processSelect(QString query) {
    QList<DBRecord>* result = new QList<DBRecord>();
    QSqlQuery q;
    q.prepare(query);
    q.exec();
    if(q.lastError().isValid()) {
        msgerr(QString("Error: ") + q.lastError().text());
        return 0;
    } else {
        QSqlRecord record = q.record();
        while(q.next()) {
            result->append(DBRecord(q.value(record.indexOf("type")).toString(),
                                    q.value(record.indexOf("data")).toString(),
                                    q.value(record.indexOf("url")).toString(),
                                    q.value(record.indexOf("datetime")).toString()));
        }
        msgok(QString("Succesfully executed: ") + query + QString("."));
        return result;
    }
}

QList<DBRecord>* SqliteController::processInsert(QString query) {
    db.transaction();
    QSqlQuery q;
    q.prepare(query);
    q.exec();
    if(!db.commit()) {
        if(db.lastError().number() == 5 || db.lastError().number() == 6) {
            queryPool.append(query);
            QTimer::singleShot(50, this, SLOT(executeOldestQuery()));
        } else {
            msgerr(QString("Error: ") + db.lastError().text());
        }
    } else {
        msgok(QString("Succesfully executed: ") + query + QString("."));
    }
    return 0;
}

QList<DBRecord>* SqliteController::processDelete(QString query) {
    db.transaction();
    QSqlQuery q;
    q.prepare(query);
    q.exec();
    if(!db.commit()) {
        if(db.lastError().number() == 5 || db.lastError().number() == 6) {
            queryPool.append(query);
            QTimer::singleShot(50, this, SLOT(executeOldestQuery()));
        } else {
            msgerr(QString("Error: ") + db.lastError().text());
        }
    } else {
        msgok(QString("Succesfully executed: ") + query + QString("."));
    }
    return 0;
}

SqliteController::SqliteController(QString dbname = "default") {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    if(!db.open()) {
        msgcrit(QString("Error: ") + db.lastError().text());
    }
}

QList<DBRecord>* SqliteController::processQuery(QString query) {
    if(query.toLower().contains("select")) {
        return processSelect(query);
    } else if(query.toLower().contains("insert")) {
        return processInsert(query);
    } else if(query.toLower().contains("delete")) {
        return processDelete(query);
    } else {
        msgmsg(QString("Untracked query: ") + query + QString(" dropped."));
        return 0;
    }
}


