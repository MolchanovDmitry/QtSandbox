#ifndef RESEARCHTABLEMODEL_H
#define RESEARCHTABLEMODEL_H

#include <QSqlQueryModel>

class ResearchTableModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit ResearchTableModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
};

#endif // RESEARCHTABLEMODEL_H
