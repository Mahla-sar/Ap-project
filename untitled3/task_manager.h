#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H
#include <QDialog>


class Task_manager
{
public:
    static QString get_task();
    static void settask(const QString &task_name);
    static QString getDueDate(const QString &taskName);
    void createTask(const QString& OrgName, const QString& taskName , const QString& description );
    void deleteTask(const QString& OrgName, const QString& taskName);
    void archiveTask(const QString& taskName);
    bool isTaskArchived(const QString& taskName);
    void unarchiveTask(const QString& taskName);
    void assignTaskToMember(const QString& taskName, const QString& memberUsernames) ;
    void assignTaskToTeam(const QString& taskName, const QString& teamName);
    void assignTaskToProject(const QString& taskName, const QString& teamName);
    static void setDueDate(const QString& taskName, const QString& dueDate);
    void addCommentToTask(const QString& taskName, const QString& commentText) ;
    void deleteCommentFromTask(const QString& taskName, const QString& username, const QString& commentText);
    QVector<QString> taskNamesSorted(const QJsonObject& taskJsonObject);
    QVector<QString> sorttasksByTime(const QJsonObject& taskJsonObject);


private:
    static QString TaskName;

};

#endif // TASK_MANAGER_H
