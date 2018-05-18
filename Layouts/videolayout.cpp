#include "videolayout.h"

#include <QtAV/QtAV>
#include <QtAVWidgets/QtAVWidgets>

#include "CustomWidgets/customvideorenderer.h"

using namespace QtAV;

//#define RTSP_TEST

VideoLayout::VideoLayout(Configuration *config, QObject* simWin, QWidget *uiWidget)
    : SimulationLayout(config, simWin, uiWidget)
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

//        if(config->physicalMonitorResolutionX && config->physicalMonitorResolutionY)
//        {
//            singleScreenWidthRatio = Utils::getMonitorWidth(config->monitorsPerRow) / (float)config->physicalMonitorResolutionX;
//            singleScreenHeightRatio = Utils::getMonitorHeight(config->monitorsPerColumn) / (float)config->physicalMonitorResolutionY;
//        }

        if(config->isMonitorFocused == false)
        {
            generateMonitorMatrice();
        }
    }
}

bool VideoLayout::connectToServer(QString ipAddress)
{
//#define ONE_BY_ONE_TEST
#ifdef ONE_BY_ONE_TEST
    static int i = 0;
    static int j = 0;
#else
    if(config->monitorsPerColumn > 0 && config->monitorsPerRow > 0)
    {
    // TODO: prepare bunch of new connects for each monitor
        for(unsigned int i = 0; i < config->monitorsPerColumn; i++)
        {
            for(unsigned int j = 0; j < config->monitorsPerRow; j++)
            {
#endif
                CustomVideoRenderer* videoRenderer = reinterpret_cast<CustomVideoRenderer*>(monitorMatrice[i][j].displayPanel);
                videoRenderer->player->play(videoRenderer->sourceUrl);

                int counter1 = 0;
                int counter2 = 0;
                while(counter1++ < 500000) {while(counter2++ < 500000);};
#ifndef ONE_BY_ONE_TEST
            }
        }
    }
#else
    j++;
    if(j == config->monitorsPerRow)
    {
        if(i < config->monitorsPerColumn)
        {
            i++;
            j=0;
        }
    }
#endif
    return true;
}

void VideoLayout::generateMonitorMatrice()
{
    rowsInMonitorMatrice = config->monitorsPerColumn;
    columnsInMonitorMatrice = config->monitorsPerRow;

    monitorMatrice = new Monitor*[rowsInMonitorMatrice];

    VideoRendererId v = VideoRendererId_OpenGLWidget;
//           v = VideoRendererId_Widget;
//           v = VideoRendererId_GLWidget2;
//           v = VideoRendererId_OpenGLWidget;
//           v = VideoRendererId_Direct2D;
//           v = VideoRendererId_GDI;
//           v = VideoRendererId_X11;
//           v = VideoRendererId_XV;

    for(unsigned int i = 0; i < config->monitorsPerColumn; i++)
    {
        monitorMatrice[i] = new Monitor[columnsInMonitorMatrice];
        for(unsigned int j = 0; j < config->monitorsPerRow; j++)
        {
            monitorMatrice[i][j].url = "";
            monitorMatrice[i][j].positionInMatrice.line = i;
            monitorMatrice[i][j].positionInMatrice.column = j;

            // reference: https://github.com/wang-bin/QtAV/tree/master/examples/videowall
            // https://superuser.com/questions/1125344/streaming-in-ffmpeg-using-rtp
            // https://trac.ffmpeg.org/wiki/StreamingGuide
            // https://andrewjprokop.wordpress.com/2013/09/30/understanding-session-description-protocol-sdp/

            CustomVideoRenderer* videoRenderer = new CustomVideoRenderer(v);
            videoRenderer->renderer->widget()->setWindowFlags(videoRenderer->renderer->widget()->windowFlags()| Qt::FramelessWindowHint);
            videoRenderer->renderer->widget()->setAttribute(Qt::WA_DeleteOnClose);
//#define NO_SCALING_TEST
#ifdef NO_SCALING_TEST
            videoRenderer->renderer->widget()->setFixedWidth(1920);
            videoRenderer->renderer->widget()->setFixedHeight(1080);
            videoRenderer->renderer->widget()->move(0, 0);
#else
            videoRenderer->renderer->widget()->setFixedWidth(Utils::getMonitorWidth(config->monitorsPerRow));
            qInfo() << "monitor width: " << Utils::getMonitorWidth(config->monitorsPerRow) << "  monitor height: " << Utils::getMonitorHeight(config->monitorsPerColumn);
            videoRenderer->renderer->widget()->setFixedHeight(Utils::getMonitorHeight(config->monitorsPerColumn));
            videoRenderer->renderer->widget()->move(j*Utils::getMonitorWidth(config->monitorsPerRow), i*Utils::getMonitorHeight(config->monitorsPerColumn));
#endif
            monitorMatrice[i][j].displayPanel = videoRenderer;
            monitorGridLayout->addWidget(reinterpret_cast<CustomVideoRenderer*>(monitorMatrice[i][j].displayPanel)->renderer->widget(), i, j);
            videoRenderer->player = new AVPlayer;

//#define RTSP_TEST
#ifdef RTSP_TEST
             videoRenderer->player = new AVPlayer;
            videoRenderer->player->audio()->setMute(true);
            videoRenderer->sourceUrl = QString("rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov");
#else
            QVariantHash opt;
            // probably since ffmpeg 3.x:
            opt["protocol_whitelist"] = "file,udp,rtp";

            //opt["probesize"] = "10240";
            //opt["analyzeduration"] = "10000000";
            opt["flush_packets"] = "1";

            //vcodec_opt["vcodec"] = "libx264";
            opt["strict"] = "strict";
            opt["preset"] = "faster";
            //opt["scale"] = "scale=w=300:h=200:force_original_aspect_ratio=decrease";

            //opt["acodec"] = "copy";
            //opt["framerate"] = "13";

            opt["fflags"] = "nobuffer";

            qInfo() << "Source ratio " << videoRenderer->renderer->sourceAspectRatio();
            videoRenderer->player->setOptionsForFormat(opt);
            videoRenderer->player->audio()->setMute(true);
#define TEST_SERVER
#ifdef TEST_SERVER
            videoRenderer->sourceUrl = QString("D:/MagDarbs/SourceCode/VideoWallSimulation/ServerCfg/server/test%1.sdp").arg((i*config->monitorsPerRow)+j);
#else
            videoRenderer->sourceUrl = QString("C:/simulation/SourceCode/VideoWallSimulation/ServerCfg/saved_sdp_file%1").arg((i*config->monitorsPerRow)+j);
#endif
#endif
            qInfo() << videoRenderer->sourceUrl;

            videoRenderer->player->setRenderer(videoRenderer->renderer);

            QObject::connect(videoRenderer, SIGNAL(monitorWasSelected(QPointF)), this, SLOT(monitorSelected(QPointF)));
            QObject::connect(videoRenderer->player, SIGNAL(error(QtAV::AVError)), this, SLOT(error(QtAV::AVError)));
            QObject::connect(videoRenderer->player, SIGNAL(started()), this, SLOT(started()));
            QObject::connect(videoRenderer->player, SIGNAL(paused(bool)), this, SLOT(paused(bool)));
            QObject::connect(videoRenderer->player, SIGNAL(stopped()), this, SLOT(stopped()));
        }
    }

    monitorMatriceGroup->setLayout(monitorGridLayout);
}


void VideoLayout::contentUpdate()
{
    // video layout use RTP to receive the expected data, updates are handled in QtAV library level
}
