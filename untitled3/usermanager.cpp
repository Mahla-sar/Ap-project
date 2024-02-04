#include "usermanager.h"
#include <QString>
#include <QJsonObject>
#include <QMessageBox>
#include "usermanager.h"
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QDebug>
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


bool UserManager::authenticateAndResetPassword(const QString& enteredUsername, const QString& enteredName,
                                               const QString& enteredEmail, const int& enteredAge,
                                               const QString& newPassword) {
    // Check if the user is logged in
    if (loggedInUsername.isEmpty()) {
        qDebug() << "No user is currently logged in.";
        return false;
    }

    // Get the user data from the logged-in user
    QJsonObject loggedInUserData = getLoggedInUserData();

    // Verify entered information with stored information
    QString storedUsername = loggedInUserData["username"].toString();
    QString storedName = loggedInUserData["name"].toString();
    QString storedEmail = loggedInUserData["email"].toString();
    int storedAge = loggedInUserData["age"].toInt();

    if (enteredUsername == storedUsername && enteredName == storedName &&
        enteredEmail == storedEmail && enteredAge == storedAge) {
        // Authentication successful, call the resetPassword function
        resetPassword(loggedInUserData, newPassword);
        QMessageBox::information(nullptr, "Password Reset", "Password reset successful.");
        return true;
    } else {
        // Authentication failed
        QMessageBox::warning(nullptr, "Authentication Failed", "Entered information does not match the stored data.");
        return false;
    }
}


void UserManager::resetPassword(const QJsonObject &userData, const QString &newPassword) {
    // Extract user information from the JSON object
    QString storedUsername = userData["username"].toString();
    QString storedPasswordHash = userData["password"].toString();

    // Verify the stored password hash with the entered current password
    // For additional security, you may also want to include other user information in the verification process
    // For example: compare stored email, age, etc.
    if (storedPasswordHash == QString(QCryptographicHash::hash(newPassword.toUtf8(), QCryptographicHash::Sha256).toHex())) {
        qDebug() << "New password should be different from the current password.";
        return;
    }

    // Set the new password hash for the user
    QJsonObject updatedUserData = userData;
    updatedUserData["password"] = QString(QCryptographicHash::hash(newPassword.toUtf8(), QCryptographicHash::Sha256).toHex());

    // Update the user data
    setLoggedInUser(storedUsername, updatedUserData);

    qDebug() << "Password reset successful.";
}
