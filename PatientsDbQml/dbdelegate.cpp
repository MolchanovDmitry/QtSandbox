#include "dbdelegate.h"
#include <QFileInfo>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>


const static QString PATIENT_NAME_ARG = ":patient_name";

const static QString allPatientsQuery = QString("SELECT NAME, BIRTHDAY, BIRTHDAY "
                                                "FROM PATIENTS "
                                                "WHERE BIRTHDAY != \'\'");

const static QString researchQuery = QString("SELECT r.DOCTOR, r.RES_DATE, r.AGE, r.DIAG, r.MEMO "
                                             "FROM ( SELECT * FROM RESEARCH WHERE trim(lower(PATIENT)) == trim(lower(%1)) ) as r "
                                             "LEFT JOIN PATIENTS AS p "
                                             "ON trim(lower(p.name)) == trim(lower(r.PATIENT));").arg(PATIENT_NAME_ARG);

DbDelegate::DbDelegate(QObject *parent)
    : QObject{parent}
{
    patientsModel = new PatientTableModel(this);
    researchModel = new ResearchTableModel(this);
    patientInfoModel = new PatientInfoModel(this);
}

void DbDelegate::openInternalDb(){
    initDb("./INTFETAL.sqlite");
}

void DbDelegate::initDb(QString dbPath){
    if(!QFileInfo::exists(dbPath)) {
        qDebug()<<"При подключении к базе данных произошла ошибка";
        //showMessage("При подключении к базе данных произошла ошибка: Отсутствует файл базы данных по пути "
        //            + dbPath);
        return;
    }

    auto dbConnect = QSqlDatabase::addDatabase("QSQLITE");
    dbConnect.setDatabaseName(dbPath);
    if(dbConnect.open()) {
        qDebug()<<"Вы успешно подключились к базе данных";
        //showMessage("Вы успешно подключились к базе данных "
        //            + dbConnect.databaseName(), MESSAGE_HIDE_DELAY_LONG);
    } else {
        qDebug()<<"При подключении к базе данных произошла ошибка";
        //showMessage("При подключении к базе данных произошла ошибка: "
        //            + dbConnect.lastError().databaseText(), MESSAGE_HIDE_DELAY_LONG);
    }

    patientsModel->setQuery(allPatientsQuery);
}

void DbDelegate::loadPatientByRowIndex(const int rowIndex){
    qDebug()<<"Загрузить данные о пациенте с индексом "<<rowIndex;
    auto record = patientsModel->record(rowIndex);
    auto patientName = record.value(0);

    QSqlQuery query;
    query.prepare(researchQuery);
    query.bindValue(PATIENT_NAME_ARG, patientName.toString());
    query.exec();

    researchModel->setQuery(query);
    updatePatientInfo(record);
}

void DbDelegate::updatePatientInfo(const QSqlRecord &record) {
    auto researchCount = researchModel->rowCount();
    auto patientName = record.value(0).toString();
    auto patientBirthday = record.value(1).toString();
    auto totalInfo = QString("Фамилия: %1\n"
                             "Дата рождения: %2\n"
                             "Количество проведенных исследований: %3"
                            )
            .arg(patientName)
            .arg(patientBirthday)
            .arg(researchCount);

    patientInfoModel->setText(totalInfo);
}

