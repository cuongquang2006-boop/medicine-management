#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include "DashboardService.h"

#include <QWidget>

class QLabel;
class QFrame;
class QTableWidget;

class DashboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardWidget(QWidget *parent = nullptr);

private:

    DashboardService* dashboardService;

    QWidget* bannerWidget;

    QFrame* patientCard;
    QFrame* medicineCard;
    QFrame* clinicCard;
    QFrame* prescriptionCard;

    QLabel* patientCountLabel;
    QLabel* medicineCountLabel;
    QLabel* clinicCountLabel;
    QLabel* prescriptionCountLabel;

    QTableWidget* recentPrescriptionTable;
    QTableWidget* lowStockTable;

private:

    void setupUI();

    void setupBanner();

    void setupCards();

    void setupTables();

    void setupStyles();

    QFrame* createStatCard(
        const QString& title,
        const QString& value,
        QLabel*& valueLabel
        );

    void handleStatsLoaded(DashboardStats stats);

    void handleApiError(QString message);

    void handleRecentLoaded(
        QVector<RecentPrescription> data
        );

    void handleLowStockLoaded(
        QVector<LowStockMedicine> data
        );
};

#endif