#include "login.h"
#include "ui_login.h"
#include "home.h"
#include <QMessageBox>
#include "Authentication.h"
#include<memory.h>
#include<string>
#include"playermanager.h"
#include "codeverification.h"
#include"globals.h"
#include"sessiontimer.h"
using namespace std;
//PlayerManager *PLAYM =new PlayerManager("players.json");
//Authentication*AUTH =new Authentication();


 using TimePoint = std::chrono::system_clock::time_point;

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowTitle("Login");


}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    GAMEM->loadGames();
    PLAYM->loadPlayers();

    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();


    string * name  =nullptr;
    string hashedpasswordfromdb;
    bool ishere =false;

    AUTH->SignIn(username.toStdString(),password.toStdString());
    AUTH->PushSignedInData(name);//NAME POINT UN

    ishere=PLAYM->getStoredPasswordIfUserExists(*name,hashedpasswordfromdb);

    if(!ishere){
         QMessageBox::information(this, "waring", "no exsting account with this username!");
        return;
    }
    AUTH->IsHereConnect(hashedpasswordfromdb,ishere);

    if(AUTH->IsHereInterface()) {
        QMessageBox::information(this, "Success", "Login successful!");
          SessionTimer::instance().updateTimeout(6000);


        // If you have a home window
         Home *homeWindow = new Home();
         homeWindow->show();
         this->close();


        //  checkTimeLeft(homeWindow);

    } else {
        QMessageBox::warning(this, "Error", "Invalid  password!");

        ui->passwordLineEdit->clear();
    }

}

void Login::on_exitButton_clicked()
{
    this->close();
}

// Optional: Add signup functionality
void Login::on_signupButton_clicked()
{
    PLAYM->loadPlayers();
    QString name = ui->nameLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QString password = ui->newPasswordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();

    AUTH->SignUp(name.toStdString(),password.toStdString(),email.toStdString());

    if(!AUTH->FieldsIsValidNew()){
         QMessageBox::information(this, "WARING", "Some filed are empty, please chack it !");
        return;
    }

    if (!AUTH->UsernameIsValid()){
         QMessageBox::information(this, "WARING", "Useranme is short, please try longer one !");
         return;
    }
    if (PLAYM->playerExists(name.toStdString())){
        QMessageBox::information(this, "WARING", "Useranme is already taken ");
        return;
    }

    if(!AUTH->PasswordLongIsValid()){
         QMessageBox::information(this, "WARING", "Your password is short, please try longer one!");
        ui->passwordLineEdit->clear();
        ui->newPasswordLineEdit->clear();
         return;
    }
    if (password!=confirmPassword){

        QMessageBox::information(this, "WARING", "Not mached password !");
        return;
    }

    if(!AUTH->PasswordComplexityIsValid()){
        QMessageBox::information(this, "WARING", "password must contain an upper case, lower case, spcial charachter, numbers !");
        return;
    }

    if(!AUTH->EmailIsValid()){
        QMessageBox::information(this, "WARING", "Invalid email!");
     return;
    }
    //AUTH->VerificationMail();
    AUTH->VerificationMailSMTP();

    CodeVerification *codepage =new CodeVerification;
    codepage->show();

}
