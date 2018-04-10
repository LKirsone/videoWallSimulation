#include "utils.h"
#include <QApplication>
#include <QDesktopWidget>

#include "CustomWidgets/monitor.h"

#include "Layouts/simulationlayout.h"
#include "Layouts/abstractsinglemonitorlayout.h"
#include "Layouts/abstractlayout.h"
#include "Layouts/videolayout.h"

Utils::Utils()
{

}

unsigned int Utils::getMonitorHeight(unsigned int monitorsPerColumn, bool forceReset)
{
    static bool heightSet = false;
    static unsigned int height = 0;

    if(!heightSet || forceReset)
    {
        QRect rec = QApplication::desktop()->screenGeometry();
        height = std::floor((rec.height()-HEIGHT_MARGINS)/monitorsPerColumn);
        heightSet = true;
    }

    return height;
}

unsigned int Utils::getMonitorWidth(unsigned int monitorPerRow, bool forceReset)
{
    static bool widthSet = false;
    static unsigned int width = 0;

    if(!widthSet || forceReset)
    {
        QRect rec = QApplication::desktop()->screenGeometry();
        width = std::floor((rec.width()-WIDTH_MARGINS)/monitorPerRow);
        widthSet = true;
    }

    return width;
}

unsigned int Utils::getEnvironmentWidth()
{
    static bool widthSet = false;
    static unsigned int width = 0;

    if(!widthSet)
    {
        QRect rec = QApplication::desktop()->screenGeometry();
        width = rec.width() - WIDTH_MARGINS;
        widthSet = true;
    }
    return width;
}

unsigned int Utils::getEnvironmentHeight()
{
    static bool heightSet = false;
    static unsigned int height = 0;

    if(!heightSet)
    {
        QRect rec = QApplication::desktop()->screenGeometry();
        height = rec.height() - HEIGHT_MARGINS;
        heightSet = true;
    }
    return height;
}

SimulationLayout* Utils::generateLayout(UniversalType type, Configuration* config, QObject* parent, Monitor* focus)
{
    SimulationLayout* layout = NULL;
    switch(type)
    {
    case TYPE_ABSTRACT:
        layout = new AbstractLayout(config, parent);
        break;
    case TYPE_VIDEO:
        layout = new VideoLayout(config, parent);
        break;
    case TYPE_ABSTRACT_SINGLE_MONITOR:
        layout = new AbstractSingleMonitorLayout(focus, config, parent);
        break;
    case TYPE_VIDEO_SINGLE_MONITOR:
        //layout = new VideoSingleMonitorLayout(&(simulationLayout->monitorMatrice[config.focusPosition.line][config.focusPosition.line]), config, this);
        break;
    case TYPE_UNKNOWN:
    default:
        break;
    }

    return layout;
}
