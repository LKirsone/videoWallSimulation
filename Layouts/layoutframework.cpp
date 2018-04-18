#include "layoutframework.h"

LayoutFramework::LayoutFramework(Configuration *cfg, QObject* parent)
    : simulationWindow(parent)
    , content(NULL)
    , headerLayout(new QHBoxLayout())
    , mainWindowLayout( new QVBoxLayout())
    , headerGroup(new QGroupBox())
    , config(cfg)
{
    generateHeader();

    mainWindowLayout->addWidget(headerGroup);
}

LayoutFramework::~LayoutFramework()
{
    this->disconnect();
    disconnect(content, 0, 0, 0);
    disconnect(0, 0, content, 0);
    disconnect(0, 0, mainWindowLayout, 0);
    disconnect(mainWindowLayout, 0, 0, 0);
    disconnect(headerGroup, 0, 0, 0);
    disconnect(headerLayout, 0, 0, 0);
    disconnect(uiHeader.selectSimOption, 0, 0, 0);
    disconnect(uiHeader.startStopSim, 0, 0, 0);

    delete content;
    delete uiHeader.selectSimOption;
    delete uiHeader.startStopSim;
    delete headerLayout;
    delete headerGroup;
    delete mainWindowLayout;
    delete config;

}

void LayoutFramework::addBody(SimulationLayout* layout)
{
    QWidget* contentWidget = NULL;
    if(layout)
    {
        contentWidget = new QWidget();
        content = layout;

        if(contentWidget)
        {
            contentWidget->setLayout(layout->getMatriceLayout());
            mainWindowLayout->addWidget(contentWidget);

            connect(content, SIGNAL(invalidIpAddress()), this, SLOT(incorrectIpAddresField()));
            connect(content, SIGNAL(hasConnect(int)), this, SLOT(connectDetected(int)));
            connect(content, SIGNAL(hasDisconnect(int)), this, SLOT(disconnectDetected(int)));
        }
    }
}

SimulationLayout* LayoutFramework::getContent() const
{
    return content;
}

void LayoutFramework::generateHeader()
{
    // simulation type selection
    uiHeader.selectSimOption = new QComboBox();
    uiHeader.selectSimOption->addItems(uiHeader.simOptions);
    headerLayout->addWidget(uiHeader.selectSimOption);

    // button to start/stop simulation
    uiHeader.startStopSim = new QPushButton();
    uiHeader.startStopSim->setText(config->isSimulationRunning ? STRING_STOP : STRING_START);
    headerLayout->addWidget(uiHeader.startStopSim);

    uiHeader.ipAddress = new QLineEdit();
    uiHeader.ipAddress->setPlaceholderText("Enter server IP address");
    headerLayout->addWidget(uiHeader.ipAddress);

    uiHeader.statusLabel = new QLabel();
    uiHeader.statusLabel->setText("No connection");
    headerLayout->addWidget(uiHeader.statusLabel);

    headerGroup->setFixedHeight(HEADER_HEIGHT);
    headerGroup->setLayout(headerLayout);

    connect(uiHeader.startStopSim, SIGNAL(pressed()), this, SLOT(simulationRunningStatusUpdate()));
    connect(uiHeader.selectSimOption, SIGNAL(currentTextChanged(QString)), this, SLOT(simulationTypeChanged(QString)));
}

void LayoutFramework::connectDetected(int conenctId)
{
    switch(config->simulationType)
    {
    case TYPE_ABSTRACT:
        uiHeader.statusLabel->setText("Connected");
        break;
    case TYPE_VIDEO:
        // TODO: here we'll need to handle the connect ID
    default:
        break;
    }
}

void LayoutFramework::disconnectDetected(int conenctId)
{
    switch(config->simulationType)
    {
    case TYPE_ABSTRACT:
        uiHeader.statusLabel->setText("Disconnected");
        break;
    case TYPE_VIDEO:
        // TODO: here we'll need to handle the connect ID
    default:
        break;
    }
}

void LayoutFramework::simulationRunningStatusUpdate(void)
{
    if(uiHeader.startStopSim->text() == STRING_START)
    {
        uiHeader.startStopSim->setText(STRING_STOP);
        config->isSimulationRunning = true;

        content->connectToServer(uiHeader.ipAddress->text());
    }
    else
    {
        uiHeader.startStopSim->setText(STRING_START);
        config->isSimulationRunning = false;

        uiHeader.ipAddress->setPlaceholderText("Enter server IP address");
    }
}

void LayoutFramework::simulationTypeChanged(const QString &command_text)
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

void LayoutFramework::incorrectIpAddresField()
{
    uiHeader.ipAddress->setText("");
    uiHeader.ipAddress->setPlaceholderText("CONNECT ERROR: invalid IP address!");
}

QVBoxLayout* LayoutFramework::getLayout() const
{
    return mainWindowLayout;
}

