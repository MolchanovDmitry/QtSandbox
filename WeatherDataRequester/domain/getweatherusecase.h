#ifndef GETWEATHERUSECASE_H
#define GETWEATHERUSECASE_H

#include <QObject>
#include "data/weatherrepository.h"
#include <QFuture>

class GetWeatherUseCase : public QObject
{
    Q_OBJECT
public:
    explicit GetWeatherUseCase(WeatherRepository *repository = new WeatherRepository(), QObject *parent = nullptr);

    QFuture<WeatherData*> run();

private:
    WeatherRepository *repository;

};

#endif // GETWEATHERUSECASE_H
