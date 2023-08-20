#ifndef SAMPLEDVALUE_H
#define SAMPLEDVALUE_H

#include "OCPP/Enumeration/Ocpp16_Enumeration.h"
#include "OCPP/Ocpp16Origin.h"

class SampledValue : public OCPP16Origin
{
    QString value;
    OCPP16_ReadingContext context;
    OCPP16_ValueFormat format;
    OCPP16_Measurand measurand;
    OCPP16_Phase phase;
    OCPP16_Location location;
    OCPP16_UnitOfMeasure unit;

public:
    SampledValue(CLQString value);
    SampledValue(CLQString value, OCPP16_ReadingContext context,
                 OCPP16_ValueFormat format,
                 OCPP16_Measurand measurand,
                 OCPP16_Phase phase,
                 OCPP16_Location location,
                 OCPP16_UnitOfMeasure unit);
    virtual ~SampledValue() {}
    QString Name() const;
    QJsonObject Json() const;
};

#endif // SAMPLEDVALUE_H
