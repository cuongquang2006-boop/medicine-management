#ifndef PATIENTMODEL_H
#define PATIENTMODEL_H

#include <QString>

struct Patient
{
    int id;

    QString fullName;

    int age;

    QString gender;

    QString phone;

    QString address;

    int clinicId;


    QString createdAt;
};

#endif