#ifndef DISEASEMODEL_H
#define DISEASEMODEL_H

#include <QString>

struct Disease
{
    int id;

    QString diseaseName;

    QString clinicName;

    QString symptoms;

    QString description;

    QString createdAt;
};

#endif