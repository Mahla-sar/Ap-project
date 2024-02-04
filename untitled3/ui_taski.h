/********************************************************************************
** Form generated from reading UI file 'taski.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKI_H
#define UI_TASKI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Taski
{
public:
    QWidget *centralwidget;
    QListWidget *owner;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *org_label;
    QLabel *ownerlbl;
    QTabWidget *tabWidget;
    QWidget *Teamtab;
    QListWidget *teamlist;
    QPushButton *addteam;
    QLineEdit *ownerteam;
    QLabel *teamlbl;
    QLabel *ownerlblteam;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_6;
    QLabel *headslbl;
    QListWidget *headslist;
    QLabel *memberslblteam;
    QListWidget *teammemberslist;
    QLabel *tasklblteam;
    QListWidget *taskteam;
    QWidget *protab;
    QLabel *projectlbl;
    QListWidget *prolist;
    QPushButton *addpro;
    QLabel *ownerlblpro;
    QListWidget *ownerprolist;
    QWidget *formLayoutWidget_3;
    QFormLayout *formLayout_7;
    QLabel *headslblpro;
    QListWidget *headslistpro;
    QLabel *memberslblpro;
    QListWidget *promemberslist;
    QLabel *tasklblpro;
    QListWidget *taskpro;
    QWidget *Tasktab;
    QPushButton *addtask;
    QListWidget *tasklist;
    QLabel *tasklbl;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *archivedtasksbutton;
    QPushButton *commentbutton;
    QFormLayout *formLayout_8;
    QLabel *deslbl;
    QLabel *assignmemberlbl;
    QListWidget *taskmemberlist;
    QListWidget *descriptiontext;
    QLabel *assignprolbl;
    QListWidget *protext;
    QLabel *assignteamlbl;
    QListWidget *teamtext;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QListWidget *orgs;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout_5;
    QLabel *adminslbl;
    QLabel *memberslbl;
    QListWidget *memberslist;
    QListWidget *adminslist;
    QLabel *label;
    QLabel *welcomlbl;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Taski)
    {
        if (Taski->objectName().isEmpty())
            Taski->setObjectName("Taski");
        Taski->setEnabled(true);
        Taski->resize(1307, 692);
        centralwidget = new QWidget(Taski);
        centralwidget->setObjectName("centralwidget");
        owner = new QListWidget(centralwidget);
        owner->setObjectName("owner");
        owner->setGeometry(QRect(550, 120, 141, 31));
        owner->setMouseTracking(false);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 220, 101, 251));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        org_label = new QLabel(centralwidget);
        org_label->setObjectName("org_label");
        org_label->setGeometry(QRect(450, 80, 211, 31));
        QFont font;
        font.setPointSize(14);
        org_label->setFont(font);
        ownerlbl = new QLabel(centralwidget);
        ownerlbl->setObjectName("ownerlbl");
        ownerlbl->setGeometry(QRect(460, 120, 91, 21));
        QFont font1;
        font1.setPointSize(12);
        ownerlbl->setFont(font1);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(740, 80, 531, 551));
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        Teamtab = new QWidget();
        Teamtab->setObjectName("Teamtab");
        teamlist = new QListWidget(Teamtab);
        teamlist->setObjectName("teamlist");
        teamlist->setGeometry(QRect(20, 70, 256, 431));
        addteam = new QPushButton(Teamtab);
        addteam->setObjectName("addteam");
        addteam->setGeometry(QRect(220, 30, 41, 29));
        ownerteam = new QLineEdit(Teamtab);
        ownerteam->setObjectName("ownerteam");
        ownerteam->setGeometry(QRect(380, 30, 141, 28));
        teamlbl = new QLabel(Teamtab);
        teamlbl->setObjectName("teamlbl");
        teamlbl->setGeometry(QRect(20, 30, 81, 20));
        ownerlblteam = new QLabel(Teamtab);
        ownerlblteam->setObjectName("ownerlblteam");
        ownerlblteam->setGeometry(QRect(310, 40, 63, 20));
        formLayoutWidget_2 = new QWidget(Teamtab);
        formLayoutWidget_2->setObjectName("formLayoutWidget_2");
        formLayoutWidget_2->setGeometry(QRect(310, 70, 211, 421));
        formLayout_6 = new QFormLayout(formLayoutWidget_2);
        formLayout_6->setObjectName("formLayout_6");
        formLayout_6->setContentsMargins(0, 0, 0, 0);
        headslbl = new QLabel(formLayoutWidget_2);
        headslbl->setObjectName("headslbl");

        formLayout_6->setWidget(0, QFormLayout::LabelRole, headslbl);

        headslist = new QListWidget(formLayoutWidget_2);
        headslist->setObjectName("headslist");

        formLayout_6->setWidget(0, QFormLayout::FieldRole, headslist);

        memberslblteam = new QLabel(formLayoutWidget_2);
        memberslblteam->setObjectName("memberslblteam");

        formLayout_6->setWidget(1, QFormLayout::LabelRole, memberslblteam);

        teammemberslist = new QListWidget(formLayoutWidget_2);
        teammemberslist->setObjectName("teammemberslist");

        formLayout_6->setWidget(1, QFormLayout::FieldRole, teammemberslist);

        tasklblteam = new QLabel(formLayoutWidget_2);
        tasklblteam->setObjectName("tasklblteam");

        formLayout_6->setWidget(2, QFormLayout::LabelRole, tasklblteam);

        taskteam = new QListWidget(formLayoutWidget_2);
        taskteam->setObjectName("taskteam");

        formLayout_6->setWidget(2, QFormLayout::FieldRole, taskteam);

        tabWidget->addTab(Teamtab, QString());
        protab = new QWidget();
        protab->setObjectName("protab");
        projectlbl = new QLabel(protab);
        projectlbl->setObjectName("projectlbl");
        projectlbl->setGeometry(QRect(20, 30, 81, 20));
        prolist = new QListWidget(protab);
        prolist->setObjectName("prolist");
        prolist->setGeometry(QRect(20, 70, 256, 431));
        addpro = new QPushButton(protab);
        addpro->setObjectName("addpro");
        addpro->setGeometry(QRect(220, 30, 41, 29));
        ownerlblpro = new QLabel(protab);
        ownerlblpro->setObjectName("ownerlblpro");
        ownerlblpro->setGeometry(QRect(310, 30, 63, 20));
        ownerprolist = new QListWidget(protab);
        ownerprolist->setObjectName("ownerprolist");
        ownerprolist->setGeometry(QRect(380, 20, 131, 31));
        formLayoutWidget_3 = new QWidget(protab);
        formLayoutWidget_3->setObjectName("formLayoutWidget_3");
        formLayoutWidget_3->setGeometry(QRect(310, 70, 211, 421));
        formLayout_7 = new QFormLayout(formLayoutWidget_3);
        formLayout_7->setObjectName("formLayout_7");
        formLayout_7->setContentsMargins(0, 0, 0, 0);
        headslblpro = new QLabel(formLayoutWidget_3);
        headslblpro->setObjectName("headslblpro");

        formLayout_7->setWidget(0, QFormLayout::LabelRole, headslblpro);

        headslistpro = new QListWidget(formLayoutWidget_3);
        headslistpro->setObjectName("headslistpro");

        formLayout_7->setWidget(0, QFormLayout::FieldRole, headslistpro);

        memberslblpro = new QLabel(formLayoutWidget_3);
        memberslblpro->setObjectName("memberslblpro");

        formLayout_7->setWidget(1, QFormLayout::LabelRole, memberslblpro);

        promemberslist = new QListWidget(formLayoutWidget_3);
        promemberslist->setObjectName("promemberslist");

        formLayout_7->setWidget(1, QFormLayout::FieldRole, promemberslist);

        tasklblpro = new QLabel(formLayoutWidget_3);
        tasklblpro->setObjectName("tasklblpro");

        formLayout_7->setWidget(2, QFormLayout::LabelRole, tasklblpro);

        taskpro = new QListWidget(formLayoutWidget_3);
        taskpro->setObjectName("taskpro");

        formLayout_7->setWidget(2, QFormLayout::FieldRole, taskpro);

        tabWidget->addTab(protab, QString());
        Tasktab = new QWidget();
        Tasktab->setObjectName("Tasktab");
        addtask = new QPushButton(Tasktab);
        addtask->setObjectName("addtask");
        addtask->setGeometry(QRect(220, 30, 41, 29));
        tasklist = new QListWidget(Tasktab);
        tasklist->setObjectName("tasklist");
        tasklist->setGeometry(QRect(20, 70, 256, 431));
        tasklbl = new QLabel(Tasktab);
        tasklbl->setObjectName("tasklbl");
        tasklbl->setGeometry(QRect(20, 30, 81, 20));
        verticalLayoutWidget_2 = new QWidget(Tasktab);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(290, 30, 221, 381));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        archivedtasksbutton = new QPushButton(verticalLayoutWidget_2);
        archivedtasksbutton->setObjectName("archivedtasksbutton");

        verticalLayout_4->addWidget(archivedtasksbutton);

        commentbutton = new QPushButton(verticalLayoutWidget_2);
        commentbutton->setObjectName("commentbutton");

        verticalLayout_4->addWidget(commentbutton);

        formLayout_8 = new QFormLayout();
        formLayout_8->setObjectName("formLayout_8");
        deslbl = new QLabel(verticalLayoutWidget_2);
        deslbl->setObjectName("deslbl");

        formLayout_8->setWidget(0, QFormLayout::LabelRole, deslbl);

        assignmemberlbl = new QLabel(verticalLayoutWidget_2);
        assignmemberlbl->setObjectName("assignmemberlbl");

        formLayout_8->setWidget(1, QFormLayout::LabelRole, assignmemberlbl);

        taskmemberlist = new QListWidget(verticalLayoutWidget_2);
        taskmemberlist->setObjectName("taskmemberlist");

        formLayout_8->setWidget(1, QFormLayout::FieldRole, taskmemberlist);

        descriptiontext = new QListWidget(verticalLayoutWidget_2);
        descriptiontext->setObjectName("descriptiontext");

        formLayout_8->setWidget(0, QFormLayout::FieldRole, descriptiontext);


        verticalLayout_4->addLayout(formLayout_8);

        assignprolbl = new QLabel(Tasktab);
        assignprolbl->setObjectName("assignprolbl");
        assignprolbl->setGeometry(QRect(290, 420, 94, 26));
        protext = new QListWidget(Tasktab);
        protext->setObjectName("protext");
        protext->setGeometry(QRect(410, 420, 101, 31));
        assignteamlbl = new QLabel(Tasktab);
        assignteamlbl->setObjectName("assignteamlbl");
        assignteamlbl->setGeometry(QRect(290, 460, 81, 35));
        teamtext = new QListWidget(Tasktab);
        teamtext->setObjectName("teamtext");
        teamtext->setGeometry(QRect(410, 460, 101, 31));
        tabWidget->addTab(Tasktab, QString());
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(70, 90, 361, 541));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName("pushButton");
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(false);
        pushButton->setFont(font2);

        gridLayout_2->addWidget(pushButton, 0, 0, 1, 1);

        orgs = new QListWidget(gridLayoutWidget);
        orgs->setObjectName("orgs");

        gridLayout_2->addWidget(orgs, 1, 0, 2, 1);

        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(460, 170, 231, 461));
        formLayout_5 = new QFormLayout(formLayoutWidget);
        formLayout_5->setObjectName("formLayout_5");
        formLayout_5->setContentsMargins(0, 0, 0, 0);
        adminslbl = new QLabel(formLayoutWidget);
        adminslbl->setObjectName("adminslbl");
        adminslbl->setFont(font1);

        formLayout_5->setWidget(0, QFormLayout::LabelRole, adminslbl);

        memberslbl = new QLabel(formLayoutWidget);
        memberslbl->setObjectName("memberslbl");
        memberslbl->setFont(font1);

        formLayout_5->setWidget(1, QFormLayout::LabelRole, memberslbl);

        memberslist = new QListWidget(formLayoutWidget);
        memberslist->setObjectName("memberslist");

        formLayout_5->setWidget(1, QFormLayout::FieldRole, memberslist);

        adminslist = new QListWidget(formLayoutWidget);
        adminslist->setObjectName("adminslist");

        formLayout_5->setWidget(0, QFormLayout::FieldRole, adminslist);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 30, 281, 71));
        label->setFont(font);
        welcomlbl = new QLabel(centralwidget);
        welcomlbl->setObjectName("welcomlbl");
        welcomlbl->setGeometry(QRect(520, 0, 241, 78));
        welcomlbl->setFont(font);
        Taski->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Taski);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1307, 25));
        Taski->setMenuBar(menubar);
        statusbar = new QStatusBar(Taski);
        statusbar->setObjectName("statusbar");
        Taski->setStatusBar(statusbar);

        retranslateUi(Taski);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Taski);
    } // setupUi

    void retranslateUi(QMainWindow *Taski)
    {
        Taski->setWindowTitle(QCoreApplication::translate("Taski", "MainWindow", nullptr));
        org_label->setText(QCoreApplication::translate("Taski", "name of org", nullptr));
        ownerlbl->setText(QCoreApplication::translate("Taski", "Owner ", nullptr));
        addteam->setText(QCoreApplication::translate("Taski", "+", nullptr));
        teamlbl->setText(QCoreApplication::translate("Taski", "TextLabel", nullptr));
        ownerlblteam->setText(QCoreApplication::translate("Taski", "Owner", nullptr));
        headslbl->setText(QCoreApplication::translate("Taski", "Heads", nullptr));
        memberslblteam->setText(QCoreApplication::translate("Taski", "Members", nullptr));
        tasklblteam->setText(QCoreApplication::translate("Taski", "tasks", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Teamtab), QCoreApplication::translate("Taski", "Teams", nullptr));
        projectlbl->setText(QCoreApplication::translate("Taski", "TextLabel", nullptr));
        addpro->setText(QCoreApplication::translate("Taski", "+", nullptr));
        ownerlblpro->setText(QCoreApplication::translate("Taski", "Owner", nullptr));
        headslblpro->setText(QCoreApplication::translate("Taski", "Heads", nullptr));
        memberslblpro->setText(QCoreApplication::translate("Taski", "Members", nullptr));
        tasklblpro->setText(QCoreApplication::translate("Taski", "Tasks", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(protab), QCoreApplication::translate("Taski", "Projects", nullptr));
        addtask->setText(QCoreApplication::translate("Taski", "+", nullptr));
        tasklbl->setText(QCoreApplication::translate("Taski", "TextLabel", nullptr));
        archivedtasksbutton->setText(QCoreApplication::translate("Taski", "Archived tasks", nullptr));
        commentbutton->setText(QCoreApplication::translate("Taski", "comments", nullptr));
        deslbl->setText(QCoreApplication::translate("Taski", "Description", nullptr));
        assignmemberlbl->setText(QCoreApplication::translate("Taski", "Assign members", nullptr));
        assignprolbl->setText(QCoreApplication::translate("Taski", "Assign project", nullptr));
        assignteamlbl->setText(QCoreApplication::translate("Taski", "Assign team", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Tasktab), QCoreApplication::translate("Taski", "Tasks", nullptr));
        pushButton->setText(QCoreApplication::translate("Taski", "+", nullptr));
        adminslbl->setText(QCoreApplication::translate("Taski", "Admins", nullptr));
        memberslbl->setText(QCoreApplication::translate("Taski", "Members", nullptr));
        label->setText(QCoreApplication::translate("Taski", "my orgnizations", nullptr));
        welcomlbl->setText(QCoreApplication::translate("Taski", "welcome person", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Taski: public Ui_Taski {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKI_H
