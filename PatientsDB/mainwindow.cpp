#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QAction"
#include "QDebug"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlError"
#include "QtSql/QSqlQueryModel"
#include "QFileInfo"
#include "researchtablemodel.h"
#include <QFileDialog>
#include <QTableView>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QObject>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>

const static int MESSAGE_HIDE_DELAY_SHORT = 2000;
const static int MESSAGE_HIDE_DELAY_LONG = 4000;

const static QString PATIENT_NAME_ARG = ":patient_name";

const static QString allPatientsQuery = QString("SELECT NAME, BIRTHDAY, BIRTHDAY "
                                                "FROM PATIENTS "
                                                "WHERE BIRTHDAY != \'\'");

const static QString researchQuery = QString("SELECT r.DOCTOR, r.RES_DATE, r.AGE, r.DIAG, r.MEMO "
                                             "FROM ( SELECT * FROM RESEARCH WHERE trim(lower(PATIENT)) == trim(lower(%1)) ) as r "
                                             "LEFT JOIN PATIENTS AS p "
                                             "ON trim(lower(p.name)) == trim(lower(r.PATIENT));").arg(PATIENT_NAME_ARG);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    patientsModel = new PatientTableModel(this);
    ui->patientTableView->setModel(patientsModel);
    ui->patientTableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);

    researchModel = new ResearchTableModel(this);
    ui->researchTableView->setModel(researchModel);

    QObject::connect(ui->patientTableView, &QTableView::clicked, this, &MainWindow::onTableClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_open_db_triggered()
{
    initUiWithDb("./INTFETAL.sqlite");
}


void MainWindow::on_action_triggered()
{

    auto externalDbPath = QFileDialog::getOpenFileName(
                this,
                tr("Выберите базу данных с пациентами"),
                "file:///",
                tr("SQLite Database Files (*.sqlite)")
                );
    showMessage("Выбрана база данных " + externalDbPath, MESSAGE_HIDE_DELAY_SHORT);

    initUiWithDb(externalDbPath);

}

void MainWindow::initUiWithDb(QString dbPath){
    if(!QFileInfo::exists(dbPath)) {
        showMessage("При подключении к базе данных произошла ошибка: Отсутствует файл базы данных по пути "
                    + dbPath);
        return;
    }

    auto dbConnect = QSqlDatabase::addDatabase("QSQLITE");
    dbConnect.setDatabaseName(dbPath);
    if(dbConnect.open()) {
        showMessage("Вы успешно подключились к базе данных "
                    + dbConnect.databaseName(), MESSAGE_HIDE_DELAY_LONG);
    } else {
        showMessage("При подключении к базе данных произошла ошибка: "
                    + dbConnect.lastError().databaseText(), MESSAGE_HIDE_DELAY_LONG);
    }

    patientsModel->setQuery(allPatientsQuery);
    ui->patientTableView->resizeColumnsToContents();
}

void MainWindow::onTableClicked(const QModelIndex &index) {
    if (index.isValid()) {

        auto record = patientsModel->record(index.row());
        auto patientName = record.value(0);

        QSqlQuery query;
        query.prepare(researchQuery);
        query.bindValue(PATIENT_NAME_ARG, patientName.toString());
        query.exec();

        researchModel->setQuery(query);
        ui->researchTableView->resizeColumnsToContents();

        updatePatientLabel(record);

    } else {
        showMessage("Невалидный индекс", MESSAGE_HIDE_DELAY_LONG);
    }
}

void MainWindow::updatePatientLabel(const QSqlRecord &record) {
    auto researchCount = researchModel->rowCount();
    auto patientName = record.value(0).toString();
    auto patientBirthday = record.value(1).toString();
    auto totalInfo = QString("Фамилия: %1\n"
                             "Дата рождения: %2\n"
                             "Количество проведенных исследований: %3"
                            )
            .arg(patientName)
            .arg(patientName)
            .arg(researchCount);
    ui->patientInfo->setText(totalInfo);
}

void MainWindow::showMessage(const QString &text, int timeout ){
    ui->statusbar->showMessage(text, timeout);
}
