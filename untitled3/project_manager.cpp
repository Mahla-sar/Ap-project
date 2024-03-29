#include "project_manager.h"
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
#include "project_manager.h"

QString Project_manager::ProjectName ;

QString Project_manager::get_project() {
    return ProjectName;
}
void Project_manager::setproject(const QString &project_name) {
    ProjectName = project_name;
}


void Project_manager::createproject(const QString& orgName, const QString& projectName) {
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

    // Check if the project already exists
    if (org.contains("projects") && org.value("projects").toArray().contains(projectName)) {
        QMessageBox::warning(nullptr, "Creat project", "project already exists in the organization.");
        return;
    }
    //
    QString loggedInUsername = UserManager::getLoggedInUsername();

    QJsonArray adminsArray = org.value("admins").toArray();

    // Check if the logged-in user is an admin of the organization
    if (!adminsArray.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "creat project", "Logged-in user is not an admin of the organization.");
        return;
    }
    QJsonArray projectsArray = org.value("projects").toArray();


    // Add the member to the organization
    projectsArray.append(projectName);
    org["projects"] = projectsArray;

    // Save the changes back to org.json
    jsonObject[orgName] = org;  // Update the organization object in the main JSON object

    QString currentDirproject = QCoreApplication::applicationDirPath();
    QString filePathproject = currentDirproject + QDir::separator() + "project.json";

    QFile fileproject(filePathproject);
    if (!fileproject.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(nullptr, "creat project", "Failed to open project.json file.");
        return;
    }

    QByteArray fileDataproject = fileproject.readAll();
    fileproject.close();

    QJsonDocument jsonDocproject = QJsonDocument::fromJson(fileDataproject);
    QJsonObject project;
    project["name"] = projectName;
    ProjectName = projectName;
    project["members"] = QJsonArray();
    project["heads"] = QJsonArray();
    project["organization"] = orgName;  // Set the organization name for the project
    // Add loggedInUsername to members
    QDateTime currentDateTime = QDateTime::currentDateTime();
    project["time to build"] = currentDateTime.toString();

    QJsonArray membersArray = project["members"].toArray();
    membersArray.append(loggedInUsername);
    project["members"] = membersArray;

    // Add loggedInUsername to heads
    QJsonArray headsArrayproject = project["heads"].toArray();
    headsArrayproject.append(loggedInUsername);
    project["heads"] = headsArrayproject;

    project["owner"] = loggedInUsername ;
    project["state"] = "undone";

    QJsonObject jsonObjectproject = jsonDocproject.object();
    if (projectName.isEmpty() || jsonObjectproject.contains(projectName)) {
        QMessageBox::warning(nullptr, "creat project", "project name is empty or already exists.");
        return;
    }

    jsonObjectproject[projectName] = project;
    jsonDocproject.setObject(jsonObjectproject);

    fileproject.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileproject.write(jsonDocproject.toJson());
    fileproject.close();

    // Save the changes back to org.json
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(QJsonDocument(jsonObject).toJson());
    file.close();

    QMessageBox::information(nullptr, "creat project", "project created successfully.");
    QString currentDirtext = QCoreApplication::applicationDirPath();
    QString filePathtext = currentDirtext + QDir::separator() + "text.json";
    QFile filetext(filePathtext);
    if (!filetext.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(nullptr, "creat project", "Failed to open file.");
        return;
    }

    QByteArray fileDatatext = filetext.readAll();
    filetext.close();

    QJsonDocument jsonDoctext = QJsonDocument::fromJson(fileDatatext);

    // Adding name to project
    QJsonObject jsonObjecttext = jsonDoctext.object();
    QJsonObject user = jsonObjecttext.value(loggedInUsername).toObject();

    // Correct the key name to "project"
    QJsonArray projectArray = user.value("projects").toArray();
    projectArray.append(projectName);
    user["projects"] = projectArray;

    // Save the changes back to text.json
    jsonObjecttext[loggedInUsername] = user;
    jsonDoctext.setObject(jsonObjecttext);

    // Save the changes back to text.json
    filetext.open(QIODevice::WriteOnly | QIODevice::Truncate);
    filetext.write(QJsonDocument(jsonObjecttext).toJson());
    filetext.close();
}

