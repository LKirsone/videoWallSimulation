#include "mainwindow.h"

#include "Layouts/abstractlayout.h"
#include "Layouts/videolayout.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , simulationLayout()
    , communication()
{
    // TEMP VALUES, while config file is not used and parsed
    config.isConfigInstalled = true;
    config.simulationType =   TYPE_ABSTRACT; // TYPE_VIDEO

    mainWidget = new QWidget();

    simulationLayout = Utils::generateLayout(config.simulationType, &config, this, mainWidget);
    if(simulationLayout)
    {
        SimulationLayout* content = simulationLayout->getContent();
        if(content)
        {
            connect(content, SIGNAL(mainWindowDisabled()), this, SLOT(disableMainWindow()));
            mainWidget->setLayout(simulationLayout->getLayout());
            mainWidget->updateGeometry();
        }
    }
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
    delete simulationLayout;
}

void MainWindow::disableMainWindow()
{
    if(mainWidget)
    {
        mainWidget->setDisabled(true);
        // TODO: here wiill also be some call for stopping updates to maiun windows UI,
        // respond to host data (like ignore updates to rest of the monitors) etc.
    }
}

void MainWindow::enableMainWindow()
{
    if(mainWidget)
    {
        mainWidget->setEnabled(true);
        // TODO: here wiill also be some call for restarting updates to maiun windows UI,
        // respond to host data (like ignore updates to rest of the monitors) etc.
    }
}
