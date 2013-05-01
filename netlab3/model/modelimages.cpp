#include "modelimages.h"

ModelImages::ModelImages(QObject *parent) : ModelLight(parent) {

}

QString ModelImages::dataToString() {
    QString result;
    for(int i = 0; i < data.size(); i++) {
        result.append(data.at(i));
        result.append("\t\t\t\t\t");
    }
    result.chop(5);
    return result;
}

void ModelImages::dataFromString(QString src) {
    data.clear();
    QStringList tmp = src.split("\t\t\t\t\t");
    for(int i = 0; i < tmp.size(); i++) {
        data.append(tmp.at(i).toLatin1());
    }

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
