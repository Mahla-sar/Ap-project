#include "new_team.h"
#include "ui_new_team.h"
#include "team_manager.h".h"
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
new_team::new_team(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::new_team)
{
    ui->setupUi(this);
}

new_team::~new_team()
{
    delete ui;
}

void new_team::on_buttonBox_accepted()
{

    QString teamname = ui->lineEdit->text();
    team_manager my_team;
    QString orgname=org_manager::get_organization();
    my_team.createTeam(orgname,teamname);
    QMessageBox::information(this, "Organization Created", "The organization has been created successfully.");
    emit newteam_added(teamname);
    this->close();
}


