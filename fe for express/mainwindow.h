#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DashboardWidget.h"
#include "PatientWidget.h"
#include "MedicineWidget.h"
#include "PrescriptionWidget.h"
#include "ClinicWidget.h"
#include "DiseaseWidget.h"
#include "UserWidget.h"

#include "LoginWindow.h"

#include <QMainWindow>
#include <QVector>

class QPushButton;
class QLabel;
class QStackedWidget;

class DashboardWidget;
class PatientWidget;
class ClinicWidget;
class DiseaseWidget;
class MedicineWidget;
class PrescriptionWidget;
class UserWidget;
class LoginWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:

    QWidget* centralWidgetContainer;

    QWidget* sidebarWidget;
    QWidget* topbarWidget;

    QStackedWidget* stack;

    QLabel* titleLabel;
    QLabel* userLabel;


    QPushButton* dashboardBtn;
    QPushButton* patientBtn;
    QPushButton* clinicBtn;
    QPushButton* diseaseBtn;
    QPushButton* medicineBtn;
    QPushButton* prescriptionBtn;
    QPushButton* userBtn;
    QPushButton* logoutBtn;

    QVector<QPushButton*> menuButtons;

    DashboardWidget* dashboardPage;
    PatientWidget* patientPage;
    ClinicWidget* clinicPage;
    DiseaseWidget* diseasePage;
    MedicineWidget* medicinePage;
    PrescriptionWidget* prescriptionPage;
    UserWidget* userPage;

private:

    void setupUI();

    void setupSidebar();

    void setupTopbar();

    void setupPages();

    void setupConnections();

    void setupStyles();


    QPushButton* createSidebarButton(const QString& text);

    void setActiveButton(QPushButton* button);

private slots:

    void openDashboard();

    void openPatients();

    void openClinics();

    void openDiseases();

    void openMedicines();

    void openPrescriptions();

    void openUsers();

    void logout();
};

#endif