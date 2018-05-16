#ifndef ABSTRACTLAYOUT_H
#define ABSTRACTLAYOUT_H

#include <QObject>
#include <QTcpSocket>
#include "simulationlayout.h"

class AbstractLayout : public SimulationLayout
{
protected:
    float               singleScreenWidthRatio;
    float               singleScreenHeightRatio;

    QList<ClientWindow> windowsList;
    QTcpSocket*         connect;
    CustomGraphicScene* m_graphScene;
public:
    AbstractLayout(Configuration*, QObject* simWin, QWidget* uiWidget);
    ~AbstractLayout();

signals:

public slots:
    virtual void        contentUpdate();
    virtual void        isConnected();
    virtual void        isDisconnected();

    void                onMove(int, QPointF, int, int);


protected:
    virtual bool        connectToServer(QString ipAddress);
    virtual void        generateMonitorMatrice();
    //virtual void    setDefaultConfig();

private:
    void                updateMonitorMatrice();
};

#endif // ABSTRACTLAYOUT_H
