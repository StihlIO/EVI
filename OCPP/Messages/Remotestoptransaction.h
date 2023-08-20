#ifndef REMOTESTOPTRANSACTION_H
#define REMOTESTOPTRANSACTION_H

#include <optional>
#include <QJsonObject>

class RemoteStopTransaction
{
    std::optional<int> transactionId;
public:
    RemoteStopTransaction(const QJsonObject &obj);
    bool IsValid() const;
    int TransactionId() const;
};

#endif // REMOTESTOPTRANSACTION_H
