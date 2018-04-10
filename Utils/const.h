#ifndef CONST_H
#define CONST_H

#define OK          0x00
#define ERROR       0xF0
#define ERROR_MEM   0xF1

#define SCENE_SELECTED_EVT_ID   (QEvent::User + 1)
#define MONITOR_CLOSED_EVT_ID   (QEvent::User + 2)
#define CONTENT_UPDATE_EVT_ID   (QEvent::User + 3)

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
#endif // CONST_H
