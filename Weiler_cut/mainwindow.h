#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include "math.h"
#include "vector"

namespace Ui {
    class MainWindow;
}

void DrawVeyler(QPainter* painter, double dx, double dy);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent*)
    {
        QPainter a(this);
        DrawVeyler(&a, dx, dy);
    }

    void keyPressEvent(QKeyEvent *ev)
    {
        switch(ev->key())
        {
        case Qt::Key_Up:
            dy -=0.1;
            break;
        case Qt::Key_Down:
            dy +=0.1;
            break;
        case Qt::Key_Right:
            dx +=0.1;
            break;
        case Qt::Key_Left:
            dx -=0.1;
            break;
        }
        update();
    }

    double dx;
    double dy;

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

struct Point2D
{
    Point2D(double a, double b)
    {
        x = a;
        y = b;
        intersec = 0;
        entered = false;
    }
    Point2D(double a, double b, int i)
    {
        x = a;
        y = b;
        intersec = i;
        entered = false;
    }

    Point2D()
    {
        entered = false;
    }

    double x, y;
    int intersec;   //-1 - РІС…РѕРґ РІ РјРЅРѕРіРѕСѓРіРѕР»СЊРЅРёРє, 1 - РІС‹С…РѕРґ, 0 - РЅРµ РѕС‚РЅРѕСЃРёС‚СЃСЏ Рє РїРµСЂРµСЃРµС‡РµРЅРёСЏРј
    bool entered;
};

double scalar(Point2D a, Point2D b);

bool proj_intersec(double a, double b, double c, double d);

struct line {
        double a, b, c;

        line() {}
        line (Point2D p, Point2D q) {
                a = p.y - q.y;
                b = q.x - p.x;
                c = - a * p.x - b * p.y;
                norm();
        }

        void norm() {
                double z = sqrt (a*a + b*b);
                if (fabs(z) > 0.000001)
                        a /= z,  b /= z,  c /= z;
        }

        double dist (Point2D p) const {
                return a * p.x + b * p.y + c;
        }
};

#define det(a,b,c,d)  (a*d-b*c)

double min(double a, double b);

double max(double a, double b);

bool betw (double l, double r, double x);

void weiler_cut(std::vector<Point2D>& cutter, std::vector<Point2D>& cutting,
                std::vector<std::vector<Point2D> >& inner,
                std::vector<std::vector<Point2D> >& outer);

bool aq(double a, double b);    //Почти равны ли?





#endif // MAINWINDOW_H
