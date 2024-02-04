#include "taski.h"
#include "ui_taski.h"
#include "new_org.h"
#include "usermanager.h"
#include "org_manager.h"
#include "edit_org.h"
#include "team_manager.h"
#include "new_team.h"
#include "edit_team.h"
#include "new_pro.h"
#include "edit_pro.h"
#include "project_manager.h"
#include "new_task.h"
#include "edit_task.h"
#include "task_manager.h"
#include "archived_tasks.h"
#include "comment_sectionoftask.h"
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


Taski::Taski(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Taski)
{

    //hide till clicking button

    ui->setupUi(this);

    ui->tabWidget->hide();
    ui->memberslbl->hide();
    ui->ownerlbl->hide();
    ui->adminslbl->hide();
    ui->memberslist->hide();
    ui->adminslist->hide();
    ui->owner->hide();
    ui->org_label->hide();

    //ui->teamlist->hide();

    ui->teamlbl->hide();
    ui->headslbl->hide();
    ui->memberslblteam->hide();
    ui->ownerlblteam->hide();
    ui->headslist->hide();
    ui->ownerprolist->hide();
    ui->teammemberslist->hide();
    ui->taskteam->hide();
    ui->tasklblteam->hide();
    QString loggedInUsername = UserManager::getLoggedInUsername();
    ui->welcomlbl->setText("Welcome "+loggedInUsername);


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
    //QString loggedInUsername = UserManager::getLoggedInUsername();

    // Adding name to organization
    QJsonObject jsonObjecttext = jsonDoctext.object();
    QJsonObject user = jsonObjecttext.value(loggedInUsername).toObject();

    // Correct the key name to "organization"
    QJsonArray orgsArray = user.value("organization").toArray();

    user["organization"] = orgsArray;

    // Save the changes back to text.json
    jsonObjecttext[loggedInUsername] = user;
    jsonDoctext.setObject(jsonObjecttext);


    filetext.open(QIODevice::WriteOnly | QIODevice::Truncate);
    filetext.write(QJsonDocument(jsonObjecttext).toJson());
    filetext.close();


    // Set up the container for buttons
    buttonContainer = new QWidget(this);
    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonContainer);
    ui->verticalLayout->addWidget(buttonContainer);

    for (int i = 0; i < orgsArray.size(); ++i) {
        addorg(orgsArray[i].toString());
    }
    ///////////////////////////////////////////////////
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "org.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();
    ////////////////////////////
}


Taski::~Taski()
{
    delete ui;
}

///adding new org
void Taski::on_pushButton_clicked()
{
    new_org *w = new new_org(this);
    connect(w, SIGNAL(neworg_added(QString)), this, SLOT(addorg(QString)));
    w->show();
}

