//#include <QtWidgets/QApplication>
//#include "gui/mainwindow.h"

#include <QCoreApplication>
#include "ftp/ftpserver.h"
#include "simpletaskrunner.h"
#include <iostream>

int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
    QCoreApplication a(argc, argv);

    SimpleTaskRunner taskRunner;

    FtpServer serv;
    std::cout << "netlab3.ftpserver" << "\n";

    QObject::connect(&serv, SIGNAL(uploadTaskFileFinished(QString)), &taskRunner, SLOT(onUploadTaskFileFinished(QString)));

    serv.start();

    return a.exec();
}
