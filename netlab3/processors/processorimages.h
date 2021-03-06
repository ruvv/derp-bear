#ifndef PROCESSORIMAGES_H
#define PROCESSORIMAGES_H
#include "processors/processor.h"
#include "model/modelimages.h"

class ProcessorImages : public Processor {
    Q_OBJECT
public:
    explicit ProcessorImages(QObject *parent = 0);
    sptr<ModelLight> process(const QString& htmlString, QString url);
signals:
    
public slots:
    
};

#endif // PROCESSORIMAGES_H
