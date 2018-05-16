#include "mainwindow.h"
#include <QApplication>
#ifdef USE_QT_AV
#include <QtAVWidgets/QtAVWidgets>
#endif

int main(int argc, char *argv[])
{
#ifdef USE_QT_AV
    QtAV::Widgets::registerRenderers();
#endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