void Project_manager::renameproject(const QString& orgName, const QString& oldprojectName, const QString& newprojectName) {
    // Access org.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "org.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(nullptr, "rename project", "Failed to open org.json file.");

        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    // Check if the organization exists
    if (!jsonObject.contains(orgName)) {
        QMessageBox::warning(nullptr, "Rename project", "Organization does not exist in org.json.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    // Check if the project exists in the organization
    QJsonArray projectsArray = org.value("projects").toArray();
    if (!projectsArray.contains(oldprojectName)) {
        QMessageBox::warning(nullptr, "Rename project", "project does not exist in the organization.");
        return;
    }

    // Check if the logged-in user is an admin of the organization
    QString loggedInUsername = UserManager::getLoggedInUsername();
    QJsonArray adminsArray = org.value("admins").toArray();
    if (!adminsArray.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "Rename project", "Logged-in user is not an admin of the organization.");
        return;
    }

    // Access project.json
    QString currentDirproject = QCoreApplication::applicationDirPath();
    QString filePathproject = currentDirproject + QDir::separator() + "project.json";

    QFile fileproject(filePathproject);
    if (!fileproject.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open project.json file.";
        return;
    }

    QByteArray fileDataproject = fileproject.readAll();
    fileproject.close();

    QJsonDocument jsonDocproject = QJsonDocument::fromJson(fileDataproject);
    QJsonObject jsonObjectproject = jsonDocproject.object();

    // Check if the project exists in project.json
    if (!jsonObjectproject.contains(oldprojectName)) {
        QMessageBox::warning(nullptr, "Rename project", "project does not exist in project.json.");
        return;
    }

    QJsonObject project = jsonObjectproject.value(oldprojectName).toObject();

    // Update the project name
    project["name"] = newprojectName;

    // Update the project name in project.json
    jsonObjectproject.remove(oldprojectName);  // Remove the old project name
    jsonObjectproject[newprojectName] = project;  // Add the project with the new name
    jsonDocproject.setObject(jsonObjectproject);

    fileproject.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileproject.write(jsonDocproject.toJson());
    fileproject.close();

    // Update the project name in the organization
    //    projectsArray.removeOne(oldprojectName);
    for (int i = 0; i < projectsArray.size(); ++i) {
        if (projectsArray.at(i).toString() == oldprojectName) {
            projectsArray[i] = newprojectName;
            break;
        }
    }
    //projectsArray.append(newprojectName);
    org["projects"] = projectsArray;

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

    // Update the project name in the user's project list
    QJsonObject jsonObjecttext = jsonDoctext.object();
    if (!jsonObjecttext.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "Rename project", "User not found in text.json.");
        return;
    }

    QJsonObject user = jsonObjecttext.value(loggedInUsername).toObject();
    QJsonValue projectsValue = user.value("projects");

    if (!projectsValue.isArray()) {
        QMessageBox::warning(nullptr, "Rename project", "projects list is not an array for the logged-in user.");
        return;
    }

    QJsonArray projectArray = projectsValue.toArray();

    // Replace the old project name with the new one
    for (int i = 0; i < projectArray.size(); ++i) {
        if (projectArray.at(i).toString() == oldprojectName) {
            projectArray[i] = newprojectName;
            break;
        }
    }
    user["projects"] = projectArray;
    QMessageBox::information(nullptr, "Rename project", "project's name has been changed succesfully");

    // Save the changes back to text.json
    jsonObjecttext[loggedInUsername] = user;
    jsonDoctext.setObject(jsonObjecttext);
    //QMessageBox::information(this, "Changing organization's name", "organization's name changed successfully");
    filetext.open(QIODevice::WriteOnly | QIODevice::Truncate);
    filetext.write(jsonDoctext.toJson());
    filetext.close();



    qDebug() << "project name changed successfully.";
}


