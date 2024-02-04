/********************************************************************************
** Form generated from reading UI file 'signin.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNIN_H
#define UI_SIGNIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_signin
{
public:
    QLabel *label;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *username;
    QLineEdit *username_2;
    QLabel *password;
    QLineEdit *password_2;
    QLabel *name;
    QLineEdit *name_2;
    QLabel *email;
    QLineEdit *email_2;
    QLabel *age;
    QLineEdit *age_2;
    QLabel *gender;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox_2;

    void setupUi(QDialog *signin)
    {
        if (signin->objectName().isEmpty())
            signin->setObjectName("signin");
        signin->resize(342, 517);
        label = new QLabel(signin);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 40, 191, 51));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        formLayoutWidget = new QWidget(signin);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(30, 110, 281, 371));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        username = new QLabel(formLayoutWidget);
        username->setObjectName("username");

        formLayout->setWidget(0, QFormLayout::LabelRole, username);

        username_2 = new QLineEdit(formLayoutWidget);
        username_2->setObjectName("username_2");

        formLayout->setWidget(0, QFormLayout::FieldRole, username_2);

        password = new QLabel(formLayoutWidget);
        password->setObjectName("password");

        formLayout->setWidget(1, QFormLayout::LabelRole, password);

        password_2 = new QLineEdit(formLayoutWidget);
        password_2->setObjectName("password_2");

        formLayout->setWidget(1, QFormLayout::FieldRole, password_2);

        name = new QLabel(formLayoutWidget);
        name->setObjectName("name");

        formLayout->setWidget(2, QFormLayout::LabelRole, name);

        name_2 = new QLineEdit(formLayoutWidget);
        name_2->setObjectName("name_2");

        formLayout->setWidget(2, QFormLayout::FieldRole, name_2);

        email = new QLabel(formLayoutWidget);
        email->setObjectName("email");

        formLayout->setWidget(3, QFormLayout::LabelRole, email);

        email_2 = new QLineEdit(formLayoutWidget);
        email_2->setObjectName("email_2");

        formLayout->setWidget(3, QFormLayout::FieldRole, email_2);

        age = new QLabel(formLayoutWidget);
        age->setObjectName("age");

        formLayout->setWidget(4, QFormLayout::LabelRole, age);

        age_2 = new QLineEdit(formLayoutWidget);
        age_2->setObjectName("age_2");

        formLayout->setWidget(4, QFormLayout::FieldRole, age_2);

        gender = new QLabel(formLayoutWidget);
        gender->setObjectName("gender");

        formLayout->setWidget(5, QFormLayout::LabelRole, gender);

        comboBox = new QComboBox(formLayoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        formLayout->setWidget(5, QFormLayout::FieldRole, comboBox);

        buttonBox_2 = new QDialogButtonBox(formLayoutWidget);
        buttonBox_2->setObjectName("buttonBox_2");
        buttonBox_2->setOrientation(Qt::Horizontal);
        buttonBox_2->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(6, QFormLayout::FieldRole, buttonBox_2);


        retranslateUi(signin);

        QMetaObject::connectSlotsByName(signin);
    } // setupUi

    void retranslateUi(QDialog *signin)
    {
        signin->setWindowTitle(QCoreApplication::translate("signin", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("signin", "SIGN IN PAGE", nullptr));
        username->setText(QCoreApplication::translate("signin", "Username", nullptr));
        password->setText(QCoreApplication::translate("signin", "Password", nullptr));
        name->setText(QCoreApplication::translate("signin", "Name", nullptr));
        email->setText(QCoreApplication::translate("signin", "Email", nullptr));
        age->setText(QCoreApplication::translate("signin", "Age", nullptr));
        gender->setText(QCoreApplication::translate("signin", "gender", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("signin", "None_binary", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("signin", "Female", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("signin", "Male", nullptr));
        comboBox->setItemText(3, QString());
        comboBox->setItemText(4, QString());

    } // retranslateUi

};

namespace Ui {
    class signin: public Ui_signin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNIN_H
