#ifndef EDIT_TEAM_H
#define EDIT_TEAM_H

#include <QDialog>

namespace Ui {
class edit_team;
}

class edit_team : public QDialog
{
    Q_OBJECT

public:
    explicit edit_team(QWidget *parent = nullptr);
    ~edit_team();
signals:
    void team_deleted(QString name);
    void name_changed(QString before , QString after);
    void content_refreshed(QString name);

private slots:
    void on_namebutton_clicked();

    void on_add_button_clicked();

    void on_deletbutton_clicked();

    void on_remove_clicked();

    void on_promotebutton_clicked();

    void on_demotebutton_clicked();

    void on_button_clicked();

private:
    Ui::edit_team *ui;
};

#endif // EDIT_TEAM_H
