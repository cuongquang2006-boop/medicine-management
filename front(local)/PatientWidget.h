#ifndef PATIENTWIDGET_H
#define PATIENTWIDGET_H

#include "PatientModel.h"
#include "PatientService.h"

#include <QWidget>
#include <QVector>

class QLineEdit;
class QSpinBox;
class QComboBox;
class QPushButton;
class QTableWidget;

class PatientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PatientWidget(QWidget *parent = nullptr);

private:

    PatientService* patientService;


    QLineEdit* searchEdit;

    QComboBox* genderFilterBox;

    QComboBox* clinicFilterBox;

    QPushButton* refreshBtn;


    QTableWidget* patientTable;


    QLineEdit* fullNameEdit;

    QSpinBox* ageSpin;

    QComboBox* genderBox;

    QLineEdit* phoneEdit;

    QLineEdit* addressEdit;

    QComboBox* clinicBox;


    QPushButton* addBtn;

    QPushButton* updateBtn;

    QPushButton* deleteBtn;

    QPushButton* clearBtn;


    QVector<Patient> patients;

    int currentSelectedRow = -1;

private:

    void setupUI();

    void setupSearchArea();

    void setupTable();

    void setupForm();

    void setupButtons();

    void setupStyles();

    void setupConnections();


    void loadData();

    void refreshTable();

    void clearForm();

    bool validateInput();

    void fillFormFromTable(int row);

private slots:

    void addPatient();

    void updatePatient();

    void deletePatient();

    void searchPatients();

    void handleTableClicked(int row, int column);

    void handlePatientsLoaded(QVector<Patient> data);

    void handleApiError(QString message);

};

#endif