void Taski::addorg(QString name)
{
    // Create a QPushButton for each item in the "organization" array
    QPushButton *button = new QPushButton(name, this);
    orgButtons.append(button);
    orgNames.append(name);


    // Create an "Edit" button for each item
    QPushButton *editButton = new QPushButton("Edit", this);
    editButton->setFixedSize(QSize(50, 30));
    // Create a QListWidgetItem
    QListWidgetItem *item = new QListWidgetItem(ui->orgs);
    item->setSizeHint(QSize(100, 50));  // Set the size of the item

    // create  widget to hold buttons
    QWidget *buttonWidget = new QWidget(this);
    QHBoxLayout *buttonWidgetLayout = new QHBoxLayout(buttonWidget);
    buttonWidgetLayout->addWidget(button);
    buttonWidgetLayout->addWidget(editButton);

    // Set the widget as the item widget
    ui->orgs->setItemWidget(item, buttonWidget);
    /////////////////////
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "org.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();





    // Connect the button click signal to a slot
    connect(button, &QPushButton::clicked, [this, name]() {
        ////////////////////////teams
        ui->headslbl->hide();
        ui->memberslblteam->hide();
        ui->ownerlblteam->hide();
        ui->headslist->hide();
        ui->ownerteam->hide();
        ui->teamlbl->hide();
        ui->teammemberslist->hide();
        refreshContent(name);

        org_manager::setorg(name);
        ui->teamlist->clear();
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
        QJsonArray teamsArray = org.value("teams").toArray();

        org["teams"] = teamsArray;

        // Save the changes back to text.json
        jsonObjectorg[name] = org;
        jsonDocorg.setObject(jsonObjectorg);


        fileorg.open(QIODevice::WriteOnly | QIODevice::Truncate);
        fileorg.write(QJsonDocument(jsonObjectorg).toJson());
        fileorg.close();


        // Set up the container for buttons
        buttonContainerteam = new QWidget(this);
        QVBoxLayout *buttonLayoutteam = new QVBoxLayout(buttonContainerteam);
        ui->verticalLayout->addWidget(buttonContainerteam);

        for (int i = 0; i < teamsArray.size(); ++i) {
            addteam(teamsArray[i].toString());
            qDebug()<<teamsArray[i].toString();
        }

        ///////////////////////teams
        //////////////////////projects
        ui->headslblpro->hide();
        ui->memberslblpro->hide();
        ui->ownerlblpro->hide();
        ui->headslistpro->hide();
        ui->ownerprolist->hide();
        ui->projectlbl->hide();
        ui->taskpro->hide();
        ui->tasklblpro->hide();
        ui->promemberslist->hide();
        refreshContent(name);

        org_manager::setorg(name);
        ui->prolist->clear();
        QJsonArray prosArray = org.value("projects").toArray();

        org["projects"] = prosArray;

        // Save the changes back to text.json
        jsonObjectorg[name] = org;
        jsonDocorg.setObject(jsonObjectorg);


        fileorg.open(QIODevice::WriteOnly | QIODevice::Truncate);
        fileorg.write(QJsonDocument(jsonObjectorg).toJson());
        fileorg.close();


        // Set up the container for buttons
        buttonContainerpro = new QWidget(this);
        QVBoxLayout *buttonLayoutpro = new QVBoxLayout(buttonContainerpro);
        ui->verticalLayout->addWidget(buttonContainerpro);

        for (int i = 0; i < prosArray.size(); ++i) {
            addpro(prosArray[i].toString());

        }
        /////////////////////////////tasks
        ///
        ui->tasklbl->hide();
        ui->tabWidget->hide();
        ui->deslbl->hide();
        ui->assignprolbl->hide();
        ui->assignmemberlbl->hide();
        ui->assignteamlbl->hide();
        ui->descriptiontext->hide();
        ui->protext->hide();
        ui->taskmemberlist->hide();
        ui->teamtext->hide();
        refreshContent(name);

        org_manager::setorg(name);
        ui->tasklist->clear();
        QJsonArray tasksArray = org.value("tasks").toArray();

        org["tasks"] = tasksArray;

        // Save the changes back to text.json
        jsonObjectorg[name] = org;
        jsonDocorg.setObject(jsonObjectorg);


        fileorg.open(QIODevice::WriteOnly | QIODevice::Truncate);
        fileorg.write(QJsonDocument(jsonObjectorg).toJson());
        fileorg.close();


        // Set up the container for buttons
        buttonContainerpro = new QWidget(this);
        QVBoxLayout *buttonLayouttask = new QVBoxLayout(buttonContainertask);
        ui->verticalLayout->addWidget(buttonContainertask);

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
            if(task["Archive"]==false){
                addtask(tasksArray[i].toString());
            }

            qDebug()<<tasksArray[i].toString();
        }


    });




    // Connect the "Edit" button click signal to a slot
    connect(editButton, &QPushButton::clicked, [this, name ]() {
        qDebug()<<name<<"is";
        edit_org *o=new edit_org(this);
        connect(o, SIGNAL(org_deleted(QString)), this, SLOT(delete_org(QString)));
        connect(o,SIGNAL(name_changed(QString,QString)),this,SLOT(changename(QString,QString)));
        connect(o,SIGNAL(content_refreshed(QString)),this,SLOT(refreshContent(QString)));
        emit orgname_get(name);
        o->show();


    });
}

void Taski::delete_org(QString name)
{

    for (int i = 0; i < orgNames.size(); ++i) {
        if (orgNames.at(i) == name) {
            // Remove button and name from lists
            QPushButton *buttonToRemove = orgButtons.at(i);
            orgButtons.removeAt(i);
            orgNames.removeAt(i);

            // Find and remove corresponding item from orgs
            QListWidgetItem *itemToRemove = nullptr;
            for (int j = 0; j < ui->orgs->count(); ++j) {
                if (ui->orgs->itemWidget(ui->orgs->item(j))->layout()->indexOf(buttonToRemove) != -1) {
                    itemToRemove = ui->orgs->takeItem(j);
                    break;
                }
            }

            // Cleanup
            QString currentDir = QCoreApplication::applicationDirPath();
            QString filePath = currentDir + QDir::separator() + "org.json";

            QFile file(filePath);
            if (!file.open(QIODevice::ReadWrite)) {
                qDebug() << "Failed to open file.";
                return;
            }

            QByteArray fileData = file.readAll();
            file.close();

            delete buttonToRemove;
            delete itemToRemove;
            refreshContent(name);
        }
    }

}

