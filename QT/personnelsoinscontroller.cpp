#include "mainwindow.h"
#include <QStandardItemModel>
#include "aproposwindow.h"
#include "ui_mainwindow.h"
#include "judgecontroller.h"
#include <QTreeView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

/*Get the list of all type name in the window "add personnel de soins"*/
QStringList GetTypeList(DatabaseController dbc)
{
    dbc.ConnectDatabase();
    QStringList typeList;
    QSqlQuery query = dbc.SelectType(NULL,"All");
    while(query.next())
    {
        typeList.append(query.value(1).toString());
    }
    return typeList;
}

/*Judge if all area formats are correct when the user adds of modifies a ressource*/
PersonnelSoinsModel *JudgeAreaFormat(QString id, QString nom, QString prenom, QString type,
                             QString username, QString password, QString confirmPassword,
                             DatabaseController dbc,QString action)
{
    dbc.ConnectDatabase();
    /*if all areas which are marked with "*" are not empty*/
    if(id!= NULL && nom!= NULL && prenom != NULL)
    {
        /*if the area "id" only contains some figures*/
        if(JudgeFigure(id) == true)
        {
            /*for the area "nom" and "premon", if their first character is majuscule letter
             * and the rest characters are either miniscule letter or a space*/
            if(JudgeCharacter(nom) == true && JudgeCharacter(prenom) == true)
            {
                PersonnelSoinsModel * perSoinsModel = new PersonnelSoinsModel();
                /*if the type of ressource is "Informaticien"*/
                if(type == "Informaticien")
                {
                    /*if the areas "username", "password", "condirm password" are not empty*/
                    if(username != NULL && password != NULL && confirmPassword !=NULL)
                    {
                        if(password == confirmPassword)
                        {
                            if(action == "Add")
                            {
                                QSqlQuery queryCompte = dbc.SelectCompte(username,"Username");
                                 /*if the username that the user inputs already exists in the database*/
                                if(!queryCompte.next())
                                {
                                    perSoinsModel->SetUsername(username);
                                    perSoinsModel->SetPassword(password);
                                }
                                else
                                {
                                    QMessageBox::warning(NULL,"Error","This username already exists!",QMessageBox::Yes);
                                    return NULL;
                                }
                            }
                            /*action == "Modify"*/
                            else
                            {
                                QSqlQuery queryCompteById = dbc.SelectCompte(id,"IdRessource");
                                queryCompteById.next();
                                /*if the user changes his username*/
                                if(queryCompteById.value(2).toString() != username)
                                {
                                    QSqlQuery queryCompteByUsername = dbc.SelectCompte(username,"Username");
                                    /*if the username that the user inputs already exists in the database*/
                                   if(!queryCompteByUsername.next())
                                   {
                                       perSoinsModel->SetUsername(username);
                                       perSoinsModel->SetPassword(password);
                                   }
                                   else
                                   {
                                       QMessageBox::warning(NULL,"Error","This username already exists!",QMessageBox::Yes);
                                       return NULL;
                                   }
                                }
                                /*if the username isn't changed*/
                                else
                                {
                                    perSoinsModel->SetUsername(username);
                                    perSoinsModel->SetPassword(password);
                                }
                            }
                        }
                        else
                        {
                            QMessageBox::warning(NULL,"Error","The two password are not correspondant!",QMessageBox::Yes);
                            return NULL;
                        }
                    }
                    else
                    {
                        QMessageBox::warning(NULL,"Error","The type you choose is \"Infomaticien\", please input the username and password!",QMessageBox::Yes);
                        return NULL;
                    }
                }
                /*If adding a new ressource, set the PersonnelSoinsB object for adding*/
                if(action == "Add")
                {
                    QSqlQuery queryRessource = dbc.SelectRessource(id,"Id");
                    if(!queryRessource.next())
                    {
                        QSqlQuery queryType = dbc.SelectType(type,"Label");
                        queryType.next();
                        perSoinsModel->SetId(id.toInt());
                        perSoinsModel->SetNom(nom);
                        perSoinsModel->SetPrenom(prenom);
                        perSoinsModel->SetTypePermi(queryType.value(0).toInt());

                        QMessageBox::information(NULL,"Information","Succeed in adding the ressource!",QMessageBox::Yes);
                        return perSoinsModel;
                    }
                    else
                    {
                        QMessageBox::warning(NULL,"Error","Can't add! The ressource with this id already exists!",QMessageBox::Yes);
                        return NULL;
                    }
                }
                /*If modifying the ressource,set the PersonnelSoinsB object for modifying*/
                else
                {
                    QSqlQuery queryType = dbc.SelectType(type,"Label");
                    queryType.next();
                    perSoinsModel->SetId(id.toInt());
                    perSoinsModel->SetNom(nom);
                    perSoinsModel->SetPrenom(prenom);
                    perSoinsModel->SetTypePermi(queryType.value(0).toInt());

                    QMessageBox::information(NULL,"Information","Succeed in modifying the ressource!",QMessageBox::Yes);
                    return perSoinsModel;
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
            QMessageBox::warning(NULL,"Error","The \"id\" can only contain figures!",QMessageBox::Yes);
            return NULL;
        }
    }
    else
    {
        QMessageBox::warning(NULL,"Error","All the areas which are marked by \"*\" shouldn't be empty!",QMessageBox::Yes);
        return NULL;
    }
}

/*Add a new ressource*/
void AddPersonnelSoins(PersonnelSoinsModel *perSoinsModel,DatabaseController dbc)
{
    dbc.ConnectDatabase();
    /*Insert into table TRessource*/
    dbc.InsertRessource(perSoinsModel);
    countInsert++;

    /*If the type is "Informaticien", insert into table TCompte*/
    if(perSoinsModel->GetTypePermi() == 7)
    {
        QSqlQuery query = dbc.SelectCompte(NULL,"Max");
        query.next();
        int compteId = query.value(0).toInt()+1;
        dbc.InsertCompte(compteId,perSoinsModel);
        countInsert++;
    }
}

/*Get current ressource id who is chosen by user in personnelSoisnTreeView*/
int SearchIdRessource(QModelIndex currentIndex)
{
    int idRessource=0;
    if(currentIndex.column() == 0)
    {
        idRessource = currentIndex.data().toInt();
    }
    else
    {
        idRessource = currentIndex.sibling(currentIndex.row(),0).data().toInt();
    }

    return idRessource;
}

/*Delete the ressource*/
bool DeletePersonnelSoins(int idRessource, DatabaseController dbc)
{
    dbc.ConnectDatabase();
    QSqlQuery query = dbc.SelectRessource(QString("%1").arg(idRessource),"Id");
    query.next();
    QMessageBox::StandardButton button = QMessageBox::information(NULL, "Confirm", "You will delete the ressource whose id="+QString("%1").arg(idRessource)+" and nom= "+query.value(1).toString()+".",
                                                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(button == QMessageBox::Yes)
    {
        dbc.DeleteRessource(idRessource);
        dbc.DeleteConsult(idRessource,"IdRessource");
        dbc.DeleteCompte(QString("%1").arg(idRessource),"IdRessource");
        return true;
    }
    else
        return false;
}

/*Modify the ressource*/
void ModifyPersonnelSoins(PersonnelSoinsModel *perSoinsModel,DatabaseController dbc)
{
    dbc.ConnectDatabase();
    /*Update table TRessource*/
    dbc.UpdateRessource(perSoinsModel);

    /*Update into table TCompte*/
    if(perSoinsModel->GetTypePermi() == 7)
    {
        dbc.UpdateCompte(perSoinsModel);
    }
}

/*Convert the type id into type label*/
QString Change_TypeID_To_TypeLabel(QString idType, DatabaseController dbc)
{
    dbc.ConnectDatabase();
    QSqlQuery queryType = dbc.SelectType(idType,"Id");
    queryType.next();
    QString labelType = queryType.value(1).toString();

    return labelType;
}

/*Get the personnelSoinsModel object*/
PersonnelSoinsModel GetPersonnelSoins(QString idRessource,DatabaseController dbc)
{
    dbc.ConnectDatabase();
    PersonnelSoinsModel perSoinsModel = PersonnelSoinsModel();

    QSqlQuery queryRessource = dbc.SelectRessource(idRessource,"Id");
    queryRessource.next();

    perSoinsModel.SetNom(queryRessource.value(1).toString());
    perSoinsModel.SetPrenom(queryRessource.value(2).toString());
    perSoinsModel.SetTypePermi(queryRessource.value(3).toInt());

    QString labelType = Change_TypeID_To_TypeLabel(queryRessource.value(3).toString(),dbc);
    if(labelType == "Informaticien")
    {
        QSqlQuery queryCompte = dbc.SelectCompte(queryRessource.value(0).toString(),"IdRessource");
        queryCompte.next();
        perSoinsModel.SetUsername(queryCompte.value(2).toString());
        perSoinsModel.SetPassword(queryCompte.value(3).toString());
    }

    return perSoinsModel;
}
