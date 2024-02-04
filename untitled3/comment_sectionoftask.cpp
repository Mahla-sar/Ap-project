#include "comment_sectionoftask.h"
#include "ui_comment_sectionoftask.h"
#include "task_manager.h"
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

comment_sectionoftask::comment_sectionoftask(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::comment_sectionoftask)
{
   QString taskname = Task_manager::get_task();
   ui->setupUi(this);


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
   //QString loggedInUsername = UserManager::getLoggedInUsername();

   // Adding name to organization
   QJsonObject jsonObject= jsonDoc.object();
   QJsonObject task = jsonObject.value(taskname).toObject();

   // Correct the key name to "organization"
   QJsonArray commentsArray = task.value("comments").toArray();

   // task["comments"] = commentsArray;

   // Save the changes back to text.json
   jsonObject[taskname] = task;
   jsonDoc.setObject(jsonObject);


   file.open(QIODevice::WriteOnly | QIODevice::Truncate);
   file.write(QJsonDocument(jsonObject).toJson());
   file.close();



   for (int i = 0; i < commentsArray.size(); ++i) {
       ui->listWidget->addItem(commentsArray[i].toString());
       //showComment(taskname,commentsArray[i].toString());
       qDebug()<<commentsArray[i].toString();
   }
}

comment_sectionoftask::~comment_sectionoftask()
{
    delete ui;
}

void comment_sectionoftask::on_pushButton_clicked()
{
    QString taskname = Task_manager::get_task();
    QString commenttext =ui->lineEdit->text();
    Task_manager my_task;
    ui->listWidget->addItem(commenttext);
    my_task.addCommentToTask(taskname,commenttext);
    //showComment(taskname,commenttext);



}
// void comment_sectionoftask::showComment(const QString &taskName, const QString &comment)
// {
//     QListWidgetItem *item = new QListWidgetItem(comment);
//     ui->listWidget->addItem(item);
// }





