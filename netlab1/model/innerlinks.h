#ifndef INNERLINKS_H
#define INNERLINKS_H
#include "model/model.h"
#include <QList>

class InnerLinks : public Model {
public:
    struct ILNode {
        QString addr;
        QString text;
    };

    InnerLinks(QObject* parent = 0, QUrl src = QUrl(""));
    Model::Type getType();
    QString serialize();
    void deserialize(QString src);

protected:
    QList<ILNode> data;
private:

};

#endif // INNERLINKS_H
