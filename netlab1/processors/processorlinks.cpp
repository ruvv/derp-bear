#include "processorlinks.h"
#include "model/modellinks.h"
#include <QDomNode>
#include <QUrl>
#include <QDebug>

ProcessorLinks::ProcessorLinks(QObject *parent) : Processor(parent) {

}

std::tr1::shared_ptr<Model> ProcessorLinks::process(const QString &htmlString, QString url) {

    sptr<ModelLinks> result(new ModelLinks);
    result->setType(1);
    result->setDateTime(QDateTime::currentDateTime().toString());
    result->setUrl(url);


//    QDomDocument doc;
//    if(!doc.setContent(htmlString, &err)) {
//        qDebug() << "not parsed";
//    }
//    QDomNodeList links = doc.elementsByTagName("a");

//    QString domain = QUrl(url).host();

//    QString href, text;

//    for(int i = 0; i < links.length(); i++) {
//        href = links.at(i).toElement().attribute("href", "");
//        if(QUrl(href).host() == domain) {
//            text = links.at(i).toElement().text();
//            result->addData(href, text);
//        }
//    }
    //ModelLinks ml = *(result.get());
    return std::tr1::dynamic_pointer_cast<Model>(result);
}
