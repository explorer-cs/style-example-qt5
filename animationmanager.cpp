#include "animationmanager.h"
#include "animation.h"

#include <QWidget>

/// 我们需要将动画与widget绑定，并且在特定时候进行特定的操作，
/// AnimationManager就是一个例子
AnimationManager::AnimationManager(QObject *parent) : QObject(parent)
{
    m_animations = new QHash<const QWidget *, Animation*>();
}

void AnimationManager::registerWidget(QWidget *w)
{
    auto animation = new Animation;
    m_animations->insert(w, animation);
}

void AnimationManager::unregisterWidget(QWidget *w)
{
    auto animation = m_animations->value(w);
    if (animation) {
        animation->deleteLater();
    }
    m_animations->remove(w);
}

void AnimationManager::startAnimation(const QWidget *w)
{
    auto animation = m_animations->value(w);
    if (animation) {
        animation->start();
    }
}

void AnimationManager::stopAnimation(const QWidget *w)
{
    auto animation = m_animations->value(w);
    if (animation) {
        animation->stop();
    }
}

void AnimationManager::setAnimationDirection(const QWidget *w, QAbstractAnimation::Direction direction)
{
    auto animation = m_animations->value(w);
    if (animation) {
        animation->setDirection(direction);
    }
}

bool AnimationManager::isAnimationRunning(const QWidget *w)
{
    auto animation = m_animations->value(w);
    if (animation) {
        return animation->state() == QAbstractAnimation::Running;
    }
    return false;
}

const QVariant AnimationManager::value(const QWidget *w)
{
    auto animation = m_animations->value(w);
    if (animation) {
        return animation->currentValue();
    }
    return QVariant();
}

