#include "AuthorizeResp.h"

AuthorizeResp::AuthorizeResp(const QJsonObject &obj)
{
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

bool AuthorizeResp::IsValid() const
{
    return idTagInfo.status.has_value();
}

IdTagInfo AuthorizeResp::getIdTagInfo() const
{
    return idTagInfo;
}
