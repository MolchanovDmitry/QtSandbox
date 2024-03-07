#include "getweatherusecase.h"
#include <QtConcurrent>
#include <QDebug>

GetWeatherUseCase::GetWeatherUseCase(WeatherRepository *repository, QObject *parent)
    : QObject{parent}
{
    this->repository = repository;
}


QFuture<WeatherData*> GetWeatherUseCase::run(){
    auto rep = this->repository;
    return QtConcurrent::run([rep]() {
        qDebug()<< "Контекст репозитория: "<<QThread::currentThreadId();
        return rep->getWeatherDate();
    });
}
