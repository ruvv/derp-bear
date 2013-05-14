#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include "qftp.h"
#include <QPixmap>
#include <QInputDialog>
#include <QMessageBox>
#include <QHostAddress>
#include <QString>
#include <QMap>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void gotListItem(QUrlInfo item);
    void gotCommandFinished(int id, bool error);
    void gotCommandStarted(int id);
    void gotRawCommandReply(int code, const QString& detail);
    void gotListLine();
    void gotSocketConnected();
    void gotSocketDisconnected();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_currentTextChanged(const QString &currentText);

private:
    Ui::MainWindow *ui;
    QFtp ftp;
    QHostAddress address;
    QString login;
    QString password;
    int port;
    QTcpSocket* sc;

    QMap<int, int> commands;

    QString path;
    QString oldpath;

    QString passiveInfo;
};

#endif // MAINWINDOW_H
