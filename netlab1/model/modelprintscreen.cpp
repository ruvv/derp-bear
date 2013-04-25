#include "modelprintscreen.h"
#include <QFile>

ModelPrintScreen::ModelPrintScreen(QObject *parent) : ModelLight(parent) {
}

QString ModelPrintScreen::dataToString() { 
    data.save(QString("img.png"), "PNG");
    QFile file("img.png");
    file.open(QIODevice::ReadOnly);
    QByteArray arr = file.readAll();
    file.close();
    return QString(arr.toBase64());
}

void ModelPrintScreen::dataFromString(QString src) {
    QFile file("img.png");
    file.open(QIODevice::WriteOnly);
    file.write(QByteArray::fromBase64(QByteArray().append(src)));
    file.close();
    data.load(QString("img.png"), "PNG");
}

QStringList ModelPrintScreen::toStringList() {
    QStringList result;
    result.append(QString::number(type));
    result.append(url);
    result.append(datetime);
    result.append(dataToString());
    return result;
}

void ModelPrintScreen::fromStringList(QStringList src) {
    type = src[0].toInt();
    url = src[1];
    datetime = src[2];
    dataFromString(src[3]);
}
