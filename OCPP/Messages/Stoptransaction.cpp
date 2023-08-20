#include "Stoptransaction.h"

#include <QJsonArray>

StopTransaction::StopTransaction(int transactionId, int meterStop)
{
    this->transactionId = transactionId;
    this->meterStop = meterStop;
}

StopTransaction::StopTransaction(CLQString idTag, int meterStop, const QDateTime &timeStamp,
                                 int transactionId,
                                 OCPP16_Reason reason,
                                 const MeterValue &transactionData) : StopTransaction(transactionId, meterStop)
{
    this->idTag = idTag;
    this->timestamp = timeStamp;
    this->reason = reason;
    this->transactionData = transactionData;
}

QString StopTransaction::Name() const
{
    return "StopTransaction";
}

QJsonObject StopTransaction::Json() const
{
    QJsonObject obj;
    NZStringInsert(obj, idTag);
    obj.insert("meterStop", meterStop);
    obj.insert("timestamp", timestamp.value_or(QDateTime::currentDateTime()).toString(Qt::ISODateWithMs));
    obj.insert("transactionId", transactionId);
    NZStringInsert(obj, reason);
    auto meters = transactionData.Json();
    if(meters.length() > 0) {
        QJsonArray meterValues;
        meterValues.append(meters);
        obj.insert("transactionData", meterValues);
    }

    return obj;
}
