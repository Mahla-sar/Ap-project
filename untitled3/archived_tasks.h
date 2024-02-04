#ifndef ARCHIVED_TASKS_H
#define ARCHIVED_TASKS_H
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMainWindow>
#include <QByteArray>
#include <QDialog>

namespace Ui {
class Archived_tasks;
}

class Archived_tasks : public QDialog
{
    Q_OBJECT

public:
    explicit Archived_tasks(QWidget *parent = nullptr);
    ~Archived_tasks();
signals:
    void task_unarchived(QString);


private slots:
    void on_close_clicked();
    void addlist(QString name);
    void delete_task(QString name);


private:
    QHBoxLayout *buttonWidgetLayout;
    QWidget* buttonContainer;
    QList<QPushButton*> orgButtons;
    QList<QString> orgNames;
    QPushButton *membersButton;
    Ui::Archived_tasks *ui;
};

#endif // ARCHIVED_TASKS_H
