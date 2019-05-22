#include "addpersonnelsoinswindow.h"
#include "ui_addpersonnelsoinswindow.h"
#include "personnelsoinsmodel.h"
#include "personnelsoinscontroller.h"

AddPersonnelSoinsWindow::AddPersonnelSoinsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPersonnelSoinsWindow)
{
    ui->setupUi(this);

    /*initialize the object of DatabaseController*/
    dbc = DatabaseController();

    /*Set the title size*/
    QFont font;
    font.setPointSize(15);
    ui->addPersonnelSoinsLabel->setFont(font);

    /*Set the type name to comboBox*/
    QStringList typeList = GetTypeList(dbc);
    for(int i=0;i<typeList.size();i++)
    {
        ui->typePermicomboBox->addItem(typeList.at(i));
    }
}

AddPersonnelSoinsWindow::~AddPersonnelSoinsWindow()
{
    delete ui;
}

/*Click button "Ok" for adding a new ressource*/
void AddPersonnelSoinsWindow::on_OkButton_clicked()
{
    /*Judge if the formats of all areas are correct*/
    PersonnelSoinsModel * perSoinsModel = new PersonnelSoinsModel();
    perSoinsModel = JudgeAreaFormat(ui->idEdit->text(),ui->nomEdit->text(),ui->prenomEdit->text(),ui->typePermicomboBox->currentText(),
                                    ui->usernameEdit->text(),ui->passwordEdit->text(),ui->confirmPasswordEdit->text(),dbc,"Add");

    /*Add a new ressource into database*/
    if(perSoinsModel != NULL)
    {
        AddPersonnelSoins(perSoinsModel,dbc);
        accept();
    }
    delete perSoinsModel;
}

/*Click button "Annuler" for closing the window without any operation*/
void AddPersonnelSoinsWindow::on_cancelButton_clicked()
{
    close();
}
