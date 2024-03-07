#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>
#include <QFuture>
#include <QFutureWatcher>

#include "domain/weatherdata.h"
#include "presentation/weathermodel.h"
#include "presentation/updatebuttonclickdelegate.h"
#include "domain/getweatherusecase.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qDebug()<< "Главный поток: "<<QThread::currentThreadId();

    WeatherModel weatherModel; // модель представления погодных данных
    UpdateButtonClickDelegate updUpdateButtonClickDelegate; // обработчик нажатия на кнопку
    GetWeatherUseCase getWeatherDataUseCase; // сценарий получения погодных данных
    QFutureWatcher<WeatherData*> watcher; // результат сценария получени погодных данных

    // Подписываемся на результат
    QObject::connect(&watcher, &QFutureWatcher<WeatherData*>::finished, [&](){
        qDebug()<< "Контекст получения результата: "<<QThread::currentThreadId();
        WeatherData *weatherData = watcher.result();
        weatherModel.setText(weatherData->getStrWeatherData());
    });

    // Подписываемся на нажатие кнопки "обновить"
    QObject::connect(&updUpdateButtonClickDelegate, &UpdateButtonClickDelegate::onUpdateButtonClick, [&watcher,&getWeatherDataUseCase](){
        watcher.setFuture(getWeatherDataUseCase.run());
    });
    watcher.setFuture(getWeatherDataUseCase.run());

    QQmlApplicationEngine engine;

    // Связываем модели с представлением
    engine.rootContext()->setContextProperty("weatherModel", QVariant::fromValue(&weatherModel));
    engine.rootContext()->setContextProperty("updUpdateButtonClickDelegate", QVariant::fromValue(&updUpdateButtonClickDelegate));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
