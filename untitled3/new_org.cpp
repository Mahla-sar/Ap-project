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
#include "userManager.h"
#include "org_manager.h"

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
    my_org.creat_organization(name);
    QMessageBox::information(this, "Organization Created", "The organization has been created successfully.");
    emit neworg_added(name);
    this->close();
}
