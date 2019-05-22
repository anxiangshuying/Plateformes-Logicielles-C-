#include "databasecontroller.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

DatabaseController::DatabaseController()
{
}

/*Connect to the database*/
void DatabaseController::ConnectDatabase()
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");

    db.setDatabaseName("base_tmp.sqli");
    db.open();
}

/*Select data from table "TCompte"*/
QSqlQuery DatabaseController::SelectCompte(QString attribute,QString constraint)
{
    QSqlQuery query;
    if(constraint == "Username")
    {
        QString username = attribute;
        query.exec("SELECT * FROM TCompte WHERE Login = '" + username + "';");
    }

    if(constraint == "IdRessource")
    {
        QString idRessource = attribute;
        query.exec("SELECT * FROM TCompte WHERE IdRessource = " + idRessource + ";");
    }

    if(constraint == "Max")
    {
        query.exec("SELECT Max(Id) FROM TConsult;");
    }

    return query;
}

/*Select data from table "TType"*/
QSqlQuery DatabaseController::SelectType(QString attribute, QString constraint)
{
    QSqlQuery query;

    if(constraint == "Id")
    {
        QString Id = attribute;
        query.exec("SELECT * FROM TType WHERE Id = " + Id + ";");
    }

    if(constraint == "Label")
    {
        QString label = attribute;
        query.exec("SELECT * FROM TType WHERE Label = '" + label + "';");
    }

    if(constraint == "All")
    {
        query.exec("SELECT * FROM TType;");
    }
    return query;
}

/*Select data from table "TRessource"*/
QSqlQuery DatabaseController::SelectRessource(QString attribute, QString constraint)
{
    QSqlQuery query;
    if(constraint == "Id")
    {
        QString id = attribute;
        query.exec("SELECT * FROM TRessource WHERE Id = " + id + ";");
    }

    if(constraint == "IdType")
    {
        QString type = attribute;
        query.exec("SELECT * FROM TRessource WHERE IdType = " + type + ";");
    }

    if(constraint == "All")
    {
        query.exec("SELECT * FROM TRessource;");
    }
    return query;
}

/*Select data from table "TPatient"*/
QSqlQuery DatabaseController::SelectPatient(QString id, QString nom, QString prenom,QString startDate, QString endDate,int radio,int condition)
{
    QSqlQuery query;

    if(radio == 1 && condition == 7)
    {
        query.exec("SELECT Id,Nom,Prenom,DateConsultation FROM TPatient WHERE Nom = '" + nom + "' AND Prenom = '" + prenom +"' AND DateConsultation BETWEEN '" + startDate +"' AND '" + endDate + "';");
    }

    if(radio == 1 && condition == 6)
    {
        query.exec("SELECT Id,Nom,Prenom,DateConsultation FROM TPatient WHERE Nom = '" + nom + "' AND Prenom = '" + prenom +"';");
    }

    if(radio == 1 && condition == 5)
    {
        query.exec("SELECT Id,Nom,Prenom,DateConsultation FROM TPatient WHERE Nom = '" + nom + "' AND DateConsultation BETWEEN '" + startDate +"' AND '" + endDate + "';");
    }

    if(radio == 1 && condition == 4)
    {
        query.exec("SELECT Id,Nom,Prenom,DateConsultation FROM TPatient WHERE Nom = '" + nom + "';");
    }

    if(radio == 1 && condition == 3)
    {
        query.exec("SELECT Id,Nom,Prenom,DateConsultation FROM TPatient WHERE Prenom = '" + prenom + "' AND DateConsultation BETWEEN '" + startDate +"' AND '" + endDate + "';");
    }

    if(radio == 1 && condition == 2)
    {
        query.exec("SELECT Id,Nom,Prenom,DateConsultation FROM TPatient WHERE Prenom = '" + prenom + "';");
    }

    if(radio == 1 && condition == 1)
    {
        query.exec("SELECT Id,Nom,Prenom,DateConsultation FROM TPatient WHERE DateConsultation BETWEEN '" + startDate +"' AND '" + endDate + "';");
    }

    if(radio == 2 && condition == 0)
    {
        query.exec("SELECT Id,Nom,Prenom,DateConsultation FROM TPatient WHERE Id = " + id + ";");
    }

    if(radio == 3 && condition == 0)
    {
        query.exec("SELECT * FROM TPatient WHERE Id = " + id + ";");
    }
    return query;
}

/*Select data from table "TConsult"*/
QSqlQuery DatabaseController::SelectConsult(QString attribute, QString constraint)
{
    QSqlQuery query;
    if(constraint == "Max")
    {
        query.exec("SELECT Max(Id) FROM TConsult;");
    }

    if(constraint == "IdPatient")
    {
        QString idPatient = attribute;
        query.exec("SELECT * FROM TConsult WHERE IdPatient = "+idPatient+";");
    }
    return query;
}

