#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>
#include "Utils/const.h"

class Monitor : public QWidget
{
    Q_OBJECT
protected:
    //ContentController*  contentController;
    QWidget*            displayPanel;
    QString             ipAddress;
    Position            positionInMatrice;
    void*               args; // pointer to possibly necessary parameters depending on monitor use

public:
    Monitor(QWidget *parent = 0);
    ~Monitor();

    virtual void        closeEvent(QCloseEvent*);

signals:
    void                monitorClosed();

private:

    friend class AbstractLayout;
    friend class AbstractSingleMonitorLayout;
    friend class VideoLayout;
    friend class VideoSingleMonitorLayout;
    friend class SimulationLayout;
    friend class CustomGraphicScene;
};

#endif // MONITOR_H
