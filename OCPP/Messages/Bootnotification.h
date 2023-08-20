#ifndef BOOTNOTIFICATION_H
#define BOOTNOTIFICATION_H

#include "OCPP/Ocpp16Origin.h"

class BootNotification : public OCPP16Origin
{
    QString chargeBoxSerialNumber;
    QString chargePointModel;
    QString chargePointSerialNumber;
    QString chargePointVendor;
    QString firmwareVersion;
    QString iccid;
    QString imsi;
    QString meterSerialNumber;
    QString meterType;

public:

    BootNotification(CLQString chargePointModel, CLQString chargePointVendor);
    BootNotification(CLQString chargeBoxSerialNumber, CLQString chargePointModel, CLQString chargePointSerialNumber, CLQString chargePointVendor, CLQString firmwareVersion,
                     CLQString iccid, CLQString imsi, CLQString meterSerialNumber, CLQString meterType);
    QString Name() const;
    QJsonObject Json() const;
};

#endif // BOOTNOTIFICATION_H
