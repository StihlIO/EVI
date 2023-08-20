#ifndef IDTAGINFO_H
#define IDTAGINFO_H

#include "OCPP/Enumeration/Ocpp16_Authorizationstatus.h"

#include <optional>
#include <QDateTime>

struct IdTagInfo {
    QDateTime expiryDate;
    QString parentIdTag;
    std::optional<OCPP16_AuthorizationStatus> status;
};

#endif // IDTAGINFO_H
