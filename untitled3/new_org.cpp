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
//    QMessageBox::information(this, "Organization Created", "The organization has been created successfully.");
//    my_org.deleteOrganization(name);
    //my_org.removeMemberFromOrganization(name, "b");
    //my_org.addMemberToOrganization(name, "b");
    //my_org.promoteMemberToAdminInOrganization(name, "b");
    //my_org.demoteAdminToMember(name , "b");
    //my_org.editOrganizationName(name, "new_name_test");
    team_manager my_team;
    //my_team.deleteTeam("b_org1" , "team3");
    //my_team.addMemberToTeam("a3", "team2", "b");
    //my_team.removeMemberFromTeam("a3", "team2", "b");
    //my_team.demoteHeadToMemberInTeam("b_org1", "team3" , "a");
    //void promoteMemberToHeadTeam(const QString& orgName, const QString& memberName);
    //my_team.renameTeam("a3" , "team2" , "team0");
    //emit add_neworg(name);
    //Project_manager my_project;
//    my_project.updateProjectState("a2" , "p1" , "done");
    Task_manager my_task;
    //my_task.createTask("l" , "t2");
//    my_task.deleteTask("a1" , "t1");
    //my_task.archiveTask("t1");
    my_task.isTaskArchived("t2");
    this->close();
}


