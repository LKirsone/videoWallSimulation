#include "CustomWidgets/monitor.h"
#include <QEvent>
#include "CustomObjects/customgraphicscene.h"

Monitor::Monitor(QWidget *parent)
    : QWidget(parent)
    //, contentController(NULL)
{
    displayPanel = NULL;
    args = NULL;
    positionInMatrice.line = 0;
    positionInMatrice.column = 0;
    url = "";
}

Monitor::~Monitor()
{
    //delete contentController;
    displayPanel->disconnect();
    delete displayPanel;
    delete args;
}

void Monitor::closeEvent(QCloseEvent* evt)
{
    emit monitorClosed();
}

