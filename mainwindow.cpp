#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "palettedialog.h"
#include "colorscheme.h"

#include <QCheckBox>
#include <QPushButton>
#include <QColorDialog>

#include <QStyle>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *p = new QPushButton("color settings", this);
    ui->statusBar->addWidget(p);
    auto c = new ColorScheme(this);
    connect(p, &QPushButton::clicked, [=](){
        auto d = new PaletteDialog;
        c->initPalette(qApp->palette());
        d->bindColorScheme(c);
        d->show();
    });

    QCheckBox *b = new QCheckBox("Disable", this);
    ui->statusBar->addWidget(b);
    connect(b, &QCheckBox::toggled, [=](bool checked){
        ui->centralWidget->setDisabled(checked);
    });

    QPushButton *p2 = new QPushButton("restore standard palette", this);
    ui->statusBar->addWidget(p2);
    connect(p2, &QPushButton::clicked, [=](){
        QApplication::setPalette(QApplication::style()->standardPalette());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
