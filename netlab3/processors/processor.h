#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include <QString>
#include <tr1/memory>
#include "../model/modellight.h"
#define sptr std::tr1::shared_ptr

class Processor : public QObject {
    Q_OBJECT

public:
    explicit Processor(QObject* parent = 0);

    virtual sptr<ModelLight> process(const QString& htmlString, QString url) = 0;

};

#endif // PROCESSOR_H
