#ifndef PERSONNELSOINSMODEL_H
#define PERSONNELSOINSMODEL_H
#include <QString>

class PersonnelSoinsModel
{
private:
    int id;
    QString nom;
    QString prenom;
    int typePermi;
    QString username;
    QString password;
public:
    PersonnelSoinsModel();

    int GetId();
    void SetId(int id);
    QString GetNom();
    void SetNom(QString nom);
    QString GetPrenom();
    void SetPrenom(QString prenom);
    int GetTypePermi();
    void SetTypePermi(int typePermi);
    QString GetUsername();
    void SetUsername(QString username);
    QString GetPassword();
    void SetPassword(QString password);
};

#endif // PERSONNELSOINSMODEL_H
