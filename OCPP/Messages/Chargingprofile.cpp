#include "Chargingprofile.h"

ChargingProfile::ChargingProfile(const QJsonObject &obj)
{
#define transformatorInt(obj, var) \
    if(obj.contains(#var)){\
        var = obj[#var].toInt();\
    }

    transformatorInt(obj, chargingProfileId);
    transformatorInt(obj, transactionId);
    transformatorInt(obj, stackLevel);

#define transformatorStr(obj, var) \
    if(obj.contains(#var)){\
        var = obj[#var].toString();\
    }

    transformatorStr(obj, chargingProfilePurpose);
    transformatorStr(obj, chargingProfileKind);
    transformatorStr(obj, recurrencyKind);

    if(obj.contains("validFrom")) {
        validFrom = QDateTime::fromString(obj["validFrom"].toString(), Qt::ISODateWithMs);
    }
    if(obj.contains("validTo")) {
        validTo = QDateTime::fromString(obj["validTo"].toString(), Qt::ISODateWithMs);
    }

    if(obj.contains("chargingSchedule")) {
        chargingSchedule = ChargingSchedule(obj["chargingSchedule"].toObject());
    }
}

ChargingSchedule ChargingProfile::Schedule() const
{
    return chargingSchedule;
}
