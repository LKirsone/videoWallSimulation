#include "customvideorenderer.h"
#include <QMouseEvent>
using namespace QtAV;

CustomVideoRenderer::CustomVideoRenderer(QWidget *parent)
    : QWidget(parent)
    , player(NULL)
{

}

CustomVideoRenderer::CustomVideoRenderer(VideoRendererId id, QWidget *parent)
    : QWidget(parent)
    , player(NULL)
{
    renderer = VideoRenderer::create(id);
}

CustomVideoRenderer::~CustomVideoRenderer()
{

}

void CustomVideoRenderer::mousePressEvent(QMouseEvent *event)
{
    if(event)
    {
        // probably in future need some better way to identify content update and monitor selection
        // but doubleClick doesn't work straight forward so for now, we'll use left and right clicks
        if(event->button() == Qt::LeftButton)
        {
            printf("LeftClick  pos[%d; %d]\n", event->pos().x(), event->pos().y());
            // event will be deleted by QT queue handler
            //ContentUpdateEvent* qEvent = new ContentUpdateEvent(ContentUpdateType::ADD_WINDOW, ownerMonitor->positionInMatrice.column, ownerMonitor->positionInMatrice.line);
            //QCoreApplication::postEvent(eventHandler, qEvent);
        }
        else if(event->button() == Qt::RightButton)
        {
            printf("RightClick pos[%d; %d]\n", event->pos().x(), event->pos().y() );
            // event will be deleted by QT queue handler
            emit monitorWasSelected(porisitonInMatice);
        }

        // pass through
        QWidget::mousePressEvent(event);
    }
}
