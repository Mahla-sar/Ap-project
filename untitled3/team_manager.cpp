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


void team_manager::createTeam(const QString& orgName, const QString& teamName) {
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
        qDebug() << "Organization does not exist in org.json.";
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    // Check if the team already exists
    if (org.contains("teams") && org.value("teams").toArray().contains(teamName)) {
        qDebug() << "Team already exists in the organization.";
        return;
    }
    //
    QString loggedInUsername = UserManager::getLoggedInUsername();

    QJsonArray adminsArray = org.value("admins").toArray();

    // Check if the logged-in user is an admin of the organization
    if (!adminsArray.contains(loggedInUsername)) {
        qDebug() << "Logged-in user is not an admin of the organization.";
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
        qDebug() << "Team name is empty or already exists.";
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

    qDebug() << "Team created successfully.";
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
        qDebug() << "Organization does not exist in org.json.";
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    // Check if the team exists in the organization
    QJsonArray teamsArray = org.value("teams").toArray();
    if (!teamsArray.contains(oldTeamName)) {
        qDebug() << "Team does not exist in the organization.";
        return;
    }

    // Check if the logged-in user is an admin of the organization
    QString loggedInUsername = UserManager::getLoggedInUsername();
    QJsonArray adminsArray = org.value("admins").toArray();
    if (!adminsArray.contains(loggedInUsername)) {
        qDebug() << "Logged-in user is not an admin of the organization.";
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
        qDebug() << "Team does not exist in Team.json.";
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
        qDebug() << "User not found in text.json.";
        return;
    }

    QJsonObject user = jsonObjecttext.value(loggedInUsername).toObject();
    QJsonValue teamsValue = user.value("teams");

    if (!teamsValue.isArray()) {
        qDebug() << "teams list is not an array for the logged-in user.";
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

    // Save the changes back to text.json
    jsonObjecttext[loggedInUsername] = user;
    jsonDoctext.setObject(jsonObjecttext);
    //QMessageBox::information(this, "Changing organization's name", "organization's name changed successfully");
    filetext.open(QIODevice::WriteOnly | QIODevice::Truncate);
    filetext.write(jsonDoctext.toJson());
    filetext.close();



    qDebug() << "Team name changed successfully.";
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
        qDebug() << "Organization does not exist in org.json.";
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    // Check if the team exists in the organization
    if (!org.contains("teams") || !org.value("teams").toArray().contains(teamName)) {
        qDebug() << "Team does not exist in the organization.";
        return;
    }

    // Check if the logged-in user is an owner of the team
    QJsonObject team = jsonObject.value(teamName).toObject();
    QString loggedInUsername = UserManager::getLoggedInUsername();
    QJsonArray ownerArray = team.value("owner").toArray();
    if (!ownerArray.contains(loggedInUsername)) {
        qDebug() << "Logged-in user is not an owner of the team.";
        return;
    }

    // Remove the team from the organization
    QJsonArray teamsArray = org.value("teams").toArray();
    for (int i = 0; i < teamsArray.size(); ++i) {
        if (teamsArray.at(i).toString() == teamName) {
            teamsArray.removeAt(i);
            break;
        }
    }
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

    // Check if the team exists in Team.json
    if (!jsonObjectTeam.contains(teamName)) {
        qDebug() << "Team does not exist in Team.json.";
        return;
    }

    // Remove the team from Team.json
    jsonObjectTeam.remove(teamName);

    jsonDocTeam.setObject(jsonObjectTeam);

    fileTeam.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileTeam.write(jsonDocTeam.toJson());
    fileTeam.close();

    qDebug() << "Team deleted successfully.";
}


void team_manager::addMemberToTeam(const QString& orgName, const QString& teamName, const QString& memberUsername) {
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
        qDebug() << "Organization does not exist in org.json.";
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    QJsonObject team = jsonObject.value(teamName).toObject();
    QString loggedInUsername = UserManager::getLoggedInUsername();
    QJsonArray headsArray = team.value("heads").toArray();
    if (!headsArray.contains(loggedInUsername)) {
        qDebug() << "Logged-in user is not an heads of the team.";
        return;
    }

    // Check if the team exists in the organization
    if (!org.contains("teams") || !org.value("teams").toArray().contains(teamName)) {
        qDebug() << "Team does not exist in the organization.";
        return;
    }

    // Check if the member is part of the organization
    if (!org.contains("members") || !org.value("members").toArray().contains(memberUsername)) {
        qDebug() << "Member does not exist in the organization.";
        return;
    }

    // Check if the logged-in user is trying to add themselves as a member
    if (loggedInUsername == memberUsername) {
        qDebug() << "Cannot add yourself as a member.";
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
        qDebug() << "Team does not exist in Team.json.";
        return;
    }

    //QJsonObject team = jsonObjectTeam.value(teamName).toObject();
    QJsonArray headsArrayTeam = team.value("headss").toArray();

    // Check if the logged-in user is an heads of the team
    if (!headsArrayTeam.contains(loggedInUsername)) {
        qDebug() << "Logged-in user is not an heads of the team.";
        return;
    }

    // Check if the member is already part of the team
    QJsonArray membersArray = team.value("members").toArray();
    if (membersArray.contains(memberUsername)) {
        qDebug() << "Member is already part of the team.";
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

    qDebug() << "Member added to the team successfully.";

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
    QJsonObject user = jsonObjecttext.value(memberUsername).toObject();

    // Correct the key name to "team"
    QJsonArray teamsArray = user.value("teams").toArray();
    teamsArray.append(teamName);
    user["teams"] = teamsArray;

    // Save the changes back to text.json
    jsonObjecttext[memberUsername] = user;
    jsonDoctext.setObject(jsonObjecttext);

    // Save the changes back to text.json
    filetext.open(QIODevice::WriteOnly | QIODevice::Truncate);
    filetext.write(QJsonDocument(jsonObjecttext).toJson());
    filetext.close();
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
        qDebug() << "Organization does not exist in org.json.";
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    QJsonObject team = jsonObject.value(teamName).toObject();
    QString loggedInUsername = UserManager::getLoggedInUsername();
    QJsonArray headsArray = team.value("heads").toArray();
    if (!headsArray.contains(loggedInUsername)) {
        qDebug() << "Logged-in user is not an heads of the team.";
        return;
    }

    // Check if the team exists in the organization
    if (!org.contains("teams") || !org.value("teams").toArray().contains(teamName)) {
        qDebug() << "Team does not exist in the organization.";
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
        qDebug() << "Team does not exist in Team.json.";
        return;
    }

    //QJsonObject team = jsonObjectTeam.value(teamName).toObject();
    QJsonArray headsArrayTeam = team.value("heads").toArray();

    // Check if the logged-in user is an heads of the team
    if (!headsArrayTeam.contains(loggedInUsername)) {
        qDebug() << "Logged-in user is not an heads of the team.";
        return;
    }

    // Check if the member is part of the team
    QJsonArray membersArray = team.value("members").toArray();
    if (!membersArray.contains(memberUsername)) {
        qDebug() << "Member is not part of the team.";
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

    qDebug() << "Member removed from the team successfully.";

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
        qDebug() << "Member does not exist in text.json.";
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

    qDebug() << "Member removed from the team in text.json successfully.";
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
        qDebug() << "Organization does not exist in org.json.";
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
        qDebug() << "Team does not exist in the organization.";
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
        qDebug() << "Team does not exist in Team.json.";
        return;
    }

    QJsonObject team = jsonObjectTeam.value(teamName).toObject();
    QJsonArray headsArray = team.value("heads").toArray();

    // Check if the head is part of the team
    if (!headsArray.contains(loggedInUsername)) {
        qDebug() << "username is not heed of the team.";
        return;
    }

    // Check if the member is part of the team
    QJsonArray membersArray = team.value("members").toArray();
    if (!membersArray.contains(memberUsername)) {
        qDebug() << "Member is not part of the team.";
        return;
    }

    // Check if the member is already a head of the team
    if (headsArray.contains(memberUsername)) {
        qDebug() << "Member is a head of the team.";
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

    qDebug() << "Member role changed to head in the team successfully.";

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
        qDebug() << "Organization does not exist in org.json.";
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    QString loggedInUsername = UserManager::getLoggedInUsername();


    // Check if the team exists in the organization
    if (!org.contains("teams") || !org.value("teams").toArray().contains(teamName)) {
        qDebug() << "Team does not exist in the organization.";
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
        qDebug() << "Team does not exist in Team.json.";
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
        qDebug() << "Logged-in user is not the owner of the team.";
        return;
    }
    // Check if the head is part of the team
    if (!headsArray.contains(loggedInUsername)) {
        qDebug() << "Username is not a head of the team.";
        return;
    }

    // Check if the member is part of the team
    QJsonArray membersArray = team.value("members").toArray();
    if (!membersArray.contains(memberUsername)) {
        qDebug() << "Member is not part of the team.";
        return;
    }

    // Check if the member is a head of the team
    if (!headsArray.contains(memberUsername)) {
        qDebug() << "Member is not a head of the team.";
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

    qDebug() << "Head role demoted to member in the team successfully.";
}
