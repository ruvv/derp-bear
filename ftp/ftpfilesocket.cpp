#include "ftpfilesocket.h"

FTPFileSocket::FTPFileSocket(QObject *parent) : QTcpServer(parent) {
    mUploading = false;
    mFilename = "";
    mSocket = new QTcpSocket;
}

void FTPFileSocket::ConnectEvents() {
    try {
        connect(mSocket,SIGNAL(readyRead()),this,SLOT(SocketReadyRead()),Qt::DirectConnection);
        connect(mSocket,SIGNAL(disconnected()),this,SLOT(SocketDisconnected()),Qt::DirectConnection);
        connect(mSocket,SIGNAL(connected()),this,SLOT(SocketConnected()),Qt::DirectConnection);
    } catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in ConnectEvents()");
    }
}

bool FTPFileSocket::isConnected() {
    try {
        if(mSocket) {
            if(mSocket->state() == QTcpSocket::ConnectedState) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;>>>
        }

    } catch(QString err) {
        emit OnError(err);
        return false;
    } catch(...) {
        emit OnError("Unknown error in isConnected()");
        return false;
    }
}

void FTPFileSocket::ConnectTo(FTPPort &PortInfo) {
    try {
        mSocket = new QTcpSocket(this);
        ConnectEvents();
        qDebug() << "--   Connecting to --" << PortInfo.IPAddress() << ":" << PortInfo.Port();
        mSocket->connectToHost(PortInfo.IPAddress(),PortInfo.Port());
        mSocket->waitForConnected();
        qDebug() << "-- File Socket State --" << mSocket->state();
        qDebug() << "-- File Socket Error String --" << mSocket->errorString();
    } catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in ConnectTo()");
    }
}

void FTPFileSocket::ListenFor(FTPPort &PortInfo, QString IPAddress) {
    try {
        if(listen(QHostAddress::Any)) {
            PortInfo.SetIPAddress(IPAddress);
            PortInfo.SetPort(serverPort());
            emit OnListening();
        } else {
            emit OnError("File socket is not listening!");
        }
    } catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in ListenFor()");
    }
}

void FTPFileSocket::Upload(QString Filename, qint64 Position) {
    try {
        mUploading = true;
        mFilename = Filename;
        if(Position > 0) {
            QFile file(mFilename);
            if(!file.resize(Position)) {
                emit OnError("File could not be truncated!");
                return;
            }
        }
    } catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in Upload()");
    }
}

void FTPFileSocket::Download(QString Filename, qint64 Position) {
    try {
        mUploading = false;
        mFilename = Filename;
        QFile file(Filename);

        if(!file.open(QFile::ReadOnly)) {
            emit OnError("Could not open file!");
            return;
        }
        qDebug() << " FileSocket  " << Filename;
        if(Position > 0) {
            file.seek(Position);
        }
        while (!file.atEnd()) {
            QByteArray buffer = file.read(1024 * 8);
            SendResponse(buffer);
        }
        file.close();
        emit OnFinished();
        CloseSocket();
    } catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in Download()");
    }
}

void FTPFileSocket::incomingConnection(int socketDescriptor) {
    try {
        mSessionID = socketDescriptor;
        mSocket = new QTcpSocket(this);
        ConnectEvents();
        if(!mSocket->setSocketDescriptor(mSessionID)) {
            qDebug() << "-- File Socket --" << mSessionID << " Error binding socket: " << mSocket->errorString();
            emit OnError("Error binding socket");
        } else {
            qDebug() << "-- File Socket --" << mSessionID << " session Connected";
            emit OnConnected();
        }
        this->close();
    }
    catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in incomingConnection()");
    }
}

void FTPFileSocket::SocketReadyRead() {
    try {
        if(mUploading == true && mFilename != "") {
            QFile file(mFilename);
            if(!file.open(QFile::Append)) {
                emit OnError("Could not open file!");
                return;
            }

            QByteArray buffer = mSocket->readAll();
            file.write(buffer);
            file.close();
        }
    } catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in SocketReadyRead()");
    }
}

void FTPFileSocket::SocketConnected() {
    try {
        emit OnConnected();
    } catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in SocketConnected()");
    }
}


void FTPFileSocket::SocketDisconnected() {
    try {
        emit OnDisconnected();
        mSocket->deleteLater();
        this->deleteLater();
    } catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in SocketDisconnected()");
    }
}

void FTPFileSocket::SendResponse(QByteArray data) {
    try {
        mSocket->write(data);
    } catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in SendResponse()");
    }
}

void FTPFileSocket::SendResponse(QString data) {
    try {
       SendResponse(data.toLatin1());
    } catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in SendResponse()");
    }
}

void FTPFileSocket::SendResponse(const char* data) {
    try {
        SendResponse(QString::fromLatin1(data));
    } catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in SendResponse()");
    }
}

void FTPFileSocket::CloseSocket() {
    //mSocket->waitForDisconnected();
    mSocket->close();
}

void FTPFileSocket::LIST(QString Path) {
    try {
        if(!isConnected()) {
            qDebug() << "FILE SOCKET NOT CONNECTED";
        }
        mUploading = false;
        mFilename = "";
        qDebug() << "SENDING LIST";

        //permissions[space]number?[space]owner[space]group[space]filesize[space]date[space]filename
        QFileInfo fi(Path);

        if(!fi.exists()) {
            emit OnError("Directory not found");
        } else {
            if(fi.isDir()) {
                QDir dir(Path);
                qDebug() << "LIST SEND DIRECTORY";
                foreach(QFileInfo item, dir.entryInfoList()) {
                    FTPListItem ftpList;
                    SendResponse(ftpList.Convert(item));
                }
                emit OnFinished();
            } else {
                qDebug() << "LIST SEND FILE";
                FTPListItem ftpList;
                SendResponse(ftpList.Convert(fi));
                emit OnFinished();
            }
        }

        CloseSocket();

    } catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in LIST()");
    }
}

void FTPFileSocket::NLST(QString Path) {

    try {
        if(!isConnected()) {
            qDebug() << "FILE SOCKET NOT CONNECTED";
        }
        mUploading = false;
        mFilename = "";

        QDir dir(Path);

        if(!dir.exists()) {
            emit OnError("Directory not found");
        } else {
            qDebug() << "NLST SEND";
            foreach(QString item, dir.entryList()) {
                SendResponse(item + "\r\n");
            }
            emit OnFinished();

        }
        CloseSocket();
    } catch(QString err) {
        emit OnError(err);
    } catch(...) {
        emit OnError("Unknown error in NLST()");
    }
}





