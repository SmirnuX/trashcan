#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.dx = 5;
    w.dy = 4;
    w.show();
    w.update();

    return a.exec();
}
