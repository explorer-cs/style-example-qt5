#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <QObject>
#include <QAbstractAnimation>

class Animation;

class AnimationManager : public QObject
{
    Q_OBJECT
public:
    explicit AnimationManager(QObject *parent = nullptr);

    void registerWidget(QWidget *w);
    void unregisterWidget(QWidget *w);

    void startAnimation(const QWidget *w);
    void stopAnimation(const QWidget *w);
    void setAnimationDirection(const QWidget *w, QAbstractAnimation::Direction direction);
    bool isAnimationRunning(const QWidget *w);
    const QVariant value(const QWidget *w);

private:
    QHash<const QWidget *, Animation *> *m_animations;
};

#endif // ANIMATIONMANAGER_H
