#ifndef FTPFILESOCKET_H
#define FTPFILESOCKET_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include "ftpport.h"
#include "ftplistitem.h"

class FTPFileSocket : public QTcpServer {
    Q_OBJECT
public:
    explicit FTPFileSocket(QObject *parent = 0);
    bool isConnected();

signals:
    void OnConnected();
    void OnListening();
    void OnError(QString Message);
    void OnFinished();
    void OnDisconnected();

public slots:
    void ConnectTo(FTPPort &PortInfo);
    void ListenFor(FTPPort &PortInfo, QString IPAddress);
    void Upload(QString Filename, qint64 Position);
    void Download(QString Filename, qint64 Position);
    void LIST(QString Path);
    void NLST(QString Path);
    void SocketReadyRead();
    void SocketConnected();
    void SocketDisconnected();
    void SendResponse(QByteArray data);
    void SendResponse(QString data);
    void SendResponse(const char* data);
    void CloseSocket();

protected:
    void incomingConnection(int socketDescriptor);

private:
    QTcpSocket *mSocket;
    int mSessionID;
    bool mUploading;
    QString mFilename;

    void ConnectEvents();
};

#endif // FTPFILESOCKET_H
