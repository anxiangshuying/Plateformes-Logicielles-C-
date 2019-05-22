#ifndef MODIFYPERSONNELSOINSWINDOW_H
#define MODIFYPERSONNELSOINSWINDOW_H

#include <QDialog>
#include "databasecontroller.h"

namespace Ui {
class ModifyPersonnelSoinsWindow;
}

class ModifyPersonnelSoinsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyPersonnelSoinsWindow(QWidget *parent = 0);
    ~ModifyPersonnelSoinsWindow();

    void  SendData(QString idRessource);

private slots:
    void on_OkButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ModifyPersonnelSoinsWindow *ui;

    DatabaseController dbc;
};

#endif // MODIFYPERSONNELSOINSWINDOW_H
