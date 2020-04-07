#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Q3DScatter>

class Data;

namespace Ui {
class MainWindow;
}

/*!
 * \brief The MainWindow class
 * \details
 * 在ui文件中拖放想要测试的控件，然后在CustomStyle中针对性的修改它们
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    Data *m_data;
    QtDataVisualization::Q3DScatter *m_scatter;
};

#endif // MAINWINDOW_H
