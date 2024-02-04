#include "archived_tasks.h"
#include "ui_archived_tasks.h"
#include "task_manager.h"
#include "org_manager.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QCheckBox>

Archived_tasks::Archived_tasks(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Archived_tasks)
{

    ui->setupUi(this);
    QString name = org_manager::get_organization();
    QString currentDirorg = QCoreApplication::applicationDirPath();
    QString filePathorg = currentDirorg + QDir::separator() + "org.json";
    QFile fileorg(filePathorg);
    if (!fileorg.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open file.";
        return;
    }

    QByteArray fileDataorg = fileorg.readAll();
    fileorg.close();

    QJsonDocument jsonDocorg = QJsonDocument::fromJson(fileDataorg);
    //QString loggedInUsername = UserManager::getLoggedInUsername();

    // Adding name to organization
    QJsonObject jsonObjectorg= jsonDocorg.object();
    QJsonObject org = jsonObjectorg.value(name).toObject();

    // Correct the key name to "organization"
    QJsonArray tasksArray = org.value("tasks").toArray();

    org["tasks"] = tasksArray;

    // Save the changes back to text.json
    jsonObjectorg[name] = org;
    jsonDocorg.setObject(jsonObjectorg);


    fileorg.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileorg.write(QJsonDocument(jsonObjectorg).toJson());
    fileorg.close();


    // Set up the container for buttons
    buttonContainer = new QWidget(this);
    QVBoxLayout *buttonLayoutteam = new QVBoxLayout(buttonContainer);
    ui->verticalLayout->addWidget(buttonContainer);

    for (int i = 0; i < tasksArray.size(); ++i) {
        QString currentDirtask = QCoreApplication::applicationDirPath();
        QString filePathtask= currentDirtask + QDir::separator() + "task.json";
        QFile filetask(filePathtask);
        if (!filetask.open(QIODevice::ReadWrite)) {
            qDebug() << "Failed to open file.";
            return;
        }

        QByteArray fileDatatask = filetask.readAll();
        filetask.close();

        QJsonDocument jsonDoctask = QJsonDocument::fromJson(fileDatatask);


        // Adding name to organization
        QJsonObject jsonObjecttask= jsonDoctask.object();
        QJsonObject task = jsonObjecttask.value(tasksArray[i].toString()).toObject();
        if(task["Archive"]==true){
            addlist(tasksArray[i].toString());
        }

    }


}
void Archived_tasks::addlist(QString name)
{
    QPushButton *button = new QPushButton(name, this);
    orgButtons.append(button);
    orgNames.append(name);

    // Create "Edit" and "Archive" buttons for each item

    QPushButton *unarchiveButton = new QPushButton("Unarchive", this);
    unarchiveButton->setFixedSize(QSize(70, 30));

    // Create a QLabel for due date
    ;

    // Fetch due time from task.json based on the task name

    QListWidgetItem *item = new QListWidgetItem(ui->archivedlist);
    item->setSizeHint(QSize(200, 50));  // Set the size of the item

    // create widget to hold buttons and due date label
    QWidget *buttonWidget = new QWidget(this);
    QHBoxLayout *buttonWidgetLayout = new QHBoxLayout(buttonWidget);
    buttonWidgetLayout->addWidget(button);

    buttonWidgetLayout->addWidget(unarchiveButton);


    // Set the widget as the item widget
    ui->archivedlist->setItemWidget(item, buttonWidget);


    connect(unarchiveButton, &QPushButton::clicked, [this, name]() {
        Task_manager my_task;
        my_task.unarchiveTask(name);
        emit task_unarchived(name);
        delete_task(name);
    });
}

void Archived_tasks::delete_task(QString name)
{
    for (int i = 0; i < orgNames.size(); ++i) {
        if (orgNames.at(i) == name) {
            // Remove button and name from lists
            QPushButton *buttonToRemove = orgButtons.at(i);
            orgButtons.removeAt(i);
            orgNames.removeAt(i);

            // Find and remove corresponding item from teamlist
            QListWidgetItem *itemToRemove = nullptr;
            for (int j = 0; j < ui->archivedlist->count(); ++j) {
                if (ui->archivedlist->itemWidget(ui->archivedlist->item(j))->layout()->indexOf(buttonToRemove) != -1) {
                    itemToRemove = ui->archivedlist->takeItem(j);
                    break;
                }
            }

            // Cleanup
            QString currentDir = QCoreApplication::applicationDirPath();
            QString filePath = currentDir + QDir::separator() + "task.json";

            QFile file(filePath);
            if (!file.open(QIODevice::ReadWrite)) {
                qDebug() << "Failed to open file.";
                return;
            }

            QByteArray fileData = file.readAll();
            file.close();

            // Remove task from JSON
            QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
            QJsonObject jsonObject = jsonDoc.object();
            jsonObject.remove(name);  // Remove the task entry

            // Save the updated JSON back to the file
            if (!file.open(QIODevice::WriteOnly)) {
                qDebug() << "Failed to open file for writing.";
                return;
            }

            file.write(jsonDoc.toJson());
            file.close();

            delete buttonToRemove;
            delete itemToRemove;

        }
    }
}


Archived_tasks::~Archived_tasks()
{
    delete ui;
}

void Archived_tasks::on_close_clicked()
{
    this->close();
}

