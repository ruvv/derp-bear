#ifndef PROCESSORPRINTSCREEN_H
#define PROCESSORPRINTSCREEN_H
#include "processors/processor.h"
#include "model/modelprintscreen.h"

class ProcessorPrintScreen : public Processor {
    Q_OBJECT
public:
    explicit ProcessorPrintScreen(QObject *parent = 0);
    sptr<ModelLight> process(const QString& htmlString, QString url);
signals:
    
public slots:
    
};

#endif // PROCESSORPRINTSCREEN_H
