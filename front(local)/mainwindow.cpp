// ===============================
// MainWindow.cpp
// ===============================

#include "MainWindow.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPushButton>
#include <QLabel>

#include <QFrame>
#include <QStackedWidget>

#include <QGraphicsDropShadowEffect>

#include <QPropertyAnimation>

#include <QMessageBox>


// ===============================
// CONSTRUCTOR
// ===============================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();

    setupSidebar();

    setupTopbar();

    setupPages();

    setupConnections();

    setupStyles();

    openDashboard();

    resize(1000, 700);

    setWindowTitle("Medicine Management System");
}


// ===============================
// SETUP UI
// ===============================
void MainWindow::setupUI()
{
    centralWidgetContainer = new QWidget;

    setCentralWidget(centralWidgetContainer);

    QHBoxLayout* rootLayout = new QHBoxLayout(centralWidgetContainer);

    rootLayout->setContentsMargins(0,0,0,0);
    rootLayout->setSpacing(0);

    // ===============================
    // SIDEBAR
    // ===============================
    sidebarWidget = new QFrame;
    sidebarWidget->setFixedWidth(240);

    // ===============================
    // RIGHT AREA
    // ===============================
    QWidget* rightWidget = new QWidget;

    QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);

    rightLayout->setContentsMargins(0,0,0,0);
    rightLayout->setSpacing(0);

    // ===============================
    // TOPBAR
    // ===============================
    topbarWidget = new QFrame;
    topbarWidget->setFixedHeight(70);

    // ===============================
    // STACK
    // ===============================
    stack = new QStackedWidget;

    rightLayout->addWidget(topbarWidget);
    rightLayout->addWidget(stack);

    rootLayout->addWidget(sidebarWidget);
    rootLayout->addWidget(rightWidget);
}


// ===============================
// SIDEBAR
// ===============================
void MainWindow::setupSidebar()
{
    QVBoxLayout* layout = new QVBoxLayout(sidebarWidget);

    layout->setContentsMargins(15,20,15,20);

    QLabel* logo = new QLabel("MEDICINE");

    logo->setAlignment(Qt::AlignCenter);

    logo->setStyleSheet(R"(
        font-size:24px;
        font-weight:bold;
        color:white;
    )");

    layout->addWidget(logo);

    layout->addSpacing(25);

    dashboardBtn   = createSidebarButton("Dashboard");
    patientBtn     = createSidebarButton("Patients");
    clinicBtn      = createSidebarButton("Clinics");
    diseaseBtn     = createSidebarButton("Diseases");
    medicineBtn    = createSidebarButton("Medicines");
    prescriptionBtn= createSidebarButton("Prescriptions");
    userBtn        = createSidebarButton("Users");

    logoutBtn      = createSidebarButton("Logout");

    menuButtons =
        {
            dashboardBtn,
            patientBtn,
            clinicBtn,
            diseaseBtn,
            medicineBtn,
            prescriptionBtn,
            userBtn
        };

    layout->addWidget(dashboardBtn);
    layout->addWidget(patientBtn);
    layout->addWidget(clinicBtn);
    layout->addWidget(diseaseBtn);
    layout->addWidget(medicineBtn);
    layout->addWidget(prescriptionBtn);
    layout->addWidget(userBtn);

    layout->addStretch();

    layout->addWidget(logoutBtn);
}


// ===============================
// TOPBAR
// ===============================
void MainWindow::setupTopbar()
{
    QHBoxLayout* layout = new QHBoxLayout(topbarWidget);

    layout->setContentsMargins(25,10,25,10);

    titleLabel = new QLabel("Dashboard");

    titleLabel->setStyleSheet(R"(
        font-size:24px;
        font-weight:bold;
        color:#1f2937;
    )");

    userLabel = new QLabel("Doctor");

    userLabel->setStyleSheet(R"(
        font-size:15px;
        color:#6b7280;
    )");

    layout->addWidget(titleLabel);

    layout->addStretch();

    layout->addWidget(userLabel);
}


// ===============================
// PAGES
// ===============================
void MainWindow::setupPages()
{
    dashboardPage     = new DashboardWidget;
    patientPage       = new PatientWidget;
    clinicPage        = new ClinicWidget;
    diseasePage       = new DiseaseWidget;
    medicinePage      = new MedicineWidget;
    prescriptionPage  = new PrescriptionWidget;
    userPage          = new UserWidget;

    stack->addWidget(dashboardPage);
    stack->addWidget(patientPage);
    stack->addWidget(clinicPage);
    stack->addWidget(diseasePage);
    stack->addWidget(medicinePage);
    stack->addWidget(prescriptionPage);
    stack->addWidget(userPage);
}


