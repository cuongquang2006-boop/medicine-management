#include "DiseaseWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>

#include <QPushButton>

#include <QTableWidget>
#include <QHeaderView>

#include <QMessageBox>

#include <QLabel>


DiseaseWidget::DiseaseWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();

    setupSearchArea();

    setupTable();

    setupForm();

    setupButtons();

    setupStyles();

    setupConnections();

    diseaseService =
        new DiseaseService(this);

    connect(diseaseService, &DiseaseService::diseasesLoaded,
            this, &DiseaseWidget::handleDiseasesLoaded);

    connect(diseaseService, &DiseaseService::errorOccurred,
            this, &DiseaseWidget::handleApiError);

    diseaseService->fetchDiseases();

}


void DiseaseWidget::setupUI()
{
    QVBoxLayout* mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        25,25,25,25
        );

    mainLayout->setSpacing(20);
}


void DiseaseWidget::setupSearchArea()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QHBoxLayout* searchLayout =
        new QHBoxLayout;

    searchEdit = new QLineEdit;

    searchEdit->setPlaceholderText(
        "Search disease..."
        );

    clinicFilterBox =
        new QComboBox;

    clinicFilterBox->addItems({
        "All Clinics",
        "General Clinic",
        "Dental Clinic",
        "Eye Clinic"
    });

    refreshBtn =
        new QPushButton("Refresh");

    searchLayout->addWidget(searchEdit);

    searchLayout->addWidget(clinicFilterBox);

    searchLayout->addWidget(refreshBtn);

    mainLayout->addLayout(searchLayout);
}


void DiseaseWidget::setupTable()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    diseaseTable =
        new QTableWidget;

    diseaseTable->setColumnCount(6);

    diseaseTable->setHorizontalHeaderLabels({
        "ID",
        "Disease Name",
        "Clinic",
        "Symptoms",
        "Description",
        "Created At"
    });

    diseaseTable->horizontalHeader()
        ->setSectionResizeMode(
            QHeaderView::Stretch
            );

    diseaseTable->setSelectionBehavior(
        QAbstractItemView::SelectRows
        );

    diseaseTable->setEditTriggers(
        QAbstractItemView::NoEditTriggers
        );

    diseaseTable->setAlternatingRowColors(true);

    diseaseTable->verticalHeader()
        ->setVisible(false);

    mainLayout->addWidget(diseaseTable);
}


void DiseaseWidget::setupForm()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QFormLayout* formLayout =
        new QFormLayout;

    diseaseNameEdit =
        new QLineEdit;

    diseaseNameEdit->setPlaceholderText(
        "Enter disease name"
        );

    clinicBox =
        new QComboBox;

    clinicBox->addItems({
        "General Clinic",
        "Dental Clinic",
        "Eye Clinic"
    });

    symptomsEdit =
        new QTextEdit;

    symptomsEdit->setPlaceholderText(
        "Enter symptoms..."
        );

    symptomsEdit->setMinimumHeight(80);

    descriptionEdit =
        new QTextEdit;

    descriptionEdit->setPlaceholderText(
        "Enter disease description..."
        );

    descriptionEdit->setMinimumHeight(100);

    formLayout->addRow(
        "Disease Name:",
        diseaseNameEdit
        );

    formLayout->addRow(
        "Clinic:",
        clinicBox
        );

    formLayout->addRow(
        "Symptoms:",
        symptomsEdit
        );

    formLayout->addRow(
        "Description:",
        descriptionEdit
        );

    mainLayout->addLayout(formLayout);
}


void DiseaseWidget::setupButtons()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QHBoxLayout* btnLayout =
        new QHBoxLayout;

    addBtn =
        new QPushButton("Add Disease");

    updateBtn =
        new QPushButton("Update Disease");

    deleteBtn =
        new QPushButton("Delete Disease");

    clearBtn =
        new QPushButton("Clear Form");

    btnLayout->addWidget(addBtn);

    btnLayout->addWidget(updateBtn);

    btnLayout->addWidget(deleteBtn);

    btnLayout->addWidget(clearBtn);

    mainLayout->addLayout(btnLayout);
}


