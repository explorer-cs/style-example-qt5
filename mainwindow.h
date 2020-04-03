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
    //我们需要在resizeEvent中动态的设置想要模糊的区域
    void resizeEvent(QResizeEvent *e);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
