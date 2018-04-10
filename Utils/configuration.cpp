#include "configuration.h"

Configuration::Configuration()
    : isConfigInstalled(false)
    , isSimulationRunning(false)
    , simulationType(TYPE_UNKNOWN)
    , monitorsPerRow(0)
    , monitorsPerColumn(0)
    , isMonitorFocused(false)
    , focusPosition()
{ }

Configuration::Configuration(bool configInstalled, bool simulationRunning, UniversalType simType, unsigned int rowSize, unsigned int columnSize,
                             bool monitorFocused, Position focusPos)
    : isConfigInstalled(configInstalled)
    , isSimulationRunning(simulationRunning)
    , simulationType(simType)
    , monitorsPerRow(rowSize)
    , monitorsPerColumn(columnSize)
    , isMonitorFocused(monitorFocused)
{
    focusPosition = focusPos;
}
