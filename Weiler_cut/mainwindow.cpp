#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

}

MainWindow::~MainWindow()
{

}


void DrawVeyler(QPainter* painter, double dx, double dy)
{
    //painter->fillRect(0,0,100,10, QBrush(QColor(100,0,0)));
    std::vector<Point2D> cutter;
    cutter.push_back(Point2D(10 + dx, 10 + dy));
    cutter.push_back(Point2D(10 + dx, 50 + dy));
    cutter.push_back(Point2D(50 + dx, 50 + dy));
    cutter.push_back(Point2D(50 + dx, 10 + dy));

    std::vector<Point2D> cutting;
    cutting.push_back(Point2D(10, 10));
    cutting.push_back(Point2D(10, 50));
    cutting.push_back(Point2D(50, 50));
    cutting.push_back(Point2D(50, 10));

    std::vector<std::vector<Point2D> > inner;
    std::vector<std::vector<Point2D> > outer;
    weiler_cut(cutter, cutting, inner, outer);

    painter->setPen(QColor(0, 0, 0));
    for (int j = 0; j < cutting.size(); j++)
    {
        if (j == cutting.size() - 1)
            painter->drawLine(cutting[j].x, cutting[j].y, cutting[0].x, cutting[0].y);
        else
            painter->drawLine(cutting[j].x, cutting[j].y, cutting[j+1].x, cutting[j+1].y);
    }

    painter->setPen(QColor(255, 0, 0));
    for (int j = 0; j < cutter.size(); j++)
    {
        if (j == cutter.size() - 1)
            painter->drawLine(cutter[j].x, cutter[j].y, cutter[0].x, cutter[0].y);
        else
            painter->drawLine(cutter[j].x, cutter[j].y, cutter[j+1].x, cutter[j+1].y);
    }

    painter->setPen(QColor(0,255,0));   //Внутреннее
    for (int i = 0; i < inner.size(); i++)
    {
        for (int j = 0; j < inner[i].size(); j++)
        {
            if (j == inner[i].size() - 1)
                painter->drawLine(inner[i][j].x + 200, inner[i][j].y + 200 * i, inner[i][0].x + 200, inner[i][0].y + 200 * i);
            else
                painter->drawLine(inner[i][j].x + 200, inner[i][j].y + 200 * i, inner[i][j+1].x + 200, inner[i][j+1].y + 200 * i);
        }
    }

    painter->setPen(QColor(0,0,255));   //Внешнее
    for (int i = 0; i < outer.size(); i++)
    {
        for (int j = 0; j < outer[i].size(); j++)
        {
            if (j == outer[i].size() - 1)
                painter->drawLine(outer[i][j].x + 400, outer[i][j].y + 200 * i, outer[i][0].x + 400, outer[i][0].y + 200 * i);
            else
                painter->drawLine(outer[i][j].x + 400, outer[i][j].y + 200 * i, outer[i][j+1].x + 400, outer[i][j+1].y + 200 * i);
        }

    }
}



bool intersect(Point2D A1, Point2D B1, Point2D A2, Point2D B2, Point2D& result)
{
    //РџРµСЂРІРёС‡РЅР°СЏ РїСЂРѕРІРµСЂРєР°
    if (!proj_intersec(A1.x, B1.x, A2.x, B2.x) || !proj_intersec(A1.y, B1.y, A2.y, B2.y))
        return false;
    line l1(A1, B1);
    line l2(A2, B2);
    double zn = det (l1.a, l1.b, l2.a, l2.b);
    if (fabs (zn) < 0.00001) {
        return false;
    }
    else {
    result.x = - det (l1.c, l1.b, l2.c, l2.b) / zn;
    result.y = - det (l1.a, l1.c, l2.a, l2.c) / zn;
    return betw (A1.x, B1.x, result.x)
            && betw (A1.y, B1.y, result.y)
            && betw (A2.x, B2.x, result.x)
            && betw (A2.y, B2.y, result.y);
    }
}



