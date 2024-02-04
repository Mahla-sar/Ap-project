/********************************************************************************
** Form generated from reading UI file 'edit_org.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_ORG_H
#define UI_EDIT_ORG_H

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

class Ui_edit_org
{
public:
    QLabel *orglabel;
    QWidget *formLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *add_button;
    QPushButton *remove;
    QPushButton *promotebutton;
    QPushButton *deletbutton;
    QPushButton *demotebutton;
    QPushButton *namebutton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *Button;

    void setupUi(QDialog *edit_org)
    {
        if (edit_org->objectName().isEmpty())
            edit_org->setObjectName("edit_org");
        edit_org->resize(590, 333);
        orglabel = new QLabel(edit_org);
        orglabel->setObjectName("orglabel");
        orglabel->setGeometry(QRect(40, 20, 171, 20));
        formLayoutWidget = new QWidget(edit_org);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(30, 50, 221, 241));
        verticalLayout_2 = new QVBoxLayout(formLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        add_button = new QPushButton(formLayoutWidget);
        add_button->setObjectName("add_button");

        verticalLayout_2->addWidget(add_button);

        remove = new QPushButton(formLayoutWidget);
        remove->setObjectName("remove");

        verticalLayout_2->addWidget(remove);

        promotebutton = new QPushButton(formLayoutWidget);
        promotebutton->setObjectName("promotebutton");

        verticalLayout_2->addWidget(promotebutton);

        deletbutton = new QPushButton(formLayoutWidget);
        deletbutton->setObjectName("deletbutton");

        verticalLayout_2->addWidget(deletbutton);

        demotebutton = new QPushButton(formLayoutWidget);
        demotebutton->setObjectName("demotebutton");

        verticalLayout_2->addWidget(demotebutton);

        namebutton = new QPushButton(formLayoutWidget);
        namebutton->setObjectName("namebutton");

        verticalLayout_2->addWidget(namebutton);

        gridLayoutWidget = new QWidget(edit_org);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(310, 100, 231, 61));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName("lineEdit");

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        Button = new QPushButton(edit_org);
        Button->setObjectName("Button");
        Button->setGeometry(QRect(420, 170, 121, 29));

        retranslateUi(edit_org);

        QMetaObject::connectSlotsByName(edit_org);
    } // setupUi

    void retranslateUi(QDialog *edit_org)
    {
        edit_org->setWindowTitle(QCoreApplication::translate("edit_org", "Dialog", nullptr));
        orglabel->setText(QString());
        add_button->setText(QCoreApplication::translate("edit_org", "Add member ", nullptr));
        remove->setText(QCoreApplication::translate("edit_org", "remove member", nullptr));
        promotebutton->setText(QCoreApplication::translate("edit_org", "promote a member to admin", nullptr));
        deletbutton->setText(QCoreApplication::translate("edit_org", "delete the orgenization", nullptr));
        demotebutton->setText(QCoreApplication::translate("edit_org", "demote an admin to memeber", nullptr));
        namebutton->setText(QCoreApplication::translate("edit_org", "change organization's name", nullptr));
        label->setText(QString());
        Button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class edit_org: public Ui_edit_org {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_ORG_H
