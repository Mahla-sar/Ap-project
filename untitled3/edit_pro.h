#ifndef EDIT_PRO_H
#define EDIT_PRO_H

#include <QDialog>

namespace Ui {
class edit_pro;
}

class edit_pro : public QDialog
{
    Q_OBJECT

public:
    explicit edit_pro(QWidget *parent = nullptr);
    ~edit_pro();
signals:
    void pro_deleted(QString name);
    void name_changed(QString before , QString after);
    void content_refreshed(QString name);

private slots:
    void on_namebutton_clicked();

    void on_add_button_clicked();

    void on_deletbutton_clicked();

    void on_remove_clicked();

    void on_button_clicked();

private:
    Ui::edit_pro *ui;
};

#endif // EDIT_PRO_H
