#include "taski.h"
#include "ui_taski.h"
#include "new_org.h"

Taski::Taski(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Taski)
{
    ui->setupUi(this);
}

Taski::~Taski()
{
    delete ui;
}

void Taski::on_pushButton_clicked()
{
    new_org *w=new new_org;
    w->show();
}

