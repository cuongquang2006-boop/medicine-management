#ifndef MEDICINESERVICE_H
#define MEDICINESERVICE_H

#include "MedicineModel.h"

#include <QObject>
#include <QVector>

class QNetworkAccessManager;
class QNetworkReply;

class MedicineService : public QObject
{
    Q_OBJECT

public:

    explicit MedicineService(
        QObject *parent = nullptr
        );

    void fetchMedicines();

    void createMedicine(
        const Medicine& medicine
        );

    void updateMedicine(
        const Medicine& medicine
        );

    void deleteMedicine(
        int medicineId
        );

signals:

    void medicinesLoaded(
        QVector<Medicine> medicines
        );

    void errorOccurred(
        QString message
        );

private slots:

    void handleMedicineResponse(
        QNetworkReply* reply
        );

private:

    QNetworkAccessManager* manager;
};

#endif