#ifndef FTPSERVER_H
#define FTPSERVER_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>

#include <QByteArray>
#include <QString>

#include "ftpport.h"
#include "ftpfilesocket.h"

class FtpServer : public QObject {
    Q_OBJECT
private:

    enum RequestCommands {
        // RFC 959  -complete
        HELP,               //! Lists all available commands
        QUIT,               //! Log out
        USER,               //! Username
        PASS,               //! Password
        ACCT,               //! Account

        CWD,                //! Change working directory
        CDUP,               //! Change to parent directory
        PORT,               //! PORT h1,h2,h3,h4,p1,p2
        PASV,               //! Passive mode
        TYPE,               //! Representation Type

        MODE,               //! Transfer Mode
        RETR,               //! Retrieve a file
        STOR,               //! Store a file
        ABOR,               //! Abort
        DELE,               //! Delete

        PWD,                //! Print Working Directory
        LIST,               //! List a directory
        NLST,               //! Name List
        SYST,               //! System
        STAT,               //! Status

        NOOP                //! No Operation
    };

    QTcpServer sv;
    QTcpSocket* sc;

    QString buffer;

    int mAuthenticated;
    bool mAnonymous;
    QString mUsername;
    QString mPassword;
    QString mAccount;

    QString mCurrentPath;
    QString mRootPath;

    bool mListRoots;
    bool mPassive;

    QString mFilename;
    QString mIPAddress;

    FTPFileSocket* fsc;
    FTPPort mPortInfo;
    qint64 mFilePosition;

    void processCommand(QString command);
    void execute(QString command);
    void respond(int code, QString message = "");
    void respond(QByteArray message);

    void DoHelp();
    void DoQuit();
    void DoUser(QString arg);
    void DoPass(QString arg);
    void DoACCT(QString arg);
    void DoCWD(QString arg);
    void DoCDUP();
    void DoPORT(QString arg);
    void DoPASV(QString arg);
    void DoTYPE(QString arg);
    void DoMODE(QString arg);
    void DoRETR(QString arg);
    void DoSTOR(QString arg);
    void DoABOR(QString arg);
    void DoDELE(QString arg);
    void DoPWD();
    void DoLIST(QString arg);
    void DoNLST(QString arg);
    void DoSYST();
    void DoSTAT(QString arg);

    void LogonUser();
    bool CheckAuthenticated();
    void CreateFileSocket();
    QString RelativePath();
    QString ClientPath(QString Requested);
    bool ConnectFileSocket();
public:
    explicit FtpServer(QObject *parent = 0);
    void start(qint16 port = 21);
    void stop();
protected:
    void incomingConnection(int descr);
signals:
    void msg(QString);
    void started();
    void stopped();
private slots:

public slots:
    void onClientConnected();
    void onClientDisconnected();
    void read();
    
    void OnFileConnected();
    void OnFileListening();
    void OnFileError(QString Message);
    void OnFileFinished();
    void OnFileDisconnected();
};

#endif // FTPSERVER_H
