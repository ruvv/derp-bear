#ifndef MODELLINKS_H
#define MODELLINKS_H
#include "model/modellight.h"
#include <QVector>
#include <QPair>
#include <QStringList>

class ModelLinks : public ModelLight {
    Q_OBJECT
protected:
    QVector<QPair<QString, QString> > data;
    QString dataToString();
    void dataFromString(QString);
public:
    explicit ModelLinks(QObject *parent = 0);

    QStringList toStringList();
    void fromStringList(QStringList);

    void setType(int x) {type = x;}
    void setDateTime(QString x) {datetime = x;}
    void setUrl(QString x) {url = x;}
    void addData(QPair<QString, QString> x) {data.append(x);}
    void addData(QString x, QString y) {data.append(QPair<QString, QString>(x,y));}
signals:
    
public slots:
    
};

#endif // MODELLINKS_H