void Taski::refreshContent(const QString& name) {
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
    // Adding name to organization
    QJsonObject jsonObject = jsonDoc.object();
    QJsonObject org = jsonObject.value(name).toObject();

    // Correct the key name to "organization"
    QJsonArray membersArray = org.value("members").toArray();
    QJsonArray adminsArray = org.value("admins").toArray();
    QString ownername = org.value("owner").toString();
    QString orgname = org.value("name").toString();


    ui->tabWidget->show();
    ui->memberslbl->show();
    ui->ownerlbl->show();
    ui->adminslbl->show();
    ui->memberslist->show();
    ui->adminslist->show();
    ui->owner->show();
    ui->memberslist->clear();
    ui->adminslist->clear();
    ui->owner->clear();
    ui->org_label->setText(orgname);
    ui->org_label->show();
    org["members"] = membersArray;
    org["admins"] = adminsArray;

    ui->owner->addItem(ownername);
    for (int i = 0; i < membersArray.size(); ++i) {
        ui->memberslist->addItem(membersArray[i].toString());
    }
    for (int i = 0; i < adminsArray.size(); ++i) {
        ui->adminslist->addItem(adminsArray[i].toString());
    }
}

void Taski::changename(const QString &before, const QString &after)
{
    delete_org(before);
    addorg(after);
}

/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//teams///////////////////////////////////////////////////
void Taski::on_addteam_clicked()
{
    new_team *t = new new_team(this);
    connect(t, SIGNAL(newteam_added(QString)), this, SLOT(addteam(QString)));
    t->show();
}
void Taski::addteam(QString name)
{
    QPushButton *button = new QPushButton(name, this);
    orgButtonsteam.append(button);
    orgNamesteam.append(name);

    // Create an "Edit" button for each item
    QPushButton *editButton = new QPushButton("Edit", this);
    editButton->setFixedSize(QSize(50, 30));

    // Create a QListWidgetItem
    QListWidgetItem *item = new QListWidgetItem(ui->teamlist);
    item->setSizeHint(QSize(100, 50));  // Set the size of the item

    // create widget to hold buttons
    QWidget *buttonWidget = new QWidget(this);
    QHBoxLayout *buttonWidgetLayoutteam = new QHBoxLayout(buttonWidget);
    buttonWidgetLayoutteam->addWidget(button);
    buttonWidgetLayoutteam->addWidget(editButton);

    // Set the widget as the item widget
    ui->teamlist->setItemWidget(item, buttonWidget);

    // Connect the button click signal to a slot
    connect(button, &QPushButton::clicked, [this, name]() {
        refreshteam(name);
    });

    // Connect the "Edit" button click signal to a slot
    connect(editButton, &QPushButton::clicked, [this, name]() {
        team_manager::setTeam(name);
        edit_team *t=new edit_team;
        connect(t, SIGNAL(team_deleted(QString)), this, SLOT(delete_team(QString)));
        connect(t,SIGNAL(name_changed(QString,QString)),this,SLOT(changenameteam(QString,QString)));
        connect(t,SIGNAL(content_refreshed(QString)),this,SLOT(refreshteam(QString)));
        t->show();

        qDebug() << name << "is";
        // Implement the code to handle the "Edit" button click
    });
}

void Taski::refreshteam(const QString &name)
{
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "Team.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    // Adding name to organization
    QJsonObject jsonObject = jsonDoc.object();
    QJsonObject team = jsonObject.value(name).toObject();

    // Correct the key name to "organization"
    QJsonArray tasksArray = team.value("tasks").toArray();
    QJsonArray membersArray = team.value("members").toArray();
    QJsonArray headsArray = team.value("heads").toArray();
    QString ownername = team.value("owner").toString();
    QString teamname = team.value("name").toString();

    ui->tasklblteam->show();
    ui->taskteam->show();
    ui->teamlbl->show();
    ui->tabWidget->show();
    ui->headslist->show();
    ui->ownerteam->show();
    ui->teammemberslist->show();
    ui->ownerlblteam->show();
    ui->headslbl->show();
    ui->memberslblteam->show();
    ui->teammemberslist->clear();
    ui->taskteam->clear();
    ui->headslist->clear();
    ui->ownerteam->clear();
    ui->teamlbl->setText(teamname);

    team["members"] = membersArray;
    team["heads"] = headsArray;

    ui->ownerteam->setText(ownername);
    for (int i = 0; i < membersArray.size(); ++i) {
        ui->teammemberslist->addItem(membersArray[i].toString());
    }
    for (int i = 0; i < headsArray.size(); ++i) {
        ui->headslist->addItem(headsArray[i].toString());
    }
    for (int i = 0; i < tasksArray.size(); ++i) {
        ui->taskteam->addItem(tasksArray[i].toString());
    }

}
// ...

