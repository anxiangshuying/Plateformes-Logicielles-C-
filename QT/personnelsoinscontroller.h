#ifndef PERSONNELSOINSCONTROLLER_H
#define PERSONNELSOINSCONTROLLER_H
#include <QString>
#include "personnelsoinsmodel.h"
#include "databasecontroller.h"

PersonnelSoinsModel * JudgeAreaFormat(QString id,QString nom, QString prenom,QString type,
                             QString username, QString password,QString confirmPassword,
                             DatabaseController dbc,QString action);

void AddPersonnelSoins(PersonnelSoinsModel * perSoinsModel,DatabaseController dbc);
bool DeletePersonnelSoins(int idRessource,DatabaseController dbc);
void ModifyPersonnelSoins(PersonnelSoinsModel * perSoinsModel,DatabaseController dbc);
QStringList GetTypeList(DatabaseController dbc);
int SearchIdRessource(QModelIndex currentIndex);
QString Change_TypeID_To_TypeLabel(QString idType, DatabaseController dbc);
PersonnelSoinsModel GetPersonnelSoins(QString idRessource,DatabaseController dbc);

#endif // PERSONNELSOINSCONTROLLER_H
