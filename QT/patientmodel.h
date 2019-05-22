#ifndef PATIENTMODEL_H
#define PATIENTMODEL_H
#include <QString>
#include <QStringList>
#include <QDate>

class PatientModel
{
private:
    int id;
    QString nom;
    QString prenom;
    QString adresse;
    QString ville;
    int codePostal;
    QDate date;
    int duree;
    int priorite;
    QStringList idRessource;
    int telephone;
    QString commentaire;
    QString remarque;
public:
    PatientModel();

    int GetId();
    void SetId(int id);
    QString GetNom();
    void SetNom(QString nom);
    QString GetPrenom();
    void SetPrenom(QString prenom);
    QString GetAdresse();
    void SetAdresse(QString adresse);
    QString GetVille();
    void SetVille(QString ville);
    int GetCodePostal();
    void SetCodePostal(int codePostal);
    QDate GetDate();
    void SetDate(QDate date);
    int GetDuree();
    void SetDuree(int duree);
    int GetPriorite();
    void SetPriorite(int priorite);
    QStringList GetIdRessource();
    void SetIdRessource(QStringList idRessource);
    int GetTelephone();
    void SetTelephone(int telephone);
    QString GetCommentaire();
    void SetCommentaire(QString commentaire);
    QString GetRemarque();
    void SetRemarque(QString remarque);
};

#endif // PATIENTMODEL_H
