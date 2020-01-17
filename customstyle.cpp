#include "customstyle.h"

#include <QStyleOptionSlider>
#include <QPainter>

#include <QApplication>

#include <QIcon>

CustomStyle::CustomStyle(const QString &proxyStyleName, QObject *parent) : QProxyStyle (proxyStyleName)
{

}

void CustomStyle::drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{
    if (control == CC_ScrollBar) {
        /// 我们参考qt的官方文档和源码，可以知道滚动条需要绘制的子控件有8个
        /// QStyle::SC_ScrollBarAddLine     一般的向下或者向右箭头 Scroll bar add line (i.e., down/right arrow); see also QScrollBar.
        /// QStyle::SC_ScrollBarSubLine     向下或向左箭头 Scroll bar sub line (i.e., up/left arrow).
        /// QStyle::SC_ScrollBarAddPage     slider一侧的区域 Scroll bar add page (i.e., page down).
        /// QStyle::SC_ScrollBarSubPage     slider另一侧的区域 Scroll bar sub page (i.e., page up).
        /// QStyle::SC_ScrollBarFirst       置顶按钮，某些style没有 Scroll bar first line (i.e., home).
        /// QStyle::SC_ScrollBarLast        至底按钮 Scroll bar last line (i.e., end).
        /// QStyle::SC_ScrollBarSlider      滚动条slider Scroll bar slider handle.
        /// QStyle::SC_ScrollBarGroove      滚动槽 Special sub-control which contains the area in which the slider handle may move.
        /// 其实有一些子控件不一定要绘制，比如SC_ScrollBarFirst和SC_ScrollBarLast，有一些style中默认是没有的（比如fusion）
        /// 还有SC_ScrollBarGroove也未必被绘制或者被遮蔽，
        /// SC_ScrollBarAddLine，SC_ScrollBarSubLine，
        /// SC_ScrollBarAddPage，SC_ScrollBarSubPage和SC_ScrollBarSlider是一个
        /// 滚动条最为常见的组成部分

        /// 我们需要获取scrollbar的详细信息，通过qstyleoption_cast可以得到
        /// 对应的option，通过拷贝构造函数得到一份备份用于绘制子控件
        /// 我们一般不用在意option是怎么得到的，大部分的Qt控件都能够提供了option的init方法
        const QStyleOptionSlider opt = *qstyleoption_cast<const QStyleOptionSlider*>(option);
        QStyleOption tmp = opt;

        /// 绘制两端指示器
        /// 我们可以通过subControlRect获取对应子控件的rect
        auto subLineRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarSubLine);
        tmp.rect = subLineRect;
        drawControl(CE_ScrollBarSubLine, &tmp, painter, widget);

        auto addLineRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarAddLine);
        tmp.rect = addLineRect;
        drawControl(CE_ScrollBarAddLine, &tmp, painter, widget);

        /// 绘制slider两侧的翻页控件，一般来说可以认为是背景
        /// 其实我们一般没有必要在两端各绘制一次背景，除非我们希望两端的背景根据状态有所区别
        /// 不论如何，Qt还是提供了这两个枚举，这里尊重一下规范
        auto subPageRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarSubPage);
        tmp.rect = subPageRect;
        drawControl(CE_ScrollBarSubPage, &tmp, painter, widget);

        auto addPageRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarAddPage);
        tmp.rect = addPageRect;
        drawControl(CE_ScrollBarAddPage, &tmp, painter, widget);

        /// 绘制滚动条slider
        ///
        /// complex control与一般控件不同之处之一在于它可能拥有不统一的子控件状态，
        /// 以滚动条为例，我们在把鼠标移动到滚动条上时，slider未必属于被hover的状态，
        /// 这是通过activeSubControls来进行判断的
        ///
        /// 我们可以通过activeSubControls和state赋予不同subcontrol更详细的状态，
        /// 比如如果scrollbar本身是被悬停但是并未悬停在slider上，
        /// 那么我们的tmp option也可以将state的State_MouseOver设置为false，
        /// 然后再绘制这个SC
        bool hover = false;
        bool pressed = false;
        if (opt.activeSubControls.testFlag(SC_ScrollBarSlider)) {
            /// 鼠标是否悬停在slider上
            if (opt.state.testFlag(State_MouseOver)) {
                hover = true;
                /// 鼠标是否按住slider
                if (opt.state.testFlag(State_Sunken)) {
                    pressed = true;
                }
            }
        }
        painter->save();
        /// 根据slider的state不同，drawControl可以做不同的绘制，
        /// 简单的处理也可以放在这里进行

        tmp.state.setFlag(State_MouseOver, hover);
        tmp.state.setFlag(State_Sunken, pressed);
        auto sliderRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarSlider, widget);
        tmp.rect = sliderRect;
        drawControl(CE_ScrollBarSlider, &tmp, painter, widget);
        painter->restore();

        return;
    }
    return QProxyStyle::drawComplexControl(control, option, painter, widget);
}

void CustomStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch (element) {
    case CE_ScrollBarSubPage: {
        painter->save();
        painter->setPen(Qt::black);
        painter->setBrush(Qt::red);
        painter->drawRect(option->rect.adjusted(0, 0, -1, 0));
        painter->restore();
        return;
    }
    case CE_ScrollBarAddPage: {
        painter->save();
        painter->setPen(Qt::black);
        painter->setBrush(Qt::green);
        painter->drawRect(option->rect.adjusted(0, 0, -1, 0));
        painter->restore();
        return;
    }
    case CE_ScrollBarSlider: {
        painter->save();
        painter->setPen(Qt::black);
        QColor color = Qt::blue;
        if (option->state & State_MouseOver) {
            color = color.darker();
            if (option->state & State_Sunken) {
                color = color.darker();
            }
        }
        painter->setBrush(color);

        painter->drawRect(option->rect.adjusted(0, 0, -1, 0));
        painter->restore();
        return;
    }
    case CE_ScrollBarSubLine: {
        /// 我们需要判断滚动条的方向来绘制subline控件，
        /// 如果需要体现点击效果，我们需要像slider一样，
        /// 通过上一级判断后修改子控件option的state，然后
        /// 再进行绘制

        QIcon icon;
        if (option->state.testFlag(State_Horizontal)) {
            icon = QIcon::fromTheme("pan-start-symbolic");
        } else {
            icon = QIcon::fromTheme("pan-up-symolic");
        }

        /// 这里我使用调色板绘制图标的底色
        painter->setBrush(option->palette.foreground());
        painter->drawRect(option->rect.adjusted(0, 0, -1, -1));
        icon.paint(painter, option->rect, Qt::AlignCenter);
        return;
    }
    case CE_ScrollBarAddLine: {
        QIcon icon;
        if (option->state.testFlag(State_Horizontal)) {
            icon = QIcon::fromTheme("pan-end-symbolic");
        } else {
            icon = QIcon::fromTheme("pan-down-symolic");
        }
        painter->setBrush(option->palette.foreground());
        painter->drawRect(option->rect.adjusted(0, 0, -1, -1));
        icon.paint(painter, option->rect, Qt::AlignCenter);
        return;
    }
    default:
        break;
    }
    return QProxyStyle::drawControl(element, option, painter, widget);
}

void CustomStyle::drawItemPixmap(QPainter *painter, const QRect &rectangle, int alignment, const QPixmap &pixmap) const
{
    return QProxyStyle::drawItemPixmap(painter, rectangle, alignment, pixmap);
}

void CustomStyle::drawItemText(QPainter *painter, const QRect &rectangle, int alignment, const QPalette &palette, bool enabled, const QString &text, QPalette::ColorRole textRole) const
{
    return QProxyStyle::drawItemText(painter, rectangle, alignment, palette, enabled, text, textRole);
}

