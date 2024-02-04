/********************************************************************************
** Form generated from reading UI file 'new_task.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEW_TASK_H
#define UI_NEW_TASK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_new_task
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *namegetter;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *descriptiongetter;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *new_task)
    {
        if (new_task->objectName().isEmpty())
            new_task->setObjectName("new_task");
        new_task->resize(403, 282);
        formLayoutWidget = new QWidget(new_task);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(10, 40, 381, 221));
        formLayout_2 = new QFormLayout(formLayoutWidget);
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        namegetter = new QLineEdit(formLayoutWidget);
        namegetter->setObjectName("namegetter");

        formLayout_2->setWidget(0, QFormLayout::FieldRole, namegetter);

        dateTimeEdit = new QDateTimeEdit(formLayoutWidget);
        dateTimeEdit->setObjectName("dateTimeEdit");

        formLayout_2->setWidget(1, QFormLayout::FieldRole, dateTimeEdit);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_3);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_2);

        descriptiongetter = new QLineEdit(formLayoutWidget);
        descriptiongetter->setObjectName("descriptiongetter");

        formLayout_2->setWidget(2, QFormLayout::FieldRole, descriptiongetter);

        buttonBox = new QDialogButtonBox(formLayoutWidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, buttonBox);


        retranslateUi(new_task);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, new_task, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, new_task, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(new_task);
    } // setupUi

    void retranslateUi(QDialog *new_task)
    {
        new_task->setWindowTitle(QCoreApplication::translate("new_task", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("new_task", "choose a name", nullptr));
        label_3->setText(QCoreApplication::translate("new_task", "choose time till finish", nullptr));
        label_2->setText(QCoreApplication::translate("new_task", "add description", nullptr));
    } // retranslateUi

};

namespace Ui {
    class new_task: public Ui_new_task {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEW_TASK_H
