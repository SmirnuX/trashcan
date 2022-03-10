#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include "rbtree.h"



namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void UpdateSelected(rbnode* selected);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSignalMapper* mapper;
    rbtree* tree;
    QString name;
    int runtime;
    int timeslice;
    int time_left;
    int time_to_add;
    int active_processes;
    int completed_processes;
    rbnode* sel_node;

private slots:
    void AddNode();
    void CalculateIdealTime();
    void RandTime();
    void Run();
};

extern MainWindow* mainW;

#endif // MAINWINDOW_H
