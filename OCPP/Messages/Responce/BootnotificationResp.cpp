#include "BootnotificationResp.h"

BootNotificationResp::BootNotificationResp(const QJsonObject &obj)
{
    if(obj.contains("currentTime")) {
        currentTime = QDateTime::fromString(obj["currentTime"].toString(), Qt::ISODateWithMs);
    }
    if(obj.contains("interval")) {
        interval = obj["interval"].toInt();
    }
    if(obj.contains("status")) {
        status = obj["status"].toString();
    }
}

QString BootNotificationResp::Status() const
{
    return status;
}

int BootNotificationResp::Interval() const
{
    return interval;
}
