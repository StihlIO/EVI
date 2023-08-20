#ifndef METERVALUE_H
#define METERVALUE_H

#include "Sampledvalue.h"

#include <optional>
#include <QDateTime>

class MeterValue : public OCPP16Origin
{
    QList<SampledValue> sampledValues;
    std::optional<QDateTime> timestamp;
public:
    MeterValue();
    MeterValue(CLQString value);
    MeterValue(const QDateTime &timestamp, const QList<SampledValue> &values);
    virtual ~MeterValue() {}

    QString Name() const;
    QJsonObject Json() const;
};

#endif // METERVALUE_H
