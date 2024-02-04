#include "new_task.h"
#include "ui_new_task.h"
#include "task_manager.h"
#include "org_manager.h"
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QDateTime>

new_task::new_task(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::new_task)
{
    ui->setupUi(this);

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}

new_task::~new_task()
{
    delete ui;
}

void new_task::on_buttonBox_accepted()
{

    QString taskname=ui->namegetter->text();
    QString taskdes=ui->descriptiongetter->text();
    QString orgname=org_manager::get_organization();
    QDateTime datetime = ui->dateTimeEdit->dateTime();
    // Convert QDateTime to QString
    QString duetime = datetime.toString("yyyy-MM-dd HH:mm:ss");
    Task_manager my_task;
    if(duetime.isEmpty()||taskdes.isEmpty()||taskdes.isEmpty()){
        QMessageBox::warning(this,"new_task","fill all the blanks");

    }

    else if (datetime <= QDateTime::currentDateTime()) {
        QMessageBox::warning(this, "new_task", "Due time should be in the future");

    }

    else {
        my_task.createTask(orgname,taskname,taskdes);
        my_task.setDueDate(taskname,duetime);


        emit newtask_added(taskname);
        this->close();
    }
}

