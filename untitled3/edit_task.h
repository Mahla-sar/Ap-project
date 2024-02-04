#ifndef EDIT_TASK_H
#define EDIT_TASK_H

#include <QDialog>

namespace Ui {
class edit_task;
}

class edit_task : public QDialog
{
    Q_OBJECT

public:
    explicit edit_task(QWidget *parent = nullptr);
    ~edit_task();
signals:
    void task_deleted(QString name);
    void content_refreshed(QString name);

private slots:
    void on_pro_button_clicked();

    void on_Memberbutton_clicked();

    void on_teambutton_clicked();

    void on_deletbutton_clicked();

    void on_button_clicked();

private:
    Ui::edit_task *ui;
};

#endif // EDIT_TASK_H
