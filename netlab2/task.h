#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QString>

#include "model/modellight.h"
#include "model/modelimages.h"
#include "model/modelinputs.h"
#include "model/modellinks.h"
#include "model/modellists.h"
#include "model/modelprintscreen.h"

#include "processors/processor.h"
#include "processors/processorimages.h"
#include "processors/processorinputs.h"
#include "processors/processorlinks.h"
#include "processors/processorlists.h"
#include "processors/processorprintscreen.h"

class Task : public QObject {
    Q_OBJECT
private:
    int id;
    int type;
    QString url;
    ModelLight* model;
    Processor* processor;
public:
    explicit Task(QObject *parent = 0);
    ~Task();
    void setType(int nType);
    void setUrl(QString nUrl) { url = nUrl; }
    void setId(int nId) { id = nId; }

    int getType() { return type; }
    QString getUrl() {return url; }
    int getId() { return id; }
    
signals:
    void started();
    void finished();
    void error(QString);
public slots:
    void process(QString url);
};

#endif // TASK_H
