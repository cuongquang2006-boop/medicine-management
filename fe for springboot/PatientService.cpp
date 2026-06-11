#include "PatientService.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QUrl>

PatientService::PatientService(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &PatientService::handlePatientsResponse);
}

void PatientService::fetchPatients()
{

    QUrl url("http://127.0.0.1:3000/api/patients");

    QNetworkRequest request(url);

    manager->get(request);
    qDebug() << "FETCH PATIENTS CALLED";
}

// load data from backend
void PatientService::handlePatientsResponse(QNetworkReply* reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        qDebug() << reply->readAll();

        emit errorOccurred(reply->errorString());

        return;
    }

    if  (reply->operation() == QNetworkAccessManager::PostOperation
        ||
        reply->operation() == QNetworkAccessManager::PutOperation
        ||
        reply->operation() == QNetworkAccessManager::DeleteOperation)
    {
        fetchPatients();

        reply->deleteLater();

        return;
    }

    QByteArray data = reply->readAll();

    qDebug() << data;
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();
    QJsonArray patientArray = root["data"].toArray();

    QVector<Patient> patients;

    for(const QJsonValue& value : patientArray)
    {
        QJsonObject obj = value.toObject();

        Patient p;

        p.id = obj["id"].toInt();

        p.fullName = obj["full_name"].toString();

        p.age = obj["age"].toInt();

        p.gender = obj["gender"].toString();

        p.phone = obj["phone"].toString();

        p.address = obj["address"].toString();

        p.clinicId = obj["clinic_id"].toInt();

        p.createdAt = obj["created_at"].toString();

        patients.append(p);
    }

    emit patientsLoaded(patients);

    reply->deleteLater();

    qDebug() << "HANDLE RESPONSE CALLED";
}

// create
void PatientService::createPatient(const Patient& patient)
{
    QUrl url("http://127.0.0.1:3000/api/patients");

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QJsonObject json;

    json["full_name"] = patient.fullName;

    json["age"] = patient.age;

    json["gender"] = patient.gender;

    json["phone"] = patient.phone;

    json["address"] = patient.address;

    json["clinic_id"] = patient.clinicId;

    QJsonDocument doc(json);

    manager->post(request,doc.toJson());
}

// update
void PatientService::updatePatient(const Patient& patient)
{
    QUrl url("http://127.0.0.1:3000/api/patients/"+ QString::number(patient.id));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;

    json["full_name"] = patient.fullName;

    json["age"] = patient.age;

    json["gender"] = patient.gender;

    json["phone"] = patient.phone;

    json["address"] = patient.address;

    json["clinic_id"] = patient.clinicId;

    QJsonDocument doc(json);

    manager->put(request,doc.toJson());
}

// delete
void PatientService::deletePatient(int patientId)
{
    QUrl url( "http://127.0.0.1:3000/api/patients/" + QString::number(patientId));

    QNetworkRequest request(url);

    manager->deleteResource(request);
}