void Project_manager::deleteproject(const QString& orgName, const QString& projectName) {
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
        QMessageBox::warning(nullptr, "Delete project", "Organization does not exist in org.json.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();

    // Check if the project exists in the organization
    if (!org.contains("projects") || !org.value("projects").toArray().contains(projectName)) {
        QMessageBox::warning(nullptr, "Delete project", "project does not exist in the organization.");
        return;
    }

    // Check if the logged-in user is an owner of the project
    QString loggedInUsername = UserManager::getLoggedInUsername();

    // Remove the project from the organization
    QJsonArray projectsArray = org.value("projects").toArray();
    for (int i = 0; i < projectsArray.size(); ++i) {
        if (projectsArray.at(i).toString() == projectName) {
            projectsArray.removeAt(i);
            break;
        }
    }
    org["projects"] = projectsArray;

    // Save the changes back to org.json
    jsonObject[orgName] = org;

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(QJsonDocument(jsonObject).toJson());
    file.close();

    // Access project.json
    QString currentDirproject = QCoreApplication::applicationDirPath();
    QString filePathproject = currentDirproject + QDir::separator() + "project.json";

    QFile fileproject(filePathproject);
    if (!fileproject.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open project.json file.";
        return;
    }

    QByteArray fileDataproject = fileproject.readAll();
    fileproject.close();

    QJsonDocument jsonDocproject = QJsonDocument::fromJson(fileDataproject);
    QJsonObject jsonObjectproject = jsonDocproject.object();

    // Check if the project exists in project.json
    if (!jsonObjectproject.contains(projectName)) {
        qDebug() << "project does not exist in project.json.";
        return;
    }
    QJsonObject project = jsonObjectproject.value(projectName).toObject();

    QString ownerstr = project.value("owner").toString();
    if (!ownerstr.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "Delete project", "Logged-in user is not an owner of the project.");
        return;
    }
    // Remove the project from project.json
    jsonObjectproject.remove(projectName);

    jsonDocproject.setObject(jsonObjectproject);

    fileproject.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileproject.write(jsonDocproject.toJson());
    fileproject.close();

    QMessageBox::information(nullptr, "Delete project", "project deleted successfully.");
}


void Project_manager::addMemberToproject(const QString& orgName, const QString& projectName, const QString& memberUsername) {
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

    QString loggedInUsername = UserManager::getLoggedInUsername();



    // Check if the project exists in the organization
    if (!org.contains("projects") || !org.value("projects").toArray().contains(projectName)) {
        QMessageBox::warning(nullptr, "Add member", "project does not exist in the organization.");
        return;
    }

    // Check if the member is part of the organization
    if (!org.contains("members") || !org.value("members").toArray().contains(memberUsername)) {
        QMessageBox::warning(nullptr, "Add member", "Member does not exist in the organization.");
        return;
    }

    // Check if the logged-in user is trying to add themselves as a member
    if (loggedInUsername == memberUsername) {
        QMessageBox::warning(nullptr, "Add member", "Cannot add yourself as a member.");
        return;
    }

    // Access project.json
    QString currentDirproject = QCoreApplication::applicationDirPath();
    QString filePathproject = currentDirproject + QDir::separator() + "project.json";

    QFile fileproject(filePathproject);
    if (!fileproject.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(nullptr, "Add member", "Failed to open project.json file.");
        return;
    }

    QByteArray fileDataproject = fileproject.readAll();
    fileproject.close();

    QJsonDocument jsonDocproject = QJsonDocument::fromJson(fileDataproject);
    QJsonObject jsonObjectproject = jsonDocproject.object();

    // Check if the project exists in project.json
    if (!jsonObjectproject.contains(projectName)) {
        QMessageBox::warning(nullptr, "Add member", "project does not exist in project.json.");
        return;
    }
    //QJsonObject project = jsonObject.value(projectName).toObject();
    QJsonObject project = jsonObjectproject.value(projectName).toObject();

    QJsonArray headsArrayProject = project.value("heads").toArray();
    if (!headsArrayProject.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "Add member","Logged-in user is not a head of the project.");
        return;
    }

    // Check if the member is already part of the project
    QJsonArray membersArray = project.value("members").toArray();
    if (membersArray.contains(memberUsername)) {
        QMessageBox::warning(nullptr, "Add member", "Member is already part of the project.");
        return;
    }

    // Add the member to the project
    membersArray.append(memberUsername);
    project["members"] = membersArray;

    // Save the changes back to project.json
    jsonObjectproject[projectName] = project;
    jsonDocproject.setObject(jsonObjectproject);

    fileproject.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileproject.write(jsonDocproject.toJson());
    fileproject.close();


    QString currentDirtext = QCoreApplication::applicationDirPath();
    QString filePathtext = currentDirtext + QDir::separator() + "text.json";
    QFile filetext(filePathtext);
    if (!filetext.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(nullptr, "Add member", "Failed to open text.json file.");
        return;
    }

    QByteArray fileDatatext = filetext.readAll();
    filetext.close();

    QJsonDocument jsonDoctext = QJsonDocument::fromJson(fileDatatext);

    // Adding name to project
    QJsonObject jsonObjecttext = jsonDoctext.object();
    QJsonObject user = jsonObjecttext.value(memberUsername).toObject();

    // Correct the key name to "project"
    QJsonArray projectsArray = user.value("projects").toArray();
    projectsArray.append(projectName);
    user["projects"] = projectsArray;

    // Save the changes back to text.json
    jsonObjecttext[memberUsername] = user;
    jsonDoctext.setObject(jsonObjecttext);

    // Save the changes back to text.json
    filetext.open(QIODevice::WriteOnly | QIODevice::Truncate);
    filetext.write(QJsonDocument(jsonObjecttext).toJson());
    filetext.close();
    QMessageBox::information(nullptr, "Add member", "Member added to the project successfully.");

}


