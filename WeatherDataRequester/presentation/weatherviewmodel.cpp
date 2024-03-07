#include "weatherviewmodel.h"
#include "domain/getweatherusecase.h"
#include <QFutureWatcher>
#include <QThread>

WeatherViewModel::WeatherViewModel(QObject *parent)
    : QObject{parent}
{
    QObject::connect(&watcher, &QFutureWatcher<WeatherData*>::finished, [&](){
        qDebug()<< "Контекст получения результата: "<<QThread::currentThreadId();
        WeatherData *weatherData = watcher.result();
        weatherModel->setText(weatherData->getStrWeatherData());
    });

    watcher.setFuture(getWeatherDataUseCase.run());
}

WeatherModel *WeatherViewModel::getWeatherModel(){
    return weatherModel;
}

void WeatherViewModel::updateWeatherData(){
    watcher.setFuture(getWeatherDataUseCase.run());
}
