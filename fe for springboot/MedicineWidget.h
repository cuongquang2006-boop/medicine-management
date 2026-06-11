#ifndef MEDICINEWIDGET_H
#define MEDICINEWIDGET_H

#include "MedicineModel.h"
#include "MedicineService.h"

#include <QWidget>
#include <QVector>

class QLineEdit;
class QSpinBox;
class QDoubleSpinBox;
class QPushButton;
class QTableWidget;


class MedicineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MedicineWidget(QWidget *parent = nullptr);

private:

    MedicineService* medicineService;

    QLineEdit* searchEdit;

    QPushButton* refreshBtn;

    QTableWidget* medicineTable;

    QLineEdit* medicineNameEdit;

    QSpinBox* stockSpin;

    QDoubleSpinBox* priceSpin;

    QPushButton* addBtn;

    QPushButton* updateBtn;

    QPushButton* deleteBtn;

    QPushButton* clearBtn;

    QVector<Medicine> medicines;

    int currentSelectedRow = -1;

private:

    void setupUI();

    void setupSearchArea();

    void setupTable();

    void setupForm();

    void setupButtons();

    void setupStyles();

    void setupConnections();

    void refreshTable();

    void clearForm();

    bool validateInput();

    void fillFormFromTable(int row);

    void applyLowStockHighlight();

    void handleMedicinesLoaded(
        QVector<Medicine> data
        );

    void handleApiError(
        QString message
        );

private slots:

    void addMedicine();

    void updateMedicine();

    void deleteMedicine();

    void searchMedicines();

    void handleTableClicked(int row, int column);
};

#endif