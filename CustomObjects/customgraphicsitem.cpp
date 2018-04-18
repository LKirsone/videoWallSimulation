#include "customgraphicsitem.h"

SignalingObject::SignalingObject(QObject *parent)
    : QObject(parent)
{
}

void SignalingObject::emitMoveSignal(int id, QPointF pos, int w, int h)
{
    emit itemMoved(id, pos, w, h);
}

CustomGraphicsItem::CustomGraphicsItem()
    : QGraphicsRectItem()
    , signaller(new SignalingObject())
{
    itemID = -1;
}

CustomGraphicsItem::~CustomGraphicsItem()
{
    signaller->disconnect();
    delete signaller;
}
void CustomGraphicsItem::setID(int id)
{
    itemID = id;
}

QVariant CustomGraphicsItem::itemChange(GraphicsItemChange change, const QVariant & value)
{
    if (change == ItemPositionChange && scene())
    {
        // value is the new position.
//        QPointF newPos = ;
//        QRectF rect = scene()->sceneRect();
//        if (!rect.contains(newPos)) {
//            // Keep the item inside the scene rect.
//            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
//            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));

            //signaller->emitMoveSignal(itemID, value.toPointF(), (int)rect().width(), (int)rect().height());
//        }
    }
    return QGraphicsItem::itemChange(change, value);

}
