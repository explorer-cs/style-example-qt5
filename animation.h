#ifndef ANIMATION_H
#define ANIMATION_H

#include <QVariantAnimation>

class Animation : public QVariantAnimation
{
    Q_OBJECT
public:
    explicit Animation(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ANIMATION_H