/*Insert data into table "TPatient"*/
void DatabaseController::InsertPatient(PatientModel *patModel)
{
    QSqlQuery query;
    QString remComt = patModel->GetCommentaire() +"\n" +patModel->GetRemarque();
    query.exec("INSERT INTO TPatient VALUES("+QString("%1").arg(patModel->GetId())+", '"+patModel->GetNom()+"', '"+patModel->GetPrenom()
               +"', '"+patModel->GetAdresse()+"', '"+patModel->GetVille()+"', "+QString("%1").arg(patModel->GetCodePostal())+", '"+ remComt
               +"', "+QString("%1").arg(patModel->GetTelephone())+", '"+patModel->GetDate().toString("yyyy-MM-dd")+"', "
               +QString("%1").arg(patModel->GetDuree())+", "+QString("%1").arg(patModel->GetPriorite())+");");
}

/*Insert data into table "TConsult"*/
void DatabaseController::InsertConsult(int id, PatientModel *patModel)
{
    QSqlQuery query;
    int idInsert=id;
    for(int i=0;i<patModel->GetIdRessource().size();i++)
    {
        query.exec("INSERT INTO TConsult VALUES("+QString("%1").arg(idInsert)+", "+QString("%1").arg(patModel->GetId())+" ,"+ QString("%1").arg(patModel->GetIdRessource().at(i))+");");
        idInsert++;
    }
}

/*Insert data into table "TRessource"*/
void DatabaseController::InsertRessource(PersonnelSoinsModel *perSoinsModel)
{
    QSqlQuery query;
    query.exec("INSERT INTO TRessource VALUES("+QString("%1").arg(perSoinsModel->GetId())+", '"+perSoinsModel->GetNom()+"', '"
               +perSoinsModel->GetPrenom()+"', "+QString("%1").arg(perSoinsModel->GetTypePermi())+");");
}

void DatabaseController::InsertCompte(int id, PersonnelSoinsModel *perSoinsModel)
{
    QSqlQuery query;
    query.exec("INSERT INTO TCompte VALUES("+QString("%1").arg(id)+", "+QString("%1").arg(perSoinsModel->GetId())+", '"
               +perSoinsModel->GetUsername()+"', '"+perSoinsModel->GetPassword()+"');");
}

/*Dlete data from table "TRessource"*/
void DatabaseController::DeleteRessource(int id)
{
    QSqlQuery query;
    query.exec("DELETE FROM TRessource WHERE Id = "+QString("%1").arg(id)+";");
}

/*Dlete data from table "TPatient"*/
void DatabaseController::DeletePatient(int id)
{
    QSqlQuery query;
    query.exec("DELETE FROM TPatient WHERE Id = "+QString("%1").arg(id)+";");
}

/*Dlete data from table "TConsult"*/
void DatabaseController::DeleteConsult(int attribute, QString constraint)
{
    QSqlQuery query;
    if(constraint == "IdPatient")
    {
        QString idPatient = QString("%1").arg(attribute);
        query.exec("DELETE FROM TConsult WHERE IdPatient = "+idPatient+";");
    }

    if(constraint == "IdRessource")
    {
        QString idRessource = QString("%1").arg(attribute);
        query.exec("DELETE FROM TConsult WHERE IdRessource= "+idRessource+";");
    }
}

/*Dlete data from table "TCompte"*/
void DatabaseController::DeleteCompte(QString attribute, QString constraint)
{
    QSqlQuery query;
    if(constraint == "IdRessource")
    {
        QString idRessource = attribute;
        query.exec("DELETE FROM TCompte WHERE IdRessource= "+idRessource+";");
    }
}

/*Update data of table "TPatient"*/
void DatabaseController::UpdatePatient(PatientModel *patModel)
{
    QSqlQuery query;
    query.exec("UPDATE TPatient SET Nom = '"+patModel->GetNom()+"', Prenom = '" +patModel->GetPrenom()+"', Adresse = '"+patModel->GetAdresse()
               +"', Ville = '"+patModel->GetVille()+"', CP = "+QString("%1").arg(patModel->GetCodePostal())+", Commentaire = '"+patModel->GetCommentaire()
               +"', Tel = "+QString("%1").arg(patModel->GetTelephone())+", DateConsultation = '"+patModel->GetDate().toString("yyyy-MM-dd")
               +"', DureeConsultation = "+QString("%1").arg(patModel->GetDuree())+", Priorite = "+QString("%1").arg(patModel->GetPriorite())
               +" WHERE ID = "+QString("%1").arg(patModel->GetId())+";");
}

/*Update data of table "TRessource"*/
void DatabaseController::UpdateRessource(PersonnelSoinsModel *perSoinsModel)
{
    QSqlQuery query;
    query.exec("UPDATE TRessource SET Nom = '"+perSoinsModel->GetNom()+"', Prenom = '" +perSoinsModel->GetPrenom()+"', IdType = "
               +QString("%1").arg(perSoinsModel->GetTypePermi())+" WHERE ID = "+QString("%1").arg(perSoinsModel->GetId())+";");
}

/*Update data of table "TCompte"*/
void DatabaseController::UpdateCompte(PersonnelSoinsModel *perSoinsModel)
{
    QSqlQuery query;
    query.exec("UPDATE TCompte SET Login = '"+perSoinsModel->GetUsername()+"', MdP = '"+perSoinsModel->GetPassword()+"' WHERE IdRessource ="
               +QString("%1").arg(perSoinsModel->GetId())+";");
}
