#include "modelprintscreen.h"
#include <QBuffer>

ModelPrintScreen::ModelPrintScreen(QObject *parent) : ModelLight(parent) {
}

QString ModelPrintScreen::dataToString() {
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    data.save(&buffer, "PNG");
    QByteArray arr = qCompress(buffer.buffer(), 5);
    QString str = arr.toBase64();
    return str;
}

void ModelPrintScreen::dataFromString(QString src) {
    QByteArray ba = QByteArray::fromBase64(QByteArray().append(src));
    QBuffer buffer(&ba);
    data.load(&buffer, "PNG");
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
