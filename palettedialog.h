#ifndef PALETTEDIALOG_H
#define PALETTEDIALOG_H

#include <QMainWindow>

class ColorScheme;
class QTableWidget;

class PaletteDialog : public QMainWindow
{
    Q_OBJECT
public:
    explicit PaletteDialog(QWidget *parent = nullptr);

    void bindColorScheme(ColorScheme *palette);

signals:

public slots:
    void updateColorTable();

private:
    ColorScheme *m_palette = nullptr;
    QTableWidget *m_table;
};

#endif // PALETTEDIALOG_H
