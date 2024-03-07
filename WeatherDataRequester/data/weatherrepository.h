#ifndef WEATHERREPOSITORY_H
#define WEATHERREPOSITORY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "domain/weatherdata.h"

class WeatherRepository : public QObject
{
    Q_OBJECT
public:
    explicit WeatherRepository(QNetworkAccessManager *netMan = new QNetworkAccessManager(), QObject *parent = nullptr);

    WeatherData *getWeatherDate();

private:
    QNetworkAccessManager *netMan;

};

#endif // WEATHERREPOSITORY_H
