#-------------------------------------------------
#
# Project created by QtCreator 2018-04-09T22:32:39
#
#-------------------------------------------------

QT       += core gui network multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = VideoWallSimulation
TEMPLATE = app

# if libVLC is used, this must be uncomented
#INCLUDEPATH += D:/MagDarbs/SourceCode/VideoWallSimulation/Resources/VLC-Qt_1.1.0_win32_mingw/include
#LIBS+= -L"D:/MagDarbs/SourceCode/VideoWallSimulation/Resources/VLC-Qt_1.1.0_win32_mingw/bin" -llibVLCQtCore -llibVLCQtWidgets
#DEFINES += USE_LIBVLC
#FORMS += \
#    UI/test.ui
#end of libVLC

# if QtAV is used, this must be uncomented
QT += avwidgets
#end of QtAV


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CustomObjects/customgraphicscene.cpp \
    CustomWidgets/monitor.cpp \
    Layouts/abstractlayout.cpp \
    Layouts/abstractsinglemonitorlayout.cpp \
    Layouts/simulationlayout.cpp \
    Layouts/videolayout.cpp \
    Layouts/layoutframework.cpp \
    Utils/configuration.cpp \
    Utils/utils.cpp \
    main.cpp \
    mainwindow.cpp \
    Communication/communication.cpp \
    CustomObjects/customgraphicsitem.cpp \
    CustomWidgets/customvideorenderer.cpp \
    Layouts/videosignlemonitorlayout.cpp


HEADERS += \
    CustomObjects/customgraphicscene.h \
    CustomWidgets/monitor.h \
    Layouts/abstractlayout.h \
    Layouts/abstractsinglemonitorlayout.h \
    Layouts/simulationlayout.h \
    Layouts/layoutframework.h \
    Layouts/videolayout.h \
    Utils/configuration.h \
    Utils/const.h \
    Utils/ui_const.h \
    Utils/utils.h \
    mainwindow.h \
    Communication/communication.h \
    CustomObjects/customgraphicsitem.h \
    CustomWidgets/customvideorenderer.h \
    Layouts/videosignlemonitorlayout.h

DISTFILES +=
