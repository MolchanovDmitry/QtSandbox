#include "weatherdataparser.h"
#include <QJsonDocument>

WeatherDataParser::WeatherDataParser(QObject *parent)
    : QObject{parent}
{

}

WeatherData *WeatherDataParser::parse(QByteArray bytes){

    QString dataAsString = QString(bytes);

    WeatherData *weatherData = new WeatherData();
    QJsonDocument doc = QJsonDocument::fromJson(dataAsString.toUtf8());
    if (!doc.isNull()){
        weatherData->initFromJson(doc);
        weatherData->printModel();
    }

    return weatherData;
}
