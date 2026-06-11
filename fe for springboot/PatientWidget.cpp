#include "PatientWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>

#include <QPushButton>

#include <QTableWidget>
#include <QHeaderView>

#include <QMessageBox>

#include <QLabel>


PatientWidget::PatientWidget(QWidget *parent) : QWidget(parent)
{
    setupUI();

    setupSearchArea();

    setupTable();

    setupForm();

    setupButtons();

    setupStyles();

    setupConnections();

    patientService = new PatientService(this);

    connect(patientService, &PatientService::patientsLoaded,
            this, &PatientWidget::handlePatientsLoaded);

    connect(patientService, &PatientService::errorOccurred,
            this, &PatientWidget::handleApiError);

    patientService->fetchPatients();
}



void PatientWidget::setupUI()
{
    QVBoxLayout* mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        25,25,25,25
        );

    mainLayout->setSpacing(20);
}


void PatientWidget::setupSearchArea()
{
    QVBoxLayout* mainLayout = qobject_cast<QVBoxLayout*>(layout());

    QHBoxLayout* searchLayout = new QHBoxLayout;

    searchEdit = new QLineEdit;

    searchEdit->setPlaceholderText("Search patient...");

    genderFilterBox = new QComboBox;

    genderFilterBox->addItems({
        "All Gender",
        "Male",
        "Female"
    });

    clinicFilterBox = new QComboBox;

    clinicFilterBox->addItems({
        "All Clinics",
        "General",
        "Dental",
        "Eye",
        "Cardiology"
    });

    refreshBtn = new QPushButton("Refresh");

    searchLayout->addWidget(searchEdit);

    searchLayout->addWidget(genderFilterBox);

    searchLayout->addWidget(clinicFilterBox);

    searchLayout->addWidget(refreshBtn);

    mainLayout->addLayout(searchLayout);
}



void PatientWidget::setupTable()
{
    QVBoxLayout* mainLayout = qobject_cast<QVBoxLayout*>(layout());

    patientTable = new QTableWidget;

    patientTable->setColumnCount(8);

    patientTable->setHorizontalHeaderLabels({
        "ID",
        "Full Name",
        "Age",
        "Gender",
        "Phone",
        "Address",
        "Clinic",
        "Created At"
    });

    patientTable->horizontalHeader()
        ->setSectionResizeMode(
            QHeaderView::Stretch
            );

    patientTable->setSelectionBehavior(
        QAbstractItemView::SelectRows
        );

    patientTable->setEditTriggers(
        QAbstractItemView::NoEditTriggers
        );

    patientTable->setAlternatingRowColors(true);

    patientTable->verticalHeader()
        ->setVisible(false);

    mainLayout->addWidget(patientTable);
}



void PatientWidget::setupForm()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QFormLayout* formLayout =
        new QFormLayout;

    fullNameEdit = new QLineEdit;

    fullNameEdit->setPlaceholderText(
        "Enter full name"
        );

    ageSpin = new QSpinBox;

    ageSpin->setRange(1,120);

    genderBox = new QComboBox;

    genderBox->addItems({
        "Male",
        "Female"
    });

    phoneEdit = new QLineEdit;

    phoneEdit->setPlaceholderText(
        "Enter phone"
        );

    addressEdit = new QLineEdit;

    addressEdit->setPlaceholderText(
        "Enter address"
        );

    clinicIdSpin = new QSpinBox;

    clinicIdSpin->setRange(1, 9999);

    formLayout->addRow(
        "Full Name:",
        fullNameEdit
        );

    formLayout->addRow(
        "Age:",
        ageSpin
        );

    formLayout->addRow(
        "Gender:",
        genderBox
        );

    formLayout->addRow(
        "Phone:",
        phoneEdit
        );

    formLayout->addRow(
        "Address:",
        addressEdit
        );

    formLayout->addRow(
        "Clinic ID:",
        clinicIdSpin
        );

    mainLayout->addLayout(formLayout);
}



