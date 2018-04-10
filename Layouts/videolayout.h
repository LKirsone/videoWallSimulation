#ifndef VIDEOLAYOUT_H
#define VIDEOLAYOUT_H


#include "simulationlayout.h"

class VideoLayout : public SimulationLayout
{
public:
    VideoLayout(Configuration*, QObject* simWin);

signals:
public slots:

protected:
    virtual void    generateMonitorMatrice();
    //virtual void    setDefaultConfig();
};

#endif // VIDEOLAYOUT_H
