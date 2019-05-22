#ifndef ADDRADIOLOGUE_H
#define ADDRADIOLOGUE_H

#include <QDialog>
#include "databasecontroller.h"

namespace Ui {
class AddRadiologue;
}

class AddRadiologue : public QDialog
{
    Q_OBJECT

public:
    explicit AddRadiologue(QWidget *parent = 0);
    ~AddRadiologue();

private slots:
    void on_OkButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::AddRadiologue *ui;
    DatabaseController dbc;
};

#endif // ADDRADIOLOGUE_H
