#ifndef SIMULATIONLAYOUT_H
#define SIMULATIONLAYOUT_H

#include <QHBoxLayout>
#include <QGroupBox>
#include <QDataStream>

#include "Utils\configuration.h"
#include "Utils\utils.h"
#include "Utils\ui_const.h"
#include "CustomWidgets/monitor.h"

class LayoutFramework;

class SimulationLayout : public QObject
{
    Q_OBJECT

    Monitor*            focusedMonitor;
    LayoutFramework*    focusLayout;
protected:
    QObject*            simulationWindow;

    QGridLayout*        monitorGridLayout;
    QGroupBox*          monitorMatriceGroup;

    Configuration*      config;

    Monitor**           monitorMatrice;
    unsigned int        rowsInMonitorMatrice;
    unsigned int        columnsInMonitorMatrice;

public:
    SimulationLayout(Configuration* config, QObject* parent);
    ~SimulationLayout();

signals:
    void                mainWindowDisabled();
    void                mainWindowEnabled();
    void                monitorClosureDetected();
    void                uiUpdated(ContentUpdateType, QDataStream*);
    void                invalidIpAddress();
    void                hasConnect(int connectId); // connect ID only necessary for video simulation
    void                hasDisconnect(int connectId); // connect ID only necessary for video simulation
    void                startManualContentUpdate(QDataStream*);

public slots:
    void                focusedMonitorClosed();
    void                monitorSelected(QPointF);
    virtual void        contentUpdate() = 0;
    virtual void        isConnected();
    virtual void        isDisconnected();
    virtual void        onManualUpdate(QDataStream*);

private:

protected:
    virtual void        generateMonitorMatrice() = 0;
    virtual void        setDefaultConfig();
    virtual bool        connectToServer(QString ipAddress);

    QLayout*            getMatriceLayout() const;

    friend class        LayoutFramework;
};

#endif // SIMULATIONLAYOUT_H
