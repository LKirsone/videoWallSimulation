#include "abstractlayout.h"

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QHostAddress>
#include "CustomObjects/customgraphicscene.h"
#include "CustomObjects/customgraphicsitem.h"

//#define CONTROL_BITE_ORDER <- don't use it, because QT handles the byte order in it's core
#ifdef CONTROL_BITE_ORDER
#include <QtEndian>
#endif


AbstractLayout::AbstractLayout(Configuration *config, QObject* simWin, QWidget *uiWidget)
    : SimulationLayout(config, simWin, uiWidget)
    , connect(new QTcpSocket())
    , singleScreenWidthRatio(0)
    , singleScreenHeightRatio(0)
    , m_graphScene(NULL)
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

        // calculate the ratio between physical screen resolution and the one available in simulation environment
        if(config->physicalMonitorResolutionX && config->physicalMonitorResolutionY)
        {
            singleScreenWidthRatio = Utils::getMonitorWidth(config->monitorsPerRow) / (float)config->physicalMonitorResolutionX;
            singleScreenHeightRatio = Utils::getMonitorHeight(config->monitorsPerColumn) / (float)config->physicalMonitorResolutionY;
        }

        if(config->isMonitorFocused == false)
        {
            generateMonitorMatrice();
        }
    }
}

AbstractLayout::~AbstractLayout()
{
    m_graphScene->disconnect();
    connect->disconnect();

    delete m_graphScene;
    delete connect;
}

bool AbstractLayout::connectToServer(QString address)
{
    bool result = false;

    if (connect)
    {
        // resolve the IP
        QHostAddress ipAddress(address);

        result = QAbstractSocket::IPv4Protocol == ipAddress.protocol() || QAbstractSocket::IPv6Protocol == ipAddress.protocol();
        if(result == false)
        {
            emit invalidIpAddress();
        }
        else
        {
            QObject::connect(connect, SIGNAL(connected()), this, SLOT(isConnected()));
            QObject::connect(connect, SIGNAL(disconnected()), this, SLOT(isDisconnected()));
            QObject::connect(connect, SIGNAL(readyRead()), this, SLOT(contentUpdate()));

            connect->connectToHost(ipAddress, ABSTRACT_SIM_SERVER_PORT);
        }
    }
    return result;
}

void AbstractLayout::generateMonitorMatrice()
{
    rowsInMonitorMatrice = config->monitorsPerColumn;
    columnsInMonitorMatrice = config->monitorsPerRow;

    m_graphScene = new CustomGraphicScene();
    qreal sceneWidth = Utils::getMonitorWidth(config->monitorsPerRow) * config->monitorsPerRow;
    qreal sceneHeight = Utils::getMonitorHeight(config->monitorsPerColumn) * config->monitorsPerColumn;
    m_graphScene->setSceneRect(0,0, sceneWidth,sceneHeight);

    qInfo() << "Scene size: " <<  sceneWidth << ", " << sceneHeight;

    // TEST CODE
    QPen something(QColor(0,60,70));
    m_graphScene->addEllipse((qreal)(80), (qreal)(80), sceneWidth - 160, sceneHeight- 160, something);
    // END OF TEST CODE

    QObject::connect(m_graphScene, SIGNAL(monitorWasSelected(QPointF)), this, SLOT(monitorSelected(QPointF)));

    monitorMatrice = new Monitor*[rowsInMonitorMatrice];

    for(unsigned int i = 0; i < config->monitorsPerColumn; i++)
    {
        monitorMatrice[i] = new Monitor[columnsInMonitorMatrice];
        for(unsigned int j = 0; j < config->monitorsPerRow; j++)
        {
            QGraphicsView* displayPanel =  new QGraphicsView();;

            displayPanel->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
            displayPanel->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
            //monitorMatrice[i][j].contentController = new AbstractContentController(monitorMatrice[i][j].displayPanel);
            monitorMatrice[i][j].url = "";
            monitorMatrice[i][j].positionInMatrice.line = i;
            monitorMatrice[i][j].positionInMatrice.column = j;

            displayPanel->setFixedSize(Utils::getMonitorWidth(config->monitorsPerRow), Utils::getMonitorHeight(config->monitorsPerColumn));
            QBrush red(QColor(250,250,200));
            displayPanel->setBackgroundBrush(red);
            displayPanel->setScene(m_graphScene);

            // get virtual monitor screen center coordinates
            monitorMatrice[i][j].monitorPosition.setX(Utils::getMonitorWidth(config->monitorsPerRow) * (j + 0.5));
            monitorMatrice[i][j].monitorPosition.setY(Utils::getMonitorHeight(config->monitorsPerColumn) * (i + 0.5));
            // set the focus to monitor center
            displayPanel->centerOn(monitorMatrice[i][j].monitorPosition);

            monitorMatrice[i][j].displayPanel = displayPanel;
            monitorGridLayout->addWidget(monitorMatrice[i][j].displayPanel, i, j);
        }
    }

    monitorMatriceGroup->setLayout(monitorGridLayout);
}

