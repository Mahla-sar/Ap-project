/********************************************************************************
** Form generated from reading UI file 'edit_pro.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_PRO_H
#define UI_EDIT_PRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_edit_pro
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *orglabel;
    QPushButton *namebutton;
    QPushButton *add_button;
    QHBoxLayout *horizontalLayout;
    QPushButton *remove;
    QPushButton *deletbutton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *textbox;
    QPushButton *button;
    QLabel *label_1;

    void setupUi(QDialog *edit_pro)
    {
        if (edit_pro->objectName().isEmpty())
            edit_pro->setObjectName("edit_pro");
        edit_pro->resize(531, 306);
        verticalLayoutWidget = new QWidget(edit_pro);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 30, 191, 221));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");

        verticalLayout->addLayout(horizontalLayout_2);

        orglabel = new QLabel(verticalLayoutWidget);
        orglabel->setObjectName("orglabel");

        verticalLayout->addWidget(orglabel);

        namebutton = new QPushButton(verticalLayoutWidget);
        namebutton->setObjectName("namebutton");

        verticalLayout->addWidget(namebutton);

        add_button = new QPushButton(verticalLayoutWidget);
        add_button->setObjectName("add_button");

        verticalLayout->addWidget(add_button);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        remove = new QPushButton(verticalLayoutWidget);
        remove->setObjectName("remove");

        horizontalLayout->addWidget(remove);


        verticalLayout->addLayout(horizontalLayout);

        deletbutton = new QPushButton(verticalLayoutWidget);
        deletbutton->setObjectName("deletbutton");

        verticalLayout->addWidget(deletbutton);

        gridLayoutWidget = new QWidget(edit_pro);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(260, 100, 221, 93));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        textbox = new QLineEdit(gridLayoutWidget);
        textbox->setObjectName("textbox");

        gridLayout->addWidget(textbox, 0, 1, 1, 1);

        button = new QPushButton(gridLayoutWidget);
        button->setObjectName("button");

        gridLayout->addWidget(button, 2, 1, 1, 1);

        label_1 = new QLabel(gridLayoutWidget);
        label_1->setObjectName("label_1");

        gridLayout->addWidget(label_1, 0, 0, 1, 1);


        retranslateUi(edit_pro);

        QMetaObject::connectSlotsByName(edit_pro);
    } // setupUi

    void retranslateUi(QDialog *edit_pro)
    {
        edit_pro->setWindowTitle(QCoreApplication::translate("edit_pro", "Dialog", nullptr));
        orglabel->setText(QString());
        namebutton->setText(QCoreApplication::translate("edit_pro", "change Project's name", nullptr));
        add_button->setText(QCoreApplication::translate("edit_pro", "Add member ", nullptr));
        remove->setText(QCoreApplication::translate("edit_pro", "remove member", nullptr));
        deletbutton->setText(QCoreApplication::translate("edit_pro", "delete the Project", nullptr));
        button->setText(QString());
        label_1->setText(QCoreApplication::translate("edit_pro", "k", nullptr));
    } // retranslateUi

};

namespace Ui {
    class edit_pro: public Ui_edit_pro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_PRO_H
