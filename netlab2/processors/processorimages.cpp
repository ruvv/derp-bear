#include "processorimages.h"

ProcessorImages::ProcessorImages(QObject *parent) : Processor(parent) {

}

QStringList getImagesDirty(QString str) {
    QStringList list;
    list = str.split(QRegExp("<img"));
    for(int i = 0; i < list.length(); i++) {
        list[i] = list[i].right( list[i].length() - list[i].indexOf(QRegExp("src=\"")) - 5 );
        list[i].chop(list[i].length() - list[i].indexOf(QRegExp("\"")));
        if(list[i].endsWith(".js")) {
            list[i].clear();
        }
    }
    return list.filter(QRegExp(".+"));
}

std::tr1::shared_ptr<ModelLight> ProcessorImages::process(const QString &htmlString, QString url) {
    ModelImages* model = new ModelImages;
    model->setType(4);
    model->setUrl(url);
    model->setDateTime(QDateTime::currentDateTime().toString());
    QStringList images = getImagesDirty(htmlString);
    //  todo: скачать картинки и сунуть их в модель

    sptr<ModelLight> result(model);
    return result;
}
