#include "simpletaskrunner.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QThread>
#include "task.h"

#include "processors/processorlinks.h"
#include "processors/processorlists.h"
#include "processors/processorprintscreen.h"
#include "processors/processorinputs.h"
#include "processors/processorimages.h"
#include "http/htmlpagegetter.h"

SimpleTaskRunner::SimpleTaskRunner(QObject *parent) : QObject(parent) {
    idCounter = 0;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("netlab.sqlite");
    if (!db.open()) {
        qDebug() << "bad grab" << db.lastError().text();
    }
    QSqlQuery q(db);

    bool result = q.exec("CREATE TABLE IF NOT EXISTS base (type INTEGER, url TEXT, datetime TEXT, data BLOB);");
    if(!result) {
        qDebug() << "bad grab" << q.lastError().text();
    }
}


int SimpleTaskRunner::runInnerLinks(QString url, int id) {
    HtmlPageGetter hpg;
    QString html = hpg.getsync(url);
    ProcessorLinks pl;
    sptr<ModelLight> model = pl.process(html, url);
    QStringList list = model->toStringList();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QString("con") + QString::number(id));
    db.setDatabaseName("netlab.sqlite");
    if (!db.open()) {
        qDebug() << "bad grab" << db.lastError().text();
        return -1;
    }
    QSqlQuery q(db);

    bool result = q.exec(QString("INSERT INTO base (type, url, datetime, data) VALUES (%1, '%2', '%3', '%4');")
                         .arg(list.at(0)).arg(list.at(1)).arg(list.at(2)).arg(list.at(3)));
    if(!result) {
        qDebug() << "bad grab" << q.lastError().text();
    }
    return id;
}



int SimpleTaskRunner::runLists(QString url, int id) {
    HtmlPageGetter hpg;
    QString html = hpg.getsync(url);
    ProcessorLists pls;
    sptr<ModelLight> model = pls.process(html, url);
    QStringList list = model->toStringList();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QString("con") + QString::number(id));
    db.setDatabaseName("netlab.sqlite");
    if (!db.open()) {
        qDebug() << "bad grab" << db.lastError().text();
        return -1;
    }
    QSqlQuery q(db);

    bool result = q.exec(QString("INSERT INTO base (type, url, datetime, data) VALUES (%1, '%2', '%3', '%4');")
                         .arg(list.at(0)).arg(list.at(1)).arg(list.at(2)).arg(list.at(3)));
    if(!result) {
        qDebug() << "bad grab" << q.lastError().text();
    }
    return id;
}


int SimpleTaskRunner::runImages(QString url, int id) {
    HtmlPageGetter hpg;
    QString html = hpg.getsync(url);
    ProcessorImages pim;
    sptr<ModelLight> model = pim.process(html, url);
    QStringList list = model->toStringList();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QString("con") + QString::number(id));
    db.setDatabaseName("netlab.sqlite");
    if (!db.open()) {
        qDebug() << "bad grab" << db.lastError().text();
        return -1;
    }
    QSqlQuery q(db);

    bool result = q.exec(QString("INSERT INTO base (type, url, datetime, data) VALUES (%1, '%2', '%3', '%4');")
                         .arg(list.at(0)).arg(list.at(1)).arg(list.at(2)).arg(list.at(3)));
    if(!result) {
        qDebug() << "bad grab" << q.lastError().text();
    }
    return id;
}


int SimpleTaskRunner::runPrintScreen(QString url, int id) {
    HtmlPageGetter hpg;
    QString html = hpg.getsync(url);
    ProcessorPrintScreen pl;
    sptr<ModelLight> model = pl.process(html, url);
    QStringList list = model->toStringList();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QString("con") + QString::number(id));
    db.setDatabaseName("netlab.sqlite");
    if (!db.open()) {
        qDebug() << "bad grab" << db.lastError().text();
        return -1;
    }
    QSqlQuery q(db);

    bool result = q.exec(QString("INSERT INTO base (type, url, datetime, data) VALUES (%1, '%2', '%3', '%4');")
                         .arg(list.at(0)).arg(list.at(1)).arg(list.at(2)).arg(list.at(3)));
    if(!result) {
        qDebug() << "bad grab" << q.lastError().text();
        return -1;
    }
    return id;
}


