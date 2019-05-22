#include "modifypersonnelsoinswindow.h"
#include "ui_modifypersonnelsoinswindow.h"
#include "personnelsoinscontroller.h"

ModifyPersonnelSoinsWindow::ModifyPersonnelSoinsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyPersonnelSoinsWindow)
{
    ui->setupUi(this);

    /*initialize the object of DatabaseController*/
    dbc = DatabaseController();

    /*Set the title size*/
    QFont font;
    font.setPointSize(15);
    ui->modifyPersonnelSoinsLabel->setFont(font);

    /*Set the type name to comboBox*/
    QStringList typeList = GetTypeList(dbc);
    for(int i=0;i<typeList.size();i++)
    {
        ui->typePermicomboBox->addItem(typeList.at(i));
    }

    /*Make the idEdit enable to be edited*/
    ui->idEdit->setEnabled(false);
}

ModifyPersonnelSoinsWindow::~ModifyPersonnelSoinsWindow()
{
    delete ui;
}

/*Receive the idRessource which is sent by the mainWindow and load the data to other EditControl according to this idRessource*/
void ModifyPersonnelSoinsWindow::SendData(QString idRessource)
{
    ui->idEdit->setText(idRessource);

    PersonnelSoinsModel perSoinsModel = GetPersonnelSoins(idRessource,dbc);
    QString labelType = Change_TypeID_To_TypeLabel(QString("%1").arg(perSoinsModel.GetTypePermi()), dbc);

    ui->nomEdit->setText(perSoinsModel.GetNom());
    ui->prenomEdit->setText(perSoinsModel.GetPrenom());
    ui->typePermicomboBox->setCurrentText(labelType);

    if(labelType == "Informaticien")
    {
        ui->usernameEdit->setText(perSoinsModel.GetUsername());
        ui->passwordEdit->setText(perSoinsModel.GetPassword());
        ui->confirmPasswordEdit->setText(perSoinsModel.GetPassword());
    }
}

/*Click button "Ok" for modifying the ressource that the user chooses*/
void ModifyPersonnelSoinsWindow::on_OkButton_clicked()
{
    PersonnelSoinsModel * perSoinsModel = new PersonnelSoinsModel();
    /*Judge if the formats of all areas are correct*/
    perSoinsModel = JudgeAreaFormat(ui->idEdit->text(),ui->nomEdit->text(),ui->prenomEdit->text(),ui->typePermicomboBox->currentText(),
                                    ui->usernameEdit->text(),ui->passwordEdit->text(),ui->confirmPasswordEdit->text(),dbc,"Modify");

    /*Update the chosen ressource in database*/
    if(perSoinsModel != NULL)
    {
        ModifyPersonnelSoins(perSoinsModel,dbc);
        accept();
    }
    delete perSoinsModel;
}

/*Click button "Annuler" for closing the window without any operation*/
void ModifyPersonnelSoinsWindow::on_cancelButton_clicked()
{
    close();
}
