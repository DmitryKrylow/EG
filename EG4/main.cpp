#include "mainwindow.h"
#include <QApplication>
#include <QImage>
#include <QLabel>
#include <QFileDialog>
#include <string>
#include <QPushButton>

QImage readFile(){

    QString str = QFileDialog::getOpenFileName(0, "Открыть", "", "*.bmp");

    std::string path = str.toStdString();

    FILE *streamIn = fopen(path.c_str(), "rb");

    unsigned char bmpHeader[54];

    for (int i = 0; i < 54; i++)
    {
        bmpHeader[i] = getc(streamIn);
    }

    int width = *(int*)&bmpHeader[18];
    int height = *(int*)&bmpHeader[22];
    int bitDepth = *(int*)&bmpHeader[28];

    unsigned char buf[height * width * 3];
    fread(buf, sizeof(unsigned char), (height * width * 3), streamIn);
    fclose(streamIn);

    QImage img(width, height, QImage::Format_RGB888);
    for (int row = 0; row < img.height(); row++) {
        for(int col = 0; col < img.width(); col++) {
            int offset = 3 * (row * img.width() + col);
            int blue = buf[offset];
            int green = buf[offset + 1];
            int red = buf[offset + 2];
            img.setPixel(col, img.height() - row - 1, qRgb(red, green, blue));
        }
    }
    return img;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel *myLabel = new QLabel();
    QImage img = readFile();
    myLabel->setPixmap(QPixmap::fromImage(img));
    myLabel->show();
    return a.exec();
}