void CustomStyle::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    return QProxyStyle::drawPrimitive(element, option, painter, widget);
}

QPixmap CustomStyle::generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *option) const
{
    return QProxyStyle::generatedIconPixmap(iconMode, pixmap, option);
}

QStyle::SubControl CustomStyle::hitTestComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, const QPoint &position, const QWidget *widget) const
{
    return QProxyStyle::hitTestComplexControl(control, option, position, widget);
}

QRect CustomStyle::itemPixmapRect(const QRect &rectangle, int alignment, const QPixmap &pixmap) const
{
    return QProxyStyle::itemPixmapRect(rectangle, alignment, pixmap);
}

QRect CustomStyle::itemTextRect(const QFontMetrics &metrics, const QRect &rectangle, int alignment, bool enabled, const QString &text) const
{
    return QProxyStyle::itemTextRect(metrics, rectangle, alignment, enabled, text);
}

int CustomStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    switch (metric) {
    /// 设置滚动条的宽度
    case PM_ScrollBarExtent: {
        return (int)12*qApp->devicePixelRatio();
    }
    /// 设置滚动条slider的最小长度
    case PM_ScrollBarSliderMin: {
        return (int)100*qApp->devicePixelRatio();
    }
    default:
        break;
    }
    return QProxyStyle::pixelMetric(metric, option, widget);
}

void CustomStyle::polish(QWidget *widget)
{
    if (widget->inherits("QScrollBar")) {
        widget->setAttribute(Qt::WA_TranslucentBackground);
        /// 我们需要在polish中激活滚动条的Hover属性
        /// 这样Hover事件才会被处理
        widget->setAttribute(Qt::WA_Hover);
    }
    return QProxyStyle::polish(widget);
}

void CustomStyle::polish(QApplication *application)
{
    return QProxyStyle::polish(application);
}

void CustomStyle::polish(QPalette &palette)
{
    /// 我们可以通过调色板的polish重载方法
    /// 修改系统调色板，这里的修改是全局的
    /// 调色板是QStyle中很重要的一部分，因为大部分
    /// 的Qt控件都使用调色板为其自身上色
    QProxyStyle::polish(palette);
    palette.setBrush(QPalette::Foreground, Qt::black);
}

void CustomStyle::unpolish(QWidget *widget)
{
    return QProxyStyle::unpolish(widget);
}

void CustomStyle::unpolish(QApplication *application)
{
    return QProxyStyle::unpolish(application);
}

QSize CustomStyle::sizeFromContents(QStyle::ContentsType type, const QStyleOption *option, const QSize &contentsSize, const QWidget *widget) const
{
    return QProxyStyle::sizeFromContents(type, option, contentsSize, widget);
}

QIcon CustomStyle::standardIcon(QStyle::StandardPixmap standardIcon, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::standardIcon(standardIcon, option, widget);
}

QPalette CustomStyle::standardPalette() const
{
    return QProxyStyle::standardPalette();
}

int CustomStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    switch (hint) {
    /// 让ScrollView viewport的绘制区域包含scrollbar和corner widget
    /// 这个例子中没有什么作用，如果我们需要绘制一个背景透明的滚动条
    /// 这个style hint对我们的意义应该很大，因为我们希望视图能够帮助
    /// 我们填充滚动条的背景区域，否则当背景透明时底下会出现明显的分割
    case SH_ScrollView_FrameOnlyAroundContents: {
        return false;
    }
    default:
        break;
    }
    return QProxyStyle::styleHint(hint, option, widget, returnData);
}

QRect CustomStyle::subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex *option, QStyle::SubControl subControl, const QWidget *widget) const
{
    return QProxyStyle::subControlRect(control, option, subControl, widget);
}

QRect CustomStyle::subElementRect(QStyle::SubElement element, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::subElementRect(element, option, widget);
}
