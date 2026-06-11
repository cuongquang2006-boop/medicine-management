#ifndef CLINICSERVICE_H
#define CLINICSERVICE_H

#include <QObject>
#include <QVector>

#include "ClinicModel.h"

class QNetworkAccessManager;
class QNetworkReply;

class ClinicService : public QObject
{
    Q_OBJECT

public:

    explicit ClinicService(QObject *parent = nullptr);

    void fetchClinics();

    void createClinic(const Clinic& clinic);

    void updateClinic(const Clinic& clinic);

    void deleteClinic(int clinicId);

signals:

    void clinicsLoaded(QVector<Clinic> clinics);

    void errorOccurred(QString message);

private slots:

    void handleClinicResponse(QNetworkReply* reply);

private:

    QNetworkAccessManager* manager;
};

#endif