void Taski::delete_team(QString name)
{
    for (int i = 0; i < orgNamesteam.size(); ++i) {
        if (orgNamesteam.at(i) == name) {
            // Remove button and name from lists
            QPushButton *buttonToRemove = orgButtonsteam.at(i);
            orgButtonsteam.removeAt(i);
            orgNamesteam.removeAt(i);

            // Find and remove corresponding item from teamlist
            QListWidgetItem *itemToRemove = nullptr;
            for (int j = 0; j < ui->teamlist->count(); ++j) {
                if (ui->teamlist->itemWidget(ui->teamlist->item(j))->layout()->indexOf(buttonToRemove) != -1) {
                    itemToRemove = ui->teamlist->takeItem(j);
                    break;
                }
            }

            // Cleanup
            QString currentDir = QCoreApplication::applicationDirPath();
            QString filePath = currentDir + QDir::separator() + "Team.json";

            QFile file(filePath);
            if (!file.open(QIODevice::ReadWrite)) {
                qDebug() << "Failed to open file.";
                return;
            }

            QByteArray fileData = file.readAll();
            file.close();

            delete buttonToRemove;
            delete itemToRemove;
            refreshteam(name);
        }
    }
}
void Taski::changenameteam(const QString &before, const QString &after)
{
    delete_org(before);
    addorg(after);
}
////////////////////project/////////////////////////////////////
/// ///////////////////////////////////////////////////////////
void Taski::on_addpro_clicked()
{
    new_pro *p = new new_pro(this);
    connect(p, SIGNAL(newpro_added(QString)), this, SLOT(addpro(QString)));
    p->show();
}
void Taski::addpro(QString name)
{
    QPushButton *button = new QPushButton(name, this);
    orgButtonspro.append(button);
    orgNamespro.append(name);

    // Create "Edit" and "Undone" buttons for each item
    QPushButton *editButton = new QPushButton("Edit", this);
    Project_manager pro;
    QPushButton *undoneButton = new QPushButton("Undone", this);

    // Set fixed size for the buttons
    editButton->setFixedSize(QSize(50, 30));
    undoneButton->setFixedSize(QSize(50, 30));

    // Create a QListWidgetItem
    QListWidgetItem *item = new QListWidgetItem(ui->prolist);
    item->setSizeHint(QSize(200, 50));  // Set the size of the item

    // create widget to hold buttons
    QWidget *buttonWidget = new QWidget(this);
    QHBoxLayout *buttonWidgetLayoutpro = new QHBoxLayout(buttonWidget);
    buttonWidgetLayoutpro->addWidget(button);
    buttonWidgetLayoutpro->addWidget(editButton);
    buttonWidgetLayoutpro->addWidget(undoneButton);

    // Set the widget as the item widget
    ui->prolist->setItemWidget(item, buttonWidget);

    // Connect the button click signals to slots
    connect(button, &QPushButton::clicked, [this, name]() {
        refreshpro(name);
    });

    // Connect the "Edit" button click signal to a slot
    connect(editButton, &QPushButton::clicked, [this, name]() {
        Project_manager::setproject(name);
        edit_pro *p = new edit_pro;
        connect(p, SIGNAL(pro_deleted(QString)), this, SLOT(delete_pro(QString)));
        connect(p, SIGNAL(name_changed(QString, QString)), this, SLOT(changenamepro(QString, QString)));
        connect(p, SIGNAL(content_refreshed(QString)), this, SLOT(refreshpro(QString)));
        p->show();
    });

    // Check project status and set the initial text of the "Undone" button
    if (pro.is_doneProject(name)) {
        undoneButton->setText("Done");
    } else {
        undoneButton->setText("Undone");
    }

    // Connect the "Undone" button click signal to a slot
    connect(undoneButton, &QPushButton::clicked, [this, name, undoneButton]() {
        QString orgname = org_manager::get_organization();
        Project_manager pro;

        // Update the project state and get the updated state
        pro.updateProjectState(orgname, name, "done");
        bool updatedState = pro.is_doneProject(name);

        // Update the button text based on the updated state
        if (updatedState) {
            undoneButton->setText("Done");
        } else {
            undoneButton->setText("Undone");
        }
    });
}



