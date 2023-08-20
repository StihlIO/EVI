#include "RemotestarttransactionResp.h"

RemoteStartTransactionResp::RemoteStartTransactionResp(OCPP16_RemoteStartStopStatus status)
{
    this->status = status;
}

QString RemoteStartTransactionResp::Name() const
{
    return "RemoteStartTransactionConf";
}

QJsonObject RemoteStartTransactionResp::Json() const
{
    QJsonObject obj;
    obj.insert("status", status);
    return obj;
}
