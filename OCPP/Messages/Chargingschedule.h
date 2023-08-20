#ifndef CHARGINGSCHEDULE_H
#define CHARGINGSCHEDULE_H

#include <QDateTime>
#include <QJsonObject>
#include "OCPP/Enumeration/Ocpp16_Enumeration.h"
#include "Chargingscheduleperiod.h"

class ChargingSchedule
{
    int duration;
    QDateTime startSchedule;
    OCPP16_ChargingRateUnitType chargingRateUnit;
    QList<ChargingSchedulePeriod> chargingSchedulePeriod;
    double minChargingRate; // Decimal one digit fraction
public:
    ChargingSchedule() {}
    ChargingSchedule(const QJsonObject &obj);
    QList<ChargingSchedulePeriod> SchedulePeriod() const;
};

#endif // CHARGINGSCHEDULE_H
