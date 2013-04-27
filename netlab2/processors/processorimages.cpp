#include "processorimages.h"
#include <QNetworkAccessManager>
#include <QFile>
#include <QEventLoop>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <http/htmlpagegetter.h>

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
    for(int i = 0; i < images.size(); i++) {
        if(QUrl(images[i]).isRelative()) {
            images[i] = QUrl(url).host() + QString("/") + images[i];
        }
    }
    //  todo: скачать картинки и сунуть их в модель
    QNetworkAccessManager* nam = new QNetworkAccessManager();
    QNetworkReply* reply;
    QEventLoop loop;

    QByteArray bytes;
    QFile savefile;
    HtmlPageGetter hpg;
    for(int i = 0; i < images.size(); i++) {
//        reply = nam->get(QNetworkRequest(QUrl(images.at(i))));
//        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
//        loop.exec();
//        if (reply->error() == QNetworkReply::NoError) {
//            bytes = reply->readAll();
//        } else {
//            bytes = "";
//        }
//        model->addData(bytes);
//        savefile.setFileName(QString("image") + QString::number(i) + QString(".") + images.at(i).right(3));
//        savefile.open(QIODevice::WriteOnly);
//        savefile.write(bytes);
//        savefile.close();
        bytes = hpg.getsync(images.at(i)).toLatin1();
        model->addData(bytes);
        savefile.setFileName(QString("image") + QString::number(i) + QString(".") + images.at(i).right(3));
        savefile.open(QIODevice::WriteOnly);
        savefile.write(bytes);
        savefile.close();

    }

    sptr<ModelLight> result(model);
    return result;
}
