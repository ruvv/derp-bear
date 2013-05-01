#include "task.h"
#include "http/htmlpagegetter.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>
#include <QDebug>

Task::Task(QObject *parent) : QObject(parent) {
    id = 0;
}

Task::~Task() {
    if(processor != 0) {
        delete processor;
    }
}

void Task::setType(int nType) {
    type = nType;
    switch (type) {
    case 1:
        processor = new ProcessorLinks;
        break;
    case 3:
        processor = new ProcessorLists;
        break;
    case 4:
        processor = new ProcessorImages;
        break;
    case 8:
        processor = new ProcessorPrintScreen;
        break;
    case 9:
        processor = new ProcessorInputs;
        break;
    default:
        emit error(QString("Err: Unknown task type."));
    }
}


void Task::process() {
    emit started(id);
    HtmlPageGetter hpg;
    QString html = hpg.getsync(url);
    sptr<ModelLight> model(processor->process(html, url));
    QStringList list = model->toStringList();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QString("con") + QString::number(id));
    db.setDatabaseName("netlab.sqlite");
    if (!db.open()) {
        qDebug() << "bad grab" << db.lastError().text();
        emit error(QString("Err: sqlite is not open."));
        return;
    }
    QSqlQuery q(db);
    q.prepare(QString("INSERT INTO base (type, url, datetime, data) VALUES (:type, :url, :datetime, :data);"));
    q.bindValue(":type", list.at(0));
    q.bindValue(":url", list.at(1));
    q.bindValue(":datetime", list.at(2));
    q.bindValue(":data", list.at(3));
    bool result = q.exec();
//    bool result = q.exec(QString("INSERT INTO base (type, url, datetime, data) VALUES (%1, '%2', '%3', '%4');")
//                         .arg(list.at(0)).arg(list.at(1)).arg(list.at(2)).arg(list.at(3)));
    if(!result) {
        qDebug() << "bad grab" << q.lastError().text();
        emit error(QString("Err: query failed."));
    }
    emit finished(id);
}
