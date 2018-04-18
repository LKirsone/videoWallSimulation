#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

#include "Utils/configuration.h"
#include "Layouts/layoutframework.h"
#include "Communication/communication.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget*            mainWidget;

    Configuration       config;
    LayoutFramework*    simulationLayout;

    Communication       communication;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void                disableMainWindow();
    void                enableMainWindow();

private:
};

#endif // MAINWINDOW_H
