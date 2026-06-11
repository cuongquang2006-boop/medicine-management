#ifndef PATIENTSERVICE_H
#define PATIENTSERVICE_H

#include "PatientModel.h"

#include <QObject>
#include <QVector>

class QNetworkAccessManager;
class QNetworkReply;

class PatientService : public QObject
{
    Q_OBJECT
public:
    explicit PatientService(QObject *parent = nullptr);

    void fetchPatients();

    void createPatient(const Patient& patient);

    void updatePatient(const Patient& patient);

    void deletePatient(int patientId);

signals:

    void patientsLoaded(QVector<Patient> patients);

    void errorOccurred(QString message);

private slots:

    void handlePatientsResponse(QNetworkReply* reply);

private:

    QNetworkAccessManager* manager;
};

#endif