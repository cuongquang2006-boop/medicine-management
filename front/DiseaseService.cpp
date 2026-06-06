#include "DiseaseService.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QUrl>


DiseaseService::DiseaseService(QObject *parent)
    : QObject(parent)
{
    manager =
        new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &DiseaseService::handleDiseaseResponse);
}


void DiseaseService::fetchDiseases()
{
    QUrl url(
        "http://127.0.0.1:3000/api/diseases"
        );

    QNetworkRequest request(url);

    manager->get(request);
}


void DiseaseService::handleDiseaseResponse(QNetworkReply *reply)
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
            == QNetworkAccessManager::PostOperation
        ||
        reply->operation()
            == QNetworkAccessManager::PutOperation
        ||
        reply->operation()
            == QNetworkAccessManager::DeleteOperation)
    {
        fetchDiseases();

        reply->deleteLater();

        return;
    }

    QByteArray data =
        reply->readAll();

    QJsonDocument doc =
        QJsonDocument::fromJson(data);

    QJsonObject root =
        doc.object();

    QJsonArray diseaseArray =
        root["data"].toArray();

    QVector<Disease> diseases;

    for(const QJsonValue& value
         : diseaseArray)
    {
        QJsonObject obj =
            value.toObject();

        Disease d;

        d.id =
            obj["id"].toInt();

        d.diseaseName =
            obj["name"].toString();

        d.clinicName =
            obj["clinic_name"].toString();

        d.symptoms =
            obj["symptoms"].toString();

        d.description =
            obj["description"].toString();

        d.createdAt =
            obj["created_at"].toString();

        diseases.append(d);
    }

    emit diseasesLoaded(diseases);

    reply->deleteLater();
}

void DiseaseService::createDisease(
    const Disease& disease
    )
{
    QUrl url(
        "http://127.0.0.1:3000/api/diseases"
        );

    QNetworkRequest request(url);

    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json"
        );

    QJsonObject json;

    json["name"] =
        disease.diseaseName;

    json["clinic_id"] = 1;

    json["symptoms"] =
        disease.symptoms;

    json["description"] =
        disease.description;

    QJsonDocument doc(json);

    manager->post(
        request,
        doc.toJson()
        );
}


void DiseaseService::updateDisease(
    const Disease& disease
    )
{
    QUrl url(
        "http://127.0.0.1:3000/api/diseases/"
        + QString::number(disease.id)
        );

    QNetworkRequest request(url);

    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json"
        );

    QJsonObject json;

    json["name"] =
        disease.diseaseName;

    json["clinic_id"] = 1;

    json["symptoms"] =
        disease.symptoms;

    json["description"] =
        disease.description;

    QJsonDocument doc(json);

    manager->put(
        request,
        doc.toJson()
        );
}


void DiseaseService::deleteDisease(
    int diseaseId
    )
{
    QUrl url(
        "http://127.0.0.1:3000/api/diseases/"
        + QString::number(diseaseId)
        );

    QNetworkRequest request(url);

    manager->deleteResource(request);
}