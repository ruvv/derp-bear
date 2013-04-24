#ifndef MODELPRINTSCREEN_H
#define MODELPRINTSCREEN_H
#include "../model/modellight.h"
#include <QImage>
#include <QStringList>

class ModelPrintScreen : public ModelLight {
    Q_OBJECT
protected:
    QImage data;
    QString dataToString();
    void dataFromString(QString);
public:
    explicit ModelPrintScreen(QObject *parent = 0);

    QStringList toStringList();
    void fromStringList(QStringList);

    void setType(int x) {type = x;}
    void setDateTime(QString x) {datetime = x;}
    void setUrl(QString x) {url = x;}
    void setData(QImage x) {data = x;}
};

#endif // MODELPRINTSCREEN_H
