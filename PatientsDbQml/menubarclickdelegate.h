#ifndef MENUBARCLICKDELEGATE_H
#define MENUBARCLICKDELEGATE_H

#include <QAbstractItemModel>
#include "dbdelegate.h"

/**
 * Делегат обработки нажатий меню
 */
class MenuBarClickDelegate : public QObject
{
    Q_OBJECT

public:
    explicit MenuBarClickDelegate(QObject *parent = nullptr);

signals:
    void onOpenInternalDbClicked();

};

#endif // MENUBARCLICKDELEGATE_H
