/********************************************************************************
** Form generated from reading UI file 'edit_team.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_TEAM_H
#define UI_EDIT_TEAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_edit_team
{
public:
    QWidget *formLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *orglabel;
    QPushButton *namebutton;
    QPushButton *promotebutton;
    QPushButton *demotebutton;
    QPushButton *remove;
    QPushButton *add_button;
    QPushButton *deletbutton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_1;
    QLineEdit *textbox;
    QPushButton *button;

    void setupUi(QDialog *edit_team)
    {
        if (edit_team->objectName().isEmpty())
            edit_team->setObjectName("edit_team");
        edit_team->resize(604, 410);
        formLayoutWidget = new QWidget(edit_team);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(20, 60, 206, 238));
        verticalLayout = new QVBoxLayout(formLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        orglabel = new QLabel(formLayoutWidget);
        orglabel->setObjectName("orglabel");

        verticalLayout->addWidget(orglabel);

        namebutton = new QPushButton(formLayoutWidget);
        namebutton->setObjectName("namebutton");

        verticalLayout->addWidget(namebutton);

        promotebutton = new QPushButton(formLayoutWidget);
        promotebutton->setObjectName("promotebutton");

        verticalLayout->addWidget(promotebutton);

        demotebutton = new QPushButton(formLayoutWidget);
        demotebutton->setObjectName("demotebutton");

        verticalLayout->addWidget(demotebutton);

        remove = new QPushButton(formLayoutWidget);
        remove->setObjectName("remove");

        verticalLayout->addWidget(remove);

        add_button = new QPushButton(formLayoutWidget);
        add_button->setObjectName("add_button");

        verticalLayout->addWidget(add_button);

        deletbutton = new QPushButton(formLayoutWidget);
        deletbutton->setObjectName("deletbutton");

        verticalLayout->addWidget(deletbutton);

        gridLayoutWidget = new QWidget(edit_team);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(260, 90, 291, 171));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_1 = new QLabel(gridLayoutWidget);
        label_1->setObjectName("label_1");

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        textbox = new QLineEdit(gridLayoutWidget);
        textbox->setObjectName("textbox");

        gridLayout->addWidget(textbox, 0, 1, 1, 1);

        button = new QPushButton(gridLayoutWidget);
        button->setObjectName("button");

        gridLayout->addWidget(button, 1, 1, 1, 1);


        retranslateUi(edit_team);

        QMetaObject::connectSlotsByName(edit_team);
    } // setupUi

    void retranslateUi(QDialog *edit_team)
    {
        edit_team->setWindowTitle(QCoreApplication::translate("edit_team", "Dialog", nullptr));
        orglabel->setText(QString());
        namebutton->setText(QCoreApplication::translate("edit_team", "change Team's name", nullptr));
        promotebutton->setText(QCoreApplication::translate("edit_team", "promote a member to head", nullptr));
        demotebutton->setText(QCoreApplication::translate("edit_team", "demote an head to memeber", nullptr));
        remove->setText(QCoreApplication::translate("edit_team", "remove member", nullptr));
        add_button->setText(QCoreApplication::translate("edit_team", "Add member ", nullptr));
        deletbutton->setText(QCoreApplication::translate("edit_team", "delete the Team", nullptr));
        label_1->setText(QString());
        button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class edit_team: public Ui_edit_team {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_TEAM_H
