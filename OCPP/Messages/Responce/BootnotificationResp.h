#ifndef BOOTNOTIFICATIONRESP_H
#define BOOTNOTIFICATIONRESP_H

#include <QDateTime>
#include <QJsonObject>
#include <QString>

#include "OCPP/Enumeration/Ocpp16_Enumeration.h"

class BootNotificationResp
{
    QDateTime currentTime;
    int interval;
    OCPP16_RegistrationStatus status;

public:
    BootNotificationResp(const QJsonObject &obj);
    QString Status() const;
    int Interval() const;
};

#endif // BOOTNOTIFICATIONRESP_H
