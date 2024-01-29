#include "usermanager.h"
#include <QString>
#include <QJsonObject>
QString UserManager::loggedInUsername;
QJsonObject UserManager::loggedInUserData;

void UserManager::setLoggedInUser(const QString &username, const QJsonObject &userData) {
    loggedInUsername = username;
    loggedInUserData = userData;
}

QString UserManager::getLoggedInUsername() {
    return loggedInUsername;
}

QJsonObject UserManager::getLoggedInUserData() {
    return loggedInUserData;
}

void UserManager::logout() {
    loggedInUsername.clear();
    loggedInUserData = QJsonObject();
}
