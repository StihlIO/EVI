#include "StarttransactionResp.h"

IdTagInfo StartTransactionResp::getIdTagInfo() const
{
    return idTagInfo;
}

int StartTransactionResp::getTransactionId() const
{
    return transactionId.value_or(0);
}

StartTransactionResp::StartTransactionResp(const QJsonObject &obj)
{
    if(obj.contains("transactionId")) {
        transactionId = obj["transactionId"].toInt();
    }
    if(obj.contains("idTagInfo")) {
        auto taginfo = obj["idTagInfo"].toObject();
        if(taginfo.contains("expiryDate")) {
            idTagInfo.expiryDate = QDateTime::fromString(taginfo["expiryDate"].toString(), Qt::ISODateWithMs);
        }
        if(taginfo.contains("parentIdTag")) {
            idTagInfo.parentIdTag = taginfo["parentIdTag"].toString();
        }
        if(taginfo.contains("status")) {
            idTagInfo.status = OCPP16_AuthorizationStatus(taginfo["status"].toString());
        }
    }
}

bool StartTransactionResp::IsValid()
{
    return transactionId.has_value() && idTagInfo.status.has_value();
}
