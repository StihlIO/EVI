#include "Remotestoptransaction.h"

RemoteStopTransaction::RemoteStopTransaction(const QJsonObject &obj)
{
    if(obj.contains("transactionId")) {
        transactionId = obj["transactionId"].toInt();
    }
}

bool RemoteStopTransaction::IsValid() const
{
    return transactionId.has_value();
}

int RemoteStopTransaction::TransactionId() const
{
    return transactionId.value_or(0);
}
