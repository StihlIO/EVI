#include "Sampledvalue.h"

SampledValue::SampledValue(CLQString value)
{
    this->value = value;
}

SampledValue::SampledValue(CLQString value, OCPP16_ReadingContext context,
                           OCPP16_ValueFormat format,
                           OCPP16_Measurand measurand,
                           OCPP16_Phase phase,
                           OCPP16_Location location,
                           OCPP16_UnitOfMeasure unit) : SampledValue(value)
{
    this->context = context;
    this->format = format;
    this->measurand = measurand;
    this->phase = phase;
    this->location = location;
    this->unit = unit;
}

QString SampledValue::Name() const
{
    return "SampledValue";
}

QJsonObject SampledValue::Json() const
{
    QJsonObject obj;
    NZStringInsert(obj, value);
    NZStringInsert(obj, context);
    NZStringInsert(obj, format);
    NZStringInsert(obj, measurand);
    NZStringInsert(obj, phase);
    NZStringInsert(obj, location);
    NZStringInsert(obj, unit);
    return obj;
}
