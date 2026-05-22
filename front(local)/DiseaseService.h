#ifndef DISEASESERVICE_H
#define DISEASESERVICE_H

#include "DiseaseModel.h"

#include <QObject>
#include <QVector>

class QNetworkAccessManager;
class QNetworkReply;

class DiseaseService : public QObject
{
    Q_OBJECT

public:
    explicit DiseaseService(QObject *parent = nullptr);

    void fetchDiseases();

    void createDisease(const Disease& disease);

    void updateDisease(const Disease& disease);

    void deleteDisease(int diseaseId);

signals:

    void diseasesLoaded(QVector<Disease> diseases);
    void errorOccurred(QString message);

private slots:
    void handleDiseaseResponse(QNetworkReply* reply);

private:

    QNetworkAccessManager* manager;
};

#endif