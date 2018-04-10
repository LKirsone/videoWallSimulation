#ifndef ABSTRACTSINGLEMONITORLAYOUT_H
#define ABSTRACTSINGLEMONITORLAYOUT_H

#include "abstractlayout.h"

class AbstractSingleMonitorLayout : public AbstractLayout
{
    Monitor*                focusedMonitor;
public:
    AbstractSingleMonitorLayout(Monitor*,Configuration*, QObject*);
    ~AbstractSingleMonitorLayout();

protected:
    virtual void            generateMonitorMatrice();
};

#endif // ABSTRACTSINGLEMONITORLAYOUT_H
