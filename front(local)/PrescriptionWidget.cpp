#include "PrescriptionWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include <QComboBox>
#include <QLineEdit>

#include <QPushButton>
#include <QLabel>

#include <QTableWidget>
#include <QHeaderView>

#include <QMessageBox>

#include <QTableWidgetItem>


PrescriptionWidget::PrescriptionWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();

    setupSearchArea();

    setupPrescriptionTable();

    setupPatientForm();

    setupMedicineTable();

    setupButtons();

    setupStyles();

    setupConnections();

    medicineService =
        new MedicineService(this);

    connect(medicineService,
            &MedicineService::medicinesLoaded,
            this,
            &PrescriptionWidget::handleMedicinesLoaded);

    connect(medicineService,
            &MedicineService::errorOccurred,
            this,
            &PrescriptionWidget::handleApiError);

    medicineService->fetchMedicines();

    prescriptionService =
        new PrescriptionService(this);

    connect(prescriptionService,
            &PrescriptionService::prescriptionsLoaded,
            this,
            &PrescriptionWidget::handlePrescriptionsLoaded);

    connect(prescriptionService,
            &PrescriptionService::errorOccurred,
            this,
            &PrescriptionWidget::handleApiError);

    prescriptionService->fetchPrescriptions();
}


void PrescriptionWidget::setupUI()
{
    QVBoxLayout* mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        25,25,25,25
        );

    mainLayout->setSpacing(20);
}


void PrescriptionWidget::setupSearchArea()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QHBoxLayout* layout =
        new QHBoxLayout;

    searchEdit = new QLineEdit;

    searchEdit->setPlaceholderText(
        "Search prescription..."
        );

    refreshBtn =
        new QPushButton("Refresh");

    createBtn =
        new QPushButton("Create Prescription");

    layout->addWidget(searchEdit);

    layout->addWidget(refreshBtn);

    layout->addWidget(createBtn);

    mainLayout->addLayout(layout);
}


void PrescriptionWidget::setupPrescriptionTable()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    prescriptionTable =
        new QTableWidget;

    prescriptionTable->setColumnCount(6);

    prescriptionTable->setHorizontalHeaderLabels({
        "ID",
        "Patient",
        "Disease",
        "Doctor",
        "Medicine Count",
        "Created At"
    });

    prescriptionTable->horizontalHeader()
        ->setSectionResizeMode(
            QHeaderView::Stretch
            );

    prescriptionTable->setSelectionBehavior(
        QAbstractItemView::SelectRows
        );

    prescriptionTable->setEditTriggers(
        QAbstractItemView::NoEditTriggers
        );

    prescriptionTable->setAlternatingRowColors(true);

    prescriptionTable->verticalHeader()
        ->setVisible(false);

    mainLayout->addWidget(
        prescriptionTable
        );
}


void PrescriptionWidget::setupPatientForm()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QFormLayout* formLayout =
        new QFormLayout;

    patientBox = new QComboBox;

    patientBox->addItems({
        "Nguyen Van A",
        "Tran Thi B"
    });

    diseaseBox = new QComboBox;

    diseaseBox->addItems({
        "Flu",
        "Fever",
        "Dental Pain"
    });

    doctorLabel =
        new QLabel("Dr. Cuong");

    diagnosisEdit =
        new QLineEdit;

    diagnosisEdit->setPlaceholderText(
        "Enter diagnosis..."
        );

    formLayout->addRow(
        "Patient:",
        patientBox
        );

    formLayout->addRow(
        "Disease:",
        diseaseBox
        );

    formLayout->addRow(
        "Doctor:",
        doctorLabel
        );

    formLayout->addRow(
        "Diagnosis:",
        diagnosisEdit
        );

    mainLayout->addLayout(formLayout);
}


void PrescriptionWidget::setupMedicineTable()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QLabel* label =
        new QLabel("Medicine List");

    label->setStyleSheet(R"(
        font-size:20px;
        font-weight:bold;
        color:#111827;
    )");

    mainLayout->addWidget(label);

    medicineTable =
        new QTableWidget;

    medicineTable->setColumnCount(4);

    medicineTable->setHorizontalHeaderLabels({
        "Medicine",
        "Quantity",
        "Dosage",
        "Instruction"
    });

    medicineTable->horizontalHeader()
        ->setSectionResizeMode(
            QHeaderView::Stretch
            );

    medicineTable->setAlternatingRowColors(true);

    medicineTable->verticalHeader()
        ->setVisible(false);

    mainLayout->addWidget(medicineTable);
}


