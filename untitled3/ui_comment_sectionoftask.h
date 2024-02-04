/********************************************************************************
** Form generated from reading UI file 'comment_sectionoftask.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMENT_SECTIONOFTASK_H
#define UI_COMMENT_SECTIONOFTASK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_comment_sectionoftask
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *comment_sectionoftask)
    {
        if (comment_sectionoftask->objectName().isEmpty())
            comment_sectionoftask->setObjectName("comment_sectionoftask");
        comment_sectionoftask->resize(624, 445);
        verticalLayout = new QVBoxLayout(comment_sectionoftask);
        verticalLayout->setObjectName("verticalLayout");
        listWidget = new QListWidget(comment_sectionoftask);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);

        lineEdit = new QLineEdit(comment_sectionoftask);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(comment_sectionoftask);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);


        retranslateUi(comment_sectionoftask);

        QMetaObject::connectSlotsByName(comment_sectionoftask);
    } // setupUi

    void retranslateUi(QDialog *comment_sectionoftask)
    {
        comment_sectionoftask->setWindowTitle(QCoreApplication::translate("comment_sectionoftask", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("comment_sectionoftask", "COMMENT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class comment_sectionoftask: public Ui_comment_sectionoftask {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMENT_SECTIONOFTASK_H
