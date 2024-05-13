#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <cmath>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <climits>
#include <QVBoxLayout>

class TrochoidWidget : public QWidget {
public:
    int r, scale;
    double sinT, cosT, step, h;

    void drawTrochoid() {
        update();
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int prevX, prevY;
        bool firstPoint = true;

        painter.translate(width() / 2, height() / 2);

        painter.setPen(Qt::white);
        painter.drawLine(-width() / 2, 0, width() / 2, 0);

        painter.drawLine(0, -height() / 2, 0, height() / 2);

        painter.setPen(Qt::red);
        for (double t = -100; t < 100; t += step) {
            sinT = sin(t);
            cosT = cos(t);
            double x = r*t - h * sinT;
            double y = r - h * cosT;
            double scaledX = x * scale;
            double scaledY = -(y * scale);

            if (std::abs(x) >= 0.001) {
                if (!firstPoint) {
                    painter.drawLine(prevX, prevY, scaledX, scaledY);
                } else {
                    firstPoint = false;
                }
            }

            prevX = scaledX;
            prevY = scaledY;
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Lab 5");

    QLineEdit inpR;
    QLineEdit inpT;
    QLineEdit inpH;
    QLineEdit scaleInput;
    QLineEdit stepInput;
    QLineEdit xstartInput;
    QLineEdit xendInput;

    QLabel labelR("R");
    QLabel labelT("T");
    QLabel labelH("H");
    QLabel labelScale("Scale");
    QLabel labelStep("Step");
    QPushButton applyButton("Draw!");

    QWidget settings;
    QVBoxLayout layout(&settings);
    layout.addWidget(&labelR);
    layout.addWidget(&inpR);
    layout.addWidget(&labelH);
    layout.addWidget(&inpH);
    layout.addWidget(&labelScale);
    layout.addWidget(&scaleInput);
    layout.addWidget(&labelStep);
    layout.addWidget(&stepInput);
    layout.addWidget(&applyButton);
    settings.setLayout(&layout);

    TrochoidWidget widget;
    widget.resize(800, 600);

    QObject::connect(&applyButton, &QPushButton::clicked, [&]() {
        widget.r = inpR.text().toInt();
        widget.h = inpH.text().toDouble();
        widget.scale = scaleInput.text().toInt();
        widget.step = stepInput.text().toDouble();
        widget.show();
        widget.update();
    });

    settings.show();

    return app.exec();
}
