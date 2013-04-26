#include "modelimages.h"

ModelImages::ModelImages(QObject *parent) : ModelLight(parent) {

}

QString ModelImages::dataToString() {
    return data;
}

void ModelImages::dataFromString(QString src) {
    data = src.toLatin1();
}

QStringList ModelImages::toStringList() {
    QStringList result;
    result.append(QString::number(type));
    result.append(url);
    result.append(datetime);
    result.append(dataToString());
    return result;
}

void ModelImages::fromStringList(QStringList src) {
    type = src[0].toInt();
    url = src[1];
    datetime = src[2];
    dataFromString(src[3]);
}
