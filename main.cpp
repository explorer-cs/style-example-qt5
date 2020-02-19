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
 * CustomStyle, MainWindow
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(new CustomStyle());
    MainWindow w;
    w.setAttribute(Qt::WA_TranslucentBackground);

    QMainWindow settingsWindow;
    settingsWindow.setAttribute(Qt::WA_TranslucentBackground);

    /*!
     * \brief c 用于切换主题
     */
    QComboBox c;
    QStringList styles = QStyleFactory::keys();
    styles.prepend("自定义");
    QStringListModel model(styles);
    c.setModel(&model);

    /*!
     * \brief c2 用于改变CustomStyle的proxy
     */
    QComboBox c2;
    QStringList styles2 = QStyleFactory::keys();
    QStringListModel model2(styles2);
    c2.setModel(&model2);
    c2.setCurrentText("Windows");

    c.connect(&c, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index){
        if (index == 0) {
            QApplication::setStyle(new CustomStyle());
            c2.setEnabled(true);
        } else {
            QApplication::setStyle(model.index(index).data().toString());
            c2.setEnabled(false);
        }
    });

    c2.connect(&c2, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index){
        if (c.currentText() == "自定义") {
            QApplication::setStyle(new CustomStyle(model2.index(index).data().toString()));
        }
    });

    QToolBar t;
    QLabel l("选择样式:");
    t.addWidget(&l);
    t.addWidget(&c);

    QLabel l2("CustomStyle继承自:");
    t.addWidget(&l2);
    t.addWidget(&c2);

    settingsWindow.addToolBar(&t);
    settingsWindow.setCentralWidget(&w);

    settingsWindow.show();

    return a.exec();
}
