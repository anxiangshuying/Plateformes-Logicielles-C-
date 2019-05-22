#include "mainwindow.h"
#include "addpatientwindow.h"
#include "addpersonnelsoinswindow.h"
#include "addradiologue.h"
#include "modifypatientwindow.h"
#include "modifypersonnelsoinswindow.h"
#include "aproposwindow.h"
#include "ui_mainwindow.h"
#include "personnelsoinscontroller.h"
#include "judgecontroller.h"
#include "patientcontroller.h"
#include <QMessageBox>
#include <QDebug>

int countInsert;

void MainWindow::LoadTreeViewHeader()
{

    modelPersonnelTreeView->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("LabelType/IdRessource")<<QStringLiteral("NomRessource"));
    ui->personnelTreeView->setColumnWidth(0,300);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(850,650);

    /*Set the title size of page "Afficher personnel de soins"*/
    QFont font;
    font.setPointSize(12);
    ui->listPersonnelLabel->setFont(font);

    /*Initialize the statusBar*/
    ui->statusBar->showMessage("Reussissez à vous connectez",60000);

    /*initialize the object of DatabaseController*/
    dbc = DatabaseController();

    /*Set the header of the personnel treeView in the pase "Afficher personnel de soins"*/
    modelPersonnelTreeView = new QStandardItemModel(ui->personnelTreeView);
    ui->personnelTreeView->setModel(modelPersonnelTreeView);
    LoadTreeViewHeader();

    /*Set the header of the patient tableView in the pase "Rechercher patient"*/
    ui->patientTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    modelPatientTableView = new QStandardItemModel(ui->patientTableView);
    ui->patientTableView->setModel(modelPatientTableView);
    modelPatientTableView->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("ID")<<QStringLiteral("Nom")<<QStringLiteral("Prenom")<<QStringLiteral("Date de RdV"));

    /*Set the header of the planification tableView in the pase "Planification"*/
    ui->personnelTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->patientTableView->setSortingEnabled(true);
    modelPlanificationTableView = new QStandardItemModel(ui->personnelTableView);
    ui->personnelTableView->setModel(modelPlanificationTableView);
    modelPlanificationTableView->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("ID")<<QStringLiteral("Nom")<<QStringLiteral("Prenom")<<QStringLiteral("Type De Permis"));

    ui->personnelTreeView->setEditTriggers(0);
    ui->patientTableView->setEditTriggers(0);
    ui->personnelTableView->setEditTriggers(0);

    ui->patientPrenomLineEdit->setText("son prenom");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete modelPersonnelTreeView;
    delete modelPatientTableView;
    delete modelPlanificationTableView;

}

/*Click "Fichier/Quitter" in the menuBar*/
void MainWindow::on_actionQuitter_triggered()
{
    close();
}

/*Click "Fichier/Ajouter/Patient" in the menuBar or in the toolBar for adding patient*/
void MainWindow::on_actionPatient_triggered()
{
    AddPatientWindow apw ;
    if(apw.exec()== QDialog::Accepted)
    {
        ui->statusBar->showMessage("Reussissez à ajouter un patient",60000);
    }
}

/*Click "Fichier/Ajouter/Personnel de soins" in the menuBar or in the toolBar for adding ressource*/
void MainWindow::on_actionPersonnel_de_soins_triggered()
{
    AddPersonnelSoinsWindow apsw;
    if(apsw.exec()==QDialog::Accepted)
    {
        modelPersonnelTreeView->clear();
        LoadTreeViewHeader();
        ShowPersonnelSoins(modelPersonnelTreeView,dbc);
        ui->statusBar->showMessage("Reussissez à ajouter une ressource",60000);
    }
}

/*Click "?/A propos" in the menuBar*/
void MainWindow::on_actionA_propos_triggered()
{
    AProposWindow pw;
    pw.exec();
}

/*Click button "Rechercher" in the page "Rechercher patient" for searching patients*/
void MainWindow::on_searchPatientButton_clicked()
{
    modelPatientTableView->clear();
    modelPatientTableView->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("ID")<<QStringLiteral("Nom")<<QStringLiteral("Prenom")<<QStringLiteral("Date de RdV"));
    SearchPatient(modelPatientTableView,dbc);
    ui->patientTableView->sortByColumn(2,Qt::AscendingOrder);
}

/*Click button "Load TreeView" in the page "Afficher personnel de soins" for Showing all ressource*/
void MainWindow::on_ViewButton_clicked()
{
    modelPersonnelTreeView->clear();
    LoadTreeViewHeader();
    ShowPersonnelSoins(modelPersonnelTreeView,dbc);
}

/*Click button "Supprimer" in the page "Afficher personnel de soins" for
 * deleting the ressource which the user choose in the TreeView*/
void MainWindow::on_deletePersonnelSoinsButton_clicked()
{
    /*If there is data in the treeView*/
    if(modelPersonnelTreeView->rowCount() !=0)
    {
        QModelIndex currentIndex = ui->personnelTreeView->currentIndex();
        /*If user has chosen a row*/
        if(currentIndex.parent().data().toString()!="")
        {
            int idRessource = SearchIdRessource(currentIndex);
            /*Delete the ressource that the user choose*/
            if(DeletePersonnelSoins(idRessource,dbc)==true)
            {
                modelPersonnelTreeView->clear();
                LoadTreeViewHeader();
                ShowPersonnelSoins(modelPersonnelTreeView,dbc);
                ui->statusBar->showMessage("Réussissez à supprimer une ressource",60000);
            }
        }
        else
        {
            QMessageBox::warning(NULL,"Error","Please choose a ressource at child level in the TreeView!",QMessageBox::Yes);
        }
    }
    else
    {
        QMessageBox::warning(NULL,"Error","Please load the tree view at first!",QMessageBox::Yes);
    }
}

