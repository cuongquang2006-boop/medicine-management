#ifndef MEDICINEMODEL_H
#define MEDICINEMODEL_H

#include <QString>

struct Medicine
{
    int id;

    QString name;

    int stock;

    double price;

    QString createdAt;
};

#endif