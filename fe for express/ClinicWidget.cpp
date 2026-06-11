#include "ClinicWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include <QLineEdit>
#include <QTextEdit>

#include <QPushButton>

#include <QTableWidget>
#include <QHeaderView>

#include <QMessageBox>

#include <QLabel>

ClinicWidget::ClinicWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();

    setupSearchArea();

    setupTable();

    setupForm();

    setupButtons();

    setupStyles();

    setupConnections();

    clinicService = new ClinicService(this);

    connect(clinicService, &ClinicService::clinicsLoaded,
            this, &ClinicWidget::handleClinicsLoaded);

    connect(clinicService, &ClinicService::errorOccurred,
            this, &ClinicWidget::handleApiError);

    clinicService->fetchClinics();
}


void ClinicWidget::setupUI()
{
    QVBoxLayout* mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(25,25,25,25);

    mainLayout->setSpacing(20);
}


void ClinicWidget::setupSearchArea()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QHBoxLayout* searchLayout =
        new QHBoxLayout;

    searchEdit = new QLineEdit;

    searchEdit->setPlaceholderText(
        "Search clinic..."
        );

    refreshBtn =
        new QPushButton("Refresh");

    searchLayout->addWidget(searchEdit);

    searchLayout->addWidget(refreshBtn);

    mainLayout->addLayout(searchLayout);
}


void ClinicWidget::setupTable()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    clinicTable =
        new QTableWidget;

    clinicTable->setColumnCount(5);

    clinicTable->setHorizontalHeaderLabels({
        "ID",
        "Clinic Name",
        "Location",
        "Description",
        "Created At"
    });

    clinicTable->horizontalHeader()
        ->setSectionResizeMode(
            QHeaderView::Stretch
            );

    clinicTable->setSelectionBehavior(
        QAbstractItemView::SelectRows
        );

    clinicTable->setEditTriggers(
        QAbstractItemView::NoEditTriggers
        );

    clinicTable->setAlternatingRowColors(true);

    clinicTable->verticalHeader()
        ->setVisible(false);

    mainLayout->addWidget(clinicTable);
}


void ClinicWidget::setupForm()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QFormLayout* formLayout =
        new QFormLayout;

    clinicNameEdit =
        new QLineEdit;

    clinicNameEdit->setPlaceholderText(
        "Enter clinic name"
        );

    locationEdit =
        new QLineEdit;

    locationEdit->setPlaceholderText(
        "Enter location"
        );

    descriptionEdit =
        new QTextEdit;

    descriptionEdit->setPlaceholderText(
        "Enter clinic description..."
        );

    descriptionEdit->setMinimumHeight(100);

    formLayout->addRow(
        "Clinic Name:",
        clinicNameEdit
        );

    formLayout->addRow(
        "Location:",
        locationEdit
        );

    formLayout->addRow(
        "Description:",
        descriptionEdit
        );

    mainLayout->addLayout(formLayout);
}


void ClinicWidget::setupButtons()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QHBoxLayout* btnLayout =
        new QHBoxLayout;

    addBtn =
        new QPushButton("Add Clinic");

    updateBtn =
        new QPushButton("Update Clinic");

    deleteBtn =
        new QPushButton("Delete Clinic");

    clearBtn =
        new QPushButton("Clear Form");

    btnLayout->addWidget(addBtn);

    btnLayout->addWidget(updateBtn);

    btnLayout->addWidget(deleteBtn);

    btnLayout->addWidget(clearBtn);

    mainLayout->addLayout(btnLayout);
}


