#ifndef OCPP16MESSAGEBUILDER_H
#define OCPP16MESSAGEBUILDER_H

#include "Ocpp16Messages.h"

#include <QString>

class Ocpp16MessageBuilder
{
public:
    static Ocpp16MessageBuilder *I();
    Ocpp16Message Build(OCPP16MessageType type, const OCPP16Origin *origin, QString &uid) const;
};

#endif // OCPP16MESSAGEBUILDER_H
