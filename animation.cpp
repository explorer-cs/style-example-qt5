#include "animation.h"

/// Animation代表着一个状态，通过设置它的持续时间、方向、初始值和结束值等，
/// 我们能够模拟出一个动画的 时间-状态 函数，
/// 这里我们模拟的是按钮背景色的透明度
Animation::Animation(QObject *parent) : QVariantAnimation(parent)
{
    setDuration(250);
    setStartValue(0.0);
    setEndValue(1.0);
}
