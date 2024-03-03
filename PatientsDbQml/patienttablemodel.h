#ifndef PATIENTTABLEMODEL_H
#define PATIENTTABLEMODEL_H

#include <QSqlQueryModel>

/**
 * Модель таблицы пациентов
 */
class PatientTableModel : public QSqlQueryModel
{
    Q_OBJECT

public:

    explicit PatientTableModel(QObject *parent = nullptr);

    // Header:
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void onRowClick(const int rowIndex);

signals:
    void onRowSelected(const int rowIndex);


};
#endif // PATIENTTABLEMODEL_H
