#include "mainwindow.h"
#include <QApplication>
#define USE_QT_AV
#ifdef USE_QT_AV
#include <QtAVWidgets/QtAVWidgets>
#include <QtAV_Global.h>
#endif
#include <QDebug>

void QtAVLogHandler(void*, int, const char* format, va_list args)
{
    QString message;
    message.vsprintf(format, args);
    qInfo() << message;
}

int main(int argc, char *argv[])
{
#ifdef USE_QT_AV
    QtAV::Widgets::registerRenderers();
    QtAV::setFFmpegLogHandler(QtAVLogHandler);
    QtAV::setFFmpegLogLevel("debug");
    QtAV::setLogLevel(QtAV::LogDebug);
#endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
