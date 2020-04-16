#ifndef CUSTOMSTYLE_H
#define CUSTOMSTYLE_H

#include <QProxyStyle>

/*!
 * \brief The InternalStyle class
 * \note
 * 在ukui主题框架下，Qt应用的默认主题将会被统一的管理起来，如果不想受到系统主题的影响，
 * 可以使用类名为InternalStyle的style派生类替换当前系统主题，InternalStyle是一个绕开主题管理的
 * 命名规范，只要当前的qApp使用这个style，则无论系统主题如何切换，InternalStyle都不会被覆盖。
 */
class InternalStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit InternalStyle(const QString &proxyStyleName = "windows", QObject *parent = nullptr);

signals:

public slots:
};

#endif // CUSTOMSTYLE_H
