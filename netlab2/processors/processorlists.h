#ifndef PROCESSORLISTS_H
#define PROCESSORLISTS_H
#include "processors/processor.h"
#include "model/modellists.h"
#define sptr std::tr1::shared_ptr

class ProcessorLists : public Processor
{
    Q_OBJECT
public:
    explicit ProcessorLists(QObject *parent = 0);
    sptr<ModelLight> process(const QString& htmlString, QString url);
signals:
    
public slots:
    
};

#endif // PROCESSORLISTS_H
