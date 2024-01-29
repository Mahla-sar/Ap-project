// OrganizationManager.h

#ifndef ORGANIZATIONMANAGER_H
#define ORGANIZATIONMANAGER_H

#include <QString>
#include <QJsonArray>
#include <QJsonObject>

class OrganizationManager {
public:
    // توابع اضافه شده
    void createOrganization(const QString &name);
    void editOrganization(const QString &name, const QJsonObject &newData);
    void deleteOrganization(const QString &name);
    void addPersonToOrganization(const QString &organizationName, const QString &personName);
    void removePersonFromOrganization(const QString &organizationName, const QString &personName);

private:
    // توابع داخلی
    QJsonObject findOrganization(const QString &name);
    QJsonArray getOrganizations();
    void saveOrganizations(const QJsonArray &organizations);
};

#endif // ORGANIZATIONMANAGER_H
