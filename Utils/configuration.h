#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "const.h"

class Configuration
{
public:
    Configuration();
    Configuration(bool configInstalled, bool simulationRunning, UniversalType simType, unsigned int rowSize, unsigned int columnSize, bool monitorFocused, Position focusPos);

protected:
    bool            isConfigInstalled;
    bool            isSimulationRunning;
    UniversalType   simulationType;

    unsigned int    monitorsPerRow;
    unsigned int    monitorsPerColumn;

    bool            isMonitorFocused;
    Position        focusPosition;


    friend class AbstractLayout;
    friend class VideoLayout;
    friend class SimulationLayout;
    friend class MainWindow;
};

#endif // CONFIGURATION_H
