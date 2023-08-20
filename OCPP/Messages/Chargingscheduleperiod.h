#ifndef CHARGINGSCHEDULEPERIOD_H
#define CHARGINGSCHEDULEPERIOD_H

#include <QJsonObject>

class ChargingSchedulePeriod
{
    int startPeriod;
    int limit;
    int numberPhases;

public:
    ChargingSchedulePeriod(const QJsonObject &obj);
    int Limit() const;
};

#endif // CHARGINGSCHEDULEPERIOD_H