void weiler_cut(std::vector<Point2D>& cutter, std::vector<Point2D>& cutting,
                std::vector<std::vector<Point2D> >& inner,
                std::vector<std::vector<Point2D> >& outer)
{
    //0. Р СџРЎР‚Р ВµР С•Р В±РЎР‚Р В°Р В·Р С•Р Р†Р В°Р Р…Р С‘Р Вµ Р С‘Р В· Polygon3D Р Р† Р Р†Р ВµР С”РЎвЂљР С•РЎР‚Р В° РЎвЂљР С•РЎвЂЎР ВµР С”, Р С•РЎР‚Р С–Р В°Р Р…Р С‘Р В·Р С•Р Р†Р В°Р Р…Р Р…РЎвЂ№Р Вµ Р С—Р С• РЎвЂЎР В°РЎРѓР С•Р Р†Р С•Р в„– РЎРѓРЎвЂљРЎР‚Р ВµР В»Р С”Р Вµ
    //std::vector<Point2D> cutter = Polygon3Dto2D(_cutter);   //Р С›Р В±РЎР‚Р ВµР В·Р В°РЎР‹РЎвЂ°Р С‘Р в„– Р СР Р…Р С•Р С–Р С•РЎС“Р С–Р С•Р В»РЎРЉР Р…Р С‘Р С”
    //std::vector<Point2D> cutting = Polygon3Dto2D(_cutting); //Р С›Р В±РЎР‚Р ВµР В·Р В°Р ВµР СРЎвЂ№Р в„– Р СР Р…Р С•Р С–Р С•РЎС“Р С–Р С•Р В»РЎРЉР Р…Р С‘Р С”
    std::vector<int> entering;
    std::vector<int> exiting;
    //1. РўРѕС‡РєРё РїРµСЂРµСЃРµС‡РµРЅРёСЏ Рё РёС… РєР»Р°СЃСЃРёС„РёРєР°С†РёСЏ
    for (int i = 0; i < cutting.size(); i++) //РћР±СЂРµР·Р°РµРјС‹Р№
    {
        //РќР°С‡Р°Р»СЊРЅР°СЏ Рё РєРѕРЅРµС‡РЅР°СЏ РІРµСЂС€РёРЅС‹
        Point2D A = cutting[i];
        Point2D B = (i < cutting.size()-1)?cutting[i+1]:cutting[0];
        //qDebug()<<"Cutting " << A.x << "," << A.y << " <>"<<B.x << "," << B.y;
        for (int j = 0; j < cutter.size(); j++)    //РћР±СЂРµР·Р°С‚РµР»СЊ
        {
            //РќР°С‡Р°Р»СЊРЅР°СЏ Рё РєРѕРЅРµС‡РЅР°СЏ РІРµСЂС€РёРЅС‹
            Point2D Start = cutter[j];
            Point2D Finish = (j < cutter.size()-1)?cutter[j+1]:cutter[0];
            //qDebug()<<"Cutter " << Start.x << "," << Start.y << " <>"<<Finish.x << "," << Finish.y;
            Point2D intersection;
            if (intersect(A, B, Start, Finish, intersection))
            {
                Point2D AB(B.x - A.x, B.y - A.y, 0);
                Point2D CD(Finish.x - Start.x, Finish.y - Start.y, 0);
                Point2D Normal(-AB.y, AB.x);
                //Check for repeating vertices
                if (aq(A.x, intersection.x) && aq(A.y, intersection.y))
                {
                    intersection.x+=1;
                }
                else if (aq(B.x, intersection.x) && aq(B.y, intersection.y))
                {
                    intersection.x+=1;
                }

                if (scalar(CD, Normal) < 0) //Р’С…РѕРґСЏС‰Р°СЏ РІРµСЂС€РёРЅР°
                {

                    cutting.insert(cutting.begin()+i+1, Point2D(intersection.x, intersection.y, -1));
                    entering.push_back(i+1);
                    cutter.insert(cutter.begin()+j+1, Point2D(intersection.x, intersection.y, -1));
                    i++;
                    j++;
                }
                else    //Р’С‹С…РѕРґСЏС‰Р°СЏ РІРµСЂС€РёРЅР°
                {
                    cutting.insert(cutting.begin()+i+1, Point2D(intersection.x, intersection.y, 1));
                    exiting.push_back(i+1);
                    cutter.insert(cutter.begin()+j+1, Point2D(intersection.x, intersection.y, 1));
                    i++;
                    j++;
                }
            }
        }
    }
    //qDebug() << "<end>";
    //2. РџРѕР»СѓС‡РµРЅРёРµ РІРЅСѓС‚СЂРµРЅРЅРµРіРѕ СЃРїРёСЃРѕРє
    for (int i = 0; i < entering.size(); i++)
    {
        if (!cutting[entering[i]].entered)    //Р•СЃР»Рё РІРµСЂС€РёРЅР° РµС‰Рµ РЅРµ РїРѕСЃРµС‰РµРЅР°
        {
            std::vector<Point2D> inside;
            int start = entering[i];
            cutting[entering[i]].entered = true; //РџРћРњР•Р§РђР•Рњ РљРђРљ РџР РћР™Р”Р•РќРќРЈР®
            inside.push_back(cutting[start]);

            bool finished = false;
            for (int enter = start; !finished ;)
            {
                int exit;
                std::vector<Point2D> outside;   //Р’РќР•РЁРќРР™ РџРћР›РР“РћРќ
                outside.push_back(cutting[enter]);

                int enter_cutter = 0;   //Р’РµСЂС€РёРЅР° enter РІ РѕР±СЂРµР·Р°С‚РµР»Рµ
                for (int j = 0; j < cutter.size(); j++) //РџРѕРёСЃРє Р°РЅР°Р»РѕРіР° РІРµСЂС€РёРЅС‹ ENTER РІ РѕР±СЂРµР·Р°С‚РµР»Рµ
                {
                    if (cutter[j].x == cutting[enter].x && cutter[j].y == cutting[enter].y)
                    {
                        enter_cutter = j;   //Searching for cutter start
                        break;
                    }
                }
                for (int j = enter_cutter; ; (j==cutter.size()-1)?j=0:j++)  //Р”РѕР±Р°РІР»РµРЅРёРµ РІРЅСѓС‚СЂРµРЅРЅРёС… РІРµСЂС€РёРЅ
                {
                    if (j == enter_cutter)  //Looking for next exit
                        continue;
                    inside.push_back(cutter[j]);
                    outside.push_back(cutter[j]);
                    if (cutter[j].intersec == 1)
                    {
                        exit = j;
                        break;
                    }
                }
                int exit_cutting = 0;   //Р’С‹С…РѕРґРЅР°СЏ РІРµСЂС€РёРЅР° РІ РѕР±СЂРµР·Р°РµРјРѕРј
                for (int j = 0; j < exiting.size(); j++)    //РџРѕРёСЃРє С‚РѕС‡РєРё РІС‹С…РѕРґР° РІ РѕР±СЂРµР·Р°РµРјРѕРј
                {
                    if (cutting[exiting[j]].x == cutter[exit].x && cutting[exiting[j]].y == cutter[exit].y)
                        exit_cutting = exiting[j];
                }
                for (int j = exit_cutting; ;(j==0)?j=cutting.size()-1:j--)  //Р—РђРљР Р«РўРР• Р’РќР•РЁРќР•Р“Рћ РџРћР›РР“РћРќРђ
                {
                    if (j != enter)
                        outside.push_back(cutting[j]);
                    else
                        break;
                }
                outer.push_back(outside);
                for(int j = exit_cutting; ; (j==cutting.size()-1)?j=0:j++)  //Р”РѕР±Р°РІР»РµРЅРёРµ РІРЅРµС€РЅРёС… РІРµСЂС€РёРЅ
                {
                    //Looking for next enter
                    if (j == exit_cutting)
                        continue;
                    if (cutting[j].intersec == -1)  //Р•СЃР»Рё РЅР°Р№РґРµРЅР° РІС…РѕРґРЅР°СЏ РІРµСЂС€РёРЅР°
                    {
                        if (j == enter ) //If found start - end clipping
                        {
                            finished = true;    //"Р—РђРљР Р«РўРР•" РїРѕР»РёРіРѕРЅР°
                            inner.push_back(inside);
                            break;
                        }
                        else if (!cutting[j].entered) //If found new start - new clipping
                        {
                            enter = j;  //РџР•Р Р•РҐРћР” Рљ РЎР›Р•Р”РЈР®Р©Р•Р™ Р’РҐРћР”РќРћР™ Р’Р•Р РЁРРќР•
                            inside.push_back(cutting[j]);
                            for (int i = 0; i < entering.size(); i++)
                            {
                                if (entering[i] == enter)
                                    cutting[entering[i]].entered = true;   //РџРћРњР•РўРљРђ Р’Р•Р РЁРРќР« РљРђРљ РџР РћР™Р”Р•РќРќРћР™
                            }
                            break;
                        }
                        else    //if found old start
                        {
                            finished = true;
                            inside.push_back(cutting[j]);
                            break;
                        }
                    }
                    else
                        inside.push_back(cutting[j]);   //Р”РћР‘РђР’Р›Р•РќРР• Р’РќР•РЁРќР•Р™ Р’Р•Р РЁРРќР«
                }
            }
            //inner.push_back(inside); (?)
        }
    }
}

double min(double a, double b)
{
    return (a<b)?a:b;
}

double max(double a, double b)
{
    return (a>b)?a:b;
}

bool betw (double l, double r, double x) {
    return min(l,r) <= x + 0.00001 && x <= max(l,r) + 0.00001;
}

double scalar(Point2D a, Point2D b)
{
    return a.x * b.x + a.y * b.y;
}

bool proj_intersec(double a, double b, double c, double d)  //РџРµСЂРµСЃРµРєР°СЋС‚СЃСЏ Р»Рё РѕС‚СЂРµР·РєРё ab Рё cd РЅР° РѕРґРЅРѕР№ РїСЂСЏРјРѕР№
{
    if (a>b)
    {
        double t = a;
        a = b;
        b = t;
    }
    if (c>d)
    {
        double t = c;
        c = d;
        d = t;
    }
    double _min = (a > c)?a:c;
    double _max = (b < d)?b:d;
    return _min <= _max + 0.00001;
}

bool aq(double a, double b)
{
    return (min(a, b) + 0.00001 > max(a, b) - 0.00001);
}

