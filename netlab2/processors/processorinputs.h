#ifndef PROCESSORINPUTS_H
#define PROCESSORINPUTS_H

#include "processors/processor.h"
#include "model/modelinputs.h"
#define sptr std::tr1::shared_ptr

class ProcessorInputs : public Processor {
    Q_OBJECT
public:
    explicit ProcessorInputs(QObject *parent = 0);
    sptr<ModelLight> process(const QString& htmlString, QString url);
signals:

public slots:

};

#endif // PROCESSORINPUTS_H
