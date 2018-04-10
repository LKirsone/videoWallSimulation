#include "simulationlayout.h"

#include <QCloseEvent>

SimulationLayout::SimulationLayout(Configuration *cfg, QObject* parent)
    : QObject()
    , focusLayout(NULL)
    , simulationWindow(parent)
    , headerLayout(new QHBoxLayout())
    , monitorGridLayout(new QGridLayout())
    , mainWindowLayout( new QVBoxLayout())
    , headerGroup(new QGroupBox())
    , monitorMatriceGroup(new QGroupBox())
    , config(cfg)
    , monitorMatrice(NULL)
    , rowsInMonitorMatrice(0)
    , columnsInMonitorMatrice(0)
{
    generateHeader();

    mainWindowLayout->addWidget(headerGroup);
    mainWindowLayout->addWidget(monitorMatriceGroup);
}

SimulationLayout::~SimulationLayout()
{
    //clearMonitorMatrice();
    delete uiHeader.selectSimOption;
    delete uiHeader.startStopSim;
    delete headerLayout;
    delete monitorGridLayout;
    delete mainWindowLayout;
    delete headerGroup;
    delete monitorMatriceGroup;
    delete config;
}

void SimulationLayout::generateHeader()
{
    // simulation type selection
    uiHeader.selectSimOption = new QComboBox();
    uiHeader.selectSimOption->addItems(uiHeader.simOptions);
    headerLayout->addWidget(uiHeader.selectSimOption);

    // button to start/stop simulation
    uiHeader.startStopSim = new QPushButton();
    uiHeader.startStopSim->setText(config->isSimulationRunning ? STRING_STOP : STRING_START);
    headerLayout->addWidget(uiHeader.startStopSim);

    headerGroup->setFixedHeight(HEADER_HEIGHT);
    headerGroup->setLayout(headerLayout);

    QObject::connect(uiHeader.startStopSim, SIGNAL(pressed()), this, SLOT(simulationRunningStatusUpdate()));
    QObject::connect(uiHeader.selectSimOption, SIGNAL(currentTextChanged(QString)), this, SLOT(simulationTypeChanged(QString)));
}

void SimulationLayout::simulationRunningStatusUpdate(void)
{
    if(uiHeader.startStopSim->text() == STRING_START)
    {
        uiHeader.startStopSim->setText(STRING_STOP);
        config->isSimulationRunning = true;
    }
    else
    {
        uiHeader.startStopSim->setText(STRING_START);
        config->isSimulationRunning = false;
    }
}

void SimulationLayout::simulationTypeChanged(const QString &command_text)
{
    if(command_text == ABSTR_SIM_STR)
    {
        config->simulationType = TYPE_ABSTRACT;
    }
    else if(command_text == VIDEO_SIM_STR)
    {
        config->simulationType = TYPE_VIDEO;
    }
    else
    {
        config->simulationType = TYPE_UNKNOWN;
    }
}


void SimulationLayout::monitorSelected(unsigned int monitorRow, unsigned int monitorColumn)
{
    // first verify that the monitor position is validSamanta1

    if(!focusedMonitor && monitorColumn < columnsInMonitorMatrice && monitorRow < rowsInMonitorMatrice)
    {
        config->isMonitorFocused = true;
        config->focusPosition.line = monitorRow;
        config->focusPosition.column = monitorColumn;

        switch(config->simulationType)
        {
        case TYPE_ABSTRACT: focusLayout = Utils::generateLayout(TYPE_ABSTRACT_SINGLE_MONITOR, config, simulationWindow, &monitorMatrice[monitorColumn][monitorRow]);   break;
        case TYPE_VIDEO:    focusLayout = Utils::generateLayout(TYPE_VIDEO_SINGLE_MONITOR, config, simulationWindow, &monitorMatrice[monitorColumn][monitorRow]);      break;
        case TYPE_UNKNOWN:
        default:
            break;
        }
        //FocusSpecificMonitor(focusLayout->getLayout());
        if(focusLayout->getLayout())
        {
            focusedMonitor = new Monitor();
            focusedMonitor->setLayout(focusLayout->getLayout());

            // show the focused monitor
            focusedMonitor->show();

            // disable current window, as we'll focus the one specific monitor now
            emit mainWindowDisabled();
            connect(focusedMonitor, SIGNAL(monitorClosed()), this, SLOT(focusedMonitorClosed()));
            connect(this, SIGNAL(monitorClosureDetected()), simulationWindow, SLOT(enableMainWindow()));
        }
    }
}

void SimulationLayout::focusedMonitorClosed()
{
    if(focusedMonitor)
    {
        // clear the object
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
}

QVBoxLayout* SimulationLayout::getLayout()
{
    return mainWindowLayout;
}