void ClinicWidget::setupStyles()
{
    setStyleSheet(R"(

        QWidget{
            background:#f4f6f9;
        }

        QLabel{
            color:#111827;
        }

        QLineEdit,
        QTextEdit{

            background:white;

            color:#111827;

            border:1px solid #dbeafe;

            border-radius:10px;

            padding:8px;

            font-size:14px;
        }

        QLineEdit:focus,
        QTextEdit:focus{

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


void ClinicWidget::setupConnections()
{
    connect(addBtn,
            &QPushButton::clicked,
            this,
            &ClinicWidget::addClinic);

    connect(updateBtn,
            &QPushButton::clicked,
            this,
            &ClinicWidget::updateClinic);

    connect(deleteBtn,
            &QPushButton::clicked,
            this,
            &ClinicWidget::deleteClinic);

    connect(clearBtn,
            &QPushButton::clicked,
            this,
            &ClinicWidget::clearForm);

    connect(searchEdit,
            &QLineEdit::textChanged,
            this,
            &ClinicWidget::searchClinic);

    connect(clinicTable,
            &QTableWidget::cellClicked,
            this,
            &ClinicWidget::handleTableClicked);
}


void ClinicWidget::refreshTable()
{
    clinicTable->setRowCount(0);

    for(int i = 0; i < clinics.size(); ++i)
    {
        const Clinic& c =
            clinics[i];

        clinicTable->insertRow(i);

        clinicTable->setItem(
            i,0,
            new QTableWidgetItem(
                QString::number(c.id)
                )
            );

        clinicTable->setItem(
            i,1,
            new QTableWidgetItem(
                c.name
                )
            );

        clinicTable->setItem(
            i,2,
            new QTableWidgetItem(
                c.location
                )
            );

        clinicTable->setItem(
            i,3,
            new QTableWidgetItem(
                c.description
                )
            );

        clinicTable->setItem(
            i,4,
            new QTableWidgetItem(
                c.createdAt
                )
            );
    }
}


void ClinicWidget::clearForm()
{
    clinicNameEdit->clear();

    locationEdit->clear();

    descriptionEdit->clear();

    currentSelectedRow = -1;
}



bool ClinicWidget::validateInput()
{
    if(clinicNameEdit->text()
            .trimmed()
            .isEmpty())
    {
        QMessageBox::warning(
            this,
            "Validation",
            "Clinic name is required"
            );

        return false;
    }

    return true;
}


void ClinicWidget::fillFormFromTable(int row)
{
    const Clinic& c =
        clinics[row];

    clinicNameEdit->setText(
        c.name
        );

    locationEdit->setText(
        c.location
        );

    descriptionEdit->setPlainText(
        c.description
        );
}


void ClinicWidget::addClinic()
{
    if(!validateInput())
        return;

    Clinic c;

    c.name =
        clinicNameEdit->text();

    c.location =
        locationEdit->text();

    c.description =
        descriptionEdit->toPlainText();

    clinicService->createClinic(c);

    clearForm();
}


void ClinicWidget::updateClinic()
{
    if(currentSelectedRow < 0)
        return;

    Clinic c =
        clinics[currentSelectedRow];

    c.name =
        clinicNameEdit->text();

    c.location =
        locationEdit->text();

    c.description =
        descriptionEdit->toPlainText();

    clinicService->updateClinic(c);

    clearForm();
}


void ClinicWidget::deleteClinic()
{
    if(currentSelectedRow < 0)
        return;

    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(

        this,

        "Delete Clinic",

        "Are you sure you want to delete this clinic?",

        QMessageBox::Yes
            |
            QMessageBox::No
        );

    if(reply == QMessageBox::No)
        return;

    int clinicId =
        clinics[currentSelectedRow].id;

    clinicService->deleteClinic(
        clinicId
        );

    clearForm();
}


void ClinicWidget::searchClinic()
{
    QString keyword =
        searchEdit->text().trimmed();

    for(int row = 0;
         row < clinicTable->rowCount();
         ++row)
    {
        bool match =
            clinicTable
                ->item(row,1)
                ->text()
                .contains(
                    keyword,
                    Qt::CaseInsensitive
                    );

        clinicTable
            ->setRowHidden(
                row,
                !match
                );
    }
}


void ClinicWidget::handleTableClicked(
    int row,
    int column
    )
{
    Q_UNUSED(column);

    currentSelectedRow = row;

    fillFormFromTable(row);
}


void ClinicWidget::handleClinicsLoaded(
    QVector<Clinic> data
    )
{
    clinics = data;

    refreshTable();
}


void ClinicWidget::handleApiError(
    QString message
    )
{
    QMessageBox::critical(
        this,
        "API Error",
        message
        );
}