#include "CustomWidgets/monitor.h"
#include <QEvent>

Monitor::Monitor(QWidget *parent)
    : QWidget(parent)
    //, contentController(NULL)
{
    displayPanel = NULL;
    args = NULL;
    positionInMatrice.line = 0;
    positionInMatrice.column = 0;
    ipAddress = "";
}

Monitor::~Monitor()
{
    //delete contentController;
    delete displayPanel;
    delete args;
}

void Monitor::closeEvent(QCloseEvent* evt)
{
    emit monitorClosed();
}

