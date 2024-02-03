#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>
#include <QJsonObject>

class UserManager {
public:
    static void setLoggedInUser(const QString &username, const QJsonObject &userData);
    static QString getLoggedInUsername();
    static QJsonObject getLoggedInUserData();
    static void logout();
    void resetPassword(const QJsonObject &userData, const QString &newPassword);

    bool authenticateAndResetPassword(const QString& enteredUsername, const QString& enteredName,
                                                  const QString& enteredEmail, const int& enteredAge,
                                                  const QString& newPassword);


private:
    static QString loggedInUsername;
    static QJsonObject loggedInUserData;
};

#endif // USERMANAGER_H