void PrescriptionWidget::setupButtons()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QHBoxLayout* btnLayout =
        new QHBoxLayout;

    addMedicineBtn =
        new QPushButton("Add Medicine");

    removeMedicineBtn =
        new QPushButton("Remove Medicine");

    saveBtn =
        new QPushButton("Save Prescription");

    clearBtn =
        new QPushButton("Clear Form");

    btnLayout->addWidget(addMedicineBtn);

    btnLayout->addWidget(removeMedicineBtn);

    btnLayout->addWidget(saveBtn);

    btnLayout->addWidget(clearBtn);

    mainLayout->addLayout(btnLayout);
}


void PrescriptionWidget::setupStyles()
{
    setStyleSheet(R"(

        QWidget{
            background:#f4f6f9;
        }

        QLabel{
            color:#111827;
        }

        QLineEdit,
        QComboBox{

            background:white;

            color:#111827;

            border:1px solid #dbeafe;

            border-radius:10px;

            padding:8px;

            min-height:20px;

            font-size:14px;
        }

        QLineEdit:focus,
        QComboBox:focus{

            border:2px solid #93c5fd;
        }

        QPushButton{

            background:#2563eb;

            color:white;

            border:1px solid #2563eb;

            border-radius:10px;

            padding:10px;

            font-size:14px;
        }

        QPushButton:hover{

            background:#1d4ed8;
        }

        QTableWidget{

            background:white;

            color:#111827;

            border:1px solid #dbeafe;

            border-radius:10px;

            font-size:14px;

            gridline-color:#e5e7eb;

            alternate-background-color:#f9fafb;
        }

        QHeaderView::section{

            background:#f3f4f6;

            color:#111827;

            border:none;

            padding:10px;

            font-weight:bold;
        }

    )");
}


void PrescriptionWidget::setupConnections()
{
    connect(addMedicineBtn,
            &QPushButton::clicked,
            this,
            &PrescriptionWidget::addMedicineRow);

    connect(removeMedicineBtn,
            &QPushButton::clicked,
            this,
            &PrescriptionWidget::removeMedicineRow);

    connect(saveBtn,
            &QPushButton::clicked,
            this,
            &PrescriptionWidget::savePrescription);

    connect(clearBtn,
            &QPushButton::clicked,
            this,
            &PrescriptionWidget::clearForm);

    connect(searchEdit,
            &QLineEdit::textChanged,
            this,
            &PrescriptionWidget::searchPrescription);

    connect(prescriptionTable,
            &QTableWidget::cellClicked,
            this,
            &PrescriptionWidget::handlePrescriptionClicked);

    connect(refreshBtn,
            &QPushButton::clicked,
            prescriptionService,
            &PrescriptionService::fetchPrescriptions);
}


void PrescriptionWidget::clearForm()
{
    patientBox->setCurrentIndex(0);

    diseaseBox->setCurrentIndex(0);

    diagnosisEdit->clear();

    medicineTable->setRowCount(0);

    currentSelectedRow = -1;
}


bool PrescriptionWidget::validateInput()
{
    if(diagnosisEdit->text()
            .trimmed()
            .isEmpty())
    {
        QMessageBox::warning(
            this,
            "Validation",
            "Diagnosis is required"
            );

        return false;
    }

    return true;
}


// void PrescriptionWidget::fillFormFromPrescription(
//     int row
//     )
// {
//     const Prescription& p =
//         prescriptions[row];

//     patientBox->setCurrentText(
//         p.patientName
//         );

//     diseaseBox->setCurrentText(
//         p.diseaseName
//         );

//     diagnosisEdit->setText(
//         p.diagnosis
//         );

//     medicineTable->setRowCount(0);

//     for(int i = 0;
//          i < p.medicines.size();
//          ++i)
//     {
//         medicineTable->insertRow(i);