void PatientWidget::setupButtons()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QHBoxLayout* btnLayout =
        new QHBoxLayout;

    addBtn = new QPushButton(
        "Add Patient"
        );

    updateBtn = new QPushButton(
        "Update Patient"
        );

    deleteBtn = new QPushButton(
        "Delete Patient"
        );

    clearBtn = new QPushButton(
        "Clear Form"
        );

    btnLayout->addWidget(addBtn);

    btnLayout->addWidget(updateBtn);

    btnLayout->addWidget(deleteBtn);

    btnLayout->addWidget(clearBtn);

    mainLayout->addLayout(btnLayout);
}


void PatientWidget::setupStyles()
{
    setStyleSheet(R"(

        QWidget{
            background:#f4f6f9;
        }

        QLineEdit,
        QComboBox,
        QSpinBox{

            background:white;

            color:black;

            border:1px solid #d1d5db;

            border-radius:10px;

            padding:8px;

            min-height:20px;

            font-size:14px;
        }

        QPushButton{

            background:#2563eb;

            color:white;

            border:none;

            border-radius:10px;

            padding:10px;

            font-size:14px;
        }

        QComboBox QAbstractItemView{

            background:white;

            color:black;

            selection-background-color:#2563eb;

            selection-color:white;

            border:1px solid #d1d5db;
        }

        QPushButton:hover{

            background:#1d4ed8;
        }

        QTableWidget{

            background:#dbeafe;

            color:#111827;

            border:3px solid #2563eb;

            border-radius:3px;

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

        QLabel{

            color:#111827;

            font-size:14px;

            font-weight:600;

            background:transparent;

            padding:2px;
        }

        QScrollBar:vertical{

            background:#f3f4f6;

            width:12px;

            border:none;

            border-radius:6px;

            margin:0px;
        }

        QScrollBar::handle:vertical{

            background:#9ca3af;

            border-radius:6px;

            min-height:40px;
        }

        QScrollBar::handle:vertical:hover{

            background:#6b7280;
        }

        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical{

            height:0px;
        }

        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical{

            background:none;
        }

        QScrollBar:horizontal{

            background:#f3f4f6;

            height:12px;

            border:none;

            border-radius:6px;

            margin:0px;
        }

        QScrollBar::handle:horizontal{

            background:#9ca3af;

            border-radius:6px;

            min-width:40px;
        }

        QScrollBar::handle:horizontal:hover{

            background:#6b7280;
        }

        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal{

            width:0px;
        }

        QScrollBar::add-page:horizontal,
        QScrollBar::sub-page:horizontal{

            background:none;
        }

    )");
}


void PatientWidget::setupConnections()
{
    qDebug() << "addBtn:" << addBtn;
    qDebug() << "updateBtn:" << updateBtn;
    qDebug() << "deleteBtn:" << deleteBtn;
    qDebug() << "clearBtn:" << clearBtn;
    qDebug() << "searchEdit:" << searchEdit;
    qDebug() << "patientTable:" << patientTable;

    connect(addBtn,&QPushButton::clicked,
            this,&PatientWidget::addPatient);

    connect(updateBtn,&QPushButton::clicked,
            this,&PatientWidget::updatePatient);

    connect(deleteBtn,&QPushButton::clicked,
            this,&PatientWidget::deletePatient);

    connect(clearBtn,&QPushButton::clicked,
            this,&PatientWidget::clearForm);

    connect(searchEdit,&QLineEdit::textChanged,
            this,&PatientWidget::searchPatients);

    connect(patientTable,&QTableWidget::cellClicked,
            this,&PatientWidget::handleTableClicked);
}



void PatientWidget::refreshTable()
{
    patientTable->setRowCount(0);

    for(int i = 0; i < patients.size(); ++i)
    {
        const Patient& p = patients[i];

        patientTable->insertRow(i);

        patientTable->setItem(
            i,0,
            new QTableWidgetItem(
                QString::number(p.id)
                )
            );

        patientTable->setItem(
            i,1,
            new QTableWidgetItem(
                p.fullName
                )
            );

        patientTable->setItem(
            i,2,
            new QTableWidgetItem(
                QString::number(p.age)
                )
            );

        patientTable->setItem(
            i,3,
            new QTableWidgetItem(
                p.gender
                )
            );

        patientTable->setItem(
            i,4,
            new QTableWidgetItem(
                p.phone
                )
            );

        patientTable->setItem(
            i,5,
            new QTableWidgetItem(
                p.address
                )
            );

        patientTable->setItem(
            i,6,
            new QTableWidgetItem(
                QString::number(p.clinicId)
                )
            );

        patientTable->setItem(
            i,7,
            new QTableWidgetItem(
                p.createdAt
                )
            );
    }
}


void PatientWidget::clearForm()
{
    fullNameEdit->clear();

    ageSpin->setValue(1);

    genderBox->setCurrentIndex(0);

    phoneEdit->clear();

    addressEdit->clear();

    clinicIdSpin->setValue(1);

    currentSelectedRow = -1;
}



bool PatientWidget::validateInput()
{
    if(fullNameEdit->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Validation", "Full name is required");
        return false;
    }
    return true;
}



void PatientWidget::fillFormFromTable(int row)
{
    const Patient& p = patients[row];

    fullNameEdit->setText(p.fullName);

    ageSpin->setValue(p.age);

    genderBox->setCurrentText(p.gender);

    phoneEdit->setText(p.phone);

    addressEdit->setText(p.address);

    clinicIdSpin->setValue(
        p.clinicId
        );


}



void PatientWidget::addPatient()
{
    if(!validateInput())
    {
        return;
    }

    Patient patient;

    patient.fullName =
        fullNameEdit->text();

    patient.age =
        ageSpin->value();

    patient.gender =
        genderBox->currentText();

    patient.phone =
        phoneEdit->text();

    patient.address =
        addressEdit->text();

    patient.clinicId =
        clinicIdSpin->value();

    qDebug() << "CLINIC ID =" << patient.clinicId;

    patientService->createPatient(patient);

    clearForm();

    QMessageBox::information(
        this,
        "Success",
        "Patient added successfully"
        );
}


void PatientWidget::updatePatient()
{
    if(currentSelectedRow < 0)
    {
        QMessageBox::warning(
            this,
            "Warning",
            "Please select patient"
            );

        return;
    }

    if(!validateInput())
    {
        return;
    }

    Patient patient =
        patients[currentSelectedRow];

    patient.fullName =
        fullNameEdit->text();

    patient.age =
        ageSpin->value();

    patient.gender =
        genderBox->currentText();

    patient.phone =
        phoneEdit->text();

    patient.address =
        addressEdit->text();

    patient.clinicId =
        clinicIdSpin->value();

    patientService->updatePatient(patient);

    clearForm();

    QMessageBox::information(
        this,
        "Success",
        "Patient updated successfully"
        );
}


void PatientWidget::deletePatient()
{
    if(currentSelectedRow < 0)
    {
        QMessageBox::warning(
            this,
            "Warning",
            "Please select patient"
            );
        return;
    }

    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(

        this,

        "Delete Patient",

        "Are you sure you want to delete this patient?",

        QMessageBox::Yes
            |
        QMessageBox::No
        );

    if(reply == QMessageBox::No)
    {
        return;
    }

    int patientId =
        patients[currentSelectedRow].id;

    patientService->deletePatient(patientId);

    clearForm();

    QMessageBox::information(
        this,
        "Success",
        "Patient deleted successfully"
        );
}


void PatientWidget::searchPatients()
{
    QString keyword =
        searchEdit->text().trimmed();

    for(int row = 0;
         row < patientTable->rowCount();
         ++row)
    {
        bool match =
            patientTable
                ->item(row,1)
                ->text()
                .contains(
                    keyword,
                    Qt::CaseInsensitive
                    );

        patientTable
            ->setRowHidden(
                row,
                !match
                );
    }
}



void PatientWidget::handleTableClicked(int row,int column)
{
    Q_UNUSED(column);

    currentSelectedRow = row;

    fillFormFromTable(row);
}


void PatientWidget::handlePatientsLoaded(QVector<Patient> data)
{
    patients = data;
    refreshTable();
}


void PatientWidget::handleApiError(QString message)
{
    QMessageBox::critical(this,"API Error",message);
}