void Project_manager::removeMemberFromproject(const QString& orgName, const QString& projectName, const QString& memberUsername) {
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
        QMessageBox::warning(nullptr, "Remove member", "Organization does not exist in org.json.");
        return;
    }

    QJsonObject org = jsonObject.value(orgName).toObject();


    // Check if the project exists in the organization
    if (!org.contains("projects") || !org.value("projects").toArray().contains(projectName)) {
        QMessageBox::warning(nullptr, "Remove member", "project does not exist in the organization.");
        return;
    }

    // Access project.json
    QString currentDirproject = QCoreApplication::applicationDirPath();
    QString filePathproject = currentDirproject + QDir::separator() + "project.json";

    QFile fileproject(filePathproject);
    if (!fileproject.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(nullptr, "Add member", "Failed to open project.json file.");
        return;
    }

    QByteArray fileDataproject = fileproject.readAll();
    fileproject.close();

    QJsonDocument jsonDocproject = QJsonDocument::fromJson(fileDataproject);
    QJsonObject jsonObjectproject = jsonDocproject.object();

    // Check if the project exists in project.json
    if (!jsonObjectproject.contains(projectName)) {
        QMessageBox::warning(nullptr, "Remove member", "project does not exist in the organization.");
        return;
    }

    QJsonObject project = jsonObjectproject.value(projectName).toObject();

    //QJsonObject project = jsonObject.value(projectName).toObject();
    QString loggedInUsername = UserManager::getLoggedInUsername();
    QJsonArray headsArray = project.value("heads").toArray();
    if (!headsArray.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "Remove member", "Logged-in user is not an heads of the project.");
        return;
    }

    // Check if the member is part of the project
    QJsonArray membersArray = project.value("members").toArray();
    if (!membersArray.contains(memberUsername)) {
        QMessageBox::warning(nullptr, "Remove member", "Member is not part of the project.");
        return;
    }

    // Remove the member from the project
    for (int i = 0; i < membersArray.size(); ++i) {
        if (membersArray.at(i).toString() == memberUsername) {
            membersArray.removeAt(i);
            break;
        }
    }
    project["members"] = membersArray;

    // Save the changes back to project.json
    jsonObjectproject[projectName] = project;
    jsonDocproject.setObject(jsonObjectproject);

    fileproject.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileproject.write(jsonDocproject.toJson());
    fileproject.close();

    qDebug() << "Member removed from the project successfully.";

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
        QMessageBox::warning(nullptr, "Remove member", "Member does not exist in text.json.");
        return;
    }

    // Remove the project from the member's projects list
    QJsonObject user = jsonObjecttext.value(memberUsername).toObject();
    QJsonArray projectsArray = user.value("projects").toArray();
    for (int i = 0; i < projectsArray.size(); ++i) {
        if (projectsArray.at(i).toString() == projectName) {
            projectsArray.removeAt(i);
            break;
        }
    }    user["projects"] = projectsArray;

    // Save the changes back to text.json
    jsonObjecttext[memberUsername] = user;
    jsonDoctext.setObject(jsonObjecttext);

    filetext.open(QIODevice::WriteOnly | QIODevice::Truncate);
    filetext.write(jsonDoctext.toJson());
    filetext.close();

    QMessageBox::information(nullptr, "Remove member", "Member removed from the project in text.json successfully.");
}

