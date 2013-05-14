#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QLayoutItem>
#include <QUrl>
#include <QDebug>
#include <QThread>
#include <QStringList>

#define CONNECT 0
#define LOGIN 1
#define CD 2
#define LIST 3
#define GET 4
#define PUT 5
#define CLOSE 6

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    address = QHostAddress::Null;
    login = "";
    password = "";
    commands.empty();
    path = "/";
    oldpath = "/";
    sc = NULL;
    passiveInfo = "";





    connect(&ftp, SIGNAL(listInfo(QUrlInfo)), this, SLOT(gotListItem(QUrlInfo)));
    connect(&ftp, SIGNAL(commandFinished(int,bool)), this, SLOT(gotCommandFinished(int,bool)));
    connect(&ftp, SIGNAL(commandStarted(int)), this, SLOT(gotCommandStarted(int)));
    connect(&ftp, SIGNAL(rawCommandReply(int,QString)), this, SLOT(gotRawCommandReply(int,QString)));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::gotListItem(QUrlInfo item) {
//    qDebug() << "got list item" << endl;
//    if(item.isDir()/* || item.isSymLink()*/) {
//        ui->listWidget->addItem(QString("# ") + item.name());
//    } else {
//        ui->listWidget->addItem(item.name());
//    }

}

void MainWindow::gotCommandFinished(int id, bool error) {
    QStringList tokens;
    QString schost = "";
    quint16 scport = 0;
    switch(commands.value(id)) {
    case CONNECT:
        if(!error) {
            qDebug() << "connected" << endl;
            QMessageBox::information(this, QString("inf"), QString("connected"));
            commands.insert(ftp.login(login, password), LOGIN);
        } else {
            QMessageBox::warning(this, QString("err"),
                                 QString("some error occured during connection: ") + ftp.errorString());
            ftp.abort();
            ftp.rawCommand("QUIT");
            ftp.close();
        }
        break;
    case LOGIN:
        if(!error) {
            qDebug() << "logged in" << endl;
            commands.insert(ftp.rawCommand(QString("PASV")), 10);
            //this->thread()->sleep(1000);

        } else {
            QMessageBox::warning(this, QString("err"),
                                 QString("some error occured during connection: ") + ftp.errorString());
        }
        break;
    case CD:
        if(!error) {
            qDebug() << "cd succesful" << endl;
            commands.insert(ftp.rawCommand(QString("PASV")), 10);
            //oldpath = path;
        } else {
            QMessageBox::warning(this, QString("err"),
                                 QString("some error occured during connection: ") + ftp.errorString());
            // rollback path change
            //path = oldpath;
        }
        break;
    case LIST:
        if(!error) {
            //qDebug() << "list succesful" << endl;

        } else {
            QMessageBox::warning(this, QString("err"),
                                 QString("some error occured during connection: ") + ftp.errorString());
        }
        break;
    case GET:
        if(!error) {
            qDebug() << "get succesful" << endl;
            // snippet for displaying pix in  qmessagebox
            QByteArray freshData = ftp.readAll();
            QMessageBox qmb(this);
            QLabel* ql = new QLabel(&qmb);
            QPixmap pm;
            if(pm.loadFromData(freshData)) {
                ql->setPixmap(pm);
            } else {
                ql->setText(freshData);
            }
            //pm.load("12.png");
            qmb.layout()->addWidget(ql);
            qmb.exec();
        } else {
            QMessageBox::warning(this, QString("err"),
                                 QString("some error occured during connection: ") + ftp.errorString());
        }
        break;
    case PUT:
        if(!error) {
            qDebug() << "put succesful" << endl;
        } else {
            QMessageBox::warning(this, QString("err"),
                                 QString("some error occured during connection: ") + ftp.errorString());
        }
        break;
    case CLOSE:
        if(!error) {
            qDebug() << "close succesful" << endl;
            QMessageBox::information(this, QString("inf"), QString("disconnected"));
        } else {
            QMessageBox::warning(this, QString("err"),
                                 QString("some error occured during connection: ") + ftp.errorString());
        }
        break;
    case 10:
        ui->listWidget->clear();
        sc = new QTcpSocket;
        connect(sc, SIGNAL(connected()), this, SLOT(gotSocketConnected()));
        tokens = passiveInfo.split(",");
        schost.append(tokens[0]);
        schost.append('.');
        schost.append(tokens[1]);
        schost.append('.');
        schost.append(tokens[2]);
        schost.append('.');
        schost.append(tokens[3]);
        scport = (tokens[4].toInt() << 8) + tokens[5].toInt();
        sc->connectToHost(schost, scport);
        commands.insert(ftp.rawCommand(QString("LIST")), LIST);
        break;
    default:
        qDebug() << "error commands-pool" << endl;
        QMessageBox::warning(this, QString("err"),
                                 QString("some error occured in client commands-pool"));
        break;
    }
    commands.remove(id);
}

