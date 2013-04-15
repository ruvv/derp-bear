#include "modellinks.h"

ModelLinks::ModelLinks(QObject *parent) : ModelLight(parent) {

}

QString ModelLinks::dataToString() {
    QString result = QString("");
    for(QVector<QPair<QString, QString> >::ConstIterator i = data.constBegin(); i == data.constEnd(); i++) {
        result.append(i->first);
        result.append("::");
        result.append(i->second);
        result.append("\t");
    }
    return result.trimmed();
}

QPair<QString, QString> splitToPair(QString src, QString delimiter) {
    QStringList t = src.split(delimiter);
    return QPair<QString, QString>(t[0], t[1]);
}

void ModelLinks::dataFromString(QString src) {
    data.clear();
    QStringList tmp = src.split("\t");
    for(int i = 0; i < tmp.length(); i++) {
        data.append(splitToPair(tmp[i], "::"));
    }
}

QStringList ModelLinks::toStringList() {
    QStringList result;
    result.append(QString::number(type));
    result.append(url);
    result.append(datetime);
    result.append(dataToString());
    return result;
}

void ModelLinks::fromStringList(QStringList src) {
    type = src[0].toInt();
    url = src[1];
    datetime = src[2];
    dataFromString(src[3]);
}
