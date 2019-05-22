#ifndef ADDPERSONNELSOINSWINDOW_H
#define ADDPERSONNELSOINSWINDOW_H

#include <QDialog>
#include "databasecontroller.h"

namespace Ui {
class AddPersonnelSoinsWindow;
}

class AddPersonnelSoinsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddPersonnelSoinsWindow(QWidget *parent = 0);
    ~AddPersonnelSoinsWindow();

private slots:
    void on_OkButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::AddPersonnelSoinsWindow *ui;

    DatabaseController dbc;
};

#endif // ADDPERSONNELSOINSWINDOW_H
