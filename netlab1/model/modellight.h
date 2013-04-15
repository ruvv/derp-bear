#ifndef MODELLIGHT_H
#define MODELLIGHT_H

#include <QObject>
#include <QString>

class ModelLight : public QObject {
    Q_OBJECT
protected:
    QString url;
    QString datetime;
    int type;
public:
    explicit ModelLight(QObject *parent = 0);

signals:
    
public slots:
    
};

#endif // MODELLIGHT_H
