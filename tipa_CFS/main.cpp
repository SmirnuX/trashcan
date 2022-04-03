#include <QApplication>

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

/*  TODO
 * - fix crash (at least one crash when last node left)
 * - add process names and completion to main surface
 * - add several cores
 * - translate all comments to English and program
 * - add screenshot to trashcan README
 * - add download links to trashcan README
 * */
