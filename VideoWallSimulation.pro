#-------------------------------------------------
#
# Project created by QtCreator 2018-04-09T22:32:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoWallSimulation
TEMPLATE = app

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
    Utils/configuration.cpp \
    Utils/utils.cpp \
    main.cpp \
    mainwindow.cpp


HEADERS += \
    CustomObjects/customgraphicscene.h \
    CustomWidgets/monitor.h \
    Layouts/abstractlayout.h \
    Layouts/abstractsinglemonitorlayout.h \
    Layouts/simulationlayout.h \
    Layouts/videolayout.h \
    Utils/configuration.h \
    Utils/const.h \
    Utils/ui_const.h \
    Utils/utils.h \
    mainwindow.h

FORMS +=
