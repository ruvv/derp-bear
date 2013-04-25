#include "modellists.h"

ModelLists::ModelLists(QObject *parent) : ModelLight(parent) {

}

QStringList ModelLists::toStringList() {
    QStringList result;
    result.append(QString::number(type));
    result.append(url);
    result.append(datetime);
    result.append(dataToString());
    return result;
}

void ModelLists::fromStringList(QStringList src) {
    type = src[0].toInt();
    url = src[1];
    datetime = src[2];
    dataFromString(src[3]);
}


QString ModelLists::dataToString() {
    QString result = QString("");
    for(int i = 0; i < data.size(); i++) {
        for(int j = 0; j < data[i].size(); j++) {
            result.append(data[i][j]);
            result.append("::");
        }
        result.append("\t");
    }
    return result.trimmed();
}

QVector<QString> splitToVector(QString src, QString delimiter) {
    QStringList t = src.split(delimiter);
    return t.toVector();
    // может появиться лишний пустой элемент в конце
}

void ModelLists::dataFromString(QString src) {
    data.clear();
    QStringList tmp = src.split("\t");
    for(int i = 0; i < tmp.length(); i++) {
        data.append(splitToVector(tmp[i], "::"));
    }
}
