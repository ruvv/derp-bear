#include <QCoreApplication>
#include "ftpserver.h"
#include <iostream>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    FtpServer serv;
    std::cout << "netlab3.ftpserver" << "\n";
    serv.start();
    return a.exec();
}
