#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include "menubarclickdelegate.h"
#include "dbdelegate.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    DbDelegate dbDelegate;
    MenuBarClickDelegate menuBarClickDelegate;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("menuBarClickDelegate", QVariant::fromValue(&menuBarClickDelegate));
    engine.rootContext()->setContextProperty("patientsModel", QVariant::fromValue(dbDelegate.patientsModel));
    engine.rootContext()->setContextProperty("researchModel", QVariant::fromValue(dbDelegate.researchModel));
    engine.rootContext()->setContextProperty("patientInfoModel", QVariant::fromValue(dbDelegate.patientInfoModel));

    QObject::connect(dbDelegate.patientsModel, &PatientTableModel::onRowSelected, &dbDelegate, &DbDelegate::loadPatientByRowIndex);
    QObject::connect(&menuBarClickDelegate, &MenuBarClickDelegate::onOpenInternalDbClicked, &dbDelegate, &DbDelegate::openInternalDb);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