int SimpleTaskRunner::runInputs(QString url, int id) {
    HtmlPageGetter hpg;
    QString html = hpg.getsync(url);
    ProcessorInputs pl;
    sptr<ModelLight> model = pl.process(html, url);
    QStringList list = model->toStringList();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QString("con") + QString::number(id));
    db.setDatabaseName("netlab.sqlite");
    if (!db.open()) {
        qDebug() << "bad grab" << db.lastError().text();
        return -1;
    }
    QSqlQuery q(db);

    bool result = q.exec(QString("INSERT INTO base (type, url, datetime, data) VALUES (%1, '%2', '%3', '%4');")
                         .arg(list.at(0)).arg(list.at(1)).arg(list.at(2)).arg(list.at(3)));
    if(!result) {
        qDebug() << "bad grab" << q.lastError().text();
        return -1;
    }
    return id;
}



int SimpleTaskRunner::proceedLinks(QString html, QString url, int id) {
    ProcessorLinks pl;
    sptr<ModelLight> model(pl.process(html, url));
    model->toStringList();
    return id;
}

void SimpleTaskRunner::errorString(QString err) {
    emit errmsg(err);
}

void SimpleTaskRunner::handleFinished() {
    int finishedId = tasktable.key(qobject_cast<QThread*>(QObject::sender()));
    emit taskFinished(finishedId);
    tasktable.remove(finishedId);
}


void SimpleTaskRunner::runsync(QString url, int type) {
    switch (type) {
    case 1:
        runInnerLinks(url, idCounter++);
        break;
    case 3:
        runLists(url, idCounter++);
        break;
    case 4:
        runImages(url, idCounter++);
        break;
    case 8:
        runPrintScreen(url, idCounter++);
        break;
    case 9:
        runInputs(url, idCounter++);
        break;
    }
}

int SimpleTaskRunner::addTask(QString url, int type) {
    Task* task = new Task;
    task->setId(idCounter);
    task->setType(type);
    task->setUrl(url);
    QThread* thread = new QThread;
    tasktable.insert(idCounter, thread);
    task->moveToThread(thread);
    connect(task, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), task, SLOT(process()));
    connect(task, SIGNAL(finished(int)), thread, SLOT(quit()));
    connect(task, SIGNAL(finished(int)), task, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), this, SLOT(handleFinished()));
    return (idCounter++);
}

void SimpleTaskRunner::startTask(int id) {
    tasktable.value(id)->start();
}

void SimpleTaskRunner::stopTask(int id) {
    tasktable.value(id)->quit();
}

void SimpleTaskRunner::startAll() {
    //stub
}

void SimpleTaskRunner::stopAll() {
    //stub
}


// deprecated
void SimpleTaskRunner::run(QString url, int type) {
//    QFutureWatcher<int>* watcher = new QFutureWatcher<int>;
//    QFuture<int> result;
//    switch (type) {
//    case 1:

//        connect(watcher, SIGNAL(finished()), this, SLOT(handleFinished()));
//        result = QtConcurrent::run(this, &SimpleTaskRunner::runInnerLinks, url, idCounter++);
//        // сказать что запущено с таким id (типа тройка: урл тип айди)
//        watcher->setFuture(result);
//        break;
//    case 3:

//        connect(watcher, SIGNAL(finished()), this, SLOT(handleFinished()));
//        result = QtConcurrent::run(this, &SimpleTaskRunner::runLists, url, idCounter++);
//        // сказать что запущено с таким id
//        watcher->setFuture(result);
//        break;
//    case 4:

//        connect(watcher, SIGNAL(finished()), this, SLOT(handleFinished()));
//        result = QtConcurrent::run(this, &SimpleTaskRunner::runImages, url, idCounter++);
//        // сказать что запущено с таким id
//        watcher->setFuture(result);
//        break;
//    }
}
