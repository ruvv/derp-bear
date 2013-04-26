#ifndef MODELIMAGES_H
#define MODELIMAGES_H
#include "model/modellight.h"
#include <QStringList>
#include <QByteArray>

class ModelImages : public ModelLight {
    Q_OBJECT
protected:
    QByteArray data;
    QString dataToString();
    void dataFromString(QString);
public:
    explicit ModelImages(QObject *parent = 0);
    
    QStringList toStringList();
    void fromStringList(QStringList);

    void setType(int x) {type = x;}
    void setDateTime(QString x) {datetime = x;}
    void setUrl(QString x) {url = x;}
    void addData(QByteArray x) {data = x;}

signals:
    
public slots:
    
};

#endif // MODELIMAGES_H
