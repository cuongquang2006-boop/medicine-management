#ifndef CLINICMODEL_H
#define CLINICMODEL_H

#include <QString>

struct Clinic
{
    int id;

    QString name;

    QString location;

    QString description;

    QString createdAt;
};

#endif