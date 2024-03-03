#ifndef PATIENTINFOMODEL_H
#define PATIENTINFOMODEL_H

#include <QObject>

/**
 * Модель информации о выбранном пациенте
 */
class PatientInfoModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText CONSTANT WRITE setText NOTIFY textChanged)
public:
    explicit PatientInfoModel(QObject *parent = nullptr);

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

#endif // PATIENTINFOMODEL_H
