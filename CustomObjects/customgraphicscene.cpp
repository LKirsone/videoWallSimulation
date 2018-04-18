#include "customgraphicscene.h"

#include <QCoreApplication>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

CustomGraphicScene::CustomGraphicScene()
    : QGraphicsScene()
{ }


void CustomGraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
            printf("RightClick pos[%d; %d]\n", event->buttonDownScenePos(Qt::RightButton).x(), event->buttonDownScenePos(Qt::RightButton).y() );
            // event will be deleted by QT queue handler
            emit monitorWasSelected(event->buttonDownScenePos(Qt::RightButton));
        }

        // pass through
        QGraphicsScene::mousePressEvent(event);
    }
}
