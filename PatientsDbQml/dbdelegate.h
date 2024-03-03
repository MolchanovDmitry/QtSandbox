#ifndef DBDELEGATE_H
#define DBDELEGATE_H

#include <QObject>
#include "patienttablemodel.h"
#include "researchtablemodel.h"
#include "patientinfomodel.h"

/**
 * Делегат работы с базой данных
 */
class DbDelegate : public QObject
{
    Q_OBJECT
public:
    explicit DbDelegate(QObject *parent = nullptr);

    PatientTableModel* patientsModel;
    ResearchTableModel* researchModel;
    PatientInfoModel* patientInfoModel;


public slots:
    void loadPatientByRowIndex(const int rowIndex);
    void openInternalDb();

private:
    void initDb(QString dbPath);
    void updatePatientInfo(const QSqlRecord &record);


signals:
};

#endif // DBDELEGATE_H
