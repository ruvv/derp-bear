#include "processorprintscreen.h"
#include <QWebPage>
#include <QWebFrame>
#include <QPainter>

ProcessorPrintScreen::ProcessorPrintScreen(QObject *parent) : Processor(parent) {
}

sptr<ModelLight> ProcessorPrintScreen::process(const QString &htmlString, QString url) {
    QWebPage page;
    page.mainFrame()->setHtml(htmlString);
    page.setViewportSize(page.mainFrame()->contentsSize());

    QImage image(page.viewportSize(), QImage::Format_ARGB32);
    QPainter painter(&image);

    page.mainFrame()->render(&painter);

    painter.end();

    ModelPrintScreen* model = new ModelPrintScreen();
    model->setType(8);
    model->setUrl(url);
    model->setDateTime(QDateTime::currentDateTime().toString());
    model->setData(image);

    return sptr<ModelLight>(model);
}
