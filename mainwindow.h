#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

protected:
    void paintEvent(QPaintEvent *e);

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

private:
    Ui::MainWindow *ui;

    QPalette m_palette;
};

#endif // MAINWINDOW_H
