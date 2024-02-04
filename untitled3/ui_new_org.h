/********************************************************************************
** Form generated from reading UI file 'new_org.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEW_ORG_H
#define UI_NEW_ORG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_new_org
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *new_org)
    {
        if (new_org->objectName().isEmpty())
            new_org->setObjectName("new_org");
        new_org->resize(305, 154);
        buttonBox = new QDialogButtonBox(new_org);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(70, 100, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(new_org);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(180, 50, 113, 28));
        label = new QLabel(new_org);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 50, 151, 20));

        retranslateUi(new_org);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, new_org, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, new_org, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(new_org);
    } // setupUi

    void retranslateUi(QDialog *new_org)
    {
        new_org->setWindowTitle(QCoreApplication::translate("new_org", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("new_org", "add a new Organization", nullptr));
    } // retranslateUi

};

namespace Ui {
    class new_org: public Ui_new_org {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEW_ORG_H
