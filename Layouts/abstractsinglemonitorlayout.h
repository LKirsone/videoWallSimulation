#ifndef ABSTRACTSINGLEMONITORLAYOUT_H
#define ABSTRACTSINGLEMONITORLAYOUT_H

#include "abstractlayout.h"

class AbstractSingleMonitorLayout : public AbstractLayout
{
    Monitor*            focusedMonitor;
    float               fullScreenWidthRatio;
    float               fullScreenHeightRatio;

    float               monitorPositionX;
    float               monitorPositionY;
public:
    AbstractSingleMonitorLayout(Monitor*,Configuration*, QObject*);
    ~AbstractSingleMonitorLayout();

public slots:
    virtual void        onManualUpdate(QDataStream*);
    void                onMove(int, QPointF, int, int);

protected:
    virtual void        generateMonitorMatrice();
private:

    void                updateMonitorMatrice();
};

#endif // ABSTRACTSINGLEMONITORLAYOUT_H
