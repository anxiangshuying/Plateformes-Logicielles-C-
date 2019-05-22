#ifndef ADDPATIENTWINDOW_H
#define ADDPATIENTWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include "databasecontroller.h"

namespace Ui {
class AddPatientWindow;
}

class AddPatientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddPatientWindow(QWidget *parent = 0);
    ~AddPatientWindow();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::AddPatientWindow *ui;
    QStandardItemModel * modelPersonnelListView;
    DatabaseController dbc;
};

#endif // ADDPATIENTWINDOW_H
