#ifndef RBTREE_H
#define RBTREE_H
#include <Qt>
#include <QColor>
#include <QPainter>
#include <QDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QPoint>
#include <QTime>


struct process
{
    int vruntime;   //����� ����������
    int maxtime;    //����������� ����� ����������
    QString name;   //�������� ��������
    int starttime;  //����� ������� ��������
    int endtime;    //����� ��������� ���������� ��������
    int exectime;   //�����, ������� ��� ��������� �� ���������� �������
    int maxexectime;    //����� ���������� �� ��������� ����������
};

class rbnode
{
public:
    rbnode(int _key, struct process* _content, int _color);
    bool selected;
    struct process* content;
    int key;
    rbnode* left;
    rbnode* right;
    rbnode* parent;
    int color;  //0 - black, 1 - red
    void draw_node(QPainter* painter, int x, int y, int r, int depth);
    rbnode* traverse_node(int x, int y, int r, int depth, int mouse_x, int mouse_y);
    int depth(int a);
    void update_ideal_time(int node_count, int timeslice);
    ~rbnode();
};

class rbtree
{
public:
    rbnode* root;
    rbtree();
    int node_count;
    rbnode* insert_node(int key, struct process* _content);
    rbnode* find_node(int key);
    void fix(rbnode* deleted);
    void delete_node(rbnode* deleted);
    void rotate_left(rbnode* pivot);
    void rotate_right(rbnode* pivot);
    void big_rotate_left(rbnode* pivot);
    void big_rotate_right(rbnode* pivot);
    int get_color(rbnode* node);
    void update_ideal_time();
    ~rbtree();
    rbnode* SelectNode(QPoint pos, int w, int h);
};

class canvas : public QWidget    //����� "������", �� ������� ����� �������������� �����������
{
    Q_OBJECT 
public:
    rbtree* tree;
    //����������� � ����������
    canvas(QWidget* parent);
    rbnode* selected;
    ~canvas();
    //������ ������
    void paintEvent(QPaintEvent *); //��������� ������ � ����
protected:
    void mousePressEvent(QMouseEvent *event);
};


#endif // RBTREE_H
