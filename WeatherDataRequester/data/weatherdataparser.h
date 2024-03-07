#ifndef WEATHERDATAPARSER_H
#define WEATHERDATAPARSER_H

#include <QObject>
#include "domain/weatherdata.h"

class WeatherDataParser : public QObject
{
    Q_OBJECT
public:
    explicit WeatherDataParser(QObject *parent = nullptr);

    static WeatherData *parse(QByteArray bytes);

signals:

};

#endif // WEATHERDATAPARSER_H
