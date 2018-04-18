#include <QGraphicsView>
#include <QGraphicsItem>

#include "abstractsinglemonitorlayout.h"
#include "CustomObjects/customgraphicscene.h"
#include "CustomObjects/customgraphicsitem.h"

AbstractSingleMonitorLayout::AbstractSingleMonitorLayout(Monitor* monitor, Configuration *config, QObject* simWin)
    : AbstractLayout(config, simWin)
    , focusedMonitor(monitor)
{
    if(focusedMonitor && config->physicalMonitorResolutionX && config->physicalMonitorResolutionY)
    {
        fullScreenWidthRatio = Utils::getEnvironmentWidth() / (float)config->physicalMonitorResolutionX ;
        fullScreenHeightRatio = Utils::getEnvironmentHeight() / (float)config->physicalMonitorResolutionY;

        monitorPositionX = (Utils::getMonitorWidth(config->monitorsPerRow) * focusedMonitor->positionInMatrice.column)/singleScreenWidthRatio;
        monitorPositionY = (Utils::getMonitorHeight(config->monitorsPerColumn) * focusedMonitor->positionInMatrice.line)/singleScreenHeightRatio;

        qInfo() << "POS X: " << monitorPositionX << ", POS Y: " << monitorPositionY;
    }
    qInfo() << "AbstractSingleMonitorLayout::focusedMonitor is " << focusedMonitor;

    generateMonitorMatrice();
}

AbstractSingleMonitorLayout::~AbstractSingleMonitorLayout()
{
}

void AbstractSingleMonitorLayout::onManualUpdate(QDataStream* dataStream)
{
    if(dataStream)
    {
        int type;

        *dataStream >> type;

        // Sends data about windows
        if (type == MT_CONFIG)
        {
            int desktopWidth = 0;
            int desktopHeight = 0;

            // currently not actually used....
            *dataStream >> desktopWidth >> desktopHeight;

            windowsList.clear();

            // gets all sent windows
            while (!dataStream->atEnd())
            {
                int hwnd = -1;
                int left, top, right, bottom;
                *dataStream >> hwnd >> left >> top >> right >> bottom;

                ClientWindow tmp;
                dataStream->readRawData(tmp.m_title, 255);

                // sets window template for client application

                tmp.m_hwnd = hwnd;

                //if (tmp.m_hwnd == m_window.winId()) continue;

                QRect rect;
                rect.setRect(left, top, right - left, bottom - top);
                tmp.m_rect = rect;

                // adds it to window list
                windowsList.append(tmp);
            }
            updateMonitorMatrice();
        }
    }
}

void AbstractSingleMonitorLayout::onMove(int id, QPointF position, int width, int height)
{
//    QByteArray packet;
//    QDataStream dataStream(&packet, QIODevice::WriteOnly);

//    dataStream << (int)1 << id << position.x() << position.y() << width << height;

//    connect->write(packet);
}

void AbstractSingleMonitorLayout::generateMonitorMatrice()
{
    // TODO: FIX THIS
    if(focusedMonitor)
    {
        QBrush brush(QColor(250,250,200));
        QGraphicsView *view = new QGraphicsView();
        m_graphScene = new CustomGraphicScene();

        m_graphScene->setSceneRect(0,0, Utils::getEnvironmentWidth(), Utils::getEnvironmentHeight());
        view->setFixedSize(Utils::getEnvironmentWidth(), Utils::getEnvironmentHeight());
        view->setBackgroundBrush(brush);
        view->setScene(m_graphScene);

        view->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
        view->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

        monitorGridLayout->addWidget(view, 0, 0);

        monitorMatriceGroup->setLayout(monitorGridLayout);
    }
}


void AbstractSingleMonitorLayout::updateMonitorMatrice()
{
    float posX = -1;
    float posY = -1;
    float width = -1;
    float height = -1;
    QBrush blueBrush(Qt::blue);
    QPen pen(QColor::fromRgb(250, 250, 250));

    qInfo() << "updateMonitorMatrice: POS X: " << monitorPositionX << ", POS Y: " << monitorPositionY;

    qInfo() << "updateMonitorMatrice::focusedMonitor is " << focusedMonitor;

    m_graphScene->clear();
    if(!windowsList.empty())
    {
        for(QList<ClientWindow>::iterator it = windowsList.begin(); it != windowsList.end(); ++it)
        {
            // trasnlate the original coordinates to local coordinate plate
            // by considering monitorX and monitorY as 0,0 point of system
            // this will allow us to draw the data without calculating if they fit to screen,
            // they'll just be out of screen
            posX = ((*it).m_rect.x() - monitorPositionX) * fullScreenWidthRatio;
            posY = ((*it).m_rect.y() - monitorPositionY) * fullScreenHeightRatio;

            width = (*it).m_rect.width() * fullScreenWidthRatio;
            height = (*it).m_rect.height() * fullScreenHeightRatio;

            qInfo() << "posX:" << posX << " posY:" << posY << " width:" << width << " height:" << height;

            CustomGraphicsItem* item = reinterpret_cast<CustomGraphicsItem*>(m_graphScene->addRect(posX, posY, width, height, pen, blueBrush));
            item->setID((*it).m_hwnd);
            item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

            //QObject::connect(item->signaller, SIGNAL(itemMoved(int, QPointF, int, int)), this, SLOT(onMove(int, QPointF, int, int)));
        }
    }
    m_graphScene->update();
}
