#ifndef MATERIALSWITCH_H
#define MATERIALSWITCH_H

#include <QWidget>
#include <QtWidgets>

/**
 * Реализация свича материал дизайна
 */
class MaterialSwitch : public QWidget {
    Q_OBJECT
public:
    MaterialSwitch(QWidget *parent = nullptr);

    void setCheck(bool isChecked) {
        if (this->isChecked != isChecked) {
            switchCheck();
        }
    }

    void switchCheck() {
        isChecked = !isChecked;
        update();
        emit onCheckChanged(isChecked);
    }

signals:

    void onCheckChanged(bool isChecked);

protected:
    void paintEvent(QPaintEvent *event) override {

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Обводка
        QPen shadowPen;
        shadowPen.setBrush(QColor(0, 0, 0, 50));

        // Фоновая линия
        painter.setBrush(getBackLineColor());
        painter.setPen(shadowPen);
        painter.drawRoundedRect(getBackLine(), 15, 15);

        // Тамб
        painter.setBrush(getThumbColor());
        painter.setPen(shadowPen);
        painter.drawEllipse(getThumb());
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            switchCheck();
        }
    }

private:
    bool isChecked = false;
    QColor checkedThumbColor = QColor(98, 0, 238);
    QColor unCheckerThumbColor = QColor{Qt::white};
    QColor checkedBackLineColor = QColor(164, 114, 234);
    QColor unCheckedBackLineColor = QColor(155, 155, 155);

    QRect getThumb() {
        int x = isChecked ? width() / 2 : 0;
        return QRect(x, 0, height(), height());
    }

    QRect getBackLine() {
        auto rootHeight = height();
        auto rectHeight = rootHeight / 1.5;
        auto topPadding = (rootHeight - rectHeight) / 2;
        auto hPadding = width() / 7;
        return QRect(hPadding, topPadding, width() - hPadding * 2, rectHeight);
    }

    QColor getThumbColor() {
        return isChecked ? checkedThumbColor : unCheckerThumbColor;
    }

    QColor getBackLineColor() {
        return isChecked ? checkedBackLineColor : unCheckedBackLineColor;
    }
};

#endif // MATERIALSWITCH_H
