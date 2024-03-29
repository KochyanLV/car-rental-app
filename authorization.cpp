#include "authorization.h"
#include "ui_authorization.h"
#include "appwindow.h"
#include "registration.h"
#pragma execution_character_set("utf-8")
int userId = 0;
int getId(){return userId;}
void setId(int id){userId=id;}

authorization::authorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorization){

    ui->setupUi(this);

    QSqlDatabase mydb;
    mydb = QSqlDatabase::addDatabase("QSQLITE");

    mydb.setDatabaseName("./carrent.db");
    mydb.open();
}

authorization::~authorization(){ delete ui;}

void authorization::on_CreateBtn_clicked(){
    hide();
    Registration RegForm;
    RegForm.setModal(true);
    RegForm.exec();
}

void authorization::on_SingInBtn_clicked(){
    QString username, password;
       username = ui->UserInput->text(); // get the login name from the login edit field
       password = ui->PasswdInput->text(); // get the password from the password edit field
       QSqlQuery query;
       query.prepare("SELECT id FROM usersdata WHERE username = :username AND password = :password");
       query.bindValue(":username", username); // bind the login name to the query
       query.bindValue(":password", password); // bind the password to the query
       if (!query.exec()) {
           qFatal("Query failed: %s", qPrintable(query.lastError().text()));
       }
       if (query.next()) {
           userId = query.value(0).toInt();
           hide();
           AppWindow AppWind;
           AppWind.setModal(true);
           AppWind.exec();
       } else {
           ui->ErrorText->setText("�������� ������!");
       }

}

