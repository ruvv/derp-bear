#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QString>

class Model : public QObject {
    Q_OBJECT

public:
    explicit Model(QObject* parent = 0);

    virtual QString serialize() = 0;
    virtual void deserialize(const QString& str) = 0;

};

#endif // MODEL_H
