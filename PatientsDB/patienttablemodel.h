#ifndef PATIENTTABLEMODEL_H
#define PATIENTTABLEMODEL_H

#include <QSqlQueryModel>

class PatientTableModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit PatientTableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // PATIENTTABLEMODEL_H
