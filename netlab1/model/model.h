#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QDateTime>
#include <QUrl>

typedef enum Type {
    TypeQ1, TypeQ3, TypeQ4, TypeQ8, TypeQ9
} Type;

class Model : public QObject {
    Q_OBJECT

public:
    QDateTime dateTime;
    QUrl url;

    explicit Model(QObject* parent = 0);

    virtual Type getType() = 0;

};

#endif // MODEL_H
