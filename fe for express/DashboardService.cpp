#include "DashboardService.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QUrl>


DashboardService::DashboardService(
    QObject *parent
    )
    : QObject(parent)
{
    manager =
        new QNetworkAccessManager(this);

    connect(manager,
            &QNetworkAccessManager::finished,
            this,
            &DashboardService::handleReply);
}


void DashboardService::fetchStats()
{
    QUrl url(
        "http://127.0.0.1:3000/api/dashboard/stats"
        );

    QNetworkRequest request(url);

    manager->get(request);
}


void DashboardService::handleReply(
    QNetworkReply *reply
    )
{
    QString path =
        reply->url().path();


    if(reply->error()
        != QNetworkReply::NoError)
    {
        emit errorOccurred(
            reply->errorString()
            );

        reply->deleteLater();

        return;
    }

    QByteArray data =
        reply->readAll();

    QJsonDocument doc =
        QJsonDocument::fromJson(data);

    QJsonObject root =
        doc.object();


    if(path.contains("stats"))
    {
        QJsonObject json =
            root["data"].toObject();

        DashboardStats stats;

        stats.patients =
            json["patients"]
                .toString()
                .toInt();

        stats.medicines =
            json["medicines"]
                .toString()
                .toInt();

        stats.clinics =
            json["clinics"]
                .toString()
                .toInt();

        stats.prescriptions =
            json["prescriptions"]
                .toString()
                .toInt();

        emit statsLoaded(stats);
    }
    else if(path.contains("recent-prescriptions"))
    {
        QVector<RecentPrescription> list;

        QJsonArray arr =
            root["data"].toArray();

        for(const QJsonValue& val : arr)
        {
            QJsonObject obj =
                val.toObject();

            RecentPrescription p;

            p.patient =
                obj["patient"].toString();

            p.disease =
                obj["disease"].toString();

            p.medicines =
                obj["medicines"]
                    .toString()
                    .toInt();

            p.createdAt =
                obj["created_at"]
                    .toString();

            list.append(p);
        }

        emit recentPrescriptionsLoaded(list);
    }

    else if(path.contains("low-stock"))
    {
        QVector<LowStockMedicine> list;

        QJsonArray arr =
            root["data"].toArray();

        for(const QJsonValue& val : arr)
        {
            QJsonObject obj =
                val.toObject();

            LowStockMedicine m;

            m.name =
                obj["name"].toString();

            m.stock =
                obj["stock"].toInt();

            if(m.stock <= 2)
            {
                m.status =
                    "CRITICAL";
            }
            else
            {
                m.status =
                    "LOW";
            }

            list.append(m);
        }

        emit lowStockLoaded(list);
    }

    reply->deleteLater();
}


void DashboardService::fetchRecentPrescriptions()
{
    QUrl url(
        "http://127.0.0.1:3000/api/dashboard/recent-prescriptions"
        );

    QNetworkRequest request(url);

    manager->get(request);
}


void DashboardService::fetchLowStockMedicines()
{
    QUrl url(
        "http://127.0.0.1:3000/api/dashboard/low-stock"
        );

    QNetworkRequest request(url);

    manager->get(request);
}