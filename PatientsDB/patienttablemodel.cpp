#include "patienttablemodel.h"
#include <QDateTime>

static const int SURNAME_COLUMN = 0;
static const int BIRTHDAY_COLUMN = 1;
static const int AGE_COLUMN = 2;
static const int DAYS_IN_YEAR = 365;
static const QString RAW_DATE_FORMAT = "dd/MM/yyyy hh:mm:ss";
static const QString DISPLAY_DATE_FORMAT = "dd/MM/yyyy";

PatientTableModel::PatientTableModel(QObject *parent)
    : QSqlQueryModel(parent)
{
}

QVariant PatientTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case SURNAME_COLUMN: return "Фамилия";
        case BIRTHDAY_COLUMN: return "Дата рождения";
        case AGE_COLUMN: return "Возраст";
        }
    }

    return QSqlQueryModel::headerData(section, orientation, role);
}

QVariant PatientTableModel::data(const QModelIndex &index, int role) const
{
    QVariant value;

    if(role != Qt::DisplayRole ) {
        return QSqlQueryModel::data(index, role);
    }

    auto column = index.column();

    switch(column){
    case SURNAME_COLUMN : {
        value = QSqlQueryModel::data(index, role).toString().trimmed();
        break;
    }
    case BIRTHDAY_COLUMN : {
        auto birthdayStr = QSqlQueryModel::data(index, role).toString().trimmed();
        QDateTime dateTime = QDateTime::fromString(birthdayStr, RAW_DATE_FORMAT);
        value =  dateTime.toString(DISPLAY_DATE_FORMAT);
        break;
    }
    case AGE_COLUMN : {
        auto birthdayStr = QSqlQueryModel::data(index, role).toString().trimmed();
        QDateTime birthday = QDateTime::fromString(birthdayStr, RAW_DATE_FORMAT);
        QDateTime currentDateTime = QDateTime::currentDateTime();
        value = birthday.daysTo(currentDateTime) / DAYS_IN_YEAR;
        break;
    }
    }

    return value;
}
