#ifndef UI_CONST_H
#define UI_CONST_H

#include <QStringList>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

const QString ABSTR_SIM_STR = "abstract";
const QString VIDEO_SIM_STR = "video";
const QString STRING_STOP = "stop";
const QString STRING_START = "start";

struct UI_HeaderData
{
    const QStringList   simOptions = { ABSTR_SIM_STR, VIDEO_SIM_STR};
    QComboBox*          selectSimOption;
    QPushButton*        startStopSim;
    QLineEdit*          ipAddress;
    QLabel*             statusLabel;
};

#endif // UI_CONST_H
