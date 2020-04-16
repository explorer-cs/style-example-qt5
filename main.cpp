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
 * \see
 * InternalStyle, MainWindow
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //想使用InternalStyle绕开系统主题，就不能对qApp设置styleSheet，但是可以对控件设置qss
//    a.setStyleSheet("QPushButton{"
//                    "color: red;"
//                    "}");

    // fusion 是qt默认的主题，这里也可以改成ukui-default或者ukui-light
    a.setStyle(new InternalStyle("fusion"));

    MainWindow w;
    w.setStyleSheet("background-color: white");

    w.show();

    return a.exec();
}
