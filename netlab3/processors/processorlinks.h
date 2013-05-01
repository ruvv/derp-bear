#ifndef PROCESSORLINKS_H
#define PROCESSORLINKS_H
#include "processors/processor.h"
#include "model/modellinks.h"

class ProcessorLinks : public Processor {
    Q_OBJECT
public:
    explicit ProcessorLinks(QObject *parent = 0);
    sptr<ModelLight> process(const QString& htmlString, QString url);
signals:
    
public slots:
    
};

#endif // PROCESSORLINKS_H
