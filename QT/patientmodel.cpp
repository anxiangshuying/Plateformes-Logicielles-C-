#include "patientmodel.h"

PatientModel::PatientModel()
{
}

int PatientModel::GetId()
{
    return id;
}
void PatientModel::SetId(int id)
{
    this->id = id;
}

QString PatientModel::GetNom()
{
    return nom;
}
void PatientModel::SetNom(QString nom)
{
    this->nom = nom;
}

QString PatientModel::GetPrenom()
{
    return prenom;
}
void PatientModel::SetPrenom(QString prenom)
{
    this->prenom = prenom;
}

QString PatientModel::GetAdresse()
{
    return adresse;
}
void PatientModel::SetAdresse(QString adresse)
{
    this->adresse = adresse;
}

QString PatientModel::GetVille()
{
    return ville;
}
void PatientModel::SetVille(QString ville)
{
    this->ville = ville;
}

int PatientModel::GetCodePostal()
{
    return codePostal;
}
void PatientModel::SetCodePostal(int codePostal)
{
    this->codePostal = codePostal;
}

QDate PatientModel::GetDate()
{
    return date;
}
void PatientModel::SetDate(QDate date)
{
    this->date = date;
}

int PatientModel::GetDuree()
{
    return duree;
}
void PatientModel::SetDuree(int duree)
{
    this->duree = duree;
}

int PatientModel::GetPriorite()
{
    return priorite;
}
void PatientModel::SetPriorite(int priorite)
{
    this->priorite = priorite;
}

QStringList PatientModel::GetIdRessource()
{
    return idRessource;
}
void PatientModel::SetIdRessource(QStringList idRessource)
{
    this->idRessource = idRessource;
}

int PatientModel::GetTelephone()
{
    return telephone;
}

void PatientModel::SetTelephone(int telephone)
{
    this->telephone = telephone;
}

QString PatientModel::GetCommentaire()
{
    return commentaire;
}

void PatientModel::SetCommentaire(QString commentaire)
{
    this->commentaire = commentaire;
}

QString PatientModel::GetRemarque()
{
    return  remarque;
}

void PatientModel::SetRemarque(QString remarque)
{
    this->remarque = remarque;
}
