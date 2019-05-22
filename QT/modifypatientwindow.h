#ifndef MODIFYPATIENTWINDOW_H
#define MODIFYPATIENTWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include "databasecontroller.h"

namespace Ui {

class ModifyPatientWindow;
}

class ModifyPatientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyPatientWindow(QWidget *parent = 0);
    ~ModifyPatientWindow();

     void  SendData(QString idPatient);
private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ModifyPatientWindow *ui;
    QStandardItemModel * modelPersonnelListView;
    DatabaseController dbc;
};

#endif // MODIFYPATIENTWINDOW_H
