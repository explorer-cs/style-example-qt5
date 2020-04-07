#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "data.h"

#include <QFileDialog>
#include <QInputDialog>

#include <QMessageBox>

using namespace QtDataVisualization;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scatter = new Q3DScatter();
    auto container = QWidget::createWindowContainer(m_scatter);

    m_data = new Data(m_scatter);

    QScatter3DSeries *series = new QScatter3DSeries;
    series->setMesh(QAbstract3DSeries::MeshCube);
    series->setItemSize(0.05);
    series->setMeshSmooth(true);
    m_scatter->addSeries(series);

    auto layout = new QHBoxLayout;
    layout->addWidget(container);
    ui->frame->setLayout(layout);
    ui->frame->setMinimumSize(400, 400);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete m_scatter;
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog dlg;
    dlg.setDirectory("/usr/share/icons");

    dlg.setNameFilter("*.png *.jpg *.svg *.jpeg");
    if (dlg.exec()) {
        auto path = dlg.selectedFiles().first();
        QImage img = QImage(path);
        if (img.rect().width() > 512) {
            QMessageBox::warning(nullptr, nullptr, "A big image should be handled slowly, you have to waiting");
        }
        if (!img.hasAlphaChannel())
            QMessageBox::warning(nullptr, nullptr, "no alpha channel");

        int alpha_pixel = 0;
        double stddev = 0;
        m_data->setImage(img, alpha_pixel, stddev);
        ui->label->setPixmap(QPixmap::fromImage(img));

        ui->statusBar->showMessage(QString("path icon: %1, stddev: %4, valid pixel: %2, total: %3").
                                   arg(path).
                                   arg(img.width()*img.height() - alpha_pixel).
                                   arg(img.width() * img.height()).
                                   arg(QString::number(stddev, 10, 5)));

        if (stddev < 0.2) {
            QMessageBox::information(nullptr, nullptr, "A pure color image");
        } else {
            QMessageBox::information(nullptr, nullptr, "Not a pure color image");
        }

//        ui->statusBar->showMessage(QString("img: %1, valid pixel: %2, total: %3").arg(path).arg(img.width()*img.height() - alpha_pixel).arg(img.width() * img.height()));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QInputDialog dlg;
    dlg.setWindowTitle("Input theme icon name");
    if (dlg.exec()) {
        auto name = dlg.textValue();
        QIcon icon = QIcon::fromTheme(name);
        if (icon.isNull()) {
            QMessageBox::critical(nullptr, "Error", "not found");
            return;
        }

        QInputDialog sizeDlg;
        sizeDlg.setInputMode(QInputDialog::IntInput);
        sizeDlg.setIntRange(0, 512);
        sizeDlg.setWindowTitle("Input theme icon size");
        if (sizeDlg.exec()) {
            int size = sizeDlg.intValue();
            //qDebug()<<size;
            if (size <= 0) {
                QMessageBox::critical(nullptr, "Error", "size is invalid");
                return;
            }

            QPixmap scaledPixmap = icon.pixmap(QSize(size, size));
            QImage img = scaledPixmap.toImage();
            int alpha_pixel = 0;
            double stddev = 0;
            m_data->setImage(img, alpha_pixel, stddev);
            ui->label->setPixmap(QPixmap::fromImage(img));

            ui->statusBar->showMessage(QString("themed icon: %1, stddev: %5, size: %4x%4, valid pixel: %2, total: %3").
                                       arg(name).
                                       arg(img.width()*img.height() - alpha_pixel).
                                       arg(img.width() * img.height()).
                                       arg(size).
                                       arg(QString::number(stddev, 10, 5)));

            if (stddev < 0.2) {
                QMessageBox::information(nullptr, nullptr, "A pure color image");
            } else {
                QMessageBox::information(nullptr, nullptr, "Not a pure color image");
            }
        }
    }
}
