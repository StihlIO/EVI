#include "RemotestoptransactionResp.h"

RemoteStopTransactionResp::RemoteStopTransactionResp(OCPP16_RemoteStartStopStatus status)
{
    this->status = status;
}

QString RemoteStopTransactionResp::Name() const
{
    return "RemoteStopTransaction";
}

QJsonObject RemoteStopTransactionResp::Json() const
{
    QJsonObject obj;
    obj.insert("status", status);
    return obj;
}
