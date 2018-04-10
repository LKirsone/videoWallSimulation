#include "videolayout.h"

VideoLayout::VideoLayout(Configuration *config, QObject* simWin)
    : SimulationLayout(config, simWin)
{
    if(config)
    {
        config->simulationType = TYPE_VIDEO;
        //if(config->isConfigInstalled)
        {
            // maybe the config could be stored in some file in future, so that next time we re-enter simulator
            // we can just load it from stored config
        }
        //else
        {
            setDefaultConfig();
        }

        if(config->isMonitorFocused == false)
        {
            generateMonitorMatrice();
        }
    }
}

void VideoLayout::generateMonitorMatrice()
{}
