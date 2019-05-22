#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "databasecontroller.h"
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *e);

    void ShowPersonnelSoins(QStandardItemModel * model,DatabaseController dbc);
    void SearchPatient(QStandardItemModel * model,DatabaseController dbc);
    bool Planifier(QStandardItemModel * model,DatabaseController dbc);
    bool WriteToFile(QStringList strList, DatabaseController dbc);
    void LoadTreeViewHeader();
    bool WriteToXML(DatabaseController dbc);


private slots:
    void on_actionQuitter_triggered();

    void on_actionPatient_triggered();

    void on_actionPersonnel_de_soins_triggered();

    void on_actionA_propos_triggered();

    void on_searchPatientButton_clicked();

    void on_ViewButton_clicked();

    void on_deletePersonnelSoinsButton_clicked();

    void on_modifyPersonnelSoinsButton_clicked();

    void on_deletePatientButton_clicked();

    void on_modifyPatientButton_clicked();

    void on_planifierButton_clicked();

    void on_addRadiologueButton_2_clicked();

    void on_ExporterPatient_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel * modelPersonnelTreeView;
    QStandardItemModel * modelPatientTableView;
    QStandardItemModel * modelPlanificationTableView;
    DatabaseController dbc;
};

#endif // MAINWINDOW_H
