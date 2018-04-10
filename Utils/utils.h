#ifndef UTILS_H
#define UTILS_H

#include <QObject>

#include "const.h"
#include "configuration.h"

#define DEFAULT_MARGIN  5
#define HEADER_HEIGHT   50
#define HEIGHT_MARGINS  (100+HEADER_HEIGHT) // general for application window itself
#define WIDTH_MARGINS   50                  // general for application window itself

class SimulationLayout;
class Monitor;

class Utils
{
public:
    Utils();
    static unsigned int getMonitorWidth(unsigned int, bool forceReset = false);
    static unsigned int getMonitorHeight(unsigned int,bool forceReset = false);
    static unsigned int getEnvironmentWidth();
    static unsigned int getEnvironmentHeight();


    static SimulationLayout* generateLayout(UniversalType type, Configuration* config, QObject* parent, Monitor* focus = NULL);
};

#endif // UTILS_H
