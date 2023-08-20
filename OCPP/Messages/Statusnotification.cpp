#include "Statusnotification.h"

#include <QLocale>

StatusNotification::StatusNotification(int connectorId, OCPP16_ErrorValue errorCode, OCPP16_Status status)
{
    this->connectorId = connectorId;
    this->errorCode = errorCode;
    this->status = status;
}

StatusNotification::StatusNotification(int connectorId, OCPP16_ErrorValue errorCode, CLQString info,
                                       OCPP16_Status status, const QDateTime &timeStamp,
                                       CLQString vendorId, CLQString vendorErrorCode) : StatusNotification(connectorId, errorCode, status)
{
    this->timestamp = timeStamp;
    this->info = info;
    this->vendorId = vendorId;
    this->vendorErrorCode = vendorErrorCode;
}

QString StatusNotification::Name() const
{
    return "StatusNotification";
}

QJsonObject StatusNotification::Json() const
{
    QJsonObject obj;
    obj.insert("connectorId", connectorId);
    obj.insert("errorCode", errorCode);
    obj.insert("info", info);
    obj.insert("status", status);
    obj.insert("timestamp", timestamp.value_or(QDateTime::currentDateTime()).toString(Qt::ISODateWithMs));
    obj.insert("vendorId", vendorId);
    obj.insert("vendorErrorCode", vendorErrorCode);
    return obj;
}
