#ifndef SIMPLETASKRUNNER_H
#define SIMPLETASKRUNNER_H

#include <QObject>
#include <QString>
#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>

class SimpleTaskRunner : public QObject {
    Q_OBJECT
public:
    explicit SimpleTaskRunner(QObject *parent = 0);
    void run(QString url, int type);

private:
    int idCounter;

    int runInnerLinks(QString url, int id);
    int runLists(QString url, int id);
    int runImages(QString url, int id);
    
signals:
    
public slots:
    void handleFinished();
    int proceedLinks(QString html, QString url, int id);
};

#endif // SIMPLETASKRUNNER_H
