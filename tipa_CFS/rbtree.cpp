#include "rbtree.h"
#include "string.h"
#include "mainwindow.h"

rbtree::rbtree()
{
    root = NULL;
    node_count = 0;
}

rbnode* rbtree::insert_node(int key, struct process* _content)
{
    node_count++;
    rbnode* new_node = new rbnode(key, _content, 1);
    if (root == NULL)
    {
        root = new_node;
        new_node->color = 0;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = NULL;
        qDebug() << "Created root";
        root->update_ideal_time(node_count, 6);
        return root;
    }
    else
    {
        //Вставка бинарным поиском
        rbnode* current = root;
        while (current != NULL)
        {
            if (key >= current->key)
            {
                if (current->right != NULL)
                    current = current->right;
                else
                {
                    current->right = new_node;
                    new_node->parent = current;
                    qDebug() << "Found right leaf";
                    break;
                }
            }
            else if (key < current->key)
            {
                if (current->left != NULL)
                    current = current->left;
                else
                {
                    current->left = new_node;
                    new_node->parent = current;
                    qDebug() << "Found left leaf";
                    break;
                }
            }
        }
        new_node->left = NULL;
        new_node->right = NULL;
        //Если предком является красный узел - исправляем
        while (1)
        {
            if (root == new_node)
            {
                new_node->color = 0;
                break;
            }
            if (new_node->parent->color != 1)
                break;
            qDebug() << "Red parent";
            rbnode* uncle;
            current = new_node->parent;
            if (current->parent->left == current)
                uncle = current->parent->right;
            else
                uncle = current->parent->left;
            if (uncle != NULL)
            {
                if (uncle->color == 1)
                {
                    //Если дядя красный
                    current->color = 0;
                    uncle->color = 0;
                    new_node->parent->parent->color = 1;
                    new_node = new_node->parent->parent;
                    continue;
                }
                else
                    uncle = NULL;   //Сводим случай с черным дядей к фиктивному
            }
            if (uncle == NULL)
            {
                //Если дядя черный/фиктивный
                qDebug()<<"Black uncle";
                if (current->parent->left == current)
                {
                    if (new_node == current->right)
                    {
                        qDebug()<<"Left diagonal";
                        rotate_left(current);
                        new_node->color = 0;
                        new_node->parent->color = 1;
                        rotate_right(new_node->parent);
                    }
                    else
                    {
                        qDebug()<<"Left straight";
                        current->color = 0;
                        current->parent->color = 1;
                        rotate_right(current->parent);
                    }
                }
                else
                {
                    if (new_node == current->left)
                    {
                        qDebug()<<"Right diagonal";
                        rotate_right(current);

                        new_node->color = 0;
                        new_node->parent->color = 1;
                        rotate_left(new_node->parent);           
                    }
                    else
                    {
                        qDebug()<<"Right straight";
                        current->color = 0;
                        current->parent->color = 1;
                        rotate_left(current->parent);
                    }
                }
                if (new_node->parent != NULL)
                    new_node = new_node->parent;
                qDebug()<<"ende";
            }
        }
        if (root != NULL)
            root->update_ideal_time(node_count, 6);
        return new_node;
    }
}

rbnode* rbtree::find_node(int key)
{
    if (root == NULL)
        return NULL;
    rbnode* current = root;
    while (current != NULL)
    {
        if (key > current->key)
            current = current->right;
        else if (key < current->key)
            current = current->left;
        else
            break;
    }
    return current;
}

