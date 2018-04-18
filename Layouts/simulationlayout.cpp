#include "simulationlayout.h"

#include <QCloseEvent>
#include "layoutframework.h"

SimulationLayout::SimulationLayout(Configuration *cfg, QObject* parent)
    : QObject()
    , focusedMonitor(NULL)
    , focusLayout(NULL)
    , simulationWindow(parent)
    , monitorGridLayout(new QGridLayout())
    , monitorMatriceGroup(new QGroupBox())
    , config(cfg)
    , monitorMatrice(NULL)
    , rowsInMonitorMatrice(0)
    , columnsInMonitorMatrice(0)
{
    connect(this, SIGNAL(monitorClosureDetected()), simulationWindow, SLOT(enableMainWindow()));
    connect(this, SIGNAL(mainWindowDisabled()), simulationWindow, SLOT(disableMainWindow()));
}

void SimulationLayout::isConnected()
{}

void SimulationLayout::isDisconnected()
{}

void SimulationLayout::onManualUpdate(QDataStream* x)
{}

SimulationLayout::~SimulationLayout()
{
    this->disconnect();
    monitorGridLayout->disconnect();
    monitorMatriceGroup->disconnect();

    //clearMonitorMatrice();
    delete monitorGridLayout;
    delete monitorMatriceGroup;
    delete config;
}

void SimulationLayout::monitorSelected(QPointF point)
{
    // first verify that the monitor position is valid
    Position monitorPos = Utils::translatePointToMonitor(point, *config);

    if(!focusedMonitor && monitorPos.column < columnsInMonitorMatrice && monitorPos.line < rowsInMonitorMatrice)
    {
        config->isMonitorFocused = true;
        config->focusPosition.line = monitorPos.line;
        config->focusPosition.column = monitorPos.column;

        switch(config->simulationType)
        {
        case TYPE_ABSTRACT: focusLayout = Utils::generateLayout(TYPE_ABSTRACT_SINGLE_MONITOR, config, simulationWindow, &monitorMatrice[monitorPos.line][monitorPos.column]);   break;
        case TYPE_VIDEO:    focusLayout = Utils::generateLayout(TYPE_VIDEO_SINGLE_MONITOR, config, simulationWindow, &monitorMatrice[monitorPos.line][monitorPos.column]);      break;
        case TYPE_UNKNOWN:
        default:
            break;
        }
        //FocusSpecificMonitor(focusLayout->getLayout());
        if(focusLayout && focusLayout->getLayout())
        {
            focusedMonitor = new Monitor();
            focusedMonitor->setLayout(focusLayout->getLayout());

            // show the focused monitor
            focusedMonitor->show();

            // disable current window, as we'll focus the one specific monitor now
            emit mainWindowDisabled();
            connect(focusedMonitor, SIGNAL(monitorClosed()), this, SLOT(focusedMonitorClosed()));
            connect(this, SIGNAL(startManualContentUpdate(QDataStream*)), focusLayout->getContent(), SLOT(onManualUpdate(QDataStream*)));
        }
    }
}

void SimulationLayout::focusedMonitorClosed()
{
    if(focusedMonitor)
    {
        config->isMonitorFocused = false;

        focusLayout->disconnect();
        delete focusLayout;
        focusLayout = NULL;

        // clear the object
        focusedMonitor->disconnect();
        delete focusedMonitor;
        focusedMonitor = NULL;

        // pass the data to main window, so it can re-enable the UI
        emit monitorClosureDetected();
    }
}

void SimulationLayout::setDefaultConfig()
{
    config->isSimulationRunning = false;
    config->monitorsPerColumn = 4;
    config->monitorsPerRow = 4;
    config->isConfigInstalled = true;

    // set by default FHD resolution
    config->physicalMonitorResolutionX= 1920;
    config->physicalMonitorResolutionY = 1080;
}

bool SimulationLayout::connectToServer(QString ipAddress)
{
    // default empty implementation for temporary layouts, when specific monitor is focused
    // at that cases new connects are not needed, updated will be transmisted from parent layout
    return false;
}

QLayout* SimulationLayout::getMatriceLayout() const
{
    return monitorGridLayout;
}
