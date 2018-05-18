#ifndef VIDEOLAYOUT_H
#define VIDEOLAYOUT_H

#include <QTcpSocket>
#include "simulationlayout.h"
#include <AVError.h>

class VideoLayout : public SimulationLayout
{
    QList<QTcpSocket>   commProfileList; // not in use
public:
    VideoLayout(Configuration*, QObject* simWin, QWidget* uiWidget);

signals:
public slots:
    virtual void        contentUpdate();

protected:
    virtual bool        connectToServer(QString ipAddress);
    virtual void        generateMonitorMatrice();
    //virtual void    setDefaultConfig();
};

#endif // VIDEOLAYOUT_H
