#include "researchtablemodel.h"

static const int DOCTOR_COLUMN = 0;
static const int RESEARCH_COLUMN = 1;
static const int AGE_COLUMN = 2;
static const int DIAGNOSIS_COLUMN = 3;
static const int MEMO_COLUMN = 4;

ResearchTableModel::ResearchTableModel(QObject *parent)
    : QSqlQueryModel(parent)
{
}

QVariant ResearchTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case DOCTOR_COLUMN: return "Фамилия";
        case RESEARCH_COLUMN:  return "Дата рождения";
        case AGE_COLUMN: return "Возраст";
        case DIAGNOSIS_COLUMN: return "Диагноз";
        case MEMO_COLUMN: return "Назначениу";
        }
    }

    return QSqlQueryModel::headerData(section, orientation, role);
}
