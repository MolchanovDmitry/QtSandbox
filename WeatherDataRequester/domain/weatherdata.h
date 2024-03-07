#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QObject>

struct Wind {
    double speed;
    double gust;
};

struct Coordinates {
    double longitude;
    double latitude;
};

/**
 * Бизнес представление погодных данных
 */
class WeatherData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(READ getStrWeatherData CONSTANT)
public:
    explicit WeatherData(QObject *parent = nullptr);
    void initFromJson(const QJsonDocument &doc);
    void printModel();
    QString getStrWeatherData();

private:
    QString name;
    QString country;
    QString weatherDescription;

    qint64 date;
    int timezone;

    int temp;
    int pressure;
    int humidity;
    int seaLevel;
    int visibility;
    int clouds;
    qint64 sunrise;
    qint64 sunset;

    Wind wind;
    Coordinates coordinates;
};

#endif // WEATHERDATA_H
