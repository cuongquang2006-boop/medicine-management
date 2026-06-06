#include "DashboardWidget.h"

#include <QDebug>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLabel>
#include <QFrame>

#include <QTableWidget>
#include <QHeaderView>

#include <QGraphicsDropShadowEffect>



DashboardWidget::DashboardWidget(QWidget *parent) : QWidget(parent)
{
    setupUI();

    setupBanner();

    setupCards();

    setupTables();

    setupStyles();

    dashboardService =
        new DashboardService(this);

    connect(dashboardService,
            &DashboardService::statsLoaded,
            this,
            &DashboardWidget::handleStatsLoaded);

    connect(dashboardService,
            &DashboardService::errorOccurred,
            this,
            &DashboardWidget::handleApiError);

    connect(dashboardService,
            &DashboardService::recentPrescriptionsLoaded,
            this,
            &DashboardWidget::handleRecentLoaded);

    connect(dashboardService,
            &DashboardService::lowStockLoaded,
            this,
            &DashboardWidget::handleLowStockLoaded);

    dashboardService->fetchStats();

    dashboardService->fetchRecentPrescriptions();

    dashboardService->fetchLowStockMedicines();
}



void DashboardWidget::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    mainLayout->setContentsMargins(25,25,25,25);

    mainLayout->setSpacing(20);


    bannerWidget = new QFrame;

    mainLayout->addWidget(bannerWidget);


    QHBoxLayout* cardLayout = new QHBoxLayout;

    cardLayout->setSpacing(18);

    patientCard = createStatCard(
        "Patients",
        "128",
        patientCountLabel
        );

    medicineCard = createStatCard(
        "Medicines",
        "54",
        medicineCountLabel
        );

    clinicCard = createStatCard(
        "Clinics",
        "12",
        clinicCountLabel
        );

    prescriptionCard = createStatCard(
        "Prescriptions",
        "302",
        prescriptionCountLabel
        );

    cardLayout->addWidget(patientCard);
    cardLayout->addWidget(medicineCard);
    cardLayout->addWidget(clinicCard);
    cardLayout->addWidget(prescriptionCard);

    mainLayout->addLayout(cardLayout);



    QLabel* recentLabel =
        new QLabel("Recent Prescriptions");

    recentLabel->setStyleSheet(R"(
        font-size:20px;
        font-weight:bold;
        color:#1f2937;
    )");

    mainLayout->addWidget(recentLabel);

    recentPrescriptionTable = new QTableWidget;

    mainLayout->addWidget(
        recentPrescriptionTable
        );


    QLabel* lowStockLabel =
        new QLabel("Low Stock Medicines");

    lowStockLabel->setStyleSheet(R"(
        font-size:20px;
        font-weight:bold;
        color:#1f2937;
    )");

    mainLayout->addWidget(lowStockLabel);

    lowStockTable = new QTableWidget;

    mainLayout->addWidget(lowStockTable);
}



void DashboardWidget::setupBanner()
{
    QVBoxLayout* layout =
        new QVBoxLayout(bannerWidget);

    QLabel* welcomeLabel =
        new QLabel("Welcome back, Doctor");

    QLabel* descLabel =
        new QLabel("Medicine Management System");

    welcomeLabel->setStyleSheet(R"(
        font-size:28px;
        font-weight:bold;
        color:white;
    )");

    descLabel->setStyleSheet(R"(
        font-size:16px;
        color:rgba(255,255,255,0.85);
    )");

    layout->addWidget(welcomeLabel);
    layout->addWidget(descLabel);

    bannerWidget->setMinimumHeight(120);

    bannerWidget->setStyleSheet(R"(

        QFrame{

            border-radius:18px;

            background:qlineargradient(
                x1:0, y1:0,
                x2:1, y2:1,

                stop:0 #2563eb,
                stop:1 #1d4ed8
            );
        }

    )");
}


void DashboardWidget::setupCards()
{
    QList<QFrame*> cards =
        {
            patientCard,
            medicineCard,
            clinicCard,
            prescriptionCard
        };

    for(QFrame* card : cards)
    {
        QGraphicsDropShadowEffect* shadow =
            new QGraphicsDropShadowEffect;

        shadow->setBlurRadius(18);

        shadow->setOffset(0,4);

        shadow->setColor(
            QColor(0,0,0,40)
            );

        card->setGraphicsEffect(shadow);
    }
}



