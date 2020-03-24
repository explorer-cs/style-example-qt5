#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "delegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->setViewMode(QListWidget::IconMode);
    ui->listWidget->setIconSize(QSize(64, 64));

    auto delegate = new Delegate(this, this);
    ui->listWidget->setItemDelegate(delegate);

    QListWidgetItem *item = new QListWidgetItem;
    item->setIcon(QIcon::fromTheme("folder"));
    item->setText(ui->plainTextEdit->toPlainText());
    ui->listWidget->addItem(item);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetDelegate()
{
    auto delegate = new Delegate(this, this);
    ui->listWidget->setItemDelegate(delegate);
}

void MainWindow::on_widthSpinBox_valueChanged(int arg1)
{
    auto delegate = new Delegate(this, this);
    ui->listWidget->setItemDelegate(delegate);
}

void MainWindow::on_heightSpinBox_valueChanged(int arg1)
{
    resetDelegate();
}

void MainWindow::on_autoAdjustCheckBox_toggled(bool checked)
{
    resetDelegate();
}

void MainWindow::on_enableCustomMaxLineCheckBox_toggled(bool checked)
{
    ui->maxLineSpinBox->setEnabled(checked);
    resetDelegate();
}

void MainWindow::on_maxLineSpinBox_valueChanged(int arg1)
{
    resetDelegate();
}

void MainWindow::on_fontSizeSpinBox_valueChanged(int arg1)
{
    auto font = QApplication::font();
    font.setPixelSize(arg1);
    QApplication::setFont(font);
    resetDelegate();
}
