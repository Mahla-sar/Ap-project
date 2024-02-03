#include "task_manager.h"
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
#include "team_manager.h"

void Task_manager::createTask(const QString& OrgName, const QString& taskName , const QString& description) {
        // Access task.json
        QString currentDir = QCoreApplication::applicationDirPath();
        QString filePath = currentDir + QDir::separator() + "task.json";

        QFile file(filePath);
        if (!file.open(QIODevice::ReadWrite)) {
            qDebug() << "Failed to open task.json file.";
            return;
        }

        QByteArray fileData = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
        QJsonObject jsonObject = jsonDoc.object();

        // Check if the task already exists
        if (jsonObject.contains(taskName)) {
            qDebug() << "Task already exists in task.json.";
            return;
        }

        // Create task object
        QJsonObject task;
        task["name"] = taskName;
        task["description"] = description;
        task["assignee Team"] = "";
        task["assignee Project"] = "";
        task["assignee Member"] = QJsonArray();
        task["Archive"] = bool(false);
        task["organization"] = OrgName;
        QString loggedInUsername = UserManager::getLoggedInUsername();
        task["owner"] = loggedInUsername;
        task["DueDate"] = "";
        // Add the task to task.json
        jsonObject[taskName] = task;
        jsonDoc.setObject(jsonObject);

        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        file.write(jsonDoc.toJson());
        file.close();

        // Access org.json
        QString orgFilePath = currentDir + QDir::separator() + "org.json";

        QFile orgFile(orgFilePath);
        if (!orgFile.open(QIODevice::ReadWrite)) {
            qDebug() << "Failed to open org.json file.";
            return;
        }

        QByteArray orgFileData = orgFile.readAll();
        orgFile.close();

        QJsonDocument orgJsonDoc = QJsonDocument::fromJson(orgFileData);
        QJsonObject orgJsonObject = orgJsonDoc.object();

        // Check if the organization exists
        if (!orgJsonObject.contains(OrgName)) {
            qDebug() << "Organization does not exist in org.json.";
            return;
        }

        // Add task name to tasks in the organization
        QJsonObject org = orgJsonObject.value(OrgName).toObject();
        QJsonArray tasksArray = org.value("tasks").toArray();
        tasksArray.append(taskName);
        org["tasks"] = tasksArray;

        // Save the changes back to org.json
        orgJsonObject[OrgName] = org;
        orgJsonDoc.setObject(orgJsonObject);

        orgFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
        orgFile.write(orgJsonDoc.toJson());
        orgFile.close();



        qDebug() << "Task created successfully.";
}



void Task_manager::deleteTask(const QString& OrgName, const QString& taskName) {
    // Access task.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "task.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open task.json file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    // Check if the task exists
    if (!jsonObject.contains(taskName)) {
        qDebug() << "Task does not exist in task.json.";
        return;
    }

    // Remove task from task.json
    jsonObject.remove(taskName);
    jsonDoc.setObject(jsonObject);

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(jsonDoc.toJson());
    file.close();

    // Access org.json
    QString orgFilePath = currentDir + QDir::separator() + "org.json";

    QFile orgFile(orgFilePath);
    if (!orgFile.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open org.json file.";
        return;
    }

    QByteArray orgFileData = orgFile.readAll();
    orgFile.close();

    QJsonDocument orgJsonDoc = QJsonDocument::fromJson(orgFileData);
    QJsonObject orgJsonObject = orgJsonDoc.object();

    // Check if the organization exists
    if (!orgJsonObject.contains(OrgName)) {
        qDebug() << "Organization does not exist in org.json.";
        return;
    }

    // Remove task name from tasks in the organization
    QJsonObject org = orgJsonObject.value(OrgName).toObject();
    QJsonArray tasksArray = org.value("tasks").toArray();
//    tasksArray.removeOne(taskName);
    for (int i = 0; i < tasksArray.size(); ++i) {
        if (tasksArray.at(i).toString() == taskName) {
            tasksArray.removeAt(i);
            break;
        }
    }
    org["tasks"] = tasksArray;

    // Save the changes back to org.json
    orgJsonObject[OrgName] = org;
    orgJsonDoc.setObject(orgJsonObject);

    orgFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    orgFile.write(orgJsonDoc.toJson());
    orgFile.close();

    qDebug() << "Task deleted successfully and removed from organization tasks.";
}

bool Task_manager::isTaskArchived(const QString& taskName) {
    // Access task.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "task.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open task.json file.";
        return false;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    // Check if the task exists
    if (!jsonObject.contains(taskName)) {
        qDebug() << "Task does not exist in task.json.";
        return false;
    }

    // Check if the task is archived
    QJsonObject task = jsonObject.value(taskName).toObject();
    qDebug() << task["Archive"].toBool();
    return task["Archive"].toBool();
}


