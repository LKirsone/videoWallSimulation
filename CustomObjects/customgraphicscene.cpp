#include "customgraphicscene.h"

#include <QCoreApplication>
#include <QGraphicsSceneMouseEvent>

CustomGraphicScene::CustomGraphicScene()
    : QGraphicsScene()
    , ownerMonitor(NULL)
{ }

CustomGraphicScene::CustomGraphicScene(Monitor* owner)
    : QGraphicsScene()
    , ownerMonitor(owner)
{
}

void CustomGraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(ownerMonitor && event)
    {
        // probably in future need some better way to identify content update and monitor selection
        // but doubleClick doesn't work straight forward so for now, we'll use left and right clicks
        if(event->button() == Qt::LeftButton)
        {
            printf("LeftClick owenr IP: %s \n", ownerMonitor->ipAddress.toStdString().c_str());
            // event will be deleted by QT queue handler
            //ContentUpdateEvent* qEvent = new ContentUpdateEvent(ContentUpdateType::ADD_WINDOW, ownerMonitor->positionInMatrice.column, ownerMonitor->positionInMatrice.line);
            //QCoreApplication::postEvent(eventHandler, qEvent);
        }
        else if(event->button() == Qt::RightButton)
        {
            printf("RightClick owenr IP: %s \n", ownerMonitor->ipAddress.toStdString().c_str());
            // event will be deleted by QT queue handler
            emit monitorWasSelected(ownerMonitor->positionInMatrice.line, ownerMonitor->positionInMatrice.column);
        }
    }
}
