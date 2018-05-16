#include "videosignlemonitorlayout.h"

#include <QtAV/QtAV>
#include <QtAVWidgets/QtAVWidgets>

#include "CustomWidgets/customvideorenderer.h"

using namespace QtAV;

VideoSignleMonitorLayout::VideoSignleMonitorLayout(Monitor* monitor, Configuration *config, QObject* simWin, QWidget *uiWidget)
    : VideoLayout(config, simWin, uiWidget)
    , focusedMonitor(monitor)
    , videoRenderer(NULL)
{
    generateMonitorMatrice();
}



VideoSignleMonitorLayout::~VideoSignleMonitorLayout()
{
    if(videoRenderer)
    {
        videoRenderer->disconnect();
        delete videoRenderer;
    }
}

void VideoSignleMonitorLayout::generateMonitorMatrice()
{
    if(focusedMonitor)
    {
        VideoRendererId v = VideoRendererId_OpenGLWidget;
    //           v = VideoRendererId_Widget;
    //           v = VideoRendererId_GLWidget2;
    //           v = VideoRendererId_OpenGLWidget;
    //           v = VideoRendererId_Direct2D;
    //           v = VideoRendererId_GDI;
    //           v = VideoRendererId_X11;
    //           v = VideoRendererId_XV;

        // reference: https://github.com/wang-bin/QtAV/tree/master/examples/videowall
        // https://superuser.com/questions/1125344/streaming-in-ffmpeg-using-rtp
        // https://trac.ffmpeg.org/wiki/StreamingGuide
        // https://andrewjprokop.wordpress.com/2013/09/30/understanding-session-description-protocol-sdp/

        videoRenderer = new CustomVideoRenderer(v);
        videoRenderer->renderer->widget()->setWindowFlags(videoRenderer->renderer->widget()->windowFlags()| Qt::FramelessWindowHint);
        videoRenderer->renderer->widget()->setAttribute(Qt::WA_DeleteOnClose);
        videoRenderer->renderer->widget()->setFixedWidth(Utils::getEnvironmentWidth());
        videoRenderer->renderer->widget()->setFixedHeight(Utils::getEnvironmentHeight());

        monitorGridLayout->addWidget(reinterpret_cast<CustomVideoRenderer*>(monitorMatrice[focusedMonitor->positionInMatrice.column][focusedMonitor->positionInMatrice.line].displayPanel)->renderer->widget(), 0, 0);

        videoRenderer->player = new AVPlayer;
#ifdef RTSP_TEST
        videoRenderer->sourceUrl = QString("rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov");
#else
        QVariantHash opt;
        // probably since ffmpeg 3.x:
        opt["protocol_whitelist"] = "file,udp,rtp";
        videoRenderer->player->setOptionsForFormat(opt);
        videoRenderer->sourceUrl = reinterpret_cast<CustomVideoRenderer*>(focusedMonitor->displayPanel)->sourceUrl;
#endif
        qInfo() << videoRenderer->sourceUrl;

        videoRenderer->player->setRenderer(videoRenderer->renderer);
        videoRenderer->player->play(videoRenderer->sourceUrl);

        monitorMatriceGroup->setLayout(monitorGridLayout);
    }
}
