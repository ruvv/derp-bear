#include "processorprintscreen.h"
#include <QWebPage>
#include <QWebFrame>
#include <QPainter>
#include <QEventLoop>
#include <QDateTime>
#include <QDir>

ProcessorPrintScreen::ProcessorPrintScreen(QObject *parent) : Processor(parent) {
}

sptr<ModelLight> ProcessorPrintScreen::process(const QString& htmlString, QString url) {
    QWebPage page;
    page.mainFrame()->setHtml(htmlString);
    QEventLoop loop;
    connect(&page, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));
    loop.exec();
    page.setViewportSize(page.mainFrame()->contentsSize());

    QImage image(QSize(1000, 1000), QImage::Format_ARGB32);
    QPainter painter(&image);

    page.mainFrame()->render(&painter);

    painter.end();

    ModelPrintScreen* model = new ModelPrintScreen();
    model->setType(8);
    model->setUrl(url);
    model->setDateTime(QDateTime::currentDateTime().toString());
    model->setData(image);

    QString path = url.mid(url.indexOf("://") + 3);
    path = path.replace("*", "");
    path = path.replace("|", "");
    path = path.replace("\\", "");
    path = path.replace(":", "");
    path = path.replace("\"", "");
    path = path.replace("<", "");
    path = path.replace(">", "");
    path = path.replace("?", "");

    QDir().mkpath(path);

    QString filename = QString("printscreen.png");
    QString filepath = path + "//" + filename;

    image.save(filepath, "png");

    return sptr<ModelLight>(model);
}
