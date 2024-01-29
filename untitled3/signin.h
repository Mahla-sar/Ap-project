#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>

namespace Ui {
class signin;
}

class signin : public QDialog
{
    Q_OBJECT

public:
    explicit signin(QWidget *parent = nullptr);
    ~signin();

signals:
    void sendinfo(QString);

private slots:





    void on_buttonBox_2_accepted();

    void on_buttonBox_2_rejected();

private:
    Ui::signin *ui;

};

#endif // SIGNIN_H
