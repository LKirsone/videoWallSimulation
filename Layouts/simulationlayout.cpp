#include "simulationlayout.h"

#include <QCloseEvent>
#include <QThreadPool>
#include "layoutframework.h"
#include <qlogging.h>
#include <qdebug.h>

SimulationLayout::SimulationLayout(Configuration *cfg, QObject* parent, QWidget* uiWidget)
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
    , mainUiWidget(uiWidget)
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
        case TYPE_ABSTRACT: focusLayout = Utils::generateLayout(TYPE_ABSTRACT_SINGLE_MONITOR, config, simulationWindow, mainUiWidget, &monitorMatrice[monitorPos.line][monitorPos.column]);   break;
        case TYPE_VIDEO:    focusLayout = Utils::generateLayout(TYPE_VIDEO_SINGLE_MONITOR, config, simulationWindow, mainUiWidget, &monitorMatrice[monitorPos.line][monitorPos.column]);      break;
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

        //monitorMatrice[config->focusPosition.column][config->focusPosition.line].displayPanel->

        config->focusPosition.line = 0;
        config->focusPosition.column = 0;

        // pass the data to main window, so it can re-enable the UI
        emit monitorClosureDetected();
    }
}

void SimulationLayout::setDefaultConfig()
{
    config->isSimulationRunning = false;
    config->monitorsPerColumn = 2;
    config->monitorsPerRow = 2;
    config->isConfigInstalled = true;

    // set by default FHD resolution
    config->physicalMonitorResolutionX= 1920;
    config->physicalMonitorResolutionY = 1080;

    QThreadPool::globalInstance()->setMaxThreadCount((config->monitorsPerColumn + config->monitorsPerRow)*5);
}

bool SimulationLayout::connectToServer(QString ipAddress)
{
    // default empty implementation for temporary layouts, when specific monitor is focused
    // at that cases new connects are not needed, updated will be transmisted from parent layout
    return false;
}

void SimulationLayout::error(const QtAV::AVError& e) //explictly use QtAV::AVError in connection for Qt4 syntax
{
    qInfo() << "ERROR: " << e.string();
}

void SimulationLayout::paused(bool p)
{
    qInfo() << "paused: " << p;
}

void SimulationLayout::started()
{
    qInfo() << "Started";
}

void SimulationLayout::stopped()
{
    qInfo() << "Stopped";
}

QLayout* SimulationLayout::getMatriceLayout() const
{
    return monitorGridLayout;
}
