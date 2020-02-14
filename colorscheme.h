#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <QObject>
#include <QPalette>

class ColorScheme : public QObject
{
    Q_OBJECT
public:
    explicit ColorScheme(QObject *parent = nullptr);
    void initPalette(const QPalette &palette) {
        m_palette = palette;
    }
    const QPalette currentPalette() {return m_palette;}

    QColor color(QPalette::ColorGroup group, QPalette::ColorRole role) {
        return m_palette.color(group, role);
    }

signals:
    void paletteChanged();

public slots:
    void setColor(const QPalette::ColorRole &role, const QColor &color, const QPalette::ColorGroup &group = QPalette::Active);

private:
    QPalette m_palette;
};

#endif // COLORSCHEME_H
