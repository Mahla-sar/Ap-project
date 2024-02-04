#include "edit_org.h"
#include "ui_edit_org.h"
#include "org_manager.h"
#include "usermanager.h"
#include "taski.h"

edit_org::edit_org(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit_org)
{
    QString OrganizationName = org_manager::get_organization();

    ui->setupUi(this);
    ui->lineEdit->hide();
    ui->label->hide();
    ui->Button->hide();
    ui->orglabel->setText(OrganizationName);



}

edit_org::~edit_org()
{
    delete ui;
}



void edit_org::on_promotebutton_clicked()
{
    ui->lineEdit->show();
    ui->label->setText("choose a member to promote to admin");
    ui->label->show();
    ui->Button->setText("Promote");
    ui->Button->show();
    ui->Button->setFocus();
}


void edit_org::on_namebutton_clicked()
{
    ui->lineEdit->show();
    ui->label->setText("change organization's name");
    ui->label->show();
    ui->Button->setText("Change");
    ui->Button->show();
    ui->Button->setFocus();
}


void edit_org::on_deletbutton_clicked()
{

    ui->label->setText("delete the whole organization");
    ui->label->show();
    ui->Button->setText("Delete");
    ui->lineEdit->hide();
    ui->Button->show();
    ui->Button->setFocus();
}


void edit_org::on_add_button_clicked()
{
    ui->lineEdit->show();
    ui->label->setText("add a new member");
    ui->label->show();
    ui->Button->setText("Add");
    ui->Button->show();
    ui->Button->setFocus();
}


void edit_org::on_demotebutton_clicked()
{
    ui->lineEdit->show();
    ui->label->setText("demote an admin");
    ui->label->show();
    ui->Button->setText("Demote");
    ui->Button->show();
    ui->Button->setFocus();
}

void edit_org::on_remove_clicked()
{
    ui->lineEdit->show();
    ui->label->setText("remove a member");
    ui->label->show();
    ui->Button->setText("Remove");
    ui->Button->show();
    ui->Button->setFocus();
}


void edit_org::on_Button_clicked()
{
    if (ui->Button->text()=="Promote")
    {
        QString text=ui->lineEdit->text();
        QString OrganizationName = org_manager::get_organization();

        org_manager my_org;
        qDebug()<<"org name is"<<OrganizationName;
        my_org.promoteMemberToAdminInOrganization(OrganizationName,text);
        emit  content_refreshed(OrganizationName);



    }
    else if (ui->Button->text()=="Demote")
    {
        QString text=ui->lineEdit->text();
        QString OrganizationName = org_manager::get_organization();

        org_manager my_org;
        qDebug()<<"org name is"<<OrganizationName;
        my_org.demoteAdminToMember(OrganizationName,text);
        emit  content_refreshed(OrganizationName);
    }
    else if (ui->Button->text()=="Add")
    {
        QString text=ui->lineEdit->text();
        QString OrganizationName = org_manager::get_organization();

        org_manager my_org;
        qDebug()<<"org name is"<<OrganizationName;
        my_org.addMemberToOrganization(OrganizationName,text);
        emit  content_refreshed(OrganizationName);
    }
    else if(ui->Button->text()=="Remove")
    {
        QString text=ui->lineEdit->text();
        QString OrganizationName = org_manager::get_organization();

        org_manager my_org;
        qDebug()<<"org name is"<<OrganizationName;
        my_org.removeMemberFromOrganization(OrganizationName,text);
        emit  content_refreshed(OrganizationName);
    }
    else if (ui->Button->text()=="Change")
    {
        QString text=ui->lineEdit->text();
        QString OrganizationName = org_manager::get_organization();

        org_manager my_org;
        qDebug()<<"org name is"<<OrganizationName;
        my_org.editOrganizationName(OrganizationName,text);
        emit name_changed(OrganizationName, text);
        this->close();
    }
    else if (ui->Button->text()=="Delete")
    {
        QString text=ui->lineEdit->text();
        QString OrganizationName = org_manager::get_organization();

        org_manager my_org;
        qDebug()<<"org name is"<<OrganizationName;
        my_org.deleteOrganization(OrganizationName);
        emit org_deleted(OrganizationName);
    }
    ui->label->hide();
    ui->lineEdit->hide();
    ui->Button->hide();


}



