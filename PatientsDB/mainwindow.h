#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updatePatientLabel(const QSqlRecord &record);

public slots:
    void onTableClicked(const QModelIndex &index);

private slots:

    void on_open_db_triggered();

    void on_action_triggered();

    void initUiWithDb(QString path);

private:

    QSqlQueryModel* patientsModel;
    QSqlQueryModel* researchModel;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H