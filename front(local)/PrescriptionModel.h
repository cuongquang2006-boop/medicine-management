#ifndef PRESCRIPTIONMODEL_H
#define PRESCRIPTIONMODEL_H

#include <QString>

struct PrescriptionModel
{
    int id;

    int patientId;

    int diseaseId;

    int createdBy;

    QString patientName;

    QString diseaseName;

    QString doctorName;

    QString diagnosis;

    QString createdAt;
};

#endif