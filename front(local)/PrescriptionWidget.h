#ifndef PRESCRIPTIONWIDGET_H
#define PRESCRIPTIONWIDGET_H

#include "MedicineService.h"
#include "MedicineModel.h"
#include "PrescriptionService.h"
#include "PrescriptionModel.h"

#include <QWidget>
#include <QVector>

class QComboBox;
class QLineEdit;
class QPushButton;
class QLabel;
class QTableWidget;

struct PrescriptionMedicine
{
    QString medicineName;

    int quantity;

    QString dosage;

    QString instruction;
};


class PrescriptionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrescriptionWidget(QWidget *parent = nullptr);

private:

    MedicineService* medicineService;

    QVector<Medicine> medicines;

    QLineEdit* searchEdit;

    QPushButton* refreshBtn;

    QPushButton* createBtn;


    QTableWidget* prescriptionTable;


    QComboBox* patientBox;

    QComboBox* diseaseBox;

    QLabel* doctorLabel;

    QLineEdit* diagnosisEdit;


    QTableWidget* medicineTable;


    QPushButton* addMedicineBtn;

    QPushButton* removeMedicineBtn;

    QPushButton* saveBtn;

    QPushButton* clearBtn;

    int currentSelectedRow = -1;

private:

    PrescriptionService* prescriptionService;

    QVector<PrescriptionModel> prescriptionData;

    void setupUI();

    void setupSearchArea();

    void setupPrescriptionTable();

    void setupPatientForm();

    void setupMedicineTable();

    void setupButtons();

    void setupStyles();

    void setupConnections();

    void refreshPrescriptionTable();

    void clearForm();

    bool validateInput();

private slots:

    void addMedicineRow();

    void removeMedicineRow();

    void savePrescription();

    void searchPrescription();

    void handlePrescriptionClicked(
        int row,
        int column
        );

    void handleMedicinesLoaded(
        QVector<Medicine> data
        );

    void handleApiError(
        QString message
        );

    void handlePrescriptionsLoaded(
        QVector<PrescriptionModel> data
        );
};

#endif