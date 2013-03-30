#ifndef HRMLPAGEGETTER_H
#define HRMLPAGEGETTER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QNetworkReply>

class HtmlPageGetter : public QObject {
    Q_OBJECT

public:
    explicit HtmlPageGetter(QObject *parent = 0);
    void start(QUrl url);

signals:
    void finished(const QString& htmlString);
    void error();
    
public slots:
    void finished(QNetworkReply* reply);

};

#endif // HRMLPAGEGETTER_H
