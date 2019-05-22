#include "judgecontroller.h"
#include <QStringList>

/*Judge if all characters are figures*/
bool JudgeFigure(QString str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

/*Judge if the first character is a majuscule letter
 * and the rest characters are either miniscule letter or a space*/
bool JudgeCharacter(QString str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if(i==0)
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
            {
                continue;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if ((str[i] >= 'a' && str[i] <= 'z') || str[i] == ' ')
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

/*change 1900/1/1 to 1900-01-01 for Select*/
QString ChangeDateFormat(QString date)
{
    QStringList dateList = date.split("/");
    QString year = dateList.at(0);

    QString month;
    if(dateList.at(1).toInt()>0 && dateList.at(1).toInt() < 10)
        month = "0"+dateList.at(1);
    else
        month = dateList.at(1);

    QString day;
    if(dateList.at(2).toInt()>0 && dateList.at(2).toInt() < 10)
        day = "0"+dateList.at(2);
    else
        day = dateList.at(2);

    QString dateFormat = year+"-"+month+"-"+day;

    return dateFormat;
}

/*Jadge if the date which the user chooses is >= the date of today*/
bool JudgeDate(QDate date)
{
   QString chosenDateStr= date.toString("yyyy-MM-dd");
   QDate curDate = QDate::currentDate();
   QString currentDateStr = curDate.toString("yyyy-MM-dd");

   QStringList chosenDateList = chosenDateStr.split("-");
   QStringList currentDateList = currentDateStr.split("-");
   int chosenDate = chosenDateList.at(0).toInt()*10000+chosenDateList.at(1).toInt()*100+chosenDateList.at(2).toInt();
   int currentDate = currentDateList.at(0).toInt()*10000+currentDateList.at(1).toInt()*100+currentDateList.at(2).toInt();

   if(chosenDate < currentDate)
       return false;
   else
       return true;
}
