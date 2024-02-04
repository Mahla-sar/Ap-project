#include "edit_team.h"
#include "ui_edit_team.h"
#include "team_manager.h"
#include "org_manager.h"
#include "taski.h"

edit_team::edit_team(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit_team)
{
    ui->setupUi(this);
    QString teamname = team_manager::get_Team();


    ui->textbox->hide();
    ui->label_1->hide();
    ui->button->hide();


    ui->orglabel->setText(teamname);
}

edit_team::~edit_team()
{
    delete ui;
}

void edit_team::on_promotebutton_clicked()
{
    ui->textbox->show();
    ui->label_1->setText("choose a member to promote to head");
    ui->label_1->show();
    ui->button->setText("Promote");
    ui->button->show();
    ui->button->setFocus();
}


void edit_team::on_namebutton_clicked()
{
    ui->textbox->show();
    ui->label_1->setText("change team's name");
    ui->label_1->show();
    ui->button->setText("Change");
    ui->button->show();
    ui->button->setFocus();
}


void edit_team::on_deletbutton_clicked()
{

    ui->label_1->setText("delete the whole team");
    ui->label_1->show();
    ui->button->setText("Delete");
    ui->button->show();
    ui->button->setFocus();
}


void edit_team::on_add_button_clicked()
{
    ui->textbox->show();
    ui->label_1->setText("add a new member");
    ui->label_1->show();
    ui->button->setText("Add");
    ui->button->show();
    ui->button->setFocus();
}


void edit_team::on_demotebutton_clicked()
{
    ui->textbox->show();
    ui->label_1->setText("demote a head");
    ui->label_1->show();
    ui->button->setText("Demote");
    ui->button->show();
    ui->button->setFocus();
}

void edit_team::on_remove_clicked()
{
    ui->textbox->show();
    ui->label_1->setText("remove a member");
    ui->label_1->show();
    ui->button->setText("Remove");
    ui->button->show();
    ui->button->setFocus();
}





void edit_team::on_button_clicked()
{
    if (ui->button->text()=="Promote")
    {
        qDebug()<<"youclicked";
        QString text=ui->textbox->text();
        QString teamname = team_manager::get_Team();
        QString OrganizationName = org_manager::get_organization();

        team_manager my_team;
        qDebug()<<"team name is"<<teamname;
        my_team.promoteMemberToHeadInTeam(OrganizationName,teamname,text);
        emit  content_refreshed(teamname);



    }
    else if (ui->button->text()=="Demote")
    {
        qDebug()<<"youclicked";
        QString text=ui->textbox->text();
        QString teamname = team_manager::get_Team();
        QString OrganizationName = org_manager::get_organization();

        team_manager my_team;
        qDebug()<<"team name is"<<teamname;
        my_team.demoteHeadToMemberInTeam(OrganizationName,teamname,text);
        emit  content_refreshed(teamname);
    }
    else if (ui->button->text()=="Add")
    {
        qDebug()<<"youclicked";
        QString text=ui->textbox->text();
        QString teamname = team_manager::get_Team();
        QString OrganizationName = org_manager::get_organization();

        team_manager my_team;
        qDebug()<<"team name is"<<teamname;
        my_team.addMemberToTeam(OrganizationName,teamname,text);
        emit  content_refreshed(teamname);
    }
    else if(ui->button->text()=="Remove")
    {
        qDebug()<<"youclicked";
        QString text=ui->textbox->text();
        QString teamname = team_manager::get_Team();
        QString OrganizationName = org_manager::get_organization();

        team_manager my_team;
        qDebug()<<"team name is"<<teamname;
        my_team.removeMemberFromTeam(OrganizationName,teamname,text);
        emit  content_refreshed(teamname);
    }
    else if (ui->button->text()=="Change")
    {
        qDebug()<<"youclicked";
        QString text=ui->textbox->text();
        QString teamname = team_manager::get_Team();
        QString OrganizationName = org_manager::get_organization();

        team_manager my_team;
        qDebug()<<"team name is"<<teamname;
        my_team.renameTeam(OrganizationName,teamname,text);

        emit name_changed(teamname, text);
        this->close();
    }
    else if (ui->button->text()=="Delete")
    {
        qDebug()<<"youclicked";
        QString text=ui->textbox->text();
        QString teamname = team_manager::get_Team();
        QString OrganizationName = org_manager::get_organization();

        team_manager my_team;
        qDebug()<<"team name is"<<teamname;
        my_team.deleteTeam(OrganizationName,teamname);
        emit team_deleted(teamname);
    }
    ui->label_1->hide();
    ui->textbox->hide();
    ui->button->hide();
}

