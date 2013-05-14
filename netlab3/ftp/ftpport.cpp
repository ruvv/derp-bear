#include "ftpport.h"

FTPPort::FTPPort(QObject *parent) :
    QObject(parent)
{
    Clear();
}

FTPPort::FTPPort(QString aIPAddress, uint aPort, QObject *parent) :
    QObject(parent)
{
    Clear();
}

QString FTPPort::IPAddress()
{
    return mIPAddress;
}

void FTPPort::SetIPAddress(QString nIPAddress)
{
    mIPAddress = nIPAddress;
}

quint16 FTPPort::Port()
{
    return mPort;
}

void FTPPort::SetPort(quint16 nPort)
{
    mPort = nPort;
}

QString FTPPort::ToString()
{
    //Returns something like 127,0,0,1,4,15

    //Format the IP Address
    QString ret = mIPAddress.replace(".",",");

    //Convert the Port into a 4 digit hex string
    QString hex = QString("%1").arg(QString().setNum(mPort,16),4,'0');

    //For conversion to dec
    bool ok;

    //convert the First part to dec
    uint nFirst = hex.mid(0,2).toUInt(&ok,16);

    //convert the First part to dec
    uint nSecond = hex.mid(2,2).toUInt(&ok,16);

    //Build the response
    ret.append(",");
    ret.append(QString::number(nFirst));
    ret.append(",");
    ret.append(QString::number(nSecond));

    return ret;
}

void FTPPort::FromString(QString Data)
{
    //Parses a string like 127,0,0,1,4,15

    QStringList List = Data.split(",");
    if(List.count() < 6) throw QString("Port information is invalid!");

    mIPAddress = QString("%1.%2.%3.%4").arg(List.at(0)).arg(List.at(1)).arg(List.at(2)).arg(List.at(3));

    QString hex;

    //Convert the to a hex string
    int nFirst = List.at(4).toUInt();
    int nSecond = List.at(5).toUInt();
    hex.append(QString("%1").arg(QString().setNum(nFirst,16),2,'0'));
    hex.append(QString("%1").arg(QString().setNum(nSecond,16),2,'0'));

    //convert the hex string into the port
    bool ok;
    mPort = hex.toUInt(&ok,16);

}

void FTPPort::Clear()
{
    mIPAddress = "0.0.0.0";
    mPort = 0;
}
