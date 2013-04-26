#ifndef HRMLPAGEGETTER_H
#define HRMLPAGEGETTER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QNetworkReply>

class HtmlPageGetter : public QObject {
    Q_OBJECT

private:
    int id;
    QString savedUrl;
public:
    explicit HtmlPageGetter(QObject *parent = 0);
    void start(QUrl url);
    void start(QString url, int id);
    QString getsync(QString url);

signals:
    //void finished(const QString& htmlString);
    void finished(const QString& htmlString, QString url, int id);
    void error();
    
public slots:
    void finished(QNetworkReply* reply);

};

#endif // HRMLPAGEGETTER_H
