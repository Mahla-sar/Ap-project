/********************************************************************************
** Form generated from reading UI file 'new_pro.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEW_PRO_H
#define UI_NEW_PRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_new_pro
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *new_pro)
    {
        if (new_pro->objectName().isEmpty())
            new_pro->setObjectName("new_pro");
        new_pro->resize(310, 149);
        buttonBox = new QDialogButtonBox(new_pro);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(50, 90, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(new_pro);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(160, 50, 113, 28));
        label = new QLabel(new_pro);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 50, 131, 20));

        retranslateUi(new_pro);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, new_pro, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, new_pro, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(new_pro);
    } // setupUi

    void retranslateUi(QDialog *new_pro)
    {
        new_pro->setWindowTitle(QCoreApplication::translate("new_pro", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("new_pro", "add new a project", nullptr));
    } // retranslateUi

};

namespace Ui {
    class new_pro: public Ui_new_pro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEW_PRO_H
