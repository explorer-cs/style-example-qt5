#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto model = new QFileSystemModel(this);
    model->setRootPath("/");

    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index("/"));
    ui->treeView->setMask(QRect(100, 100, 100, 100));
}

MainWindow::~MainWindow()
{
    delete ui;
}
