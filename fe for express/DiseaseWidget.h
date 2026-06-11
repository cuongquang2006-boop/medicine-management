#ifndef DISEASEWIDGET_H
#define DISEASEWIDGET_H

#include "DiseaseModel.h"
#include "DiseaseService.h"

#include <QWidget>
#include <QVector>

class QLineEdit;
class QTextEdit;
class QComboBox;
class QPushButton;
class QTableWidget;


class DiseaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DiseaseWidget(QWidget *parent = nullptr);

private:

    DiseaseService* diseaseService;

    QLineEdit* searchEdit;

    QComboBox* clinicFilterBox;

    QPushButton* refreshBtn;


    QTableWidget* diseaseTable;

    QLineEdit* diseaseNameEdit;

    QComboBox* clinicBox;

    QTextEdit* symptomsEdit;

    QTextEdit* descriptionEdit;

    QPushButton* addBtn;

    QPushButton* updateBtn;

    QPushButton* deleteBtn;

    QPushButton* clearBtn;

    QVector<Disease> diseases;

    int currentSelectedRow = -1;

private:

    void setupUI();

    void setupSearchArea();

    void setupTable();

    void setupForm();

    void setupButtons();

    void setupStyles();

    void setupConnections();

    void clearForm();

    bool validateInput();

    void fillFormFromTable(int row);

    void refreshTable();

private slots:

    void addDisease();

    void updateDisease();

    void deleteDisease();

    void searchDisease();

    void handleTableClicked(
        int row,
        int column
        );

    void handleDiseasesLoaded(
        QVector<Disease> data
        );

    void handleApiError(
        QString message
        );
};

#endif