void Taski::delete_pro(QString name)
{
    for (int i = 0; i < orgNamespro.size(); ++i) {
        if (orgNamespro.at(i) == name) {
            // Remove button and name from lists
            QPushButton *buttonToRemove = orgButtonspro.at(i);
            orgButtonspro.removeAt(i);
            orgNamespro.removeAt(i);

            // Find and remove corresponding item from prolist
            QListWidgetItem *itemToRemove = nullptr;
            for (int j = 0; j < ui->prolist->count(); ++j) {
                if (ui->prolist->itemWidget(ui->prolist->item(j))->layout()->indexOf(buttonToRemove) != -1) {
                    itemToRemove = ui->prolist->takeItem(j);
                    break;
                }
            }

            // Cleanup
            QString currentDir = QCoreApplication::applicationDirPath();
            QString filePath = currentDir + QDir::separator() + "project.json";

            QFile file(filePath);
            if (!file.open(QIODevice::ReadWrite)) {
                qDebug() << "Failed to open file.";
                return;
            }

            QByteArray fileData = file.readAll();
            file.close();

            delete buttonToRemove;
            delete itemToRemove;
            refreshpro(name);
        }
    }
}

void Taski::changenamepro(const QString &before, const QString &after)
{
    delete_pro(before);
    addpro(after);
}

void Taski::refreshpro(const QString &name)
{
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "project.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    // Adding name to project
    QJsonObject jsonObject = jsonDoc.object();
    QJsonObject pro = jsonObject.value(name).toObject();

    // Correct the key name to "project"
    QJsonArray tasksArray=pro.value("tasks").toArray();
    QJsonArray membersArray = pro.value("members").toArray();
    QJsonArray headsArray = pro.value("heads").toArray();
    QString ownername = pro.value("owner").toString();
    QString proname = pro.value("name").toString();

    ui->tasklblpro->show();
    ui->taskpro->show();
    ui->projectlbl->show();
    ui->tabWidget->show();
    ui->headslistpro->show();
    ui->ownerprolist->show();
    ui->promemberslist->show();
    ui->ownerlblpro->show();
    ui->headslblpro->show();
    ui->memberslblpro->show();
    ui->taskpro->clear();
    ui->promemberslist->clear();
    ui->headslistpro->clear();
    ui->ownerprolist->clear();
    ui->projectlbl->setText(proname);

    pro["members"] = membersArray;
    pro["heads"] = headsArray;

    ui->ownerprolist->addItem(ownername);
    for (int i = 0; i < membersArray.size(); ++i) {
        ui->promemberslist->addItem(membersArray[i].toString());
    }
    for (int i = 0; i < headsArray.size(); ++i) {
        ui->headslistpro->addItem(headsArray[i].toString());
    }
    for (int i = 0; i < tasksArray.size(); ++i) {
        ui->taskpro->addItem(tasksArray[i].toString());
    }
}
/////////////////////////////////////////////
/// tasks//////////////////////////////////////////////////////////////////
////////////////////////////////////////////
void Taski::on_addtask_clicked()
{
    new_task *t=new new_task;
    connect(t, SIGNAL(newtask_added(QString)), this, SLOT(addtask(QString)));
    t->show();
}
void Taski::on_archivedtasksbutton_clicked()
{
    Archived_tasks *a=new Archived_tasks;
    connect(a, SIGNAL(newtask_added(QString)), this, SLOT(addtask(QString)));
    a->show();
}
void Taski::addtask(QString name)
{
    QPushButton *button = new QPushButton(name, this);
    orgButtonstask.append(button);
    orgNamestask.append(name);

    // Create "Edit," "Archive," and "Comment" buttons for each item
    QPushButton *editButton = new QPushButton("Edit", this);
    editButton->setFixedSize(QSize(50, 30));
    orgButtonstask.append(editButton);

    QPushButton *archiveButton = new QPushButton("Archive", this);
    archiveButton->setFixedSize(QSize(60, 30));
    orgButtonstask.append(archiveButton);

    QPushButton *commentButton = new QPushButton("Comment", this);
    commentButton->setFixedSize(QSize(60, 30));
    orgButtonstask.append(commentButton);

    // Create a QLabel for due date
    QLabel *dueDateLabel = new QLabel(this);

    // Fetch due time from task.json based on the task name
    QString dueTime = Task_manager::getDueDate(name);
    qDebug() << dueTime;
    dueDateLabel->setText(dueTime);

    // Create a QListWidgetItem
    QListWidgetItem *item = new QListWidgetItem(ui->tasklist);
    item->setSizeHint(QSize(200, 50));  // Set the size of the item

    // create widget to hold buttons and due date label
    QWidget *buttonWidget = new QWidget(this);
    QHBoxLayout *buttonWidgetLayout = new QHBoxLayout(buttonWidget);
    buttonWidgetLayout->addWidget(button);
    buttonWidgetLayout->addWidget(editButton);
    buttonWidgetLayout->addWidget(archiveButton);
    buttonWidgetLayout->addWidget(commentButton);
    buttonWidgetLayout->addWidget(dueDateLabel);  // Add due date label to the layout

    // Set the widget as the item widget
    ui->tasklist->setItemWidget(item, buttonWidget);

    // Connect the button click signals to slots
    connect(button, &QPushButton::clicked, [this, name]() {
        refreshtask(name);
    });

    connect(editButton, &QPushButton::clicked, [this, name]() {
        Task_manager::settask(name);
        edit_task *t = new edit_task;
        connect(t, SIGNAL(task_deleted(QString)), this, SLOT(delete_task(QString)));
        connect(t, SIGNAL(content_refreshed(QString)), this, SLOT(refreshtask(QString)));
        t->show();

        qDebug() << name << "is";
    });

    connect(archiveButton, &QPushButton::clicked, [this, name]() {
        Task_manager my_task;
        my_task.archiveTask(name);
        delete_task(name);
    });

    connect(commentButton, &QPushButton::clicked, [this, name]() {
        comment_sectionoftask *c= new comment_sectionoftask ;
        Task_manager::settask(name);
        c->show();
    });
}

