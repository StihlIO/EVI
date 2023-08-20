#ifndef OCPP16MESSAGE_H
#define OCPP16MESSAGE_H

#include "Messages/Bootnotification.h"
#include "Messages/Heartbeat.h"
#include "Messages/Authorize.h"
#include "Messages/Statusnotification.h"
#include "Messages/Metervalues.h"
#include "Messages/Starttransaction.h"
#include "Messages/Stoptransaction.h"
#include "Messages/Remotestoptransaction.h"
#include "Messages/Remotestarttransaction.h"

#include "Messages/Responce/AuthorizeResp.h"
#include "Messages/Responce/BootnotificationResp.h"
#include "Messages/Responce/StarttransactionResp.h"
#include "Messages/Responce/RemotestarttransactionResp.h"
#include "Messages/Responce/RemotestoptransactionResp.h"

#include "Ocpp16Constant.h"
#include "OCPP/Enumeration/Ocpp16_Enumeration.h"

#include <QString>
#include <QJsonObject>

class Ocpp16Message
{
    QJsonObject payLoad;
    QString messageId;
    QString action;
    OCPP16MessageType type;
    QString jsonText;

public:

    Ocpp16Message(OCPP16MessageType type, QString messageId, QString action, QJsonObject payLoad);
    Ocpp16Message(OCPP16MessageType type, QString messageId, QJsonObject payLoad);
    QString AsString() const;
    QString Action() const;
    OCPP16MessageType Type() const;
    QString MessageId() const;
};

#endif // OCPP16MESSAGE_H
