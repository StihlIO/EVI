#include "Chargingschedule.h"

#include <QJsonArray>

ChargingSchedule::ChargingSchedule(const QJsonObject &obj)
{
    if(obj.contains("duration")) {
        duration = obj["duration"].toInt();
    }
    if(obj.contains("startSchedule")) {
        startSchedule = QDateTime::fromString(obj["startSchedule"].toString(), Qt::ISODateWithMs);
    }
    if(obj.contains("chargingRateUnit")) {
        chargingRateUnit = obj["chargingRateUnit"].toString();
    }
    if(obj.contains("chargingSchedulePeriod")) {
        QJsonArray arrayOfPeriods = obj["chargingSchedulePeriod"].toArray();
        for(auto obj : arrayOfPeriods) {
            chargingSchedulePeriod.append(ChargingSchedulePeriod(obj.toObject()));
        }
    }
    if(obj.contains("minChargingRate")) {
        minChargingRate = obj["minChargingRate"].toDouble();
    }
}

QList<ChargingSchedulePeriod> ChargingSchedule::SchedulePeriod() const
{
    return chargingSchedulePeriod;
}
