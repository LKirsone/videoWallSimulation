#ifndef LAYOUTFRAMEWORK_H
#define LAYOUTFRAMEWORK_H

#include <QObject>

#include "Layouts/simulationlayout.h"

class LayoutFramework : public QObject
{
    Q_OBJECT
protected:
    QObject*            simulationWindow;
    SimulationLayout*   content;

    QHBoxLayout*        headerLayout;
    QVBoxLayout*        mainWindowLayout;
    QGroupBox*          headerGroup;

    Configuration*      config;
    UI_HeaderData       uiHeader;
public:
    LayoutFramework(Configuration *cfg, QObject* parent);
    ~LayoutFramework();

    void                addBody(SimulationLayout* layout);

public slots:
    void                simulationRunningStatusUpdate(void);
    void                simulationTypeChanged(const QString &command_text);
    void                incorrectIpAddresField();
    void                connectDetected(int conenctId);
    void                disconnectDetected(int connectId);

protected:
    SimulationLayout*   getContent() const;
    QVBoxLayout*        getLayout() const;

private:
    void                generateHeader();

    friend class        MainWindow;
    friend class        SimulationLayout;
    friend class        Communication;
};

#endif // LAYOUTFRAMEWORK_H
