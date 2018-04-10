#include <QGraphicsView>

#include "abstractsinglemonitorlayout.h"
#include "CustomObjects/customgraphicscene.h"

AbstractSingleMonitorLayout::AbstractSingleMonitorLayout(Monitor* monitor, Configuration *config, QObject* simWin)
    : AbstractLayout(config, simWin)
    , focusedMonitor(monitor)
{
    generateMonitorMatrice();
}

AbstractSingleMonitorLayout::~AbstractSingleMonitorLayout()
{
}

void AbstractSingleMonitorLayout::generateMonitorMatrice()
{
    if(focusedMonitor)
    {
        QGraphicsView *view = new QGraphicsView();
        CustomGraphicScene* m_graphScen = new CustomGraphicScene(focusedMonitor);
        m_graphScen->setSceneRect(0,0, Utils::getEnvironmentWidth()-DEFAULT_MARGIN, Utils::getEnvironmentHeight()-DEFAULT_MARGIN);

        view->setFixedSize(Utils::getEnvironmentWidth(), Utils::getEnvironmentHeight());
        QBrush red(QColor(250,50,50));
        view->setBackgroundBrush(red);
        view->setScene(m_graphScen);

        monitorGridLayout->addWidget(view, 0, 0);

        monitorMatriceGroup->setLayout(monitorGridLayout);
    }
}

