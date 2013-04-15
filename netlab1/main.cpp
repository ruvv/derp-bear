#include <QtWidgets/QApplication>
#include "gui/mainwindow.h"
#include "processors/processorlinks.h"
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    ProcessorLinks pl;
    QFile test("test.txt");
    if(!test.open(QIODevice::ReadOnly)) {
        qDebug() << "not opened";
    }
    pl.process(test.readAll(), "http://www.w3.org/TR/CSS2/selector.html#type-selectors");
    return a.exec();
}
