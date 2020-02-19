#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPalette>
#include <QPainter>
#include <QColorDialog>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_palette = QApplication::palette();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QApplication::palette().color(QPalette::Active, QPalette::Window));
    p.drawRect(this->rect());

    QMainWindow::paintEvent(e);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    auto windowBgActive = QApplication::palette().color(QPalette::Active, QPalette::Window);
    windowBgActive.setAlphaF(value/100.0);
    m_palette.setColor(QPalette::Active, QPalette::Window, windowBgActive);

    auto buttonBgActive = QApplication::palette().color(QPalette::Active, QPalette::Button);
    buttonBgActive.setAlphaF(value/100.0);
    m_palette.setColor(QPalette::Active, QPalette::Button, buttonBgActive);

    QApplication::setPalette(m_palette);
    setPalette(m_palette);
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"clicked";
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug()<<"clicked";
}

void MainWindow::on_pushButton_2_released()
{
    qDebug()<<"released";
    QColorDialog d;
    if (d.exec()) {
        qDebug()<<"ok";
        auto windowBgActive = d.selectedColor();
        windowBgActive.setAlphaF(this->ui->horizontalSlider->value()/100.0);
        m_palette.setColor(QPalette::Active, QPalette::Window, windowBgActive);

        QApplication::setPalette(m_palette);
        setPalette(m_palette);
        this->ui->label_4->setBackgroundRole(QPalette::Window);
    }
}

void MainWindow::on_pushButton_3_released()
{
    qDebug()<<"released";
    QColorDialog d;
    if (d.exec()) {
        qDebug()<<"ok";
        auto buttonBgActive = d.selectedColor();
        buttonBgActive.setAlphaF(this->ui->horizontalSlider->value()/100.0);
        m_palette.setColor(QPalette::Active, QPalette::Button, buttonBgActive);

        QApplication::setPalette(m_palette);
        setPalette(m_palette);
        ui->label_5->setBackgroundRole(QPalette::Button);
    }
}
