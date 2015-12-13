#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImageReader>
#include <QImage>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    camera = new clsCamera;
    scene = new QGraphicsScene(0);
    ui->graphicsView->setScene(scene);

//    ui->graphicsView->scale(640/ui->graphicsView->width(),480/ui->graphicsView->height());
    connect(camera,SIGNAL(dataReady(const void*,int)),SLOT(readData(const void*,int)));
}

void MainWindow::readData(const void *p, int size)
{
    ui->graphicsView->scene()->clear();
    unsigned char yuyv_image[size];
    memcpy(yuyv_image,p,size);
    int width = 640,height = 480;
    unsigned char* rgb_image = new unsigned char[width * height * 3]; //width and height of the image to be converted

    int y;
    int cr;
    int cb;

    double r;
    double g;
    double b;

    for (int i = 0, j = 0; i < width * height * 3; i+=6 ,j+=4) {
        //first pixel
        y = yuyv_image[j];
        cb = yuyv_image[j+1];
        cr = yuyv_image[j+3];

        r = y + (1.4065 * (cr - 128));
        g = y - (0.3455 * (cb - 128)) - (0.7169 * (cr - 128));
        b = y + (1.7790 * (cb - 128));

        //This prevents colour distortions in your rgb image
        if (r < 0) r = 0;
        else if (r > 255) r = 255;
        if (g < 0) g = 0;
        else if (g > 255) g = 255;
        if (b < 0) b = 0;
        else if (b > 255) b = 255;

        rgb_image[i] = (unsigned char)r;
        rgb_image[i+1] = (unsigned char)g;
        rgb_image[i+2] = (unsigned char)b;

        //second pixel
        y = yuyv_image[j+2];
        cb = yuyv_image[j+1];
        cr = yuyv_image[j+3];

        r = y + (1.4065 * (cr - 128));
        g = y - (0.3455 * (cb - 128)) - (0.7169 * (cr - 128));
        b = y + (1.7790 * (cb - 128));

        if (r < 0) r = 0;
        else if (r > 255) r = 255;
        if (g < 0) g = 0;
        else if (g > 255) g = 255;
        if (b < 0) b = 0;
        else if (b > 255) b = 255;

        rgb_image[i+3] = (unsigned char)r;
        rgb_image[i+4] = (unsigned char)g;
        rgb_image[i+5] = (unsigned char)b;
    }
        QImage im(rgb_image,width,height,QImage::Format_RGB888);
        scene->addPixmap(QPixmap::fromImage(im));
        delete rgb_image;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    camera->mainCamera();
}
