/********************************************************************************
** Form generated from reading UI file 'forgetpass.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORGETPASS_H
#define UI_FORGETPASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_forgetpass
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *username;
    QLineEdit *username_2;
    QLineEdit *name_2;
    QLabel *name;
    QLabel *email;
    QLineEdit *email_2;
    QLineEdit *age_2;
    QLabel *age;
    QLabel *password;
    QLineEdit *password_2;

    void setupUi(QDialog *forgetpass)
    {
        if (forgetpass->objectName().isEmpty())
            forgetpass->setObjectName("forgetpass");
        forgetpass->resize(298, 423);
        buttonBox = new QDialogButtonBox(forgetpass);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(60, 350, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(forgetpass);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 20, 201, 51));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        formLayoutWidget = new QWidget(forgetpass);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(10, 80, 281, 204));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        username = new QLabel(formLayoutWidget);
        username->setObjectName("username");

        formLayout->setWidget(0, QFormLayout::LabelRole, username);

        username_2 = new QLineEdit(formLayoutWidget);
        username_2->setObjectName("username_2");

        formLayout->setWidget(0, QFormLayout::FieldRole, username_2);

        name_2 = new QLineEdit(formLayoutWidget);
        name_2->setObjectName("name_2");

        formLayout->setWidget(1, QFormLayout::FieldRole, name_2);

        name = new QLabel(formLayoutWidget);
        name->setObjectName("name");

        formLayout->setWidget(1, QFormLayout::LabelRole, name);

        email = new QLabel(formLayoutWidget);
        email->setObjectName("email");

        formLayout->setWidget(2, QFormLayout::LabelRole, email);

        email_2 = new QLineEdit(formLayoutWidget);
        email_2->setObjectName("email_2");

        formLayout->setWidget(2, QFormLayout::FieldRole, email_2);

        age_2 = new QLineEdit(formLayoutWidget);
        age_2->setObjectName("age_2");

        formLayout->setWidget(3, QFormLayout::FieldRole, age_2);

        age = new QLabel(formLayoutWidget);
        age->setObjectName("age");

        formLayout->setWidget(3, QFormLayout::LabelRole, age);

        password = new QLabel(formLayoutWidget);
        password->setObjectName("password");

        formLayout->setWidget(4, QFormLayout::LabelRole, password);

        password_2 = new QLineEdit(formLayoutWidget);
        password_2->setObjectName("password_2");

        formLayout->setWidget(4, QFormLayout::FieldRole, password_2);


        retranslateUi(forgetpass);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, forgetpass, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, forgetpass, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(forgetpass);
    } // setupUi

    void retranslateUi(QDialog *forgetpass)
    {
        forgetpass->setWindowTitle(QCoreApplication::translate("forgetpass", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("forgetpass", "Forget Password", nullptr));
        username->setText(QCoreApplication::translate("forgetpass", "Entered username", nullptr));
        name->setText(QCoreApplication::translate("forgetpass", "Entered Name", nullptr));
        email->setText(QCoreApplication::translate("forgetpass", "Entered Email", nullptr));
        age->setText(QCoreApplication::translate("forgetpass", "Entered Age", nullptr));
        password->setText(QCoreApplication::translate("forgetpass", "New password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class forgetpass: public Ui_forgetpass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORGETPASS_H
