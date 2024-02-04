#include "signin.h"
#include "ui_signin.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QCryptographicHash>
#include <algorithm>
signin::signin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signin)
{
    ui->setupUi(this);
}

signin::~signin()
{
    delete ui;
}

void signin::on_buttonBox_2_accepted()
{
    QString uname, name, pass, mail, gen, age;
    uname = ui->username_2->text();
    name = ui->name_2->text();
    pass = ui->password_2->text();
    mail = ui->email_2->text();
    age = ui->age_2->text();
    gen = ui->comboBox->currentText();

    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "text.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc;
    jsonDoc = QJsonDocument::fromJson(fileData);

    QJsonObject user;
    user["username"] = uname;
    user["name"] = name;
    user["password"] = QString(QCryptographicHash::hash(pass.toUtf8(), QCryptographicHash::Sha256).toHex());
    user["email"] = mail;
    user["age"] = age;
    user["gender"] = gen;
    //user["orgnization"]=QJsonArray();

    bool isAgeValid;
    int ageInt = age.toInt(&isAgeValid);
    QJsonObject jsonObject = jsonDoc.object();
    if (uname.isEmpty() || name.isEmpty() || pass.isEmpty() || mail.isEmpty() || age.isEmpty()) {
        QMessageBox::warning(this, "Sign in", "Please fill in all the fields.");
        return;
    }
   else if(pass.size()<8 ){
           QMessageBox::warning(this, "Sign in", "Password must be at least 8 characters long.");
           return;
   }


   // else if (!(std::any_of(pass.begin(), pass.end(), ::isupper) && std::any_of(pass.begin(), pass.end(), ::islower))) {
   //     QMessageBox::warning(this, "Sign in", "Password must contain both uppercase and lowercase letters.");
   //     return;
   // }
    else if (!isAgeValid) {
        QMessageBox::warning(this, "Sign in", "Please enter a valid age.");
        return;
    }
    else if (jsonObject.contains(uname)) {
        QMessageBox::warning(this, "Sign in", "Username already exists.");
        return;
    }
    else if (jsonObject.contains(mail)) {
        QMessageBox::warning(this, "Sign in", "Email already exists.");
        return;
    }
   else {
       bool hasUpperCase = false;
       bool hasLowerCase = false;

       for (QChar c : pass) {
           if (c.isUpper()) {
               hasUpperCase = true;
           } else if (c.isLower()) {
               hasLowerCase = true;
           }
       }

       if (!hasUpperCase || !hasLowerCase) {
           QMessageBox::warning(this, "Sign in", "Password must contain both uppercase and lowercase letters.");
           return;
       }
   }


    jsonObject[uname] = user;
    jsonDoc.setObject(jsonObject);

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(jsonDoc.toJson());
    file.close();
    QMessageBox::information(this, "Sign in", "Your sign in was successful");
    this->close();
}

void signin::on_buttonBox_2_rejected()
{
    this->close();
}
