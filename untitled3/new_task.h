#ifndef NEW_TASK_H
#define NEW_TASK_H

#include <QDialog>

namespace Ui {
class new_task;
}

class new_task : public QDialog
{
    Q_OBJECT

public:
    explicit new_task(QWidget *parent = nullptr);
    ~new_task();
signals:
    void newtask_added(QString);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::new_task *ui;
};

#endif // NEW_TASK_H
