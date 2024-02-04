#ifndef NEW_TEAM_H
#define NEW_TEAM_H

#include <QDialog>

namespace Ui {
class new_team;
}

class new_team : public QDialog
{
    Q_OBJECT

public:
    explicit new_team(QWidget *parent = nullptr);
    ~new_team();
signals:
    void newteam_added(QString);
private slots:
    void on_buttonBox_accepted();


private:
    Ui::new_team *ui;
};

#endif // NEW_TEAM_H
