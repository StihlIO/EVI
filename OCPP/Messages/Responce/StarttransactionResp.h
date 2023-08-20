#ifndef STARTTRANSACTIONRESP_H
#define STARTTRANSACTIONRESP_H

#include "OCPP/Ocpp16Constant.h"
#include "OCPP/Enumeration/Ocpp16_Authorizationstatus.h"
#include "OCPP/Messages/Idtaginfo.h"

#include <optional>
#include <QDateTime>
#include <QJsonObject>

class StartTransactionResp
{
    IdTagInfo idTagInfo;
    std::optional<int> transactionId;

public:
    StartTransactionResp(const QJsonObject &obj);
    bool IsValid();
    IdTagInfo getIdTagInfo() const;
    int getTransactionId() const;
};

#endif // STARTTRANSACTIONRESP_H
