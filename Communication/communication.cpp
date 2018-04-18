#include "communication.h"
#include <QHostAddress>

Communication::Communication(QObject *parent) : QObject(parent)
{}

Communication::~Communication()
{}

bool Communication::setConnectionProfile(QString& address, unsigned int port)
{
    return false;

}

void Communication::onUiUpdate(ContentUpdateType, QDataStream*)
{

}
