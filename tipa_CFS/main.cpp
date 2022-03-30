#include <QtGui/QApplication>
#include "mainwindow.h"
#include "rbtree.h"

MainWindow* mainW;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    mainW = &w;
    w.show();
    return a.exec();
}
