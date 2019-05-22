#include "modifypatientwindow.h"
#include "ui_modifypatientwindow.h"
#include <QSqlQuery>
#include "patientcontroller.h"

ModifyPatientWindow::ModifyPatientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyPatientWindow)
{
    ui->setupUi(this);

    /*initialize the object of DatabaseController*/
    dbc = DatabaseController();

    modelPersonnelListView = new QStandardItemModel(ui->personnelListView);

     /*Set the title size*/
    QFont font;
    font.setPointSize(15);
    ui->modifyPatientLabel->setFont(font);

    /*Set the priority data to comboBox*/
    ui->priorityComboBox->addItem(QWidget::tr("5"));
    ui->priorityComboBox->addItem(QWidget::tr("4"));
    ui->priorityComboBox->addItem(QWidget::tr("3"));
    ui->priorityComboBox->addItem(QWidget::tr("2"));
    ui->priorityComboBox->addItem(QWidget::tr("1"));

    /*Load the ressource data to the TableView*/
    ui->personnelListView->setModel(LoadPersonnelSoinsList(modelPersonnelListView,dbc));
    ui->personnelListView->setEditTriggers(0);

    /*Make the idEdit enable to be edited*/
    ui->IdEdit->setEnabled(false);
}

ModifyPatientWindow::~ModifyPatientWindow()
{
    delete ui;
    delete modelPersonnelListView;
}

/*Receive the idPatient which is sent by the mainWindow and load the data to other EditControl according to this idPatient*/
void ModifyPatientWindow::SendData(QString idPatient)
{
    ui->IdEdit->setText(idPatient);

    PatientModel patModel = GetPatient(idPatient, dbc);

    ui->nomEdit->setText(patModel.GetNom());
    ui->prenomEdit->setText(patModel.GetPrenom());
    ui->adresseEdit->setText(patModel.GetAdresse());
    ui->villeEdit->setText(patModel.GetVille());
    ui->codepostalEdit->setText(QString("%1").arg(patModel.GetCodePostal()));
    ui->commentaireEdit->setText(patModel.GetCommentaire());
    ui->telephoneEdit->setText(QString("%1").arg(patModel.GetTelephone()));
    ui->dateEdit->setDate(patModel.GetDate());
    ui->dureeEdit->setText(QString("%1").arg(patModel.GetDuree()));
    ui->priorityComboBox->setCurrentText(QString("%1").arg(patModel.GetPriorite()));
}

/*Click button "Ok" for modifying the patient that the user chooses*/
void ModifyPatientWindow::on_okButton_clicked()
{
     /*Get the multiple ressources which the user chooses from the ListView*/
    QStandardItemModel * model = qobject_cast<QStandardItemModel *>(ui->personnelListView->model());
    QModelIndexList modelIndexList = ui->personnelListView->selectionModel()->selectedIndexes();
    QStringList idRessource;
    foreach (QModelIndex modelIndex, modelIndexList)
    {
        QStringList idRes = model->data(modelIndex).toString().split("\t");
        idRessource.append(idRes.at(0));
    }

    /*Judge if the formats of all areas are correct*/
    PatientModel *patModel = new PatientModel();
    patModel = JudgeAreaFormat(ui->IdEdit->text(),ui->nomEdit->text(),ui->prenomEdit->text(),ui->adresseEdit->text(),
                    ui->villeEdit->text(),ui->codepostalEdit->text(),ui->dateEdit->text(),ui->priorityComboBox->currentText(),
                    ui->dureeEdit->text(),ui->telephoneEdit->text(),idRessource,ui->commentaireEdit->toPlainText(),dbc,"Modify");

    /*Update the chosen patient in database*/
    if(patModel != NULL)
    {
        ModifyPatient(patModel,dbc);
        accept();
    }
    delete patModel;
}

/*Click button "Annuler" for closing the window without any operation*/
void ModifyPatientWindow::on_cancelButton_clicked()
{
    close();
}
