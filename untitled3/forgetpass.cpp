#include "forgetpass.h"
#include "ui_forgetpass.h"
#include "usermanager.h"

forgetpass::forgetpass(QWidget *parent)
    : QDialog(parent), ui(new Ui::forgetpass) {
    ui->setupUi(this);
}

forgetpass::~forgetpass() {
    delete ui;
}

void forgetpass::on_buttonBox_accepted() {
    qint32 age = ui->age_2->text().toInt();
    QString user = ui->username_2->text();
    QString name = ui->name_2->text();
    QString email = ui->email_2->text();
    QString pass = ui->password_2->text();


    QJsonObject jsonObject;
    jsonObject["age"] = age;
    jsonObject["user"] = user;
    jsonObject["name"] = name;
    jsonObject["email"] = email;
    jsonObject["pass"] = pass;


    UserManager my_user;
    bool trueIdentity = my_user.authenticateAndResetPassword(user, name, email, age, pass);

    if (trueIdentity) {

        my_user.resetPassword(jsonObject, pass);
    }
}
