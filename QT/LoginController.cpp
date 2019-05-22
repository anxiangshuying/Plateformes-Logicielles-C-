#include "loginwindow.h"
#include "databasecontroller.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

/*Judge if the password corresponds to the username*/
bool LoginWindow::Identify(QString username, QString password)
{
    DatabaseController dbc = DatabaseController();
    dbc.ConnectDatabase();

    QSqlQuery query = dbc.SelectCompte(username,"Username");

    /*if the username doesn't exist*/
    if(!query.next())
        return false;
    else
    {
        /*if the password is not correct*/
        if(password != query.value(3).toString())
            return false;
        /*Both of the username and password are correct*/
        else
            return true;
    }
}

