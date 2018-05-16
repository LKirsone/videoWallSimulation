#ifndef VIDEOSIGNLEMONITORLAYOUT_H
#define VIDEOSIGNLEMONITORLAYOUT_H

#include "videolayout.h"

class CustomVideoRenderer;

class VideoSignleMonitorLayout : public VideoLayout
{
    Monitor*                focusedMonitor;
    CustomVideoRenderer*    videoRenderer;
public:
    VideoSignleMonitorLayout(Monitor*,Configuration*, QObject*, QWidget* uiWidget);
    ~VideoSignleMonitorLayout();

protected:
    virtual void        generateMonitorMatrice();
};

#endif // VIDEOSIGNLEMONITORLAYOUT_H