void Task_manager::archiveTask(const QString& taskName) {
    // Access task.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "task.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open task.json file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    // Check if the task exists
    if (!jsonObject.contains(taskName)) {
        qDebug() << "Task does not exist in task.json.";
        return;
    }

    // Check if the task is already archived
    QJsonObject task = jsonObject.value(taskName).toObject();
    if (task["Archive"].toBool()) {
        qDebug() << "Task is already archived.";
        return;
    }

    // Archive the task
    task["Archive"] = true;

    // Save the changes back to task.json
    jsonObject[taskName] = task;
    jsonDoc.setObject(jsonObject);

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(jsonDoc.toJson());
    file.close();

    qDebug() << "Task archived successfully.";
}

void Task_manager::unarchiveTask(const QString& taskName) {
    // Access task.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "task.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open task.json file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    // Check if the task exists
    if (!jsonObject.contains(taskName)) {
        qDebug() << "Task does not exist in task.json.";
        return;
    }

    // Check if the task is already unarchived
    QJsonObject task = jsonObject.value(taskName).toObject();
    if (!task["Archive"].toBool()) {
        qDebug() << "Task is not archived.";
        return;
    }

    // Unarchive the task
    task["Archive"] = false;

    // Save the changes back to task.json
    jsonObject[taskName] = task;
    jsonDoc.setObject(jsonObject);

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(jsonDoc.toJson());
    file.close();

    qDebug() << "Task unarchived successfully.";
}



void Task_manager::assignTaskToMember(const QString& taskName, const QString& memberUsername) {
    // Access task.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "task.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open task.json file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    // Check if the task exists
    if (!jsonObject.contains(taskName)) {
        qDebug() << "Task does not exist in task.json.";
        return;
    }

    // Retrieve the task object
    QJsonObject task = jsonObject.value(taskName).toObject();

    QString ownerUsername = task.value("owner").toString();
    QString loggedInUsername = UserManager::getLoggedInUsername();

    if (loggedInUsername != ownerUsername) {
        QMessageBox::warning(nullptr, "demote member", "Logged-in user is not the owner of the task.");
        return;
    }

    // Assign the task to the specified member
    QJsonArray membersArray = task["assignee Member"].toArray();

    // Check if the member is not already assigned
    if (!membersArray.contains(memberUsername)) {
        membersArray.append(memberUsername);
    }

    // Update the task object with the new member
    task["assignee Member"] = membersArray;

    // Save the changes back to task.json
    jsonObject[taskName] = task;
    jsonDoc.setObject(jsonObject);

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(jsonDoc.toJson());
    file.close();



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

    if (!usersJsonObject.contains(memberUsername)) {
        qDebug() << "User does not exist in users.json.";
        //QMessageBox::warning(this, "Add Member", "User does not exist.");
        return;
    }

    QJsonObject user = usersJsonObject.value(memberUsername).toObject();
    QJsonArray tasksArray = user.value("tasks").toArray();
    if (tasksArray.contains(taskName)){
        qDebug() << "Member is already part of the task";
        return;}

    tasksArray.append(taskName);
    user["tasks"] = tasksArray;
    usersJsonObject[memberUsername] = user;

    // Save the changes back to users.json
    QJsonDocument updatedUsersJsonDoc(usersJsonObject);

    usersFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    usersFile.write(updatedUsersJsonDoc.toJson());
    usersFile.close();

    // Save the changes back to text.json
    QJsonDocument updatedJsonDoc(jsonObject);
//    QMessageBox::information(this, "Adding member", "member was added succesfully");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(updatedJsonDoc.toJson());
    file.close();
    qDebug() << "Task assigned to member successfully.";

}


void Task_manager::assignTaskToTeam(const QString& taskName, const QString& teamName) {
    // Access task.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "task.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open task.json file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    // Check if the task exists
    if (!jsonObject.contains(taskName)) {
        qDebug() << "Task does not exist in task.json.";
        return;
    }

    // Retrieve the task object
    QJsonObject task = jsonObject.value(taskName).toObject();

    QString ownerUsername = task.value("owner").toString();
    QString loggedInUsername = UserManager::getLoggedInUsername();

    if (loggedInUsername != ownerUsername) {
        QMessageBox::warning(nullptr, "assign task to team", "Logged-in user is not the owner of the task.");
        return;
    }

    // Assign the task to the specified team
    task["assignee Team"] = teamName;

    // Save the changes back to task.json
    jsonObject[taskName] = task;
    jsonDoc.setObject(jsonObject);

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(jsonDoc.toJson());
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
        QMessageBox::warning(nullptr, "Promot member", "Team does not exist in Team.json.");
        return;
    }

    QJsonObject team = jsonObjectTeam.value(teamName).toObject();
    QJsonArray tasksArray = team.value("tasks").toArray();



    // Check if the member is already a head of the team
    if (tasksArray.contains(taskName)) {
        QMessageBox::warning(nullptr, " ","Team is already in task");
        return;
    }
    // Add the heads to the team
    tasksArray.append(taskName);
    team["tasks"] = tasksArray;

    // Save the changes back to Team.json
    jsonObjectTeam[teamName] = team;
    jsonDocTeam.setObject(jsonObjectTeam);

    fileTeam.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileTeam.write(jsonDocTeam.toJson());
    fileTeam.close();

    QMessageBox::information(nullptr, "","successfully.");
    qDebug() << "successfully.";
}

