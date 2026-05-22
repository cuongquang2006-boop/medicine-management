#include "AuthService.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonDocument>
#include <QJsonObject>

#include <QUrl>


AuthService::AuthService(QObject *parent)
    : QObject(parent)
{
    manager =
        new QNetworkAccessManager(this);

    connect(manager,
            &QNetworkAccessManager::finished,
            this,
            &AuthService::handleLoginResponse);
}


void AuthService::login(
    const QString& username,
    const QString& password
    )
{
    QUrl url(
        "http://127.0.0.1:3000/api/users/login"
        );

    QNetworkRequest request(url);

    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json"
        );

    QJsonObject json;

    json["username"] =
        username;

    json["password"] =
        password;

    QJsonDocument doc(json);

    manager->post(
        request,
        doc.toJson()
        );
}


void AuthService::handleLoginResponse(QNetworkReply *reply)
{

    if(reply->error()
        != QNetworkReply::NoError)
    {
        emit loginFailed(
            reply->errorString()
            );

        reply->deleteLater();

        return;
    }

    QByteArray data =
        reply->readAll();

    QJsonDocument doc =
        QJsonDocument::fromJson(data);

    QJsonObject obj =
        doc.object();

    bool success =
        obj["success"].toBool();

    if(success)
    {
        emit loginSuccess();
    }
    else
    {
        QString message =
            obj["message"].toString();

        if(obj.contains("remaining_seconds"))
        {
            int seconds =
                obj["remaining_seconds"]
                    .toInt();

            int minutes =
                seconds / 60;

            int remain =
                seconds % 60;

            message +=
                QString(
                    " (%1m %2s remaining)"
                    )
                    .arg(minutes)
                    .arg(remain);
        }

        emit loginFailed(message);
    }

    reply->deleteLater();
}