#include "innerlinks.h"
#include <QStringList>

InnerLinks::InnerLinks(QObject* parent, QUrl src) {
    this->setParent(parent);
    dateTime = QDateTime::currentDateTime();
    type = TypeQ1;
    url = src;
}

Model::Type InnerLinks::getType() {
    return type;
}

QString InnerLinks::serialize() {
    QString result = "";
    result += "type=";
    result += type;
    result += "\t";
    result += "datetime'";
    result += dateTime.toString();
    result += "\t";
    result += "url=";
    result += url.toEncoded();
    result += "\t";
    for(QList<ILNode>::ConstIterator i = data.constBegin(); i == data.constEnd(); i++) {
        result += "addr=";
        result += i->addr;
        result += "\t";
        result += "text=";
        result += i->text;
        result += "\t";
    }
    return result;
}

void InnerLinks::deserialize(QString src) {
    QStringList splitted = src.split('\t');
    // возможно надо срезать последний
    type = TypeQ1;
    dateTime = QDateTime::fromString(splitted[1].remove(QRegExp("^datetime=")));
    url = QUrl::fromEncoded(splitted[2].remove(QRegExp("^url=")).toLatin1());
    ILNode node;
    for(int i = 3; i < splitted.length(); i += 2) {
        node.addr = splitted[i].remove(QRegExp("^addr="));
        node.text = splitted[i + 1].remove(QRegExp("^text="));;
        data.append(node);
    }
}
