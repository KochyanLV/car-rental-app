#include "registration.h"
#include "authorization.h"
#include "ui_registration.h"

#pragma execution_character_set("utf-8")

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration){
    ui->setupUi(this);

}

Registration::~Registration(){delete ui;}

void Registration::on_RegistrBtn_clicked(){
       QString firstname, lastname, email, phone, username, password, confpassword;
       static int id;
       firstname = ui->FirstNameInput->text();
       lastname = ui->LastNameInput->text();
       email = ui->EmailInput->text();
       phone = ui->PhoneInput->text();
       username = ui->UserInput->text();
       password = ui->PasswdInput->text();
       confpassword = ui->ConfirmPasswdInput->text();

       QSqlQuery query;
       query.prepare("SELECT * FROM usersdata WHERE username = :username");
       query.bindValue(":username", username);
       if (query.exec()) {
         if (query.first()) {
           ui->ErrorText->setText("Измените никнейм!");
         }
         else {
             if (!password.isEmpty() && !firstname.isEmpty() && !lastname.isEmpty() && !email.isEmpty() && !username.isEmpty() && !password.isEmpty()){
                 if(password == confpassword){
                     query.prepare("SELECT id FROM usersdata WHERE id = (SELECT MAX(id) FROM usersdata)");
                     if (query.exec()) {
                        if (query.first()) { id = query.value(0).toInt();}
                        }
                     else { id = 0; }

                     query.prepare("INSERT INTO usersdata (id, firstname, lastname, email, phone, username, password) VALUES (:id, :firstname, :lastname, :email, :phone, :username, :password);");
                     query.bindValue(":id", ++id);
                     query.bindValue(":firstname", firstname);
                     query.bindValue(":lastname", lastname);
                     query.bindValue(":email", email);
                     query.bindValue(":phone", phone);
                     query.bindValue(":username", username);
                     query.bindValue(":password", password);
                     if (!query.exec()) {
                       ui->ErrorText->setText("Ошибка, попробуйте ещё раз!");
                     }
                     else{
                       ui->ErrorText->setText("Успешно!");
                       hide();
                       authorization AppWind;
                       AppWind.setModal(true);
                       AppWind.exec();
                     }
                 }
                 else{
                     ui->ErrorText->setText("Проверьте правильность паролей!");
                 }
             }
             else{
                  ui->ErrorText->setText("Заполните все поля!");
             }
         }
       }
       else {
          ui->ErrorText->setText("Что-то не так с базой данных!");
       }

}
