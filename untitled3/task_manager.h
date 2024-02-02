#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H
#include <QDialog>


class Task_manager
{
public:
    void createTask(const QString& OrgName, const QString& taskName , const QString& description );
    void deleteTask(const QString& OrgName, const QString& taskName);
    void archiveTask(const QString& taskName);
    bool isTaskArchived(const QString& taskName);
    void unarchiveTask(const QString& taskName);
    void assignTaskToMember(const QString& taskName, const QString& memberUsernames) ;
    void assignTaskToTeam(const QString& taskName, const QString& teamName);
    void assignTaskToProject(const QString& taskName, const QString& teamName);



private:


};

#endif // TASK_MANAGER_H
