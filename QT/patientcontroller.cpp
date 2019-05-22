#include "mainwindow.h"
#include "aproposwindow.h"
#include "ui_mainwindow.h"
#include "judgecontroller.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDomDocument>

/*Load the ressource TableView in the window of "Add Patient"*/
QStandardItemModel *LoadPersonnelSoinsList(QStandardItemModel *model,DatabaseController dbc)
{
    dbc.ConnectDatabase();
    QSqlQuery queryRessource = dbc.SelectRessource(NULL,"All");
    QSqlQuery queryType;
    while(queryRessource.next())
    {

        queryType = dbc.SelectType(queryRessource.value(3).toString(),"Id");
        queryType.next();
        QStandardItem *item = new QStandardItem(queryRessource.value(0).toString()+"\t"+queryRessource.value(1).toString()+"  "+queryRessource.value(2).toString()+"\t\t"+queryType.value(1).toString());
        model->appendRow(item);
    }
    return model;
}


/*Judge if all area formats are correct when the user adds of modifies a patient*/
PatientModel * JudgeAreaFormat(QString id,QString nom, QString prenom, QString adresse,
                                              QString ville, QString codepostal, QString dateStr,
                                              QString priority,QString duree, QString telephone,
                                              QStringList idRessource,QString commentaire,
                                              DatabaseController dbc, QString action)
{
    dbc.ConnectDatabase();
    /*if all areas which are marked with "*" are not empty*/
    if(id!= NULL && nom!= NULL && prenom != NULL && adresse != NULL && ville != NULL
            && codepostal != NULL && duree != NULL && idRessource.size()>0)
    {
        /*if the area "id","code postal" and "duree" only contain some figures*/
        if(JudgeFigure(id) == true && JudgeFigure(QString("%1").arg(codepostal)) == true && JudgeFigure(QString("%1").arg(duree)))
        {
            /*for the area "nom","premon" and "ville", if their first character is majuscule letter
             * and the rest characters are either miniscule letter or a space*/
            if(JudgeCharacter(nom) == true && JudgeCharacter(prenom) == true && JudgeCharacter(ville)== true)
            {
                QStringList dateList = dateStr.split("/");
                QDate date = QDate(dateList.at(0).toInt(),dateList.at(1).toInt(),dateList.at(2).toInt());
                /*Jadge if the date which the user choose is >= the date of today*/
                if(JudgeDate(date) ==true)
                {
                    /*if the area "telephone" is not empty, it only contains some figures, otherwise, it is empty*/
                    if((telephone != NULL && JudgeFigure(QString("%1").arg(telephone)) == true) ||  telephone == NULL)
                    {
                        /*If adding a new patient*/
                        if(action == "Add")
                        {
                            QSqlQuery query = dbc.SelectPatient(id,NULL,NULL,NULL,NULL,2,0);
                            /*if the id that the user input doesn't exist in the database*/
                            if(!query.next())
                            {
                                QStringList adressStrList = adresse.split("'");

                                QString strAdresse = "";
                                for(int i=0;i<adressStrList.size();i++)
                                {
                                    if(i==adressStrList.size()-1)
                                        strAdresse +=adressStrList.at(i);
                                    else
                                        strAdresse +=adressStrList.at(i)+"'"+"'";
                                }

                                QString chosenDateStr= date.toString("yyyy-MM-dd");
                                QDate curDate = QDate::currentDate();
                                QString currentDateStr = curDate.toString("yyyy-MM-dd");

                                QStringList chosenDateList = chosenDateStr.split("-");
                                QStringList currentDateList = currentDateStr.split("-");
                                int chosenDate = chosenDateList.at(0).toInt()*10000+chosenDateList.at(1).toInt()*100+chosenDateList.at(2).toInt();
                                int currentDate = currentDateList.at(0).toInt()*10000+currentDateList.at(1).toInt()*100+currentDateList.at(2).toInt();
                                /* question 1 */
                             if((chosenDateList.at(1).toInt() != currentDateList.at(1).toInt() &&  chosenDate - currentDate  < 100 ) || (chosenDateList.at(1).toInt() == currentDateList.at(1).toInt() &&  chosenDate - currentDate  < 30 ))
                             {
                                PatientModel * patModel = new PatientModel();
                                patModel->SetId(id.toInt());
                                patModel->SetNom(nom);
                                patModel->SetPrenom(prenom);
                                patModel->SetAdresse(strAdresse);
                                patModel->SetVille(ville);
                                patModel->SetCodePostal(codepostal.toInt());
                                patModel->SetDate(date);
                                patModel->SetPriorite(priority.toInt());
                                patModel->SetDuree(duree.toInt());
                                patModel->SetTelephone(telephone.toInt());
                                patModel->SetIdRessource(idRessource);
                                patModel->SetCommentaire(commentaire);


                                QMessageBox::information(NULL,"Information","Succeed in adding the patient!",QMessageBox::Yes);

                                return patModel;
                                }
                             else
                             {
                                 QMessageBox::warning(NULL,"Error","Can't add! The date must < 30 of today !",QMessageBox::Yes);
                                 return NULL;
                             }

                            }
                            else
                            {
                                QMessageBox::warning(NULL,"Error","Can't add! The patient with this id already exist!",QMessageBox::Yes);
                                return NULL;
                            }
                        }
                        /*If modifying the patient*/
                        else
                        {
                            QStringList adressStrList = adresse.split("'");

                            QString strAdresse = "";
                            for(int i=0;i<adressStrList.size();i++)
                            {
                                if(i==adressStrList.size()-1)
                                    strAdresse +=adressStrList.at(i);
                                else
                                    strAdresse +=adressStrList.at(i)+"'"+"'";
                            }
                            QString chosenDateStr= date.toString("yyyy-MM-dd");
                            QDate curDate = QDate::currentDate();
                            QString currentDateStr = curDate.toString("yyyy-MM-dd");

                            QStringList chosenDateList = chosenDateStr.split("-");
                            QStringList currentDateList = currentDateStr.split("-");
                            int chosenDate = chosenDateList.at(0).toInt()*10000+chosenDateList.at(1).toInt()*100+chosenDateList.at(2).toInt();
                            int currentDate = currentDateList.at(0).toInt()*10000+currentDateList.at(1).toInt()*100+currentDateList.at(2).toInt();


                            /* question 1 */
                         if((chosenDateList.at(1).toInt() != currentDateList.at(1).toInt() &&  chosenDate - currentDate  < 100 ) || (chosenDateList.at(1).toInt() == currentDateList.at(1).toInt() &&  chosenDate - currentDate  < 30 ))
                         {


                            PatientModel * patModel = new PatientModel();
                            patModel->SetId(id.toInt());
                            patModel->SetNom(nom);
                            patModel->SetPrenom(prenom);
                            patModel->SetAdresse(strAdresse);
                            patModel->SetVille(ville);
                            patModel->SetCodePostal(codepostal.toInt());
                            patModel->SetDate(date);
                            patModel->SetPriorite(priority.toInt());
                            patModel->SetDuree(duree.toInt());
                            patModel->SetTelephone(telephone.toInt());
                            patModel->SetIdRessource(idRessource);
                            patModel->SetCommentaire(commentaire);

                            QMessageBox::information(NULL,"Information","Succeed in modifying the patient!",QMessageBox::Yes);

                            return patModel;
                         }
                      else
                      {
                          QMessageBox::warning(NULL,"Error","Can't add! The date must < 30 of today !",QMessageBox::Yes);
                          return NULL;
                      }

                        }
                    }
                    else
                    {
                        QMessageBox::warning(NULL,"Error","The \"telephone\" can only contain figures!",QMessageBox::Yes);
                        return NULL;
                    }
                }
                else
                {
                    QMessageBox::warning(NULL,"Error","The date which you choose should be >= today!",QMessageBox::Yes);
                    return NULL;
                }
            }
            else
            {
                QMessageBox::warning(NULL,"Error","For \"nom\" and \"prenom\", the first letter should be majuscule, the rest letters should be miniscule!\nAttention: without any accent!",QMessageBox::Yes);
                return NULL;
            }
        }
        else
        {
            QMessageBox::warning(NULL,"Error","The \"id\",\"code postal\" and \"duree\" can only contain figures!",QMessageBox::Yes);
            return NULL;
        }
    }
    else
    {
       QMessageBox::warning(NULL,"Error","All the areas which are marked by \"*\" shouldn't be empty!",QMessageBox::Yes);
       return NULL;
    }
}

