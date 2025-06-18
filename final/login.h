#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
class Ui_Login;
QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QDialog
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_loginButton_clicked();
    void on_exitButton_clicked();
    void on_signupButton_clicked();

private:
    Ui::Login *ui;
};





#endif // LOGIN_H