void rbtree::delete_node(rbnode* deleted)
{
    if (deleted->left != NULL && deleted->right != NULL)
    {
        //Ищем макс элемент в левом поддереве, и сводим к случаю с 0/1 потомками
        rbnode* swap = deleted->left;
        while (swap->right != NULL)
            swap = swap->right;
        deleted->key = swap->key;
        deleted->content = swap->content;
        deleted = swap;
    }

    if (deleted->color == 1)
    {
        if (deleted->parent->left == deleted)
            deleted->parent->left = NULL;
        else
            deleted->parent->right = NULL;
        qDebug()<<"Deleting red node.";
    }
    else if (get_color(deleted->right) == 1)
    {
        if (deleted->parent == NULL)
            root = deleted->right;
        else if (deleted->parent->left == deleted)
            deleted->parent->left = deleted->right;
        else
            deleted->parent->right = deleted->right;
        deleted->right->color = 0;
        deleted->right->parent = deleted->parent;
    }
    else if (get_color(deleted->left) == 1)
    {
        if (deleted->parent == NULL)
            root = deleted->left;
        else if (deleted->parent->left == deleted)
            deleted->parent->left = deleted->left;
        else
            deleted->parent->right = deleted->left;
        deleted->left->color = 0;
        deleted->left->parent = deleted->parent;
    }
    else    //Черный узел без потомков
    {
        if (deleted->parent == NULL)
            root = NULL;
        else
        {
            if (deleted->parent->left == deleted)
            {
                deleted->parent->left = NULL;
                qDebug()<<"Deleted left connection";
            }
            else
            {
                deleted->parent->right = NULL;
                qDebug()<<"Deleted right connection";
            }
            qDebug()<<"===Fixing tree===";
            fix(deleted);   //Правка дерева
            qDebug()<<"===End of fixing===";
        }
    }

    delete deleted;
    node_count--;
    if (root != NULL && node_count > 0)
        root->update_ideal_time(node_count, 6);
}

int rbtree::get_color(rbnode* node)
{
    if (node == NULL)   //Все фиктивные листья - черные
        return 0;
    else
        return node->color;
}

void rbtree::fix(rbnode* deleted)
{
    if (deleted == root)
    {
        qDebug()<<"1. Making root black.";
        root->color = 0;
    }
    else
    {
        rbnode* parent = deleted->parent;
        rbnode* brother;
        if (parent->left == NULL || parent->left == deleted)
        {
            qDebug()<<"Left child deleted";
            brother = parent->right;
            qDebug()<<"A";
            if (brother->color == 1)
            {
                qDebug()<<"2. Black parent, red brother";
                rotate_left(parent);
                parent->color = 1;
                brother->color = 0;
                brother = parent->right;
            }
            if (parent->color == 0 && get_color(brother->right) == 0 && get_color(brother->left) == 0)
            {
                qDebug()<<"3. Black parent, black brother, black nephews";
                brother->color = 1;
                fix(parent);
            }
            else if (parent->color == 1 && get_color(brother->right) == 0 && get_color(brother->left) == 0)
            {
                qDebug()<<"4. Red parent, black brother, black nephews";
                brother->color = 1;
                parent->color = 0;
            }
            else if (get_color(brother->left) == 1)
            {
                qDebug()<<"5. Black brother, red left nephew";
                rotate_right(brother);
                brother->color = 1;
                brother->parent->color = 0;
                brother = brother->parent;
            }
            if (brother->color == 0 && get_color(brother->right) == 1)
            {
                qDebug()<<"6. Black brother, red right nephew";
                rotate_left(parent);
                brother->color = parent->color;
                parent->color = 0;
                if (brother->right != NULL)
                    brother->right->color = 0;
            }
        }
        else
        {
            qDebug()<<"Right child deleted";
            brother = parent->left;
            if (brother->color == 1)
            {
                qDebug()<<"2. Black parent, red brother";
                rotate_right(parent);
                parent->color = 1;
                brother->color = 0;
                brother = parent->left;
            }
            if (parent->color == 0 && get_color(brother->right) == 0 && get_color(brother->left) == 0)
            {
                qDebug()<<"3. Black parent, black brother, black nephews";
                brother->color = 1;
                fix(parent);
            }
            else if (parent->color == 1 && get_color(brother->right) == 0 && get_color(brother->left) == 0)
            {
                qDebug()<<"4. Red parent, black brother, black nephews";
                brother->color = 1;
                parent->color = 0;
            }
            else if (get_color(brother->right) == 1)
            {
                qDebug()<<"5. Black brother, red right nephew";
                rotate_left(brother);
                brother->color = 1;
                brother->parent->color = 0;
                brother = brother->parent;
            }
            if (brother->color == 0 && get_color(brother->left) == 1)
            {
                qDebug()<<"6. Black brother, red left nephew";
                rotate_right(parent);
                brother->color = parent->color;
                parent->color = 0;
            }
        }
    }
}


