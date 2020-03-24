#include "delegate.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QTextLayout>
#include <QPainter>

Delegate::Delegate(MainWindow *window, QObject *parent) : QStyledItemDelegate(parent)
{
    this->window = window;
}

QSize Delegate::sizeHint(const QStyleOptionViewItem &option0, const QModelIndex &index) const
{
    QStyleOptionViewItem option = option0;
    initStyleOption(&option, index);

    qDebug()<<"size hint";
    bool autoAdjust = window->ui->autoAdjustCheckBox->isChecked();
    if (autoAdjust) {
        int fixedWidth = window->ui->widthSpinBox->value();
        int maxLineCount = 0;
        if (window->ui->maxLineSpinBox->isEnabled()) {
            maxLineCount = window->ui->maxLineSpinBox->value();
        }

        QString text = option.text;
        QFont font = option.font;
        QFontMetrics fontMetrics = option.fontMetrics;
        int lineSpacing = fontMetrics.lineSpacing();
        int textHight = 0;

        int itemHeight = 5 + window->ui->listWidget->iconSize().height() + 5 + textHight + 5;

        QTextLayout textLayout(text, font);

        QTextOption opt;
        opt.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        opt.setAlignment(Qt::AlignHCenter);

        textLayout.setTextOption(opt);
        textLayout.beginLayout();

        while (true) {
            QTextLine line = textLayout.createLine();
            if (!line.isValid())
                break;

            line.setLineWidth(fixedWidth);
            textHight += lineSpacing;
        }

        textLayout.endLayout();
        if (maxLineCount > 0) {
            textHight = qMin(maxLineCount * lineSpacing, textHight);
        }
        itemHeight += textHight;

        return QSize(fixedWidth, itemHeight);
    } else {
        int width = window->ui->widthSpinBox->value();
        int height = window->ui->heightSpinBox->value();
        return QSize(width, height);
    }
    return QStyledItemDelegate::sizeHint(option, index);
}

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option0, const QModelIndex &index) const
{
    QStyleOptionViewItem option = option0;
    initStyleOption(&option, index);

    auto size = option.rect.size();
    int textMaxHeight = size.height();

    painter->save();
    painter->fillRect(option.rect, option.palette.highlight());
    painter->translate(0, 5);
    textMaxHeight -= 5;
    auto iconSize = window->ui->listWidget->iconSize();
    option.icon.paint(painter, 0, 0, option.rect.width(), iconSize.height());
    painter->translate(0, iconSize.height());
    textMaxHeight -= iconSize.height();
    painter->translate(0, 5);
    textMaxHeight -= 5;

    int maxLineCount = 0;
    int lineCount = 0;
    if (window->ui->maxLineSpinBox->isEnabled()) {
        maxLineCount = window->ui->maxLineSpinBox->value();
    }

    QString text = option.text;
    QFont font = option.font;
    QFontMetrics fontMetrics = option.fontMetrics;
    int lineSpacing = fontMetrics.lineSpacing();

    QTextLayout textLayout(text, font);

    QTextOption opt;
    opt.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    opt.setAlignment(Qt::AlignHCenter);

    textLayout.setTextOption(opt);
    textLayout.beginLayout();

    int width = option.rect.width();

    int y = 0;
    while (true) {
        QTextLine line = textLayout.createLine();
        if (!line.isValid())
            break;

        line.setLineWidth(option.rect.width());
        int nextLineY = y + lineSpacing;
        lineCount++;

        if (textMaxHeight >= nextLineY + lineSpacing && lineCount != maxLineCount) {
            line.draw(painter, QPoint(0, y));
            y = nextLineY;
        } else {
            QString lastLine = option.text.mid(line.textStart());
            QString elidedLastLine = fontMetrics.elidedText(lastLine, Qt::ElideRight, width);
            auto rect = QRect(0, y /*+ fontMetrics.ascent()*/, width, textMaxHeight);
            //opt.setWrapMode(QTextOption::NoWrap);
            opt.setWrapMode(QTextOption::NoWrap);
            painter->drawText(rect, elidedLastLine, opt);
            //painter->drawText(QPoint(0, y + fontMetrics.ascent()), elidedLastLine);
            line = textLayout.createLine();
            break;
        }
    }
    textLayout.endLayout();

    painter->restore();
}
