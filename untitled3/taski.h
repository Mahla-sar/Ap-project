#ifndef TASKI_H
#define TASKI_H
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMainWindow>
#include <QByteArray>

namespace Ui {
class Taski;
}

class Taski : public QMainWindow
{
    Q_OBJECT

public:
    explicit Taski(QWidget *parent = nullptr);

    ~Taski();
signals:
    void orgname_get(QString name);

private slots:
    //orgs
    void on_pushButton_clicked();
    void addorg(QString name);
    void delete_org(QString name);
    void refreshContent(const QString& name);
    void changename(const QString& before,const QString& after);

    //teams
    void on_addteam_clicked();
    void addteam(QString name);
    void delete_team(QString name);
    void refreshteam(const QString& name);
    void changenameteam(const QString &before, const QString &after);

    //projects
    void on_addpro_clicked();
    void addpro(QString name);
    void delete_pro(QString name);
    void refreshpro(const QString& name);
    void changenamepro(const QString &before, const QString &after);

    //tasks
    void on_addtask_clicked();
    void addtask(QString name);
    void refreshtask(const QString& name);
    void delete_task(QString name);


    void on_archivedtasksbutton_clicked();

    void on_commentbutton_clicked();

private:
    Ui::Taski *ui;
    QHBoxLayout *buttonWidgetLayout;
    QWidget* buttonContainer;
    QList<QPushButton*> orgButtons;
    QList<QString> orgNames;
    QPushButton *membersButton;

    QWidget* buttonContainerteam;
    QList<QPushButton*> teamorgButtons;
    QList<QString> teamorgNames;
    QHBoxLayout *buttonWidgetLayoutteam;
    QList<QPushButton*> orgButtonsteam;
    QList<QString> orgNamesteam;
    QPushButton *membersButtonteam;

    QWidget* buttonContainerpro;
    QList<QPushButton*> proorgButtons;
    QList<QString> proorgNames;
    QHBoxLayout *buttonWidgetLayoutpro;
    QList<QPushButton*> orgButtonspro;
    QList<QString> orgNamespro;
    QPushButton *membersButtonpro;

    QWidget* buttonContainertask;
    QList<QPushButton*> taskorgButtons;
    QList<QString> taskorgNames;
    QHBoxLayout *buttonWidgetLayouttask;
    QList<QPushButton*> orgButtonstask;
    QList<QString> orgNamestask;
    QPushButton *membersButtontask;
};

#endif // TASKI_H
