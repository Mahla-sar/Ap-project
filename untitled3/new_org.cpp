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
    : QDialog(parent),
    ui(new Ui::new_org)
{
    ui->setupUi(this);
}

new_org::~new_org()
{
    delete ui;
}

void new_org::on_buttonBox_accepted()
{
    QString name = ui->lineEdit->text();

    // Access text.json
    QString currentDirtext = QCoreApplication::applicationDirPath();
    QString filePathtext = currentDirtext + QDir::separator() + "text.json";
    QFile filetext(filePathtext);
    if (!filetext.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open file.";
        return;
    }

    QByteArray fileDatatext = filetext.readAll();
    filetext.close();

    QJsonDocument jsonDoctext = QJsonDocument::fromJson(fileDatatext);
    QString loggedInUsername = UserManager::getLoggedInUsername();

    // Adding name to organization
    QJsonObject jsonObjecttext = jsonDoctext.object();
    QJsonObject user = jsonObjecttext.value(loggedInUsername).toObject();

    // Correct the key name to "organization"
    QJsonArray orgsArray = user.value("organization").toArray();
    orgsArray.append(name);
    user["organization"] = orgsArray;

    // Save the changes back to text.json
    jsonObjecttext[loggedInUsername] = user;
    jsonDoctext.setObject(jsonObjecttext);

    // Save the changes back to text.json
    filetext.open(QIODevice::WriteOnly | QIODevice::Truncate);
    filetext.write(QJsonDocument(jsonObjecttext).toJson());
    filetext.close();

    // Access org.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "org.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject org;
    org["name"] = name;
    org["members"] = QJsonArray();
    org["admins"] = QJsonArray();
    org["teams"] = QJsonArray();
    org["projects"] = QJsonArray();



    // Add loggedInUsername to members
    QJsonArray membersArray = org["members"].toArray();
    membersArray.append(loggedInUsername);
    org["members"] = membersArray;

    // Add loggedInUsername to admins
    QJsonArray adminsArray = org["admins"].toArray();
    adminsArray.append(loggedInUsername);
    org["admins"] = adminsArray;

    QJsonObject jsonObject = jsonDoc.object();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "add new org", "Please fill in all the fields.");
        return;
    }
    if (jsonObject.contains(name)) {
        QMessageBox::warning(this, "add new org", "Username already exists.");
        return;
    }
    jsonObject[name] = org;
    jsonDoc.setObject(jsonObject);

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(jsonDoc.toJson());
    file.close();

    QMessageBox::information(this, "Organization Created", "The organization has been created successfully.");
    //emit add_neworg(name);
    this->close();
}
