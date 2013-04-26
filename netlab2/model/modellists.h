#ifndef MODELLISTS_H
#define MODELLISTS_H
#include "model/modellight.h"
#include <QVector>
#include <QStringList>

class ModelLists : public ModelLight {
    Q_OBJECT
protected:
    QVector<QVector<QString> > data;
    QString dataToString();
    void dataFromString(QString);
public:
    explicit ModelLists(QObject *parent = 0);

    QStringList toStringList();
    void fromStringList(QStringList);

    void setType(int x) {type = x;}
    void setDateTime(QString x) {datetime = x;}
    void setUrl(QString x) {url = x;}
    void addData(QVector<QString> x) {data.append(x);}
    void addData(QStringList x) {data.append(x.toVector());}
    
signals:
    
public slots:
    
};

#endif // MODELLISTS_H
