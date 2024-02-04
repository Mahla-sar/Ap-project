#include "new_pro.h"
#include "ui_new_pro.h"
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
#include "project_manager.h"
#include "org_manager.h"

new_pro::new_pro(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::new_pro)
{
    ui->setupUi(this);
}

new_pro::~new_pro()
{
    delete ui;
}




void new_pro::on_buttonBox_accepted()
{
    QString proname = ui->lineEdit->text();
    Project_manager my_pro;
    QString orgname=org_manager::get_organization();
    my_pro.createproject(orgname,proname);
    QMessageBox::information(this, "Organization Created", "The organization has been created successfully.");
    emit newpro_added(proname);
    this->close();
}

