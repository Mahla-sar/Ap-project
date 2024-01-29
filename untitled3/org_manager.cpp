#include "org_manager.h"


void OrganizationManager::editOrganization(const QString &name, const QJsonObject &newData) {
    QJsonArray organizations = getOrganizations();
    for (int i = 0; i < organizations.size(); ++i) {
        QJsonObject org = organizations[i].toObject();
        if (org["name"].toString() == name) {
            org = newData;  // شما ممکن است اطلاعات دیگر را هم ویرایش کنید
            organizations[i] = org;
            saveOrganizations(organizations);
            return;
        }
    }
}

void OrganizationManager::deleteOrganization(const QString &name) {
    QJsonArray organizations = getOrganizations();
    for (int i = 0; i < organizations.size(); ++i) {
        QJsonObject org = organizations[i].toObject();
        if (org["name"].toString() == name) {
            organizations.removeAt(i);
            saveOrganizations(organizations);
            return;
        }
    }
}

void OrganizationManager::addPersonToOrganization(const QString &organizationName, const QString &personName) {
    QJsonArray organizations = getOrganizations();
    for (int i = 0; i < organizations.size(); ++i) {
        QJsonObject org = organizations[i].toObject();
        if (org["name"].toString() == organizationName) {
            QJsonArray members = org["members"].toArray();
            members.append(personName);
            org["members"] = members;
            organizations[i] = org;
            saveOrganizations(organizations);
            return;
        }
    }
}

void OrganizationManager::removePersonFromOrganization(const QString &organizationName, const QString &personName) {
    QJsonArray organizations = getOrganizations();
    for (int i = 0; i < organizations.size(); ++i) {
        QJsonObject org = organizations[i].toObject();
        if (org["name"].toString() == organizationName) {
            QJsonArray members = org["members"].toArray();
            //members.erase(personName);
            int i ;
            for(i = 0 ; i < members.size() ; i++){
                if(members[i] == personName )
                {
                    break;
                }
            }
            members.removeAt(i);
            org["members"] = members;
            organizations[i] = org;
            saveOrganizations(organizations);
            return;
        }
    }
}

QJsonObject OrganizationManager::findOrganization(const QString &name) {
    QJsonArray organizations = getOrganizations();
    for (int i = 0; i < organizations.size(); ++i) {
        QJsonObject org = organizations[i].toObject();
        if (org["name"].toString() == name) {
            return org;
        }
    }
    return QJsonObject();
}

QJsonArray OrganizationManager::getOrganizations() {
    // مثال: خواندن اطلاعات از فایل یا منبع دیگر
    // در اینجا یک مثال ساده از یک آرایه خالی آورده شده است
    return QJsonArray();
}
