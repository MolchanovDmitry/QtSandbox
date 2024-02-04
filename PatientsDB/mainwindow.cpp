#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QAction"
#include "QDebug"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlError"
#include "QtSql/QSqlQueryModel"
#include "QFileInfo"
#include <QFileDialog>
#include <QTableView>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QObject>
#include <QSqlQueryModel>
#include <QSqlRecord>

const static int MESSAGE_HIDE_DELAY_LONG = 4000;
const static int MESSAGE_HIDE_DELAY_SHORT = 2000;
const static QString appPatientsQuery = QString("SELECT NAME, BIRTHDAY FROM PATIENTS WHERE BIRTHDAY != \'\'");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QSqlQueryModel(this);

    ui->tableView->setModel(model);
    ui->tableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);

    QObject::connect(ui->tableView, &QTableView::clicked, this, &MainWindow::onTableClicked);

    on_open_db_triggered(); // TODO удалить

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_open_db_triggered()
{
    initUiWithDb("./../INTFETAL.sqlite");
}


void MainWindow::on_action_triggered()
{

    auto externalDbPath = QFileDialog::getOpenFileName(
                this,
                tr("Выберите базу данных с пациентами"),
                "file:///",
                tr("SQLite Database Files (*.sqlite)")
                );
    ui->statusbar->showMessage("Выбрана база данных " + externalDbPath, MESSAGE_HIDE_DELAY_SHORT);

    initUiWithDb(externalDbPath);

}

void MainWindow::initUiWithDb(QString dbPath){
    if(!QFileInfo::exists(dbPath)) {
        ui->statusbar->showMessage("При подключении к базе данных произошла ошибка: Отсутствует файл базы данных по пути " + dbPath);
        return;
    }

    auto dbConnect = QSqlDatabase::addDatabase("QSQLITE");
    dbConnect.setDatabaseName(dbPath);
    if(dbConnect.open()) {
        ui->statusbar->showMessage("Вы успешно подключились к базе данных " + dbConnect.databaseName(), MESSAGE_HIDE_DELAY_LONG);
    } else {
        ui->statusbar->showMessage("При подключении к базе данных произошла ошибка: " + dbConnect.lastError().databaseText(), MESSAGE_HIDE_DELAY_LONG);
    }

    model->setQuery(appPatientsQuery);
    model->setHeaderData(0, Qt::Orientation::Horizontal, QObject::tr("Имя"));
    model->setHeaderData(1, Qt::Orientation::Horizontal, QObject::tr("Дата рождения"));
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::onTableClicked(const QModelIndex &index) {

    if (index.isValid()) {

        auto record = model->record(index.row());
        auto patientName = record.value(0);

        qDebug()<<"Выбранный пациент: "<<patientName;
    } else {
        ui->statusbar->showMessage("Невалидный индекс", MESSAGE_HIDE_DELAY_LONG);
    }
}