void Project_manager::updateProjectState(const QString& orgName, const QString& projectName, const QString& newState) {
    // Access project.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "project.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(nullptr, "Project State", "Failed to open project.json file.");
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    // Check if the project exists
    if (!jsonObject.contains(projectName)) {
        QMessageBox::warning(nullptr, "Project State", "Project does not exist in project.json.");
        return;
    }

    QJsonObject project = jsonObject.value(projectName).toObject();

    // Check if the logged-in user has the authority to update the project state
    QString loggedInUsername = UserManager::getLoggedInUsername();
    QJsonArray headsArray = project.value("heads").toArray();
    if (!headsArray.contains(loggedInUsername)) {
        QMessageBox::warning(nullptr, "Project State" ,"Logged-in user is not a head of the project.");
        return;
    }

    // Update the project state
    project["state"] = newState;

    // Save the changes back to project.json
    jsonObject[projectName] = project;  // Update the project object in the main JSON object
    jsonDoc.setObject(jsonObject);

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(jsonDoc.toJson());
    file.close();
    QMessageBox::warning(nullptr, "Project State" ,"Project state updated successfully.");

}

bool Project_manager::is_doneProject(const QString& projectName) {
    // Access project.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "project.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "is done project" ,"Failed to open project.json file.");
        return false;  // Assuming "undone" as default if the file cannot be opened
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    // Check if the project exists
    if (!jsonObject.contains(projectName)) {
        QMessageBox::warning(nullptr, "is done project" ,"Failed to open project.json file.");
        return false;
    }

    QJsonObject project = jsonObject.value(projectName).toObject();

    // Check the project state
    QString projectState = project.value("state").toString();
    return (projectState.toLower() == "done");
}
QVector<QString> Project_manager::projectNamesSorted(const QJsonObject& projectJsonObject) {
    QVector<QString> projectNames;

    // Iterate through the projectanization names and add them to the list
    for (auto it = projectJsonObject.begin(); it != projectJsonObject.end(); ++it) {
        projectNames.append(it.key());
    }

    // Sort the list alphabetically
    projectNames.sort();

    return projectNames;
}



QVector<QString> Project_manager::sortprojectsByTime(const QJsonObject& projectJsonObject) {
    QVector<QString> projectNamesSortedByTime;

    // Create a vector to store pairs of time and projectanization name
    QVector<QPair<QString, QString>> projectTimePairs;

    // Iterate through the projects and extract the date strings and project names
    for (auto it = projectJsonObject.begin(); it != projectJsonObject.end(); ++it) {
        QJsonObject projectObject = it.value().toObject();
        QString timeToBuildString = projectObject["time to build"].toString();
        QString projectName = it.key();

        // Add the pair of time and project name to the vector
        projectTimePairs.append(qMakePair(timeToBuildString, projectName));
    }

    // Sort the vector based on time strings
    std::sort(projectTimePairs.begin(), projectTimePairs.end(), [](const QPair<QString, QString>& a, const QPair<QString, QString>& b) {
        return a.first < b.first; // Compare time strings
    });

    // Extract the projectanization names from the sorted pairs
    for (const auto& pair : projectTimePairs) {
        projectNamesSortedByTime.append(pair.second);
    }

    qDebug() << projectNamesSortedByTime;

    return projectNamesSortedByTime;
}


