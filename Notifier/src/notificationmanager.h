#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QObject>
#include <QDebug>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusInterface>
#include <QVariantMap>

class NotificationManager : public QObject
{
    Q_OBJECT
public:
    explicit NotificationManager(QObject *parent = nullptr);

    Q_INVOKABLE void notify(const QString text);
};

#endif // NOTIFICATIONMANAGER_H
