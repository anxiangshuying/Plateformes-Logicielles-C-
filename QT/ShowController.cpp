#include "mainwindow.h"
#include "addpatientwindow.h"
#include "ui_mainwindow.h"
#include "judgecontroller.h"
#include <QTreeView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

/*Show all ressource in the TreeView in the page "Afficher personnel de soins*/
void MainWindow::ShowPersonnelSoins(QStandardItemModel * model,DatabaseController dbc)
{
    dbc.ConnectDatabase();
    QSqlQuery queryType = dbc.SelectType(NULL,"All");
    while(queryType.next())
    {
            QList<QStandardItem *> items;

            QStandardItem * item = new QStandardItem(queryType.value(1).toString());
            items.push_back(item);
            model->appendRow(items);

            QSqlQuery queryNom = dbc.SelectRessource(queryType.value(0).toString(),"IdType");

            while(queryNom.next())
            {
                QList<QStandardItem *> childItems;

                QStandardItem *item = new QStandardItem(queryNom.value(0).toString());
                childItems.push_back(item);
                 item = new QStandardItem(queryNom.value(1).toString());
                 childItems.push_back(item);
                items.at(0)->appendRow(childItems);
            }
    }
}

/*Show the patients which the user searche in the TableView in the page "Rechercher patient*/
bool AddToTableView(QStandardItemModel * model,QSqlQuery queryPatient)
{
    if(!queryPatient.next())
    {
        model->removeRows(0,model->rowCount());
        return false;
    }
    else
    {
        queryPatient.first();
        QStandardItem *item;
        int count=0;
        do
        {
            for(int i=0;i<4;i++)
            {
                item = new QStandardItem(queryPatient.value(i).toString());
                model->setItem(count,i,item);
                model->item(count,i)->setTextAlignment(Qt::AlignCenter);
            }
            count++;
        }while(queryPatient.next());
        return true;
    }
}

