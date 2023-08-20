#ifndef REMOTESTOPTRANSACTIONRESP_H
#define REMOTESTOPTRANSACTIONRESP_H

#include "OCPP/Ocpp16Origin.h"
#include "OCPP/Enumeration/Ocpp16_Enumeration.h"

class RemoteStopTransactionResp : public OCPP16Origin
{
    OCPP16_RemoteStartStopStatus status;

public:
    RemoteStopTransactionResp(OCPP16_RemoteStartStopStatus status);

    QString Name() const;
    QJsonObject Json() const;
};

#endif // REMOTESTOPTRANSACTIONRESP_H
