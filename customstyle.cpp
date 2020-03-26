#include "customstyle.h"

#include <QAbstractItemView>
#include <QEvent>

CustomStyle::CustomStyle(const QString &proxyStyleName, QObject *parent) : QProxyStyle (proxyStyleName)
{

}

bool CustomStyle::eventFilter(QObject *obj, QEvent *e)
{
    auto view = qobject_cast<QAbstractItemView *>(obj);
    if (!view)
        return false;
    if (e->type() == QEvent::Resize) {
        bool ret = QProxyStyle::eventFilter(obj, e);

        QRegion region;
        QPainterPath path;
        int pm_frameWidth = pixelMetric(PM_DefaultFrameWidth);
        path.addRoundedRect(view->rect().adjusted(pm_frameWidth, pm_frameWidth, -pm_frameWidth, -pm_frameWidth), 6, 6);
        region = path.toFillPolygon().toPolygon();
        view->setMask(region);

        return ret;
    }
}

void CustomStyle::drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{
    return QProxyStyle::drawComplexControl(control, option, painter, widget);
}

void CustomStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
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
    return QProxyStyle::pixelMetric(metric, option, widget);
}

void CustomStyle::polish(QWidget *widget)
{
    if (auto view = qobject_cast<const QAbstractItemView *>(widget)) {
        QRegion region;
        QPainterPath path;
        int pm_frameWidth = pixelMetric(PM_DefaultFrameWidth);
        path.addRoundedRect(view->rect().adjusted(pm_frameWidth, pm_frameWidth, -pm_frameWidth, -pm_frameWidth), 6, 6);
        region = path.toFillPolygon().toPolygon();
        const_cast<QWidget *>(widget)->setMask(region);

        widget->installEventFilter(this);
        return;
    }
    return QProxyStyle::polish(widget);
}

void CustomStyle::polish(QApplication *application)
{
    return QProxyStyle::polish(application);
}

void CustomStyle::polish(QPalette &palette)
{
    return QProxyStyle::polish(palette);
}

void CustomStyle::unpolish(QWidget *widget)
{
    if (auto view = qobject_cast<const QAbstractItemView *>(widget)) {
        /// 当主题切换时，需要还原mask，并且移除事件钩子
        widget->setMask(QRegion());
        widget->removeEventFilter(this);
        return;
    }
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
