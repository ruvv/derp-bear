#include "processorlists.h"

ProcessorLists::ProcessorLists(QObject *parent) : Processor(parent) {

}

QStringList getListsDirty(QString str) {
    QStringList list = str.split(QRegExp("(</ul>|</ol>)", Qt::CaseInsensitive));
    for(int i = 0; i < list.size(); i++) {
        if(list[i].endsWith(QString("</ul>"))) {
            list[i] = list[i].right( list[i].length() - list[i].indexOf(QRegExp("<ul.+", Qt::CaseInsensitive)) ) + QString("</ul>");
        } else if (list[i].endsWith(QString("</ol>"))) {
            list[i] = list[i].right( list[i].length() - list[i].indexOf(QRegExp("<ol.+", Qt::CaseInsensitive)) ) + QString("</ol>");
        }

    }
    list = list.filter(QRegExp("^(<ul.*/ul>|<ol.*/ol>)$"));
    return list;
}

std::tr1::shared_ptr<ModelLight> ProcessorLists::process(const QString &htmlString, QString url) {
    ModelLists* model = new ModelLists;
    model->setType(3);
    model->setUrl(url);
    model->setDateTime(QDateTime::currentDateTime().toString());
    QStringList lists = getListsDirty(htmlString);
    for(int i = 0; i < lists.length(); i++) {

    }
    sptr<ModelLight> result(model);
    return result;
}
