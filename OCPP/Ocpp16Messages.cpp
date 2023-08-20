#include "Ocpp16Messages.h"

#include <QJsonDocument>
#include <QJsonArray>

Ocpp16Message::Ocpp16Message(OCPP16MessageType type, QString messageId, QString action, QJsonObject payLoad)
{
    this->payLoad = payLoad;
    this->messageId = messageId;
    this->action = action;
    this->type = type;

    QJsonArray jArr;
    jArr.append(static_cast<int>(type));
    jArr.append(messageId);
    jArr.append(action);
    jArr.append(payLoad);
    jsonText = QJsonDocument(jArr).toJson(QJsonDocument::Indented);
}

Ocpp16Message::Ocpp16Message(OCPP16MessageType type, QString messageId, QJsonObject payLoad)
{
    this->payLoad = payLoad;
    this->messageId = messageId;
    this->type = type;

    QJsonArray jArr;
    jArr.append(static_cast<int>(type));
    jArr.append(messageId);
    jArr.append(payLoad);
    jsonText = QJsonDocument(jArr).toJson(QJsonDocument::Indented);
}

QString Ocpp16Message::AsString() const
{
    return jsonText;
}

QString Ocpp16Message::Action() const
{
    return action;
}

OCPP16MessageType Ocpp16Message::Type() const
{
    return type;
}

QString Ocpp16Message::MessageId() const
{
    return messageId;
}