void DiseaseWidget::setupStyles()
{
    setStyleSheet(R"(

        QWidget{
            background:#f4f6f9;
        }

        QLabel{
            color:#111827;
        }

        QLineEdit,
        QTextEdit,
        QComboBox{

            background:white;

            color:#111827;

            border:1px solid #dbeafe;

            border-radius:10px;

            padding:8px;

            font-size:14px;
        }

        QLineEdit:focus,
        QTextEdit:focus,
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


void DiseaseWidget::setupConnections()
{
    connect(addBtn,
            &QPushButton::clicked,
            this,
            &DiseaseWidget::addDisease);

    connect(updateBtn,
            &QPushButton::clicked,
            this,
            &DiseaseWidget::updateDisease);

    connect(deleteBtn,
            &QPushButton::clicked,
            this,
            &DiseaseWidget::deleteDisease);

    connect(clearBtn,
            &QPushButton::clicked,
            this,
            &DiseaseWidget::clearForm);

    connect(searchEdit,
            &QLineEdit::textChanged,
            this,
            &DiseaseWidget::searchDisease);

    connect(clinicFilterBox,
            &QComboBox::currentTextChanged,
            this,
            &DiseaseWidget::searchDisease);

    connect(diseaseTable,
            &QTableWidget::cellClicked,
            this,
            &DiseaseWidget::handleTableClicked);

    connect(refreshBtn,
            &QPushButton::clicked,
            diseaseService,
            &DiseaseService::fetchDiseases);
}


void DiseaseWidget::clearForm()
{
    diseaseNameEdit->clear();

    clinicBox->setCurrentIndex(0);

    symptomsEdit->clear();

    descriptionEdit->clear();

    currentSelectedRow = -1;
}


bool DiseaseWidget::validateInput()
{
    if(diseaseNameEdit->text()
            .trimmed()
            .isEmpty())
    {
        QMessageBox::warning(
            this,
            "Validation",
            "Disease name is required"
            );

        return false;
    }

    return true;
}


void DiseaseWidget::fillFormFromTable(int row)
{
    const Disease& d =
        diseases[row];

    diseaseNameEdit->setText(
        d.diseaseName
        );

    clinicBox->setCurrentText(
        d.clinicName
        );

    symptomsEdit->setPlainText(
        d.symptoms
        );

    descriptionEdit->setPlainText(
        d.description
        );
}

void DiseaseWidget::addDisease()
{
    if(!validateInput())
        return;

    Disease d;

    d.diseaseName =
        diseaseNameEdit->text();

    d.clinicName =
        clinicBox->currentText();

    d.symptoms =
        symptomsEdit->toPlainText();

    d.description =
        descriptionEdit->toPlainText();

    diseaseService->createDisease(d);

    clearForm();
}

void DiseaseWidget::updateDisease()
{
    if(currentSelectedRow < 0)
        return;

    Disease d =
        diseases[currentSelectedRow];

    d.diseaseName =
        diseaseNameEdit->text();

    d.clinicName =
        clinicBox->currentText();

    d.symptoms =
        symptomsEdit->toPlainText();

    d.description =
        descriptionEdit->toPlainText();

    diseaseService->updateDisease(d);

    clearForm();
}

void DiseaseWidget::deleteDisease()
{
    if(currentSelectedRow < 0)
        return;

    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(

        this,

        "Delete Disease",

        "Are you sure you want to delete this disease?",

        QMessageBox::Yes
            |
            QMessageBox::No
        );

    if(reply == QMessageBox::No)
        return;

    int diseaseId =
        diseases[currentSelectedRow].id;

    diseaseService->deleteDisease(
        diseaseId
        );

    clearForm();
}


void DiseaseWidget::searchDisease()
{
    QString keyword =
        searchEdit->text().trimmed();

    QString clinicFilter =
        clinicFilterBox->currentText();

    for(int row = 0;
         row < diseaseTable->rowCount();
         ++row)
    {
        bool nameMatch =
            diseaseTable
                ->item(row,1)
                ->text()
                .contains(
                    keyword,
                    Qt::CaseInsensitive
                    );

        bool clinicMatch =
            clinicFilter == "All Clinics"
            ||
            diseaseTable
                    ->item(row,2)
                    ->text() == clinicFilter;

        diseaseTable->setRowHidden(
            row,
            !(nameMatch && clinicMatch)
            );
    }
}


void DiseaseWidget::refreshTable()
{
    diseaseTable->setRowCount(0);

    for(int i = 0;
         i < diseases.size();
         ++i)
    {
        const Disease& d =
            diseases[i];

        diseaseTable->insertRow(i);

        diseaseTable->setItem(
            i,0,
            new QTableWidgetItem(
                QString::number(d.id)
                )
            );

        diseaseTable->setItem(
            i,1,
            new QTableWidgetItem(
                d.diseaseName
                )
            );

        diseaseTable->setItem(
            i,2,
            new QTableWidgetItem(
                d.clinicName
                )
            );

        diseaseTable->setItem(
            i,3,
            new QTableWidgetItem(
                d.symptoms
                )
            );

        diseaseTable->setItem(
            i,4,
            new QTableWidgetItem(
                d.description
                )
            );

        diseaseTable->setItem(
            i,5,
            new QTableWidgetItem(
                d.createdAt
                )
            );
    }
}


void DiseaseWidget::handleTableClicked(
    int row,
    int column
    )
{
    Q_UNUSED(column);

    currentSelectedRow = row;

    fillFormFromTable(row);
}

void DiseaseWidget::handleDiseasesLoaded(
    QVector<Disease> data
    )
{
    diseases = data;

    refreshTable();
}


void DiseaseWidget::handleApiError(
    QString message
    )
{
    QMessageBox::critical(
        this,
        "API Error",
        message
        );
}