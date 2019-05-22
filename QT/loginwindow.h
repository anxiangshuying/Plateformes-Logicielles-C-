#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_connectButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::LoginWindow *ui;
    bool Identify(QString username, QString password);
};

#endif // LOGINWINDOW_H
