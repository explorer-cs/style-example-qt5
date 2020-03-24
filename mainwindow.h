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
    friend class Delegate;
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resetDelegate();

private slots:
    void on_widthSpinBox_valueChanged(int arg1);

    void on_heightSpinBox_valueChanged(int arg1);

    void on_autoAdjustCheckBox_toggled(bool checked);

    void on_enableCustomMaxLineCheckBox_toggled(bool checked);

    void on_maxLineSpinBox_valueChanged(int arg1);

    void on_fontSizeSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