void rbtree::rotate_left(rbnode* pivot)
{
    rbnode* N = pivot->right;
    rbnode* G = pivot->parent;
    rbnode* n2 = N->left;
    if (G == NULL)
        root = N;
    else if (G->left == pivot)
        G->left = N;
    else
        G->right = N;
    N->parent = G;
    N->left = pivot;
    pivot->parent = N;
    pivot->right = n2;
    if (n2 != NULL)
        n2->parent = pivot;
}

void rbtree::rotate_right(rbnode* pivot)
{
    rbnode* N = pivot->left;
    rbnode* G = pivot->parent;
    rbnode* n2 = N->right;
    if (G == NULL)
        root = N;
    else if (G->left == pivot)
        G->left = N;
    else
        G->right = N;
    N->parent = G;
    N->right = pivot;
    pivot->parent = N;
    pivot->left = n2;
    if (n2 != NULL)
        n2->parent = pivot;
}

void rbtree::big_rotate_left(rbnode* pivot)
{
    rbnode* B = pivot->right;
    rbnode* G = pivot->parent;
    rbnode* C = B->left;
    rbnode* Q = C->left;
    rbnode* R = C->right;
    if (G == NULL)
    {
        root = C;
        C->color = 0;
    }
    else if (G->left == pivot)
        G->left = C;
    else
        G->right = C;
    pivot->parent = C;
    B->parent = C;
    C->left = pivot;
    C->right = B;
    pivot->right = Q;
    B->left = R;
    if (Q != NULL)
        Q->parent = pivot;
    if (R != NULL)
        R->parent = B;
}

void rbtree::big_rotate_right(rbnode* pivot)
{
    rbnode* B = pivot->left;
    rbnode* G = pivot->parent;
    rbnode* C = B->right;
    rbnode* Q = C->right;
    rbnode* R = C->left;
    if (G == NULL)
    {
        root = C;
        C->color = 0;
    }
    else if (G->left == pivot)
        G->left = C;
    else
        G->right = C;
    pivot->parent = C;
    B->parent = C;
    C->right = pivot;
    C->left = B;
    pivot->left = Q;
    B->right = R;
    if (Q != NULL)
        Q->parent = pivot;
    if (R != NULL)
        R->parent = B;
}

rbtree::~rbtree()
{

}

rbnode::rbnode(int _key, struct process* _content, int _color)
{
    selected = false;
    key = _key;
    content = _content;
    color = _color;
}

void rbnode::draw_node(QPainter* painter, int x, int y, int r, int depth)
{
    qDebug()<<content->name<<"This: "<< this <<" Color: "<< color<<" Parent: "<<parent<<", LEFT: "<<left<<", RIGHT: "<<right;
    int delta = 1;
    for (int i = 0; i < depth; i++)
        delta*=2;
    delta*=r*0.4;
    if (left != NULL)   //Connection to the left child
    {
        painter->setPen(QColor(0,0,0));
        painter->drawLine(x, y, x - delta, y + 2*r);
        left->draw_node(painter, x - delta, y + 2*r, r, depth-1);
    }
    if (right != NULL)  //Connection to the right child
    {
        painter->setPen(QColor(0,0,0));
        painter->drawLine(x, y, x + delta, y + 2*r);
        right->draw_node(painter, x + delta, y + 2*r, r, depth-1);
    }
    if (selected)
    {
        QBrush transp_brush(QColor(255,255,255,0));
        painter->setBrush(transp_brush);
        painter->setPen(QColor(0,0,255));
        painter->drawEllipse(x-1.5*r, y-1.5*r, 3*r, 3*r);
    }

    QBrush brush(QColor(255,255,255));
    painter->setBrush(brush);
    if (color == 1)
        painter->setPen(QColor(255,0,0));
    else
        painter->setPen(QColor(0,0,0));
    painter->drawEllipse(x-r, y-r, 2*r, 2*r);
    QPen penn(QColor(180, 180, 180));
    penn.setWidthF(1 + r * 0.2);
    painter->setPen(penn);

    painter->drawArc(x-r, y-r, 2*r, 2*r, 0, -floor(360 * 16 * (double)content->vruntime/content->maxtime ));

    if (color == 1)
        painter->setPen(QColor(255,0,0));
    else
        painter->setPen(QColor(0,0,0));
    painter->drawEllipse(x-r, y-r, 2*r, 2*r);
    painter->drawText(x-r, y-r, 2*r, 2*r, Qt::AlignCenter, QString::number(key));
}

