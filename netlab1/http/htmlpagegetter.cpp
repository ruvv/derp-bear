#include "htmlpagegetter.h"

#include <QNetworkAccessManager>
#include <QFile>

HtmlPageGetter::HtmlPageGetter(QObject *parent) : QObject(parent) {
}

void HtmlPageGetter::start(QUrl url) {
    QNetworkAccessManager* nam = new QNetworkAccessManager(this);
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));

    QNetworkReply* reply = nam->get(QNetworkRequest(url));
    // NOTE: Store QNetworkReply pointer (maybe into caller).
    // When this HTTP request is finished you will receive this same
    // QNetworkReply as response parameter.
    // By the QNetworkReply pointer you can identify request and response.
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
        emit finished(QString(bytes));
    } else {
        // handle errors here
        emit error();
    }

    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    delete reply;
}
