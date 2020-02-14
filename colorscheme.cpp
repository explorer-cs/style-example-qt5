#include "colorscheme.h"

ColorScheme::ColorScheme(QObject *parent) : QObject(parent)
{

}

void ColorScheme::setColor(const QPalette::ColorRole &role, const QColor &color, const QPalette::ColorGroup &group)
{
    m_palette.setColor(group, role, color);
    Q_EMIT paletteChanged();
}
