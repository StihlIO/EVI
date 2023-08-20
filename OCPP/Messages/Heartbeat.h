#ifndef HEARBEAT_H
#define HEARBEAT_H

#include "OCPP/Ocpp16Origin.h"

class Heartbeat : public OCPP16Origin
{
public:
    QString Name() const;
    QJsonObject Json() const;
};

#endif // HEARBEAT_H
