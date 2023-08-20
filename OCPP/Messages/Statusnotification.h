#ifndef STATUSNOTIFICATION_H
#define STATUSNOTIFICATION_H

#include "OCPP/Ocpp16Origin.h"
#include "OCPP/Ocpp16Constant.h"

#include "OCPP/Enumeration/Ocpp16_Enumeration.h"

#include <optional>
#include <QDateTime>

class StatusNotification : public OCPP16Origin
{
    std::optional<QDateTime> timestamp;

    int connectorId;
    OCPP16_ErrorValue errorCode;
    OCPP16_Status status;

    QString info;
    QString vendorId;
    QString vendorErrorCode;

public:
    StatusNotification(int connectorId, OCPP16_ErrorValue errorCode, OCPP16_Status status);
    StatusNotification(int connectorId, OCPP16_ErrorValue errorCode, CLQString info, OCPP16_Status status, const QDateTime &timeStamp, CLQString vendorId, CLQString vendorErrorCode);

    QString Name() const;
    QJsonObject Json() const;
};

#endif // STATUSNOTIFICATION_H
