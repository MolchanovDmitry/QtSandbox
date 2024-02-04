#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QAction"
#include "QDebug"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlError"
#include "QtSql/QSqlQueryModel"
#include "QFileInfo"
#include <QFileDialog>
#include <QTableWidget>
#include <QStandardItemModel>

const int MESSAGE_HIDE_DELAY_LONG = 4000;
const int MESSAGE_HIDE_DELAY_SHORT = 2000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QSqlQueryModel(this);

    ui->tableView->setModel(model);

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

    model->setQuery("SELECT * FROM patients");
    model->setHeaderData(0, Qt::Orientation::Horizontal, QObject::tr("Имя"));
    model->setHeaderData(1, Qt::Orientation::Horizontal, QObject::tr("Дата рождения"));
    ui->tableView->resizeColumnsToContents();
}

