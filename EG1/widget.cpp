#include "widget.h"
#include "./ui_widget.h"
#include <QRandomGenerator>
#include <QRect>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,800,600,this);
    ui->graphicsView->setScene(scene);

    scene->addRect(scene->sceneRect());
    animTimer = new QTimer(this);
    connect(animTimer,SIGNAL(timeout()),scene,SLOT(advance()));
    animTimer->start(1000/60);

    animPtime = new QTimer(this);
    connect(animPtime,SIGNAL(timeout()),scene,SLOT(advance()));
    animPtime->start(1000/60);


    scene->addItem(new Sky(scene->sceneRect().width(), scene->sceneRect().height() / 2, QColor("BLUE"),0,0));
    scene->addItem(new Sky(scene->sceneRect().width(), scene->sceneRect().height() / 2,QColor("GREEN"),0,scene->sceneRect().height() / 2));
    scene->addItem(new Sun(100,scene->sceneRect().width()-100,0));

    generate();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::generate(){
    for (int i = 0; i < 100; i++)
        scene->addItem(new Cloud(scene->sceneRect().width() / QRandomGenerator::global()->bounded(4,5), scene->sceneRect().height() / QRandomGenerator::global()->bounded(1,5)));
    for (int i = 0; i < 100; i++)
        scene->addItem(new Plancs(i*10,130,30,100));
}


Plancs::Plancs(int x, int y, int x_size, int y_size) : QGraphicsRectItem(0){
    QColor color = QColor("BROWN");
    setBrush(color);
    setRect(x,y,x_size,y_size);
    setPos(x,y);
    x_cord = x;

}
void Plancs::advance(int phase){
    if(phase && x_cord < 600 && !direction){
        moveBy(xspeed,0);
        x_cord += xspeed;
    }else if(phase && x_cord >= 0){
        moveBy(-xspeed,0);
        x_cord -= xspeed;
        direction = true;
    }else if (phase){
        direction = false;
    }
}

Sun::Sun(int rad, int posx, int posy) : QGraphicsEllipseItem(0){
    QColor color = QColor("YELLOW");
    setBrush(color);
    setRect(0,0,rad,rad);
    setPos(posx,posy);
}

Sky::Sky(int xsize, int ysize, QColor color, int posX, int posY) : QGraphicsRectItem(0){
    setBrush(color);
    setRect(0,0,xsize,ysize);
    setPos(posX,posY);
}

Cloud::Cloud(int x_line, int y_line) : QGraphicsEllipseItem(0){
    QColor color = QColor(255,255,255);
    setBrush(color);
    setRect(0,0,100,50);
    x_cord = rand() % y_line;
    setPos(x_cord,rand() % (x_line - 50));
}
void Cloud::advance(int phase){
    if(phase && x_cord < 800 && !direction){
        moveBy(xspeed,0);
        x_cord += xspeed;
    }else if(phase && x_cord >= 0){
        moveBy(-xspeed,0);
        x_cord -= xspeed;
        direction = true;
    }else if (phase){
        direction = false;
    }
}