/*Click button "Modifier" in the page "Afficher personnel de soins" for
 * modifying the ressource which the user choose in the TreeView*/
void MainWindow::on_modifyPersonnelSoinsButton_clicked()
{
    ModifyPersonnelSoinsWindow *mpsw = new ModifyPersonnelSoinsWindow();
    /*If there is data in the treeView*/
    if(modelPersonnelTreeView->rowCount() !=0)
    {
        QModelIndex currentIndex = ui->personnelTreeView->currentIndex();
        /*If user has chosen a row*/
        if(currentIndex.parent().data().toString()!="")
        {
            int idRessource = SearchIdRessource(currentIndex);

            /*Send id of the ressource that the user choose to the "modify" window*/
            mpsw->SendData(QString("%1").arg(idRessource));

            /*Open a new window for modifying*/
            if(mpsw->exec()==QDialog::Accepted)
            {
                modelPersonnelTreeView->clear();
                LoadTreeViewHeader();
                ShowPersonnelSoins(modelPersonnelTreeView,dbc);
                ui->statusBar->showMessage("Reussissez à modifier une ressource",60000);
            }
        }
        else
        {
            QMessageBox::warning(NULL,"Error","Please choose a ressource at child level in the TreeView!",QMessageBox::Yes);
        }
    }
    else
    {
        QMessageBox::warning(NULL,"Error","Please load the tree view at first!",QMessageBox::Yes);
    }
    delete mpsw;
}

/*Click button "Supprimer" in the page "Rechercher patient" for
 * deleting the patient which the user choose in the TableView*/
void MainWindow::on_deletePatientButton_clicked()
{
    /*If there is data in the treeView*/
    if(modelPatientTableView->rowCount() != 0)
    {
       int currentRow = ui->patientTableView->currentIndex().row();
       /*If user has chosen a row*/
       if(currentRow != -1)
       {
           QAbstractItemModel *abdModel = ui->patientTableView->model();
           int idPatient = SearchIdPatient(currentRow,abdModel);
           /*Delete the patient that the user choose*/
           if(DeletePatient(idPatient,dbc) == true)
           {
               modelPatientTableView->removeRow(currentRow);
               ui->statusBar->showMessage("Réussissez à supprimer un patient",60000);
           }
       }
       else
       {
           QMessageBox::warning(NULL,"Error","Please choose a patient in the TableView!",QMessageBox::Yes);
       }
    }
    else
    {
        QMessageBox::warning(NULL,"Error","Please search patients at first!",QMessageBox::Yes);
    }
}

/*Click button "Modifier" in the page "Rechercher patient" for
 * modifying the patient which the user choose in the TableView*/
void MainWindow::on_modifyPatientButton_clicked()
{
    ModifyPatientWindow *mpw = new ModifyPatientWindow();
    /*If there is data in the treeView*/
    if(modelPatientTableView->rowCount() != 0)
    {
       int currentRow = ui->patientTableView->currentIndex().row();
       /*If user has chosen a row*/
       if(currentRow != -1)
       {
           QAbstractItemModel *abdModel = ui->patientTableView->model();
           int idPatient = SearchIdPatient(currentRow,abdModel);

           /*Send id of the patient that the user choose to the "modify" window*/
           mpw->SendData(QString("%1").arg(idPatient));

           /*Open a new window for modifying*/
           if(mpw->exec()== QDialog::Accepted)
           {
               modelPatientTableView->clear();
               modelPatientTableView->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("ID")<<QStringLiteral("Nom")<<QStringLiteral("Prenom")<<QStringLiteral("Date de RdV"));
               SearchPatient(modelPatientTableView,dbc);
               ui->statusBar->showMessage("Reussissez à modifier un patient",60000);
           }
       }
       else
       {
           QMessageBox::warning(NULL,"Error","Please choose a patient in the TableView!",QMessageBox::Yes);
       }
    }
    else
    {
        QMessageBox::warning(NULL,"Error","Please search patients at first!",QMessageBox::Yes);
    }
    delete mpw;
}

/*Click button "Planifier" in the page "Planification" for search availible ressources
 * in the day the user choose*/
void MainWindow::on_planifierButton_clicked()
{
    modelPlanificationTableView->removeRows(0,modelPlanificationTableView->rowCount());
    if(Planifier(modelPlanificationTableView,dbc)==true)
    {
        ui->statusBar->showMessage("Reussissez à écrire la planification dans le fichier texte!",60000);
    }
}

void MainWindow::on_addRadiologueButton_2_clicked()
{
    AddRadiologue arw;
    if(arw.exec()==QDialog::Accepted)
    {
        modelPersonnelTreeView->clear();
        LoadTreeViewHeader();
        ShowPersonnelSoins(modelPersonnelTreeView,dbc);
        ui->statusBar->showMessage("Reussissez à ajouter un radiologue",60000);
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    qWarning()<<"Le nombre de requete \"Insert\": "<<countInsert;
}

void MainWindow::on_ExporterPatient_clicked()
{
    WriteToXML(dbc);
}
