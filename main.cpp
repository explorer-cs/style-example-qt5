#include "mainwindow.h"
#include <QApplication>

#include <QMainWindow>
#include <QStyleFactory>
#include <QProxyStyle>
#include <QStringListModel>
#include <QComboBox>
#include <QLabel>
#include <QToolBar>

#include "customstyle.h"

/*!
 * \brief main
 * \param argc
 * \param argv
 * \return
 * \details
 * 这个例子展示了如何在主题框架下定制顶级窗口的模糊区域，
 * 主题框架支持qt widget使用blurRegion属性规定自己的模糊区域。
 *
 * 使用条件，首先确保窗口是顶级窗口，如果窗口是不可缩放的，我们在
 * 它show之前设置一次blurRegion属性即可，如果在show之后设置，可能需要
 * 手动使用窗口的update()，确保设置的blurRegion生效。
 *
 * 如果窗口可缩放，建议重写resizeEvent，
 * 在resizeEvent中对blurRegion进行动态更新
 *
 * \note
 * 一定不要在paintEvent中调用widget的update()，否则会导致
 * 循环绘制，使得ui线程繁忙，并且由于优先级，子线程可能无法被正常的调度
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //使用系统主题，不使用custom style
    //QApplication::setStyle(new CustomStyle());
    MainWindow w;
    w.show();

    return a.exec();
}
