#ifndef WEATHERVIEWMODEL_H
#define WEATHERVIEWMODEL_H

#include <QObject>
#include <QFutureWatcher>
#include "presentation/weathermodel.h"
#include "domain/weatherdata.h"
#include "domain/getweatherusecase.h"

/**
 * Вьюмодель/Презентер/Контроллер экрана получения погодных данных
 */
class WeatherViewModel : public QObject
{
    Q_OBJECT
public:
    explicit WeatherViewModel(QObject *parent = nullptr);

    WeatherModel *getWeatherModel();

public slots:

    void updateWeatherData();

private:
    WeatherModel *weatherModel;
    QFutureWatcher<WeatherData*> watcher;
    GetWeatherUseCase getWeatherDataUseCase;

};

#endif // WEATHERVIEWMODEL_H
