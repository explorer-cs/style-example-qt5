#include "palettedialog.h"
#include "colorscheme.h"

#include <QColorDialog>

#include <QTableWidget>

#include <QMetaEnum>

#include <QApplication>

#include <QDebug>

PaletteDialog::PaletteDialog(QWidget *parent) : QMainWindow(parent)
{
    auto table = new QTableWidget(this);
    m_table = table;
    setCentralWidget(table);

    connect(m_table, &QTableWidget::clicked, [=](const QModelIndex &index){
        if (!index.isValid())
            return;

        QColorDialog d;
        auto result = d.exec();
        if (result == QDialog::Accepted) {
            auto color = d.selectedColor();
            m_palette->setColor(QPalette::ColorRole(index.row()),
                                color,
                                QPalette::ColorGroup(index.column()));

            QApplication::setPalette(m_palette->currentPalette());
        }
    });
}

void PaletteDialog::bindColorScheme(ColorScheme *palette)
{
    m_palette = palette;

    QMetaEnum me = QMetaEnum::fromType<QPalette::ColorRole>();
    m_table->setRowCount(QPalette::ColorRole::NColorRoles);

    me = QMetaEnum::fromType<QPalette::ColorGroup>();
    m_table->setColumnCount(me.keyCount());

    updateColorTable();
}

void PaletteDialog::updateColorTable()
{
    if (!m_palette)
        return;

    QMetaEnum meRow = QMetaEnum::fromType<QPalette::ColorRole>();
    QMetaEnum meColumn = QMetaEnum::fromType<QPalette::ColorGroup>();

    for (int i = 0; i < m_table->rowCount(); i++) {
        m_table->setVerticalHeaderItem(i, new QTableWidgetItem(meRow.key(i)));
        for (int j = 0; j < m_table->columnCount(); j++) {
            if (!m_table->horizontalHeaderItem(j)) {
                m_table->setHorizontalHeaderItem(j, new QTableWidgetItem(meColumn.key(j)));
            }
            m_table->setItem(i, j, new QTableWidgetItem);
            auto color = m_palette->color(QPalette::ColorGroup(meColumn.value(j)), QPalette::ColorRole(meRow.value(i)));
            qDebug()<<j<<i;
            qDebug()<<meColumn.key(j)<<meRow.key(i)<<color;
            qDebug()<<"========";
            m_table->item(i, j)->setBackgroundColor(color);
        }
    }
}