void Taski::refreshtask(const QString &name)
{
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "task.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    // Adding name to organization
    QJsonObject jsonObject = jsonDoc.object();
    QJsonObject task = jsonObject.value(name).toObject();

    // Correct the key name to "organization"
    QJsonArray assignmembersArray = task.value("assignee Member").toArray();
    QString description = task.value("description").toString();
    QString assignpro = task.value("assignee Project").toString();
    QString assignteam=task.value("assignee Team").toString();
    QString taskname = task.value("name").toString();

    ui->tasklbl->show();
    ui->tabWidget->show();
    ui->deslbl->show();
    ui->assignprolbl->show();
    ui->assignmemberlbl->show();
    ui->assignteamlbl->show();
    ui->descriptiontext->show();
    ui->protext->show();
    ui->taskmemberlist->show();
    ui->teamtext->show();

    ui->taskmemberlist->clear();
    ui->teamtext->clear();
    ui->protext->clear();
    ui->descriptiontext->clear();



    ui->tasklbl->setText(taskname);

    task["assignee Member"] = assignmembersArray;

    ui->descriptiontext->addItem(description);
    ui->teamtext->addItem(assignteam);
    ui->protext->addItem(assignpro);
    for (int i = 0; i < assignmembersArray.size(); ++i) {
        ui->taskmemberlist->addItem(assignmembersArray[i].toString());
    }

}
void Taski::delete_task(QString name)
{
    for (int i = 0; i < orgNamestask.size(); ++i) {
        if (orgNamestask.at(i) == name) {
            // Remove button and name from lists
            QPushButton *buttonToRemove = orgButtonstask.at(i);
            orgButtonstask.removeAt(i);
            orgNamestask.removeAt(i);

            // Find and remove corresponding item from teamlist
            QListWidgetItem *itemToRemove = nullptr;
            for (int j = 0; j < ui->tasklist->count(); ++j) {
                if (ui->tasklist->itemWidget(ui->tasklist->item(j))->layout()->indexOf(buttonToRemove) != -1) {
                    itemToRemove = ui->tasklist->takeItem(j);
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
            refreshtask(name);
        }
    }
}





void Taski::on_commentbutton_clicked()
{
    comment_sectionoftask *c= new comment_sectionoftask ;
    c->show();
}

