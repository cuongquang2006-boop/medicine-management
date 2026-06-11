#include "ClinicService.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QUrl>


ClinicService::ClinicService(QObject *parent)
    : QObject(parent)
{
    manager =
        new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &ClinicService::handleClinicResponse);
}

void ClinicService::fetchClinics()
{
    QUrl url("http://127.0.0.1:3000/api/clinics");

    QNetworkRequest request(url);

    manager->get(request);
}


void ClinicService::handleClinicResponse(QNetworkReply *reply)
{

    if(reply->error() != QNetworkReply::NoError)
    {
        emit errorOccurred(
            reply->errorString()
            );

        reply->deleteLater();

        return;
    }

    if(reply->operation()
            == QNetworkAccessManager::PostOperation
        ||
        reply->operation()
            == QNetworkAccessManager::PutOperation
        ||
        reply->operation()
            == QNetworkAccessManager::DeleteOperation)
    {
        fetchClinics();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonObject root = doc.object();

    QJsonArray clinicArray = root["data"].toArray();

    QVector<Clinic> clinics;

    for(const QJsonValue& value : clinicArray)
    {
        QJsonObject obj =
            value.toObject();

        Clinic c;

        c.id = obj["id"].toInt();

        c.name = obj["name"].toString();

        c.location = obj["location"].toString();

        c.description = obj["description"].toString();

        c.createdAt = obj["created_at"].toString();

        clinics.append(c);
    }

    emit clinicsLoaded(clinics);
    reply->deleteLater();
}


void ClinicService::createClinic(const Clinic& clinic)
{
    QUrl url("http://127.0.0.1:3000/api/clinics");

    QNetworkRequest request(url);

    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;

    json["name"] = clinic.name;

    json["location"] = clinic.location;

    json["description"] = clinic.description;

    QJsonDocument doc(json);


    manager->post(request, doc.toJson());
}

void ClinicService::updateClinic(const Clinic& clinic)
{
    QUrl url(
        "http://127.0.0.1:3000/api/clinics/"
        + QString::number(clinic.id)
        );

    QNetworkRequest request(url);

    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json"
        );

    QJsonObject json;

    json["name"] =
        clinic.name;

    json["location"] =
        clinic.location;

    json["description"] =
        clinic.description;

    QJsonDocument doc(json);

    manager->put(
        request,
        doc.toJson()
        );
}

void ClinicService::deleteClinic(int clinicId)
{
    QUrl url("http://127.0.0.1:3000/api/clinics/" + QString::number(clinicId));

    QNetworkRequest request(url);

    manager->deleteResource(request);
}