#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>

#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Cloud : public QGraphicsEllipseItem{
public:
    Cloud(int x_line, int y_line);
    virtual void advance(int phase);
private:
    int xspeed = 2;
    int x_cord;
    bool direction = false;
};

class Sky : public QGraphicsRectItem{
public:
    Sky(int xsize, int ysize, QColor color, int posX, int posY);
};

class Sun :  public QGraphicsEllipseItem{
public:
    Sun(int rad, int posx, int posy);
};

class Plancs : public QGraphicsRectItem{
public:
    Plancs(int x, int y, int x_size, int y_size);
    virtual void advance(int phase);
private:
    int xspeed = 1;
    int x_cord;
    bool direction = false;
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void generate();
private:
    Ui::Widget *ui;
    QGraphicsScene* scene;
    QTimer* animTimer;
    QTimer* animPtime;
};
#endif // WIDGET_H

