#include "htmlpagegetter.h"

#include <QNetworkAccessManager>
#include <QFile>
#include <QEventLoop>

HtmlPageGetter::HtmlPageGetter(QObject *parent) : QObject(parent) {
    id = 0;
    savedUrl = "";
}

void HtmlPageGetter::start(QUrl url) {
    QNetworkAccessManager* nam = new QNetworkAccessManager(this);
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));

    /*QNetworkReply* reply = */nam->get(QNetworkRequest(url));
    // NOTE: Store QNetworkReply pointer (maybe into caller).
    // When this HTTP request is finished you will receive this same
    // QNetworkReply as response parameter.
    // By the QNetworkReply pointer you can identify request and response.
}

void HtmlPageGetter::start(QString url, int id) {
    this->id = id;
    this->savedUrl = url;
    QNetworkAccessManager* nam = new QNetworkAccessManager(this);
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
    /*QNetworkReply* reply = */nam->get(QNetworkRequest(QUrl(url)));
}

QString HtmlPageGetter::getsync(QString url) {
    QNetworkAccessManager* nam = new QNetworkAccessManager(this);
    QNetworkReply* reply = nam->get(QNetworkRequest(QUrl(url)));
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QByteArray bytes;
    if (reply->error() == QNetworkReply::NoError) {
        bytes = reply->readAll();
    } else {
        bytes = "";
    }
    return bytes;
}

void HtmlPageGetter::finished(QNetworkReply* reply) {
    // Reading attributes of the reply
    // e.g. the HTTP status code
    //QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    // Or the target URL if it was a redirect:
    //QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    // see CS001432 on how to handle this

    // no error received?
    if (reply->error() == QNetworkReply::NoError) {
        // read data from QNetworkReply here

        // Reading bytes form the reply
        QByteArray bytes = reply->readAll();  // bytes
        emit finished(QString(bytes), this->savedUrl, this->id);
    } else {
        // handle errors here
        emit error();
    }

    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    delete reply;
    QObject::sender()->deleteLater();
}

