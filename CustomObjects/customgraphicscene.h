#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include "CustomWidgets/monitor.h"

class CustomGraphicScene : public QGraphicsScene
{
    Q_OBJECT
    Monitor*    ownerMonitor;
public:
    CustomGraphicScene();
    CustomGraphicScene(Monitor*);

signals:
    void        monitorWasSelected(unsigned int row, unsigned int column);

protected:
    // doesn't work with mousePressEvent overwritten, so yeah.. for now out!
    //void mouseDoubleClickEvent( QGraphicsSceneMouseEvent * e );

    void        mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMSCENE_H
