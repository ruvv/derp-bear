#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QDateTime>
#include <QUrl>

class Model : public QObject {
    Q_OBJECT

public:
    enum Type {
        TypeQ1, TypeQ3, TypeQ4, TypeQ8, TypeQ9
    };

    explicit Model(QObject* parent = 0);
    virtual Model::Type getType() = 0;

protected:
    QDateTime dateTime;
    QUrl url;
    Model::Type type;

private:

};

#endif // MODEL_H
