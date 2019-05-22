#include "addradiologue.h"
#include "ui_addradiologue.h"
#include "personnelsoinsmodel.h"
#include "personnelsoinscontroller.h"

AddRadiologue::AddRadiologue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRadiologue)
{
    ui->setupUi(this);

    /*initialize the object of DatabaseController*/
    dbc = DatabaseController();

    /*Set the title size*/
    QFont font;
    font.setPointSize(15);
    ui->addRadiologueLabel->setFont(font);

   ui->typePermicomboBox->addItem("Radiologue");
}

AddRadiologue::~AddRadiologue()
{
    delete ui;
}

void AddRadiologue::on_OkButton_clicked()
{
    /*Judge if the formats of all areas are correct*/
    PersonnelSoinsModel * perSoinsModel = new PersonnelSoinsModel();
    perSoinsModel = JudgeAreaFormat(ui->idEdit->text(),ui->nomEdit->text(),ui->prenomEdit->text(),ui->typePermicomboBox->currentText(),
                                    NULL,NULL,NULL,dbc,"Add");

    /*Add a new ressource into database*/
    if(perSoinsModel != NULL)
    {
        AddPersonnelSoins(perSoinsModel,dbc);
        accept();
    }
    delete perSoinsModel;
}

void AddRadiologue::on_cancelButton_clicked()
{
    close();
}