/*Add a new patient*/
void AddPatient(PatientModel * patModel, DatabaseController dbc)
{
    dbc.ConnectDatabase();

    /*Insert into table TPatient*/
    dbc.InsertPatient(patModel);
    countInsert++;

    /*Insert into table TConsult*/
    QSqlQuery query = dbc.SelectConsult(NULL,"Max");
    query.next();
    int consultId = query.value(0).toInt()+1;
    dbc.InsertConsult(consultId,patModel);
    countInsert++;
}

/*Get current patient id who is chosen by user in patientTableView*/
int SearchIdPatient(int currentRow,QAbstractItemModel *abdModel)
{
    QModelIndex index = abdModel->index(currentRow,0);
    int idPatient = abdModel->data(index).toInt();

    return idPatient;
}

/*Delete the chosen patient*/
bool DeletePatient(int idPatient,DatabaseController dbc)
{
    dbc.ConnectDatabase();
    QSqlQuery query = dbc.SelectPatient(QString("%1").arg(idPatient),NULL,NULL,NULL,NULL,2,0);
    query.next();
    QMessageBox::StandardButton button = QMessageBox::information(NULL, "Confirm", "You will delete the ressource whose id="+QString("%1").arg(idPatient)+" and nom= "+query.value(1).toString()+".",
                                                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(button == QMessageBox::Yes)
    {
        dbc.DeletePatient(idPatient);
        dbc.DeleteConsult(idPatient,"IdPatient");
        return true;
    }
    else
        return false;
}

/*Modify the chosen patient*/
void ModifyPatient(PatientModel * patModel, DatabaseController dbc)
{
    dbc.ConnectDatabase();
    /*Update table TPatient*/
    dbc.UpdatePatient(patModel);

    /*Update table TConsult, delete and re-add*/
    dbc.DeleteConsult(patModel->GetId(),"IdPatient");
    QSqlQuery query = dbc.SelectConsult(NULL,"Max");
    query.next();
    int consultId = query.value(0).toInt()+1;
    dbc.InsertConsult(consultId,patModel);
}

/*Get a PatientModel object*/
PatientModel GetPatient(QString idPatient, DatabaseController dbc)
{
    dbc.ConnectDatabase();
    QSqlQuery query = dbc.SelectPatient(idPatient,NULL,NULL,NULL,NULL,3,0);
    query.next();

    QStringList dateList = query.value(8).toString().split("-");

    PatientModel patModel = PatientModel();

    patModel.SetId(query.value(0).toInt());
    patModel.SetNom(query.value(1).toString());
    patModel.SetPrenom(query.value(2).toString());
    patModel.SetAdresse(query.value(3).toString());
    patModel.SetVille(query.value(4).toString());
    patModel.SetCodePostal(query.value(5).toInt());
    patModel.SetCommentaire(query.value(6).toString());
    patModel.SetTelephone(query.value(7).toInt());
    patModel.SetDate(QDate(dateList.at(0).toInt(),dateList.at(1).toInt(),dateList.at(2).toInt()));
    patModel.SetDuree(query.value(9).toInt());
    patModel.SetPriorite(query.value(10).toInt());

    return patModel;
}

/*Write the patient result to xml file*/
bool MainWindow::WriteToXML(DatabaseController dbc)
{
    dbc.ConnectDatabase();
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save File"),"../TRessrource","XML files (*.xml)");
    QFile f(fileName);
    if(!f.open(QIODevice::WriteOnly|QIODevice::Truncate));
    QDomDocument doc;

    QDomElement root=doc.createElement(tr("TRessource"));
    doc.appendChild(root);
    QDomElement IdRessource=doc.createElement(tr("IdRessource"));
    QDomElement NomRessource=doc.createElement(tr("Nom"));
    QDomElement PrenomRessource=doc.createElement(tr("Prenom"));
    QDomText text;

    f.close();
    return true;
}
