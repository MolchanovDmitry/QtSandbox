#include "weathermodel.h"

WeatherModel::WeatherModel(QObject *parent)
    : QObject{parent}
{

}

const QString &WeatherModel::getText() const
{
    return text;
}