void AbstractLayout::updateMonitorMatrice()
{
    float posX = -1;
    float posY = -1;

    QBrush blueBrush(Qt::blue);
    QPen pen(QColor::fromRgb(250, 250, 250));

    m_graphScene->clear();
    if(!windowsList.empty())
    {
        for(QList<ClientWindow>::iterator it = windowsList.begin(); it != windowsList.end(); ++it)
        {
            // trasnlate the original position into simulator coordinate plate
            posX = (*it).m_rect.x() * singleScreenWidthRatio;
            posY = (*it).m_rect.y() * singleScreenHeightRatio;

            CustomGraphicsItem* item = reinterpret_cast<CustomGraphicsItem*>(m_graphScene->addRect(posX, posY, (*it).m_rect.width() * singleScreenWidthRatio, (*it).m_rect.height() * singleScreenHeightRatio, pen, blueBrush));
            item->setID((*it).m_hwnd);
            item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

            //QObject::connect(item->signaller, SIGNAL(itemMoved(int, QPointF, int, int)), this, SLOT(onMove(int, QPointF, int, int)));
        }
    }
    m_graphScene->update();
}

void AbstractLayout::isConnected()
{
    emit hasConnect(0);
}

void AbstractLayout::isDisconnected()
{
    emit hasDisconnect(0);
}

void AbstractLayout::onMove(int id, QPointF position, int width, int height)
{
    QByteArray packet;
    QDataStream dataStream(&packet, QIODevice::WriteOnly);

    dataStream << (int)MT_CONFIG << id << position.x() << position.y() << width << height;

    connect->write(packet);
}

void AbstractLayout::contentUpdate()
{
    // data available to be read
    QDataStream dataStream(connect->readAll());
    int type = 0;
    int desktopWidth = 0;
    int desktopHeight = 0;

#ifdef CONTROL_BITE_ORDER
    static QDataStream::ByteOrder currentByteOrder = QSysInfo::ByteOrder == QSysInfo::LittleEndian
                                                ? QDataStream::LittleEndian
                                                : QDataStream::BigEndian;

    static bool validateEndians = dataStream.byteOrder() != currentByteOrder;

    if(validateEndians)
    {
        qInfo() << "byte order must be changed" << dataStream.byteOrder() << " != " << currentByteOrder;
        dataStream.setByteOrder(currentByteOrder);
    }

#endif

    if(config->isMonitorFocused)
    {
        emit startManualContentUpdate(&dataStream);
    }
    else
    {
        dataStream >> type;        

        // Sends data about windows
        if (type == MT_CONFIG)
        {

            // currently not actually used....
            dataStream >> desktopWidth >> desktopHeight;

            qInfo() << "desktop width: " << desktopWidth << " desktop height " << desktopHeight;

            windowsList.clear();

            // gets all sent windows
            while (!dataStream.atEnd())
            {
                int hwnd = -1;
                int left, top, right, bottom;
                dataStream >> hwnd >> left >> top >> right >> bottom;

                qInfo() << "hwnd " << hwnd  << " left " << left << " top " << top  << " right " << right << " bottom " << bottom;;

                ClientWindow tmp;
                dataStream.readRawData(tmp.m_title, 255);

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

//        QByteArray packet;
//        QDataStream writeData(&packet, QIODevice::WriteOnly);

//        // asks for app list
//        writeData << (int)3;

//        client.write(packet);

    // sends desktop application data
    /*} else if (type == MT_APP_DATA)
    {
        QStringList files;
        while (!dataStream.atEnd())
        {
            char buff[255];
            dataStream.readRawData(buff, 255);
            QString file(buff);
            files.append(buff);
        }

        m_window.setApps(files);*/
    }
}
