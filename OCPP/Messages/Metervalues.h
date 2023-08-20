#ifndef METERVALUES_H
#define METERVALUES_H

#include "OCPP/Ocpp16Origin.h"
#include "OCPP/Ocpp16Constant.h"
#include "OCPP/Enumeration/Ocpp16_Enumeration.h"
#include "Metervalue.h"

#include <QDateTime>

class MeterValues : public OCPP16Origin
{
    int connectorId;
    int transactionId;
    QList<MeterValue> meterValues;

public:

    MeterValues(int connectorId, QString value);
    MeterValues(int connectorId, int transactionId, const QList<MeterValue> &valuess);

    QString Name() const;
    QJsonObject Json() const;
};

#endif // METERVALUES_H
