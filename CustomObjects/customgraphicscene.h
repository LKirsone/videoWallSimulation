#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QPointF>
#include "CustomWidgets/monitor.h"

class CustomGraphicScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CustomGraphicScene();

signals:
    void        monitorWasSelected(QPointF point);

protected:
    // doesn't work with mousePressEvent overwritten, so yeah.. for now out!
    //void mouseDoubleClickEvent( QGraphicsSceneMouseEvent * e );

    void        mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMSCENE_H
