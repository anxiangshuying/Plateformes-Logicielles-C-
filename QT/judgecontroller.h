#ifndef JUDGECONTROLLER_H
#define JUDGECONTROLLER_H
#include <QString>
#include <QDate>

/*Provide some founctions for judge the format of the character chain*/

bool JudgeFigure(QString str);
bool JudgeCharacter(QString str);
QString ChangeDateFormat(QString date);
bool JudgeDate(QDate date);

extern int countInsert;
#endif // JUDGECONTROLLER_H
