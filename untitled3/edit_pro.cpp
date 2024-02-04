#include "edit_pro.h"
#include "ui_edit_pro.h"
#include "org_manager.h"
#include "project_manager.h"

edit_pro::edit_pro(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit_pro)
{
    ui->setupUi(this);
    QString proname = Project_manager::get_project();


    ui->textbox->hide();
    ui->label_1->hide();
    ui->button->hide();


    ui->orglabel->setText(proname);
}

edit_pro::~edit_pro()
{
    delete ui;
}

void edit_pro::on_namebutton_clicked()
{
    ui->textbox->show();
    ui->label_1->setText("change Project's name");
    ui->label_1->show();
    ui->button->setText("Change");
    ui->button->show();
    ui->button->setFocus();
}


void edit_pro::on_deletbutton_clicked()
{

    ui->label_1->setText("delete the whole project");
    ui->label_1->show();
    ui->button->setText("Delete");
    ui->button->show();
    ui->button->setFocus();
}


void edit_pro::on_add_button_clicked()
{
    ui->textbox->show();
    ui->label_1->setText("add a new member");
    ui->label_1->show();
    ui->button->setText("Add");
    ui->button->show();
    ui->button->setFocus();
}


void edit_pro::on_remove_clicked()
{
    ui->textbox->show();
    ui->label_1->setText("remove a member");
    ui->label_1->show();
    ui->button->setText("Remove");
    ui->button->show();
    ui->button->setFocus();
}
void edit_pro::on_button_clicked()
{
    if (ui->button->text()=="Add")
    {
        qDebug()<<"youclicked";
        QString text=ui->textbox->text();
        QString proname = Project_manager::get_project();
        QString OrganizationName = org_manager::get_organization();

        Project_manager my_pro;
        qDebug()<<"pro name is"<<proname;
        my_pro.addMemberToproject(OrganizationName,proname,text);
        emit  content_refreshed(proname);
    }
    else if(ui->button->text()=="Remove")
    {
        qDebug()<<"youclicked";
        QString text=ui->textbox->text();
        QString proname = Project_manager::get_project();
        QString OrganizationName = org_manager::get_organization();

        Project_manager my_pro;
        qDebug()<<"pro name is"<<proname;
        my_pro.removeMemberFromproject(OrganizationName,proname,text);
        emit  content_refreshed(proname);
    }
    else if (ui->button->text()=="Change")
    {
        qDebug()<<"youclicked";
        QString text=ui->textbox->text();
        QString proname = Project_manager::get_project();
        QString OrganizationName = org_manager::get_organization();

        Project_manager my_pro;
        qDebug()<<"project name is"<<proname;
        my_pro.renameproject(OrganizationName,proname,text);

        emit name_changed(proname, text);
        this->close();
    }
    else if (ui->button->text()=="Delete")
    {
        qDebug()<<"youclicked";
        QString text=ui->textbox->text();
        QString proname = Project_manager::get_project();
        QString OrganizationName = org_manager::get_organization();

        Project_manager my_pro;
        qDebug()<<"pro name is"<<proname;
        my_pro.deleteproject(OrganizationName,proname);
        emit pro_deleted(proname);
    }
    ui->label_1->hide();
    ui->textbox->hide();
    ui->button->hide();
}


