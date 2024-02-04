#include "mainwindow.h"
#include "login.h"
#include "ui_mainwindow.h"
#include "signin.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    signin *S=new signin;
    S->show();
    this->close();


}


void MainWindow::on_pushButton_clicked()
{
    login *L=new login;
    L->show();
    this->close();
}

