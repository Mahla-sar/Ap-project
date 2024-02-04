/********************************************************************************
** Form generated from reading UI file 'edit_task.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_TASK_H
#define UI_EDIT_TASK_H

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

class Ui_edit_task
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *teambutton;
    QPushButton *deletbutton;
    QPushButton *Memberbutton;
    QPushButton *pro_button;
    QLabel *orglabel;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QLineEdit *textbox;
    QPushButton *button;
    QLabel *label_1;

    void setupUi(QDialog *edit_task)
    {
        if (edit_task->objectName().isEmpty())
            edit_task->setObjectName("edit_task");
        edit_task->resize(519, 422);
        verticalLayoutWidget = new QWidget(edit_task);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 70, 191, 261));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        teambutton = new QPushButton(verticalLayoutWidget);
        teambutton->setObjectName("teambutton");

        verticalLayout->addWidget(teambutton);

        deletbutton = new QPushButton(verticalLayoutWidget);
        deletbutton->setObjectName("deletbutton");

        verticalLayout->addWidget(deletbutton);

        Memberbutton = new QPushButton(verticalLayoutWidget);
        Memberbutton->setObjectName("Memberbutton");

        verticalLayout->addWidget(Memberbutton);

        pro_button = new QPushButton(verticalLayoutWidget);
        pro_button->setObjectName("pro_button");

        verticalLayout->addWidget(pro_button);

        orglabel = new QLabel(edit_task);
        orglabel->setObjectName("orglabel");
        orglabel->setGeometry(QRect(20, 20, 189, 31));
        gridLayoutWidget = new QWidget(edit_task);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(240, 160, 241, 71));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        textbox = new QLineEdit(gridLayoutWidget);
        textbox->setObjectName("textbox");

        gridLayout_2->addWidget(textbox, 2, 0, 1, 1);

        button = new QPushButton(gridLayoutWidget);
        button->setObjectName("button");

        gridLayout_2->addWidget(button, 2, 1, 1, 1);

        label_1 = new QLabel(gridLayoutWidget);
        label_1->setObjectName("label_1");

        gridLayout_2->addWidget(label_1, 1, 0, 1, 1);


        retranslateUi(edit_task);

        QMetaObject::connectSlotsByName(edit_task);
    } // setupUi

    void retranslateUi(QDialog *edit_task)
    {
        edit_task->setWindowTitle(QCoreApplication::translate("edit_task", "Dialog", nullptr));
        teambutton->setText(QCoreApplication::translate("edit_task", "assign Task To a Team", nullptr));
        deletbutton->setText(QCoreApplication::translate("edit_task", "delete the Task", nullptr));
        Memberbutton->setText(QCoreApplication::translate("edit_task", "assign Task To a Member", nullptr));
        pro_button->setText(QCoreApplication::translate("edit_task", "assign Task To a Project", nullptr));
        orglabel->setText(QString());
        button->setText(QString());
        label_1->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class edit_task: public Ui_edit_task {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_TASK_H