void DashboardWidget::setupTables()
{
    recentPrescriptionTable->setColumnCount(4);

    recentPrescriptionTable->setHorizontalHeaderLabels(
        {
            "Patient",
            "Disease",
            "Medicines",
            "Created At"
        });

    recentPrescriptionTable->horizontalHeader()
        ->setSectionResizeMode(
            QHeaderView::Stretch
            );

    recentPrescriptionTable->setRowCount(3);

    recentPrescriptionTable->setItem(
        0,0,
        new QTableWidgetItem("Nguyen Van A")
        );

    recentPrescriptionTable->setItem(
        0,1,
        new QTableWidgetItem("Flu")
        );

    recentPrescriptionTable->setItem(
        0,2,
        new QTableWidgetItem("3")
        );

    recentPrescriptionTable->setItem(
        0,3,
        new QTableWidgetItem("2026-05-08")
        );


    lowStockTable->setColumnCount(3);

    lowStockTable->setHorizontalHeaderLabels(
        {
            "Medicine",
            "Stock",
            "Status"
        });

    lowStockTable->horizontalHeader()
        ->setSectionResizeMode(
            QHeaderView::Stretch
            );

    lowStockTable->setRowCount(2);

    lowStockTable->setItem(
        0,0,
        new QTableWidgetItem("Paracetamol")
        );

    lowStockTable->setItem(
        0,1,
        new QTableWidgetItem("5")
        );

    lowStockTable->setItem(
        0,2,
        new QTableWidgetItem("LOW")
        );
}


void DashboardWidget::setupStyles()
{
    setStyleSheet(R"(

        QWidget{

            background:#f4f6f9;
        }

        QTableWidget{

            background:white;

            color:#111827;

            border:3px solid #2563eb;

            border-radius:3px;

            gridline-color:#e5e7eb;

            font-size:14px;

            alternate-background-color:#f9fafb;
        }

        QHeaderView::section{

            background:#f3f4f6;

            padding:12px;

            border:none;

            font-weight:bold;

            color:#374151;
        }

        QTableWidget::item{

            padding:10px;
        }

    )");

    recentPrescriptionTable
        ->setAlternatingRowColors(true);

    lowStockTable
        ->setAlternatingRowColors(true);

    recentPrescriptionTable
        ->setEditTriggers(
            QAbstractItemView::NoEditTriggers
            );

    lowStockTable
        ->setEditTriggers(
            QAbstractItemView::NoEditTriggers
            );

    recentPrescriptionTable
        ->setSelectionBehavior(
            QAbstractItemView::SelectRows
            );

    lowStockTable
        ->setSelectionBehavior(
            QAbstractItemView::SelectRows
            );

    recentPrescriptionTable
        ->verticalHeader()
        ->setVisible(false);

    lowStockTable
        ->verticalHeader()
        ->setVisible(false);
}



QFrame* DashboardWidget::createStatCard(
    const QString& title,
    const QString& value,
    QLabel*& valueLabel
    )
{
    QFrame* card = new QFrame;

    card->setMinimumHeight(120);

    card->setStyleSheet(R"(

        QFrame{

            background:white;

            border-radius:18px;
        }

    )");

    QVBoxLayout* layout =
        new QVBoxLayout(card);

    QLabel* titleLabel =
        new QLabel(title);

    valueLabel =
        new QLabel(value);

    titleLabel->setStyleSheet(R"(
        font-size:15px;
        color:#6b7280;
    )");

    valueLabel->setStyleSheet(R"(
        font-size:32px;
        font-weight:bold;
        color:#111827;
    )");

    layout->addWidget(titleLabel);

    layout->addStretch();

    layout->addWidget(valueLabel);

    return card;
}

void DashboardWidget::handleStatsLoaded(
    DashboardStats stats
    )
{
    patientCountLabel->setText(
        QString::number(
            stats.patients
            )
        );

    medicineCountLabel->setText(
        QString::number(
            stats.medicines
            )
        );

    clinicCountLabel->setText(
        QString::number(
            stats.clinics
            )
        );

    prescriptionCountLabel->setText(
        QString::number(
            stats.prescriptions
            )
        );
}


void DashboardWidget::handleApiError(
    QString message
    )
{
    qDebug() << message;
}

void DashboardWidget::handleRecentLoaded(
    QVector<RecentPrescription> data
    )
{
    recentPrescriptionTable->setRowCount(0);

    for(int i = 0;
         i < data.size();
         ++i)
    {
        const RecentPrescription& p =
            data[i];

        recentPrescriptionTable->insertRow(i);

        recentPrescriptionTable->setItem(
            i,0,
            new QTableWidgetItem(
                p.patient
                )
            );

        recentPrescriptionTable->setItem(
            i,1,
            new QTableWidgetItem(
                p.disease
                )
            );

        recentPrescriptionTable->setItem(
            i,2,
            new QTableWidgetItem(
                QString::number(
                    p.medicines
                    )
                )
            );

        recentPrescriptionTable->setItem(
            i,3,
            new QTableWidgetItem(
                p.createdAt
                )
            );
    }
}


void DashboardWidget::handleLowStockLoaded(
    QVector<LowStockMedicine> data
    )
{
    lowStockTable->setRowCount(0);

    for(int i = 0;
         i < data.size();
         ++i)
    {
        const LowStockMedicine& m =
            data[i];

        lowStockTable->insertRow(i);

        lowStockTable->setItem(
            i,0,
            new QTableWidgetItem(
                m.name
                )
            );

        lowStockTable->setItem(
            i,1,
            new QTableWidgetItem(
                QString::number(
                    m.stock
                    )
                )
            );

        lowStockTable->setItem(
            i,2,
            new QTableWidgetItem(
                m.status
                )
            );
    }
}