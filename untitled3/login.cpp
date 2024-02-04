#include "login.h"
#include "ui_login.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCryptographicHash>
#include <QMessageBox>
#include "taski.h"
#include "userManager.h"
#include "forgetpass.h"

login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
}

login::~login()
{
    delete ui;
}

void login::on_buttonBox_2_accepted()
{
    QString uname, pass;
    uname = ui->lineEdit->text();
    pass = ui->lineEdit_2->text();

    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "text.json";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc(QJsonDocument::fromJson(fileData));

    QJsonObject jsonObject = jsonDoc.object();
    if (!jsonObject.contains(uname)) {
        QMessageBox::warning(this, "Login", "User not found");
        return;
    }

    QJsonValue passwordValue = jsonObject.value(uname).toObject().value("password");
    QString storedPassword = passwordValue.toString();

    // Hash the entered password
    QByteArray hashedPassword = QCryptographicHash::hash(pass.toUtf8(), QCryptographicHash::Sha256).toHex();
    //new
    if (hashedPassword == storedPassword) {
        UserManager::setLoggedInUser(uname, jsonObject);
        Taski *t=new Taski;
        t->show();
        emit loginSuccess(uname);
        this->close();

    } else {
        QMessageBox::warning(this, "Login", "Invalid username or password.");
    }
}

void login::on_buttonBox_2_rejected()
{
    this->close();
}

QString login::getMyName() const
{
    return myname;
}

void login::on_pushButton_clicked()
{
    forgetpass *f=new forgetpass;
    f->show();
}

