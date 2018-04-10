#ifndef ABSTRACTLAYOUT_H
#define ABSTRACTLAYOUT_H

#include <QObject>
#include "simulationlayout.h"

class AbstractLayout : public SimulationLayout
{
public:
    AbstractLayout(Configuration*, QObject* simWin);

signals:
public slots:

protected:
    virtual void    generateMonitorMatrice();
    //virtual void    setDefaultConfig();
};

#endif // ABSTRACTLAYOUT_H
