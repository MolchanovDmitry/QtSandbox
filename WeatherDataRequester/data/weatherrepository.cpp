#include "weatherrepository.h"
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>
#include <QThread>
#include "data/weatherdataparser.h"

const static QString url = "https://otestserver_1-1-o9142362.deta.app/weather";

WeatherRepository::WeatherRepository(QNetworkAccessManager *netMan,QObject *parent)
    : QObject{parent}
{
    this->netMan = netMan;
}

WeatherData *WeatherRepository::getWeatherDate() {

    qDebug()<< "Контекст репозитория: "<<QThread::currentThreadId();

    QNetworkRequest request(url);
    QNetworkReply *reply = netMan->get(request);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray responseData = reply->readAll();
    reply->deleteLater();

    return WeatherDataParser::parse(responseData);
}
