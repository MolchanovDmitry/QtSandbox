#ifndef UPDATEBUTTONCLICKDELEGATE_H
#define UPDATEBUTTONCLICKDELEGATE_H

#include <QObject>

/**
 * Обработчик нажатия на кнопку "Обновить"
 */
class UpdateButtonClickDelegate : public QObject
{
    Q_OBJECT
public:
    explicit UpdateButtonClickDelegate(QObject *parent = nullptr);

signals:
    void onUpdateButtonClick();
};

#endif // UPDATEBUTTONCLICKDELEGATE_H
