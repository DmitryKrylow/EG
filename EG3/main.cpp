#include <QApplication>
#include <QGraphicsView>
#include <QRectF>
#include <QGraphicsPixmapItem>
#include <QInputDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QPainter>


QGraphicsPolygonItem *square = nullptr;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QGraphicsScene scene;
    scene.setBackgroundBrush(Qt::white);
    QGraphicsView view(&scene);
    a.setApplicationName("Lab3");

    view.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view.setFixedSize(800, 600);
    view.show();

    scene.addLine(-400, 0, 400, 0, QPen(Qt::black));
    scene.addLine(0, -300, 0, 300, QPen(Qt::black));

    QLineEdit sideSize;
    sideSize.setPlaceholderText("Размер стороны");

    QLineEdit xInput;
    xInput.setPlaceholderText("X");

    QLineEdit yInput;
    yInput.setPlaceholderText("Y");

    QLineEdit scaleInput;
    scaleInput.setPlaceholderText("Масштаб");

    QLineEdit angleInput;
    angleInput.setPlaceholderText("Угол поворота");

    QPushButton applyButton("Нарисовать");

    QWidget menu;

    QVBoxLayout layout(&menu);
    layout.addWidget(&sideSize);
    layout.addWidget(&xInput);
    layout.addWidget(&yInput);
    layout.addWidget(&scaleInput);
    layout.addWidget(&angleInput);
    layout.addWidget(&applyButton);
    menu.setLayout(&layout);
    menu.show();

    QGraphicsPolygonItem *square = new QGraphicsPolygonItem();

    QObject::connect(&applyButton, &QPushButton::clicked, [&]() {
        if(square){
            scene.removeItem(square);
            delete square;
        }
        int sideLength = sideSize.text().toDouble();
        int centerX = xInput.text().toDouble() / 2;
        int centerY = yInput.text().toDouble() / 2;
        int rotationAngle = angleInput.text().toDouble();
        double scale = scaleInput.text().toDouble();

        QPolygonF polygon;
        QPointF p1((centerX - sideLength / 2) * scale, (centerY - sideLength / 2) * scale);
        QPointF p2((centerX + sideLength / 2) * scale, (centerY - sideLength / 2) * scale);
        QPointF p3((centerX + sideLength / 2) * scale, (centerY + sideLength / 2) * scale);
        QPointF p4((centerX - sideLength / 2) * scale, (centerY + sideLength / 2) * scale);

        double rad = rotationAngle * M_PI / 180.0;

        //x' = x cos(angle) +- ysin(angle)
        //y' = +-xcos(angle) + ysin(angle)

        //x' = centerX + (x - centerX) * cos(angle) - (y - centerY) * sin(angle)
        //y' = centerY + (x - centerX) * sin(angle) + (y - centerY) * cos(angle)

        QPointF p1_scaled(centerX + (p1.x() - centerX) * cos(rad) - (p1.y() - centerY) * sin(rad),
                          centerY + (p1.x() - centerX) * sin(rad) + (p1.y() - centerY) * cos(rad));
        QPointF p2_scaled(centerX + (p2.x() - centerX) * cos(rad) - (p2.y() - centerY) * sin(rad),
                          centerY + (p2.x() - centerX) * sin(rad) + (p2.y() - centerY) * cos(rad));
        QPointF p3_scaled(centerX + (p3.x() - centerX) * cos(rad) - (p3.y() - centerY) * sin(rad),
                          centerY + (p3.x() - centerX) * sin(rad) + (p3.y() - centerY) * cos(rad));
        QPointF p4_scaled(centerX + (p4.x() - centerX) * cos(rad) - (p4.y() - centerY) * sin(rad),
                          centerY + (p4.x() - centerX) * sin(rad) + (p4.y() - centerY) * cos(rad));

        polygon << p1_scaled << p2_scaled << p3_scaled << p4_scaled;
        square = new QGraphicsPolygonItem(polygon);
        scene.addItem(square);

    });

    return a.exec();
}
