#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //autofit the size of the widget display
    //w.showMaximized();
    return a.exec();
}
