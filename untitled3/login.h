#ifndef LOGINP_H
#define LOGINP_H

#include <QDialog>
extern QString globalString;
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
     QString getMyName() const;
    QString myname;
    ~login();

signals:
        void loginSuccess(const QString &username);

private slots:
    void on_buttonBox_2_accepted();

    void on_buttonBox_2_rejected();

    void on_pushButton_clicked();

private:
    Ui::login *ui;
    // QString myname;
};

#endif // LOGINP_H