// ===============================
// CONNECTIONS
// ===============================
void MainWindow::setupConnections()
{
    connect(dashboardBtn,&QPushButton::clicked,
            this,&MainWindow::openDashboard);

    connect(patientBtn,&QPushButton::clicked,
            this,&MainWindow::openPatients);

    connect(clinicBtn,&QPushButton::clicked,
            this,&MainWindow::openClinics);

    connect(diseaseBtn,&QPushButton::clicked,
            this,&MainWindow::openDiseases);

    connect(medicineBtn,&QPushButton::clicked,
            this,&MainWindow::openMedicines);

    connect(prescriptionBtn,&QPushButton::clicked,
            this,&MainWindow::openPrescriptions);

    connect(userBtn,&QPushButton::clicked,
            this,&MainWindow::openUsers);

    connect(logoutBtn,&QPushButton::clicked,
            this,&MainWindow::logout);
}


// ===============================
// STYLE
// ===============================
void MainWindow::setupStyles()
{
    setStyleSheet(R"(

        QMainWindow{
            background:#f4f6f9;
        }

        QFrame{
            background:white;
        }

    )");

    sidebarWidget->setStyleSheet(R"(

        background:#1f2937;

    )");

    topbarWidget->setStyleSheet(R"(

        background:white;
        border-bottom:1px solid #e5e7eb;

    )");
}


// ===============================
// CREATE BUTTON
// ===============================
QPushButton* MainWindow::createSidebarButton(const QString& text)
{
    QPushButton* btn = new QPushButton(text);

    btn->setCursor(Qt::PointingHandCursor);

    btn->setMinimumHeight(45);

    btn->setStyleSheet(R"(

        QPushButton{

            text-align:left;

            padding-left:18px;

            border:none;

            border-radius:10px;

            font-size:15px;

            color:white;

            background:transparent;
        }

        QPushButton:hover{

            background:#374151;
        }

    )");

    return btn;
}


// ===============================
// ACTIVE BUTTON
// ===============================
void MainWindow::setActiveButton(QPushButton* button)
{
    for(QPushButton* btn : menuButtons)
    {
        btn->setStyleSheet(R"(

            QPushButton{

                text-align:left;

                padding-left:18px;

                border:none;

                border-radius:10px;

                font-size:15px;

                color:white;

                background:transparent;
            }

            QPushButton:hover{

                background:#374151;
            }

        )");
    }

    button->setStyleSheet(R"(

        QPushButton{

            text-align:left;

            padding-left:18px;

            border:none;

            border-radius:10px;

            font-size:15px;

            color:white;

            background:#2563eb;
        }

    )");
}


// ===============================
// OPEN PAGES
// ===============================
void MainWindow::openDashboard()
{
    stack->setCurrentWidget(dashboardPage);

    titleLabel->setText("Dashboard");

    setActiveButton(dashboardBtn);
}

void MainWindow::openPatients()
{
    stack->setCurrentWidget(patientPage);

    titleLabel->setText("Patients");

    setActiveButton(patientBtn);
}

void MainWindow::openClinics()
{
    stack->setCurrentWidget(clinicPage);

    titleLabel->setText("Clinics");

    setActiveButton(clinicBtn);
}

void MainWindow::openDiseases()
{
    stack->setCurrentWidget(diseasePage);

    titleLabel->setText("Diseases");

    setActiveButton(diseaseBtn);
}

void MainWindow::openMedicines()
{
    stack->setCurrentWidget(medicinePage);

    titleLabel->setText("Medicines");

    setActiveButton(medicineBtn);
}

void MainWindow::openPrescriptions()
{
    stack->setCurrentWidget(prescriptionPage);

    titleLabel->setText("Prescriptions");

    setActiveButton(prescriptionBtn);
}

void MainWindow::openUsers()
{
    stack->setCurrentWidget(userPage);

    titleLabel->setText("Users");

    setActiveButton(userBtn);
}

void MainWindow::logout()
{
    QMessageBox msgBox;

    msgBox.setWindowTitle("Logout");

    msgBox.setText(
        "Are you sure you want to logout?"
        );

    msgBox.setIcon(QMessageBox::Question);

    msgBox.setStandardButtons(
        QMessageBox::Yes | QMessageBox::No
        );

    msgBox.setStyleSheet(R"(

    QMessageBox{

        background:white;
    }

    QLabel{

        color:#111827;

        font-size:14px;
    }

    QPushButton{

        background:#2563eb;

        color:white;

        border:none;

        border-radius:8px;

        padding:8px 18px;

        min-width:80px;
    }

    QPushButton:hover{

        background:#1d4ed8;
    }

    )");

    int reply = msgBox.exec();

    if(reply == QMessageBox::Yes)
    {
        LoginWindow* login =
            new LoginWindow;

        login->show();

        close();
    }
}

