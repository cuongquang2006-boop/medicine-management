#include "UserService.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QUrl>


UserService::UserService(QObject *parent)
    : QObject(parent)
{
    manager =
        new QNetworkAccessManager(this);

    connect(manager,
            &QNetworkAccessManager::finished,
            this,
            &UserService::handleUserResponse);
}


void UserService::fetchUsers()
{
    QUrl url(
        "http://127.0.0.1:3000/api/users"
        );

    QNetworkRequest request(url);

    manager->get(request);
}


void UserService::createUser(
    const User& user
    )
{
    QUrl url(
        "http://127.0.0.1:3000/api/users"
        );

    QNetworkRequest request(url);

    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json"
        );

    QJsonObject json;

    json["username"] =
        user.username;

    json["full_name"] =
        user.fullName;

    json["password"] =
        user.password;

    json["role"] =
        user.role;

    QJsonDocument doc(json);

    manager->post(
        request,
        doc.toJson()
        );
}


void UserService::updateUser(
    const User& user
    )
{
    QUrl url(
        "http://127.0.0.1:3000/api/users/"
        + QString::number(user.id)
        );

    QNetworkRequest request(url);

    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json"
        );

    QJsonObject json;

    json["username"] =
        user.username;

    json["full_name"] =
        user.fullName;

    json["password"] =
        user.password;

    json["role"] =
        user.role;

    QJsonDocument doc(json);

    manager->put(
        request,
        doc.toJson()
        );
}


void UserService::deleteUser(
    int userId
    )
{
    QUrl url(
        "http://127.0.0.1:3000/api/users/"
        + QString::number(userId)
        );

    QNetworkRequest request(url);

    manager->deleteResource(request);
}

void UserService::handleUserResponse(
    QNetworkReply *reply
    )
{
    if(reply->error()
        != QNetworkReply::NoError)
    {
        emit errorOccurred(
            reply->errorString()
            );

        reply->deleteLater();

        return;
    }

    if(reply->operation()
            == QNetworkAccessManager::PostOperation
        ||
        reply->operation()
            == QNetworkAccessManager::PutOperation
        ||
        reply->operation()
            == QNetworkAccessManager::DeleteOperation)
    {
        fetchUsers();

        reply->deleteLater();

        return;
    }

    QByteArray data =
        reply->readAll();

    QJsonDocument doc =
        QJsonDocument::fromJson(data);

    QJsonObject root =
        doc.object();

    QJsonArray userArray =
        root["data"].toArray();

    QVector<User> users;

    for(const QJsonValue& value
         : userArray)
    {
        QJsonObject obj =
            value.toObject();

        User u;

        u.id =
            obj["id"].toInt();

        u.username =
            obj["username"].toString();

        u.fullName =
            obj["full_name"].toString();

        u.password =
            obj["password"].toString();

        u.role =
            obj["role"].toString();

        u.createdAt =
            obj["created_at"].toString();

        users.append(u);
    }

    emit usersLoaded(users);

    reply->deleteLater();
}