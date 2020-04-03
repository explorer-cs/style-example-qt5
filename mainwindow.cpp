#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainterPath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    QMainWindow::resizeEvent(e);
    //调整边距
    auto rect = this->rect().adjusted(10, 10, -10, -10);
    QPainterPath blurPath;
    //增加圆角
    blurPath.addRoundedRect(rect, 10, 10);
    //使用QPainterPath的api生成多边形Region
    setProperty("blurRegion", QRegion(blurPath.toFillPolygon().toPolygon()));
    this->update();
}
