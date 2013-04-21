#include "processorlinks.h"
#include <QUrl>
#include <QDebug>

ProcessorLinks::ProcessorLinks(QObject *parent) : Processor(parent) {

}

QStringList getLinksDirty(QString str) {
    QStringList list = str.split(QRegExp("</a>", Qt::CaseInsensitive));
    for(int i = 0; i < list.size(); i++) {
        list[i] = list[i].right( list[i].length() - list[i].indexOf(QRegExp("<a href=.+", Qt::CaseInsensitive)) ) + QString("</a>");
    }
    list = list.filter(QRegExp("^<a.*/a>$"));
    return list;
}

std::tr1::shared_ptr<ModelLight> ProcessorLinks::process(const QString &htmlString, QString url) {
    ModelLinks* model = new ModelLinks;
    model->setType(1);
    model->setUrl(url);
    model->setDateTime(QDateTime::currentDateTime().toString());
    QStringList links = getLinksDirty(htmlString);
    QString href = "";
    QString text = "";
    QString quot = "";
    for(int i = 0; i < links.size(); i++) {
        text = links[i].mid(links[i].indexOf('>') + 1, ( links[i].lastIndexOf('<') - links[i].indexOf('>') - 1 ));
        href = links[i].right( links[i].length() - links[i].indexOf("href=") - 5 );
        quot = href.at(0);
        href.remove(0, 1);
        href.remove(QRegExp(quot + QString(".*$")));
        if(QUrl(href).host().isEmpty() || QUrl(href).host() == QUrl(url).host()) {
            model->addData(href, text);
        }
    }
    sptr<ModelLight> result(model);
    return result;
}
