//// org_manager.cpp
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
#include "org_manager.h"
#include <QMap>
#include <QStringList>
#include <QList>
QString org_manager::OrganizationName ;

QString org_manager::get_organization() {
    return OrganizationName;
}
///////
void org_manager::setorg(const QString &orgname) {
    OrganizationName = orgname;
}
////////
void org_manager::creat_organization(const QString& name){
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
    OrganizationName=name;
    org["members"] = QJsonArray();
    org["admins"] = QJsonArray();
    org["teams"] = QJsonArray();
    org["projects"] = QJsonArray();
    org["owner"] = loggedInUsername;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    org["time to build"] = currentDateTime.toString();
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
}

void org_manager::deleteOrganization(const QString& orgName)
{
    // Access org.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "org.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open org.json file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    QString loggedInUsername = UserManager::getLoggedInUsername();

    // Check if the organization exists
    if (!jsonObject.contains(orgName)) {
        qDebug() << "Organization does not exist in org.json.";
        QMessageBox::warning(this, "Delete Org", "Organization does not exist.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();
    QJsonArray adminsArray = org.value("admins").toArray();

    // Check if the logged-in user is the owner of the organization
    QString ownerUsername = org.value("owner").toString();

    if (loggedInUsername != ownerUsername) {
        qDebug() << "Logged-in user is not the owner of the organization.";
        QMessageBox::warning(this, "Demote to Member", "You are not authorized to demote admins in this organization.");
        return;
    }


    // Remove organization from json object
    jsonObject.remove(orgName);

    // Save the changes back to org.json
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(QJsonDocument(jsonObject).toJson());
    file.close();

    // Update user's organization list in text.json
    QString currentDirtext = QCoreApplication::applicationDirPath();
    QString filePathtext = currentDirtext + QDir::separator() + "text.json";
    QFile filetext(filePathtext);
    if (!filetext.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open text.json file.";
        return;
    }

    QByteArray fileDatatext = filetext.readAll();
    filetext.close();

    QJsonDocument jsonDoctext = QJsonDocument::fromJson(fileDatatext);

    qDebug() << "Logged-in User: " << loggedInUsername;

    // Update the organization list for the logged-in user
    QJsonObject jsonObjecttext = jsonDoctext.object();
    if (!jsonObjecttext.contains(loggedInUsername)) {
        qDebug() << "User not found in text.json.";
        return;
    }

    QJsonObject user = jsonObjecttext.value(loggedInUsername).toObject();
    QJsonValue organizationsValue = user.value("organization");

    if (!organizationsValue.isArray()) {
        qDebug() << "Organization list is not an array for the logged-in user.";
        return;
    }

    QJsonArray orgsArray = organizationsValue.toArray();

    // Remove the deleted organization from the user's organization list
    for (int i = 0; i < orgsArray.size(); ++i) {
        if (orgsArray.at(i).toString() == orgName) {
            orgsArray.removeAt(i);
            break;
        }
    }
    user["organization"] = orgsArray;

    // Save the changes back to text.json
    jsonObjecttext[loggedInUsername] = user;
    jsonDoctext.setObject(jsonObjecttext);
    QMessageBox::information(this, "Deletation", "organization has been deleted succefully");
    filetext.open(QIODevice::WriteOnly | QIODevice::Truncate);
    filetext.write(jsonDoctext.toJson());
    filetext.close();
}


void org_manager::editOrganizationName(const QString& oldName, const QString& newName)
{
    // Access org.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "org.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open org.json file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    QString loggedInUsername = UserManager::getLoggedInUsername();

    // Check if the organization exists
    if (!jsonObject.contains(oldName)) {
        qDebug() << "Organization does not exist in org.json.";
        QMessageBox::warning(this, "Edit Org Name", "Organization does not exist.");
        return;
    }

    QJsonObject org = jsonObject.value(oldName).toObject();
    QJsonArray adminsArray = org.value("admins").toArray();

    // Check if the logged-in user is the owner of the organization
    QString ownerUsername = org.value("owner").toString();

    if (loggedInUsername != ownerUsername) {
        qDebug() << "Logged-in user is not the owner of the organization.";
        QMessageBox::warning(this, "Edit Org Name", "You are not authorized to edit the name of this organization.");
        return;
    }

    // Remove the old organization entry
    jsonObject.remove(oldName);

    // Update the organization name in the organization object
    org["name"] = newName;

    OrganizationName = newName;
    // Add the updated organization entry with the new name
    jsonObject[newName] = org;

    // Save the changes back to org.json
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(QJsonDocument(jsonObject).toJson());
    file.close();

    // Update user's organization list in text.json
    QString currentDirtext = QCoreApplication::applicationDirPath();
    QString filePathtext = currentDirtext + QDir::separator() + "text.json";
    QFile filetext(filePathtext);
    if (!filetext.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open text.json file.";
        return;
    }

    QByteArray fileDatatext = filetext.readAll();
    filetext.close();

    QJsonDocument jsonDoctext = QJsonDocument::fromJson(fileDatatext);

    // Update the organization name in the user's organization list
    QJsonObject jsonObjecttext = jsonDoctext.object();
    if (!jsonObjecttext.contains(loggedInUsername)) {
        qDebug() << "User not found in text.json.";
        return;
    }

    QJsonObject user = jsonObjecttext.value(loggedInUsername).toObject();
    QJsonValue organizationsValue = user.value("organization");

    if (!organizationsValue.isArray()) {
        qDebug() << "Organization list is not an array for the logged-in user.";
        return;
    }

    QJsonArray orgsArray = organizationsValue.toArray();

    // Replace the old organization name with the new one
    for (int i = 0; i < orgsArray.size(); ++i) {
        if (orgsArray.at(i).toString() == oldName) {
            orgsArray[i] = newName;
            break;
        }
    }
    user["organization"] = orgsArray;

    // Save the changes back to text.json
    jsonObjecttext[loggedInUsername] = user;
    jsonDoctext.setObject(jsonObjecttext);
    QMessageBox::information(this, "Changing organization's name", "organization's name changed successfully");
    filetext.open(QIODevice::WriteOnly | QIODevice::Truncate);
    filetext.write(jsonDoctext.toJson());
    filetext.close();
}


void org_manager::addMemberToOrganization(const QString& orgName, const QString& memberName)
{
    // Access org.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "org.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open org.json file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    QString loggedInUsername = UserManager::getLoggedInUsername();

    // Check if the organization exists
    if (!jsonObject.contains(orgName)) {
        qDebug() << "Organization does not exist in org.json.";
        QMessageBox::warning(this, "Add Member", "Organization does not exist.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();
    QJsonArray adminsArray = org.value("admins").toArray();
    QJsonArray membersArray = org.value("members").toArray();

    // Check if the logged-in user is an admin of the organization
    if (!adminsArray.contains(loggedInUsername)) {
        qDebug() << "Logged-in user is not an admin of the organization.";
        QMessageBox::warning(this, "Add Member", "You are not authorized to add members to this organization.");
        return;
    }

    // Check if the member to be added already exists in the organization
    if (membersArray.contains(memberName)) {
        qDebug() << "Member already exists in the organization.";
        QMessageBox::warning(this, "Add Member", "Member already exists in the organization.");
        return;
    }

    // Add the member to the organization
    membersArray.append(memberName);
    org["members"] = membersArray;

    // Save the changes back to org.json
    jsonObject[orgName] = org;  // Update the organization object in the main JSON object

    // Find user in users.json and add the organization to the user's organizations
    QString usersFilePath = currentDir + QDir::separator() + "text.json";
    QFile usersFile(usersFilePath);
    if (!usersFile.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open text.json file.";
        return;
    }

    QByteArray usersFileData = usersFile.readAll();
    usersFile.close();

    QJsonDocument usersJsonDoc = QJsonDocument::fromJson(usersFileData);
    QJsonObject usersJsonObject = usersJsonDoc.object();

    if (!usersJsonObject.contains(memberName)) {
        qDebug() << "User does not exist in users.json.";
        QMessageBox::warning(this, "Add Member", "User does not exist.");
        return;
    }

    QJsonObject user = usersJsonObject.value(memberName).toObject();
    QJsonArray organizationsArray = user.value("organization").toArray();
    if (!organizationsArray.contains(orgName))
        organizationsArray.append(orgName);

    user["organization"] = organizationsArray;
    usersJsonObject[memberName] = user;

    // Save the changes back to users.json
    QJsonDocument updatedUsersJsonDoc(usersJsonObject);

    usersFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    usersFile.write(updatedUsersJsonDoc.toJson());
    usersFile.close();

    // Save the changes back to org.json
    QJsonDocument updatedJsonDoc(jsonObject);
    QMessageBox::information(this, "Adding member", "member was added succesfully");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(updatedJsonDoc.toJson());
    file.close();
}




void org_manager::removeMemberFromOrganization(const QString& orgName, const QString& memberName)
{
    // Access org.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "org.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open org.json file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    QString loggedInUsername = UserManager::getLoggedInUsername();

    // Check if the organization exists
    if (!jsonObject.contains(orgName)) {
        qDebug() << "Organization does not exist in org.json.";
        QMessageBox::warning(this, "Remove Member", "Organization does not exist.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();
    QJsonArray adminsArray = org.value("admins").toArray();
    QJsonArray membersArray = org.value("members").toArray();

    // Check if the logged-in user is an admin of the organization
    if (!adminsArray.contains(loggedInUsername)) {
        qDebug() << "Logged-in user is not an admin of the organization.";
        QMessageBox::warning(this, "Remove Member", "You are not authorized to remove members from this organization.");
        return;
    }

    // Check if the member to be removed exists in the organization
    if (!membersArray.contains(memberName)) {
        qDebug() << "Member does not exist in the organization.";
        QMessageBox::warning(this, "Remove Member", "Member does not exist in the organization.");
        return;
    }

    // Remove the member from the organization
    for (int i = 0; i < membersArray.size(); ++i) {
        if (membersArray.at(i).toString() == memberName) {
            membersArray.removeAt(i);
            break;
        }
        for (int i=0;i<adminsArray.size();++i)
        {
            if(adminsArray.at(i).toString()==memberName){
                adminsArray.removeAt(i);
                break;
            }
        }

    }
    org["admins"]=adminsArray;
    org["members"] = membersArray;

    // Save the changes back to org.json
    jsonObject[orgName] = org;  // Update the organization object in the main JSON object

    // Find user in users.json and remove the organization from the user's organizations
    QString usersFilePath = currentDir + QDir::separator() + "text.json";
    QFile usersFile(usersFilePath);
    if (!usersFile.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open text.json file.";
        return;
    }

    QByteArray usersFileData = usersFile.readAll();
    usersFile.close();

    QJsonDocument usersJsonDoc = QJsonDocument::fromJson(usersFileData);
    QJsonObject usersJsonObject = usersJsonDoc.object();

    if (!usersJsonObject.contains(memberName)) {
        qDebug() << "User does not exist in users.json.";
        QMessageBox::warning(this, "Remove Member", "User does not exist.");
        return;
    }

    QJsonObject user = usersJsonObject.value(memberName).toObject();
    QJsonArray organizationsArray = user.value("organization").toArray();
    //organizationsArray.removeOne(orgName);
    for (int i = 0; i < organizationsArray.size(); ++i) {
        if (organizationsArray.at(i).toString() == orgName) {
            organizationsArray.removeAt(i);
            break;
        }
    }
    user["organization"] = organizationsArray;
    usersJsonObject[memberName] = user;

    // Save the changes back to users.json
    QJsonDocument updatedUsersJsonDoc(usersJsonObject);

    usersFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    usersFile.write(updatedUsersJsonDoc.toJson());
    usersFile.close();

    // Save the changes back to org.json
    QJsonDocument updatedJsonDoc(jsonObject);
    QMessageBox::information(this, "Removing member", "member has been removed succesfully");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(updatedJsonDoc.toJson());
    file.close();
}


void org_manager::promoteMemberToAdminInOrganization(const QString& orgName, const QString& memberName)
{

    // Access org.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "org.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open org.json file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    QString loggedInUsername = UserManager::getLoggedInUsername();

    // Check if the organization exists
    if (!jsonObject.contains(orgName)) {
        qDebug() << "Organization does not exist in org.json.";
        QMessageBox::warning(nullptr, "Promote to Admin", "Organization does not exist.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();
    QJsonArray adminsArray = org.value("admins").toArray();
    QJsonArray membersArray = org.value("members").toArray();

    // Check if the logged-in user is an admin of the organization
    if (!adminsArray.contains(loggedInUsername)) {
        qDebug() << "Logged-in user is not an admin of the organization.";
        QMessageBox::warning(nullptr, "Promote to Admin", "You are not authorized to promote members in this organization.");
        return;
    }

    // Check if the member to be promoted exists in the organization members
    if (!membersArray.contains(memberName)) {
        qDebug() << "Member does not exist in the organization.";
        QMessageBox::warning(nullptr, "Promote to Admin", "Member does not exist in the organization.");
        return;
    }

    // Check if the member is already an admin
    if (adminsArray.contains(memberName)) {
        qDebug() << "Member is already an admin.";
        QMessageBox::warning(nullptr, "Promote to Admin", "Member is already an admin.");
        return;
    }

    // Promote the member to admin
    adminsArray.append(memberName);
    org["admins"] = adminsArray;

    // Save the changes back to org.json
    jsonObject[orgName] = org;  // Update the organization object in the main JSON object

    // Save the changes back to org.json
    QJsonDocument updatedJsonDoc(jsonObject);
    QMessageBox::information(this, "Promoting member", "Promoting member to admin was succesfull");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(updatedJsonDoc.toJson());
    file.close();

}
void org_manager::demoteAdminToMember(const QString& orgName, const QString& adminName)
{
    // Access org.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "org.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open org.json file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    QString loggedInUsername = UserManager::getLoggedInUsername();

    // Check if the organization exists
    if (!jsonObject.contains(orgName)) {
        qDebug() << "Organization does not exist in org.json.";
        QMessageBox::warning(this, "Demote to Member", "Organization does not exist.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();
    QJsonArray adminsArray = org.value("admins").toArray();
    QJsonArray membersArray = org.value("members").toArray();

    // Check if the logged-in user is the owner of the organization
    QString ownerUsername = org.value("owner").toString();

    if (loggedInUsername != ownerUsername) {
        qDebug() << "Logged-in user is not the owner of the organization.";
        QMessageBox::warning(this, "Demote to Member", "You are not authorized to demote admins in this organization.");
        return;
    }


    // Check if the admin to be demoted exists in the organization admins
    if (!adminsArray.contains(adminName)) {
        qDebug() << "Admin does not exist in the organization.";
        QMessageBox::warning(this, "Demote to Member", "Admin does not exist in the organization.");
        return;
    }

    // Check if the admin is the last admin in the organization
    if (adminsArray.size() == 1) {
        qDebug() << "Cannot demote the last admin.";
        QMessageBox::warning(this, "Demote to Member", "Cannot demote the last admin.");
        return;
    }

    // Demote the admin to member
    //adminsArray.removeOne(adminName);
    for (int i = 0; i < adminsArray.size(); ++i) {
        if (adminsArray.at(i).toString() == adminName) {
            adminsArray.removeAt(i);
            break;
        }
    }
    org["admins"] = adminsArray;

    // Save the changes back to org.json
    jsonObject[orgName] = org;  // Update the organization object in the main JSON object

    // Save the changes back to org.json
    QJsonDocument updatedJsonDoc(jsonObject);
    QMessageBox::information(this, "Demoting admin", "admin was demoted to member succesfully");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(updatedJsonDoc.toJson());
    file.close();
}


QVector<QString> org_manager::orgNamesSorted(const QJsonObject& orgJsonObject) {
    QVector<QString> orgNames;

    // Iterate through the organization names and add them to the list
    for (auto it = orgJsonObject.begin(); it != orgJsonObject.end(); ++it) {
        orgNames.append(it.key());
    }

    // Sort the list alphabetically
    orgNames.sort();

    return orgNames;
}



QVector<QString> org_manager::sortOrgsByTime(const QJsonObject& orgJsonObject) {
    QVector<QString> orgNamesSortedByTime;

    // Create a vector to store pairs of time and organization name
    QVector<QPair<QString, QString>> orgTimePairs;

    // Iterate through the organizations and extract the date strings and organization names
    for (auto it = orgJsonObject.begin(); it != orgJsonObject.end(); ++it) {
        QJsonObject orgObject = it.value().toObject();
        QString timeToBuildString = orgObject["time to build"].toString();
        QString orgName = it.key();

        // Add the pair of time and organization name to the vector
        orgTimePairs.append(qMakePair(timeToBuildString, orgName));
    }

    // Sort the vector based on time strings
    std::sort(orgTimePairs.begin(), orgTimePairs.end(), [](const QPair<QString, QString>& a, const QPair<QString, QString>& b) {
        return a.first < b.first; // Compare time strings
    });

    // Extract the organization names from the sorted pairs
    for (const auto& pair : orgTimePairs) {
        orgNamesSortedByTime.append(pair.second);
    }

    qDebug() << orgNamesSortedByTime;

    return orgNamesSortedByTime;
}

