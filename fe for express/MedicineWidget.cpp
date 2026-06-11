#include "MedicineWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>

#include <QPushButton>

#include <QTableWidget>
#include <QHeaderView>

#include <QMessageBox>

#include <QLabel>

#include <QBrush>
#include <QColor>


MedicineWidget::MedicineWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();

    setupSearchArea();

    setupTable();

    setupForm();

    setupButtons();

    setupStyles();

    setupConnections();

    medicineService =
        new MedicineService(this);

    connect(medicineService, &MedicineService::medicinesLoaded,
            this, &MedicineWidget::handleMedicinesLoaded);

    connect(medicineService, &MedicineService::errorOccurred,
            this, &MedicineWidget::handleApiError);

    medicineService->fetchMedicines();
}


void MedicineWidget::setupUI()
{
    QVBoxLayout* mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        25,25,25,25
        );

    mainLayout->setSpacing(20);
}


void MedicineWidget::setupSearchArea()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QHBoxLayout* searchLayout =
        new QHBoxLayout;

    searchEdit = new QLineEdit;

    searchEdit->setPlaceholderText(
        "Search medicine..."
        );

    refreshBtn =
        new QPushButton("Refresh");

    searchLayout->addWidget(searchEdit);

    searchLayout->addWidget(refreshBtn);

    mainLayout->addLayout(searchLayout);
}


void MedicineWidget::setupTable()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    medicineTable = new QTableWidget;

    medicineTable->setColumnCount(5);

    medicineTable->setHorizontalHeaderLabels({
        "ID",
        "Medicine Name",
        "Stock",
        "Price",
        "Created At"
    });

    medicineTable->horizontalHeader()
        ->setSectionResizeMode(
            QHeaderView::Stretch
            );

    medicineTable->setSelectionBehavior(
        QAbstractItemView::SelectRows
        );

    medicineTable->setEditTriggers(
        QAbstractItemView::NoEditTriggers
        );

    medicineTable->setAlternatingRowColors(true);

    medicineTable->verticalHeader()
        ->setVisible(false);

    mainLayout->addWidget(medicineTable);
}


void MedicineWidget::setupForm()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QFormLayout* formLayout =
        new QFormLayout;

    medicineNameEdit = new QLineEdit;

    medicineNameEdit->setPlaceholderText(
        "Enter medicine name"
        );

    stockSpin = new QSpinBox;

    stockSpin->setRange(0,100000);

    priceSpin = new QDoubleSpinBox;

    priceSpin->setRange(0,999999);

    priceSpin->setDecimals(2);

    priceSpin->setPrefix("$ ");

    formLayout->addRow(
        "Medicine Name:",
        medicineNameEdit
        );

    formLayout->addRow(
        "Stock:",
        stockSpin
        );

    formLayout->addRow(
        "Price:",
        priceSpin
        );

    mainLayout->addLayout(formLayout);
}


void MedicineWidget::setupButtons()
{
    QVBoxLayout* mainLayout =
        qobject_cast<QVBoxLayout*>(layout());

    QHBoxLayout* btnLayout =
        new QHBoxLayout;

    addBtn =
        new QPushButton("Add Medicine");

    updateBtn =
        new QPushButton("Update Medicine");

    deleteBtn =
        new QPushButton("Delete Medicine");

    clearBtn =
        new QPushButton("Clear Form");

    btnLayout->addWidget(addBtn);

    btnLayout->addWidget(updateBtn);

    btnLayout->addWidget(deleteBtn);

    btnLayout->addWidget(clearBtn);

    mainLayout->addLayout(btnLayout);
}


