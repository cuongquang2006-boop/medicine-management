#ifndef DASHBOARDSERVICE_H
#define DASHBOARDSERVICE_H

#include <QObject>
#include <QVector>

class QNetworkAccessManager;
class QNetworkReply;


struct DashboardStats
{
    int patients;

    int medicines;

    int clinics;

    int prescriptions;
};

struct RecentPrescription
{
    QString patient;

    QString disease;

    int medicines;

    QString createdAt;
};


struct LowStockMedicine
{
    QString name;

    int stock;

    QString status;
};

class DashboardService : public QObject
{
    Q_OBJECT

public:

    explicit DashboardService(
        QObject *parent = nullptr
        );

    void fetchStats();

signals:

    void statsLoaded(
        DashboardStats stats
        );

    void errorOccurred(
        QString message
        );

    void recentPrescriptionsLoaded(
        QVector<RecentPrescription> data
        );

    void lowStockLoaded(
        QVector<LowStockMedicine> data
        );

private slots:

    void handleReply(
        QNetworkReply* reply
        );

private:

    QNetworkAccessManager* manager;

public:
    void fetchRecentPrescriptions();

    void fetchLowStockMedicines();
};

#endif