#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "UserModel.h"

#include <QObject>
#include <QVector>

class QNetworkAccessManager;
class QNetworkReply;

class UserService : public QObject
{
    Q_OBJECT

public:

    explicit UserService(
        QObject *parent = nullptr
        );

    void fetchUsers();

    void createUser(
        const User& user
        );

    void updateUser(
        const User& user
        );

    void deleteUser(
        int userId
        );

signals:

    void usersLoaded(
        QVector<User> users
        );

    void errorOccurred(
        QString message
        );

private slots:

    void handleUserResponse(
        QNetworkReply* reply
        );

private:

    QNetworkAccessManager* manager;
};

#endif