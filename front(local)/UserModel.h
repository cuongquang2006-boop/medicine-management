#ifndef USERMODEL_H
#define USERMODEL_H

#include <QString>

struct User
{
    int id;

    QString username;

    QString fullName;

    QString password;

    QString role;

    QString createdAt;
};

#endif