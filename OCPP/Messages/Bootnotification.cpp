#include "Bootnotification.h"

BootNotification::BootNotification(CLQString chargePointModel, CLQString chargePointVendor)
{
    this->chargePointModel = chargePointModel;
    this->chargePointVendor = chargePointVendor;
}

BootNotification::BootNotification(CLQString chargeBoxSerialNumber, CLQString chargePointModel, CLQString chargePointSerialNumber,
                                   CLQString chargePointVendor, CLQString firmwareVersion, CLQString iccid, CLQString imsi,
                                   CLQString meterSerialNumber, CLQString meterType) : BootNotification(chargePointModel, chargePointVendor)
{
    this->chargeBoxSerialNumber = chargeBoxSerialNumber;
    this->chargePointSerialNumber = chargePointSerialNumber;
    this->firmwareVersion = firmwareVersion;
    this->iccid = iccid;
    this->imsi = imsi;
    this->meterSerialNumber = meterSerialNumber;
    this->meterType = meterType;
}

QString BootNotification::Name() const
{
    return "BootNotification";
}

QJsonObject BootNotification::Json() const
{
    QJsonObject obj;
    obj.insert("chargeBoxSerialNumber", chargeBoxSerialNumber);
    obj.insert("chargePointModel", chargePointModel);
    obj.insert("chargePointSerialNumber", chargePointSerialNumber);
    obj.insert("chargePointVendor", chargePointVendor);
    obj.insert("firmwareVersion", firmwareVersion);
    obj.insert("iccid", iccid);
    obj.insert("imsi", imsi);
    obj.insert("meterSerialNumber", meterSerialNumber);
    obj.insert("meterType", meterType);
    return obj;
}
