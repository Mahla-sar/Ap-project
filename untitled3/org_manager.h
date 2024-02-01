#ifndef ORG_MANAGER_H
#define ORG_MANAGER_H
#include <QDialog>

//namespace Ui {
//class org_manager;
//}
class org_manager : public QDialog
{
    Q_OBJECT

public:
//    explicit org_manager(QWidget *parent = nullptr);
//    ~org_manager();
//    void deleteOrganization(const QString& orgName);
    static QString get_organization();
    void creat_organization(const QString& name);
    void deleteOrganization(const QString& orgName);
    void addMemberToOrganization(const QString& orgName, const QString& memberName);
    void removeMemberFromOrganization(const QString& orgName, const QString& memberName);
    void promoteMemberToAdminInOrganization(const QString& orgName, const QString& memberName);
    void demoteAdminToMember(const QString& orgName, const QString& adminName);
    void editOrganizationName(const QString& oldName, const QString& newName);


private :
    static QString OrganizationName;

//private:
//    //ui::org_manager *ui;
//    // Add any necessary private members for managing the organization
//    // ...

//    // Declare functions for managing the organization
//    void editOrganization(const QString& orgName, const QJsonObject& newOrgData);
};

#endif // ORG_MANAGER_H
