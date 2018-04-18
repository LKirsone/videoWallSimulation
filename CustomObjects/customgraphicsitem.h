#ifndef CUSTOMGRAPHICSITEM_H
#define CUSTOMGRAPHICSITEM_H

#include <QGraphicsRectItem>
#include <QObject>

//dirty hack
class SignalingObject : public QObject
{
    Q_OBJECT
public:
    explicit SignalingObject(QObject *parent = nullptr);

    void                emitMoveSignal(int, QPointF, int, int);
signals:
    void                itemMoved(int, QPointF, int, int);
};

class CustomGraphicsItem : public QGraphicsRectItem
{
    int                 itemID;
public:
    CustomGraphicsItem();
    ~CustomGraphicsItem();

    void                setID(int);
    virtual QVariant    itemChange(GraphicsItemChange change, const QVariant & value);

    SignalingObject*     signaller;
};

#endif // CUSTOMGRAPHICSITEM_H
