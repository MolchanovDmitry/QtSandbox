#ifndef WEATHERMODEL_H
#define WEATHERMODEL_H

#include <QObject>

/**
 * Модель представления погодных данных
 */
class WeatherModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText CONSTANT WRITE setText NOTIFY textChanged)
public:
    explicit WeatherModel(QObject *parent = nullptr);

    const QString &getText() const;

public slots:
    void setText(QString text){
        if (this->text == text)
            return;
        this->text = text;
        emit textChanged(this->text);
    }
signals:
    void textChanged(QString text);

private:
    QString text;

};
#endif // WEATHERMODEL_H
