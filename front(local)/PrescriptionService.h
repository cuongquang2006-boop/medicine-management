#ifndef PRESCRIPTIONSERVICE_H
#define PRESCRIPTIONSERVICE_H

#include "PrescriptionModel.h"

#include <QObject>
#include <QVector>

class QNetworkAccessManager;
class QNetworkReply;

class PrescriptionService : public QObject
{
    Q_OBJECT

public:

    explicit PrescriptionService(
        QObject *parent = nullptr
        );

    void fetchPrescriptions();

    void createPrescription(
        const PrescriptionModel& prescription
        );

signals:

    void prescriptionsLoaded(
        QVector<PrescriptionModel> prescriptions
        );

    void errorOccurred(
        QString message
        );

private slots:

    void handlePrescriptionResponse(
        QNetworkReply* reply
        );

private:

    QNetworkAccessManager* manager;
};

#endif