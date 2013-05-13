#include "ftpserver.h"
#include <QStringList>
#include <QMetaEnum>
#include <QCryptographicHash>
#include <QDir>

FtpServer::FtpServer(QObject *parent) : QObject(parent) {
    connect(&sv, SIGNAL(newConnection()), this, SLOT(onClientConnected()));
    connect(this, SIGNAL(msg(QString)), this, SLOT(onMsg(QString)));
    mAnonymous = false;
    mAuthenticated = false;
    mUsername = "user";
    mPassword = QCryptographicHash::hash(QString("user").toLatin1(),QCryptographicHash::Sha1);
    mAccount = "";
    mRootPath = "C:/t2/";
    mCurrentPath = mRootPath;
    mIPAddress = "127.0.0.1";
    mPassive = false;
    mFilePosition = 0;
    fsc = 0;
}

void FtpServer::start(qint16 port) {
    if(!sv.listen(QHostAddress::Any, port)) {
        emit msg("error starting server");
    } else {
        emit msg(QString("server started on ") + sv.serverAddress().toString() + QString(":") + QString::number(sv.serverPort()));
        emit started();
    }
}

void FtpServer::stop() {
    sv.close();
    emit msg("server stopped");
    emit stopped();
}


void FtpServer::onClientConnected() {
    sc = sv.nextPendingConnection();
    emit msg(sc->peerAddress().toString() + QString(":") + QString::number(sc->peerPort()) + QString(" connected"));
    connect(sc, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
    connect(sc, SIGNAL(disconnected()), sc, SLOT(deleteLater()));

    connect(sc, SIGNAL(readyRead()), this, SLOT(read()));
    respond(220);
}

void FtpServer::onClientDisconnected() {
    emit msg(sc->peerAddress().toString() + QString(":") + QString::number(sc->peerPort()) + QString(" disconnected"));
}

void FtpServer::read() {
    buffer.append(sc->readAll());
    if(buffer.endsWith('\n')) {
        processCommand(buffer);
        buffer.clear();
    }
}

void FtpServer::OnFileConnected() {
    qDebug() << "FileConnected";
}

void FtpServer::OnFileListening() {
    qDebug() << "Listening on: " + mPortInfo.IPAddress() + ":" + QString::number(mPortInfo.Port());
    respond(227,"Entering Passive Mode (" + mPortInfo.ToString() + ").");
}

void FtpServer::OnFileError(QString Message) {
    qDebug() << "FileError";
    fsc->CloseSocket();
    mFilePosition = 0;
    respond(550,Message);
}

void FtpServer::OnFileFinished() {
    qDebug() << "FileFinished";
    mFilename = "";
    mFilePosition = 0;
    //fsc->deleteLater();
    //fsc = NULL;
    respond(250);
}

void FtpServer::OnFileDisconnected() {
    qDebug() << "FileDisconnected";
    respond(226, "Data transfer finished.");
    mFilePosition = 0;
    //fsc->deleteLater();
    //fsc = NULL;
}


void FtpServer::processCommand(QString command) {
    QStringList commandList = command.split("\n");
    foreach(QString c, commandList) {
        QString cmd = c.trimmed();
        if(cmd != "") {
            execute(cmd);
        }
    }
}

void FtpServer::execute(QString command) {
    QString Command = "";
    QString Arg = "";

    if(command.contains(" ")) {
        //Contains arquments
        int pos = command.indexOf(" ");
        Command = command.mid(0,pos).trimmed();
        Arg = command.mid(pos + 1).trimmed();
    } else {
        //No arquments
        Command = command.trimmed();
    }

    qDebug() << "Client: " << Command << " " << Arg;
    RequestCommands cmd = cmdStrToInt(Command);
//    QMetaObject metaObject = this->staticMetaObject;
//    int enumIndex = metaObject.indexOfEnumerator("RequestCommands");
//    QMetaEnum metaEnum = metaObject.enumerator(enumIndex);

//    switch(metaEnum.keysToValue(Command.toUpper().toStdString().data())) {
    switch(cmd) {

        case HELP: // Lists all available commands
        DoHelp();
        break;
        case QUIT: // Log out
        DoQuit();
        break;
        case USER: // Username
        DoUser(Arg);
        break;
        case PASS: // Password
        DoPass(Arg);
        break;
        case ACCT: // Account
        DoACCT(Arg);
        break;
        case CWD: // Change working directory
        DoCWD(Arg);
        break;
        case CDUP: // Change to parent directory
        DoCDUP();
        break;
        case PORT: // PORT h1,h2,h3,h4,p1,p2
        DoPORT(Arg);
        break;
        case PASV: // Passive mode
        DoPASV(Arg);
        break;
        case TYPE: // Representation Type
        DoTYPE(Arg);
        break;
        case MODE: // Transfer Mode
        DoMODE(Arg);
        break;
        case RETR: // Retrieve a file
        DoRETR(Arg);
        break;
        case STOR: // Store a file
        DoSTOR(Arg);
        break;
        case ABOR: // Abort
        DoABOR(Arg);
        break;
        case DELE: // Delete
        DoDELE(Arg);
        break;
        case PWD: // Print Working Directory
        DoPWD();
        break;
        case LIST: // List a directory
        DoLIST(Arg);
        break;
        case NLST: // Name List
        DoNLST(Arg);
        break;
        case SYST: // System
        DoSYST();
        break;
        case STAT: // Status
        DoSTAT(Arg);
        break;
        case NOOP: // No Operation
        respond(200);
        break;
        default://Command not recognized
        respond(500);
        break;
    }
}

void FtpServer::respond(int code, QString message) {
    QString data = QString::number(code) + " " + message + "\r\n";
    qDebug() << "Server: " << data;
    sc->write(data.toLatin1());
}

void FtpServer::respond(QByteArray message) {
    qDebug() << "Server: " << message;
    sc->write(message);
}

FtpServer::RequestCommands FtpServer::cmdStrToInt(QString cmd) {
    if(cmd == QString("HELP")) { return HELP; }
    if(cmd == QString("QUIT")) { return QUIT; }
    if(cmd == QString("USER")) { return USER; }
    if(cmd == QString("PASS")) { return PASS; }
    if(cmd == QString("ACCT")) { return ACCT; }

    if(cmd == QString("CWD"))  { return CWD; }
    if(cmd == QString("CDUP")) { return CDUP; }
    if(cmd == QString("PORT")) { return PORT; }
    if(cmd == QString("PASV")) { return PASV; }
    if(cmd == QString("TYPE")) { return TYPE; }

    if(cmd == QString("MODE")) { return MODE; }
    if(cmd == QString("RETR")) { return RETR; }
    if(cmd == QString("STOR")) { return STOR; }
    if(cmd == QString("ABOR")) { return ABOR; }
    if(cmd == QString("DELE")) { return DELE; }

    if(cmd == QString("PWD"))  { return PWD; }
    if(cmd == QString("LIST")) { return LIST; }
    if(cmd == QString("NLST")) { return NLST; }
    if(cmd == QString("SYST")) { return SYST; }
    if(cmd == QString("STAT")) { return STAT; }

    // NOOP for everything else
    return NOOP;
}

void FtpServer::DoHelp() {
    QString ret;
    ret.append("214 The following commands are available:");

    ret.append(" ABOR\r\n");
    ret.append(" CDUP\r\n");
    ret.append(" CWD\r\n");
    ret.append(" DELE\r\n");
    ret.append(" HELP\r\n");

    ret.append(" LIST\r\n");
    ret.append(" MODE\r\n");
    ret.append(" NLST\r\n");
    ret.append(" NOOP\r\n");
    ret.append(" PASS\r\n");

    ret.append(" PASV\r\n");
    ret.append(" PWD\r\n");
    ret.append(" QUIT\r\n");
    ret.append(" RETR\r\n");
    ret.append(" STAT\r\n");

    ret.append(" STOR\r\n");
    ret.append(" SYST\r\n");
    ret.append(" TYPE\r\n");
    ret.append(" USER\r\n");
    ret.append(" ACCT\r\n");

    ret.append(" PORT\r\n");

    respond(214, ret);
}

void FtpServer::DoQuit() {
    respond(221);
    sc->close();
}

void FtpServer::DoUser(QString arg) {
    if(mAnonymous) {
        respond(331);
        return;
    }

    if(mUsername == "") {
        respond(530, "Username has not been configured.");
        return;
    }

    if(mUsername.toUpper() != arg.toUpper()) {
        respond(530, "Username not valid.");
        return;
    }

    mUsername = arg;
    respond(331);
}

void FtpServer::DoPass(QString arg) {
    if(mAnonymous) {
        LogonUser();
        return;
    }

    QString Hash = QCryptographicHash::hash(arg.toLatin1(),QCryptographicHash::Sha1);

    if(Hash == mPassword && mUsername != "") {
        LogonUser();
    }
    else {
        respond(530);
    }
}

void FtpServer::DoACCT(QString arg) {
    if(!CheckAuthenticated()) return;

    mAccount = arg;
    respond(200);
}

void FtpServer::DoCWD(QString arg) {
    if(!CheckAuthenticated()) return;

    QString Requested = ClientPath(arg);

    if(Requested == "") {
        respond(550, "Requested path not valid.");
        return;
    }

    QDir path(Requested);
    if(!path.exists()) {
        respond(550, "Requested path not found.");
    } else {
        mCurrentPath = Requested;
        respond(250, "CWD command successful.");
    }
}

void FtpServer::DoCDUP() {
    if(!CheckAuthenticated()) return;

    if(RelativePath() != "/") {
        QDir path(mCurrentPath);
        if(path.cdUp()) {
            mCurrentPath = path.absolutePath();
            respond(250, "CDUP command successful.");
        } else {
            respond(550, "Could not change to parent");
        }
    } else {
        respond(550, "Could not change to parent");
    }
}

void FtpServer::DoPORT(QString arg) {
    if(!CheckAuthenticated()) return;

    mPortInfo.Clear();
    mPortInfo.FromString(arg);
    mPortInfo.SetIPAddress(sc->peerAddress().toString());
    mPassive = false;

    CreateFileSocket();
    respond(200);
}

void FtpServer::DoPASV(QString arg) {
    arg = arg;
    if(!CheckAuthenticated()) return;

    mPortInfo.Clear();
    mPassive = true;

    CreateFileSocket();
    fsc->ListenFor(mPortInfo,mIPAddress);
}

void FtpServer::DoTYPE(QString arg) {
    arg = arg;
    respond(200);
}

void FtpServer::DoMODE(QString arg) {
    arg = arg;
    respond(200);
}

void FtpServer::DoRETR(QString arg) {
    if(!CheckAuthenticated()) return;

    QString Requested = ClientPath(arg);
    QFile file(Requested);

    if(!file.exists()) {
        respond(450);
        return;
    }

    if(ConnectFileSocket()) {
        qDebug() << "** FileSocket RETR **";
        fsc->Download(Requested, mFilePosition);
    }
}

void FtpServer::DoSTOR(QString arg) {
    if(!CheckAuthenticated()) return;

    QString Requested = ClientPath(arg);
    QFile file(Requested);

    if(file.exists()) {
        if(!file.remove()) {
            respond(551, "File could not be overwritten");
            return;
        }
    }

    if(ConnectFileSocket()) {
        qDebug() << "** FileSocket STOR **";
        fsc->Upload(Requested, mFilePosition);
    }
}

void FtpServer::DoABOR(QString arg) {
    arg = arg;
    if(!CheckAuthenticated()) return;

    if(fsc) {
        if(fsc->isConnected() || fsc->isListening()) {
            fsc->CloseSocket();
            fsc->deleteLater();
            fsc = NULL;
            respond(226);
        } else {
            respond(226);
        }
    } else {
        respond(226);
    }
}

void FtpServer::DoDELE(QString arg) {
    if(!CheckAuthenticated()) return;

    QString Requested = ClientPath(arg);
    QFile file(Requested);

    if(file.exists()) {
        if(file.remove()) {
            respond(250);
        } else {
            respond(550,"Could not delete file!");
        }
    } else {
        respond(550,"File not found!");
    }
}

void FtpServer::DoPWD() {
    if(!CheckAuthenticated()) return;
    respond(257, "\"" + RelativePath() +"\" is the current path.");
}

void FtpServer::DoLIST(QString arg) {
    if(!CheckAuthenticated()) return;

    QString Requested;
    if(arg == "") {
        Requested = mCurrentPath;
    } else {
        Requested = ClientPath(arg);
        if(Requested == "") {
            respond(550, "Requested path not valid.");
            return;
        }
    }

    if(Requested == "") {
        respond(550, "Requested path not valid.");
        return;
    }
    if(fsc->isConnected()) {
        qDebug() << "** FileSocket LIST **";
        fsc->LIST(Requested);
    } else {
        if(ConnectFileSocket()) {
            qDebug() << "** FileSocket LIST **";
            fsc->LIST(Requested);
        }
    }
}

void FtpServer::DoNLST(QString arg) {
    if(!CheckAuthenticated()) return;

    QString Requested;
    if(arg == "") {
        Requested = mCurrentPath;
    } else {
        Requested = ClientPath(arg);
        if(Requested == "") {
            respond(550, "Requested path not valid.");
            return;
        }
    }

    if(ConnectFileSocket()) {
        qDebug() << "** FileSocket NLST **";
        fsc->NLST(Requested);
    }
}

void FtpServer::DoSYST() {
    if(!CheckAuthenticated()) return;
#ifdef Q_OS_WIN
    respond(215,"Windows");
    return;
#endif

#ifdef Q_OS_MAC
    respond(215,"Mac");
    return;
#endif

#ifdef Q_OS_UNIX
    respond(215,"Unix");
    return;
#endif

#ifdef Q_OS_LINUX
    respond(215,"Linux");
    return;
#endif

    respond(215,"Unknown");
}

void FtpServer::DoSTAT(QString arg) {
    if(!CheckAuthenticated()) return;

    //arg and no transfer
    if(arg != "") {
        respond(213, "213-status of " + arg + "\r\n");
        QString Requested = ClientPath(arg);
        QDir dir(Requested);
        if(dir.exists()) {
            foreach(QFileInfo item, dir.entryInfoList()) {
                //FTPListItem ftpList;
                //respond(ftpList.Convert(item));
            }
        } else {
            respond(213, "Not found!");
        }

        respond(213);
        return;
    }


    //no arg and transfer
    if(fsc) {
        respond(211, "Transfering data.");
        return;
    }

    //no arg and no transfer
    if(!fsc && arg == "") {
        respond(211);
        return;
    }
}

void FtpServer::LogonUser() {
    mAuthenticated = true;
    respond(230);
}

bool FtpServer::CheckAuthenticated() {
    if(!mAuthenticated) {
        respond(530);
    }
    return mAuthenticated;
}

void FtpServer::CreateFileSocket() {
    fsc = new FTPFileSocket(this);
    connect(fsc,SIGNAL(OnConnected()),this,SLOT(OnFileConnected()));
    connect(fsc,SIGNAL(OnDisconnected()),this,SLOT(OnFileDisconnected()));
    connect(fsc,SIGNAL(OnError(QString)),this,SLOT(OnFileError(QString)));
    connect(fsc,SIGNAL(OnFinished()),this,SLOT(OnFileFinished()));
    connect(fsc,SIGNAL(OnListening()),this,SLOT(OnFileListening()));
}

QString FtpServer::RelativePath() {
    QString RelPath = mCurrentPath;
    if(RelPath.toUpper() == mRootPath.toUpper()) {
        RelPath = "/";
    } else {
        RelPath = mCurrentPath.mid(mRootPath.length());
        if(RelPath.length() == 0) {
            RelPath = "/";
        }
    }
    return RelPath;
}

QString FtpServer::ClientPath(QString Requested) {
    QString temp = "";
    QString ret = "";

    if(mRootPath == "") return "";

    if(mCurrentPath == "") mCurrentPath = mRootPath;

    if(Requested == "") Requested = mCurrentPath;

    if(Requested.startsWith("/")) {
        //full path
        if(Requested == "/") {
            temp = mRootPath;
        } else {
            temp = mRootPath + Requested;
        }
    } else {
        //name only
        if(!mCurrentPath.endsWith("/")) {
            mCurrentPath.append("/");
        }
        temp = mCurrentPath + Requested;
    }

    ret = QDir::cleanPath(temp);
    qDebug() << "PATH temp = " << temp;
    qDebug() << "PATH ret = " << ret;

    QDir rootpath(temp);
    QDir retpath(ret);
    if(!retpath.absolutePath().contains(rootpath.absolutePath())) {
        ret = "";
    }

    return ret;
}

bool FtpServer::ConnectFileSocket() {
    //connect(fsc, SIGNAL(OnError(QString)), this, SLOT(onMsg(QString)));
    bool ret = false;
    if(!mPassive) {
        respond(150);
        fsc->ConnectTo(mPortInfo);
    } else {
        respond(125);
        fsc->waitForNewConnection();
    }

    if(fsc) {
        if(fsc->isConnected()) {
            qDebug() << "** FileSocket connected **";
            ret = true;
        } else {
            qDebug() << "-- FileSocket not connected --";
            qDebug() << "-- Passive -- " << mPassive;
            qDebug() << "-- Connected -- " << fsc->isConnected();
            qDebug() << "-- Listening -- " << fsc->isListening();
            respond(503, "FILE SOCKET NOT CONNECTED!");
            ret = false;
        }
    }
    return ret;
}


void FtpServer::onMsg(QString message) {
    qDebug() << message << "\n";
}
