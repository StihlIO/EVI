#include "Metervalues.h"

#include <QJsonArray>

MeterValues::MeterValues(int connectorId, QString value)
{
    this->connectorId = connectorId;
    this->transactionId = 0;
    meterValues.append(MeterValue(value));
}

MeterValues::MeterValues(int connectorId, int transactionId, const QList<MeterValue> &values)
{
    this->connectorId = connectorId;
    this->transactionId = transactionId;
    meterValues = values;
}

QString MeterValues::Name() const
{
    return "MeterValues";
}

QJsonObject MeterValues::Json() const
{
    QJsonObject obj;
    obj.insert("connectorId", connectorId);
    obj.insert("transactionId", transactionId);
    QJsonArray meterValuesJson;
    for(auto mv : meterValues) {
        meterValuesJson.append(mv.Json());
    }
    obj.insert("meterValue", meterValuesJson);
    return obj;
}
