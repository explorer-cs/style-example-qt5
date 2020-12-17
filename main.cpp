#include "mainwindow.h"
#include <QApplication>

#include <QVector4D>

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

    MainWindow w;

    w.setWindowFlag(Qt::Popup);
    w.move(100, 100);

    w.setProperty("useCustomShadow", true);
    w.setProperty("customShadowDarkness", 1.0);
    w.setProperty("customShadowWidth", 20);
    w.setProperty("customShadowRadius", QVector4D(1, 1, 1, 1));
    w.setProperty("customShadowMargins", QVector4D(20, 20, 20, 20));

    w.show();

    return a.exec();
}
