#include "personnelsoinsmodel.h"

PersonnelSoinsModel::PersonnelSoinsModel()
{
}

int PersonnelSoinsModel::GetId()
{
    return id;
}
void PersonnelSoinsModel::SetId(int id)
{
    this->id = id;
}

QString PersonnelSoinsModel::GetNom()
{
    return nom;
}
void PersonnelSoinsModel::SetNom(QString nom)
{
    this->nom = nom;
}

QString PersonnelSoinsModel::GetPrenom()
{
    return prenom;
}
void PersonnelSoinsModel::SetPrenom(QString prenom)
{
    this->prenom = prenom;
}

int PersonnelSoinsModel::GetTypePermi()
{
    return typePermi;
}
void PersonnelSoinsModel::SetTypePermi(int typePermi)
{
    this->typePermi = typePermi;
}

QString PersonnelSoinsModel::GetUsername()
{
    return username;
}
void PersonnelSoinsModel::SetUsername(QString username)
{
    this->username = username;
}

QString PersonnelSoinsModel::GetPassword()
{
    return password;
}
void PersonnelSoinsModel::SetPassword(QString password)
{
    this->password = password;
}
