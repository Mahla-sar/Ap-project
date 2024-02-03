#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H
#include <QDialog>


class Project_manager
{
public:
//    Project_manager();
    static QString get_project();
    static void setproject(const QString &project_name);
    void createproject(const QString& orgName, const QString& projectName);
    void deleteproject(const QString& orgName, const QString& projectName);
    void renameproject(const QString& orgName, const QString& oldprojectName, const QString& newprojectName);
    void addMemberToproject(const QString& orgName, const QString& projectName, const QString& memberUsername);
    void removeMemberFromproject(const QString& orgName, const QString& projectName, const QString& memberUsername);
    void updateProjectState(const QString& orgName, const QString& projectName, const QString& newState);
    bool is_doneProject(const QString& projectName);
    QVector<QString> projectNamesSorted(const QJsonObject& orgJsonObject);
    QVector<QString> sortprojectsByTime(const QJsonObject& orgJsonObject);
private:
    static QString ProjectName;


};

#endif // PROJECT_MANAGER_H
