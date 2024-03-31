#include "notificationmanager.h"

NotificationManager::NotificationManager(QObject *parent) : QObject(parent)
{

}

void NotificationManager::notify(const QString text)
{
    QDBusInterface interface("org.freedesktop.Notifications",
                             "/org/freedesktop/Notifications",
                             "org.freedesktop.Notifications",
                             QDBusConnection::sessionBus());

    if (interface.isValid()) {
        interface.call("Notify",
                       QString("Notifier"),
                       uint(0),
                       QString(),
                       QString("Уведомление"),
                       text,
                       QStringList(),
                       QVariantMap(),
                       int(-1)).arguments().at(0).toUInt();
    }
}
