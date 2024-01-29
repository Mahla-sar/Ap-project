#include "new_org.h"
#include "ui_new_org.h"
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


new_org::new_org(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::new_org)
{
    ui->setupUi(this);
}

new_org::~new_org()
{
    delete ui;
}

void new_org::on_buttonBox_accepted()
{
    QString name;
    name=ui->lineEdit->text();


    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "org.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc;
    jsonDoc = QJsonDocument::fromJson(fileData);

    QString loggedInUsername = UserManager::getLoggedInUsername();

    QJsonObject org;
    org["name"] = name;
    org["members"] = QJsonArray();
    org["admins"] = QJsonArray();
    org["teams"] = QJsonArray();
    org["projects"] = QJsonArray();
    //new
    QJsonArray membersArray = org["members"].toArray();
    membersArray.append(loggedInUsername);
    org["members"] = membersArray;

    QJsonArray adminsArray = org["admins"].toArray();
    adminsArray.append(loggedInUsername);
    org["admins"] = adminsArray;

    //QMessageBox::warning(this, "Sign in", loggedInUsername );
    QJsonObject loggedInUserData = UserManager::getLoggedInUserData();
    //new


//    if (loggedInUserData.contains("orgnization")) {
//        QMessageBox::warning(this, "Sign in", "yes");

////            QJsonArray orgsArray = loggedInUserData["orgnization"].toArray();
////            orgsArray.append("123");
////            loggedInUserData["orgnization"] = orgsArray;
//    }
    QJsonObject jsonObject = jsonDoc.object();


    jsonObject [name] = org;
    jsonDoc.setObject(jsonObject);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(jsonDoc.toJson());
    file.close();
// QObject::connect(&loginDialog, &login::loginSuccess, [](const QString &username) {
//        qDebug() << "Login successful. Username:" << username;
//}
     //QMessageBox::warning(this, "Sign in", "done");



}