//         const PrescriptionMedicine& m =
//             p.medicines[i];

//         medicineTable->setItem(
//             i,0,
//             new QTableWidgetItem(
//                 m.medicineName
//                 )
//             );

//         medicineTable->setItem(
//             i,1,
//             new QTableWidgetItem(
//                 QString::number(
//                     m.quantity
//                     )
//                 )
//             );

//         medicineTable->setItem(
//             i,2,
//             new QTableWidgetItem(
//                 m.dosage
//                 )
//             );

//         medicineTable->setItem(
//             i,3,
//             new QTableWidgetItem(
//                 m.instruction
//                 )
//             );
//     }
// }

void PrescriptionWidget::addMedicineRow()
{
    int row =
        medicineTable->rowCount();

    medicineTable->insertRow(row);

    QComboBox* medicineBox =
        new QComboBox;

    for(const Medicine& medicine : medicines)
    {
        if(medicine.stock > 0)
        {
            medicineBox->addItem(

                    medicine.name
                    + " (Stock: "
                    + QString::number(medicine.stock)
                    + ")",

                medicine.id
                );
        }
    }

    medicineTable->setCellWidget(
        row,
        0,
        medicineBox
        );

    medicineTable->setItem(
        row,
        1,
        new QTableWidgetItem("1")
        );

    medicineTable->setItem(
        row,
        2,
        new QTableWidgetItem("")
        );

    medicineTable->setItem(
        row,
        3,
        new QTableWidgetItem("")
        );
}

void PrescriptionWidget::removeMedicineRow()
{
    int row =
        medicineTable->currentRow();

    if(row >= 0)
    {
        medicineTable->removeRow(row);
    }
}



void PrescriptionWidget::savePrescription()
{

    if(!validateInput())
        return;

    PrescriptionModel model;

    model.patientId = 1;

    model.diseaseId = 1;

    model.createdBy = 1;

    model.diagnosis =
        diagnosisEdit->text();

    prescriptionService
        ->createPrescription(model);

    clearForm();
}



void PrescriptionWidget::searchPrescription()
{
    QString keyword =
        searchEdit->text().trimmed();

    for(int row = 0;
         row < prescriptionTable->rowCount();
         ++row)
    {
        bool match =
            prescriptionTable
                ->item(row,1)
                ->text()
                .contains(
                    keyword,
                    Qt::CaseInsensitive
                    );

        prescriptionTable
            ->setRowHidden(
                row,
                !match
                );
    }
}



void PrescriptionWidget::handlePrescriptionClicked(int row, int column)
{
    Q_UNUSED(column);

    currentSelectedRow = row;
}

void PrescriptionWidget::handleMedicinesLoaded(
    QVector<Medicine> data
    )
{
    medicines = data;
}


void PrescriptionWidget::handleApiError(
    QString message
    )
{
    QMessageBox::critical(
        this,
        "API Error",
        message
        );
}


void PrescriptionWidget::handlePrescriptionsLoaded(
    QVector<PrescriptionModel> data
    )
{
    prescriptionData = data;

    refreshPrescriptionTable();

}


void PrescriptionWidget::refreshPrescriptionTable()
{
    prescriptionTable->setRowCount(0);

    for(int i = 0;
         i < prescriptionData.size();
         ++i)
    {
        const PrescriptionModel& p =
            prescriptionData[i];

        prescriptionTable->insertRow(i);

        prescriptionTable->setItem(
            i,0,
            new QTableWidgetItem(
                QString::number(p.id)
                )
            );

        prescriptionTable->setItem(
            i,1,
            new QTableWidgetItem(
                p.patientName
                )
            );

        prescriptionTable->setItem(
            i,2,
            new QTableWidgetItem(
                p.diseaseName
                )
            );

        prescriptionTable->setItem(
            i,3,
            new QTableWidgetItem(
                p.doctorName
                )
            );

        prescriptionTable->setItem(
            i,4,
            new QTableWidgetItem(
                "-"
                )
            );

        prescriptionTable->setItem(
            i,5,
            new QTableWidgetItem(
                p.createdAt
                )
            );
    }
}