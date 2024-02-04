#include "edit_task.h"
#include "ui_edit_task.h"
#include "task_manager.h"
#include "org_manager.h"


edit_task::edit_task(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit_task)
{
    ui->setupUi(this);
    ui->textbox->hide();
    ui->label_1->hide();
    ui->button->hide();
}

edit_task::~edit_task()
{
    delete ui;
}

void edit_task::on_pro_button_clicked()
{
    ui->textbox->show();
    ui->label_1->setText("Assigne a Project to task");
    ui->label_1->show();
    ui->button->setText("Assigne Project");
    ui->button->show();
    ui->button->setFocus();
}


void edit_task::on_Memberbutton_clicked()
{
    ui->textbox->show();
    ui->label_1->setText("Assigne Member to task");
    ui->label_1->show();
    ui->button->setText("Assigne Member");
    ui->button->show();
    ui->button->setFocus();
}


void edit_task::on_teambutton_clicked()
{
    ui->textbox->show();
    ui->label_1->setText("Assigne a Team to task");
    ui->label_1->show();
    ui->button->setText("Assigne Team");
    ui->button->show();
    ui->button->setFocus();
}


void edit_task::on_deletbutton_clicked()
{
    ui->label_1->setText("delete the whole Task");
    ui->label_1->show();
    ui->button->setText("Delete");
    ui->button->show();
    ui->button->setFocus();
}


void edit_task::on_button_clicked()
{
    if (ui->button->text()=="Assigne Team")
    {
        QString text=ui->textbox->text();
        QString taskname = Task_manager::get_task();
        QString OrganizationName = org_manager::get_organization();

        Task_manager my_task;

        my_task.assignTaskToTeam(taskname,text);
        emit  content_refreshed(taskname);
    }
    else if(ui->button->text()=="Assigne Project")
    {
        QString text=ui->textbox->text();
        QString taskname = Task_manager::get_task();
        QString OrganizationName = org_manager::get_organization();

        Task_manager my_task;

        my_task.assignTaskToProject(taskname,text);
        emit  content_refreshed(taskname);
    }
    else if (ui->button->text()=="Assigne Member")
    {
        QString text=ui->textbox->text();
        QString taskname = Task_manager::get_task();
        QString OrganizationName = org_manager::get_organization();

        Task_manager my_task;

        my_task.assignTaskToMember(taskname,text);
        emit  content_refreshed(taskname);
    }
    else if (ui->button->text()=="Delete")
    {
        qDebug()<<"youclicked";
        QString text=ui->textbox->text();
        QString taskname = Task_manager::get_task();
        QString OrganizationName = org_manager::get_organization();

        Task_manager my_task;

        my_task.deleteTask(OrganizationName,taskname);
        emit task_deleted(taskname);
    }
    ui->label_1->hide();
    ui->textbox->hide();
    ui->button->hide();

}

