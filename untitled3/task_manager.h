#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H
#include <QDialog>


class Task_manager
{
public:
    void createTask(const QString& OrgName, const QString& taskName);
    void deleteTask(const QString& OrgName, const QString& taskName);



private:


};

#endif // TASK_MANAGER_H
