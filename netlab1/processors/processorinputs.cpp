#include "processorinputs.h"
#include <QUrl>
#include <QDebug>

ProcessorInputs::ProcessorInputs(QObject *parent) : Processor(parent) {

}

QStringList getInputsDirty(QString str) {
    QStringList list = str.split(QRegExp("<input", Qt::CaseInsensitive));
    list.pop_front();
    for(int i = 0; i < list.size(); i++) {
        list[i] = QString("<input") + list[i].left(list[i].indexOf(QRegExp(">", Qt::CaseInsensitive) + 1));
    }
    return list;
}

std::tr1::shared_ptr<ModelLight> ProcessorInputs::process(const QString &htmlString, QString url) {
    ModelInputs* model = new ModelInputs;
    model->setType(1);
    model->setUrl(url);
    model->setDateTime(QDateTime::currentDateTime().toString());
    QStringList inputs = getInputsDirty(htmlString);
    for(int i = 0; i < inputs.size(); i++) {
        model->addData("", inputs[i]);
    }
    sptr<ModelLight> result(model);
    return result;
}