void Task_manager::assignTaskToProject(const QString& taskName, const QString& projectName) {
    // Access task.json
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "task.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open task.json file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObject = jsonDoc.object();

    // Check if the task exists
    if (!jsonObject.contains(taskName)) {
        qDebug() << "Task does not exist in task.json.";
        return;
    }

    // Retrieve the task object
    QJsonObject task = jsonObject.value(taskName).toObject();

    QString ownerUsername = task.value("owner").toString();
    QString loggedInUsername = UserManager::getLoggedInUsername();

    if (loggedInUsername != ownerUsername) {
        QMessageBox::warning(nullptr, "assign task to project", "Logged-in user is not the owner of the task.");
        return;
    }

    // Assign the task to the specified project
    task["assignee Project"] = projectName;

    // Save the changes back to task.json
    jsonObject[taskName] = task;
    jsonDoc.setObject(jsonObject);

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(jsonDoc.toJson());
    file.close();

    // Access Project.json
    QString currentDirProject = QCoreApplication::applicationDirPath();
    QString filePathProject = currentDirProject + QDir::separator() + "Project.json";

    QFile fileProject(filePathProject);
    if (!fileProject.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open Project.json file.";
        return;
    }

    QByteArray fileDataProject = fileProject.readAll();
    fileProject.close();

    QJsonDocument jsonDocProject = QJsonDocument::fromJson(fileDataProject);
    QJsonObject jsonObjectProject = jsonDocProject.object();



    QJsonObject Project = jsonObjectProject.value(projectName).toObject();
    QJsonArray tasksArray = Project.value("tasks").toArray();



    // Check if the member is already a head of the Project
    if (tasksArray.contains(taskName)) {
        QMessageBox::warning(nullptr, " ","Project is already in task");
        return;
    }
    // Add the heads to the Project
    tasksArray.append(taskName);
    Project["tasks"] = tasksArray;

    // Save the changes back to Project.json
    jsonObjectProject[projectName] = Project;
    jsonDocProject.setObject(jsonObjectProject);

    fileProject.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileProject.write(jsonDocProject.toJson());
    fileProject.close();

    QMessageBox::information(nullptr, "","successfully.");
    qDebug() << "successfully.";
    qDebug() << "Task assigned to project successfully.";
}



    void Task_manager::setDueDate(const QString& taskName, const QString& dueDate) {
        // Access task.json
        QString currentDir = QCoreApplication::applicationDirPath();
        QString filePath = currentDir + QDir::separator() + "task.json";

        QFile file(filePath);
        if (!file.open(QIODevice::ReadWrite)) {
            qDebug() << "Failed to open task.json file.";
            return;
        }

        QByteArray fileData = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
        QJsonObject jsonObject = jsonDoc.object();

        // Check if the task exists
        if (!jsonObject.contains(taskName)) {
            qDebug() << "Task does not exist in task.json.";
            return;
        }
        QJsonObject task = jsonObject.value(taskName).toObject();

        QString ownerUsername = task.value("owner").toString();
        QString loggedInUsername = UserManager::getLoggedInUsername();

        if (loggedInUsername != ownerUsername) {
            QMessageBox::warning(nullptr, "demote member", "Logged-in user is not the owner of the task.");
            return;
        }
        // Update the due date of the task
        task["dueDate"] = dueDate;

        // Save the changes back to task.json
        jsonObject[taskName] = task;
        jsonDoc.setObject(jsonObject);

        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        file.write(jsonDoc.toJson());
        file.close();

        qDebug() << "Due date set successfully.";
    }

    QString Task_manager::getDueDate(const QString& taskName) {
        // Access task.json
        QString currentDir = QCoreApplication::applicationDirPath();
        QString filePath = currentDir + QDir::separator() + "task.json";

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open task.json file for reading.";
            return QString();
        }

        QByteArray fileData = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
        QJsonObject jsonObject = jsonDoc.object();

        // Check if the task exists
        if (!jsonObject.contains(taskName)) {
            qDebug() << "Task does not exist in task.json.";
            return QString();
        }

        // Retrieve the task object
        QJsonObject task = jsonObject.value(taskName).toObject();

        // Check if the task has a due date
        if (task.contains("dueDate")) {
            qDebug() << task.value("dueDate").toString();
            return task.value("dueDate").toString();

        } else {
            qDebug() << "Task does not have a due date.";
            return QString(); //
        }
    }


    void Task_manager::addCommentToTask(const QString& taskName, const QString& commentText) {
        // Access task.json
        QString currentDir = QCoreApplication::applicationDirPath();
        QString filePath = currentDir + QDir::separator() + "task.json";

        QFile file(filePath);
        if (!file.open(QIODevice::ReadWrite)) {
            qDebug() << "Failed to open task.json file.";
            return;
        }

        QByteArray fileData = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
        QJsonObject jsonObject = jsonDoc.object();

        // Check if the task exists
        if (!jsonObject.contains(taskName)) {
            qDebug() << "Task does not exist in task.json.";
            return;
        }

        // Get the task object
        QJsonObject task = jsonObject.value(taskName).toObject();

        // Create a new comment object
        QJsonArray commentsArray = task.value("comments").toArray();
        QJsonObject newComment;
        QString loggedInUsername = UserManager::getLoggedInUsername();

        newComment[loggedInUsername] = commentText;
        //newComment["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);

        // Add the new comment to the comments array
        commentsArray.append(newComment);
        task["comments"] = commentsArray;

        // Save the changes back to task.json
        jsonObject[taskName] = task;
        jsonDoc.setObject(jsonObject);

        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        file.write(jsonDoc.toJson());
        file.close();

        qDebug() << "Comment added to the task successfully.";
    }
    void Task_manager::deleteCommentFromTask(const QString& taskName, const QString& username, const QString& commentText) {
        QString currentDir = QCoreApplication::applicationDirPath();
        QString filePath = currentDir + QDir::separator() + "task.json";

        QFile file(filePath);
        if (!file.open(QIODevice::ReadWrite)) {
            qDebug() << "Failed to open task.json file.";
            return;
        }

        QByteArray fileData = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
        QJsonObject jsonObject = jsonDoc.object();

        // Check if the task exists
        if (!jsonObject.contains(taskName)) {
            qDebug() << "Task does not exist in task.json.";
            return;
        }

        // Get the task object
        QJsonObject task = jsonObject.value(taskName).toObject();

        // Check if the task has comments
        if (!task.contains("comments")) {
            qDebug() << "No comments found for the task.";
            return;
        }

        // Get the comments array
        QJsonArray commentsArray = task.value("comments").toArray();

        // Find and remove the comment with the specified username and comment text
        for (int i = 0; i < commentsArray.size(); ++i) {
            QJsonObject comment = commentsArray[i].toObject();
            if (comment.contains(username) && comment.value(username).toString() == commentText) {
                commentsArray.removeAt(i);
                qDebug() << "Comment deleted from the task successfully.";
                break; // Assuming only one comment with the matching text per user can exist, remove the break if multiple comments with the same text per user are allowed
            }
        }

        // Update the comments array in the task object
        task["comments"] = commentsArray;

        // Update the task object in the JSON
        jsonObject[taskName] = task;
        jsonDoc.setObject(jsonObject);

        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        file.write(jsonDoc.toJson());
        file.close();
    }

    QVector<QString> Task_manager::taskNamesSorted(const QJsonObject& taskJsonObject) {
        QVector<QString> taskNames;

        // Iterate through the taskanization names and add them to the list
        for (auto it = taskJsonObject.begin(); it != taskJsonObject.end(); ++it) {
            taskNames.append(it.key());
        }

        // Sort the list alphabetically
        taskNames.sort();

        return taskNames;
    }



    QVector<QString> Task_manager::sorttasksByTime(const QJsonObject& taskJsonObject) {
        QVector<QString> taskNamesSortedByTime;

        // Create a vector to store pairs of time and taskanization name
        QVector<QPair<QString, QString>> taskTimePairs;

        // Iterate through the taskanizations and extract the date strings and taskanization names
        for (auto it = taskJsonObject.begin(); it != taskJsonObject.end(); ++it) {
            QJsonObject taskObject = it.value().toObject();
            QString timeToBuildString = taskObject["dueDate"].toString();
            QString taskName = it.key();

            // Add the pair of time and taskanization name to the vector
            taskTimePairs.append(qMakePair(timeToBuildString, taskName));
        }

        // Sort the vector based on time strings
        std::sort(taskTimePairs.begin(), taskTimePairs.end(), [](const QPair<QString, QString>& a, const QPair<QString, QString>& b) {
            return a.first < b.first; // Compare time strings
        });

        // Extract the taskanization names from the sorted pairs
        for (const auto& pair : taskTimePairs) {
            taskNamesSortedByTime.append(pair.second);
        }

        qDebug() << taskNamesSortedByTime;

        return taskNamesSortedByTime;
    }

