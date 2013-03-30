#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include <QString>
#include <tr1/memory>
#include "../model/model.h"

class Processor : public QObject {
    Q_OBJECT

public:
    explicit Processor(QObject* parent = 0);

    virtual std::tr1::shared_ptr<Model> process(const QString& htmlString) = 0;

};

#endif // PROCESSOR_H
