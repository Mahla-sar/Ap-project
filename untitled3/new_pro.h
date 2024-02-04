#ifndef NEW_PRO_H
#define NEW_PRO_H

#include <QDialog>

namespace Ui {
class new_pro;
}

class new_pro : public QDialog
{
    Q_OBJECT

public:
    explicit new_pro(QWidget *parent = nullptr);
    ~new_pro();

private slots:
    void on_buttonBox_accepted();
signals:
    void newpro_added(QString);
private:
    Ui::new_pro *ui;
};

#endif // NEW_PRO_H
