#include "PrescriptionService.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QUrl>


PrescriptionService::PrescriptionService(
    QObject *parent
    )
    : QObject(parent)
{
    manager =
        new QNetworkAccessManager(this);

    connect(manager,
            &QNetworkAccessManager::finished,
            this,
            &PrescriptionService::handlePrescriptionResponse);
}


void PrescriptionService::fetchPrescriptions()
{
    QUrl url(
        "http://127.0.0.1:3000/api/prescriptions"
        );

    QNetworkRequest request(url);

    manager->get(request);
}


void PrescriptionService::createPrescription(
    const PrescriptionModel& prescription
    )
{
    QUrl url(
        "http://127.0.0.1:3000/api/prescriptions"
        );

    QNetworkRequest request(url);

    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json"
        );

    QJsonObject json;

    json["patient_id"] =
        prescription.patientId;

    json["disease_id"] =
        prescription.diseaseId;

    json["created_by"] =
        prescription.createdBy;

    json["diagnosis"] =
        prescription.diagnosis;

    QJsonDocument doc(json);

    manager->post(
        request,
        doc.toJson()
        );
}

void PrescriptionService::handlePrescriptionResponse(
    QNetworkReply *reply
    )
{
    if(reply->error()
        != QNetworkReply::NoError)
    {
        emit errorOccurred(
            reply->errorString()
            );

        reply->deleteLater();

        return;
    }

    if(reply->operation()
        == QNetworkAccessManager::PostOperation)
    {
        fetchPrescriptions();

        reply->deleteLater();

        return;
    }

    QByteArray data =
        reply->readAll();

    QJsonDocument doc =
        QJsonDocument::fromJson(data);

    QJsonObject root =
        doc.object();

    QJsonArray prescriptionArray =
        root["data"].toArray();

    QVector<PrescriptionModel> prescriptions;

    for(const QJsonValue& value
         : prescriptionArray)
    {
        QJsonObject obj =
            value.toObject();

        PrescriptionModel p;

        p.id =
            obj["id"].toInt();

        p.patientId =
            obj["patient_id"].toInt();

        p.diseaseId =
            obj["disease_id"].toInt();

        p.createdBy =
            obj["created_by"].toInt();

        p.patientName =
            obj["patient_name"].toString();

        p.diseaseName =
            obj["disease_name"].toString();

        p.doctorName =
            obj["doctor_name"].toString();

        p.diagnosis =
            obj["diagnosis"].toString();

        p.createdAt =
            obj["created_at"].toString();

        prescriptions.append(p);

    }

    emit prescriptionsLoaded(
        prescriptions
        );

    reply->deleteLater();
}