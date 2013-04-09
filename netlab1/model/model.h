#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QUrl>

typedef enum Type {
    Q1, Q3, Q4, Q8, Q9
} Type;

class Model : public QObject {
    Q_OBJECT

public:
    Type type;
    QDateTime dateTime;
    QUrl url;

    explicit Model(QObject* parent = 0);

    virtual QString serialize() = 0;
    virtual void deserialize(const QString& str) = 0;

};

#endif // MODEL_H
