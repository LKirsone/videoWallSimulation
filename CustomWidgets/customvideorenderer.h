#ifndef CUSTOMVIDEORENDERER_H
#define CUSTOMVIDEORENDERER_H

#include <QWidget>
#include <QObject>
#include <QtAV/QtAV>
#include <QtAVWidgets/QtAVWidgets>


class CustomVideoRenderer : public QWidget
{
    Q_OBJECT
public:
    CustomVideoRenderer(QWidget *parent = 0);
    CustomVideoRenderer(QtAV::VideoRendererId id, QWidget *parent = 0);

    ~CustomVideoRenderer();
signals:
    void        monitorWasSelected(QPointF);

protected:
    // TODO: MOUSE CLICKS can't be received, videoRenderer actually eats them :/
    void        mousePressEvent(QMouseEvent *event);

    QtAV::VideoRenderer*    renderer;
    QtAV::AVPlayer*         player;
    QString                 sourceUrl;
    QPointF                 porisitonInMatice;


    friend class VideoLayout;
    friend class VideoSignleMonitorLayout;
};

#endif // CUSTOMVIDEORENDERER_H
