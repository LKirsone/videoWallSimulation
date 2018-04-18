#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QDataStream>
#include <QList>
#include <QTcpSocket>
#include <QString>

#include "Utils/const.h"

class Communication : public QObject
{
    Q_OBJECT
    QList<QTcpSocket>   commProfileList;
public:
    explicit Communication(QObject *parent = nullptr);
    ~Communication();

    bool                    setConnectionProfile(QString& address, unsigned int port);
signals:
    void                    dataReceived(QDataStream*);

public slots:
    void                    onUiUpdate(ContentUpdateType, QDataStream*);
};


#endif // COMMUNICATION_H
