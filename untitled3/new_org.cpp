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
//#include "userManager.h"
#include "org_manager.h"
#include "team_manager.h"
#include "project_manager.h"
#include "task_manager.h"

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
    org_manager my_org;
    //my_org.creat_organization(name);
    // در تابعی دیگر یا در محل مناسب دیگر:
    QString currentDir = QCoreApplication::applicationDirPath();
    QString filePath = currentDir + QDir::separator() + "org.json";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file.";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject orgJsonObject = jsonDoc.object();

    // ارسال orgJsonObject به تابع sortOrgsByTime
    QVector<QString> sortedOrgs = my_org.orgNamesSorted(orgJsonObject);
    qDebug() << sortedOrgs ;
    // sortedOrgs حاوی نام‌های سازمان‌ها مرتب شده بر اساس زمان ساخت است
//    QMessageBox::information(this, "Organization Created", "The organization has been created successfully.");
//    my_org.deleteOrganization(name);
    //my_org.removeMemberFromOrganization(name, "b");
    //my_org.addMemberToOrganization(name, "b");
    //my_org.promoteMemberToAdminInOrganization(name, "b");
    //my_org.demoteAdminToMember(name , "b");
    //my_org.editOrganizationName(name, "new_name_test");
    team_manager my_team;
    //my_team.deleteTeam("b_org1" , "team3");
    //my_team.addMemberToTeam("a3", "team0", "b");
    //my_team.removeMemberFromTeam("a3", "team2", "b");
    //my_team.demoteHeadToMemberInTeam("b_org1", "team3" , "a");
    //void promoteMemberToHeadTeam(const QString& orgName, const QString& memberName);
    //my_team.renameTeam("a3" , "team2" , "team0");
    //emit add_neworg(name);
//    Project_manager my_project;
//    my_project.deleteproject("a2" , "p1");
//    my_project.updateProjectState("a2" , "p1" , "done");
    Task_manager my_task;
    //my_task.createTask("a1" , "t1" , "AP");
//    my_task.deleteTask("a1" , "t1");
    //my_task.unarchiveTask("t1");
    //my_task.isTaskArchived("t2");
//    my_task.setDueDate("t1" , "2024/01/01");
    //my_task.setDueDate("t1" , "2025/01/01");
    //my_task.deleteCommentFromTask("t1", "a" ,"soooo bad");
    //my_task.getDueDate("t1");
    //this->close();
}


