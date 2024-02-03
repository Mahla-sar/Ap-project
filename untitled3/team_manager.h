#ifndef TEAM_MANAGER_H
#define TEAM_MANAGER_H
#include <QDialog>


class team_manager
{
public:
    //team_manager();
    static QString get_Team();
    void createTeam(const QString& orgName, const QString& teamName);
    void renameTeam(const QString& orgName, const QString& oldTeamName, const QString& newTeamName);
    void deleteTeam(const QString& orgName, const QString& teamName);
    void addMemberToTeam(const QString& orgName, const QString& teamName, const QString& memberUsername);
    void removeMemberFromTeam(const QString& orgName, const QString& teamName, const QString& memberUsername);
    void promoteMemberToHeadInTeam(const QString& orgName, const QString& teamName, const QString& membername);
    void demoteHeadToMemberInTeam(const QString& orgName, const QString& teamName, const QString& memberUsername);
    static void setTeam(const QString &team_name) ;
    QVector<QString> teamNamesSorted(const QJsonObject& teamJsonObject);
    QVector<QString> sortteamsByTime(const QJsonObject& teamJsonObject);

private:
    static QString TeamName;

};

#endif // TEAM_MANAGER_H
