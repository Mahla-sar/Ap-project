/********************************************************************************
** Form generated from reading UI file 'archived_tasks.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARCHIVED_TASKS_H
#define UI_ARCHIVED_TASKS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Archived_tasks
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QListWidget *archivedlist;
    QPushButton *close;

    void setupUi(QDialog *Archived_tasks)
    {
        if (Archived_tasks->objectName().isEmpty())
            Archived_tasks->setObjectName("Archived_tasks");
        Archived_tasks->resize(367, 473);
        verticalLayout_2 = new QVBoxLayout(Archived_tasks);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");

        verticalLayout_2->addLayout(verticalLayout);

        archivedlist = new QListWidget(Archived_tasks);
        archivedlist->setObjectName("archivedlist");

        verticalLayout_2->addWidget(archivedlist);

        close = new QPushButton(Archived_tasks);
        close->setObjectName("close");

        verticalLayout_2->addWidget(close);


        retranslateUi(Archived_tasks);

        QMetaObject::connectSlotsByName(Archived_tasks);
    } // setupUi

    void retranslateUi(QDialog *Archived_tasks)
    {
        Archived_tasks->setWindowTitle(QCoreApplication::translate("Archived_tasks", "Dialog", nullptr));
        close->setText(QCoreApplication::translate("Archived_tasks", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Archived_tasks: public Ui_Archived_tasks {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARCHIVED_TASKS_H
