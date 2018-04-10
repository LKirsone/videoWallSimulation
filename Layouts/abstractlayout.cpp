#include "abstractlayout.h"

#include <QGraphicsView>

#include "CustomObjects/customgraphicscene.h"


AbstractLayout::AbstractLayout(Configuration *config, QObject* simWin)
    : SimulationLayout(config, simWin)
{
    if(config)
    {
        config->simulationType = TYPE_ABSTRACT;
        //if(config->isConfigInstalled)
        {
            // maybe the config could be stored in some file in future, so that next time we re-enter simulator
            // we can just load it from stored config
        }
        //else
        {
            setDefaultConfig();
        }

        if(config->isMonitorFocused == false)
        {
            generateMonitorMatrice();
        }
    }
}

void AbstractLayout::generateMonitorMatrice()
{
    rowsInMonitorMatrice = config->monitorsPerColumn;
    columnsInMonitorMatrice = config->monitorsPerRow;

    monitorMatrice = new Monitor*[rowsInMonitorMatrice];

    for(unsigned int i = 0; i < config->monitorsPerColumn; i++)
    {
        monitorMatrice[i] = new Monitor[columnsInMonitorMatrice];
        for(unsigned int j = 0; j < config->monitorsPerRow; j++)
        {
            monitorMatrice[i][j].displayPanel = new QGraphicsView();
            //monitorMatrice[i][j].contentController = new AbstractContentController(monitorMatrice[i][j].displayPanel);
            monitorMatrice[i][j].ipAddress = "";
            monitorMatrice[i][j].positionInMatrice.line = i;
            monitorMatrice[i][j].positionInMatrice.column = j;


            CustomGraphicScene* m_graphScen = new CustomGraphicScene(&monitorMatrice[i][j]);
            connect(m_graphScen, SIGNAL(monitorWasSelected(uint,uint)), this, SLOT(monitorSelected(uint,uint)));
            m_graphScen->setSceneRect(0,0, Utils::getMonitorWidth(config->monitorsPerRow)-DEFAULT_MARGIN, Utils::getMonitorHeight(config->monitorsPerColumn)-DEFAULT_MARGIN);

            static_cast<QGraphicsView*>(monitorMatrice[i][j].displayPanel)->setFixedSize(Utils::getMonitorWidth(config->monitorsPerRow), Utils::getMonitorHeight(config->monitorsPerColumn));
            QBrush red(QColor(250-(50*i),50+(50*j),50));
            static_cast<QGraphicsView*>(monitorMatrice[i][j].displayPanel)->setBackgroundBrush(red);
            static_cast<QGraphicsView*>(monitorMatrice[i][j].displayPanel)->setScene(m_graphScen);

            monitorGridLayout->addWidget(monitorMatrice[i][j].displayPanel, i, j);
        }
    }
    monitorMatriceGroup->setLayout(monitorGridLayout);
}
