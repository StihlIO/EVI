#ifndef REMOTESTARTTRANSACTIONRESP_H
#define REMOTESTARTTRANSACTIONRESP_H

#include "OCPP/Ocpp16Origin.h"
#include "OCPP/Enumeration/Ocpp16_Remotestartstopstatus.h"

class RemoteStartTransactionResp : public OCPP16Origin
{
    OCPP16_RemoteStartStopStatus status;
public:
    RemoteStartTransactionResp(OCPP16_RemoteStartStopStatus status);

    QString Name() const;
    QJsonObject Json() const;
};

#endif // REMOTESTARTTRANSACTIONRESP_H
