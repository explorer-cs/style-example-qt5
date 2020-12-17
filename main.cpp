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
#include "xatom-helper.h"

/*!
 * \brief main
 * \param argc
 * \param argv
 * \return
 * \see
 * CustomStyle, MainWindow
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(new CustomStyle());
    MainWindow w;

    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS | MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(w.winId(), hints);

    w.show();

    return a.exec();
}
