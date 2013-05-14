#ifndef FTPLISTITEM_H
#define FTPLISTITEM_H

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QDateTime>

class FTPListItem : public QObject {
    Q_OBJECT
public:
    explicit FTPListItem(QObject *parent = 0);
    QString Convert(QFileInfo &FileInfo);

private:
    void GetType(QFileInfo &FileInfo, QString &Line);
    void GetPermissions(QFileInfo &FileInfo, QString &Line);
    void GetLinks(QFileInfo &FileInfo, QString &Line);
    void GetOwner(QFileInfo &FileInfo, QString &Line);
    void GetGroup(QFileInfo &FileInfo, QString &Line);
    void GetSize(QFileInfo &FileInfo, QString &Line);
    void GetDate(QFileInfo &FileInfo, QString &Line);
    void GetName(QFileInfo &FileInfo, QString &Line);
};

#endif // FTPLISTITEM_H