rbnode::~rbnode()
{

}

int rbnode::depth(int a)
{
    int l=0, r=0;
    if (left != NULL)
        l = left->depth(a+1);
    if (right != NULL)
        r = right->depth(a+1);
    if (l>r)
        return l + 1;
    else
        return r + 1;
}


canvas::canvas(QWidget* parent):QWidget(parent)    //Конструктор окна
{
    //QTextCodec::setCodecForTr(QTextCodec::codecForName ("Windows-1251"));   //Для отображения кириллицы
    tree = NULL;
}

void canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(0,0,width(),height(),QColor(255,255,255));
    if (tree != NULL)
    {
        if (tree->root == NULL)
            return;
        int startx = width()/2;
        int starty;
        int depth = tree->root->depth(1);
        int maxhor = 1;
        for (int i = 0; i < depth; i++)
            maxhor *= 2;
        int radius = (width() / maxhor) * 0.6;
        if (radius > 20)
            radius = 20;
        starty = (height() - (depth - 1) * 2*radius) / 2;
        //painter.drawText(10, 10, 100, 20, Qt::AlignCenter, "Tree depth: "+QString::number(depth));
        tree->root->draw_node(&painter, startx, starty, radius, depth);
    }
}

canvas::~canvas()
{

}

rbnode* rbtree::SelectNode(QPoint pos, int w, int h)
{
    int mx = pos.x();
    int my = pos.y();
    if (root == NULL)
        return NULL;
    int startx = w/2;
    int starty;
    int depth = root->depth(1);
    int maxhor = 1;
    for (int i = 0; i < depth; i++)
        maxhor *= 2;
    int radius = (w / maxhor) * 0.6;
    if (radius > 20)
        radius = 20;
    starty = (h - (depth - 1) * 2*radius) / 2;
    return root->traverse_node(startx, starty, radius, depth, mx, my);
}

rbnode* rbnode::traverse_node(int x, int y, int r, int depth, int mouse_x, int mouse_y)
{
    int delta = 1;
    for (int i = 0; i < depth; i++)
        delta*=2;
    delta*=r*0.4;
    rbnode* l_node = NULL;
    rbnode* r_node = NULL;
    if (left != NULL)
        l_node = left->traverse_node(x - delta, y + 2*r, r, depth-1, mouse_x, mouse_y);
    if (right != NULL)
        r_node = right->traverse_node(x + delta, y + 2*r, r, depth-1, mouse_x, mouse_y);
    if (mouse_x > x-r && mouse_x < x+r && mouse_y > y-r && mouse_y < y + r)
    {
        selected = true;
        return this;
    }
    else
    {
        selected = false;
        if (l_node != NULL)
            return l_node;
        if (r_node != NULL)
            return r_node;
        return NULL;
    }
}

void canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        selected = tree->SelectNode(event->pos(), width(), height());
        mainW->UpdateSelected(selected);
        update();
    }
}

void rbnode::update_ideal_time(int node_count, int timeslice)
{
    qDebug()<<"NodeCount = "<<node_count;
    content->maxexectime = timeslice / node_count;
    if (content->maxexectime == 0)
        content->maxexectime = 1;
    if (content->maxexectime > (content->maxtime - content->vruntime))
        content->maxexectime = content->maxtime - content->vruntime;
    if (left != NULL)
        left->update_ideal_time(node_count, timeslice);
    if (right != NULL)
        right->update_ideal_time(node_count, timeslice);
}
