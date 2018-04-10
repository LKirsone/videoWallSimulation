#ifndef SIMULATIONLAYOUT_H
#define SIMULATIONLAYOUT_H

#include <QHBoxLayout>
#include <QGroupBox>

#include "Utils\configuration.h"
#include "Utils\utils.h"
#include "Utils\ui_const.h"

#include "CustomWidgets/monitor.h"

class SimulationLayout : public QObject
{
    Q_OBJECT

    Monitor*            focusedMonitor;
    SimulationLayout*   focusLayout;
protected:
    QObject*            simulationWindow;

    QHBoxLayout*        headerLayout;
    QGridLayout*        monitorGridLayout;
    QVBoxLayout*        mainWindowLayout;

    QGroupBox*          headerGroup;
    QGroupBox*          monitorMatriceGroup;

    Configuration*      config;
    UI_HeaderData       uiHeader;

    Monitor**           monitorMatrice;
    unsigned int        rowsInMonitorMatrice;
    unsigned int        columnsInMonitorMatrice;

public:
    SimulationLayout(Configuration* config, QObject* parent);
    ~SimulationLayout();

    QVBoxLayout*        getLayout();

signals:
    void                mainWindowDisabled();
    void                mainWindowEnabled();
    void                monitorClosureDetected();

public slots:
    void                simulationRunningStatusUpdate(void);
    void                simulationTypeChanged(const QString&);
    void                focusedMonitorClosed();
    void                monitorSelected(unsigned int monitorRow, unsigned int monitorColumn);

private:
    void                generateHeader();

protected:
    virtual void        generateMonitorMatrice() = 0;
    virtual void        setDefaultConfig();
};

#endif // SIMULATIONLAYOUT_H
