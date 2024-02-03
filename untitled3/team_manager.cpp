#include "team_manager.h"
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
#include "usermanager.h"
#include "org_manager.h"
#include "team_manager.h"

//team_manager::team_manager()
//{

//}
QString team_manager::TeamName ;

QString team_manager::get_Team() {
    return TeamName;
}
void team_manager::setTeam(const QString &team_name) {
    TeamName = team_name;
}


void team_manager::createTeam(const QString& orgName,const QString& teamName) {
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
    //QString orgName=org_manager::get_organization();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    // Check if the organization exists
    if (!jsonObject.contains(orgName)) {
        qDebug() << "Organization does not exist in org.json.";
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    // Check if the team already exists
    if (org.contains("teams") && org.value("teams").toArray().contains(teamName)) {
        QMessageBox::warning(nullptr,"Creat team","Team already exists in the organization.");
        return;
    }
    //
    QString loggedInUsername = UserManager::getLoggedInUsername();
    qDebug()<<loggedInUsername;
    QJsonArray adminsArray = org.value("admins").toArray();

    // Check if the logged-in user is an admin of the organization
    if (!adminsArray.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "creat team", "Logged-in user is not an admin of the organization.");
        //QMessageBox::warning(this, "Add Member", "You are not authorized to add members to this organization.");
        return;
    }
    QJsonArray teamsArray = org.value("teams").toArray();


    // Add the member to the organization
    teamsArray.append(teamName);
    org["teams"] = teamsArray;

    // Save the changes back to org.json
    jsonObject[orgName] = org;  // Update the organization object in the main JSON object

    QString currentDirTeam = QCoreApplication::applicationDirPath();
    QString filePathTeam = currentDirTeam + QDir::separator() + "Team.json";

    QFile fileTeam(filePathTeam);
    if (!fileTeam.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open Team.json file.";
        return;
    }

    QByteArray fileDataTeam = fileTeam.readAll();
    fileTeam.close();

    QJsonDocument jsonDocTeam = QJsonDocument::fromJson(fileDataTeam);
    QJsonObject Team;
    Team["name"] = teamName;
    TeamName = teamName;
    Team["members"] = QJsonArray();
    Team["heads"] = QJsonArray();
    Team["organization"] = orgName;  // Set the organization name for the team
    // Add loggedInUsername to members
    QJsonArray membersArray = Team["members"].toArray();
    membersArray.append(loggedInUsername);
    Team["members"] = membersArray;

    // Add loggedInUsername to heads
    QJsonArray headsArrayTeam = Team["heads"].toArray();
    headsArrayTeam.append(loggedInUsername);
    Team["heads"] = headsArrayTeam;

    Team["owner"] = loggedInUsername ;


    QJsonObject jsonObjectTeam = jsonDocTeam.object();
    if (teamName.isEmpty() || jsonObjectTeam.contains(teamName)) {
        QMessageBox::warning(nullptr, "creat team", "Team name is empty or already exists.");
        return;
    }

    jsonObjectTeam[teamName] = Team;
    jsonDocTeam.setObject(jsonObjectTeam);

    fileTeam.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileTeam.write(jsonDocTeam.toJson());
    fileTeam.close();

    // Add the new team to the organization
    //    QJsonArray teamsArray = org["teams"].toArray();
    //    teamsArray.append(teamName);
    //    org["teams"] = teamsArray;

    // Save the changes back to org.json
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(QJsonDocument(jsonObject).toJson());
    file.close();

    QMessageBox::information(nullptr, "creat team", "Team created successfully.");
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

    // Adding name to team
    QJsonObject jsonObjecttext = jsonDoctext.object();
    QJsonObject user = jsonObjecttext.value(loggedInUsername).toObject();

    // Correct the key name to "team"
    QJsonArray teamArray = user.value("teams").toArray();
    teamArray.append(teamName);
    user["teams"] = teamArray;

    // Save the changes back to text.json
    jsonObjecttext[loggedInUsername] = user;
    jsonDoctext.setObject(jsonObjecttext);

    // Save the changes back to text.json
    filetext.open(QIODevice::WriteOnly | QIODevice::Truncate);
    filetext.write(QJsonDocument(jsonObjecttext).toJson());
    filetext.close();
}

