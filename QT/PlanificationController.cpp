#include "mainwindow.h"
#include "addpatientwindow.h"
#include "ui_mainwindow.h"
#include "judgecontroller.h"
#include <QTreeView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

/*Search the availible ressources in the date that the user chooses*/
bool MainWindow::Planifier(QStandardItemModel *model, DatabaseController dbc)
{
    dbc.ConnectDatabase();
    QStringList dateList = ui->planificationDateEdit->text().split("/");
    /*Jadge if the date which the user chooses is >= the date of today*/
    if(JudgeDate(QDate(dateList.at(0).toInt(),dateList.at(1).toInt(),dateList.at(2).toInt())) == true)
    {
        QString date = ChangeDateFormat(ui->planificationDateEdit->text());

        /*Selete the patient whose consultation date is that the user chooses*/
        QSqlQuery queryPatient = dbc.SelectPatient(NULL,NULL,NULL,date,date,1,1);
        QSqlQuery queryRessource = dbc.SelectRessource(NULL,"All");
        QStringList strList;
        QStandardItem *item;
        int count=0;
        QString str="";

        /*If none of patient exists, it means all ressources are availible*/
        if(!queryPatient.next())
        {
             while(queryRessource.next())
             {
                 str = "";
                 for(int i=0;i<4;i++)
                 {
                     if(i==3)
                     {
                         QSqlQuery queryType = dbc.SelectType(queryRessource.value(3).toString(),"Id");
                         queryType.next();
                         item = new QStandardItem(queryType.value(1).toString());
                     }
                     else
                     {
                         item = new QStandardItem(queryRessource.value(i).toString());
                     }
                     model->setItem(count,i,item);
                     model->item(count,i)->setTextAlignment(Qt::AlignCenter);
                     str += queryRessource.value(i).toString()+"\t";
                 }
                 strList.push_back(str);
                 count++;
             }
        }
        /*If at least one patient exists*/
        else
        {
            QStringList idRessourceList;
            queryPatient.first();
            do
            {
                /*Selete idRessource from table TConsult according to idPatient*/
                QSqlQuery queryConsult = dbc.SelectConsult(queryPatient.value(0).toString(),"IdPatient");
                while(queryConsult.next())
                {
                    /*Find the ressources who will be consulted by patients*/
                    QList<QString>::iterator iterList = idRessourceList.begin();
                    bool find=false;
                    for(;iterList!=idRessourceList.end();iterList++)
                    {

                        if(*iterList == queryConsult.value(2).toString())
                        {
                            find=true;
                            break;
                        }
                    }
                    if(find==false)
                    {
                        idRessourceList.append(queryConsult.value(2).toString());
                    }
                }
            }while(queryPatient.next());

            while(queryRessource.next())
            {
                /*Delete ressources who will be consulted by patients from list of all ressources,
                 * the rest ressources are availible*/
                QList<QString>::iterator iterList = idRessourceList.begin();
                bool find=false;

                for(;iterList!=idRessourceList.end();iterList++)
                {
                    if(*iterList == queryRessource.value(0).toString())
                    {
                        find=true;
                        break;
                    }
                }
                if(find==false)
                {
                    str = "";
                    for(int i=0;i<4;i++)
                    {
                        if(i==3)
                        {
                            QSqlQuery queryType = dbc.SelectType(queryRessource.value(3).toString(),"Id");
                            queryType.next();
                            item = new QStandardItem(queryType.value(1).toString());
                        }
                        else
                        {
                            item = new QStandardItem(queryRessource.value(i).toString());
                        }
                        model->setItem(count,i,item);
                        model->item(count,i)->setTextAlignment(Qt::AlignCenter);
                        str += queryRessource.value(i).toString()+"\t";
                    }
                    strList.push_back(str);
                    count++;
                }
            }
        }
        /*Write the result to text file*/
        if(WriteToFile(strList,dbc)==true)
            return true;
        else
            return false;
    }
    else
    {
        QMessageBox::warning(this,tr("Error"),tr("The date you choose should be >= the date of today!"),QMessageBox::Yes);
        return false;
    }
}

/*Write the planification result to text file*/
bool MainWindow::WriteToFile(QStringList strList,DatabaseController dbc)
{
    dbc.ConnectDatabase();
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save File"),"../planification","Text files (*.txt)");
    QFile f(fileName);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream txtOutput(&f);

    for(int i=0;i<strList.size();i++)
    {
        QStringList itemList = strList.at(i).split("\t");
        for(int j=0;j<itemList.size();j++)
        {
            txtOutput<<itemList.at(j)<<" ";
        }
        txtOutput<<endl;
    }

    f.close();
    return true;
}