/*Search the patient in two ways, and it should meet at least one of this constraint*/
void MainWindow::SearchPatient(QStandardItemModel * model, DatabaseController dbc)
{
    dbc.ConnectDatabase();
    /*Search by nom or prenom or two dates*/
    if(ui->patientNomRadio->isChecked())
    {
        /*clean radioBox ID*/
        ui->patientIdLineEdit->setText("");

        QStringList startList = ui->rdvStartDateEdit->text().split("/");
        QStringList endList = ui->rdvEndDateEdit->text().split("/");
        int startDate = startList.at(0).toInt()*10000+startList.at(1).toInt()*100+startList.at(2).toInt();
        int endDate = endList.at(0).toInt()*10000+endList.at(1).toInt()*100+endList.at(2).toInt();

        /*if at least one area is not empty*/
        if(ui->patientNomLineEdit->text()!=NULL || ui->patientPrenomLineEdit->text()!=NULL ||
                (ui->rdvStartDateEdit->text()!="1900/1/1" && ui->rdvEndDateEdit->text()!="1900/1/1" && endDate>=startDate))
        {
            QString startDateFormat = ChangeDateFormat(ui->rdvStartDateEdit->text());
            QString endDateFormat = ChangeDateFormat(ui->rdvEndDateEdit->text());

            /*if the nom area is not empty*/
            if(ui->patientNomLineEdit->text()!=NULL)
            {
                if(JudgeCharacter(ui->patientNomLineEdit->text())==true)
                {
                    /*if the nom area is not empty and the prenom area is not empty*/
                    if(ui->patientPrenomLineEdit->text()!=NULL && ui->patientPrenomLineEdit->text() != "son prenom")
                    {
                        if(JudgeCharacter(ui->patientPrenomLineEdit->text())==true)
                        {
                            /*111*/
                            if(ui->rdvStartDateEdit->text()!="1900/1/1" && ui->rdvEndDateEdit->text()!="1900/1/1" && endDate>=startDate)
                            {
                                QSqlQuery queryPatient = dbc.SelectPatient(NULL,ui->patientNomLineEdit->text(),ui->patientPrenomLineEdit->text(),startDateFormat,endDateFormat,1,7);
                               bool find = AddToTableView(model,queryPatient);
                                if(!find)
                                {
                                    QMessageBox::warning(this,tr("Error"),tr("None of patient is found!"),QMessageBox::Yes);
                                }
                            }
                            /*110*/
                            else
                            {
                               if(endDate<startDate)
                                   QMessageBox::warning(this,tr("Error"),tr("The end date should be >= the start date!"),QMessageBox::Yes);
                               else
                               {
                                   QSqlQuery queryPatient = dbc.SelectPatient(NULL,ui->patientNomLineEdit->text(),ui->patientPrenomLineEdit->text(),NULL,NULL,1,6);
                                   bool find = AddToTableView(model,queryPatient);
                                   if(!find)
                                   {
                                       QMessageBox::warning(this,tr("Error"),tr("None of patient is found!"),QMessageBox::Yes);
                                   }
                               }
                            }
                        }
                        else
                        {
                            QMessageBox::warning(NULL,"Error","For \"nom\" and \"prenom\", the first letter should be majuscule, the rest letters should be miniscule!\nAttention: without any accent!",QMessageBox::Yes);
                        }
                    }
                    /*if the nom area is not empty  but the prenom area is empty*/
                    else
                    {
                        /*101*/
                        if(ui->rdvStartDateEdit->text()!="1900/1/1" && ui->rdvEndDateEdit->text()!="1900/1/1" && endDate>=startDate)
                        {
                            QSqlQuery queryPatient = dbc.SelectPatient(NULL,ui->patientNomLineEdit->text(),NULL,startDateFormat,endDateFormat,1,5);
                           bool find = AddToTableView(model,queryPatient);
                            if(!find)
                            {
                                QMessageBox::warning(this,tr("Error"),tr("None of patient is found!"),QMessageBox::Yes);
                            }
                        }
                        /*100*/
                        else
                        {
                           if(endDate<startDate)
                               QMessageBox::warning(this,tr("Error"),tr("The end date should be >= the start date!"),QMessageBox::Yes);
                           else
                           {
                               QSqlQuery queryPatient = dbc.SelectPatient(NULL,ui->patientNomLineEdit->text(),NULL,NULL,NULL,1,4);
                               bool find = AddToTableView(model,queryPatient);
                               if(!find)
                               {
                                   QMessageBox::warning(this,tr("Error"),tr("None of patient is found!"),QMessageBox::Yes);
                               }
                           }
                        }
                    }
                }
                else
                {
                    QMessageBox::warning(NULL,"Error","For \"nom\" and \"prenom\", the first letter should be majuscule, the rest letters should be miniscule!\nAttention: without any accent!",QMessageBox::Yes);
                }
            }
            /*if the nom area is empty*/
            else
            {
                /*if the nom area is empty but the prenom area is not empty*/
                if(ui->patientPrenomLineEdit->text()!=NULL && ui->patientPrenomLineEdit->text() != "son prenom")
                {
                    if(JudgeCharacter(ui->patientPrenomLineEdit->text())==true)
                    {
                        /*011*/
                        if(ui->rdvStartDateEdit->text()!="1900/1/1" && ui->rdvEndDateEdit->text()!="1900/1/1" && endDate>=startDate)
                        {
                            QSqlQuery queryPatient = dbc.SelectPatient(NULL,NULL,ui->patientPrenomLineEdit->text(),startDateFormat,endDateFormat,1,3);
                           bool find = AddToTableView(model,queryPatient);
                            if(!find)
                            {
                                QMessageBox::warning(this,tr("Error"),tr("None of patient is found!"),QMessageBox::Yes);
                            }
                        }
                        /*010*/
                        else
                        {
                            if(endDate<startDate)
                                QMessageBox::warning(this,tr("Error"),tr("The end date should be >= the start date!"),QMessageBox::Yes);
                            else
                            {
                                QSqlQuery queryPatient = dbc.SelectPatient(NULL,NULL,ui->patientPrenomLineEdit->text(),NULL,NULL,1,2);
                                bool find = AddToTableView(model,queryPatient);
                                if(!find)
                                {
                                    QMessageBox::warning(this,tr("Error"),tr("None of patient is found!"),QMessageBox::Yes);
                                }
                            }
                        }
                    }
                    else
                    {
                        QMessageBox::warning(NULL,"Error","For \"nom\" and \"prenom\", the first letter should be majuscule, the rest letters should be miniscule!\nAttention: without any accent!",QMessageBox::Yes);
                    }
                }
                /*if the nom area is empty and the prenom area is empty*/
                else
                {
                    /*001*/
                    if(ui->rdvStartDateEdit->text()!="1900/1/1" && ui->rdvEndDateEdit->text()!="1900/1/1" && endDate>=startDate)
                    {
                        QSqlQuery queryPatient = dbc.SelectPatient(NULL,NULL,NULL,startDateFormat,endDateFormat,1,1);
                       bool find = AddToTableView(model,queryPatient);
                        if(!find)
                        {
                            QMessageBox::warning(this,tr("Error"),tr("None of patient is found!"),QMessageBox::Yes);
                        }
                    }
                }
            }
        }
        /*000*/
        else
        {
            model->removeRows(0,model->rowCount());
            QMessageBox::warning(this,tr("Error"),tr("At least one area can't be empty, the dates can't be \"1900/1/1\", and the end date should be >= start date"),QMessageBox::Yes);
        }
    }

    /*Search by ID*/
    else
    {
        if(ui->patientIdRadio->isChecked())
        {
            /*clean radioBox Nom,Prenom and two dates*/
            ui->patientNomLineEdit->setText("");
            ui->patientPrenomLineEdit->setText("");
            ui->rdvStartDateEdit->setDate(QDate(1900,1,1));
            ui->rdvEndDateEdit->setDate(QDate(1900,1,1));

            if(ui->patientIdLineEdit->text() != NULL && JudgeFigure(ui->patientIdLineEdit->text()) == true)
            {
                QSqlQuery queryPatient = dbc.SelectPatient(ui->patientIdLineEdit->text(),NULL,NULL,NULL,NULL,2,0);
                bool find = AddToTableView(model,queryPatient);
                if(!find)
                {
                    QMessageBox::warning(this,tr("Error"),tr("The patient with this id doesn't exist!"),QMessageBox::Yes);
                }
            }
            else
            {
                model->removeRows(0,model->rowCount());
                QMessageBox::warning(this,tr("Error"),tr("The area \"ID\" can't be empty, and it can only contain figures!"),QMessageBox::Yes);
            }
        }

        else
        {
            QMessageBox::warning(this,tr("Error"),tr("Please choose a radioBox for searching!"),QMessageBox::Yes);
        }
    }
}
