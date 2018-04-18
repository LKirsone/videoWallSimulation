#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "const.h"

class Configuration
{
public:
    Configuration();
    Configuration(bool configInstalled, bool simulationRunning, UniversalType simType, unsigned int rowSize, unsigned int columnSize, bool monitorFocused, Position focusPos);

    bool            isConfigInstalled;
    bool            isSimulationRunning;
    UniversalType   simulationType;

    unsigned int    monitorsPerRow;
    unsigned int    monitorsPerColumn;

    bool            isMonitorFocused;
    Position        focusPosition;

    int             physicalMonitorResolutionX;
    int             physicalMonitorResolutionY;
};

#endif // CONFIGURATION_H
