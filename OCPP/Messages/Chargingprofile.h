#ifndef CHARGINGPROFILE_H
#define CHARGINGPROFILE_H

#include "OCPP/Enumeration/Ocpp16_Enumeration.h"
#include "Chargingschedule.h"
#include <QDateTime>
#include <QJsonObject>

class ChargingProfile
{
    int chargingProfileId;
    int transactionId;
    int stackLevel;
    OCPP16_ChargingProfilePurposeType chargingProfilePurpose;
    OCPP16_ChargingProfileKindType chargingProfileKind;
    OCPP16_RecurrencyKindType recurrencyKind;

    QDateTime validFrom;
    QDateTime validTo;

    ChargingSchedule chargingSchedule;

public:
    ChargingProfile(){}
    ChargingProfile(const QJsonObject &obj);
    ChargingSchedule Schedule() const;
};

#endif // CHARGINGPROFILE_H
