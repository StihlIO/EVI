#ifndef STOPTRANSACTION_H
#define STOPTRANSACTION_H

#include "OCPP/Ocpp16Origin.h"
#include "OCPP/Ocpp16Constant.h"
#include "Metervalues.h"

#include <optional>
#include <QDateTime>

class StopTransaction : public OCPP16Origin
{
    QString idTag;
    int meterStop;
    std::optional<QDateTime> timestamp;
    int transactionId;
    OCPP16_Reason reason;
    MeterValue transactionData;

public:
    StopTransaction(int transactionId, int meterStop);
    StopTransaction(CLQString idTag, int meterStop, const QDateTime &timeStamp, int transactionId, OCPP16_Reason reason, const MeterValue &transactionData);

    QString Name() const;
    QJsonObject Json() const;
};

#endif // STOPTRANSACTION_H