void MedicineWidget::setupStyles()
{
    setStyleSheet(R"(

        QWidget{
            background:#f4f6f9;
        }

        QLabel{
            color:#111827;
        }

        QLineEdit,
        QSpinBox,
        QDoubleSpinBox{

            background:white;

            color:#111827;

            border:1px solid #dbeafe;

            border-radius:10px;

            padding:8px;

            min-height:20px;

            font-size:14px;
        }

        QLineEdit:focus,
        QSpinBox:focus,
        QDoubleSpinBox:focus{

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


void MedicineWidget::setupConnections()
{
    connect(addBtn,
            &QPushButton::clicked,
            this,
            &MedicineWidget::addMedicine);

    connect(updateBtn,
            &QPushButton::clicked,
            this,
            &MedicineWidget::updateMedicine);

    connect(deleteBtn,
            &QPushButton::clicked,
            this,
            &MedicineWidget::deleteMedicine);

    connect(clearBtn,
            &QPushButton::clicked,
            this,
            &MedicineWidget::clearForm);

    connect(searchEdit,
            &QLineEdit::textChanged,
            this,
            &MedicineWidget::searchMedicines);

    connect(medicineTable,
            &QTableWidget::cellClicked,
            this,
            &MedicineWidget::handleTableClicked);

    connect(refreshBtn,
            &QPushButton::clicked,
            medicineService,
            &MedicineService::fetchMedicines);
}


void MedicineWidget::refreshTable()
{
    medicineTable->setRowCount(0);

    for(int i = 0; i < medicines.size(); ++i)
    {
        const Medicine& m = medicines[i];

        medicineTable->insertRow(i);

        medicineTable->setItem(
            i,0,
            new QTableWidgetItem(
                QString::number(m.id)
                )
            );

        medicineTable->setItem(
            i,1,
            new QTableWidgetItem(
                m.name
                )
            );

        medicineTable->setItem(
            i,2,
            new QTableWidgetItem(
                QString::number(m.stock)
                )
            );

        medicineTable->setItem(
            i,3,
            new QTableWidgetItem(
                QString::number(m.price)
                )
            );

        medicineTable->setItem(
            i,4,
            new QTableWidgetItem(
                m.createdAt
                )
            );
    }

    applyLowStockHighlight();
}


void MedicineWidget::clearForm()
{
    medicineNameEdit->clear();

    stockSpin->setValue(0);

    priceSpin->setValue(0);

    currentSelectedRow = -1;
}


bool MedicineWidget::validateInput()
{
    if(medicineNameEdit->text()
            .trimmed()
            .isEmpty())
    {
        QMessageBox::warning(
            this,
            "Validation",
            "Medicine name is required"
            );

        return false;
    }

    return true;
}


void MedicineWidget::fillFormFromTable(int row)
{
    const Medicine& m = medicines[row];

    medicineNameEdit->setText(
        m.name
        );

    stockSpin->setValue(
        m.stock
        );

    priceSpin->setValue(
        m.price
        );
}



void MedicineWidget::applyLowStockHighlight()
{
    for(int row = 0;
         row < medicineTable->rowCount();
         ++row)
    {
        int stock =
            medicineTable
                ->item(row,2)
                ->text()
                .toInt();

        if(stock < 10)
        {
            for(int col = 0;
                 col < medicineTable->columnCount();
                 ++col)
            {
                medicineTable
                    ->item(row,col)
                    ->setBackground(
                        QColor("#fee2e2")
                        );
            }
        }
    }
}


void MedicineWidget::addMedicine()
{
    if(!validateInput())
        return;

    Medicine m;

    m.name =
        medicineNameEdit->text();

    m.stock =
        stockSpin->value();

    m.price =
        priceSpin->value();

    medicineService->createMedicine(m);

    clearForm();
}


void MedicineWidget::updateMedicine()
{
    if(currentSelectedRow < 0)
        return;

    Medicine m =
        medicines[currentSelectedRow];

    m.name =
        medicineNameEdit->text();

    m.stock =
        stockSpin->value();

    m.price =
        priceSpin->value();

    medicineService->updateMedicine(m);

    clearForm();
}


void MedicineWidget::deleteMedicine()
{
    if(currentSelectedRow < 0)
        return;

    medicineService->deleteMedicine(
        medicines[currentSelectedRow].id
        );

    clearForm();
}


void MedicineWidget::searchMedicines()
{
    QString keyword =
        searchEdit->text().trimmed();

    for(int row = 0;
         row < medicineTable->rowCount();
         ++row)
    {
        bool match =
            medicineTable
                ->item(row,1)
                ->text()
                .contains(
                    keyword,
                    Qt::CaseInsensitive
                    );

        medicineTable
            ->setRowHidden(
                row,
                !match
                );
    }
}


void MedicineWidget::handleTableClicked(
    int row,
    int column
    )
{
    Q_UNUSED(column);

    currentSelectedRow = row;

    fillFormFromTable(row);
}

void MedicineWidget::handleMedicinesLoaded(QVector<Medicine> data)
{
    medicines = data;

    refreshTable();
}


void MedicineWidget::handleApiError(QString message)
{
    QMessageBox::critical(this, "API Error", message);
}
