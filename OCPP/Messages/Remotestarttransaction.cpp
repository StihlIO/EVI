#include "Remotestarttransaction.h"

RemoteStartTransaction::RemoteStartTransaction(const QJsonObject &obj)
{
    if(obj.contains("connectorId")){
        connectorId = obj["connectorId"].toInt();
    }
    if(obj.contains("idTag")){
        valid = true;
        idTag = obj["idTag"].toString();
    }
    if(obj.contains("chargingProfile")){
        chargingProfile = ChargingProfile(obj["chargingProfile"].toObject());
    }
}

int RemoteStartTransaction::Connector() const
{
    return connectorId;
}

QString RemoteStartTransaction::IdTag() const
{
    return idTag;
}

bool RemoteStartTransaction::IsValid() const
{
    return valid;
}

ChargingProfile RemoteStartTransaction::Profile() const
{
    return chargingProfile;
}
