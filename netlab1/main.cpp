//#include <QCoreApplication>
#include <QtWidgets/QApplication>
#include <QTextStream>
#include "gui/mainwindow.h"
#include "processors/processorlinks.h"
#include "simpletaskrunner.h"
#include "http/htmlpagegetter.h"

int main(int argc, char *argv[]) {
    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    QTextStream qin(stdin, QIODevice::ReadOnly);
    QTextStream qout(stdout, QIODevice::WriteOnly);

    QString url;
    qint32 var;

    qout << "Write url:";
    endl(qout);
    url = qin.readLine();

    qout << "Write variant(1, 3, 4, 8, 9)";
    endl(qout);
    qin >> var;

    SimpleTaskRunner str;
    str.runsync(url, var);

    qout << "Complete";
    endl(qout);
    endl(qout);
    qout << "ENTER to exit";
    endl(qout);

    qin.readLine();
    a.exit();
}
