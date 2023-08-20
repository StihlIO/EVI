#ifndef REMOTESTARTTRANSACTION_H
#define REMOTESTARTTRANSACTION_H

#include <QJsonObject>

#include "Chargingprofile.h"

class RemoteStartTransaction
{
    int connectorId;
    QString idTag;
    ChargingProfile chargingProfile;

    bool valid;

public:
    RemoteStartTransaction(const QJsonObject &obj);
    int Connector() const;
    QString IdTag() const;
    bool IsValid() const;
    ChargingProfile Profile() const;
};

#endif // REMOTESTARTTRANSACTION_H
