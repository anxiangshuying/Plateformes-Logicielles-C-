#include "addpatientwindow.h"
#include "patientmodel.h"
#include "ui_addpatientwindow.h"
#include "patientcontroller.h"
#include <QStandardItemModel>
#include <QDebug>

AddPatientWindow::AddPatientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPatientWindow)
{
    ui->setupUi(this);

    /*initialize the object of DatabaseController*/
    dbc = DatabaseController();

    modelPersonnelListView = new QStandardItemModel(ui->personnelListView);

    /*Set the title size*/
    QFont font;
    font.setPointSize(15);
    ui->addPatientLabel->setFont(font);

    /*Set the priority data to comboBox*/
    ui->priorityComboBox->addItem(QWidget::tr("5"));
    ui->priorityComboBox->addItem(QWidget::tr("4"));
    ui->priorityComboBox->addItem(QWidget::tr("3"));
    ui->priorityComboBox->addItem(QWidget::tr("2"));
    ui->priorityComboBox->addItem(QWidget::tr("1"));

    /*Set the default values to priority and duree*/
    ui->priorityComboBox->setCurrentText("1");
    ui->dureeEdit->setText("60");

    /*Load the ressource data to the TableView*/
    ui->personnelListView->setModel(LoadPersonnelSoinsList(modelPersonnelListView,dbc));
    ui->personnelListView->setEditTriggers(0);
}

AddPatientWindow::~AddPatientWindow()
{
    delete ui;
    delete modelPersonnelListView;
}

/*Click button "Ok" for adding a new patient*/
void AddPatientWindow::on_okButton_clicked()
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
                    ui->dureeEdit->text(),ui->telephoneEdit->text(),idRessource,ui->commentaireEdit->toPlainText(),dbc,"Add");

    patModel->SetRemarque(ui->remarqueLineEdit->text());
    /*Add a new patient into database*/
    if(patModel != NULL)
    {
        AddPatient(patModel,dbc);
        accept();
    }
    delete patModel;
}

/*Click button "Cancel" for closing the window without any operation*/
void AddPatientWindow::on_cancelButton_clicked()
{
    close();
}
