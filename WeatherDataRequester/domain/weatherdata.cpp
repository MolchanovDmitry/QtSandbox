#include "weatherdata.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>
#include <QDateTime>

WeatherData::WeatherData(QObject *parent)
    : QObject{parent}
{

}

void WeatherData::initFromJson(const QJsonDocument &doc){
    QJsonObject json = doc.object();

    this->name = json["name"].toString();
    this->timezone = json["timezone"].toInt();
    this->visibility = json["visibility"].toInt();
    this->date = json["dt"].toInt();

    QJsonObject coord = json["coord"].toObject();
    this->coordinates.longitude = coord["lon"].toDouble();
    this->coordinates.latitude = coord["lat"].toDouble();

    QJsonArray weather = json["weather"].toArray();
    this->weatherDescription = weather.first()["main"].toString();

    QJsonObject main = json["main"].toObject();
    this->temp = main["temp"].toInt();
    this->pressure = main["pressure"].toInt();
    this->humidity = main["humidity"].toInt();
    this->seaLevel = main["sea_level"].toInt();

    QJsonObject wind = json["wind"].toObject();
    this->wind.speed = wind["speed"].toDouble();
    this->wind.gust= wind["gust"].toDouble();

    QJsonObject clouds = json["clouds"].toObject();
    this->clouds = clouds["all"].toInt();

    QJsonObject sys = json["sys"].toObject();
    this->sunrise = sys["sunrise"].toInt();
    this->sunset = sys["sunset"].toInt();
    this->country = sys["country"].toString();
}

QString WeatherData::getStrWeatherData() {
    return QString("Наименование точки: " + name + "\n" +
                   "Погода: "+ weatherDescription + "\n" +
                   "Страна: " +country + "\n" +
                   "Долгота: " + QString::number(coordinates.longitude) + "\n" +
                   "Широта: " +QString::number(coordinates.latitude)+ "\n" +
                   "Временная зона: " +QString::number(timezone)+ "\n" +
                   "Температура: " +QString::number(temp)+ "\n" +
                   "Давление: " +QString::number(pressure)+ "\n" +
                   "Влажность: " +QString::number(humidity)+ "\n" +
                   "Высота над уровнем моря: " +QString::number(seaLevel)+ "\n" +
                   "Видимость: " +QString::number(+visibility)+ "\n" +
                   "Скосроть ветра: "+QString::number(wind.speed) + "\n" +
                   "Порыв ветра: " +QString::number(wind.gust)+ "\n" +
                   "Облачность: " +QString::number(clouds)+ "\n" +
                   "Дата прогноза: " +QDateTime::fromSecsSinceEpoch(date).toString("yyyy/MM/dd hh:mm:ss")+ "\n" +
                   "Восход солнца: " +QDateTime::fromSecsSinceEpoch(sunrise).toString("yyyy/MM/dd hh:mm:ss")+ "\n" +
                   "Закат солнца: " +QDateTime::fromSecsSinceEpoch(sunset).toString("yyyy/MM/dd hh:mm:ss")+ "\n"
                   );
}

void WeatherData::printModel(){
    qDebug() << "Weather data for" << name;
    qDebug() << "weatherDescription" << weatherDescription;
    qDebug() << "country" << country;
    qDebug() << "Timezone:" << timezone;
    qDebug() << "Longitude:" << coordinates.longitude;
    qDebug() << "Latitude:" << coordinates.latitude;
    qDebug() << "Temp"<< temp;
    qDebug() << "pressure"<< pressure;
    qDebug() << "humidity"<< humidity;
    qDebug() << "seaLevel"<< seaLevel;
    qDebug() << "visibility"<< visibility;

    qDebug() << "wind.speed"<< wind.speed;
    qDebug() << "wind.gust"<< wind.gust;

    qDebug() << "sunrise"<< sunrise;
    qDebug() << "sunset"<< sunset;

    qDebug() << "clouds"<< clouds;
    qDebug() << "date"<< date;
}
