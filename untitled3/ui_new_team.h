/********************************************************************************
** Form generated from reading UI file 'new_team.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEW_TEAM_H
#define UI_NEW_TEAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_new_team
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *new_team)
    {
        if (new_team->objectName().isEmpty())
            new_team->setObjectName("new_team");
        new_team->resize(240, 146);
        buttonBox = new QDialogButtonBox(new_team);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(10, 90, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(new_team);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(110, 40, 113, 28));
        label = new QLabel(new_team);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 40, 111, 20));

        retranslateUi(new_team);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, new_team, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, new_team, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(new_team);
    } // setupUi

    void retranslateUi(QDialog *new_team)
    {
        new_team->setWindowTitle(QCoreApplication::translate("new_team", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("new_team", "Add new team", nullptr));
    } // retranslateUi

};

namespace Ui {
    class new_team: public Ui_new_team {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEW_TEAM_H
