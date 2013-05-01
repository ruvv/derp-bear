#include "modelinputs.h"

ModelInputs::ModelInputs(QObject *parent) : ModelLight(parent) {

}

QString ModelInputs::dataToString() {
    QString result = QString("");
    for(int i = 0; i < data.size(); i++) {
        result.append(data.at(i).first);
        result.append("::");
        result.append(data.at(i).second);
        result.append("\t");
    }
    return result.trimmed();
}

QPair<QString, QString> ModelInputs::splitToPair(QString src, QString delimiter) {
    QStringList t = src.split(delimiter);
    return QPair<QString, QString>(t[0], t[1]);
}

void ModelInputs::dataFromString(QString src) {
    data.clear();
    QStringList tmp = src.split("\t");
    for(int i = 0; i < tmp.length(); i++) {
        data.append(splitToPair(tmp[i], "::"));
    }
}

QStringList ModelInputs::toStringList() {
    QStringList result;
    result.append(QString::number(type));
    result.append(url);
    result.append(datetime);
    result.append(dataToString());
    return result;
}

void ModelInputs::fromStringList(QStringList src) {
    type = src[0].toInt();
    url = src[1];
    datetime = src[2];
    dataFromString(src[3]);
}
