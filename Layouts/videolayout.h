#ifndef VIDEOLAYOUT_H
#define VIDEOLAYOUT_H

#include <QTcpSocket>
#include "simulationlayout.h"

class VideoLayout : public SimulationLayout
{
    QList<QTcpSocket>   commProfileList;
public:
    VideoLayout(Configuration*, QObject* simWin);

signals:
public slots:
    virtual void        contentUpdate();

protected:
    virtual bool        connectToServer(QString ipAddress);
    virtual void        generateMonitorMatrice();
    //virtual void    setDefaultConfig();
};

#endif // VIDEOLAYOUT_H
