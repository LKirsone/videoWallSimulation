#include "utils.h"
#include <QApplication>
#include <QDesktopWidget>

#include "CustomWidgets/monitor.h"

#include "Layouts/layoutframework.h"
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
        QRect rec = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
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
        QRect rec = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
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
        QRect rec = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
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
        QRect rec = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
        height = rec.height() - HEIGHT_MARGINS;
        heightSet = true;
    }
    return height;
}

Position Utils::translatePointToMonitor(QPointF point, Configuration config)
{
    Position pos;
    if(config.monitorsPerRow && config.monitorsPerColumn)
    {
        pos.column = std::floor(point.x() / Utils::getMonitorWidth(config.monitorsPerRow));
        pos.line = std::floor(point.y() / Utils::getMonitorHeight(config.monitorsPerColumn));
    }
    return pos;
}

LayoutFramework* Utils::generateLayout(UniversalType type, Configuration* config, QObject* parent, Monitor* focus)
{
    LayoutFramework* layout = new LayoutFramework(config, parent);
    switch(type)
    {
    case TYPE_ABSTRACT:
        layout->addBody(new AbstractLayout(config, parent));
        break;
    case TYPE_VIDEO:
        layout->addBody(new VideoLayout(config, parent));
        break;
    case TYPE_ABSTRACT_SINGLE_MONITOR:
        layout->addBody(new AbstractSingleMonitorLayout(focus, config, parent));
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
