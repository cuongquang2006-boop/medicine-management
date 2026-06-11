#include "MedicineService.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QUrl>


MedicineService::MedicineService(QObject *parent)
    : QObject(parent)
{
    manager =
        new QNetworkAccessManager(this);

    connect(manager,
            &QNetworkAccessManager::finished,
            this,
            &MedicineService::handleMedicineResponse);
}


void MedicineService::fetchMedicines()
{
    QUrl url(
        "http://127.0.0.1:3000/api/medicines"
        );

    QNetworkRequest request(url);

    manager->get(request);
}

void MedicineService::handleMedicineResponse(
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
            == QNetworkAccessManager::PostOperation
        ||
        reply->operation()
            == QNetworkAccessManager::PutOperation
        ||
        reply->operation()
            == QNetworkAccessManager::DeleteOperation)
    {
        fetchMedicines();

        reply->deleteLater();

        return;
    }

    QByteArray data =
        reply->readAll();

    QJsonDocument doc =
        QJsonDocument::fromJson(data);

    QJsonObject root =
        doc.object();

    QJsonArray medicineArray =
        root["data"].toArray();

    QVector<Medicine> medicines;

    for(const QJsonValue& value
         : medicineArray)
    {
        QJsonObject obj =
            value.toObject();

        Medicine m;

        m.id =
            obj["id"].toInt();

        m.name =
            obj["name"].toString();

        m.stock =
            obj["stock"].toInt();

        m.price =
            obj["price"].toDouble();

        m.createdAt =
            obj["created_at"].toString();

        medicines.append(m);
    }

    emit medicinesLoaded(medicines);

    reply->deleteLater();
}

void MedicineService::createMedicine(
    const Medicine& medicine
    )
{
    QUrl url(
        "http://127.0.0.1:3000/api/medicines"
        );

    QNetworkRequest request(url);

    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json"
        );

    QJsonObject json;

    json["name"] =
        medicine.name;

    json["stock"] =
        medicine.stock;

    json["price"] =
        medicine.price;

    QJsonDocument doc(json);

    manager->post(
        request,
        doc.toJson()
        );
}


void MedicineService::updateMedicine(
    const Medicine& medicine
    )
{
    QUrl url(
        "http://127.0.0.1:3000/api/medicines/"
        + QString::number(medicine.id)
        );

    QNetworkRequest request(url);

    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json"
        );

    QJsonObject json;

    json["name"] =
        medicine.name;

    json["stock"] =
        medicine.stock;

    json["price"] =
        medicine.price;

    QJsonDocument doc(json);

    manager->put(
        request,
        doc.toJson()
        );
}


void MedicineService::deleteMedicine(
    int medicineId
    )
{
    QUrl url(
        "http://127.0.0.1:3000/api/medicines/"
        + QString::number(medicineId)
        );

    QNetworkRequest request(url);

    manager->deleteResource(request);
}