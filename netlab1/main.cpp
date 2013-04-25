#include <QtWidgets/QApplication>
#include "gui/mainwindow.h"
#include "processors/processorlinks.h"
#include <QFile>
#include <QDebug>
#include "simpletaskrunner.h"
#include "http/htmlpagegetter.h"
#include <QUrl>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    ProcessorLinks pl;
//    QFile test("test.txt");
//    if(!test.open(QIODevice::ReadOnly)) {
//        qDebug() << "not opened";
//    }
//    sptr<ModelLight> model(pl.process(test.readAll(), "http://qt-project.org/doc/qt-4.8/qstringlist.html#filter-2"));
//    QStringList links = model->toStringList();
//    ModelLight* newmodel = new ModelLinks;
//    newmodel->fromStringList(links);
//    int t = 0;
//    delete newmodel;

//    HtmlPageGetter hpg;
//    hpg.start("http://rubyonrails.org/", 1);

    SimpleTaskRunner str;
    str.run("http://htmlbook.ru/html/ol", 3);

    return a.exec();
}
