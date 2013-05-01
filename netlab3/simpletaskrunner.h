#ifndef SIMPLETASKRUNNER_H
#define SIMPLETASKRUNNER_H

#include <QObject>
#include <QString>
#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>
#include <QMap>

class SimpleTaskRunner : public QObject {
    Q_OBJECT
public:
    explicit SimpleTaskRunner(QObject *parent = 0);
    void runsync(QString url, int type);

    int addTask(QString url, int type);
    void startTask(int id);
    void stopTask(int id);
    void startAll();
    void stopAll();

private:
    int idCounter;
    QMap<int, QThread*> tasktable;

    int runInnerLinks(QString url, int id);
    int runLists(QString url, int id);
    int runImages(QString url, int id);
    int runPrintScreen(QString url, int id);
    int runInputs(QString url, int id);
    
signals:
    void taskFinished(int);
    void errmsg(QString);
    
public slots:
    void handleFinished();
    int proceedLinks(QString html, QString url, int id);
    void errorString(QString);
};

#endif // SIMPLETASKRUNNER_H
