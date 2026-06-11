#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class AuthService : public QObject
{
    Q_OBJECT

public:

    explicit AuthService(
        QObject *parent = nullptr
        );

    void login(
        const QString& username,
        const QString& password
        );

signals:

    void loginSuccess();

    void loginFailed(
        QString message
        );

private slots:

    void handleLoginResponse(
        QNetworkReply* reply
        );

private:

    QNetworkAccessManager* manager;
};

#endif