#include "mainwindow.h"
#include "rbtree.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QTime time=QTime::currentTime();
    timeslice = 6;
    time_left = timeslice;
    qsrand(time.msecsTo(QTime(0,0)));
    runtime = 0;
    time_to_add = 1;
    ui->setupUi(this);
    ui->CpuRuntime->display(0);
    ui->CpuTimeSlice->display(6);
    tree = new rbtree();
    ui->RbTreeWidget->tree = tree;
    name = "A";
    ui->NewProcessName->setText(name);
    connect(ui->NewProcessAdd, SIGNAL(clicked()), this, SLOT(AddNode()));
    //connect(ui->CpuTime, SIGNAL(editingFinished()), this, SLOT(CalculateIdealTime()));
    connect(ui->NewProcessRandomTime, SIGNAL(clicked()), this, SLOT(RandTime()));
    connect(ui->RunButton , SIGNAL(clicked()), this, SLOT(Run()));
    active_processes = 0;
    completed_processes = 0;
    sel_node = NULL;
}

MainWindow::~MainWindow()
{
    delete tree;
    delete ui;
}

void MainWindow::AddNode()
{
    struct process* new_pid = new struct process;
    new_pid->name = name;
    new_pid->vruntime = 0;
    new_pid->starttime = runtime;
    new_pid->endtime = -1;
    new_pid->maxtime = ui->NewProcessMaxTime->value();
    new_pid->exectime = 0;
    tree->insert_node(new_pid->vruntime, new_pid);
    active_processes++;
    ui->ActiveProcesses->setText(QString::number(active_processes));
    ui->RbTreeWidget->update();
    int c = name.count();
    int n = 0;
    for(int i = c-1; i >= 0; i--)
    {
        if (name[i] == QChar('Z'))
        {
            n++;
            name.remove(i,1);
            if (i == 0)
                name.append('A');
        }
        else
        {
            name[i] = name[i].toAscii() + 1;
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        name.append('A');
    }
    qDebug()<<"New process added" << new_pid->name;
    ui->NewProcessName->setText(name);
}

void MainWindow::UpdateSelected(rbnode* selected)
{
    sel_node = selected;
    if (selected != NULL)
    {
        ui->SelProcessName->setText(selected->content->name);
        ui->SelProcessTime->setText(QString::number(selected->content->vruntime));
        ui->SelProcessMaxTime->setText(QString::number(selected->content->maxtime));
        if (selected->content->maxtime == 0)
            ui->SelProcessCompletion->setValue(100);
        else
            ui->SelProcessCompletion->setValue(100 * selected->content->vruntime/selected->content->maxtime);
        ui->StartTime->setText(QString::number(selected->content->starttime));
        if (selected->content->endtime > -1)
              ui->EndTime->setText(QString::number(selected->content->endtime));
        else
              ui->EndTime->setText("");
        ui->IdealTime->setText(QString::number(selected->content->maxexectime));
    }
}

void MainWindow::CalculateIdealTime()
{
    //TODO - добавить?
}

void MainWindow::RandTime()
{
    ui->NewProcessMaxTime->setValue(1+qrand()%99);
}

void MainWindow::Run()
{
    int maxtime = ui->CpuTime->value();
    for (int time = 0; time < maxtime; )
    {
        if (tree->root == NULL)
        {
            qDebug() << "RUN::No process";
            time += (maxtime - time);
            break;
        }
        //Поиск минимального узла
        rbnode* current = tree->root;
        while (current->left != NULL)
            current = current->left;
        qDebug() << "RUN::Min exectime = " << current->content->vruntime;
        qDebug() << "exectime = " << current->content->exectime <<"/maxexectime = " << current->content->maxexectime;
        qDebug() << "Left time = " << (maxtime - time);
        if ((maxtime - time) >= (current->content->maxexectime - current->content->exectime))    //Если хватает времени, чтобы покрыть maxexectime и переключить/закончить процесс
        {
            time += (current->content->maxexectime - current->content->exectime);
            current->content->vruntime += (current->content->maxexectime - current->content->exectime);
            qDebug()<<"Vruntime: "<<current->content->vruntime;
            if (current->content->vruntime >= current->content->maxtime)
            {
                qDebug()<<"RUN::End of process"<<current->content->name;
                //Окончание выполнения процесса
                //Закинуть в таблицу
                current->content->endtime = runtime + time;
                ui->Table->setRowCount(ui->Table->rowCount() + 1);
                QTableWidgetItem* name = new QTableWidgetItem(current->content->name);
                QTableWidgetItem* idealtime = new QTableWidgetItem(QString::number(current->content->maxtime));
                QTableWidgetItem* actualtime = new QTableWidgetItem(QString::number(current->content->endtime - current->content->starttime));
                ui->Table->setItem(ui->Table->rowCount()-1,0,name);
                ui->Table->setItem(ui->Table->rowCount()-1,1,idealtime);
                ui->Table->setItem(ui->Table->rowCount()-1,2,actualtime);
                active_processes--;
                completed_processes++;
                delete current->content;
                tree->delete_node(current);
                if (tree->root == NULL)
                {
                    qDebug() << "RUN::No root";
                    break;
                }
                else
                    tree->root->update_ideal_time(tree->node_count, timeslice);
            }
            else
            {
                //Обновление времени рыботы, если не выполнился
                qDebug()<<"RUN::End of maxexectime for "<<current->content->name;
                process* temp = current->content;
                tree->delete_node(current);
                tree->insert_node(temp->vruntime, temp);
            }       
        }
        else
        {
            //Если не хватает времени
            qDebug()<<"RUN::Added "<<(maxtime - time)<<" to process"<<current->content->name;
            current->content->exectime += (maxtime - time);
            current->content->vruntime += (maxtime - time);
            time += (maxtime - time);
            break;
        }

    }
    UpdateSelected(sel_node);
    runtime += maxtime;
    ui->CpuTimeSlice->display(6 - runtime%6);
    ui->CpuRuntime->display(runtime);
    ui->RbTreeWidget->update();
    ui->CompletedProcesses->setText(QString::number(completed_processes));
    ui->ActiveProcesses->setText(QString::number(active_processes));
}