void team_manager::renameTeam(const QString& orgName, const QString& oldTeamName, const QString& newTeamName) {
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

    // Check if the organization exists
    if (!jsonObject.contains(orgName)) {
        QMessageBox::warning(nullptr, "Rename team", "Organization does not exist in org.json.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    // Check if the team exists in the organization
    QJsonArray teamsArray = org.value("teams").toArray();
    if (!teamsArray.contains(oldTeamName)) {
        QMessageBox::warning(nullptr, "Rename team", "Team does not exist in the organization.");
        return;
    }

    // Check if the logged-in user is an admin of the organization
    QString loggedInUsername = UserManager::getLoggedInUsername();
    QJsonArray adminsArray = org.value("admins").toArray();
    if (!adminsArray.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "Rename team",  "Logged-in user is not an admin of the organization.");
        return;
    }

    // Access Team.json
    QString currentDirTeam = QCoreApplication::applicationDirPath();
    QString filePathTeam = currentDirTeam + QDir::separator() + "Team.json";

    QFile fileTeam(filePathTeam);
    if (!fileTeam.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open Team.json file.";
        return;
    }

    QByteArray fileDataTeam = fileTeam.readAll();
    fileTeam.close();

    QJsonDocument jsonDocTeam = QJsonDocument::fromJson(fileDataTeam);
    QJsonObject jsonObjectTeam = jsonDocTeam.object();

    // Check if the team exists in Team.json
    if (!jsonObjectTeam.contains(oldTeamName)) {
        QMessageBox::warning(nullptr, "Rename team", "Team does not exist in Team.json.");
        return;
    }

    QJsonObject team = jsonObjectTeam.value(oldTeamName).toObject();

    // Update the team name
    team["name"] = newTeamName;

    // Update the team name in Team.json
    jsonObjectTeam.remove(oldTeamName);  // Remove the old team name
    jsonObjectTeam[newTeamName] = team;  // Add the team with the new name
    jsonDocTeam.setObject(jsonObjectTeam);

    fileTeam.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileTeam.write(jsonDocTeam.toJson());
    fileTeam.close();

    // Update the team name in the organization
    //    teamsArray.removeOne(oldTeamName);
    for (int i = 0; i < teamsArray.size(); ++i) {
        if (teamsArray.at(i).toString() == oldTeamName) {
            teamsArray[i] = newTeamName;
            break;
        }
    }
    //teamsArray.append(newTeamName);
    org["teams"] = teamsArray;
    // Save the changes back to org.json
    jsonObject[orgName] = org;  // Update the organization object in the main JSON object

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(QJsonDocument(jsonObject).toJson());
    file.close();
    //////////
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

    // Update the team name in the user's team list
    QJsonObject jsonObjecttext = jsonDoctext.object();
    if (!jsonObjecttext.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "Rename team", "User not found in text.json.");
        return;
    }

    QJsonObject user = jsonObjecttext.value(loggedInUsername).toObject();
    QJsonValue teamsValue = user.value("teams");

    if (!teamsValue.isArray()) {
        QMessageBox::warning(nullptr, "Rename team", "teams list is not an array for the logged-in user.");
        return;
    }

    QJsonArray teamArray = teamsValue.toArray();

    // Replace the old team name with the new one
    for (int i = 0; i < teamArray.size(); ++i) {
        if (teamArray.at(i).toString() == oldTeamName) {
            teamArray[i] = newTeamName;
            break;
        }
    }
    user["teams"] = teamArray;
    QMessageBox::information(nullptr, "Rename team", "Team's name has been changed succesfully");
    // Save the changes back to text.json
    jsonObjecttext[loggedInUsername] = user;
    jsonDoctext.setObject(jsonObjecttext);
    //QMessageBox::information(this, "Changing organization's name", "organization's name changed successfully");
    filetext.open(QIODevice::WriteOnly | QIODevice::Truncate);
    filetext.write(jsonDoctext.toJson());
    filetext.close();




}


