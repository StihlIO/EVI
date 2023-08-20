#include "Metervalue.h"

#include <QJsonArray>

MeterValue::MeterValue()
{
}

MeterValue::MeterValue(CLQString value)
{
    sampledValues.append(SampledValue(value));
}

MeterValue::MeterValue(const QDateTime &timestamp, const QList<SampledValue> &values)
{
    this->timestamp = timestamp;
    sampledValues = values;
}

QString MeterValue::Name() const
{
    return "MeterValue";
}

QJsonObject MeterValue::Json() const
{
    QJsonObject obj;
    QJsonArray sampledValuesJson;
    if(sampledValues.count()) {
        for(auto sv : sampledValues) {
            sampledValuesJson.append(sv.Json());
        }
        obj.insert("sampledValue", sampledValuesJson);
        obj.insert("timestamp", timestamp.value_or(QDateTime::currentDateTime()).toString(Qt::ISODateWithMs));
    }

    return obj;
}
