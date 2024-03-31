#include <auroraapp.h>
#include <QtQuick>
#include "notificationmanager.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("Notifier"));

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/Notifier.qml")));

    NotificationManager listener;
    view->rootContext()->setContextProperty("clickListener", QVariant::fromValue(&listener));
    view->show();

    //QObject::connect(&listener, &ClickListener::notify, &dbDelegate, &DbDelegate::openInternalDb);

    return application->exec();
}
