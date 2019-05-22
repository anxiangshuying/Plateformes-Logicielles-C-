#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H
#include <QString>
#include <QSqlQuery>
#include "patientmodel.h"
#include "personnelsoinsmodel.h"

class DatabaseController
{
public:
    DatabaseController();

    void ConnectDatabase();
    QSqlQuery SelectCompte(QString attribute, QString constraint);
    QSqlQuery SelectType(QString attribute, QString constraint);
    QSqlQuery SelectRessource(QString attribute, QString constraint);
    QSqlQuery SelectPatient(QString id, QString nom, QString prenom,QString startDate, QString endDate,int radio,int condition);
    QSqlQuery SelectConsult(QString attribute, QString constraint);
    void InsertPatient(PatientModel * patModel);
    void InsertConsult(int id, PatientModel *patModel);
    void InsertRessource(PersonnelSoinsModel *perSoinsModel);
    void InsertCompte(int id,PersonnelSoinsModel *perSoinsModel);
    void DeleteRessource(int id);
    void DeletePatient(int id);
    void DeleteConsult(int attribute, QString constraint);
    void DeleteCompte(QString attribute,QString constraint);
    void UpdatePatient(PatientModel * patModel);
    void UpdateRessource(PersonnelSoinsModel *perSoinsModel);
    void UpdateCompte(PersonnelSoinsModel *perSoinsModel);

};

#endif // DATABASECONTROLLER_H
