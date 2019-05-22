#include "mainwindow.h"
#include "loginwindow.h"
#include "c_init_bd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw;
    LoginWindow lw;

    mw.setWindowTitle("Gestion de RDV");
    C_INIT_BD bd;
    if(bd.Creation_BD()==true)
    {
        if(lw.exec()== QDialog::Accepted)
        {
            mw.show();
            return a.exec();
        }
    }
    return 0;
}
