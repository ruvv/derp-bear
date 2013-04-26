#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QObject>
#include <QString>
#include <tr1/memory>
#include "../model/model.h"

class Serializer {
public:
    static QString serialize(std::tr1::shared_ptr<Model> model);
    static std::tr1::shared_ptr<Model> deserialize(Type type, const QString& data);

private:
    Serializer() { }
    
};

#endif // SERIALIZER_H
