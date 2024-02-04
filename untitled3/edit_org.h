#ifndef EDIT_ORG_H
#define EDIT_ORG_H

#include <QDialog>

namespace Ui {
class edit_org;
}

class edit_org : public QDialog
{
    Q_OBJECT

public:
    explicit edit_org(QWidget *parent = nullptr);
    ~edit_org();

signals:
    void org_deleted(QString name);
    void name_changed(QString before , QString after);
    void content_refreshed(QString name);
private slots:

    void on_promotebutton_clicked();



    void on_Button_clicked();

    void on_namebutton_clicked();

    void on_deletbutton_clicked();

    void on_add_button_clicked();

    void on_demotebutton_clicked();




    void on_remove_clicked();

private:
    Ui::edit_org *ui;
};

#endif // EDIT_ORG_H
