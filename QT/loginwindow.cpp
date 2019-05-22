#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setFixedSize(400,300);

    /*Set the title size*/
    QFont font;
    font.setPointSize(20);
    ui->loginLabel->setFont(font);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


/*Click button "Connect* for connecting the system*/
void LoginWindow::on_connectButton_clicked()
{
    QString username;
    username = ui->usernameLineEdit->text();

    QString password;
    password = ui->passwordLineEdit->text();

    /*if the password corresponds to the username*/
    if(Identify(username,password) == true)
    {
        accept();
    }
    /*if the password doesn't corresponds to the username*/
    else
    {
        QMessageBox::warning(this,tr("Error"),tr("Incorrect username or password!"),QMessageBox::Yes);
        /*Clear the area of password*/
        ui->passwordLineEdit->clear();
    }
}

/*Click button "Cancel" for closing the window and exiting the system*/
void LoginWindow::on_cancelButton_clicked()
{
    close();
}
