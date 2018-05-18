#ifndef SIMULATIONLAYOUT_H
#define SIMULATIONLAYOUT_H

#include <QHBoxLayout>
#include <QGroupBox>
#include <QDataStream>

#include "Utils\configuration.h"
#include "Utils\utils.h"
#include "Utils\ui_const.h"
#include "CustomWidgets/monitor.h"

#include <AVError.h>

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

    QWidget*            mainUiWidget;

public:
    SimulationLayout(Configuration* config, QObject* parent, QWidget* uiWidget);
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

    void error(const QtAV::AVError& e); //explictly use QtAV::AVError in connection for Qt4 syntax
    void paused(bool p);
    void started();
    void stopped();

private:

protected:
    virtual void        generateMonitorMatrice() = 0;
    virtual void        setDefaultConfig();
    virtual bool        connectToServer(QString ipAddress);

    QLayout*            getMatriceLayout() const;

    friend class        LayoutFramework;
};

#endif // SIMULATIONLAYOUT_H
