#ifndef CONST_H
#define CONST_H

#include <QRect>
#include <QWindow>

#define OK          0x00
#define ERROR       0xF0
#define ERROR_MEM   0xF1

#define SCENE_SELECTED_EVT_ID   (QEvent::User + 1)
#define MONITOR_CLOSED_EVT_ID   (QEvent::User + 2)
#define CONTENT_UPDATE_EVT_ID   (QEvent::User + 3)

#define ABSTRACT_SIM_SERVER_PORT    8888

enum MessageTypes
{
    MT_INVALID = -1,
    MT_INIT_RATIO,
    MT_CONFIG,
    MT_APP_DATA
};

enum UniversalType
{
    TYPE_UNKNOWN = -1,
    TYPE_ABSTRACT,
    TYPE_ABSTRACT_SINGLE_MONITOR,
    TYPE_VIDEO,
    TYPE_VIDEO_SINGLE_MONITOR
};

enum ContentUpdateType
{
    ADD_WINDOW,
    REMOVE_WINDOW,
    MOVE_WINDOW,
    POSITION_CLICKED,
};

struct Position
{
    unsigned int line;
    unsigned int column;

    Position() { line = 0; column = 0;}
};

struct ClientWindow {
    int m_hwnd;
    QRect m_rect;
    QWindow *m_item;
    char m_title[255];
};
#endif // CONST_H
