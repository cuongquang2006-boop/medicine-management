#ifndef CLINICWIDGET_H
#define CLINICWIDGET_H

#include "ClinicModel.h"
#include "ClinicService.h"

#include <QWidget>
#include <QVector>

class QLineEdit;
class QTextEdit;
class QPushButton;
class QTableWidget;


class ClinicWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClinicWidget(QWidget *parent = nullptr);

private:
    QVector<Clinic> clinics;

    ClinicService* clinicService;

    QLineEdit* searchEdit;

    QPushButton* refreshBtn;


    QTableWidget* clinicTable;


    QLineEdit* clinicNameEdit;

    QLineEdit* locationEdit;

    QTextEdit* descriptionEdit;


    QPushButton* addBtn;

    QPushButton* updateBtn;

    QPushButton* deleteBtn;

    QPushButton* clearBtn;



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

private slots:

    void addClinic();

    void updateClinic();

    void deleteClinic();

    void searchClinic();

    void handleTableClicked(int row, int column);

    void handleClinicsLoaded(QVector<Clinic> clinics);

    void handleApiError(QString message);
};

#endif