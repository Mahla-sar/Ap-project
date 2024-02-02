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

void Task_manager::createTask(const QString& OrgName, const QString& taskName) {
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
        task["description"] = "";
        task["assignee Team"] = "";
        task["assignee Project"] = "";
        task["assignee Member"] = "";
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










//static void setDueDate(const QString& taskName, const QDateTime& dueDate) {
//        // Access task.json
//        QString currentDir = QCoreApplication::applicationDirPath();
//        QString filePath = currentDir + QDir::separator() + "task.json";

//        QFile file(filePath);
//        if (!file.open(QIODevice::ReadWrite)) {
//            qDebug() << "Failed to open task.json file.";
//            return;
//        }

//        QByteArray fileData = file.readAll();
//        file.close();

//        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
//        QJsonObject jsonObject = jsonDoc.object();

//        // Check if the task exists
//        if (!jsonObject.contains(taskName)) {
//            qDebug() << "Task does not exist in task.json.";
//            return;
//        }

//        // Update the due date of the task
//        QJsonObject task = jsonObject.value(taskName).toObject();
//        task["dueDate"] = dueDate.toString(Qt::ISODate);

//        // Save the changes back to task.json
//        jsonObject[taskName] = task;
//        jsonDoc.setObject(jsonObject);

//        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
//        file.write(jsonDoc.toJson());
//        file.close();

//        qDebug() << "Due date set successfully.";
//    }
