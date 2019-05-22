#ifndef PATIENTCONTROLLER_H
#define PATIENTCONTROLLER_H

#include <QString>
#include <QStandardItemModel>
#include "patientmodel.h"
#include "databasecontroller.h"

PatientModel *JudgeAreaFormat(QString id,QString nom, QString prenom, QString adresse,
                             QString ville, QString codepostal, QString dateStr,
                             QString priority,QString duree, QString telephone,
                             QStringList idRessource,QString commentaire,
                              DatabaseController dbc, QString action);

void AddPatient(PatientModel * patModel,DatabaseController dbc);
bool DeletePatient(int idPatient,DatabaseController dbc);
void ModifyPatient(PatientModel * patModel,DatabaseController dbc);
QStandardItemModel *LoadPersonnelSoinsList(QStandardItemModel *model, DatabaseController dbc);
int SearchIdPatient(int currentRow,QAbstractItemModel *abdModel);
PatientModel GetPatient(QString idPatient,DatabaseController dbc);

#endif // PATIENTCONTROLLER_H