void MainWindow::gotCommandStarted(int id) {
    switch(commands.value(id)) {
    case CONNECT:
        qDebug() << "trying to connect" << endl;
        break;
    case LOGIN:
        qDebug() << "trying to login" << endl;
        break;
    case CD:
        qDebug() << "trying to cd" << endl;
        break;
    case LIST:
        qDebug() << "trying to list" << endl;
        // clear file list in GUI
        //ui->listWidget->clear();
        break;
    case GET:
        qDebug() << "trying to get" << endl;
        break;
    case PUT:
        qDebug() << "trying to put" << endl;
        break;
    case CLOSE:
        qDebug() << "trying to close" << endl;
        break;
    default:
        qDebug() << "noone is supposed to see this :)" << endl;
        break;
    }
}

void MainWindow::gotRawCommandReply(int code, const QString &detail) {
    qDebug() << "raw reply: " << endl << code << endl << detail << endl;
    if(code == 227) {
        passiveInfo = detail.right(detail.length() - detail.indexOf(QString("(")) - 1).remove(")").remove(".");
    }
}

void MainWindow::gotListLine() {
    qDebug() << "got list lines from reserve socket: ";
    QByteArray data;
    data = sc->readAll();
    QStringList lines = QString(data).split("\r\n");
    for(int i = 0; i < lines.length(); i++) {
        if(lines[i].startsWith("d")) {
            lines[i] = lines[i].right(lines[i].length() - 61);
            lines[i].prepend("# ");
            lines[i] = lines[i].trimmed();
        } else {
            lines[i] = lines[i].right(lines[i].length() - 61);
            lines[i] = lines[i].trimmed();
        }
    }
    for(int i = 0; i < lines.size() - 1; i++) {
        ui->listWidget->addItem(lines[i]);
    }
    qDebug() << data << endl;
}

void MainWindow::gotSocketConnected() {
    qDebug() << "reserve socket connected";
    connect(sc, SIGNAL(readyRead()), this, SLOT(gotListLine()));
    connect(sc, SIGNAL(disconnected()), this, SLOT(gotSocketDisconnected()));
}

void MainWindow::gotSocketDisconnected() {
    sc->deleteLater();
}

void MainWindow::on_pushButton_clicked() {
    // connect button
    address = QHostAddress(ui->lineEdit->text());
    if(address.isNull()) {
        QMessageBox::warning(this, QString("err"), QString("no host address given"));
        return;
    }
    port = 21;
    login = ui->lineEdit_2->text();
    password = ui->lineEdit_3->text();
    //if(ftp.state() != QFtp::Unconnected) {
        commands.insert(ftp.connectToHost(address.toString(), port), CONNECT);
    //} else {

    //}

}

void MainWindow::on_pushButton_4_clicked() {
    // disconnect button
    ftp.abort();

    commands.insert(ftp.close(), CLOSE);

}

void MainWindow::on_pushButton_2_clicked() {
    // new task button
    QString task = QInputDialog::getText(this, QString("input"), QString("input format: \"variant<space>url\""));
    commands.insert(ftp.put(task.toLatin1(), /*path + */QString("AWFUL.task")), PUT);
}

void MainWindow::on_listWidget_currentTextChanged(const QString &currentText) {
    // click on list element
    // @currentText - selected element text
    if(currentText.isEmpty()) {
        return;
    }
    if(currentText.startsWith(QString("#"))) {
        commands.insert(ftp.cd(currentText.right(currentText.length() - 2)), CD);
        //path = path + QString("/") + currentText;
        //commands.insert(ftp.list(currentText), LIST);
    } else {
        qDebug() << "retr " << currentText << endl;
        commands.insert(ftp.get(/*path + QString("/") + */currentText), GET);
    }
}

#undef CONNECT
#undef LOGIN
#undef CD
#undef LIST
#undef GET
#undef PUT
#undef CLOSE