void team_manager::deleteTeam(const QString& orgName, const QString& teamName) {
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

    // Check if the organization exists
    if (!jsonObject.contains(orgName)) {
        QMessageBox::warning(nullptr, "Delete team", "Organization does not exist in org.json.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    // Check if the team exists in the organization
    QJsonArray teamsArray = org.value("teams").toArray();
    int indexToRemove = -1;

    for (int i = 0; i < teamsArray.size(); ++i) {
        if (teamsArray.at(i).toString() == teamName) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove == -1) {
        QMessageBox::warning(nullptr, "Delete team",  "Team does not exist in the organization.");
        return;
    }

    // Check if the logged-in user is an owner of the team
    QString loggedInUsername = UserManager::getLoggedInUsername();

    // Remove the team from the organization
    teamsArray.removeAt(indexToRemove);
    org["teams"] = teamsArray;

    // Save the changes back to org.json
    jsonObject[orgName] = org;

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(QJsonDocument(jsonObject).toJson());
    file.close();

    // Access Team.json
    QString currentDirTeam = QCoreApplication::applicationDirPath();
    QString filePathTeam = currentDirTeam + QDir::separator() + "Team.json";

    QFile fileTeam(filePathTeam);
    if (!fileTeam.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open Team.json file.";
        return;
    }

    QByteArray fileDataTeam = fileTeam.readAll();
    fileTeam.close();

    QJsonDocument jsonDocTeam = QJsonDocument::fromJson(fileDataTeam);
    QJsonObject jsonObjectTeam = jsonDocTeam.object();

    QJsonObject team = jsonObjectTeam.value(teamName).toObject();
    QString ownerArray = team.value("owner").toString();

    if (!ownerArray.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "Delete team", "Logged-in user is not an owner of the team.");
        return;
    }
    // Check if the team exists in Team.json
    if (!jsonObjectTeam.contains(teamName)) {
        QMessageBox::warning(nullptr, "Delete team",  "Team does not exist in Team.json.");
        return;
    }

    // Remove the team from Team.json
    jsonObjectTeam.remove(teamName);

    jsonDocTeam.setObject(jsonObjectTeam);

    fileTeam.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileTeam.write(jsonDocTeam.toJson());
    fileTeam.close();

    QMessageBox::information(nullptr, "Delete team","Team deleted successfully.");
}

//

void team_manager::addMemberToTeam(const QString& orgName, const QString& teamName, const QString& memberUsername) {
    // Access org.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "org.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(nullptr, "Add member", "Failed to open org.json file.");
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    // Check if the organization exists
    if (!jsonObject.contains(orgName)) {
        QMessageBox::warning(nullptr, "Add member", "Organization does not exist in org.json.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    // Check if the team exists in the organization
    if (!org.contains("teams") || !org.value("teams").toArray().contains(teamName)) {
        QMessageBox::warning(nullptr, "Add member", "Team does not exist in the organization.");
        return;
    }

    // Check if the member is part of the organization
    if (!org.contains("members") || !org.value("members").toArray().contains(memberUsername)) {
        QMessageBox::warning(nullptr, "Add member", "Member does not exist in the organization.");
        return;
    }

    // Check if the logged-in user is trying to add themselves as a member
    QString loggedInUsername = UserManager::getLoggedInUsername();
    if (loggedInUsername == memberUsername) {
        QMessageBox::warning(nullptr, "Add member", "Cannot add yourself as a member.");
        return;
    }

    // Access Team.json
    QString filePathTeam = currentDir + QDir::separator() + "Team.json";

    QFile fileTeam(filePathTeam);
    if (!fileTeam.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(nullptr, "Add member", "Failed to open Team.json file.");
        return;
    }

    QByteArray fileDataTeam = fileTeam.readAll();
    fileTeam.close();

    QJsonDocument jsonDocTeam = QJsonDocument::fromJson(fileDataTeam);
    QJsonObject jsonObjectTeam = jsonDocTeam.object();

    // Check if the team exists in Team.json
    if (!jsonObjectTeam.contains(teamName)) {
        QMessageBox::warning(nullptr, "Add member", "Team does not exist in Team.json.");
        return;
    }

    QJsonObject team = jsonObjectTeam.value(teamName).toObject();

    // Check if the logged-in user is a head of the team
    QJsonArray headsArrayTeam = team.value("heads").toArray();
    if (!headsArrayTeam.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "Add member","Logged-in user is not a head of the team.");
        return;
    }

    // Check if the member is already part of the team
    QJsonArray membersArray = team.value("members").toArray();
    if (membersArray.contains(memberUsername)) {
        QMessageBox::warning(nullptr, "Add member","Member is already part of the team.");
        return;
    }

    // Add the member to the team
    membersArray.append(memberUsername);
    team["members"] = membersArray;

    // Save the changes back to Team.json
    jsonObjectTeam[teamName] = team;
    jsonDocTeam.setObject(jsonObjectTeam);

    fileTeam.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileTeam.write(jsonDocTeam.toJson());
    fileTeam.close();

    // Update text.json with the new team information for the member
    QString filePathText = currentDir + QDir::separator() + "text.json";

    QFile fileText(filePathText);
    if (!fileText.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(nullptr, "Add member", "Failed to open text.json file.");
        return;
    }

    QByteArray fileDataText = fileText.readAll();
    fileText.close();

    QJsonDocument jsonDocText = QJsonDocument::fromJson(fileDataText);
    QJsonObject jsonObjectText = jsonDocText.object();

    // Check if the member exists in text.json
    if (!jsonObjectText.contains(memberUsername)) {
        QMessageBox::warning(nullptr, "Add member", "Member does not exist in text.json.");
        return;
    }

    QJsonObject user = jsonObjectText.value(memberUsername).toObject();

    // Update the user's teams information
    QJsonArray teamsArray = user.value("teams").toArray();
    teamsArray.append(teamName);
    user["teams"] = teamsArray;

    // Save the changes back to text.json
    jsonObjectText[memberUsername] = user;
    jsonDocText.setObject(jsonObjectText);

    fileText.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileText.write(jsonDocText.toJson());
    fileText.close();

    QMessageBox::information(nullptr, "Add member", "Member added to the team successfully.");
}



void team_manager::removeMemberFromTeam(const QString& orgName, const QString& teamName, const QString& memberUsername) {
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

    // Check if the organization exists
    if (!jsonObject.contains(orgName)) {
        QMessageBox::warning(nullptr, "Remove member","Organization does not exist in org.json.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();
    QString loggedInUsername = UserManager::getLoggedInUsername();


    // Check if the team exists in the organization
    if (!org.contains("teams") || !org.value("teams").toArray().contains(teamName)) {
        QMessageBox::warning(nullptr, "Remove member", "Team does not exist in the organization.");
        return;
    }

    // Access Team.json
    QString currentDirTeam = QCoreApplication::applicationDirPath();
    QString filePathTeam = currentDirTeam + QDir::separator() + "Team.json";

    QFile fileTeam(filePathTeam);
    if (!fileTeam.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open Team.json file.";
        return;
    }

    QByteArray fileDataTeam = fileTeam.readAll();
    fileTeam.close();

    QJsonDocument jsonDocTeam = QJsonDocument::fromJson(fileDataTeam);
    QJsonObject jsonObjectTeam = jsonDocTeam.object();

    // Check if the team exists in Team.json
    if (!jsonObjectTeam.contains(teamName)) {
        QMessageBox::warning(nullptr, "Remove member","Team does not exist in Team.json.");
        return;
    }

    QJsonObject team = jsonObjectTeam.value(teamName).toObject();
    QJsonArray headsArray = team.value("heads").toArray();
    if (!headsArray.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "Remove member", "Logged-in user is not an heads of the team.");
        return;
    }

    //QJsonObject team = jsonObjectTeam.value(teamName).toObject();
    QJsonArray headsArrayTeam = team.value("heads").toArray();

    // Check if the logged-in user is an heads of the team
    if (!headsArrayTeam.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "Remove member", "Logged-in user is not an heads of the team.");
        return;
    }

    // Check if the member is part of the team
    QJsonArray membersArray = team.value("members").toArray();
    if (!membersArray.contains(memberUsername)) {
        QMessageBox::warning(nullptr, "Remove member", "Member is not part of the team.");
        return;
    }
    // Remove the member from the team
    for (int i = 0; i < membersArray.size(); ++i) {
        if (membersArray.at(i).toString() == memberUsername) {
            membersArray.removeAt(i);
            break;
        }
    }
    team["members"] = membersArray;

    // Save the changes back to Team.json
    jsonObjectTeam[teamName] = team;
    jsonDocTeam.setObject(jsonObjectTeam);

    fileTeam.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileTeam.write(jsonDocTeam.toJson());
    fileTeam.close();

    //QMessageBox::information(this, "Remove member", "Member removed from the team successfully.");

    // Access text.json
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
    QJsonObject jsonObjecttext = jsonDoctext.object();

    // Check if the member exists in text.json
    if (!jsonObjecttext.contains(memberUsername)) {
        QMessageBox::warning(nullptr, "Remove member","Member does not exist in text.json.");
        return;
    }

    // Remove the team from the member's teams list
    QJsonObject user = jsonObjecttext.value(memberUsername).toObject();
    QJsonArray teamsArray = user.value("teams").toArray();
    for (int i = 0; i < teamsArray.size(); ++i) {
        if (teamsArray.at(i).toString() == teamName) {
            teamsArray.removeAt(i);
            break;
        }
    }    user["teams"] = teamsArray;

    // Save the changes back to text.json
    jsonObjecttext[memberUsername] = user;
    jsonDoctext.setObject(jsonObjecttext);

    filetext.open(QIODevice::WriteOnly | QIODevice::Truncate);
    filetext.write(jsonDoctext.toJson());
    filetext.close();

    QMessageBox::information(nullptr, "Remove member","Member removed from the team in text.json successfully.");
}


void team_manager::promoteMemberToHeadInTeam(const QString& orgName, const QString& teamName, const QString& memberUsername) {
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

    // Check if the organization exists
    if (!jsonObject.contains(orgName)) {
        QMessageBox::warning(nullptr, "Promot member","Organization does not exist in org.json.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    // Check if the logged-in user is an admin of the organization
    QString loggedInUsername = UserManager::getLoggedInUsername();
    QJsonArray adminsArray = org.value("admins").toArray();
    //    if (!adminsArray.contains(loggedInUsername)) {
    //        qDebug() << "Logged-in user is not an admin of the organization.";
    //        return;
    //    }

    // Check if the team exists in the organization
    if (!org.contains("teams") || !org.value("teams").toArray().contains(teamName)) {
        QMessageBox::warning(nullptr, "Promot member", "Team does not exist in the organization.");
        return;
    }

    // Access Team.json
    QString currentDirTeam = QCoreApplication::applicationDirPath();
    QString filePathTeam = currentDirTeam + QDir::separator() + "Team.json";

    QFile fileTeam(filePathTeam);
    if (!fileTeam.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open Team.json file.";
        return;
    }

    QByteArray fileDataTeam = fileTeam.readAll();
    fileTeam.close();

    QJsonDocument jsonDocTeam = QJsonDocument::fromJson(fileDataTeam);
    QJsonObject jsonObjectTeam = jsonDocTeam.object();

    // Check if the team exists in Team.json
    if (!jsonObjectTeam.contains(teamName)) {
        QMessageBox::warning(nullptr, "Promot member", "Team does not exist in Team.json.");
        return;
    }

    QJsonObject team = jsonObjectTeam.value(teamName).toObject();
    QJsonArray headsArray = team.value("heads").toArray();

    // Check if the head is part of the team
    if (!headsArray.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "Promot member", "username is not heed of the team.");
        return;
    }

    // Check if the member is part of the team
    QJsonArray membersArray = team.value("members").toArray();
    if (!membersArray.contains(memberUsername)) {
        QMessageBox::warning(nullptr, "Promot member","Member is not part of the team.");
        return;
    }

    // Check if the member is already a head of the team
    if (headsArray.contains(memberUsername)) {
        QMessageBox::warning(nullptr, "Promot member","Member is a head of the team");
        return;
    }
    // Add the heads to the team
    headsArray.append(memberUsername);
    team["heads"] = headsArray;
    // Change the role of the member to head
    // Fix: Change "admins" to "heads"

    // Save the changes back to Team.json
    jsonObjectTeam[teamName] = team;
    jsonDocTeam.setObject(jsonObjectTeam);

    fileTeam.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileTeam.write(jsonDocTeam.toJson());
    fileTeam.close();

    QMessageBox::information(nullptr, "Promot member","Member role changed to head in the team successfully.");

}
void team_manager::demoteHeadToMemberInTeam(const QString& orgName, const QString& teamName, const QString& memberUsername) {
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

    // Check if the organization exists
    if (!jsonObject.contains(orgName)) {
        QMessageBox::warning(nullptr, "demote member","Organization does not exist in org.json.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    QString loggedInUsername = UserManager::getLoggedInUsername();


    // Check if the team exists in the organization
    if (!org.contains("teams") || !org.value("teams").toArray().contains(teamName)) {
        QMessageBox::warning(nullptr, "demote member", "Team does not exist in the organization.");
        return;
    }

    // Access Team.json
    QString currentDirTeam = QCoreApplication::applicationDirPath();
    QString filePathTeam = currentDirTeam + QDir::separator() + "Team.json";

    QFile fileTeam(filePathTeam);
    if (!fileTeam.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open Team.json file.";
        return;
    }

    QByteArray fileDataTeam = fileTeam.readAll();
    fileTeam.close();

    QJsonDocument jsonDocTeam = QJsonDocument::fromJson(fileDataTeam);
    QJsonObject jsonObjectTeam = jsonDocTeam.object();

    // Check if the team exists in Team.json
    if (!jsonObjectTeam.contains(teamName)) {
        QMessageBox::warning(nullptr, "demote member","Team does not exist in Team.json.");
        return;
    }

    QJsonObject team = jsonObjectTeam.value(teamName).toObject();
    QJsonArray headsArray = team.value("heads").toArray();

    //    QJsonArray ownerArray = team.value("owner").toArray();
    //    if (!ownerArray.contains(loggedInUsername)) {
    //        qDebug() << "Logged-in user is not an owner of the team.";
    //        return;
    //    }
    // Check if the logged-in user is the owner of the organization
    QString ownerUsername = team.value("owner").toString();

    if (loggedInUsername != ownerUsername) {
        QMessageBox::warning(nullptr, "demote member", "Logged-in user is not the owner of the team.");
        return;
    }
    // Check if the head is part of the team
    if (!headsArray.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "demote member","Username is not a head of the team.");
        return;
    }

    // Check if the member is part of the team
    QJsonArray membersArray = team.value("members").toArray();
    if (!membersArray.contains(memberUsername)) {
        QMessageBox::warning(nullptr, "demote member",  "Member is not part of the team.");
        return;
    }

    // Check if the member is a head of the team
    if (!headsArray.contains(memberUsername)) {
        QMessageBox::warning(nullptr, "demote member","Member is not a head of the team.");
        return;
    }

    // Remove the member from the heads

    for (int i = 0; i < headsArray.size(); ++i) {
        if (headsArray.at(i).toString() == memberUsername) {
            headsArray.removeAt(i);
            break;
        }
    }
    team["heads"] = headsArray;

    // Save the changes back to Team.json
    jsonObjectTeam[teamName] = team;
    jsonDocTeam.setObject(jsonObjectTeam);

    fileTeam.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileTeam.write(jsonDocTeam.toJson());
    fileTeam.close();

    QMessageBox::information(nullptr, "demote member", "Head role demoted to member in the team successfully.");
}

QVector<QString> team_manager::teamNamesSorted(const QJsonObject& teamJsonObject) {
    QVector<QString> teamNames;

    // Iterate through the teamanization names and add them to the list
    for (auto it = teamJsonObject.begin(); it != teamJsonObject.end(); ++it) {
        teamNames.append(it.key());
    }

    // Sort the list alphabetically
    teamNames.sort();

    return teamNames;
}



QVector<QString> team_manager::sortteamsByTime(const QJsonObject& teamJsonObject) {
    QVector<QString> teamNamesSortedByTime;

    // Create a vector to store pairs of time and teamanization name
    QVector<QPair<QString, QString>> teamTimePairs;

    // Iterate through the teams and extract the date strings and team names
    for (auto it = teamJsonObject.begin(); it != teamJsonObject.end(); ++it) {
        QJsonObject teamObject = it.value().toObject();
        QString timeToBuildString = teamObject["time to build"].toString();
        QString teamName = it.key();

        // Add the pair of time and team name to the vector
        teamTimePairs.append(qMakePair(timeToBuildString, teamName));
    }

    // Sort the vector based on time strings
    std::sort(teamTimePairs.begin(), teamTimePairs.end(), [](const QPair<QString, QString>& a, const QPair<QString, QString>& b) {
        return a.first < b.first; // Compare time strings
    });

    // Extract the teamanization names from the sorted pairs
    for (const auto& pair : teamTimePairs) {
        teamNamesSortedByTime.append(pair.second);
    }

    qDebug() << teamNamesSortedByTime;

    return teamNamesSortedByTime;
}


