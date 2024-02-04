#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "researchtablemodel.h"
#include "patienttablemodel.h"

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onTableClicked(const QModelIndex &index);

private slots:

    void on_open_db_triggered();

    void on_action_triggered();

    void initUiWithDb(QString path);

    void updatePatientLabel(const QSqlRecord &record);

    void showMessage(const QString &text, int timeout = 0);

private:

    PatientTableModel* patientsModel;
    ResearchTableModel* researchModel;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
