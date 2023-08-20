#include "Chargingscheduleperiod.h"

ChargingSchedulePeriod::ChargingSchedulePeriod(const QJsonObject &obj)
{
    if(obj.contains("limit")){
        limit = obj["limit"].toInt();
    }
}

int ChargingSchedulePeriod::Limit() const
{
    return limit;
}
