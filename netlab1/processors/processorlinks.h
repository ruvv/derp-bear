#ifndef PROCESSORLINKS_H
#define PROCESSORLINKS_H
#include "processors/processor.h"
#include <QDomDocument>

#define sptr std::tr1::shared_ptr

class ProcessorLinks : public Processor {
    Q_OBJECT
public:
    explicit ProcessorLinks(QObject *parent = 0);
    sptr<Model> process(const QString& htmlString, QString url);
signals:
    
public slots:
    
};

#endif // PROCESSORLINKS_H
