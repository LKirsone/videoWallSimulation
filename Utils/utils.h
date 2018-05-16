#ifndef UTILS_H
#define UTILS_H

#include <QObject>

#include "const.h"
#include "configuration.h"

#define HEADER_HEIGHT   50
#define HEIGHT_MARGINS  (100+HEADER_HEIGHT) // general for application window itself
#define WIDTH_MARGINS   50                  // general for application window itself

class LayoutFramework;
class Monitor;

class Utils
{
public:
    Utils();
    static unsigned int     getMonitorWidth(unsigned int, bool forceReset = false);
    static unsigned int     getMonitorHeight(unsigned int,bool forceReset = false);
    static unsigned int     getEnvironmentWidth(bool noPadding = false);
    static unsigned int     getEnvironmentHeight(bool noPadding = false);

    static Position         translatePointToMonitor(QPointF point, Configuration config);
    static LayoutFramework* generateLayout(UniversalType type, Configuration* config, QObject* parent, QWidget* uiWidget, Monitor* focus = NULL);
};

#endif // UTILS_H
