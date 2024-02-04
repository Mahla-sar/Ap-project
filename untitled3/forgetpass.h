#ifndef FORGETPASS_H
#define FORGETPASS_H

#include <QDialog>

namespace Ui {
class forgetpass;
}

class forgetpass : public QDialog
{
    Q_OBJECT

public:
    explicit forgetpass(QWidget *parent = nullptr);
    ~forgetpass();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::forgetpass *ui;
};

#endif // FORGETPASS_H
