#ifndef DELEGATE_H
#define DELEGATE_H

#include <QStyledItemDelegate>

class MainWindow;

class Delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit Delegate(MainWindow *window, QObject *parent = nullptr);

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    MainWindow *window;
};

#endif // DELEGATE_H
