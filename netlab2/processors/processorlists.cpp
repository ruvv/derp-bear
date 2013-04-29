#include "processorlists.h"
#include <QDateTime>

ProcessorLists::ProcessorLists(QObject *parent) : Processor(parent) {

}

QStringList getListsDirty(QString str) {
    QStringList list = str.split(QRegExp("(</ul>|</ol>)", Qt::CaseInsensitive));
    for(int i = 0; i < list.size(); i++) {
        list[i] = list[i].right( list[i].length() - list[i].indexOf(QRegExp("(<ul.+|<ol.+)", Qt::CaseInsensitive)) ) + QString("</");
        list[i].append(list[i].at(1));
        list[i].append("l>");
    }
    list = list.filter(QRegExp("^(<ul.*/ul>|<ol.*/ol>)$"));
    for(int i = 0; i < list.size(); i++) {
        list[i].remove(0, list[i].indexOf("<li"));
        list[i].remove(list[i].lastIndexOf("</li>") + 5, list[i].length() - list[i].lastIndexOf("</li>") - 5);
    }
    list.length();
    return list;
}

std::tr1::shared_ptr<ModelLight> ProcessorLists::process(const QString &htmlString, QString url) {
    ModelLists* model = new ModelLists;
    model->setType(3);
    model->setUrl(url);
    model->setDateTime(QDateTime::currentDateTime().toString());
    QStringList lists = getListsDirty(htmlString);
    QStringList tmp;
    for(int i = 0; i < lists.length(); i++) {
        tmp = lists[i].split(QRegExp("</li>"));
        for(int j = 0; j < tmp.length(); j++) {
            tmp[j].remove(0, tmp[j].indexOf(">") + 1);
            tmp[j].remove(QRegExp("(<ul|<ol|</ul>|</ol>)"));
            tmp[j].remove(QRegExp("<li>|</li>"));
        }
        if(!tmp.isEmpty() && tmp.last().isEmpty()) {
            tmp.removeLast();
        }
        model->addData(tmp);
    }
    sptr<ModelLight> result(model);
    return result;
}
