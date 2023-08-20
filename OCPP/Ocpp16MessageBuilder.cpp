#include "Ocpp16MessageBuilder.h"

#include <QJsonArray>
#include <QUuid>

Ocpp16MessageBuilder *Ocpp16MessageBuilder::I()
{
    static Ocpp16MessageBuilder instance;
    return &instance;
}

Ocpp16Message Ocpp16MessageBuilder::Build(OCPP16MessageType type, const OCPP16Origin *origin, QString &uid) const
{
    if(type == OCPP16MessageType::CALLRESULT) {
        return Ocpp16Message(type, uid, origin->Json());
    }
    uid = QUuid::createUuid().toString(QUuid::StringFormat::WithoutBraces);
    return Ocpp16Message(type, uid, origin->Name(), origin->Json());
}
